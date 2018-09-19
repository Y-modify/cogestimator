/*************************************
  YamaX Arduino Core v3.0 with auto-stabilization system
  To burn on AX-03 for YamaX 4.3
  made by Y-modify, Nyanyan & coord.e
  Copyright © 2017 Y-modify All Rights Reserved.
  QIO,80,160,4M(1M),Disabled,none,nodemcu,115200~
*************************************/

#include "fake_stream.h"
#define FIRMWARE_VER "1.0"

void setup() {
  Serial.begin(115200);
  verInfo();
  strm::cout << "Initializing" << strm::endl;
  StabilizationInit();
  strm::cout << "Complete" << strm::endl;
}

void loop() {
  CommandCheck();
  delay(1);
}

void verInfo() {
  strm::cout << strm::endl
    << "*************************************" << strm::endl
    << "COMEstimator v" << FIRMWARE_VER << strm::endl
    << "Made by Y-modify, Nyanyan & coord.e" << strm::endl
    << "Copyright (c) 2018 Y-modify All Rights Reserved." << strm::endl
    << "*************************************" << strm::endl
    << strm::endl;
}

