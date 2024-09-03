#include <Servo.h>   
Servo servo_horizontal;
int servoh = 90;              // Start position of horizontal servo
int servohLimitHigh = 180;    // Servo max position limit
int servohLimitLow = 0;      // Servo min position limit

Servo servo_vertical;
int servov = 135;              // Start position of vertical servo
int servovLimitHigh = 180;    // Servo max position limit
int servovLimitLow = 90;      // Servo min position limit

bool increase = true;

#define SERVO_H_LIMIT_H     160   

void setup() {
 
  Serial.begin(9600);

  servo_horizontal.attach(9);       // attach servo and move to start position
  servo_horizontal.write(servoh);

  servo_vertical.attach(11);        // attach servo and move to start position
  servo_vertical.write(servov);

  Serial.println("Servo_H\tServo_V\tincrease");
}

void loop() {
  // put your main code here, to run repeatedly:
  int servo_h_val = servo_horizontal.read();
  int servo_v_val = servo_vertical.read();

  Serial.println("Servo_H\tServo_V\tincrease");
  Serial.print(servo_h_val);
  Serial.print("\t");
  Serial.print(servo_v_val);
  Serial.print("\t");
  Serial.print(increase);
  Serial.println("\t");

  // check if the servo has reached its limit if so flip the direction
  if (servo_h_val == servohLimitHigh) {
    increase = false;
  }
  else if (servo_h_val == servohLimitLow) {
    increase = true;
  }

  // increases or decreases the horizontal servo
  if (servo_h_val < servohLimitHigh & increase == true) {
    servo_horizontal.write(servo_h_val + 1);
  }
  else if (servo_h_val > servohLimitLow & increase == false) {
    servo_horizontal.write(servo_h_val - 1);
  }

  // increases or decreases the vertical servo
  if (servo_v_val < servovLimitHigh & increase == true) {
    servo_vertical.write(servo_v_val + 1);
  }
  else if (servo_v_val > servovLimitLow & increase == false) {
    servo_vertical.write(servo_v_val - 1);
  }

  delay(25);
}
