#ifndef COG_ESTIMATOR_MEASURE_H_
#define COG_ESTIMATOR_MEASURE_H_

#include "cog_estimator.h"

namespace measure {

static constexpr uint_fast8_t num_sensors = 8;

// definition of sensor ports
/* Previously defined as                     A   B  C  D   E   F   G  H */
constexpr uint_fast8_t dats[num_sensors]  = {13, 5, 7, 11, A0, A2, 3, 9 };
constexpr uint_fast8_t clks[num_sensors]  = {2,  6, 8, 12, A1, A3, 4, 10};

Cog_estimator* R_estimator = {};
Cog_estimator* L_estimator = {};

void setup() {
  R_estimator = new Cog_estimator(
                  new Load_cell(dats[0], clks[0]),
                  new Load_cell(dats[1], clks[1]),
                  new Load_cell(dats[2], clks[2]),
                  new Load_cell(dats[3], clks[3])
                );
  L_estimator = new Cog_estimator(
                  new Load_cell(dats[4], clks[4]),
                  new Load_cell(dats[5], clks[5]),
                  new Load_cell(dats[6], clks[6]),
                  new Load_cell(dats[7], clks[7])
                );
}

void draw_com() {
  int sizx = 10;//>=2
  int sizy = 10;//>=2

  float valSum = 0;
  float Gxl;
  float Gyl;
  float Gxr;
  float Gyr;
  valSum += R_estimator->get_center_of_gravity(&Gxr, &Gyr);
  valSum += L_estimator->get_center_of_gravity(&Gxl, &Gyl);

  int GxlPoint = Gxl * sizx / 2 + sizx / 2;
  int GylPoint = Gyl * sizx / 2 + sizy / 2;
  int GxrPoint = -Gxr * sizx / 2 + sizx / 2;
  int GyrPoint = Gyr * sizx / 2 + sizy / 2;
  /*  for (int i = 0; i < sizx - 2; i++)
      print_c("");*/
  strm::cout << "left front right" << strm::endl;

  for (int i = sizy; i > 0; i--) //列の管理
  {
    for (int j = 0; j < sizx; j++)//左脚行の描画
    {
      if (j == GxlPoint)
      {
        if (i == GylPoint)
          strm::cout << "*";
        else
          strm::cout << "-";
      } else
      {
        strm::cout << "-";
      }
    }

    strm::cout << "  ";

    for (int j = 0; j < sizx; j++)//右脚行の描画
    {
      if (j == GxrPoint)
      {
        if (i == GyrPoint)
          strm::cout << "*";
        else
          strm::cout << "-";
      } else
      {
        strm::cout << "-";
      }
    }


    strm::cout << strm::endl;

  }

  strm::cout << Gxl << "\t" << Gyl << "\t" << Gxr << "\t" << Gyr << "\t" << valSum << strm::endl << strm::endl << strm::endl;
}

};

#endif
