#include <Arduino.h>
#include <hcsr04.h>

const int led = 16;
const int eSensor = 15;
const int dSensor = 13;
const int trigPin = 25;
const int echoPin = 26;
int acabou = 0;
const int distancia1 = 100;
const int distancia2 = 50;
const int stepPinD = 12;
const int dirPinD = 14;
const int stepPinE = 0;
const int dirPinE = 2;
const int InfraBaixa = 500;
const int InfraAlta = 1500;

void square();

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
  delay(2000);
}

void loop()
{
  SensorDireito = analogRead(dSensor);
  SensorEsquerdo = analogRead(eSensor);

  square();
}

void square()
{
  /*------------------------------------Andar para frente--------------------------------------------------------*/
  digitalWrite(dirPinD, HIGH);
  digitalWrite(dirPinE, LOW);
  for (int i = 0; i < 6400; i++)
  {
    if (distancia2 < hcsr04.distanceInMillimeters() && hcsr04.distanceInMillimeters() <= distancia1)
    {
      digitalWrite(dirPinD, HIGH);
      digitalWrite(dirPinE, HIGH);
      for (int i = 0; i < 1600; i++)
      {
        digitalWrite(stepPinD, HIGH);
        digitalWrite(stepPinE, HIGH);
        delayMicroseconds(500);
        digitalWrite(stepPinD, LOW);
        digitalWrite(stepPinE, LOW);
        delayMicroseconds(500);
      }
      square();
    }
    digitalWrite(stepPinD, HIGH);
    digitalWrite(stepPinE, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPinD, LOW);
    digitalWrite(stepPinE, LOW);
    delayMicroseconds(500);
  }
  /*------------------Virar o robo-----------------------------------------------------------------------------*/
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
}