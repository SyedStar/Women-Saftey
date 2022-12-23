#include <SoftwareSerial.h>

void setup()
{
    Serial.begin(9600);   //Initialise serial to communicate with GSM Modem
}

void loop()
{
    Serial.println("AT"); //Once the handshake test is successful, it will back to OK
  delay(2000);

  Serial.println("AT+CMGF=1"); // Configuring TEXT mode
  delay(2000);
  Serial.println("AT+CMGS=\"+919000451559\"");//change ZZ with country code and xxxxxxxxxxx with phone number to sms
  delay(2000);
  Serial.println("Last Minute Engineers | lastminuteengineers.com"); //text content
  delay(2000);
  Serial.println((char)26);
  delay(2000);
     while(1);     //Wait forever
}
