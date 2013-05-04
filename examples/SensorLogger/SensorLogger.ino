#include <SD.h>
#include <XString.h>
#include <SDLogger.h>

#define SD_PIN 4
#define SAMPLE_RATE 5000
// sd data logger
SDLogger logger;
// sensor input
int sensorPin = A0;
// log sample rate
unsigned long lastLog;

// put your sensor reading here
float readSensor(){

	float value = analogRead(sensorPin);
	return value;
}

void setup(){

	Serial.begin(9600);

	// init SD library at desired pin
	logger.initSD(SD_PIN);
	// set log file name
	logger.setLogFileName("Sensor.txt");
	// init analog input
	pinMode(sensorPin,INPUT);

}


void loop(){

	// logs value; into file
	if(millis() - lastLog >= SAMPLE_RATE){

		float value = readSensor();
		lastLog = millis();
		Serial.println("Logging data.");
		 //  logs a new CSV line in file with sensor value
		logger.logCSVFloat(value);
		Serial.println("Data logged.");
	}





}
