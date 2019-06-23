
#include <Servo.h>
#include <DHT11.h>

DHT11 dht11(D3);
Servo servo;

//서보모터 - 주황 D4 , 빨강 3v3 , 갈색 gnd
int ondo = 20; // 온도
int ondo2 = 15; //최저온도
int ondo3 = 29;
int dust = 400; //먼지

boolean window = false;   //false -> 닫혀있는상태
                          //true -> 열려있는상태

const int dustPin = A0; // 먼지


void sensor_open() {
  Serial.println("open");
  for(int angle = 0; angle < 180; angle++) 
  { 
    servo.write(angle); 
    delay(15); 
  } 
  Serial.println("stop");
  window = true;

  Serial.print("Window Status : ");
  Serial.println(window);
  Serial.println();

}

void sensor_close()
{
  Serial.println("Close");
  for(int angle = 180; angle > 0; angle--) 
  { 
    servo.write(angle); 
    delay(15); 
  window = false;

  Serial.print("Window Status : ");
  Serial.println(window);
  Serial.println();
  }
}

void setup()
{
  Serial.begin(9600);
  servo.attach(2); //D2
  servo.write(0);
}

void loop()
{
  
  float temp,humi;
  int result = dht11.read(humi,temp);

  Serial.print("Temperature : ");
  Serial.print(temp);
  Serial.println(" C");
  Serial.println();
  // Serial.print("current dust : ");
  // Serial.println(analogRead(dustPin));
  Serial.println();
  Serial.print("Humidity : ");
  Serial.println(humi);
  
  Serial.print("Window : ");
  if (window == false) Serial.println("Close");
  else if (window == true) Serial.println("Open");
  
  Serial.println("=============================================== ");
  Serial.println();

  if (window == false && humi < 50) //창문이 닫혀있고 비 안옴  
  {
    if (temp >= ondo)
    {
      sensor_open();
    }
    else if (temp <= ondo)
    {
      // 동작안함
    }
  }
  else if(window == false && humi > 50) 
  {
    if (temp <= ondo)
    {
      // 동작안함
    }
    else if (temp >= ondo3)
    {
      sensor_open();
    }
    else if (analogRead(dustPin) >= dust) // 집안 공기가 좋지않을 때
    {
      sensor_open();
    }
  }

  else if (window == true && humi < 35) //창문이열려있고 비가 안오는 상태 
  {
    if (temp < ondo2)
    {
      sensor_close();
    }
    else if (temp >= ondo || analogRead(dustPin) >= dust)
    {
      //동작안함
    }
  }

  else if (window == true && humi > 50) //창문이열려있고 비가 오는 상태
  {
   if (temp > ondo3 || analogRead(dustPin) >= dust){
      // 동작안함
    }
    else{
      sensor_close();
    }
  }
  delay(5000);
}
