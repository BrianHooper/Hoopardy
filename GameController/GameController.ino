#include <stdio.h>
#include <string.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define NUMPINS 4

int RESET_PIN = 13;

int pins[] = {9, 10, 11, 12};
unsigned long lastPressed[] = {0, 0, 0, 0};
char *words[NUMPINS];

boolean isCurrentlyPressed = false;

unsigned int globalDelayTimeMs = 60 * 1000;
unsigned long globalTime = 0;

LiquidCrystal_I2C lcd(0x27, 16, 2);

void resetCounter()
{
    for (unsigned short i = 0; i < NUMPINS; i++)
    {
        lastPressed[i] = 0;
    }
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("##### HOOPARDY #####");
    lcd.setCursor(0, 2);
    lcd.print("   A:  B:  C:  D:   ");
    isCurrentlyPressed = false;
}


void setup()
{
    Wire.begin();
    Serial.begin(9600);

    for (unsigned short i = 0; i < NUMPINS; i++)
    {
        pinMode(pins[i], INPUT);
    }
    pinMode(RESET_PIN, INPUT);

    lcd.init();
    lcd.backlight();
    resetCounter();
}

char *intToString(int num)
{
    int length = snprintf(NULL, 0, "%d", num);
    char *str = (char *)malloc(length + 1);
    snprintf(str, length + 1, "%d", num);
    return str;
}

char *joinStrings(char *strings[])
{
    int totalLength = 0;
    for (int i = 0; i < NUMPINS; ++i)
    {
        totalLength += strlen(strings[i]);
    }
    totalLength += NUMPINS - 1; // Account for the commas

    char *result = (char *)malloc(totalLength + 1);
    strcpy(result, strings[0]);

    for (int i = 1; i < NUMPINS; ++i)
    {
        strcat(result, ",");
        strcat(result, strings[i]);
    }

    return result;
}

char *calcRank(int pinIdx)
{
    char *posPinA = "-";
    if (lastPressed[pinIdx] > 0)
    {
        int counter = 1;
        for (unsigned short i = 0; i < NUMPINS; i++)
        {
            if (i == pinIdx)
            {
                continue;
            }
            if (lastPressed[i] != 0 && lastPressed[i] < lastPressed[pinIdx])
            {
                counter++;
            }
        }
        posPinA = intToString(counter);
    }
    return posPinA;
}

void updateDisplay()
{
    for (unsigned short i = 0; i < NUMPINS; i++)
    {
        //words[i] = calcRank(i);
        lcd.setCursor(i * 2, 2);
        lcd.print(String(calcRank(i)));
    }

    char *joinedString = joinStrings(words);
    //lcd.setCursor(0, 2);
    //lcd.print(joinedString);
}


void press(int pinIdx)
{
    if (lastPressed[pinIdx] > 0)
    {
        return;
    }

    unsigned long currentTime = millis();
    if (!isCurrentlyPressed)
    {
        globalTime = currentTime;
    }
    isCurrentlyPressed = true;
    lastPressed[pinIdx] = currentTime;

    lcd.setCursor((pinIdx + 1) * 4 + 1, 2);
    lcd.print(String(calcRank(pinIdx)));

    //updateDisplay();
}

void scanI2C()
{
    byte error, address;
    int nDevices;

    Serial.println("Scanning...");

    nDevices = 0;
    for (address = 1; address < 127; address++)
    {
        // The i2c_scanner uses the return value of
        // the Write.endTransmisstion to see if
        // a device did acknowledge to the address.
        Wire.beginTransmission(address);
        error = Wire.endTransmission();

        if (error == 0)
        {
            Serial.print("I2C device found at address 0x");
            if (address < 16)
                Serial.print("0");
            Serial.print(address, HEX);
            Serial.println("  !");

            nDevices++;
        }
        else if (error == 4)
        {
            Serial.print("Unknown error at address 0x");
            if (address < 16)
                Serial.print("0");
            Serial.println(address, HEX);
        }
    }
    if (nDevices == 0)
        Serial.println("No I2C devices found\n");
    else
        Serial.println("done\n");

    delay(5000); // wait 5 seconds for next scan
}

void loop()
{
    unsigned long currentTime = millis();
    if (isCurrentlyPressed && currentTime - globalTime >= globalDelayTimeMs)
    {
        resetCounter();
    }

    for (unsigned short i = 0; i < NUMPINS; i++)
    {
        if (digitalRead(pins[i]) == HIGH)
        {
            press(i);
        }
    }

    if (digitalRead(RESET_PIN) == HIGH)
    {
        resetCounter();
        delay(500);
    }

    // scanI2C();
}
