import time
import stepper
import machine


dir_pin_x = 2
step_pin_x = 3
end_switch_x = 4

dir_pin_y = 5
step_pin_y = 6
end_switch_y = 7

stepperX = stepper.Stepper(
    step_pin=step_pin_x,
    dir_pin=dir_pin_x,
    steps_per_rev=200,
    speed_sps=100,  # RPM
)

stepperY = stepper.Stepper(
    step_pin=step_pin_y,
    dir_pin=dir_pin_y,
    steps_per_rev=200,
    speed_sps=100,  # RPM
)

endswitchX = machine.Pin(end_switch_x, machine.Pin.IN, machine.Pin.PULL_UP)
endswitchY = machine.Pin(end_switch_y, machine.Pin.IN, machine.Pin.PULL_UP)
