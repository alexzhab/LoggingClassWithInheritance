#include "Logging.h"
#include <string>
#include <iostream>

int main() {
  Logging l{};
  l.set_log_limit(3);

  std::string str = "check string";
  l.print(str, MessageType::Log);
  l.print(str, MessageType::Debug);

  // Logging l2{l}; // call to deleted constructor of 'Logging'
  Logging l2{};
  l2.print(str, MessageType::Log);
  l.print(str, MessageType::Log);
  l2.print(str, MessageType::Log);
  l.print(str, MessageType::Important);
  l2.print(str, MessageType::Log);
  l.set_log_limit(2);
  l2.print(str, MessageType::Log);
  l.set_log_limit(5);
  l2.print(str, MessageType::Log);
  l2.print(str, MessageType::Log);
  l2.print(str, MessageType::Log);
  Logging::set_ignore_log_limit(true);
  l2.print(str, MessageType::Log);

  l.set_debug(true);
  l.print(str, MessageType::Debug);
  Logging::print(str, MessageType::Debug);

  return 0;
}