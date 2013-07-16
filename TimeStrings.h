#ifndef TIMESTRINGS_H_
#define TIMESTRINGS_H_

#include <Arduino.h>
#include "../Time/Time.h"
#include "../XString/XString.h"

// TIME STRINGS


String dateString();
String hourString();
String dateHourString();
String timeStampString();
String timeStampString(int );
//String timeStampZString(int );
#endif /* TIMESTRINGS_H_ */
