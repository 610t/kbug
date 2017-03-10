#!/usr/local/bin/python2.7
import serial
import scratch

class ScratchReceiver(object):
  @staticmethod
  def broadcast_handler(message):
    print('[receive] broadcast:', message)
    s.write(message.encode('utf-8'))
  @staticmethod
  def sensor_update_handler(**sensor_data):
    for name, value in sensor_data.items():
      print('[receive] sensor-update:', name, value)

PORT = "/dev/cuaU0"
BAUD = 115200

s = serial.Serial(PORT)
s.baudrate = BAUD
s.parity   = serial.PARITY_NONE
s.databits = serial.EIGHTBITS
s.stopbits = serial.STOPBITS_ONE

rsc = scratch.RemoteSensorConnection(ScratchReceiver.broadcast_handler, ScratchReceiver.sensor_update_handler)
rsc.connect()
while True:
    data = s.readline().decode('UTF-8')
    data_list = data.rstrip().split(' ')
    try:
        x, y, z, a, b = data_list
        print(x,y,z,a,b)
        rsc.send_sensor_update(x=int(x))
        rsc.send_sensor_update(y=int(y))
        rsc.send_sensor_update(z=int(z))
        rsc.send_sensor_update(a=str(a))
        rsc.send_sensor_update(b=str(b))
    except:
        pass
rsc.disconnect()
