#include <Arduino.h>

#define TOUCH_PIN 4  // TTP223 signal connected to GPIO4

String morse = "";
String currentWord = "";
unsigned long pressStart = 0;
unsigned long lastReleaseTime = 0;
bool isPressed = false;

int dotThreshold = 300;       // < 300ms = dot, else dash
int letterPause = 1000;       // >= 1s gap = new letter
int wordPause = 2000;         // >= 2s gap = new word

char decodeMorse(String code);

void setup() {
  Serial.begin(115200);
  pinMode(TOUCH_PIN, INPUT);
  Serial.println("Morse Code Translator Started...");
}

void loop() {
  int state = digitalRead(TOUCH_PIN);

  // Press detected
  if (state == HIGH && !isPressed) {
    pressStart = millis();
    isPressed = true;
  }

  // Released
  if (state == LOW && isPressed) {
    unsigned long pressDuration = millis() - pressStart;

    if (pressDuration < dotThreshold) {
      morse += ".";
    } else {
      morse += "-";
    }

    isPressed = false;
    lastReleaseTime = millis();
  }

  // Letter pause
  if (!isPressed && morse.length() > 0 && millis() - lastReleaseTime >= letterPause) {
    char decoded = decodeMorse(morse);
    currentWord += decoded;
    Serial.print(decoded);  // Print on same line
    morse = "";
  }

  // Word pause
  if (!isPressed && currentWord.length() > 0 && millis() - lastReleaseTime >= wordPause) {
    Serial.println();  // Move to next line = new word
    currentWord = "";
  }

  delay(10);
}

// Morse decoder
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
