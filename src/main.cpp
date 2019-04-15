#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-err58-cpp"
//
// Created by Misha on 4/13/2019.
//


#include <Arduino.h>
#include <AccelStepper.h>
#include <Servo.h>

AccelStepper horizontal(8, 9, 11, 10, 12);
AccelStepper planar(8, A0, A2, A1, A3);
Servo vertical;
int cue_pin = 5;

void setup() {
    Serial.begin(9600);

    vertical.attach(4);
    vertical.write(0);

    horizontal.setMaxSpeed(1000.0);
    horizontal.setAcceleration(150.0);

    planar.setMaxSpeed(1000.0);
    planar.setAcceleration(150.0);

    pinMode(cue_pin, OUTPUT);
    digitalWrite(cue_pin, LOW);
}

void loop() {
    if (Serial.available() > 0) {
        char type = Serial.read();

        switch (type) {
            case 'H':
                horizontal.move((long) (4076.0 * Serial.parseFloat() / 20.0 / 2.0 * 25.4));
                horizontal.runToPosition();
                break;
            case 'V':
                vertical.write(vertical.read() - Serial.parseInt());
                delay(200);
                break;
            case 'R':
                planar.move((long) ((float) Serial.parseInt() * (4076.0 / 360)));
                planar.runToPosition();
                break;
            case 'Q':
                digitalWrite(cue_pin, HIGH);
                delay(200);
                digitalWrite(cue_pin, LOW);
                break;
            default:
                break;
        }

        Serial.println("Done!");
    }
}

#pragma clang diagnostic pop