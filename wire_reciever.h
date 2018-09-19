#ifndef COG_ESTIMATOR_WIRE_RECIEVER_H_
#define COG_ESTIMATOR_WIRE_RECIEVER_H_

#include <Wire.h>

namespace wire_reciever {

static constexpr i2c_addr = 0x09;

void setup() {
  Wire.begin(i2c_addr);
  Wire.onRequest(on_request);
}

void on_request() {
  while (!Wire.available());
  const uint8_t addr = Wire.read();
  while (!Wire.available());
  const uint8_t value = Wire.read();
  const uint8_t ret = dispatch_address(addr, value);
  Wire.write(ret);
}

uint8_t dispatch_address(uint8_t addr, uint8_t value) {
  switch (addr) {
    case 0x09:
      return command::who_am_i();
    case 0x0A:
    case 0x0B:
      return command::get_rx(addr - 0x0A);
    case 0x0C:
    case 0x0D:
      return command::get_ry(addr - 0x0C);
    case 0x1A:
    case 0x1B:
      return command::get_lx(addr - 0x1A);
    case 0x1C:
    case 0x1D:
      return command::get_ly(addr - 0x1C);
    case 0x20:
      return command::measure();
    default:
      return 0xff;
  }
}

namespace command {

static uint16_t rx_cache, ry_cache, lx_cache, ly_cache;

uint16_t float_to_word(float in) {
  return (in / 2 + 0.5) * 0xFFFF;
}

uint8_t measure() {
  float rx, ry, lx, ly;
  measure::R_estimator->get_center_of_gravity(&rx, &ry);
  measure::L_estimator->get_center_of_gravity(&lx, &ly);
  rx_cache = float_to_word(rx);
  ry_cache = float_to_word(ry);
  lx_cache = float_to_word(lx);
  ly_cache = float_to_word(ly);
  return 0x00;
}

uint8_t who_am_i() {
  return 0x09;
}

uint8_t get_rx(uint8_t idx) {
  return 
}

};

};

#endif
