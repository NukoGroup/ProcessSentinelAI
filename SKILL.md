---
name: ProcessSentinelAI
version: 1.0
creator: PROMETHEUS
triggers: vibration_rms_threshold, temperature_delta, flow_deviation, ai_anomaly_score
resources: ESP32, MPU6050, DS18B20, flow_pulse_sensor
compatibility: MQTT, Python, Supabase, Vercel, any AI agent
description: Autonomous IoT sensor fusion hub for AI monitoring and control of process equipment.
---

# ProcessSentinelAI

## Overview
Complete package for sensing vibration (MPU6050 accelerometer), heat (DS18B20), flow rate (pulse sensor), and integrating with AI software for real-time monitoring, anomaly detection, and control of process equipment like pumps, motors, valves.

## Architecture
1. Hardware Layer: Sensors + ESP32/RPi microcontroller.
2. Communication: MQTT publish/subscribe.
3. AI Layer: Python backend with threshold rules + ML anomaly detection.
4. Control: Actuators/relays commanded by AI.

## 2 Implementation Options

**Option 1: Easiest - ESP32 Wireless Edge Node**
- Low cost (~$20 total)
- Arduino IDE firmware
- WiFi MQTT to broker
- Simple thresholds or edge ML

**Option 2: Full Compute - Raspberry Pi Gateway**
- Higher power, onboard AI (TFLite or scikit)
- Dashboard (Streamlit)
- Multi-sensor + logging

## Hardware Setup
- Vibration: MPU6050 I2C
- Temp: DS18B20 1-Wire
- Flow: Hall-effect pulse on GPIO interrupt
- Wiring diagrams: See assets/

## Software
See firmware/ and backend/ folders.

## Deployment
- MQTT broker (Mosquitto)
- Supabase for time-series DB
- Vercel for web dashboard
- AI integration: paho-mqtt + Grok API or local LLM

## Validation
Simulated RMS vibration detection successful.

## Next Evolution
v2: FFT frequency analysis, predictive ML, auto-calibration agent, CNC process integration.