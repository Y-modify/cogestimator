#ifndef COG_ESTIMATOR_COG_ESTIMATOR_H_
#define COG_ESTIMATOR_COG_ESTIMATOR_H_

#include "load_cell.h"

namespace measure {

class Cog_estimator {
public:
  Cog_estimator(Load_cell* cell_a, Load_cell* cell_b, Load_cell* cell_c, Load_cell* cell_d)
    : cell_a(cell_a), cell_b(cell_b), cell_c(cell_c), cell_d(cell_d) {}

  float get_center_of_gravity(float* x, float* y) {
    const auto a = -this->cell_a->read();
    const auto b =  this->cell_b->read();
    const auto c =  this->cell_c->read();
    const auto d = -this->cell_d->read();

    const auto sum = a + b + c + d;

    /* Centor of mass -1...1 */
    *x = -1 + 2 * (b + c) / sum;
    *y = -1 + 2 * (a + b) / sum;
  }

private:
  Load_cell* cell_a;
  Load_cell* cell_b;
  Load_cell* cell_c;
  Load_cell* cell_d;
};

#endif
