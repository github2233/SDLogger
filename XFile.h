/* XFile.h
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
#ifndef XFILE_H_
#define XFILE_H_

#include <Arduino.h>
#include "../SD/SD.h"
#include <XString.h>
#include "TimeStrings.h"

#define COLUMNS 0
#define ROWS 1

/** Xtra functionality class for SD Files */
class XFile : public File{
public :

	XFile();
	virtual ~XFile();

	/** jumps line */
	bool jumpln();
	/** jumps CSV */
	bool jumpCSV();
	/** Makes file point to line */
	bool goToLine(int line);
	/** Reads CSV String at given row,column position */
	bool goToCSV(int row, int column);
	/** Gets file's number of lines @return Number of lines in the file*/
	int getLines();

	// READING METHODS

	/** Reads next line in this file. @return Next line*/
	String readLine();
	/** Reads lineNumber line in this file @return lineNumber line*/
	String readLine(int lineNumber);

	/** Reads next ';' separated String. */
	XString readNextCSVString();
	/** Reads next ';' separated long */
	long readNextCSVLong();
	/** Reads next ';' separated float */
	float readNextCSVFloat();
	/** Reads next ';' separated e float */
	float readNextCSVEFloat();

	/** Reads CSV String at given row,column position */
	String getCSVColumnInString(String s, unsigned int &column);

	/** Reads CSV String at given row,column position */
	String readCSVString(int row, int column);
	/** Reads CSV integer at position */
	long readCSVLong(int row, int column);
	/** Reads CSV real at position */
	float readCSVFloat(int row, int column);
	/** Reads CSV e format real at position */
	float readCSVEFloat(int row, int column);



	// WRITTING METHODS

	// Help methods
	void sc();

	/** Writes float value to file */
	void writeLong(long &number, uint8_t size = 2);
	/** Writes value and ";" */
	void writeCSVLong(long &value,uint8_t intSize = 2);
	/** Writes columns values and ";" */
	void writeCSVLong(long* value,int &columns,uint8_t intSize = 2);

	/** Writes float value to file */
	void writeByteValue(byte number);
	/** Writes value and ";" */
	void writeCSVByte(byte value);
	/** Writes size CSV values from byte array either as a row as a column */
	void writeCSVByte(byte* values,uint8_t size = 1,uint8_t mode=COLUMNS);
	/** Writes CSV byte array one each row values and ";" */
	//void writeCSVByteArray(byte* value,int &rows = 1);

	/** Writes float value to file */
	void writeFloat(float &number,uint8_t intSize = 2,uint8_t floatSize = 2);
	/** Writes value and ";" */
	void writeCSVFloat(float &number,uint8_t intSize,uint8_t floatSize);
	/** Writes columns values and ";" */
	void writeCSVFloat(float* value,uint8_t columns = 1,uint8_t intSize = 2,uint8_t floatSize = 2);


	/** Writes String and ";" */
	void writeCSVString(String &s);

	/** Writes value and ";" */
	void writeCSVEFloat(float &value);
	/** Writes columns values and ";" */
	void writeCSVEFloat(float* value,int columns = 1);

	// TIME WRITING

	/** Writes formatted date to file. Date format is DD:MM:YYYY */
	void writeDate();
	/** Writes formatted time to file. Date format is HH:MM:SS */
	void writeHour();
	/** Writes formatted date and time to file. */
	void writeDateHour();
	/** Writes millis to file. */
	void writeMillis();


	// OTHERS

	/** Operator overload */
	void operator = (File file);

	/** Flushes and closes log file */
	void flushAndClose();

	/** Prints this file throug stream */
	void print2Stream(Stream *stream);


};



#endif /* XFILE_H_ */
