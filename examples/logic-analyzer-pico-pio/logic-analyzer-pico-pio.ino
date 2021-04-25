/**
 * @file logic_analyzer-pico.ino
 * @author Phil Schatzmann
 * @copyright GPLv3
 * @brief Arduino Sketch for the sigrok LogicAnalyzer for the Rasperry Pico using the SUMP protocol
 * See https://sigrok.org/wiki/Openbench_Logic_Sniffer#Short_Commands * 
 */

#include "Arduino.h"
#include "capture_raspberry_pico.h"
#include "SoftwareSerial.h"
using namespace logic_analyzer;  

int pinStart=START_PIN;
int numberOfPins=PIN_COUNT;
LogicAnalyzer logicAnalyzer;
PicoCapturePIO capture;

// Use Event handler to cancel capturing
void onEvent(Event event) {
    if (event == STATUS) {
        switch (logicAnalyzer.status()) {
            case ARMED:
                digitalWrite(LED_BUILTIN, LOW);
                break;
            case STOPPED:
                capture.cancel();
                digitalWrite(LED_BUILTIN, LOW);
                break;
        }
    }
}

void setup() {
    Serial2.begin(115200);
    logicAnalyzer.setLogger(Serial2);
    //Logger.begin(Serial2,PicoLogger::Debug);

    Serial.begin(SERIAL_SPEED);  
    Serial.setTimeout(SERIAL_TIMEOUT);
            pinMode(LED_BUILTIN, OUTPUT);

    capture.activateTestSignal(pinStart, 90.0);
    logicAnalyzer.setDescription("Raspberry-Pico-PIO");
    logicAnalyzer.setEventHandler(&onEvent);

    logicAnalyzer.begin(Serial, &capture, MAX_CAPTURE_SIZE, pinStart, numberOfPins);
}

void loop() {
    if (Serial) logicAnalyzer.processCommand();
}
