from gpiozero import Button
from signal import pause, alarm, sigtimedwait
import time

current_time = 0.0
diffs = []
infrared = Button(0, pull_up=False)


def infra_event_pressed():
    global current_time
    current_time = time.time()

def infra_event_released():
    global diffs
    diff_time = time.time() - current_time
    diffs += [diff_time]
    # print("Infrared Deactivated", diff_time * 1000000, "uS")


infrared.when_pressed = infra_event_pressed
infrared.when_released = infra_event_released

sigtimedwait([],5)
print([int(a * 10**6) for a in diffs])
# state = 0

# while True:
#     if infrared.value != state:
#         temp_time = time.time()
#         diff = temp_time - current_time1
#         current_time1 = temp_time
#         print("difference ", diff * 1000000)
#         state = infrared.value