#include <Wire.h>
#include <I2C_RTC.h>

static PCF8563 RTC;

void setup()
{
	Serial.begin(115200);
    while (!Serial); // wait for serial port to connect. Needed for native USB port only
	
	RTC.begin();

	if(RTC.isConnected() == false)
	{
		Serial.println("RTC Not Connected!");
		while(true);
	}

	RTC.setDay(13);
	RTC.setMonth(05);
	RTC.setYear(2030);
	RTC.setWeek(7);  // Always Set weekday after setting Date
	RTC.setHours(9);
	RTC.setMinutes(47);
	RTC.setSeconds(56);
	Serial.println(RTC.getDateTimeString());

	RTC.setDate(22, 7, 1985);  //SetDate(Day,Month,Year)
	RTC.setTime(20, 14, 36);  //SetTime(Hours,Minutes,Seconds)
	RTC.updateWeek();
	Serial.println(RTC.getDateTimeString());
}

void loop() 
{
	RTC.setDate(22, 7, 2025);  //SetDate(Day,Month,Year)
	RTC.setTime(12, 34, 56);  //SetTime(Hours,Minutes,Seconds)
	
	Serial.print(RTC.getWeekString().substring(0,3));
	Serial.print(" ");
	Serial.print(RTC.getDateString());
	Serial.print(" ");
	Serial.println(RTC.getTimeString());

	delay(2000);
}
