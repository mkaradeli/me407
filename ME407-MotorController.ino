#include <AFMotor.h>

#define STEPS_PER_REV 200 // spr

// Connect a stepper motor with 200 steps per revolution (1.8 degree)
// to motor port #1 (M1 and M2)
AF_Stepper motorX(STEPS_PER_REV, 1);
AF_Stepper motorY(STEPS_PER_REV, 2);

#define endSwitchX 31
#define endSwitchY 33



#define exposureTime 1 // s 
#define projectionWidth 3.1 // mm 
#define projectionHeight 2.4 // mm

#define totalWidth 101.6 // mm
#define leadScrewPitch 2 // mm

int absoluteX = 0;
int absoluteY = 0;

int zoneIndexX = 0;
int zoneIndexY = 0;

const int zoneIndexXMax = ceil(totalWidth / projectionWidth);
const int zoneIndexYMax = ceil(totalWidth / projectionHeight);


int projectionWidthInSteps = projectionWidth * STEPS_PER_REV / leadScrewPitch;
int projectionHeightInSteps = projectionHeight * STEPS_PER_REV / leadScrewPitch;



void setup() {
  Serial.begin(9600);           // set up Serial library at 9600 bps
  Serial.println("Stepper test!");

  motorX.setSpeed(100);  // 100 rpm
  motorY.setSpeed(100);  // 100 rpm

  pinMode(endSwitchX,INPUT_PULLUP);
  pinMode(endSwitchY,INPUT_PULLUP);


  calibrate();

  loopThroughSubstrate();


}

// Wrap step functions to allow angle recording
void stepX(int stepCount,int direction) {
  motorX.step(stepCount, direction,SINGLE);
  absoluteX += stepCount;
}
void stepY(int stepCount,int direction) {
  motorY.step(stepCount, direction,SINGLE);
  absoluteY += stepCount;
}


void targetX(int targetStep) {
  if (targetStep - absoluteX > 0){
    motorX.step(targetStep - absoluteX, FORWARD, SINGLE);
  }
  else {
    motorX.step(absoluteX - targetStep, BACKWARD, SINGLE);
  }
  absoluteX = targetStep;
}
void targetY(int targetStep) {
  if (targetStep - absoluteY > 0) {
    motorY.step(targetStep - absoluteY, FORWARD, SINGLE);
  }
  else {
    motorY.step(absoluteY - targetStep, BACKWARD, SINGLE);
  }
  
  absoluteY = targetStep;
}

void moveTo(int targetZoneX, int targetZoneY){
  targetX(targetZoneX * projectionWidthInSteps);
  targetY(targetZoneY * projectionHeightInSteps);
}


void loopThroughSubstrate() {
  while (zoneIndexY < zoneIndexYMax) {
    while (zoneIndexX < zoneIndexXMax) {
      Serial.print("Moving to zone ");
      Serial.print(zoneIndexX);
      Serial.print(", ");
      Serial.println(zoneIndexY);
      moveTo(zoneIndexX,zoneIndexY);

      Serial.println("Exposing...");
      delay(exposureTime * 1000);
      zoneIndexX++;
    }
    zoneIndexX = 0;
    zoneIndexY++;
  }
}


void calibrate() {
  // Calibrate X axis 
  motorX.setSpeed(10);
  Serial.println("Calibrating X until endswitch is triggered.");
  while (digitalRead(endSwitchX)){
    stepX(10, BACKWARD);
  }
  Serial.println("end switch is triggered, setting absolute angle to 0");
  absoluteX = 0;
  motorX.setSpeed(100);

  // Calibrate Y axis 
  motorY.setSpeed(10);
  Serial.println("Calibrating Y until endswitch is triggered.");
  while (digitalRead(endSwitchY)){
    Serial.println("Calibrating Y until endswitch is triggered.");
    stepY(10, BACKWARD);
  }
  Serial.println("end switch is triggered, setting absolute angle to 0");
  absoluteY = 0;
  motorY.setSpeed(100);
}



// the loop function runs over and over again forever
void loop() {
  delay(1000);
}
