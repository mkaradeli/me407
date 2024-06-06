import time

from motor import stepperX, stepperY, endswitchX, endswitchY
from math import ceil

exposureTime = 0.1  # s

projectionWidth = 3.1  # mm
projectionHeight = 2.4  # mm

totalWidth = 101.6  # mm

STEPS_PER_REV = 200
leadScrewPitch = 2  # mm

print("initializing")
# Go Left until toggleing switch
stepperX.speed(20)  # low speed for calibration
stepperX.free_run(-1)  # move backwards without stopping
while endswitchX.value():  # wait until endswitch is triggered
    pass
stepperX.stop()  # stop stepper motor as soon as endswitch is triggered
stepperX.overwrite_pos(0)  # overwrite absolute angle of the stepper motor
stepperX.speed(100)  # return to high speed operation
stepperX.target(0)  # set target angle to current angle to avoid jumping upon activation
stepperX.track_target()  # start stepper again

stepperY.speed(20)  # low speed for calibration
stepperY.free_run(-1)  # move backwards without stopping
while endswitchY.value():  # wait until endswitch is triggered
    pass
stepperY.stop()  # stop stepper motor as soon as endswitch is triggered
stepperY.overwrite_pos(0)  # overwrite absolute angle of the stepper motor
stepperY.speed(100)  # return to high speed operation
stepperY.target(0)  # set target angle to current angle to avoid jumping upon activation
stepperY.track_target()  # start stepper again


projectionWidthInSteps = projectionWidth * STEPS_PER_REV // leadScrewPitch
projectionHeightInSteps = projectionHeight * STEPS_PER_REV // leadScrewPitch


horizontalZoneIndex = 0
verticalZoneIndex = 0

horizontalZoneIndexMax = ceil(totalWidth / projectionWidth)
verticalZoneIndexMax = ceil(totalWidth / projectionHeight)
print(f"horizontalZoneIndexMax = {horizontalZoneIndexMax}")
print(f"verticalZoneIndexMax = {verticalZoneIndexMax}")
while verticalZoneIndexMax < verticalZoneIndexMax:
    while horizontalZoneIndex < horizontalZoneIndexMax:
        # expose area by the dedicated time exposureTime
        time.sleep(exposureTime)
        horizontalZoneIndex += 1
        if horizontalZoneIndex != horizontalZoneIndexMax:
            stepperX.target(projectionWidthInSteps * horizontalZoneIndex)
            print(
                f"stepperX target angle = {projectionWidthInSteps * horizontalZoneIndex}"
            )
    horizontalZoneIndex = 0
    stepperX.target(0)
    print(f"stepperX target angle = {0}")
    verticalZoneIndex += 1
    if verticalZoneIndex != verticalZoneIndexMax:
        stepperY.target(projectionHeightInSteps * verticalZoneIndex)
        print("stepperY target angle = {projectionHeightInSteps * verticalZoneIndex}")
verticalZoneIndex = 0
stepperX.target(0)
print(f"stepperX target angle = {0}")
stepperY.target(0)
print(f"stepperY target angle = {0}")
print("Done")
