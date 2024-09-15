#ifndef IM920SL_CMD_LIST_H
#define IM920SL_CMD_LIST_H

namespace IM920SLCtrl {
namespace CMD {

enum TYPE { INFO, CTRL, FUNC, SETTING, SEND };

template <TYPE> struct Cmd {};

// Information-related commands
template <> struct Cmd<INFO> {
  static constexpr const char *UNIQUE_ID = "RDID ";
  static constexpr const char *RSSI = "RDRS ";
  static constexpr const char *VERSION = "RDVR ";
  static constexpr const char *ALL = "RPRM ";
};

// Control-related commands
template <> struct Cmd<CTRL> {
  static constexpr const char *BAUDRATE = "SBRT ";
  static constexpr const char *RESET = "SRST ";
  static constexpr const char *CLEAR_SETTINGS = "PCLR ";
};

// Function-related commands
template <> struct Cmd<FUNC> {
  static constexpr const char *EN_SAVE = "ENWR ";
  static constexpr const char *DS_SAVE = "DSWR ";
  static constexpr const char *EN_CHAR_IO = "ECIO ";
  static constexpr const char *DS_CHAR_IO = "DCIO ";
  static constexpr const char *EN_SLEEP = "DSRX ";
  static constexpr const char *DS_SLEEP = "ENRX ";
  static constexpr const char *EN_RETRY = "ENAR ";
  static constexpr const char *DS_RETRY = "DSAR ";
  static constexpr const char *EN_ANSWER_BACK = "EABK ";
  static constexpr const char *DS_ANSWER_BACK = "DABK ";
  static constexpr const char *EN_REPEATER = "ERPT ";
  static constexpr const char *DS_REPEATER = "DRPT ";
};

// Setting-related commands
template <> struct Cmd<SETTING> {
  static constexpr const char *W_NODE = "STNN ";
  static constexpr const char *R_NODE = "RDNN ";
  static constexpr const char *W_DEST_NODE = "STTN ";
  static constexpr const char *R_DEST_NODE = "RDTN ";
  static constexpr const char *W_GROUP = "STGN ";
  static constexpr const char *R_GROUP = "RDGN ";
  static constexpr const char *W_CHANNEL = "STCH ";
  static constexpr const char *R_CHANNEL = "RDCH ";
  static constexpr const char *W_RF_POWER = "STPO ";
  static constexpr const char *R_RF_POWER = "RDPO ";
  static constexpr const char *W_RF_RATE = "STRT ";
  static constexpr const char *R_RF_RATE = "RDRT ";
  static constexpr const char *W_SLEEP_TIME = "SSTM ";
  static constexpr const char *R_SLEEP_TIME = "RSTM ";
  static constexpr const char *W_WAIT_TIME = "SWTM ";
  static constexpr const char *R_WAIT_TIME = "RWTM ";
};

// Sending-related commands
template <> struct Cmd<SEND> {
  static constexpr const char *BROADCAST_FIXED = "TXDT ";
  static constexpr const char *BROADCAST = "TXDA ";
  static constexpr const char *UNICAST = "TXDU ";
  static constexpr const char *SEND_BACK = "TXSB ";
  static constexpr const char *DELEGATE = "TXDG ";
};

} // namespace CMD
} // namespace IM920SLCtrl

#endif /* IM920SL_CMD_LIST_H */
