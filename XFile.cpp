#include "XFile.h"

XFile::XFile() : File(){setTimeout(20);}
XFile::~XFile(){}

/** jumps line */
bool XFile::jumpln(){
	int c = 0;
	while((c != -1) && (c!= '\n')) {c = read();}
	return (c != -1 );
}
/** jumps CSV */
bool XFile::jumpCSV(){
	int c = 0;
	while((c != -1) && (c!= ';')) {c = read();}
	return (c != -1 );
}

/** Makes file point to line */
bool XFile::goToLine(int line){
	unsigned long n = -1;
	seek(0);
	while((++n<line) && jumpln());
	return (n==line);
}


/** Reads CSV String at given row,column position */
bool XFile::goToCSV(int row, int column){
	if(!goToLine(row)) return false;
	int c = 0;
	while ((c < column) && jumpCSV()){c++;}
	return (c == column);

}

/** Gets file's number of lines @return Number of lines in the file*/
int XFile::getLines(){
	seek(0);
	int lines = 0;
	while(jumpln()) lines++;
	return lines;
}

// READING METHODS

/** Reads next line in this file. @return Next line*/
String XFile::readLine(){
	String s = readStringUntil('\n');
	if(s.endsWith("\r")){s = s.substring(0,s.length()-1);}
	return s;
}
/** Reads lineNumber line in this file @return lineNumber line*/
String XFile::readLine(int lineNumber){
	goToLine(lineNumber);
	return readLine();
}

/** Prints this file throug stream */
void XFile::print2Stream(Stream *stream){
	int c;
	seek(0);
	while((c = read()) != -1){stream->print((char)c);}

}

// WRITTING METHODS

// Help methods
void XFile::sc(){print(';');}

/** Writes float value to file */
void XFile::writeLong(long &number, uint8_t size){printFormattedLong(this,number,size);}
/** Writes value and ";" */
void XFile::writeCSVLong(long &value,uint8_t intSize){writeLong(value,intSize);sc();}
/** Writes columns values and ";" */
void XFile::writeCSVLong(long* value,int &columns,uint8_t intSize){
	int n = 0;
	while(n++ < columns){writeCSVLong(*value++,intSize);}
}

/** Writes float value to file */
void XFile::writeByteValue(byte number){printFormattedByte(this,number);}
/** Writes value and ";" */
void XFile::writeCSVByte(byte value){writeByteValue(value);sc();}
/** Writes columns values and ";" */
void XFile::writeCSVByte(byte* values,uint8_t size,uint8_t mode){
	int n = 0;
	while(n++ < size){
		writeCSVByte(*values++);
		if(mode)println();
	}
}



/** Writes float value to file */
void XFile::writeFloat(float &number,uint8_t intSize,uint8_t floatSize){printFormattedFloat(this,number, intSize,floatSize);}
/** Writes value and ";" */
void XFile::writeCSVFloat(float &number,uint8_t intSize,uint8_t floatSize){writeFloat(number,intSize,floatSize);sc();}
/** Writes columns values and ";" */
void XFile::writeCSVFloat(float* values,uint8_t columns,uint8_t intSize,uint8_t floatSize){
	int n = 0;
	while(n++ < columns){writeFloat(*values++,intSize,floatSize);sc();}
}


/** Writes String and ";" */
void XFile::writeCSVString(String &s){print(s);sc();}
/** Writes value and ";" */
void XFile::writeCSVEFloat(float &value){
//		printFormattedEFloat(this,value);sc();
	XString s;
	s.formatEFloat(value);
	writeCSVString(s);
}
/** Writes columns values and ";" */
void XFile::writeCSVEFloat(float* value,int columns){
	int n = 0;
	while(n++ < columns){writeCSVEFloat(*value++);}
}

// TIME WRITING

/** Writes formatted date to file. Date format is DD:MM:YYYY */
void XFile::writeDate(){print(dateString());}
/** Writes formatted time to file. Date format is HH:MM:SS */
void XFile::writeHour(){print(hourString());}
/** Writes formatted date and time to file. */
void XFile::writeDateHour(){print(dateHourString());}
/** Writes millis to file. */
void XFile::writeMillis(){print(millis());}

// READING

/** Reads next ';' separated String. */
XString XFile::readNextCSVString(){

	int c = read();
	XString s;
	while((c != -1) && (c!=';')){
		if((!isSpace(c) || (c ==' '))) s += (char)c;
		c = read();
	}
	return s;
}
/** Reads next ';' separated long */
long XFile::readNextCSVLong(){ return readNextCSVString().toInt();}
/** Reads next ';' separated float */
float XFile::readNextCSVFloat(){ return readNextCSVString().getFloat();}
/** Reads next ';' separated e float */
float XFile::readNextCSVEFloat(){ return readNextCSVString().getEFloat();}

//	/** Reads CSV String at given row,column position */
String XFile::getCSVColumnInString(String s, unsigned int &column){

	unsigned int c = 0;
	unsigned int n;

	while(c<column && s.length()>0){
		n = s.indexOf(';');
		if(n>=0){s = s.substring(n+1);}
		c++;
	}

	n = s.indexOf(';');
	if(n > 0) s = s.substring(0,n);
	return s;

}


/** Reads CSV String at given row,column position */
String XFile::readCSVString(int row, int column){
	goToCSV(row,column);
	return readNextCSVString();
}

/** Reads CSV integer at position */
long XFile::readCSVLong(int row, int column){return  readCSVString(row,column).toInt();}
/** Reads CSV real at position */
float XFile::readCSVFloat(int row, int column){
	XString s =  readCSVString(row,column);
	return s.getFloat();
}
/** Reads CSV e format real at position */
float XFile::readCSVEFloat(int row, int column){
	XString s  =  readCSVString(row,column);
	return s.getEFloat();
}


// OPERATORS

/** Operator overload */
void XFile::operator = (File file){File::operator=(file);}

/** Flushes and closes log file */
void XFile::flushAndClose(){flush();close();}





