#ifndef COG_ESTIMATOR_SERIAL_CONTROL_H_
#define COG_ESTIMATOR_SERIAL_CONTROL_H_

#include "fake_stream.h"
#include "measure.h"
#include <SerialCommand.h>


#define FIRMWARE_VER "1.0"


namespace serial_control {

SerialCommand SCmd;

void print_com() {
  measure::draw_com();
}


void print_version() {
  strm::cout << strm::endl
    << "*************************************" << strm::endl
    << "COMEstimator v" << FIRMWARE_VER << strm::endl
    << "Made by Y-modify, Nyanyan & coord.e" << strm::endl
    << "Copyright (c) 2018 Y-modify All Rights Reserved." << strm::endl
    << "*************************************" << strm::endl
    << strm::endl;
}


void what() {
  strm::cout << "I can't understand" << strm::endl;
}


void what(const char *command) {
  strm::cout << "Command" << command << "is not defined" << strm::endl;
}

void setup() {
  SCmd.addCommand("get", print_com);
  SCmd.addCommand("version", print_version);
  SCmd.setDefaultHandler(what);
}

void check_command() {
  SCmd.readSerial();
}

};

#endif
