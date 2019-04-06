#include <Arduino.h>
#include <hcsr04.h>

const int led = 16;
const int eSensor = 15;
const int dSensor = 13;
const int trigPin = 25;
const int echoPin = 26;
int acabou = 0;
const int distancia1 = 250;
const int distancia2 = 100;
const int stepPinD = 12;
const int dirPinD = 14;
const int stepPinE = 0;
const int dirPinE = 2;
const int InfraBaixa = 500;
const int InfraAlta = 1500;

int SensorDireito, SensorEsquerdo;

HCSR04 hcsr04(trigPin, echoPin, 20, 4000);

void setup()
{

  pinMode(led, OUTPUT);
  Serial.begin(9600);

  pinMode(stepPinD, OUTPUT);
  pinMode(stepPinE, OUTPUT);
  pinMode(dirPinD, OUTPUT);
  pinMode(dirPinE, OUTPUT);
}

void loop()
{
  SensorDireito = analogRead(dSensor);
  SensorEsquerdo = analogRead(eSensor);

  //Loop para fazer o quadrado
  /*
  while (acabou != 4)
  {
    digitalWrite(dirPinD, HIGH);
    digitalWrite(dirPinE, LOW);

    for (int i = 0; i < 1600; i++)
    {
      digitalWrite(stepPinD, HIGH);
      digitalWrite(stepPinE, HIGH);
      delayMicroseconds(500);
      digitalWrite(stepPinD, LOW);
      digitalWrite(stepPinE, LOW);
      delayMicroseconds(500);
    }
    digitalWrite(dirPinD, LOW);
    digitalWrite(dirPinE, LOW);
    for (int j = 0; j < 800; j++)
    {
      digitalWrite(stepPinD, HIGH);
      digitalWrite(stepPinE, HIGH);
      delayMicroseconds(500);
      digitalWrite(stepPinD, LOW);
      digitalWrite(stepPinE, LOW);
      delayMicroseconds(500);
    }
    acabou = acabou + 1;
  }*/

  if (distancia2 < hcsr04.distanceInMillimeters() && hcsr04.distanceInMillimeters() <= distancia1)
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

  if ( SensorDireito >= InfraAlta)
  {
    digitalWrite(dirPinD, LOW);
    digitalWrite(dirPinE, LOW);

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

  if (SensorEsquerdo >= InfraAlta)
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
}