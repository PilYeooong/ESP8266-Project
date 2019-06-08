#include <Stepper.h>
const int TMP36_pin = A1; //�µ�

const int stepsPerRevolution = 200; //ȸ����  200/�ѹ���
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

boolean window = false;   //false -> �����ִ»���
						  //true -> �����ִ»���

const int gasPin = A0; // ����

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

	if (window == false && value == 1) //â���� �����ְ� �� �ȿ��� ����
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
			// ���۾���
		}
		else if (temperatureC >= ondo1 && analogRead(gasPin) <= gas2)
		{
			sensor_open();
		}
	}

	else if (window == false && value == 0) //â���� �����ְ� �� ���� ����
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
			// ���۾���
		}
		else if (temperatureC >= ondo1 && analogRead(gasPin) <= gas2)
		{
			//���۾���
		}
		else
		{
			//���۾���
		}
	}

	else if (window == true && value == 1) //â���̿����ְ� �� �ȿ��� ���� 
	{
		if (temperatureC <= ondo2 && analogRead(gasPin) >= gas1)
		{
			//���۾���
		}
		else if (temperatureC >= ondo1 && analogRead(gasPin) >= gas1)
		{
			//���۾���
		}
		else if (temperatureC <= ondo2 && analogRead(gasPin) <= gas2)
		{
			sensor_close();
		}
		else if (temperatureC >= ondo1 && analogRead(gasPin) <= gas2)
		{
			//���۾���
		}
	}

	else if (window == true && value == 0) //â���̿����ְ� �� ���� ����
	{
		if (temperatureC <= ondo2 && analogRead(gasPin) >= gas1)
		{
			//���۾���
		}
		else if (temperatureC >= ondo1 && analogRead(gasPin) >= gas1)
		{
			//���۾���
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