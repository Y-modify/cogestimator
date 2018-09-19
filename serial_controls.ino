/*************************************
  Controls - YamaX Arduino Core v3.0
  Command control block
  made by coord.e, Y-modify
  Copyright © 2017 Y-modify All Rights Reserved.
*************************************/

#include "fake_stream.h"
#include <SerialCommand.h>

SerialCommand SCmd;

void ControlInit() {
  SCmd.addCommand("get", print_com);
  SCmd.addCommand("version", verInfo);
  SCmd.setDefaultHandler(what);
}

void print_com() {
  getCentroid();

  for (uint_fast8_t i = 0; i < num_sensors; i++) {
    strm::cout << i << ": " << values[i] << strm::endl;
  }
  strm::cout << "Gxl: " << Gxl << strm::endl;
  strm::cout << "Gyl: " << Gyl << strm::endl;
  strm::cout << "Gxr: " << Gxr << strm::endl;
  strm::cout << "Gyr: " << Gyr << strm::endl;
}

void CommandCheck() {
  SCmd.readSerial();
}

void what() {
  strm::cout << "I can't understand" << strm::endl;
}

void what(const char *command) {
  strm::cout << "Command" << command << "is not defined" << strm::endl;
}
