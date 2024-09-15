#include "IM920SL.h"

IM920SL im920SL;
const size_t usb_baudrate = 115200;
const size_t im920SL_baudrate = 19200;

const uint32_t response_wait_ms = 500;
uint32_t prev_ms = 0;

void WaitForResponse(uint16_t ms = 0) {
  delay(ms);

  im920SL.update();
  if (im920SL.available()) {
    im920SL.print();
    im920SL.pop();
  }
}

void HandleResponse() {
  im920SL.update();
  if (im920SL.available()) {
    // get remote device info
    Serial.print(im920SL.remoteNode(), HEX);
    Serial.print(",");
    Serial.print(im920SL.remoteUID(), HEX);
    Serial.print(",");
    Serial.print(im920SL.remoteRSSI(), HEX);
    Serial.print(":");

    // get & handle received data
    for (size_t i = 0; i < im920SL.size() - 1; ++i) {
      Serial.print(im920SL.data(i), HEX);
      Serial.print(",");
    }
    Serial.println(im920SL.data(im920SL.size() - 1), HEX);

    im920SL.pop();
  }
}

void setup() {
  Serial.begin(usb_baudrate);

  // for Uno
  Serial.begin(im920SL_baudrate);
  im920SL.setup(Serial);

  // for Mega, Teensy, and other arduino which have multiple serial
  // Serial2.begin(im920SL_baudrate);
  // im920SL.setup(Serial2);

  delay(2000);

  Serial.println("write setting start");

  // write settings to IM920SL
  im920SL.writable(true);
  WaitForResponse(response_wait_ms);
  im920SL.clearSettings();
  WaitForResponse(response_wait_ms);
  //im920SL.eraseID();
  WaitForResponse(response_wait_ms);
  //im920SL.recvID(0x1234);
  WaitForResponse(response_wait_ms);
  im920SL.channel(IM920SLParam::CHANNEL::CH36_923_0MHZ);
  WaitForResponse(response_wait_ms);
  im920SL.power(IM920SLParam::RF_POWER::POWER_10_0_mW);
  WaitForResponse(response_wait_ms);
  im920SL.rate(IM920SLParam::RF_RATE::RATE_FAST);
  WaitForResponse(response_wait_ms);
  im920SL.reset();
  WaitForResponse(response_wait_ms);

  Serial.println("start test");
}

void loop() {
  HandleResponse();

  if (millis() - prev_ms > 1000) {
    // append data to buffer & send
    im920SL << "test" << 1;
    im920SL << "data" << 2 << 3 << 4;
    im920SL.send();

    delay(100);

    // send in one line
    im920SL.send(1, 2, 3, 4, 5, 6, 7, 8, 9, 10);

    prev_ms = millis();
  }
}
