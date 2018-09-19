/*************************************
  Controls - YamaX Arduino Core v3.0
  stabilization controlling block
  made by coord.e, Y-modify
  Copyright © 2017 Y-modify All Rights Reserved.
*************************************/

namespace measure {

constexpr uint_fast8_t num_sensors = 8;

// definition of sensor ports
/* Previously defined as                     A   B  C  D   E   F   G  H */
constexpr uint_fast8_t dats[num_sensors]  = {13, 5, 7, 11, A0, A2, 3, 9 };
constexpr uint_fast8_t clks[num_sensors]  = {2,  6, 8, 12, A1, A3, 4, 10};
// sensor value gains
constexpr float gains[num_sensors]        = {-1, 1, 1, -1, -1,  1, 1, -1};

Load_cell* sensors[num_sensors] = {};
float values[num_sensors] = {};

//values of each axis
float Gxl = 0;
float Gyl = 0;
float Gxr = 0;
float Gyr = 0;

void setup() {
  for (uint_fast8_t i = 0; i < num_sensors; i++) {
    sensors[i] = new Load_cell(dats[i], clks[i]);
  }
}

void get_com() {
  for(uint_fast8_t i = 0; i < num_sensors; i++) {
    values[i] = gains[i] * sensors[i]->read();
    valSum += values[i];
  }

  const auto sum_a2d = values[0] + values[1] + values[2] + values[3];
  const auto sum_e2h = values[4] + values[5] + values[6] + values[7];

  /* Centor of mass -1...1 */
  Gxl = -1 + 2 * (values[1] + values[3]) / sum_a2d;
  Gyl = -1 + 2 * (values[0] + values[1]) / sum_a2d;
  Gxr = -1 + 2 * (values[4] + values[6]) / sum_e2h;
  Gyr = -1 + 2 * (values[4] + values[5]) / sum_e2h;
}

void draw_com() {
  int sizx = 10;//>=2
  int sizy = 10;//>=2
  int GxlPoint = Gxl * sizx / 2 + sizx / 2;
  int GylPoint = Gyl * sizx / 2 + sizy / 2;
  int GxrPoint = -Gxr * sizx / 2 + sizx / 2;
  int GyrPoint = Gyr * sizx / 2 + sizy / 2;
  /*  for (int i = 0; i < sizx - 2; i++)
      print_c("");*/
  print_c("left front right\n");

  for (int i = sizy; i > 0; i--) //列の管理
  {
    for (int j = 0; j < sizx; j++)//左脚行の描画
    {
      if (j == GxlPoint)
      {
        if (i == GylPoint)
          print_c("*");
        else
          print_c("-");
      } else
      {
        print_c("-");
      }
    }

    print_c("  ");

    for (int j = 0; j < sizx; j++)//右脚行の描画
    {
      if (j == GxrPoint)
      {
        if (i == GyrPoint)
          print_c("*");
        else
          print_c("-");
      } else
      {
        print_c("-");
      }
    }


    print_c("\n");

  }

  //print_c("Gxl=%s\tGyl=%s\tGxr=%s\tGyr=%s\n",Gxl,Gyl,Gxr,Gyr);
  //Serial.print("Gxl= ");
  Serial.print(Gxl);
  Serial.print("\t");
  //Serial.print("\t Gyl= ");
  Serial.print(Gyl);
  Serial.print("\t");
  //Serial.print("\t Gxr= ");
  Serial.print(Gxr);
  Serial.print("\t");
  //Serial.print("\t Gyr= ");
  Serial.print(Gyr);
  Serial.print("\t");
  Serial.print(valSum);
  Serial.println("");
  /*
        Serial.print("GxlPoint=");
        Serial.print(GxlPoint);
        Serial.print("\t GylPoint=");
        Serial.print(GylPoint);
        Serial.print("\t GxrPoint=");
        Serial.print(GxrPoint);
        Serial.print("\t GyrPoint=");
        Serial.print(GyrPoint);
        Serial.println("");
  */
   /* Serial.print(valA);
    Serial.print("\t");
    Serial.print(valB);
    Serial.print("\t");
    Serial.print(valC);
    Serial.print("\t");
    Serial.print(valD);
    Serial.print("\t");
    Serial.print(valE);
    Serial.print("\t");
    Serial.print(valF);
    Serial.print("\t");
    Serial.print(valG);
    Serial.print("\t");
    Serial.print(valH);*/

  Serial.println("");
  Serial.println("");

}

};
