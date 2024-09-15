# IM920SL
Interplan [IM920SL series](http://www.interplan.co.jp/solution/wireless/im920SL.php) wrapper for Arduino and openFrameworks

## Usage
### Set up IM920SL

```c++

#include "IM920SL.h"

IM920SL im920SL;

// setup IM920SL for Arduino
Serial1.begin(im920SL_baudrate);
im920SL.setup(Serial1);

// setup IM920SL for openFrameworks
ofSerial serial;
serial.setup("your serial device", im920SL_baudrate);
im920SL.setup(serial);

// write settings to IM920SL
im920SL.writable(true);
im920SL.clearSettings(); // set to factory default
im920SL.recvID(0x1234);
im920SL.channel(IM920SLParam::CHANNEL::CH36_923_0MHZ);
im920SL.power(IM920SLParam::RF_POWER::POWER_10_0_mW);
im920SL.rate(IM920SLParam::RF_RATE::RATE_FAST);
im920SL.reset();
```

### Reading Data
``` c++
im920SL.update();

if (im920SL.available())
{
    // get remote device info
    Serial.print(im920SL.remoteNode(), HEX); Serial.print(",");
    Serial.print(im920SL.remoteUID(),  HEX); Serial.print(",");
    Serial.print(im920SL.remoteRSSI(), HEX); Serial.print(":");

    // get & handle received data
    for (size_t i = 0; i < im920SL.size(); ++i)
    {
        Serial.print(im920SL.data(i), HEX);
        Serial.print(",");
    }

    // go to next data
    im920SL.pop();
}
```

### Sending Data

``` c++
// send in one line
im920SL.send(1, 2, 3, 4, 5, 6, 7, 8, 9, 10);

// append data to buffer & send
im920SL << "test" << 1;
im920SL << "data" << 2 << 3;
im920SL.send();

// same as above
im920SL.append("test");
im920SL.append(1);
im920SL.append("data");
im920SL.append(2);
im920SL.append(3);
im920SL.send();
```

## Parameters

``` c++
IM920SLParam::BAUDRATE::BPS_1200
IM920SLParam::BAUDRATE::BPS_2400
IM920SLParam::BAUDRATE::BPS_4800
IM920SLParam::BAUDRATE::BPS_9600
IM920SLParam::BAUDRATE::BPS_19200 // default
IM920SLParam::BAUDRATE::BPS_38400
IM920SLParam::BAUDRATE::BPS_57600
IM920SLParam::BAUDRATE::BPS_115200

IM920SLParam::CHANNEL::CH24_920_6MHZ // default
IM920SLParam::CHANNEL::CH25_920_8MHZ
IM920SLParam::CHANNEL::CH26_921_0MHZ
IM920SLParam::CHANNEL::CH27_921_2MHZ
IM920SLParam::CHANNEL::CH28_921_4MHZ
IM920SLParam::CHANNEL::CH29_921_6MHZ
IM920SLParam::CHANNEL::CH30_921_8MHZ
IM920SLParam::CHANNEL::CH31_922_0MHZ
IM920SLParam::CHANNEL::CH32_922_2MHZ
IM920SLParam::CHANNEL::CH33_922_4MHZ
IM920SLParam::CHANNEL::CH34_922_6MHZ
IM920SLParam::CHANNEL::CH35_922_8MHZ
IM920SLParam::CHANNEL::CH36_923_0MHZ
IM920SLParam::CHANNEL::CH37_923_2MHZ
IM920SLParam::CHANNEL::CH38_923_4MHZ

IM920SLParam::RF_POWER::POWER_0_1_mW
IM920SLParam::RF_POWER::POWER_1_0_mW
IM920SLParam::RF_POWER::POWER_10_0_mW // default

IM920SLParam::RF_RATE::RATE_FAST
IM920SLParam::RF_RATE::RATE_LONG // default
```

## Supported Platform

- Arduino Platforms
- openFrameworks (tested on 0.9.8)


## Notation

If you want to build the oF example, add IM920SL/IM920SL.h and IM920SL/IM920SL/* to your oF project.


## License

MIT