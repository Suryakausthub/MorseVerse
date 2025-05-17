#include <Arduino.h>

#define TOUCH_PIN T0  // GPIO4 (can change to T1-T9)

String morse = "";
unsigned long lastTouchTime = 0;
bool isTouched = false;
int dotDuration = 200; // ms

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("Touch sensor Morse decoder started");
}

void loop() {
  int touchValue = touchRead(TOUCH_PIN);  // Read capacitance value
  bool touched = touchValue < 30;  // Adjust threshold as needed

  if (touched && !isTouched) {
    lastTouchTime = millis();
    isTouched = true;
  }

  if (!touched && isTouched) {
    unsigned long duration = millis() - lastTouchTime;

    if (duration < dotDuration) {
      morse += ".";  // DOT
    } else {
      morse += "-";  // DASH
    }

    Serial.print("Morse so far: ");
    Serial.println(morse);

    isTouched = false;
  }

  // End of letter detection
  static unsigned long lastInputTime = 0;
  if (!touched) {
    if (millis() - lastTouchTime > 1000 && morse.length() > 0) {
      char decoded = decodeMorse(morse);
      Serial.print("Decoded: ");
      Serial.println(decoded);
      morse = "";
    }
  }

  delay(10);
}

// Basic Morse decoding map
char decodeMorse(String code) {
  if (code == ".-") return 'A';
  if (code == "-...") return 'B';
  if (code == "-.-.") return 'C';
  if (code == "-..") return 'D';
  if (code == ".") return 'E';
  if (code == "..-.") return 'F';
  if (code == "--.") return 'G';
  if (code == "....") return 'H';
  if (code == "..") return 'I';
  if (code == ".---") return 'J';
  if (code == "-.-") return 'K';
  if (code == ".-..") return 'L';
  if (code == "--") return 'M';
  if (code == "-.") return 'N';
  if (code == "---") return 'O';
  if (code == ".--.") return 'P';
  if (code == "--.-") return 'Q';
  if (code == ".-.") return 'R';
  if (code == "...") return 'S';
  if (code == "-") return 'T';
  if (code == "..-") return 'U';
  if (code == "...-") return 'V';
  if (code == ".--") return 'W';
  if (code == "-..-") return 'X';
  if (code == "-.--") return 'Y';
  if (code == "--..") return 'Z';
  return '?';  // Unknown
}
