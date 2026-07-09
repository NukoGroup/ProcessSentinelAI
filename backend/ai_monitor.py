# Python AI Monitor for ProcessSentinelAI
import paho.mqtt.client as mqtt
import json
from sklearn.ensemble import IsolationForest
import numpy as np

model = IsolationForest(contamination=0.1) # Train on normal data later

def on_message(client, userdata, msg):
  data = json.loads(msg.payload)
  vib = data.get('vib_rms', 0)
  temp = data.get('temp', 0)
  flow = data.get('flow', 0)
  print(f'Received: Vib {vib}, Temp {temp}, Flow {flow}')
  if vib > 0.5 or temp > 45:
    print('ANOMALY! Alert and control action.')
    # Publish control command e.g. client.publish('control/relay1', 'OFF')

client = mqtt.Client()
client.on_message = on_message
client.connect('YOUR_BROKER', 1883, 60)
client.subscribe('sensors/#')
client.loop_forever()