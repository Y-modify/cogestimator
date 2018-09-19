class Load_cell {
public:
  Load_cell(uint_fast8_t dat, uint_fast8_t clk) : dat_pin(dat), clk_pin(clk), offset(0) {
    pinMode(this->dat_pin, INPUT);
    pinMode(this->clk_pin, OUTPUT);
    this->offset = this->read();
  }

  float read() const {
    uint_fast32_t data = 0;
    while (digitalRead(this->dat_pin) != 0);
    for (uint_fast8_t i = 0; i < 24; i++) {
      digitalWrite(this->clk_pin, 1);
      delayMicroseconds(1);
      digitalWrite(this->clk_pin, 0);
      delayMicroseconds(1);
      data = (data << 1) | digitalRead(this->dat_pin);
    }
    digitalWrite(this->clk_pin, 1); //gain=128
    delayMicroseconds(1);
    digitalWrite(this->clk_pin, 0);
    delayMicroseconds(1);
    data = data ^ 0x800000;

    const auto volt = data * (4.2987 / 16777216.0 / 128); //Serial.println(volt,10);
    const auto gram = volt / (0.000669 * 4.2987 / 200.0); //Serial.println(gram,4);
    return gram - this->offset;
  }

private:
  uint_fast8_t dat_pin;
  uint_fast8_t clk_pin;

  float offset;
};
