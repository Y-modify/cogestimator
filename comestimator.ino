/*************************************
  YamaX Arduino Core v3.0 with auto-stabilization system
  To burn on AX-03 for YamaX 4.3
  made by Y-modify, Nyanyan & coord.e
  Copyright © 2017 Y-modify All Rights Reserved.
  QIO,80,160,4M(1M),Disabled,none,nodemcu,115200~
*************************************/

/*****Version Definition*****/
#define YAMAX_VER "4.0"
#define FIRMWARE_VER "5.0-uno"

#if defined(ARDUINO_AVR_UNO) || defined(ESP8266) // AX-01 or something nice
#define S_STABLE
#define BOARD_VER "01"
#else
#error This board is not supported! Please use ESP8266 or Arduino UNO.
#endif

/*****System Setup*****/
void setup() {
  Serial.begin(115200);
  verInfo(); // Print Version Information
  print_c("Initializing...\n");
  StabilizationInit();
  print_c("Initialization Complete.\n");
}

/*****Waiting Loop*****/
void loop() {
  CommandCheck();
  delay(1);
}

/*****Print Version Information*****/
void verInfo() {
  print_c("\n*************************************\n");
  print_c("YamaX Arduino Core (MCore) v%s\n", FIRMWARE_VER);
  print_c("To burn on AX-%s for YamaX %s\n", BOARD_VER, YAMAX_VER);
  print_c("Made by Y-modify, Nyanyan & coord.e\n");
  print_c("Copyright (c) 2016 Y-modify All Rights Reserved.\n");
  print_c("*************************************\n\n");
}

/*****That's all. Enjoy!*****/
