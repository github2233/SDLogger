#include <SD.h>
#include <XString.h>
#include <SDLogger.h>
#include <ArduinoBasicIO.h>
#include <Refresh.h>

SDLogger logger;
AnalogInputPin sensor;
Refresh r,t;
String name = "Sensor.txt";
bool logging = false;


// Option Menu
void printMenu(){


	Serial.print(F("Logger, Menu for file : "));
	Serial.println(logger.fileName);
	Serial.println();
	Serial.println(F("Send (s) to start data logging"));
	Serial.println(F("Send (r) to read file data"));
	Serial.println(F("Send (e) to erase file"));
	Serial.println(F("Send (f)name.txt to change file name to name.txt. Example fSensor.txt"));
	Serial.println(F("Send (a)n to change the analog input to An. Example a0.txt to read A0"));
	Serial.println(F("Send (n)n to read line number n in file Example n14 reads full line number 14"));
	Serial.println(F("Send (c)row,column to read a CSV string at row, column. Example c2,1"));
	Serial.println(F("Send (d)row,column to read a CSV float at row, column. Example d2,1"));
	Serial.println(F("Send (t)row,column to read a CSV int at row, column. Example t2,1"));
	Serial.println();


}

void setup(){


	Serial.begin(9600);

	/** Block if no SD detected */
	if(!logger.initSD(4)){
		Serial.print(F("Failed to detect SD\r\nEND"));
		while(1);
	}

	// sets default file name
	logger.setLogFileName(name);
	// inits senosr input on A3
	sensor.initInput(A3);
	// sets sensor sample rate to 100 ms
	r.initRefresh(100);
	printMenu();


}


void loop(){

	// Logging
	if(logging){
		if(r.shouldRefresh()){
			float p[] = {t.getMillis()/1000.0f,sensor.readAnalog()};
			logger.logCSVFloatRow(p,2);}
		if(t.shouldRefresh()){
			Serial.println(F("All Data logged"));
			Serial.println();
			logging = false;
			printMenu();
		}
	}else{

		int c = Serial.read();


		if(c == -1) return;
		// Start logging
		if(c == 's'){
			t.initRefresh(5,Refresh::SECONDS);
			logging = true;
			Serial.println(F("Logging data.."));
		// Read log file over Serial
		}else if(c == 'r'){

			Serial.print(F("File :"));
			Serial.println(logger.fileName);
			Serial.println(F("Content:"));
			logger.print2Stream(&Serial);
			Serial.println(F("End of file content"));
			printMenu();
		// Erase log file
		}else if(c== 'e'){
			Serial.print(F("Erasing file ... "));
			Serial.println(logger.fileName);
			if(logger.removeFile()) Serial.println(F("File couldn't be erased."));
			else Serial.println(F("File erased."));
			printMenu();
		// Change file name
		}else if(c=='f'){

			String s = Serial.readStringUntil('\r');
			if(s.length()>2){
//				s.trim();

				Serial.print(F("Changing file name from "));
				Serial.print(logger.fileName);
				Serial.print(F(" to "));
				Serial.println(s);
				logger.setLogFileName(s);
				Serial.print(F("File name changed to: "));
				Serial.println(logger.fileName);
				Serial.println();


			}else{
				Serial.println(F("Falied reading file"));
			}

			printMenu();



		// Change analog input pin
		}else if(c=='a'){

			sensor.setPinMode(OUTPUT);
			int newPin = Serial.parseInt();
			Serial.print(F("Switching analog input pin to A"));
			Serial.println(newPin);
			Serial.println();
			printMenu();
			sensor.initInput(A0 + newPin);
		// Write 200 lines test
		}else  if(c == 'l'){

			int n = -199;
		    XString s;
		    Serial.println(F("Writting!"));
		    while(n < 200){
		      s = "Linea";
		      appendByte(s,n);
//		      s.formatLong(n,3);
		      s+= ";";
		      appendByte(s,n);
//		      s.formatInt(n,3);
		      s+= ";";
		      logger.logString(s);
		      n++;

		    }
		     Serial.println(F("Written!"));
		     printMenu();
		// Read line
		}else if( c== 'n'){

			 int line = Serial.parseInt();
			 logger.openLogFile();
			 XFile* file = logger.getFile();
			 Serial.print (F("Line "));
			 Serial.println(line);
		     Serial.println(file->readLine(line));
		     logger.close();
		// Read CSV position as String
		}else if( c== 'c'){

			 int row = Serial.parseInt();
			 int column = Serial.parseInt();
			 Serial.print (F("CSV at Row : "));
			 Serial.print(row);
			 Serial.print (F(" Column : "));
			 Serial.println(column);
			 Serial.print(F("Value : "));

			 logger.openLogFile();
			 XFile* file = logger.getFile();
//			 String s = file->readCSVString(row,column);
		     Serial.println(file->readCSVString(row,column));
		     Serial.println();
		     logger.close();

		// Read CSV position as float
		}else if( c== 'd'){

			 int row = Serial.parseInt();
			 int column = Serial.parseInt();
			 Serial.print (F("CSV at Row : "));
			 Serial.print(row);
			 Serial.print (F(" Column : "));
			 Serial.println(column);
			 Serial.print(F("Value : "));


			 logger.openLogFile();
			 XFile* file = logger.getFile();
			 float s = file->readCSVFloat(row,column);

			 Serial.println(s);
			 Serial.println();

			 logger.close();

		 // Read CSV position as int
		}else if( c== 't'){

			 int row = Serial.parseInt();
			 int column = Serial.parseInt();
			 Serial.print (F("CSV at Row : "));
			 Serial.print(row);
			 Serial.print (F(" Column : "));
			 Serial.println(column);
			 Serial.print(F("Value : "));

			 logger.openLogFile();
			 XFile* file = logger.getFile();

			 int s = file->readCSVLong(row,column);

			 Serial.println(s);
			 Serial.println();

			 logger.close();

		}else{
			Serial.println(F("Wrong command"));
			Serial.println();
			printMenu();
		}

	}


}
