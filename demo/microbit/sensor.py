from microbit import *

def get_sensor_data():
    x, y, z = accelerometer.get_x(), accelerometer.get_y(), accelerometer.get_z()
    a, b = button_a.is_pressed(), button_b.is_pressed()
    print(x, y, z, a, b)

uart.init(115200)

while True:
    sleep(100)
    get_sensor_data()
    if uart.any():
        str=uart.readline()
        display.scroll(str,wait=False,loop=True)
