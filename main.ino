#include <Servo.h>

Servo leftTopMotor;
Servo leftBottomMotor;
Servo rightTopMotor;
Servo rightBottomMotor;

/*
  Motors Pins:

  (4) o---o (6)
        |
        |
  (5) o---o (7)

  Sensors Pins:

      (A0)
      o---o
  (A5)  |  (A1)
  (A4)  |  (A2)
      o---o
      (A3)

  Logic:
    -read values from all sensors
    -remember the minimum value and index of the sensor recorded it
    (less sensor value -> higher light intensity)
    -if LIGHT_INTENSITY_THRESHOLD is not met -> stop all motors
    -if minimum value recorded from the forward sensor -> move forward
    -rotate rotate to the direction of the index sensor
*/

int MOTOR_PINS[] = {4,5,6,7};
int SENSOR_PINS[] = {A0, A1, A2, A3, A4, A5};

int sensorValue = 0;
int FORWARD_SENSOR_INDEX = 0;

const int SPEED = 50;
const int LIGHT_INTENSITY_THRESHOLD = 200;    // minimum light intensity to start moving

void setup() {
  Serial.begin(9600);

  pinMode(MOTOR_PINS[0],OUTPUT);
  pinMode(MOTOR_PINS[1],OUTPUT);
  pinMode(MOTOR_PINS[2],OUTPUT);
  pinMode(MOTOR_PINS[3],OUTPUT);

  leftTopMotor.attach(MOTOR_PINS[0]);
  leftBottomMotor.attach(MOTOR_PINS[1]);
  rightTopMotor.attach(MOTOR_PINS[2]);
  rightBottomMotor.attach(MOTOR_PINS[3]);
  
  for (int i = 0; i < 6; i++) {
    pinMode(SENSOR_PINS[i], INPUT);
  }
}

void loop() {

  int minLight = 500;         // sensor values do not exceed 500
  int minLightIndex = 0;

  for (int i = 0; i < 6; i++) {
    int sensorValue = analogRead(SENSOR_PINS[i]);
    if(i == 1) {
      sensorValue *= 2;       // custom readjustment for A1 photoresistor with excessive sensivity
    }

    // printing all sensor measurements for debugging
    Serial.print(i);
    Serial.print(" ");
    Serial.print(sensorValue);
    Serial.print("; ");


    if (sensorValue < minLight) {
      minLight = sensorValue;
      minLightIndex = i;
    }
  }
  Serial.println();

  if (minLight >= LIGHT_INTENSITY_THRESHOLD) {
    Serial.println("Stop moving");
    stop();
    return;
  }

  if(minLightIndex == FORWARD_SENSOR_INDEX){
    Serial.println("Move forward");
    moveForward();
  } else {
    if(minLightIndex == 1 || minLightIndex == 2) {    // rotate to the direction of the triggered side sensors
      Serial.println("Rotate Left");
      turnLeft();
    } else {
      Serial.println("Rotate Right");
      turnRight();
    }
  }
  delay(1200);
}

void moveForward() {
  moveLeftTopMotor(SPEED);
  moveLeftBottomMotor(-SPEED);
  moveRightTopMotor(-SPEED);
  moveRightBottomMotor(SPEED);
  delay(10);
}

void stop() {
  moveLeftTopMotor(0);
  moveLeftBottomMotor(0);
  moveRightTopMotor(0);
  moveRightBottomMotor(0);
  delay(10);
}

void turnLeft() {
  moveLeftTopMotor(-SPEED);
  moveLeftBottomMotor(-SPEED);
  moveRightTopMotor(-SPEED);
  moveRightBottomMotor(-SPEED);
  delay(10);
}

void turnRight() {
  moveLeftTopMotor(SPEED);
  moveLeftBottomMotor(SPEED);
  moveRightTopMotor(SPEED);
  moveRightBottomMotor(SPEED);
  delay(10);
}

void moveLeftTopMotor(int value) {
  leftTopMotor.write(map(value,-100,100,1000,2000));
}
void moveLeftBottomMotor(int value) {
  leftBottomMotor.write(map(value,-100,100,1000,2000));
}
void moveRightTopMotor(int value) {
  rightTopMotor.write(map(value,-100,100,1000,2000));
}
void moveRightBottomMotor(int value) {
  rightBottomMotor.write(map(value,-100,100,1000,2000));
}
