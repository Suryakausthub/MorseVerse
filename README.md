Comparative Analysis of Morse Code Detection: TinyML vs. Cloud-Based Machine Learning

Authors:
- Shail Garg (BL.EN.U4CSE22254)
- Gayatri Yerukola (BL.EN.U4CSE22267)
- A. Surya Kausthub (BL.EN.U4CSE22287)

PROJECT OVERVIEW
This repository contains code, models, and documentation for comparing two deployment strategies for real-time Morse-code translation:
1. TinyML (Edge) – a lightweight Transformer/LSTM model running on an ESP32 via TensorFlow Lite for Microcontrollers. On-device inference with minimal network dependency and low latency.
2. Cloud-Based ML – a more complex Transformer/LSTM model served by FastAPI. Remote inference over Wi-Fi, leveraging GPU compute but subject to network delays.

We measure accuracy, latency, and power consumption under identical inputs and visualize results in a web dashboard.

REPOSITORY STRUCTURE
.
├── cloud-backend/
│   ├── app.py               FastAPI server for tap data & decoding
│   ├── requirements.txt     Python dependencies
│   └── models/
│       └── cloud_transformer.pt
├── edge-firmware/
│   ├── main.cpp             ESP32 firmware: sensor input, preprocessing, TinyML inference
│   ├── model.tflite         Quantized TFLite model
│   └── platformio.ini       Build configuration
├── dashboard/
│   ├── src/                 React/Vue UI for live results & charts
│   ├── package.json
│   └── README.md            Dashboard setup instructions
├── data/
│   ├── morse_dataset.xlsx   Raw tap-text dataset
│   └── processed.csv        Preprocessed data
├── notebooks/
│   ├── training.ipynb       Model training & evaluation
│   └── analysis.ipynb       Results visualization & metrics
└── README.txt               This file

INSTALLATION & SETUP

1. Cloud Backend
   a. Create & activate a Python 3.9+ virtual environment:
      python -m venv .venv
      source .venv/bin/activate   (or .venv\Scripts\activate on Windows)
   b. Install dependencies:
      pip install -r cloud-backend/requirements.txt
   c. Launch server:
      uvicorn cloud-backend.app:app --host 0.0.0.0 --port 8000

2. Edge Firmware
   a. Install PlatformIO (CLI or VS Code).
   b. Copy model.tflite into edge-firmware/lib/model/.
   c. Build & upload:
      cd edge-firmware
      pio run --target upload

3. Dashboard
   a. Install Node.js 16+:
      cd dashboard
      npm install
      npm run dev
   b. Configure API URL to http://<server-ip>:8000

SYSTEM ARCHITECTURE
Edge Path:
  Sensor → ESP32 preprocessing → TFLite inference → OLED/Serial output

Cloud Path:
  Sensor → ESP32 preprocess & send JSON → FastAPI inference → JSON response → UI

Comparison Dashboard:
  Collects latency, accuracy, power data from both paths and shows side-by-side charts.

RESULTS & METRICS
Metric            | TinyML (ESP32)  | Cloud ML (Server)
------------------|-----------------|-------------------
Accuracy          | ~92%            | ~97%
End-to-End Latency| <50 ms          | 300–500 ms
Power Consumption | <200 mW         | N/A

See notebooks/analysis.ipynb for full evaluation.

DEFINITION OF DONE
- Tap detection with >90% accuracy on ESP32
- TinyML inference <100 ms
- Cloud model response <500 ms
- Real-time comparison dashboard
- Complete documentation and user guide

FUTURE SCOPE
1. Multi-modal Input (audio, accelerometer)
2. Bidirectional Feedback (vibration/audio output)
3. Adaptive On-device Learning
4. Secure Encrypted Communication

LICENSE
MIT License (see LICENSE file)

ACKNOWLEDGMENTS
- TensorFlow Lite for Microcontrollers
- FastAPI & Uvicorn
- ESP32 community examples

“First transmitted in 1844, Morse code bridges distances—now with ML at both the edge and the cloud.”
