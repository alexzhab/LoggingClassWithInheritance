#include <string>
#include <iostream>

enum class MessageColor {
  ANSI_red = 196,
  ANSI_orange = 214,
  ANSI_blue = 33
};

class AbstractMsg {
};

class ImportantMsg : public AbstractMsg {

};

class LogMsg : public AbstractMsg {

};

class DebugMsg : public AbstractMsg {

};

class Logging : public ImportantMsg, public LogMsg, public DebugMsg {

};