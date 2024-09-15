#ifndef IM920SL_SENDER_H
#define IM920SL_SENDER_H

#if defined(TEENSYDUINO) || defined(ESP_PLATFORM) || defined(ESP8266)
#include "Arduino.h"
#include <cstdint>
#include <type_traits>
#elif defined(__AVR__)
#include "Arduino.h"
#elif defined OF_VERSION_MAJOR
#include "ofMain.h"
#include <string>
#else
#error THIS PLATFORM IS NOT SUPPORTED
#endif
#include "IM920SLCommands.h"
#include "IM920SLSettings.h"

namespace IM920SLCtrl {

template <typename S> class Sender {
public:
  Sender() {}
  ~Sender() {}

  bool setup(S &s) {
    stream = &s;
    stream->flush();
    return true;
  }

  // IM92j0 info
  void uniqueID() {
    append(CMD::Cmd<CMD::TYPE::INFO>::UNIQUE_ID);
    write();
  }

  void rssi() {
    append(CMD::Cmd<CMD::TYPE::INFO>::RSSI);
    write();
  }

  void version() {
    append(CMD::Cmd<CMD::TYPE::INFO>::VERSION);
    write();
  }

  void dump() {
    append(CMD::Cmd<CMD::TYPE::INFO>::ALL);
    write();
  }

  // IM920SL control
  void baudrate(const BAUDRATE &baud) {
    append(CMD::Cmd<CMD::TYPE::CTRL>::BAUDRATE);
    append(baud);
    write();
  }

  void reset() {
    append(CMD::Cmd<CMD::TYPE::CTRL>::RESET);
    write();
  }

  void clearSettings() {
    append(CMD::Cmd<CMD::TYPE::CTRL>::CLEAR_SETTINGS);
    write();
  }

  // enable / disable function
  void writable(const bool b) {
    if (b)
      append(CMD::Cmd<CMD::TYPE::FUNC>::EN_SAVE);
    else
      append(CMD::Cmd<CMD::TYPE::FUNC>::DS_SAVE);
    write();
  }

  void charIO(const bool b) {
    if (b)
      append(CMD::Cmd<CMD::TYPE::FUNC>::EN_CHAR_IO);
    else
      append(CMD::Cmd<CMD::TYPE::FUNC>::DS_CHAR_IO);
    write();
  }

  void sleep(const bool b) {
    if (b)
      append(CMD::Cmd<CMD::TYPE::FUNC>::EN_SLEEP);
    else
      append(CMD::Cmd<CMD::TYPE::FUNC>::DS_SLEEP);
    write();
  }

  void answerback(const bool b) {
    if (b)
      append(CMD::Cmd<CMD::TYPE::FUNC>::EN_ANSWER_BACK);
    else
      append(CMD::Cmd<CMD::TYPE::FUNC>::DS_ANSWER_BACK);
    write();
  }

  void repeater(const bool b) {
    if (b)
      append(CMD::Cmd<CMD::TYPE::FUNC>::EN_REPEATER);
    else
      append(CMD::Cmd<CMD::TYPE::FUNC>::DS_REPEATER);
    write();
  }

  // settings
  void node() {
    append(CMD::Cmd<CMD::TYPE::SETTING>::R_NODE);
    write();
  }
  void node(uint8_t node) {
    append(CMD::Cmd<CMD::TYPE::SETTING>::W_NODE);
    append(node);
    write();
  }

  void recvID() {
    append(CMD::Cmd<CMD::TYPE::SETTING>::R_RECEIVE_ID);
    write();
  }
  void recvID(uint16_t id) {
    append(CMD::Cmd<CMD::TYPE::SETTING>::W_RECEIVE_ID);
    append(id);
    write();
  }

  void channel() {
    append(CMD::Cmd<CMD::TYPE::SETTING>::R_CHANNEL);
    write();
  }
  void channel(const CHANNEL channel) {
    append(CMD::Cmd<CMD::TYPE::SETTING>::W_CHANNEL);
    if (channel < 10)
      append("0", 1);
    append((uint8_t)channel, 10);
    write();
  }

  void power() {
    append(CMD::Cmd<CMD::TYPE::SETTING>::R_RF_POWER);
    write();
  }
  void power(const RF_POWER power) {
    append(CMD::Cmd<CMD::TYPE::SETTING>::W_RF_POWER);
    append((uint8_t)power, 10);
    write();
  }

  void rate() {
    append(CMD::Cmd<CMD::TYPE::SETTING>::R_RF_RATE);
    write();
  }
  void rate(RF_RATE rate) {
    append(CMD::Cmd<CMD::TYPE::SETTING>::W_RF_RATE);
    append((uint8_t)rate, 10);
    write();
  }

  void sleepTime() {
    append(CMD::Cmd<CMD::TYPE::SETTING>::R_SLEEP_TIME);
    write();
  }
  void sleepTime(uint16_t ms) {
    append(CMD::Cmd<CMD::TYPE::SETTING>::W_SLEEP_TIME);
    append(ms);
    write();
  }

  void waitTime() {
    append(CMD::Cmd<CMD::TYPE::SETTING>::R_WAIT_TIME);
    write();
  }
  void waitTime(uint16_t ms) {
    append(CMD::Cmd<CMD::TYPE::SETTING>::W_WAIT_TIME);
    append(ms);
    write();
  }

  // send data
  void send() { write(); }

  template <typename First, typename... Rest>
  void send(First &&first, Rest &&...args) {
    if (empty())
      append(CMD::Cmd<CMD::TYPE::SEND>::MULTI_BYTES);
    append(first);
    send(args...);
  }

  template <typename T> Sender<S> &operator<<(const T &arg) {
    if (empty())
      append(CMD::Cmd<CMD::TYPE::SEND>::MULTI_BYTES);
    append(arg);
    return *this;
  }

  Sender<S> &operator<<(const char *arg) {
    if (empty())
      append(CMD::Cmd<CMD::TYPE::SEND>::MULTI_BYTES);
    append(arg, sizeof(arg));
    return *this;
  }

protected:
#if defined(TEENSYDUINO) || defined(ESP_PLATFORM) || defined(ESP8266)

  using StringType = String;

  template <
      typename T,
      typename std::enable_if<std::is_integral<
          typename std::remove_reference<T>::type>::value>::type * = nullptr>
  String toHex(const T &value) {
    size_t size = sizeof(T) * 2;
    String format = "%0" + String(size) + "X";
    char hex[size + 1];
    sprintf(hex, format.c_str(), value);
    return String(hex);
  }

  bool empty() { return (asc_buffer.length() == 0); }

#elif defined(__AVR__)

  using StringType = String;

  // works correctly only for integer
  template <typename T> String toHex(const T &value) {
    size_t size = sizeof(T) * 2;
    String format = "%0" + String(size) + "X";
    char hex[size + 1];
    sprintf(hex, format.c_str(), value);
    return String(hex);
  }

  bool empty() { return (asc_buffer.length() == 0); }

#elif defined OF_VERSION_MAJOR

  using StringType = std::string;

  bool empty() { return asc_buffer.empty(); }

#else

#error THIS PLATFORM IS NOT SUPPORTED

#endif

  template <typename T> void append(const T &n, uint8_t base = 16);
  void append(const char *c) { asc_buffer += c; }

  void delimiter() { append("\r\n", 2); }

  void write();

  S *stream;
  StringType asc_buffer{""};
};

#if defined(TEENSYDUINO) || defined(__AVR__) || defined(ESP_PLATFORM) ||       \
    defined(ESP8266)

template <> void Sender<Stream>::write() {
  delimiter();
  stream->write(asc_buffer.c_str(), asc_buffer.length());
  asc_buffer.remove(0, asc_buffer.length());
}

template <>
template <typename T>
void Sender<Stream>::append(const T &n, uint8_t base) {
  String s;
  if (base == 16)
    s = toHex(n);
  else if (base == 10)
    s = String(n, DEC);
  else {
    Serial.println("invalid base parameter");
    return;
  }
  asc_buffer += s;
}

#elif defined(OF_VERSION_MAJOR)

template <> void Sender<ofSerial>::write() {
  delimiter();
  stream->writeBytes((unsigned char *)asc_buffer.c_str(), asc_buffer.length());
  asc_buffer.clear();
}

template <>
template <typename T>
void Sender<ofSerial>::append(const T &n, uint8_t base) {
  stringstream ss;
  if (base == 16)
    ss << std::hex;
  else if (base == 10)
    ss << std::dec;
  else {
    ofLogError("invalid base parameter");
    return;
  }
  ss << std::setw(sizeof(T) * 2) << std::setfill('0') << (size_t)n;
  asc_buffer += ss.str();
}

#else

#error THIS PLATFORM IS NOT SUPPORTED

#endif

} // namespace IM920SLCtrl

#endif /* IM920SL_SENDER_H */
