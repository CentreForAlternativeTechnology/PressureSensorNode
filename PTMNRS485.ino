#include "PTMNRS485_F.h"

#define RX_PIN 10
#define TX_PIN 9
#define EN_TX_PIN 6

PTMNRS485 sensor(RX_PIN, TX_PIN, EN_TX_PIN);

void setup()
{
	Serial.begin(115200);
}

void loop()
{
	if(!sensor.blockingRead()) {
		Serial.print(F("Sensor read failed\r\n"));
	} else {
		Serial.print(F("sensor read successfully - "));
		Serial.print(sensor.getReading());
		float value = sensor.getReading();
		value = (value - (float)10232)/860;
		Serial.print(F(" - "));
		Serial.print(value);
		Serial.println("m");
	}
	delay(100);
}
