#include <Arduino.h>
#include <hcsr04.h>
#include <MPU6050_tockn.h>
#include <wire.h>

#define TRIG_PIN 25
#define ECHO_PIN 26

const int led = 16;
const int eSensor = 15;
const int dSensor = 13;
const int trigPin = 25;
const int echoPin = 26;
int acabou = 0;
const int distancia1 = 90;
const int distancia2 = 30;
const int stepPinD = 12;
const int dirPinD = 14;
const int stepPinE = 0;
const int dirPinE = 2;
const int InfraBaixa = 500;
const int InfraAlta = 1500;

void Andar();
void Girar90();
void Girar180();

int SensorDireito, SensorEsquerdo;

HCSR04 hcsr04(trigPin, echoPin, 20, 4000);
MPU6050 mpu(Wire);

void setup()
{
    Wire.begin(5, 4);    
    Serial.begin(9600);

    pinMode(led, OUTPUT);
    pinMode(stepPinD, OUTPUT);
    pinMode(stepPinE, OUTPUT);
    pinMode(dirPinD, OUTPUT);
    pinMode(dirPinE, OUTPUT);
}

void loop()
{
    SensorDireito = analogRead(dSensor);
    SensorEsquerdo = analogRead(eSensor);

    if (distancia2 < hcsr04.distanceInMillimeters() && hcsr04.distanceInMillimeters() <= distancia1)
    {
        Andar();

        if(10 < hcsr04.distanceInMillimeters()&& hcsr04.distanceInMillimeters() <= 20)
        {
            delay(1000);
            Andar();
        }
    }
    if(SensorDireito == 300)
    {
        Girar180();
    }
        if(SensorEsquerdo == 300)
    {
        Girar180();
    }
}
/*-----------------------------------------------------------------------função------------------------------------------------------------------------------------------------*/
void Andar()
{
    digitalWrite(dirPinD, HIGH);
    digitalWrite(dirPinE, LOW);

    for (int j = 0; j < 1600; j++)
    {
        digitalWrite(stepPinD, HIGH);
        digitalWrite(stepPinE, HIGH);
        delayMicroseconds(500);
        digitalWrite(stepPinD, LOW);
        digitalWrite(stepPinE, LOW);
        delayMicroseconds(500);
    }
}

void Girar90()
{
    digitalWrite(dirPinD, HIGH);
    digitalWrite(dirPinE, HIGH);

    for (int j = 0; j < 900; j++)
    {
        digitalWrite(stepPinD, HIGH);
        digitalWrite(stepPinE, HIGH);
        delayMicroseconds(500);
        digitalWrite(stepPinD, LOW);
        digitalWrite(stepPinE, LOW);
        delayMicroseconds(500);
    }
}

void Girar180()
{
    digitalWrite(dirPinD, HIGH);
    digitalWrite(dirPinE, HIGH);

    for (int j = 0; j < 1600; j++)
    {
        digitalWrite(stepPinD, HIGH);
        digitalWrite(stepPinE, HIGH);
        delayMicroseconds(500);
        digitalWrite(stepPinD, LOW);
        digitalWrite(stepPinE, LOW);
        delayMicroseconds(500);
    }
}