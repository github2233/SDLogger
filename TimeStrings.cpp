#include "TimeStrings.h"


String dateString(){
//	String s;
//	appendLong(s,day(),2);
//	s+= '/';
//	appendLong(s,month(),2);
//	s+= '/';
//	appendLong(s,year(),4);

	XString s;
	s.formatLong(day(),2);
	s+= '/';
	s.formatLong(month(),2);
	s+= '/';
	s.formatLong(year(),4);
	return s;
}

String hourString(){
//	String s;
//	appendLong(s,hour(),2);
//	s+= ':';
//	appendLong(s,minute(),2);
//	s+= ':';
//	appendLong(s,second(),2);

	XString s;
	s.formatLong(hour(),2);
	s+= ':';
	s.formatLong(minute(),2);
	s+= ':';
	s.formatLong(second(),2);
	return s;
}

String dateHourString(){return dateString() + " " + hourString();}

String timeStampString( ){

	XString s;
	s.formatLong(year(),4);
	s+= '-';
	s.formatLong(month(),2);
	s+= '-';
	s.formatLong(day(),2);
	s+= 'T';
	s+=hourString();
	s+= "+0200";

	return s;
}

String timeStampString(int utcMinutesDifference){

	XString s;
	s.formatLong(year(),4);
	s+= '-';
	s.formatLong(month(),2);
	s+= '-';
	s.formatLong(day(),2);
	s+= 'T';
	s+=hourString();

	if(utcMinutesDifference<0) {
		s += '-';
		utcMinutesDifference += -1;
	}else{
		s+= '+';
	}
	s.formatLong(utcMinutesDifference/60,2);
	s.formatLong(utcMinutesDifference%60,2);
//	s+= "+0200";


	return s;
}





