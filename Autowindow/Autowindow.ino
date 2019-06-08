#include <Stepper.h>
const int TMP36_pin = A1; //온도

const int stepsPerRevolution = 200; //회전수  200/한바퀴
Stepper myStepper(stepsPerRevolution, 3, 4, 6, 7);
int ENA = 8;
int ENB = 5;
int enablePin = 11;
int in1Pin = 10;
int in2Pin = 9;

int ondo1 = 32;
int ondo2 = 30;
int gas1 = 400;
int gas2 = 200;

boolean window = false;   //false -> 닫혀있는상태
              //true -> 열려있는상태

const int gasPin = A0; // 가스

void setup()
{
  myStepper.setSpeed(60);
  Serial.begin(9600);
  pinMode(enablePin, OUTPUT);
  pinMode(in1Pin, OUTPUT);
  pinMode(in2Pin, OUTPUT);
  pinMode(ENA, OUTPUT); //
  pinMode(ENB, OUTPUT);//
  pinMode(2, INPUT);
  digitalWrite(ENA, HIGH);//
  digitalWrite(ENB, HIGH);//
}

void loop()
{
  int sensorValue = analogRead(TMP36_pin);
  float mVoltage = sensorValue * 5000.0 / 1024.0;
  float temperatureC = (mVoltage - 500) / 10.0;
  int value = digitalRead(2);

  Serial.print("Now : ");
  Serial.print(temperatureC);
  Serial.println(" C");
  Serial.println();
  Serial.print("current gas : ");
  Serial.println(analogRead(gasPin));
  Serial.println();
  Serial.print("Rain : ");
  Serial.println(value);
  Serial.print("Window : ");
  if (window == false) Serial.println("Close");
  else if (window == true) Serial.println("Open");
  Serial.println("=============================================== ");
  Serial.println();

  if (window == false && value == 1) //창문이 닫혀있고 비가 안오는 상태
  {
    if (temperatureC <= ondo2 && analogRead(gasPin) >= gas1)
    {
      sensor_open();
    }
    else if (temperatureC >= ondo1 && analogRead(gasPin) >= gas1)
    {
      sensor_open();
    }
    else if (temperatureC <= ondo2 && analogRead(gasPin) <= gas2)
    {
      // 동작안함
    }
    else if (temperatureC >= ondo1 && analogRead(gasPin) <= gas2)
    {
      sensor_open();
    }
  }

  else if (window == false && value == 0) //창문이 닫혀있고 비가 오는 상태
  {
    if (temperatureC <= ondo2 && analogRead(gasPin) >= gas1)
    {
      sensor_open();
    }
    else if (temperatureC >= ondo1 && analogRead(gasPin) >= gas1)
    {
      sensor_open();
    }
    else if (temperatureC <= ondo2 && analogRead(gasPin) <= gas2)
    {
      // 동작안함
    }
    else if (temperatureC >= ondo1 && analogRead(gasPin) <= gas2)
    {
      //동작안함
    }
    else
    {
      //동작안함
    }
  }

  else if (window == true && value == 1) //창문이열려있고 비가 안오는 상태 
  {
    if (temperatureC <= ondo2 && analogRead(gasPin) >= gas1)
    {
      //동작안함
    }
    else if (temperatureC >= ondo1 && analogRead(gasPin) >= gas1)
    {
      //동작안함
    }
    else if (temperatureC <= ondo2 && analogRead(gasPin) <= gas2)
    {
      sensor_close();
    }
    else if (temperatureC >= ondo1 && analogRead(gasPin) <= gas2)
    {
      //동작안함
    }
  }

  else if (window == true && value == 0) //창문이열려있고 비가 오는 상태
  {
    if (temperatureC <= ondo2 && analogRead(gasPin) >= gas1)
    {
      //동작안함
    }
    else if (temperatureC >= ondo1 && analogRead(gasPin) >= gas1)
    {
      //동작안함
    }
    else if (temperatureC <= ondo2 && analogRead(gasPin) <= gas2)
    {
      sensor_close();
    }
    else if (temperatureC >= ondo1 && analogRead(gasPin) <= gas2)
    {
      sensor_close();
    }
    else
    {
      sensor_close();
    }
  }
  delay(5000);
}
void sensor_open() {
  Serial.println("open");
  myStepper.step(stepsPerRevolution);
  Serial.println("stop");
  window = true;

  Serial.print("Window Status : ");
  Serial.println(window);
  Serial.println();

}

void sensor_close()
{
  Serial.println("Close");
  myStepper.step(-stepsPerRevolution);
  window = false;

  Serial.print("Window Status : ");
  Serial.println(window);
  Serial.println();
}
