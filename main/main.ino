#include <Servo.h>

Servo servo;

int servoPin = 9;
int n = 2;
int photoResistors[] = {A0, A1};


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
      delay(20);
    }
  } 
  else {
    for(int i = currentAngle; i >= angle; i--) {
      servo.write(i);
      delay(20);
    }
  }

}

int getResistorDifference(int vals[]) {
  return vals[1] - vals[0];
}


void setup() {
  Serial.begin(9600);
  servo.attach(servoPin);
  servo.write(90);
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

  if(abs(difference) > 50) {
    if(difference > 0) {
      turnServoTo(140);
    }
    else {
      turnServoTo(40);
    }
  }

  delay(2000);
}
