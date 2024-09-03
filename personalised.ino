#include <Servo.h>

Servo servo_horizontal;
int servoH = 90;
int horizontal_max = 160;
int horizontal_min = 10;

Servo servo_vertical;
int servoV = 130;
int vertical_max = 180;
int vertical_min = 50;

#define topRightLDR       A4
#define topLeftLDR        A0
#define bottomLeftLDR     A1
#define bottomRightLDR    A3

void setup() {
 
  Serial.begin(9600);

  servo_horizontal.attach(9);
  servo_vertical.attach(11);


  pinMode(topRightLDR, INPUT);
  pinMode(topLeftLDR, INPUT);
  pinMode(bottomLeftLDR, INPUT);
  pinMode(bottomRightLDR, INPUT);

  startup_calibrate();
}

void loop() {
  
  int TR_val = analogRead(topRightLDR);
  int TL_val = analogRead(topLeftLDR);
  int BL_val = analogRead(bottomLeftLDR);
  int BR_val = analogRead(bottomRightLDR);

  print_Debug_Info(TR_val, TL_val, BL_val, BR_val);
  track_sun(TR_val, TL_val, BL_val, BR_val);

  delay(50); 

}

void startup_calibrate() {
  servo_horizontal.write(servoH);
  servo_vertical.write(servoV);
}

void print_Debug_Info(int TR_value, int TL_value, int BL_value, int BR_value) {
  Serial.println("TR\tTL\tBL\tBR\tSH\tSV");
  Serial.print(TR_value);
  Serial.print("\t");
  Serial.print(TL_value);
  Serial.print("\t");
  Serial.print(BL_value);
  Serial.print("\t");
  Serial.print(BR_value);
  Serial.print("\t");
  Serial.print(servoH);
  Serial.print("\t");
  Serial.print(servoV);
  Serial.print("\t");
  Serial.println();
}

void track_sun(int TR_value, int TL_value, int BL_value, int BR_value) {
  int avg_bot   = (BR_value + BL_value) / 2;
  int avg_top   = (TR_value + TL_value) / 2;
  int avg_left  = (BL_value + TL_value) / 2;
  int avg_right = (TR_value + BR_value) / 2;


  // is difference greater than 10
  // Yes -> move vertical towards the light
  // No  -> don't move the servo
  if (abs(avg_bot - avg_top) > 10) 
  {
    if (avg_bot < avg_top && servoV < vertical_max) 
    {
      servoV++;
    }
    else if (avg_bot > avg_top && servoV > vertical_min)
    {
      servoV--;
    }

    servo_vertical.write(servoV);
  }

  // is difference greater than 10
  // Yes -> move horizontal towards the light
  // No  -> don't move the servo
  if (abs(avg_left - avg_right) > 10) 
  {
    if (avg_left > avg_right && servoH < horizontal_max) 
    {
      servoH++;
    }
    else if (avg_left < avg_right && servoH > horizontal_min)
    {
      servoH--;
    }
    
    servo_horizontal.write(servoH);
  }
}

