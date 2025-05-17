==============================================================
Comparative Analysis of Morse Code Detection: TinyML vs. Cloud-Based ML
==============================================================

Authors:
  • Shail Garg            (BL.EN.U4CSE22254)
  • Gayatri Yerukola      (BL.EN.U4CSE22267)
  • A. Surya Kausthub     (BL.EN.U4CSE22287)

PROJECT OVERVIEW
----------------
This repository contains code, models, and documentation for a side-by-side comparison of two deployment strategies for real-time Morse-code translation:

  1) TinyML (Edge)
     - Lightweight Transformer/LSTM model running on an ESP32 via TensorFlow Lite for Microcontrollers.
     - Fully on-device inference with minimal network dependency and very low latency.

  2) Cloud-Based ML
     - Full-scale Transformer/LSTM model served by FastAPI on GPU-equipped servers.
     - Remote inference over Wi-Fi; leverages powerful compute resources but incurs network round-trip delay.

We evaluate both systems on identical tap inputs and compare:
  • Accuracy (%)  
  • End-to-end Latency (ms)  
  • Power Consumption (mW)  

Results are visualized in a web dashboard for easy analysis.

REPOSITORY STRUCTURE
--------------------
.
├── cloud-backend/  
│     app.py               FastAPI server receives tap data and returns decoded text  
│     requirements.txt     Python dependencies for cloud service  
│     models/  
│         cloud_transformer.pt   Trained PyTorch model for server inference  

├── edge-firmware/  
│     main.cpp             ESP32 firmware: sensor input, preprocessing, TinyML inference  
│     model.tflite         Quantized TensorFlow Lite model for on-device use  
│     platformio.ini       PlatformIO build configuration  

├── dashboard/  
│     src/                 Frontend source (React or Vue) for live comparison charts  
│     package.json         Node.js dependencies and scripts  
│     README.md            Dashboard setup and usage instructions  

├── data/  
│     morse_dataset.xlsx   Original tap-to-text dataset  
│     processed.csv        Cleaned and preprocessed training data  

├── notebooks/  
│     training.ipynb       Jupyter notebook for model training and evaluation  
│     analysis.ipynb       Notebook for logging, metrics calculation, and plotting  

└── README.txt            This file

INSTALLATION & SETUP
--------------------

1) Cloud Backend
   a) Create Python v3.9+ virtual environment  
      └─ python -m venv .venv  
         Windows: .venv\Scripts\activate  
         macOS/Linux: source .venv/bin/activate  
   b) Install dependencies  
      └─ pip install -r cloud-backend/requirements.txt  
   c) Run the server  
      └─ uvicorn cloud-backend.app:app --host 0.0.0.0 --port 8000  

2) Edge Firmware
   a) Install PlatformIO CLI or VS Code extension  
   b) Copy model.tflite into edge-firmware/lib/model/  
   c) Build and upload to ESP32  
      └─ cd edge-firmware  
      └─ pio run --target upload  

3) Dashboard
   a) Install Node.js (v16+)  
   b) Install and launch  
      └─ cd dashboard  
      └─ npm install  
      └─ npm run dev  
   c) Configure API endpoint in dashboard settings to  
      http://<CLOUD_SERVER_IP>:8000  

SYSTEM ARCHITECTURE
-------------------
Edge (TinyML) Path:
  Sensor → ESP32 Preprocessing → TensorFlow Lite Inference → OLED/Serial Output

Cloud Path:
  Sensor → ESP32 Preprocessing → JSON over MQTT/HTTP → FastAPI Inference → JSON Response → UI

Comparison Dashboard:
  Collects and displays latency, accuracy, and power data from both paths in side-by-side charts.

RESULTS & METRICS
-----------------
Metric               | TinyML (ESP32)   | Cloud ML (Server)
---------------------|------------------|-------------------
Accuracy             | ~92%             | ~97%
End-to-End Latency   | <50 ms           | 300–500 ms
Power Consumption    | <200 mW          | N/A

(See notebooks/analysis.ipynb for full logs and plots.)

DEFINITION OF DONE
------------------
[✔] Tap detection on ESP32 with >90% classification accuracy  
[✔] TinyML inference latency <100 ms  
[✔] Cloud model response <500 ms  
[✔] Real-time comparison dashboard operational  
[✔] Complete documentation and user guide included  

FUTURE SCOPE
------------
1) Multi-modal Input (audio + accelerometer + touch)  
2) Bidirectional Feedback (vibration or audio output of Morse code)  
3) On-device Adaptive Learning for personalized tap patterns  
4) Lightweight Encryption for secure cloud communication  

LICENSE
-------
This project is released under the MIT License. See the LICENSE file for details.

ACKNOWLEDGMENTS
---------------
• TensorFlow Lite for Microcontrollers  
• FastAPI & Uvicorn  
• ESP32 and PlatformIO communities  

“First transmitted in 1844, Morse code bridges distances—now with machine learning at both the edge and the cloud.”  
