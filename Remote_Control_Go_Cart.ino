#include <AccelStepper.h>

const int gasPulse = 1, gasDir = 2;
const int brakePulse = 3, brakeDir = 4;
const int steerPulse = 5, steerDir = 6;

AccelStepper gasStepper(AccelStepper::DRIVER, gasPulse, gasDir);
AccelStepper brakeStepper(AccelStepper::DRIVER, brakePulse, brakeDir);
AccelStepper steerStepper(AccelStepper::DRIVER, steerPulse, steerDir);

const float pedalMaxSpeed = 300, pedalAcceleration = 100;
const float steerMaxSpeed = 500, steerAcceleration = 200;

const long pedalMinPos = 0, pedalMaxPos = 100;
const long steerMinPos = -100, steerMaxPos = 100;

long minInput = 0.0, maxInput = 1.0;
long rawGasInput = 0, rawBrakeInput = 0, rawSteerInput = 0;

void setup() {
  gasStepper.setMaxSpeed(pedalMaxSpeed);
  brakeStepper.setMaxSpeed(pedalMaxSpeed);

  gasStepper.setAcceleration(pedalAcceleration);
  brakeStepper.setAcceleration(pedalAcceleration);

  steerStepper.setMaxSpeed(steerMaxSpeed);
  steerStepper.setAcceleration(pedalAcceleration);
}

void loop() {
  // insert processing to get inputs

  setPedalStepperPos(gasStepper, mapStepperInputs(rawGasInput, pedalMinPos, pedalMaxPos));
  setPedalStepperPos(brakeStepper, mapStepperInputs(rawBrakeInput, pedalMinPos, pedalMaxPos));

  setSteerStepperPos(mapStepperInputs(rawSteerInput, steerMinPos, steerMaxPos));
}

long mapStepperInputs(long stepperInput, long stepperMinPos, long stepperMaxPos) {
  return map(stepperInput, minInput, maxInput, stepperMinPos, stepperMaxPos);
}

void setPedalStepperPos(AccelStepper stepper, long targetPos) {
  if (targetPos < pedalMinPos) {
    targetPos = pedalMinPos;
  } else if (targetPos > pedalMaxPos) {
    targetPos = pedalMaxPos;
  }

  stepper.moveTo(targetPos);
}

void setSteerStepperPos(long targetPos) {
  if (targetPos < steerMinPos) {
    targetPos = steerMinPos;
  } else if (targetPos > steerMaxPos) {
    targetPos = steerMaxPos;
  }

  steerStepper.moveTo(targetPos);
}
