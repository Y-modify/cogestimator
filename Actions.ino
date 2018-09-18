/*************************************
  Debug - YamaX Arduino Core v3.0
  Actions block
  made by coord.e, Y-modify
  Copyright © 2017 Y-modify All Rights Reserved.
*************************************/

void walk(int times, int delaytime)
{
  if (delaytime < 40)
    delaytime = 40;  //20未満は危険

  print_c("Walking %d steps with %dms\n", times, delaytime);

  if (times <= 2)
    times = times;
  else
    times = times - 2;

  crouch();
  delay(500);
  for (int i = 0; i < times; i += 2)
  {
    walkLForward(delaytime, 0);
    walkLDown(delaytime, 0);
    walkRUp(delaytime, 0);
    walkRForward(delaytime, 0);
    walkRDown(delaytime, 0);
    walkLUp(delaytime, 0);
  }
  crouch();
  delay(500);
  reset(20, 30);
}


void back(int times, int delaytime)
{
  if (delaytime < 40)
    delaytime = 40;  //20未満は危険

  print_c("BackWalking %d steps with %dms\n", times, delaytime);

  if (times <= 2)
    times = times;
  else
    times = times - 2;

  crouch();
  delay(500);
  for (int i = 0; i < times; i += 2)
  {
    backLUp(delaytime, 5);
    backLForward(delaytime, 0);
    //Serial.println("debug1");
    //backLDown(delaytime, 5);
    backRUp(delaytime, 5);
    backRForward(delaytime, 0);
    //Serial.println("debug2");
    //backRDown(delaytime, 5);
  }
  crouch();
  delay(500);
  reset(20, 30);
}





/*
  void back(int times, int delaytime)
  {
  if (delaytime < 20)
    delaytime = 20;  //20未満は危険

  print_c("Walking %d steps with %dms\n", times, delaytime);

  if (times <= 2)
    times = times;
  else
    times = times - 2;

  crouch();
  delay(500);
  LEFTwalkBeginUp(delaytime);//最初に左足上げる
  LEFTbackBeginForward(delaytime);
  LEFTbackBeginDown(delaytime);

  for (int i = 0; i < times; i += 2)
  {
    if (i != 0)
    {
      backLEFTUp(delaytime);
      backLEFTForward(delaytime);
      backLEFTDown(delaytime);
    }
    backRIGHTUp(delaytime);
    backRIGHTForward(delaytime);
    backRIGHTDown(delaytime);
  }
  backLEFTUp(delaytime);
  backLEFTEndForward(delaytime);
  backLEFTEnd(delaytime);
  //delay(500);
  //backRIGHTToCrouch(40);
  delay(500);
  reset(20, 20);
  }







  void crabWalkingRight(int times, int delaytime)
  {
  if (delaytime < 20)
    delaytime = 20;  //20未満は危険

  print_c("CrabWalkingRight %d steps with %dms\n", times, delaytime);

  crouch();
  delay(500);
  for (int i = 0; i < times; i ++)
  {
    RIGHTwalkBeginUp(delaytime);
    RIGHTrightCrabForward(delaytime);
    RIGHTrightCrabDown(delaytime);

    RIGHTleftCrabUp(delaytime);
    RIGHTleftCrabForward(delaytime);
    RIGHTleftCrabDown(delaytime);
  }
  delay(500);
  reset(20, 20);
  delay(2000);
  }






  void crabWalkingLeft(int times, int delaytime)
  {
  if (delaytime < 20)
    delaytime = 20;  //20未満は危険

  print_c("CrabWalkingRight %d steps with %dms\n", times, delaytime);

  crouch();
  delay(500);
  for (int i = 0; i < times; i ++)
  {
    LEFTwalkBeginUp(delaytime);
    LEFTleftCrabForward(delaytime);
    LEFTleftCrabDown(delaytime);

    LEFTrightCrabUp(delaytime);
    LEFTrightCrabForward(delaytime);
    LEFTrightCrabDown(delaytime);
  }
  delay(500);
  reset(20, 20);
  delay(2000);
  }






  void turnright(int times, int delaytime)//左足の歩幅小さくする
  {
  print_c("Turning right %d times with %dms\n", times, delaytime);
  if (delaytime < 20)
    delaytime = 20;  //20未満は危険

  crouch();
  delay(500);
  int i = 0;
  for (i = 0; i < times; i ++)
  {
    LEFTwalkBeginUp(delaytime);
    LEFTwalkBeginForward(delaytime);
    LEFTwalkBeginDown(delaytime);//普通の左足出た状態に
    turnRightLEFTToCrouch(delaytime);
  }
  delay(500);
  reset(20, 20);
  }






  void turnleft(int times, int delaytime)//右足の歩幅小さくする
  {
  print_c("Turning left %d times with %dms\n", times, delaytime);
  if (delaytime < 20)
    delaytime = 20;  //20未満は危険

  crouch();
  delay(500);
  int i = 0;
  for (i = 0; i < times; i ++)
  {
    RIGHTwalkBeginUp(delaytime);
    RIGHTwalkBeginForward(delaytime);
    RIGHTwalkBeginDown(delaytime);//普通の左足出た状態に
    turnLeftRIGHTToCrouch(delaytime);
  }
  delay(500);
  reset(20, 20);
  }
*/



void automaDogeza(int delaytime)
{
  seiza1();
  delay(delaytime);
}





void no(int times)
{
  print_c("Denying %d times\n", times);

  for (int i = 0; i < times; i ++)
  {
    setServoPulse(servoA, stA - 60); //首
    delay(200);
    setServoPulse(servoA, stA + 60); //首
    delay(200);
  }
  setServoPulse(servoA, stA); //首
}





void bow(int delaytime)
{
  print_c("Bowing %dms\n", delaytime);
  bowing();
  delay(delaytime);
  reset(20, 20);
}






void bye(int times, int dir)//0:right, 1:left 2:both
{
  print_c("Bye %d times ", times);

  stand();

  if (dir == 0)
  {
    print_c("with right hand\n", times);
    setServoPulse(servoE, stE + 80);
    setServoPulse(servoF, stF - 70);
    for (int i = 0; i < times; i ++)
    {
      int tim = 20;
      for (int j = 0; j < 8; j++)
      {
        setServoPulse(servoG, stG + 80 - j * 10); //右腕
        delay(tim);
      }
      for (int j = 0; j < 8; j++)
      {
        setServoPulse(servoG, stG + j * 10); //右腕
        delay(tim);
      }
    }
  }

  if (dir == 1) {
    print_c("with left hand\n", times);
    setServoPulse(servoB, stB - 50);
    setServoPulse(servoC, stC + 80);
    for (int i = 0; i < times; i ++)
    {
      int tim = 20;
      for (int j = 0; j < 8; j++)
      {
        setServoPulse(servoD, stD - 80 + j * 10); //左腕
        delay(tim);
      }
      for (int j = 0; j < 8; j++)
      {
        setServoPulse(servoD, stD - j * 10); //左腕
        delay(tim);
      }
    }


  }

  if (dir == 2)
  {
    print_c("with both hand\n", times);

    setServoPulse(servoB, stB - 50);
    setServoPulse(servoC, stC + 80);
    setServoPulse(servoE, stE + 50);
    setServoPulse(servoF, stF - 60);
    for (int i = 0; i < times; i ++)
    {
      int tim = 20;
      for (int j = 0; j < 8; j++)
      {
        setServoPulse(servoG, stG + 80 - j * 10); //右腕
        setServoPulse(servoD, stD - 80 + j * 10); //左腕
        delay(tim);
      }
      for (int j = 0; j < 8; j++)
      {
        setServoPulse(servoG, stG + j * 10); //右腕
        setServoPulse(servoD, stD - j * 10); //左腕
        delay(tim);
      }
    }
  }
}







void nadenade(int times, bool dir) //0:right 1:left
{
  print_c("Nadenade %d times\n", times);

  stand();

  if (dir)
  {
    print_c("with left hand\n", times);
    setServoPulse(servoC, stC + 80);

    for (int i = 0; i < times; i ++)
    {
      int tim = 20;
      for (int j = 0; j < 8; j++)
      {
        setServoPulse(servoD, stD - 80 + j * 10); //左腕
        delay(tim);
      }
      for (int j = 0; j < 8; j++)
      {
        setServoPulse(servoD, stD - j * 10); //左腕
        delay(tim);
      }
    }
  }

  if (!dir)
  {
    print_c("with right hand\n", times);
    setServoPulse(servoF, stF - 60);
    for (int i = 0; i < times; i ++)
    {
      int tim = 20;
      for (int j = 0; j < 8; j++)
      {
        setServoPulse(servoG, stG + 80 - j * 10); //右腕
        delay(tim);
      }
      for (int j = 0; j < 8; j++)
      {
        setServoPulse(servoG, stG + j * 10); //右腕
        delay(tim);
      }
    }
  }
}


void sitDown()
{
  sitdown1();
  sitdown2();
}

void sitUp()
{
  situp1();
  delay(1000);
  situp2();
}




void dance(int times)
{
  print_c("Dancing %d times\n", times);
  for (int i = 0; i < times; i ++)
  {
  }
}
