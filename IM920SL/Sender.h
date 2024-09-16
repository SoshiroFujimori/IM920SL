#ifndef IM920SL_SENDER_H
#define IM920SL_SENDER_H

#include "Arduino.h"
#include "IM920SLCommands.h"
#include "IM920SLSettings.h"

namespace IM920SLCtrl {

class Sender {
public:
  Sender() {}
  ~Sender() {}

  bool setup(Stream &s) {
    stream = &s;
    stream->flush();
    return true;
  }

  // IM920 info
  void uniqueID() {
    appendStr(CMD::Cmd<CMD::TYPE::INFO>::UNIQUE_ID);
    write();
  }

  void rssi() {
    appendStr(CMD::Cmd<CMD::TYPE::INFO>::RSSI);
    write();
  }

  void version() {
    appendStr(CMD::Cmd<CMD::TYPE::INFO>::VERSION);
    write();
  }

  void all() {
    appendStr(CMD::Cmd<CMD::TYPE::INFO>::ALL);
    write();
  }

  // IM920SL control
  void baudrate(const BAUDRATE &baud) {
    appendStr(CMD::Cmd<CMD::TYPE::CTRL>::BAUDRATE);
    appendInt((int)baud, DEC, 1);
  }

  void reset() {
    appendStr(CMD::Cmd<CMD::TYPE::CTRL>::RESET);
    write();
  }

  void clearSettings() {
    appendStr(CMD::Cmd<CMD::TYPE::CTRL>::CLEAR_SETTINGS);
    write();
  }

  // enable / disable function
  void write(const bool b) {
    if (b)
      appendStr(CMD::Cmd<CMD::TYPE::FUNC>::EN_WRITE);
    else
      appendStr(CMD::Cmd<CMD::TYPE::FUNC>::EN_WRITE);
    write();
  }

  void charIO(const bool b) {
    if (b)
      appendStr(CMD::Cmd<CMD::TYPE::FUNC>::EN_CHAR_IO);
    else
      appendStr(CMD::Cmd<CMD::TYPE::FUNC>::DS_CHAR_IO);
    write();
  }

  void sleep(const bool b) {
    if (b)
      appendStr(CMD::Cmd<CMD::TYPE::FUNC>::EN_SLEEP);
    else
      appendStr(CMD::Cmd<CMD::TYPE::FUNC>::DS_SLEEP);
    write();
  }

  void retry(const bool b) {
    if (b)
      appendStr(CMD::Cmd<CMD::TYPE::FUNC>::EN_RETRY);
    else
      appendStr(CMD::Cmd<CMD::TYPE::FUNC>::DS_RETRY);
    write();
  }

  void answerback(const bool b) {
    if (b)
      appendStr(CMD::Cmd<CMD::TYPE::FUNC>::EN_ANSWER_BACK);
    else
      appendStr(CMD::Cmd<CMD::TYPE::FUNC>::DS_ANSWER_BACK);
    write();
  }

  void repeater(const bool b) {
    if (b)
      appendStr(CMD::Cmd<CMD::TYPE::FUNC>::EN_REPEATER);
    else
      appendStr(CMD::Cmd<CMD::TYPE::FUNC>::DS_REPEATER);
    write();
  }

  // settings
  void node() {
    appendStr(CMD::Cmd<CMD::TYPE::SETTING>::R_NODE);
    write();
  }
  void node(uint8_t node) {
    appendStr(CMD::Cmd<CMD::TYPE::SETTING>::W_NODE);
    appendInt(node, HEX, 4);
    write();
  }

  void destNode() {
    appendStr(CMD::Cmd<CMD::TYPE::SETTING>::R_DEST_NODE);
    write();
  }
  void destNode(uint16_t node) {
    appendStr(CMD::Cmd<CMD::TYPE::SETTING>::W_DEST_NODE);
    appendInt(node, HEX, 4);
    write();
  }

  void groupNumber() {
    appendStr(CMD::Cmd<CMD::TYPE::SETTING>::R_GROUP);
    write();
  }
  void groupMake() {
    appendStr(CMD::Cmd<CMD::TYPE::SETTING>::W_GROUP);
    write();
  }

  void channel() {
    appendStr(CMD::Cmd<CMD::TYPE::SETTING>::R_CHANNEL);
    write();
  }
  void channel(const CHANNEL channel) {
    appendStr(CMD::Cmd<CMD::TYPE::SETTING>::W_CHANNEL);
    appendInt((int)channel, DEC, 2);
    write();
  }

  void power() {
    appendStr(CMD::Cmd<CMD::TYPE::SETTING>::R_RF_POWER);
    write();
  }
  void power(const RF_POWER power) {
    appendStr(CMD::Cmd<CMD::TYPE::SETTING>::W_RF_POWER);
    appendInt((int)power, DEC, 1);
    write();
  }

  void rate() {
    appendStr(CMD::Cmd<CMD::TYPE::SETTING>::R_RF_RATE);
    write();
  }
  void rate(RF_RATE rate) {
    appendStr(CMD::Cmd<CMD::TYPE::SETTING>::W_RF_RATE);
    appendInt((int)rate, DEC, 1);
    write();
  }

  void sleepTime() {
    appendStr(CMD::Cmd<CMD::TYPE::SETTING>::R_SLEEP_TIME);
    write();
  }
  void sleepTime(uint16_t ms) {
    appendStr(CMD::Cmd<CMD::TYPE::SETTING>::W_SLEEP_TIME);
    appendInt(ms, HEX, 4);
    write();
  }

  void waitTime() {
    appendStr(CMD::Cmd<CMD::TYPE::SETTING>::R_WAIT_TIME);
    write();
  }
  void waitTime(uint16_t ms) {
    appendStr(CMD::Cmd<CMD::TYPE::SETTING>::W_WAIT_TIME);
    appendInt(ms, HEX, 4);
    write();
  }

  // send data
  // broadcast
  // 固定長(int、float、structなど)のデータを送信する
  template <typename T>
  void broadcastFixedVar(const T &arg, bool isTXDT = false) {
    appendStr(isTXDT ? CMD::Cmd<CMD::TYPE::SEND>::BROADCAST_FIXED
                     : CMD::Cmd<CMD::TYPE::SEND>::BROADCAST);
    appendBin(arg, sizeof(T));
    write();
  }

  // 文字列を送信する
  void broadcastString(const char *str) {
    appendStr(CMD::Cmd<CMD::TYPE::SEND>::BROADCAST);
    appendStr(str);
    write();
  }

  // unicast
  // 固定長(int、float、structなど)のデータを送信する
  template <typename T> void unicastFixedVar(uint8_t node, const T &arg) {
    appendStr(CMD::Cmd<CMD::TYPE::SEND>::UNICAST);
    appendInt(node, HEX, 2); // todo: fix sending format
    appendBin(arg, sizeof(T));
    write();
  }

  // 文字列を送信する
  void unicastString(uint8_t node, const char *str) {
    appendStr(CMD::Cmd<CMD::TYPE::SEND>::UNICAST);
    appendInt(node, HEX, 2); // todo: fix sending format
    appendStr(str);
    write();
  }

  // send back
  // 固定長(int、float、structなど)のデータを送信する
  template <typename T> void sendBackFixedVar(const T &arg) {
    appendStr(CMD::Cmd<CMD::TYPE::SEND>::SEND_BACK);
    appendBin(arg, sizeof(T)); // todo: fix sending format
    write();
  }

  // 文字列を送信する
  void sendBackString(const char *str) {
    appendStr(CMD::Cmd<CMD::TYPE::SEND>::SEND_BACK);
    appendStr(str);
    write();
  }

  // delegate
  // 固定長(int、float、structなど)のデータを送信する
  template <typename T> void delegateFixedVar(uint8_t node, const T &arg) {
    appendStr(CMD::Cmd<CMD::TYPE::SEND>::DELEGATE);
    appendInt(node, HEX, 2); // todo: fix sending format
    appendBin(arg, sizeof(T));
    write();
  }

  // 文字列を送信する
  void delegateString(uint8_t node, const char *str) {
    appendStr(CMD::Cmd<CMD::TYPE::SEND>::DELEGATE);
    appendInt(node, HEX, 2); // todo: fix sending format
    appendStr(str);
    write();
  }

private:
  void delimiter() { asc_buffer += "\r\n"; }
  bool empty() { return asc_buffer.length() == 0; }

  void appendBin(uintptr_t address, size_t size) {
    uint8_t *data = reinterpret_cast<uint8_t *>(address);
    for (size_t i = 0; i < size; i++) {
      // 16進数で送信
      char hex[3]; // 2桁の16進数と終端文字
      snprintf(hex, sizeof(hex), "%02X", data[i]);
      asc_buffer += hex;
    }
  }
  void appendInt(int i, int base, int width) {
    char buf[width + 1];
    if (base == DEC)
      snprintf(buf, sizeof(buf), "%*d", width, i);
    else if (base == HEX)
      snprintf(buf, sizeof(buf), "%*X", width, i);
    else
      return;
    asc_buffer += buf;
  }
  void appendStr(const char *str) { asc_buffer += str; }

  void write() {
    delimiter();
    stream->write(asc_buffer.c_str(), asc_buffer.length());
    asc_buffer.remove(0, asc_buffer.length());
  }

  Stream *stream;
  String asc_buffer{""};
}; // class Sender
} // namespace IM920SLCtrl

#endif /* IM920SL_SENDER_H */
