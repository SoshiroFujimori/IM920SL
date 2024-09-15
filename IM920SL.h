#ifndef ARDUINO_IM920SL_H
#define ARDUINO_IM920SL_H

#include "Arduino.h"
using SerialStream = Stream;
#include "IM920SL/IM920SLCommands.h"
#include "IM920SL/IM920SLSettings.h"
#include "IM920SL/Receiver.h"
#include "IM920SL/Sender.h"

template <typename S>
class IM920SL_ : public IM920SLCtrl::Sender<S>,
                 public IM920SLCtrl::Receiver<S> {
public:
  bool setup(S &s) {
    IM920SLCtrl::Sender<S>::setup(s);
    IM920SLCtrl::Receiver<S>::setup(s);
    return true;
  }

private:
};

using IM920SL = IM920SL_<SerialStream>;
namespace IM920SLParam = IM920SLCtrl;

#endif /* ARDUINO_IM920SL_H */
