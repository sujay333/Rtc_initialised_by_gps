# Rtc_initialised_by_gps
libraries to be used:
1.<Tinygps++>
2.<RTClib.h>
3.<wire.h>
4.<SoftwareSerial.h>

description:

A Gps is used to show the current location but it is also used to reset the RTC(Real Time Clock).RTC is used to show GMT time according to the location. RTC contains a Lithium battery which retains the time when the device is swiched off.Then GPS is used to reset the RTC and convert UTC time to GMT+5.5 according to Indian standred time.This is how time is shows in any smart phone. It is a simple project but gives knowlage about working of GPS,RTC modules in Smartphones.
