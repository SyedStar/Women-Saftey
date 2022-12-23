
#include <TinyGPS++.h>
#include <SoftwareSerial.h>
SoftwareSerial GPS_SoftSerial(4, 3);/* (Rx, Tx) */
/* Create an object named gps of the class TinyGPSPlus */
TinyGPSPlus gps;   

volatile float minutes, seconds;
volatile int degree, secs, mins;

void setup()
{
    Serial.begin(9600);   //Initialise serial to communicate with GSM Modem
    GPS_SoftSerial.begin(9600); /* Define baud rate for software serial communication */
}
//String s3, s4;
void SendGPS()
{
  smartDelay(1000); /* Generate precise delay of 1ms */
        unsigned long start;
        double lat_val, lng_val, alt_m_val;
        uint8_t hr_val, min_val, sec_val;
        bool loc_valid, alt_valid, time_valid;
        lat_val = gps.location.lat(); /* Get latitude data */
        loc_valid = gps.location.isValid(); /* Check if valid location data is available */
        lng_val = gps.location.lng(); /* Get longtitude data */
        alt_m_val = gps.altitude.meters();  /* Get altitude data in meters */
        alt_valid = gps.altitude.isValid(); /* Check if valid altitude data is available */
        hr_val = gps.time.hour(); /* Get hour */
        min_val = gps.time.minute();  /* Get minutes */
        sec_val = gps.time.second();  /* Get seconds */
        time_valid = gps.time.isValid();  /* Check if valid time data is available */
        if (!loc_valid)
        {          
          Serial.print("Latitude : ");
          Serial.println("*****");
          Serial.print("Longitude : ");
          Serial.println("*****");
        }
        else
        {
          DegMinSec(lat_val);
          Serial.print("Latitude in Decimal Degrees : ");
          Serial.println(lat_val, 6);
          Serial.print("Latitude in Degrees Minutes Seconds : ");
          Serial.print(degree);
          Serial.print("\t");
          Serial.print(mins);
          Serial.print("\t");
          Serial.println(secs);
          DegMinSec(lng_val); /* Convert the decimal degree value into degrees minutes seconds form */
          Serial.print("Longitude in Decimal Degrees : ");
          Serial.println(lng_val, 6);
          Serial.print("Longitude in Degrees Minutes Seconds : ");
          Serial.print(degree);
          Serial.print("\t");
          Serial.print(mins);
          Serial.print("\t");
          Serial.println(secs);
        }
        if (!alt_valid)
        {
          Serial.print("Altitude : ");
          Serial.println("*****");
        }
        else
        {
          Serial.print("Altitude : ");
          Serial.println(alt_m_val, 6);    
        }
        if (!time_valid)
        {
          Serial.print("Time : ");
          Serial.println("*****");
        }
        else
        {
          char time_string[32];
          sprintf(time_string, "Time : %02d/%02d/%02d \n", hr_val, min_val, sec_val);
          Serial.print(time_string);   
           
        }
        delay(10000); //Give enough time for GSM to register on Network
 
  Serial.println("AT+CMGF=1");    //To send SMS in Text Mode
  delay(1000);
  Serial.println("AT+CMGS=\"+918147668398\"\r"); //Change to destination phone number 
  String Latn = String(lat_val, 6);
  String Lonn = String(lng_val, 6);
  String Location = Latn + "," + Lonn;
  //lat_val+","+lng_val
Serial.print("Your Vehicle Current Location ");
      Serial.print(Location);
      Serial.print("\n");
      Serial.print("Check Map: \n");
      Serial.print("https://maps.google.com/?q=");
      Serial.println(Location);
      Serial.println((char)26);
  
  // s3 = "Emergency current location is," + String(lat_val) + "," + String(lng_val) + '\n' ;
//   s4 = "Click link" + '\n' + "https://maps.google.com/?q=" + String(lat_val) + "," + String(lng_val);
 // Serial.println(s3);//the content of the message
  delay(200);
  //Serial.println((char)26); //the stopping character Ctrl+Z
  delay(1000);  
}

/* Create object named bt of the class SoftwareSerial */
   




  
  


void loop() {
     SendGPS();    //Send one SMS
    // while(1);     //Wait forever 
}

static void smartDelay(unsigned long ms)
{
  unsigned long start = millis();
  do 
  {
    while (GPS_SoftSerial.available())  /* Encode data read from GPS while data is available on serial port */
      gps.encode(GPS_SoftSerial.read());
/* Encode basically is used to parse the string received by the GPS and to store it in a buffer so that information can be extracted from it */
  } while (millis() - start < ms);
}

void DegMinSec( double tot_val)   /* Convert data in decimal degrees into degrees minutes seconds form */
{  
  degree = (int)tot_val;
  minutes = tot_val - degree;
  seconds = 60 * minutes;
  minutes = (int)seconds;
  mins = (int)minutes;
  seconds = seconds - minutes;
  seconds = 60 * seconds;
  secs = (int)seconds;
}
