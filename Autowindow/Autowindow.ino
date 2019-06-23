#include <Servo.h>
#include <DHT11.h>

DHT11 dht11(D3);
Servo servo;

//서보모터 - 주황 D4 , 빨강 3v3 , 갈색 gnd

int ondo = 25; // 온도
int ondo2 = 15; //최저온도
int ondo3 = 29;

int dustPin = A0; // 먼지
int dustLED = 2;
float dust_value = 0;
float Voltage = 0;
float Dust = 0;

boolean window = false;   //false -> 닫혀있는상태
                          //true -> 열려있는상태

void setup()
{
  Serial.begin(9600);
  servo.attach(2); //D2
  servo.write(0);
  pinMode(dustLED,OUTPUT);
  pinMode(dustPin,INPUT);
}

void loop()
{
  
  float temp,humi;
  int result = dht11.read(humi,temp);
  Voltage = dust_value *5.0 /1024.0; 
  Dust = (Voltage - 0.3)/0.005; //사용 전압을 기준으로 미세먼지 값을 변환
  
  Serial.print("Temperature : ");
  Serial.print(temp);
  Serial.println(" C");
  Serial.println();
  Serial.print("Dust : ");
  Serial.println(Dust);
  Serial.println();
  Serial.print("Humidity : ");
  Serial.println(humi);
  
  Serial.print("Window : ");
  if (window == false) Serial.println("Close");
  else if (window == true) Serial.println("Open");
  
  Serial.println("=============================================== ");
  Serial.println();

  if (window == false && humi < 45) //창문이 닫혀있고 비 안옴  
  {
    if (temp >= ondo && Dust <55 ) 
    {
      sensor_open();
    }
  }
  
  else if(window == false && humi > 60) // 창문이 닫혀있고 비가 올때
  {
 
    if (temp >= ondo3) //29도 이상으로 올라가면 창문 개방
    {
      sensor_open();
    }
  }

  else if (window == true && humi < 45) //창문이열려있고 비가 안오는 상태 
  {
    if (temp < ondo2 || Dust > 60) // 15도 이하로 떨어지면 창문 닫음
    {
      sensor_close();
    }
    else if (temp >= ondo )
    {
      //동작안함
    }
  }

  else if (window == true && humi > 60) //창문이열려있고 비가 오는 상태
  {
      sensor_close(); 
  }
  delay(5000);
}

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
