#include "IM920SL.h"

IM920SL im920SL;
const unsigned long usb_baudrate = 115200;
const unsigned long im920SL_baudrate = 19200;

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
    for (uint8_t i = 0; i < im920SL.size() - 1; ++i) {
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
  im920SL.write(true);
  WaitForResponse(response_wait_ms);
  im920SL.clearSettings();
  WaitForResponse(response_wait_ms);
  im920SL.node(1);
  WaitForResponse(response_wait_ms);
  im920SL.groupMake();
  WaitForResponse(response_wait_ms);
  im920SL.channel(IM920SLParam::CHANNEL::CH360S_923_2MHz);
  WaitForResponse(response_wait_ms);
  im920SL.power(IM920SLParam::RF_POWER::POWER_10_mW);
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
    im920SL.broadcastString("hello");
    im920SL.broadcastString("send");

    delay(100);

    prev_ms = millis();
  }
}
