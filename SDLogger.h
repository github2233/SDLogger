/* SDLogger.h
 * Created on: 07/03/2013
 *      Author: J.M Tome
 * Copyright (c) 20012-2013 J.M Tome
 * Contact : josemiguel.tomejimenez@gmail.com
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General
 * Public License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place, Suite 330,
 * Boston, MA  02111-1307  USA
 */

#ifndef SDLOGGER_H_
#define SDLOGGER_H_

#include "../SD/SD.h"
#include "XFile.h"

class SDLogger{

protected :

	/** fileName size alloc */
	void allocFileName(unsigned int size);

public :

	/** SD xtra File */
	XFile file;

	/** File name */
	char* fileName;
	/** Precisson sizes.
	 * 	Includes sign which will only be shown in negative number, eg: 003.01,-03.01
	 */
	uint8_t intSize;
	uint8_t floatSize;

	SDLogger();
	virtual ~SDLogger();

	/** Inits SD library */
	bool initSD(uint8_t csPin);

	// SETTING

	//	- DIGIT PRECISSION SETTING

	/** Sets integer part precission, sign will be part of whole size */
	void setIntSize(uint8_t intSize);
	/** Sets decimal part precisson */
	void setFloatSize(uint8_t floatSize);
	/** Sets both integer and decimal part precisson */
	void setDigitSizes(uint8_t intSize,uint8_t floatSize);

	//	- FILE NAME SETTING

	/** Sets full name of the log file (path must be included) */
	void setLogFileName(char* logFile);
	/** Sets full name of the log file (path must be included) */
	void setLogFileName(String &logFile);

	//	FILE OPENING/CLOSING

	/** Opens logFile to start logging data*/
	void openLogFile(char* logFile);
	/** Opens logFile pointing to seekPosition */
	void openLogFile(char* logFile,int seekPosition);
	/** Opens file to start logging data */
	void openLogFile();
	/** Opens inner file pointing to seekPosition */
	void openLogFile(int seekPosition);
	/** Closes log file */
	void close();
	/** Writes line, flushes and closes file */
	void endLog();

	// LOGGING METHODS

	/** Logs value into file */
	void logCSVFloat(float &value);
	/** Logs a full CSV into file */
	void logCSVFloatRow(float *values,int nColumns);
	/** Logs formated hour HH:MM:SS and value into file */
	void logHourValue(float &value);
	/** Logs formated date DD:MM:YYYY, hour HH:MM:SS and value into file */
	void logDateHourValue(float value);
	/** Logs a line into log file*/
	void logString(String &s);
	/** Logs a commented line int log file, every line will begin with # symbol*/
	void logComment(String s);


	// READING METHODS

	/** Reads line lineNumber in log file */
	String readLine(int lineNumber);
	/** Reads CSV String at given row,column position */
	String readCSVString(int row, int column);
	/** Reads CSV integer at position TODO maybe useless */
	long readCSVLong(int row, int column);
	/** Reads CSV float at position */
	float readCSVFloat(int row, int column);
	/** Reads CSV e format real at position */
	float readCSVEFloat(int row, int column);

	// FILE METHODS

	/** Prints log file throug stream */
	void print2Stream(Stream *stream);
	/** Removes log file from SD card */
	bool removeFile();
	/** Returns a pointer to inner file */
	XFile* getFile();


};

//class SDLogger : public XFile{
//
//protected :
//
//	/** fileName size alloc */
//	void allocFileName(unsigned int size);
//
//
//
//
//public :
//
//
//
//	/** File name */
//	char* fileName;
//	/** Precisson sizes */
//	// includes sign which will only be shown in negative numbers
//	uint8_t intSize;
//	uint8_t floatSize;
//
//	SDLogger();
//	virtual ~SDLogger();
//
//	/** Inits SD library */
//	bool initSD(uint8_t csPin);
//
//	// SETTING
//
//	//	- DIGIT PRECISSION SETTING
//
//	/** Sets integer part precission, sign will be part of whole size */
//	void setIntSize(uint8_t intSize);
//	/** Sets decimal part precisson */
//	void setFloatSize(uint8_t floatSize);
//	/** Sets both integer and decimal part precisson */
//	void setDigitSizes(uint8_t intSize,uint8_t floatSize);
//
//	//	- FILE NAME SETTING
//
//	/** Sets full name of the log file (path must be included) */
//	void setLogFileName(char* logFile);
//	/** Sets full name of the log file (path must be included) */
//	void setLogFileName(String &logFile);
//
//	/** Opens logFile to start logging data*/
//	void openLogFile(char* logFile);
//	/** Opens logFile pointing to seekPosition */
//	void openLogFile(char* logFile,int seekPosition);
//	/** Opens file to start logging data */
//	void openLogFile();
//	/** Opens inner file pointing to seekPosition */
//	void openLogFile(int seekPosition);
//
//	/** Closes log file */
//	void close();
//	/** Writes line, flushes and closes file */
//	void endLog();
//
//	/** Logs value into file */
//	void logCSVFloat(float &value);
//	/** Logs a full CSV into file */
//	void logCSVFloatRow(float *values,int nColumns);
//
//	/** Logs formated hour HH:MM:SS and value into file */
//	void logHourValue(float &value);
//	/** Logs formated date DD:MM:YYYY, hour HH:MM:SS and value into file */
//	void logDateHourValue(float value);
//	/** Logs a line into log file*/
//	void logString(String &s);
//	/** Logs a commented line int log file, every line will begin with # symbol*/
//	void logComment(String s);
//
//	// LOG METHODS
//
//	// READING METHODS
//
//
//	/** Reads line lineNumber in log file */
//	String readLine(unsigned int lineNumber);
//	/** Reads CSV String at given row,column position */
//	String readCSVString(unsigned int row, unsigned int column);
//	/** Reads CSV integer at position TODO maybe useless */
//	long readCSVInt(unsigned int row, unsigned int column);
//	/** Reads CSV float at position */
//	float readCSVFloat(unsigned int row, unsigned int column);
//	/** Reads CSV e format real at position */
//	float readCSVEFloat(unsigned int row, unsigned int column);
//
//
//	/** Prints log file throug stream */
//	void print2Stream(Stream *stream);
//	/** Removes log file from SD card */
//	bool removeFile();
//	/** Returns a pointer to inner file */
//	XFile* getFile();
//
//};


//	/** Logs @value into file */
//	void logFloatValue(char* logFile,float &value){
//		openLogFile(logFile);
//		file.writeCSVFloat(value,intSize,floatSize);
//		endLog();
//	}
//	/** Logs a full CSV into file */
//	void logCSVFloatRow(char* logFile,float *values,int nColumns){
//		openLogFile(logFile);
//		file.writeCSVFloat(values,nColumns,intSize,floatSize);
//		endLog();
//	}
//	/** Logs formated hour HH:MM:SS and value into file */
//	void logHourValue(char* logFile,float &value){
//		openLogFile(logFile);
//		file.writeHour();file.sc();
//		file.writeCSVFloat(value,intSize,floatSize);
//		endLog();
//	}
//	/** Logs formated date DD:MM:YYYY, hour HH:MM:SS and value into file */
//	void logDateHourValue(char* logFile,float &value){
//		openLogFile(logFile);
//		file.writeDate();file.sc();
//		file.writeHour();file.sc();
//		file.writeCSVFloat(value,intSize,floatSize);
//		endLog();
//	}
//	/** Logs a line into log file*/
//	void logString(char* logFile,String &s){
//		openLogFile(logFile);
//		file.print(s);
//		endLog();
//	}
//	/** Logs a commented line int log file, every line will begin with # symbol*/
//	void logComment(char* logFile,String s){logString(logFile,"#" + s);	}


	// LOG METHODS WHEN FILE IS SET

//	/** Logs value into file */
//	void logFloatValue(float &value){logFloatValue(fileName,value);}
//	/** Logs value into file */
//	void logFloatCSVRow(float *values,int nColumns){logCSVFloatRow(fileName,values,nColumns);}
//	/** Logs formated hour HH:MM:SS and value into file */
//	void logHourValue(float &value){logHourValue(fileName,value);}
//	/** Logs formated date DD:MM:YYYY, hour HH:MM:SS and value into file */
//	void logDateHourValue(float &value){logDateHourValue(fileName,value);}
//	/** Logs a commented line int log file, every line will begin with # symbol*/
//	void logString(String s){logString(fileName,s);}
//	/** Logs a commented line int log file, every line will begin with # symbol*/
//	void logComment(String s){logComment(fileName,s);}

#endif /* SDLOGGER_H_ */
