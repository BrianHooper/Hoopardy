#include <stdio.h>
#include <string.h>

#define NUMPINS 4
#define ULONG_MAX 4294967295

int RESET_PIN = 7;

int pins[] = {10, 11, 12, 13};
boolean pressed[] = {false, false, false, false};
unsigned long lastPressed[] = {ULONG_MAX, ULONG_MAX, ULONG_MAX, ULONG_MAX}; 
char* words[NUMPINS];

unsigned int globalDelayTimeMs = 5000;
unsigned long globalTime = 0;

void setup() {
  Serial.begin(9600);
  
  for(unsigned short i = 0; i < NUMPINS; i++) {
      pinMode(pins[i], INPUT);
  }
  pinMode(RESET_PIN, INPUT);
}

char* intToString(int num) {
    int length = snprintf(NULL, 0, "%d", num);
    char* str = (char*)malloc(length + 1);
    snprintf(str, length + 1, "%d", num);
    return str;
}

char* joinStrings(char* strings[]) {
    int totalLength = 0;
    for (int i = 0; i < NUMPINS; ++i) {
        totalLength += strlen(strings[i]);
    }
    totalLength += NUMPINS - 1; // Account for the commas

    char* result = (char*)malloc(totalLength + 1);
    strcpy(result, strings[0]);
  
    for (int i = 1; i < NUMPINS; ++i) {
        strcat(result, ",");
        strcat(result, strings[i]);
    }

    return result;
}

char* calcRank(int pinIdx) {
  char* posPinA = "-";
  if (lastPressed[pinIdx] != ULONG_MAX) {
    int counter = 1;
    for(unsigned short i = 0; i < NUMPINS; i++) {
      if (i == pinIdx) {
        continue;
      }
      if (lastPressed[i] < lastPressed[pinIdx]) {
        counter++; 
      }
    }
    posPinA = intToString(counter);
  }
  return posPinA;
}

void resetCounter() {
  Serial.println("Timer reset");
  for(unsigned short i = 0; i < NUMPINS; i++) {
  lastPressed[i] = ULONG_MAX;
  }
}

void press(int pinIdx) {
  unsigned long currentTime = millis();
  
  if (currentTime - globalTime >= globalDelayTimeMs) {
    globalTime = currentTime;
    resetCounter();
  }
  
  lastPressed[pinIdx] = currentTime;
  
  for(unsigned short i = 0; i < NUMPINS; i++) {
    words[i] = calcRank(i);
  }
  
  char* joinedString = joinStrings(words);
  Serial.println(joinedString); 
}

void loop() {
  for(unsigned short i = 0; i < NUMPINS; i++) {
    if (digitalRead(pins[i]) == HIGH) {
      if (!pressed[i]) {
        pressed[i] = true;
        press(i);
      }
    } else {
      pressed[i] = false;
    }
  }
  
  if (digitalRead(RESET_PIN) == HIGH) {
    resetCounter();
    delay(500);
  }
}
