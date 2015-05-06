#include "PTMNRS485_F.h"
#include <Wire.h>
#define EN_TX_PIN 7
#define RX_PIN 10
#define TX_PIN 9

PTMNRS485 *sensor;

void setup()
{
	Serial.begin(115200);
	Serial.println("Sensor board online...");
	sensor = new PTMNRS485(RX_PIN, TX_PIN, EN_TX_PIN);
	Wire.begin(4);
	Wire.onRequest(requestEvent);
	
}

void requestEvent() {
	Wire.write(((uint8_t *)(sensor->getReadingPtr())), 2);
	char buffer[60];
	sprintf(buffer, "Sent 0x%x, 0x%x\r\n", ((uint8_t *)(sensor->getReadingPtr()))[0], ((uint8_t *)(sensor->getReadingPtr()))[1]);
	Serial.print(buffer);
}

void loop()
{
	if(sensor->blockingRead()) {
		Serial.println(sensor->getReading());
	} else {
		Serial.println("Sensor read failed");
	}
}
