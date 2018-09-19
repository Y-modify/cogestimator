/*************************************
  Controls - YamaX Arduino Core v3.0
  Command control block
  made by coord.e, Y-modify
  Copyright © 2017 Y-modify All Rights Reserved.
*************************************/

#include "fake_stream.h"
#include "measure.h"
#include <SerialCommand.h>

SerialCommand SCmd;

void init_control() {
  SCmd.addCommand("get", print_com);
  SCmd.addCommand("version", print_version);
  SCmd.setDefaultHandler(what);
}

void print_com() {
  measure::draw_com();
}

void check_command() {
  SCmd.readSerial();
}

void what() {
  strm::cout << "I can't understand" << strm::endl;
}

void what(const char *command) {
  strm::cout << "Command" << command << "is not defined" << strm::endl;
}
