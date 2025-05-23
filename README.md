
# Morse Code Translator using TinyML

### Authors:
Shail Garg, Yerukola Gayatri, Surya Kausthub A, Pooja Gowda  
Department of Computer Science and Engineering, Amrita School of Computing, Bengaluru, Amrita Vishwa Vidyapeetham

---

## 🔍 Overview

This project compares two approaches for Morse code translation using tactile taps:  
- **TinyML (on-device)** with ESP32 and TTP223B sensor  
- **Cloud-based** using LSTM autoencoder via REST API  

It evaluates trade-offs in **accuracy, latency, and deployment** to identify the most suitable method for real-time assistive communication systems.

---

## 📁 Folder Structure

```
├── cloud_model/
│   ├── morse_lstm.py
│   ├── translate_api.py
│   ├── cloud_transformer.pt
├── tinyml_model/
│   ├── morse_lstm_tinyml.ipynb
│   ├── tflite_model.h
│   ├── main_esp32.ino
├── dataset/
│   └── morse_dataset.xlsx
├── README.md
├── requirements.txt
```

---

**Format**: Sequences of dots and dashes (0 = dot, 1 = dash) paired with alphanumeric characters  
**Total samples**: 40,000  
**Balanced distribution** of letters and digits

---

## 🧠 Model Architecture

### TinyML Model:
- **Framework**: TensorFlow Lite  
- **Architecture**: 2-layer LSTM (quantized)  
- **Deployment**: Runs on ESP32 (TFLite Micro)

### Cloud Model:
- **Framework**: PyTorch  
- **Architecture**: 3-layer LSTM with 128 hidden units each  
- **Deployment**: Flask API served over HTTP

---

## ⚙️ How to Run

### 1. Train the Models

#### Cloud Model
```bash
cd cloud_model
python morse_lstm.py
```

#### TinyML Model
- Open `morse_lstm_tinyml.ipynb` in Jupyter or Google Colab
- Train and export model as `.tflite`
- Convert to `.h` and include in `main_esp32.ino`
- Upload to ESP32 using Arduino IDE

### 2. Start the Cloud API
```bash
cd cloud_model
python translate_api.py
```

### 3. Connect ESP32 + Sensor
- Connect TTP223B sensor to ESP32 GPIO pin  
- Taps are read as Morse (0 = short tap, 1 = long tap)  
- Choose local inference (TinyML) or send HTTP POST to cloud

---

## 📊 Evaluation

| Metric           | TinyML (ESP32) | Cloud LSTM |
|------------------|----------------|-------------|
| Accuracy         | 77.0%          | 89.0%       |
| Precision        | 75.0%          | 88.0%       |
| Recall           | 78.0%          | 90.0%       |
| F1 Score         | 76.0%          | 89.0%       |
| Avg Latency      | ~0.12 sec      | ~80.89 sec  |
| Internet Required| ❌             | ✅          |

---

## 💡 Use Cases

- Assistive communication for individuals with disabilities  
- Disaster/emergency response systems  
- Offline IoT/wearable applications

---

## 📬 Contact

For queries, contact:  
- Shail Garg: bl.en.u4cse22254@bl.students.amrita.edu  
- Yerukola Gayatri: bl.en.u4cse22267@bl.students.amrita.edu  
- Surya Kausthub A: bl.en.u4cse22287@bl.students.amrita.edu  
- Pooja Gowda : g_pooja@blr.amrita.edu 

---

## 📚 References

Refer to the final project paper for complete list of citations used.
