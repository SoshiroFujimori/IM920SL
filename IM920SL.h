#ifndef ARDUINO_IM920SL_H
#define ARDUINO_IM920SL_H

#include "Arduino.h"
#include "IM920SL/IM920SLCommands.h"
#include "IM920SL/IM920SLSettings.h"
#include "IM920SL/Receiver.h"
#include "IM920SL/Sender.h"

class IM920SL : public IM920SLCtrl::Sender, public IM920SLCtrl::Receiver {
public:
  bool setup(Stream &s) {
    IM920SLCtrl::Sender::setup(s);
    IM920SLCtrl::Receiver::setup(s);
    return true;
  }

private:
};

namespace IM920SLParam = IM920SLCtrl;

#endif /* ARDUINO_IM920SL_H */
