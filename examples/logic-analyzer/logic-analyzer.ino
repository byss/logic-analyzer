/**
 * @file logic_analyzer.ino
 * @author Phil Schatzmann
 * @copyright GPLv3
 * @brief Arduino Sketch for the sigrok LogicAnalyzer for the ESP32 and AVR processors using the SUMP protocol
 * See https://sigrok.org/wiki/Openbench_Logic_Sniffer#Short_Commands * 
 */

#include "Arduino.h"
#include "logic_analyzer.h"

using namespace logic_analyzer;  

LogicAnalyzer<PinBitArray> logicAnalyzer;
int pinStart=4;
int numberOfPins=8;

void setup() {
    setupLogger(); // as defined in processor specific config
    Serial.begin(SERIAL_SPEED);  
    Serial.setTimeout(SERIAL_TIMEOUT);
    logicAnalyzer.begin(Serial, new PinReader(pinStart), MAX_FREQ, MAX_CAPTURE_SIZE, pinStart, numberOfPins);
}

void loop() {
    logicAnalyzer.processCommand();
}
