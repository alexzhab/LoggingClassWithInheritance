#include <string>
#include <iostream>

enum class MessageType {
  Important,
  Log,
  Debug
};

enum class MessageColor {
  ANSI_red = 196,
  ANSI_orange = 214,
  ANSI_blue = 33
};

class AbstractMsg {
protected:
  AbstractMsg() =  default;
  virtual ~AbstractMsg() = default;

  static std::string get_colored_string(const MessageColor & color, const std::string & comment, const std::string & msg) {
    return "\033[38;5;" + std::to_string(int(color)) + "m" + comment + msg + "\033[39m";
  }
};

class ImportantMsg : public AbstractMsg {
protected:
  ImportantMsg() = default;
  virtual ~ImportantMsg() =  default;

  static void print_important(const std::string & msg) {
    std::cout << get_colored_string(MessageColor::ANSI_red, "Important: ", msg) << std::endl;
  }
};

class LogMsg : public AbstractMsg {
private:
  static inline int m_log_limit = 0;
  static inline bool m_ignore_log_limit = false;
  static inline bool m_reached_log_limit = false;

protected:
  LogMsg() = default;
  virtual ~LogMsg() = default;

public:
  static void set_log_limit(int log_limit) {
    m_log_limit = log_limit;
    m_reached_log_limit = false;
  }

  static void set_ignore_log_limit(bool ignore_log_limit) {
    m_ignore_log_limit = ignore_log_limit;
  }

  static void print_log(const std::string & msg) {
    static int s_count = 0;
    if (s_count < m_log_limit || m_ignore_log_limit) {
      std::cout << get_colored_string(MessageColor::ANSI_blue, "Log: ", msg) << std::endl;
      s_count++;
    }
    else if (!m_reached_log_limit) {
      std::cout << "Maximum number of log messages is reached: " << s_count << std::endl;
      m_reached_log_limit = true;
    }
  }
};

class DebugMsg : public AbstractMsg {
private:
  static inline bool m_debug = false;

protected:
  DebugMsg() = default;
  virtual ~DebugMsg() = default;

public:
  static void set_debug(bool debug) {
    m_debug = debug;
  }

  static void print_debug(const std::string & msg) {
    if (m_debug)
      std::cout << get_colored_string(MessageColor::ANSI_orange, "Debug: ", msg) << std::endl;
  }
};

class Logging : public ImportantMsg, public LogMsg, public DebugMsg {
public:
  Logging() : ImportantMsg(), LogMsg(), DebugMsg() {}
  ~Logging() = default;
  Logging(const Logging& l) = delete;
  Logging & operator=(const Logging & l) = delete;

  static void print_msg(const std::string & msg, const MessageType & msg_type) {
    switch(msg_type) {
        case MessageType::Important: {
          print_important(msg);
          break;
        }
        case MessageType::Log: {
          print_log(msg);
          break;
        }
        case MessageType::Debug: {
          print_debug(msg);
          break;
        }
      }
  }
};