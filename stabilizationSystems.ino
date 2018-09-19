/*************************************
  Controls - YamaX Arduino Core v3.0
  stabilization controlling block
  made by coord.e, Y-modify
  Copyright © 2017 Y-modify All Rights Reserved.
*************************************/

constexpr uint_fast8_t num_sensors = 8;

// definition of sensor ports
/* Previously defined as                     A   B  C  D   E   F   G  H */
constexpr uint_fast8_t dats[num_sensors]  = {13, 5, 7, 11, A0, A2, 3, 9 };
constexpr uint_fast8_t clks[num_sensors]  = {2,  6, 8, 12, A1, A3, 4, 10};
// sensor value gains
constexpr uint_fast8_t gains[num_sensors] = {-1, 1, 1, -1, -1,  1, 1, -1};

uint_fast8_t offsets[num_sensors] = {};

//values of each sensor
uint_fast8_t values[num_sensors] = {};
float valSum = 0;

//values of each axis
float Gxl = 0;
float Gyl = 0;
float Gxr = 0;
float Gyr = 0;





void StabilizationInit() {
  for (const auto dat : dats) {
    pinMode(dat, INPUT);
  }
  for (const auto clk : clks) {
    pinMode(clk, OUTPUT);
  }
  for (decltype(num_sensors) i = 0; i < num_sensors; i++) {
    offsets[i] = read_sensor(clks[i], dats[i], 0);
  }
}


void stabilization() {
  //  getG();
  float num = 5;//maximum num
  float threshold = 0.7;
  //int exponent = 3;//n次
  int times = 5;
  float height = 2.5;//重心の高さ,1=足の爪先-踵
  //PID();
  if (valSum >= 800)//800g or more, stabilize.
  {
    float duty = PID();
    float Ndegress = (asin(duty / height - sin(fN * PI / 180)) + fN * PI / 180) * 180 / PI;
    Serial.print(duty);
    Serial.print("\t");
    Serial.println(Ndegress);

    /*
      //左脚y軸
       if (Gxr > threshold)
         setServoPulse(servoO, fO - num);
       if (Gxr < -threshold)
         setServoPulse(servoO, fO + num);
      //右脚y軸
      if (Gyr < threshold && Gyr > -threshold) {
       Serial.print("OKOKOKOKOKOKOKOK");
       Serial.print("\t");
       Serial.print(fN);
       Serial.print("\t");
       Serial.println(Gyr);
       for (int i = 0; i < times; i++)
         smoothmotion(servoN, fN, times, i);
       //setServoPulse(servoN, fN);
      } else if (Gyr >= threshold) {
       Serial.print("+++++threshold!!");
       Serial.print("\t");
       Serial.print(fM);
       Serial.print("\t");
       Serial.println(Gyr);
       for (int i = 0; i < times; i++)
         smoothmotion(servoM, fN + num * pow(Gyr, exponent) , times, i);
       //setServoPulse(servoM, fM - num);
      } else if (Gyr <= -threshold) {
       Serial.print("-----threshold!!");
       Serial.print("\t");
       Serial.print(fM);
       Serial.print("\t");
       Serial.println(Gyr);
       for (int i = 0; i < times; i++)
         smoothmotion(servoM, fN + num * pow(Gyr, exponent) , times, i);
       //setServoPulse(servoM, fM + num);
      }


       if (Gyr > threshold)
         setServoPulse(servoN, fN + num);
       if (Gyr < -threshold)
         setServoPulse(servoN, fN - num);
       if (Gyl > threshold)
         setServoPulse(servoT, fT - num);
       if (Gyl < -threshold)
         setServoPulse(servoT, fT + num);*/
  } else {
    for (int i = 0; i < times; i++)
      smoothmotion(servoN, fN , 2, i);
  }
}

float PID()
{
  float preTime = 0;
  float preP = 0;
  float dt = 0;
  float P = 0;
  float I = 0;
  float D = 0;
  float duty = 0;
  float Kp = 1;
  float Ki = 0.7;
  float Kd = 0.7;

  dt = (micros() - preTime) / 1000000;
  preTime = micros();
  P = -Gyr;//誤差
  I += P * dt;//積分=総和
  D = (P - preP) / dt;//微分=変化量
  preP = P;
  Serial.print(P);
  Serial.print("\t");
  Serial.print(I);
  Serial.print("\t");
  Serial.print(D);
  Serial.print("\t");
  return Kp * P + Ki * I - Kd * D;
}

void resetCentroid() {
  /*offset_A =Read(CLK_A, DAT_A, offset_A);
    offset_B = offset_B + Read(CLK_B, DAT_B, 0);
    offset_C = offset_C + Read(CLK_C, DAT_C, 0);
    offset_D = offset_D + Read(CLK_D, DAT_D, 0);
    offset_E = offset_E + Read(CLK_E, DAT_E, 0);
    offset_F = offset_F + Read(CLK_F, DAT_F, 0);
    offset_G = offset_G + Read(CLK_G, DAT_G, 0);
    offset_H = offset_H + Read(CLK_H, DAT_H, 0);*/
}

void getCentroid() {
  for(decltype(num_sensors) i = 0; i < num_sensors; i++) {
    values[i] = gains[i] * read_sensor(clks[i], dats[i], offsets[i]);
    valSum += values[i];
  }

  const sum_a2d = values[0] + values[1] + values[2] + values[3];
  const sum_e2h = values[4] + values[5] + values[6] + values[7];

  /* Centor of mass -1...1 */
  Gxl = -1 + 2 * (values[1] + values[3]) / sum_a2d;
  Gyl = -1 + 2 * (values[0] + values[1]) / sum_a2d;
  Gxr = -1 + 2 * (values[4] + values[6]) / sum_e2h;
  Gyr = -1 + 2 * (values[4] + values[5]) / sum_e2h;
}

void drawCentroid() {
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


float read_sensor(int clk, int dat, float offset) {
  uint_fast32_t data = 0;
  while (digitalRead(dat) != 0);
  for (uint_fast8_t i = 0; i < 24; i++) {
    digitalWrite(clk, 1);
    delayMicroseconds(1);
    digitalWrite(clk, 0);
    delayMicroseconds(1);
    data = (data << 1) | digitalRead(dat);
  }
  digitalWrite(clk, 1); //gain=128
  delayMicroseconds(1);
  digitalWrite(clk, 0);
  delayMicroseconds(1);
  data = data ^ 0x800000;

  const float volt = data * (4.2987 / 16777216.0 / 128); //Serial.println(volt,10);
  const float gram = volt / (0.000669 * 4.2987 / 200.0); //Serial.println(gram,4);
  return gram - offset;
}
