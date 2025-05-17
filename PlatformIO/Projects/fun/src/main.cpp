#include <Arduino.h>

// ----- CONFIG -----
const int TOUCH_PIN        = 4;     // టచ్ సిగ్నల్ పిన్
const uint16_t DOT_MAX_MS  = 200;   // ≤200 ms ⇒ DOT
const uint16_t LETTER_GAP_MS = 600; // ≥600 ms ⇒ letter end
const uint16_t WORD_GAP_MS   = 1400;// ≥1400 ms ⇒ word end
// -------------------

String currentSymbol;
uint32_t pressStart  = 0;
uint32_t lastRelease = 0;
bool pressing = false;

struct MorsePair { const char* code; char letter; };
const MorsePair table[] = {
  {".-", 'A'},  {"-...", 'B'}, {"-.-.", 'C'}, {"-..", 'D'}, {".", 'E'},
  {"..-.", 'F'},{"--.", 'G'},  {"....", 'H'}, {"..", 'I'},  {".---", 'J'},
  {"-.-", 'K'}, {".-..", 'L'}, {"--", 'M'},   {"-.", 'N'},  {"---", 'O'},
  {".--.", 'P'},{"--.-", 'Q'}, {".-.", 'R'},  {"...", 'S'}, {"-", 'T'},
  {"..-", 'U'}, {"...-", 'V'}, {".--", 'W'},  {"-..-", 'X'},{"-.--", 'Y'},
  {"--..", 'Z'},
  {"-----",'0'},{".----",'1'},{"..---",'2'},{"...--",'3'},{"....-",'4'},
  {".....",'5'},{"-....",'6'},{"--...",'7'},{"---..",'8'},{"----.",'9'}
};
const int TABLE_LEN = sizeof(table)/sizeof(table[0]);

char decode(const String& code) {
  for (int i = 0; i < TABLE_LEN; ++i)
    if (code == table[i].code) return table[i].letter;
  return '?';
}

void flushLetter(bool endOfWord = false) {
  if (currentSymbol.length()) {
    Serial.print(decode(currentSymbol)); // అక్షరాన్ని ప్రింట్ చేయి
    if (endOfWord)
      Serial.println();                  // పదం పూర్తైతే కొత్త లైన్
    else
      Serial.print(' ');                 // లేకపోతే space
    currentSymbol = "";
  } else if (endOfWord) {
    Serial.println();                    // పదాల మధ్య రెండు కొత్తలైన్లు రావకుండా చేసేందుకు
  }
}

void setup() {
  pinMode(TOUCH_PIN, INPUT);
  Serial.begin(115200);
  Serial.println("\n--- ESP32 Morse Reader (letter space, word newline) ---");
}

void loop() {
  bool touched = digitalRead(TOUCH_PIN) == HIGH;  // TTP223 HIGH on touch
  uint32_t now = millis();

  // టచ్ ప్రారంభం
  if (touched && !pressing) {
    pressing = true;
    pressStart = now;

    uint32_t gap = now - lastRelease;
    if (gap >= WORD_GAP_MS) {          // WORD GAP
      flushLetter(true);               // అక్షరం వస్తే ప్రింట్ చేసి newline
    } else if (gap >= LETTER_GAP_MS) { // LETTER GAP
      flushLetter(false);              // అక్షరం వస్తే ప్రింట్ చేసి space
    }
  }

  // టచ్ ముగింపు
  if (!touched && pressing) {
    pressing = false;
    uint32_t dur = now - pressStart;
    currentSymbol += (dur <= DOT_MAX_MS) ? '.' : '-';
    lastRelease = now;
  }

  // చివరలో (గ్యాప్ లేనప్పటికీ) 2 సెకన్లకు పైగా ఇన్‌పుట్ లేకపోతే లాస్ట్ లెటర్ ఫ్లష్ చేయండి
  if (!pressing && (millis() - lastRelease) > WORD_GAP_MS * 2) {
    flushLetter(true);
  }
}