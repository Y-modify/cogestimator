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
    default:
      return 0xff;
  }
}

namespace command {

uint8_t who_am_i() {
  return 0x09;
}

};

};
