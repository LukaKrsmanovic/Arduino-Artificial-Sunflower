#include <Servo.h>

Servo servo;

int servoPin = 9;
int n = 2;
int photoResistors[] = {A0, A1};
int diffLimit = 30;


void printPhotoResVals(int vals[]) {
  for(int i = 0; i < n; i++) {
    Serial.print(i+1);
    Serial.print(". photo resistor: ");
    Serial.println(vals[i]);
  }
  Serial.println();
}

void turnServoTo(int angle) {
  int currentAngle = servo.read();

  if(currentAngle < angle) {
    for(int i = currentAngle; i <= angle; i++) {
      servo.write(i);
      delay(5);
    }
  } 
  else {
    for(int i = currentAngle; i >= angle; i--) {
      servo.write(i);
      delay(5);
    }
  }

}

int getResistorDifference(int vals[]) {
  return vals[1] - vals[0];
}

bool turnRight(int v1, int v2, int angle) {
  if(v2 > v1+diffLimit && angle < 180) {
    turnServoTo(angle + 1);
    return false;
  }
  return true;
}

bool turnLeft(int v1, int v2, int angle) {
  if(v1 > v2+diffLimit && angle > 0) {
    turnServoTo(angle - 1);
    return false;
  }
  return true;
}


void setup() {
  Serial.begin(9600);
  servo.attach(servoPin);

  // turnServoTo(90);
}

void loop() {

  int angle = servo.read();
  Serial.print("Servo angle is: ");
  Serial.println(angle);

  int vals[n];
  for(int i = 0; i < n; i++) {
    vals[i] = analogRead(photoResistors[i]);
  }
  printPhotoResVals(vals);

  int difference = getResistorDifference(vals);

  if(abs(difference) > diffLimit) {
    if(difference > 0) {
      // A1 is larger than A0
      while(!turnRight(analogRead(photoResistors[0]), analogRead(photoResistors[1]), servo.read())) {}
    }
    else {
      // A0 is larger than A1
      while(!turnLeft(analogRead(photoResistors[0]), analogRead(photoResistors[1]), servo.read())) {}
    }
  }

  delay(1000);
}
