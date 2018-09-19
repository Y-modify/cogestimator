#ifndef COG_ESTIMATOR_SERIAL_CONTROL_H_
#define COG_ESTIMATOR_SERIAL_CONTROL_H_

#include "fake_stream.h"
#include "measure.h"
#include <SerialCommand.h>


namespace serial_control {

SerialCommand SCmd;

void setup() {
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

};

#endif
