#include <Arduino.h>
#include <hcsr04.h>
#include <Wire.h>

#define TRIG_PIN 25
#define ECHO_PIN 26

const int led = 16;
const int eSensor = 15;
const int dSensor = 13;
const int trigPin = 25;
const int echoPin = 26;
const int distancia1 = 450;
const int distancia2 = 250;
const int distancia3 = 40;
const int distancia4 = 200;
const int stepPinD = 12;
const int dirPinD = 14;
const int stepPinE = 0;
const int dirPinE = 2;
const int setPoint = 50;
const int KP = 1;
int manipulacao2;
int entrada;
int  erroCalc;
int retonar;

void Andar(int retonar);
void Volta(int retornar);
int Erro();

void Girar180();
void GirarD();
void GirarE();

int SensorDireito, SensorEsquerdo;

HCSR04 hcsr04(trigPin, echoPin, 20, 4000);


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

    // if (distancia3 < hcsr04.distanceInMillimeters() && hcsr04.distanceInMillimeters() <= distancia4 && SensorEsquerdo < 1500 && SensorDireito < 1500)
    // {
    //   Volta();
    // }
    
    // if (distancia2 < hcsr04.distanceInMillimeters() && hcsr04.distanceInMillimeters() <= distancia1 && SensorEsquerdo < 1500 && SensorDireito < 1500)
    // {
    //   Andar();
    // }

    retonar = Erro();
        
    retonar = retonar * KP;

    Serial.print("Retornar: ");
    Serial.println(retonar);

    if (retonar > 5)
    {
      if(retonar > 1600)
      {
        retonar = 1600;
      }
      Andar(retonar);
    }
    
    if (retonar <= -5) 
    {  
      if(retonar > 1600)
      {
        retonar = 1600;
      }
      Volta(retonar);
    }
    
    if(SensorDireito >= 1500)
    {
      GirarE();
    }
    if(SensorEsquerdo >= 1500)
    {
      GirarD();
    }
}

//---------------------------------------Funções------------------------------------------------

int Erro()
{
  erroCalc = hcsr04.distanceInMillimeters() - setPoint;  

  return erroCalc;
}

void Volta(int manipulacao)
{
    digitalWrite(dirPinD, LOW);
    digitalWrite(dirPinE, HIGH);

    manipulacao = manipulacao * - 1;

    Serial.print("Manipulacao: ");
    Serial.println(manipulacao);

    for (int j = 0; j < manipulacao; j++)
    {
        digitalWrite(stepPinD, HIGH);
        digitalWrite(stepPinE, HIGH);
        delayMicroseconds(500);
        digitalWrite(stepPinD, LOW);
        digitalWrite(stepPinE, LOW);
        delayMicroseconds(500);
        
    }
}

void Andar(int manipulacao)
{
    digitalWrite(dirPinD, HIGH);
    digitalWrite(dirPinE, LOW);

    for (int j = 0; j < manipulacao; j++)
    {
        digitalWrite(stepPinD, HIGH);
        digitalWrite(stepPinE, HIGH);
        delayMicroseconds(500);
        digitalWrite(stepPinD, LOW);
        digitalWrite(stepPinE, LOW);
        delayMicroseconds(500);        
    }
}

void GirarE()
{
    digitalWrite(dirPinD, HIGH);
    digitalWrite(dirPinE, HIGH);

    for (int j = 0; j < 100; j++)
    {
        digitalWrite(stepPinD, HIGH);
        digitalWrite(stepPinE, HIGH);
        delayMicroseconds(500);
        digitalWrite(stepPinD, LOW);
        digitalWrite(stepPinE, LOW);
        delayMicroseconds(500);
    }
}

void GirarD()
{
    digitalWrite(dirPinD, LOW);
    digitalWrite(dirPinE, LOW);

    for (int j = 0; j < 100; j++)
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