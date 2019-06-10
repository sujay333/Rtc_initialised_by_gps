#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include "RTClib.h"
#include "Wire.h"  
#include <RTClib.h>
RTC_DS3231 rtc;

/*
   This sample sketch demonstrates the normal use of a TinyGPS++ (TinyGPSPlus) object.
   It requires the use of SoftwareSerial, and assumes that you have a
   4800-baud serial GPS device hooked up on pins 4(rx) and 3(tx).
*/
static const int RXPin = 4, TXPin = 3;//these pins are for gps , Rtc pins are connected to analog pins (4,5)
static const uint32_t GPSBaud = 9600;

// The TinyGPS++ object
TinyGPSPlus gps;

// The serial connection to the GPS device
SoftwareSerial ss(RXPin, TXPin);
float latit,lon;
int hours,minut,seconds,yer,mnth,dte;
String date_data;
void setup()
{
  Serial.begin(9600);
  ss.begin(GPSBaud);
   Serial.println(TinyGPSPlus::libraryVersion());
  Serial.println();

   if (! rtc.begin()) 
  {
     Serial.println("Couldn't find RTC");
 
      while (1);
  }
    else 
 {   Serial.println("FOUND RTC...");
 
    delay(1000);
    
 }

 rtc.adjust(DateTime(2000, 05, 14, 04, 25, 30));//reset RTC with wrong time and date
      DateTime now = rtc.now();
    date_data+=String(now.day(), DEC);
    date_data+="/";
    date_data += String(now.month(), DEC);
    date_data +="/";
    date_data += String(now.year()%2000, DEC);
    date_data +=" ";
    date_data += String(now.hour(), DEC);
    date_data +=":";
    date_data += String(now.minute(), DEC);
    date_data +=":"; 
   // Serial.println("no");
    date_data += String(now.second(), DEC);
    Serial.print("OLD TIME");
    Serial.println(date_data);
    date_data="";
    delay(1000);

}

void loop()
{     
 if (millis() > 5000 && gps.charsProcessed() < 10)
  {
    Serial.println(F("No GPS detected: check wiring."));
    while(true);
  }

  // This sketch displays information every time a new sentence is correctly encoded.
  while (ss.available() > 0)
    if (gps.encode(ss.read()))
     {
  
   if (gps.time.isValid())
  {
    hours=gps.time.hour();
    minut= gps.time.minute();
    seconds=gps.time.second();
  }


   if (gps.date.isValid())
  {
    mnth=gps.date.month();
    yer=gps.date.year();
    dte=gps.date.day();
  }
 
 
  if(gps.time.isValid())
    {                      //UTC time is converted GMT+5.5(Indian time)
         int mon[]={31,28,31,30,31,30,31,31,30,31,30,31};
    if ( ((yer % 4) == 0) && ( ((yer % 100) != 0) || ((yer % 400) == 0) ))
      mon[1]=29;
    else
      mon[1]=28;

    minut=minut+30;

    if(minut>=60)
       {
         minut=minut-60;
         hours=hours+1;
       }

     hours=hours+5;

       if(hours>=24)
       {
           hours=hours-24;
           dte=dte+1;
       }

      if(dte>mon[mnth-1])
      {
          dte=dte-mon[mnth-1];
          mnth=mnth+1;
      }

      if(mnth>12)
      {
          mnth=1;
          yer=yer+1;
      }
    } 
   

  rtc.adjust(DateTime(yer, mnth, dte,hours,minut,seconds));
    //delay(2000);
    
      DateTime now = rtc.now();
     date_data+=String(now.day() , DEC);
    date_data +="/";
    date_data += String(now.month(), DEC);
    date_data +="/";
    date_data += String( now.year() %2000, DEC);
    date_data +=" ";
    date_data += String(now.hour(), DEC);
    date_data +=":";
    date_data += String(now.minute(), DEC);
    date_data +=":"; 
    date_data += String(now.second() , DEC);
    
     Serial.print("NEW DATE");
     Serial.println(date_data);
    delay(1000);
    date_data="";
     }

  
}
