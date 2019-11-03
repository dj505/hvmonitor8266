import psutil
import json
import requests
import time

while True:
    try:
        # temps = str(psutil.sensors_temperatures()['coretemp'][1].current) + "°C"
        temps = '''Core 0: {}
Core 1: {}
Core 2: {}
Core 3: {}'''.format(str(psutil.sensors_temperatures()['coretemp'][0].current) + "°C", str(psutil.sensors_temperatures()['coretemp'][1].current) + "°C",
                   str(psutil.sensors_temperatures()['coretemp'][2].current) + "°C", str(psutil.sensors_temperatures()['coretemp'][1].current) + "°C")
        print(str(temps))
        data = temps
        r = requests.post('http://192.168.1.84/post', data=data.encode("utf-8"))
        time.sleep(1)
    except Exception as e:
        print(e)
        time.sleep(60)
