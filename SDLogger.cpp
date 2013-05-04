#include "SDLogger.h"

SDLogger::SDLogger() : intSize(2), floatSize(2){

}
SDLogger::~SDLogger(){free(fileName);}

/** fileName size alloc */
void SDLogger::allocFileName(unsigned int size){
	if(fileName)free(fileName);
	fileName = (char*)malloc(sizeof(char)*size);
}

/** Inits SD library */
bool SDLogger::initSD(uint8_t csPin){return SD.begin(csPin);}

// SETTING

// DIGIT PRECISSION SETTING

/** Sets integer part precission, sign will be part of whole size */
void SDLogger::setIntSize(uint8_t intSize){this->intSize = intSize;}
/** Sets decimal part precisson */
void SDLogger::setFloatSize(uint8_t floatSize){this->floatSize = floatSize;}
/** Sets both integer and decimal part precisson */
void SDLogger::setDigitSizes(uint8_t intSize,uint8_t floatSize){
	setIntSize(intSize);
	setFloatSize(floatSize);

}

/** Sets full name of the log file (path must be included) */
void SDLogger::setLogFileName(char* logFile)
{
	allocFileName(strlen(logFile) + 1);
	strcpy(fileName,logFile);
}
/** Sets full name of the log file (path must be included) */
void SDLogger::setLogFileName(String &logFile)
{
	allocFileName(logFile.length() + 1);
	logFile.toCharArray(fileName,logFile.length()+1);
}

/** Opens logFile to start logging data*/
void SDLogger::openLogFile(char* logFile){file.close();file = SD.open(logFile,FILE_WRITE);}
/** Opens logFile pointing to seekPosition */
void SDLogger::openLogFile(char* logFile,int seekPosition){openLogFile(logFile);file.seek(seekPosition);}
/** Opens file to start logging data */
void SDLogger::openLogFile(){openLogFile(fileName);}
/** Opens inner file pointing to seekPosition */
void SDLogger::openLogFile(int seekPosition){openLogFile(fileName,seekPosition);}

/** Closes log file */
void SDLogger::close(){file.close();}
/** Writes line flushes and closes file */
void SDLogger::endLog(){file.println();file.flushAndClose();}

// LOGGING METHODS

/** Logs @value into file */
void SDLogger::logCSVFloat(float &value){
	openLogFile();
	file.writeCSVFloat(value,intSize,floatSize);
	endLog();
}
/** Logs a full CSV into file */
void SDLogger::logCSVFloatRow(float *values,int nColumns){
	openLogFile();
	file.writeCSVFloat(values,nColumns,intSize,floatSize);
	endLog();
}

/** Logs formated hour HH:MM:SS and value into file */
void SDLogger::logHourValue(float &value){
	openLogFile();
	file.writeHour();file.sc();
	file.writeCSVFloat(value,intSize,floatSize);
	endLog();
}
/** Logs formated date DD:MM:YYYY, hour HH:MM:SS and value into file */
void SDLogger::logDateHourValue(float value){
	openLogFile();
	file.writeDate();file.sc();
	file.writeHour();file.sc();
	file.writeCSVFloat(value,intSize,floatSize);
	endLog();
}
/** Logs a line into log file*/
void SDLogger::SDLogger::logString(String &s){
	openLogFile();
	file.print(s);
	endLog();
}
/** Logs a commented line int log file, every line will begin with # symbol*/
void SDLogger::logComment(String s){logString("#" + s);	}



// FILE METHODS

/** Prints log file throug stream */
void SDLogger::print2Stream(Stream *stream){openLogFile();file.print2Stream(stream/*,true*/);file.close();}

/** Returns a pointer to inner file */
XFile* SDLogger::getFile(){return &file;}

bool SDLogger::removeFile(){

	if(file.operator bool()) file.flushAndClose();
	return SD.remove(fileName);
}

// READING METHODS


/** Reads line lineNumber in log file */
String SDLogger::readLine(int lineNumber){
	openLogFile();
	String s = file.readLine(lineNumber);
	file.close();
	return s;
}
/** Reads CSV String at given row,column position */
String SDLogger::readCSVString(int row, int column){
	openLogFile();
	String s = file.readCSVString(row,column);
	file.close();
	return s;
}
/** Reads CSV integer at position TODO maybe useless */
long SDLogger::readCSVLong(int row, int column){
	openLogFile();
	long l = file.readCSVLong(row,column);
	file.close();
	return l;
}
/** Reads CSV float at position */
float SDLogger::readCSVFloat(int row, int column){
	openLogFile();
	float f = file.readCSVFloat(row,column);
	file.close();
	return f;
}
/** Reads CSV e format real at position */
float SDLogger::readCSVEFloat(int row, int column){
	openLogFile();
	float f  = file.readCSVEFloat(row,column);
	file.close();
	return f;
}








