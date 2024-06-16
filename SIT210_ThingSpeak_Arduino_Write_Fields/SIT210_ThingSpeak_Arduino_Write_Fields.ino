// Basic Variable Setup.
//#include "DateTime.h"
//long TimeElapsed = DateTime.Now.Ticks/TimeSpan.TicksPerMillisecond;

// WiFi & ThingSpeak setup.
#include "WiFiNINA.h"
#include "secrets.h"
#include "ThingSpeak.h" // always include thingspeak header file after other header files and custom macros

char ssid[] = SECRET_SSID;   // your network SSID (name) 
char pass[] = SECRET_PASS;   // your network password
int keyIndex = 0;            // your network key Index number (needed only for WEP)
WiFiClient  client;

unsigned long myChannelNumber = SECRET_CH_ID;
const char * myWriteAPIKey = SECRET_WRITE_APIKEY;

// Temperature/Humidity Sensor setup.
#include "DHT.h"
#define DHTPIN 2
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

// Light Sensor Setup.
#include <BH1750.h>
#include <Wire.h>

BH1750 lightMeter;

// Sound Buzzer setup.
#include <string>
#define timeDelay 60
#define pinout 3

// Variable Initialisation.
// ThingSpeak Status.
String myStatus = "";

// Temperature & Humidity.
float Temperature = 0.0;
float Humidity = 0.0;

// Light Intensity.
float LightIntensity = 0;

// Sound Buzzer
int Bar = 1;
int Note = 1;
//long SoundTimer = DateTime.Now.Ticks/TimeSpan.TicksPerMillisecond;

// Arduino Setup.
void setup()
{
  // Initialize Serial.
  Serial.begin(115200);
  Wire.begin();
  while (!Serial)
  {
    // Wait for serial port to connect. Needed for Leonardo native USB port only.
  }
  
  // Initialize ThingSpeak.
  ThingSpeak.begin(client);

  // Initialise Temperature/Humidity Sensor.
  dht.begin();

  // Initialise Light Sensor.
  lightMeter.begin();
}

// Arduino Loop.
void loop()
{
  // Connect or reconnect to WiFi.
  if(WiFi.status() != WL_CONNECTED){
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(SECRET_SSID);

    while(WiFi.status() != WL_CONNECTED)
    {
      WiFi.begin(ssid, pass);  // Connect to WPA/WPA2 network. Change this line if using open or WEP network.
      Serial.print(".");
      delay(5000);     
    } 
    Serial.println("\nConnected.\n");
  }

  // Collect temperature and humidity data from sensor.
  Temperature = dht.readTemperature();
  Humidity = dht.readHumidity();

  Serial.print("Temperature: ");
  Serial.print(Temperature);
  Serial.println("°C");
  Serial.print("Humidity: ");
  Serial.print(Humidity);
  Serial.println("%");

  // Collect light data from sensor.
  LightIntensity = lightMeter.readLightLevel();
  
  Serial.print("Light Intensity: ");
  Serial.print(LightIntensity);
  Serial.println(" lx");

  // Set ThingSpeak fields with values.
  ThingSpeak.setField(1, Temperature);
  ThingSpeak.setField(2, Humidity);
  ThingSpeak.setField(3, LightIntensity);

  // Set ThingSpeak status.
  ThingSpeak.setStatus(myStatus);
  
  // Write to ThingSpeak channel. 
  int x = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
  if(x == 200){
    Serial.println("Channel update successful.");
  }
  else{
    Serial.println("Problem updating channel. HTTP error code " + String(x));
  }
  Serial.println();

  if (Temperature > 34 & Humidity < 25 & LightIntensity > 100)
  {
    tone(pinout, 988);
    delay(8*timeDelay);

    tone(pinout, 0);
    delay(8*timeDelay);

    tone(pinout, 988);
    delay(8*timeDelay);

    tone(pinout, 0);
    delay(8*timeDelay);
  }
  /*
  // Play Buzzer.
  for (int i = 0; i < 2; i++)
  {
    // First Bar
    tone(pinout, 0);
    delay(2*timeDelay);

    tone(pinout, 0);
    delay(4*timeDelay);

    // B5
    tone(pinout, 988);
    delay(2*timeDelay);

    tone(pinout, 0);
    delay(4*timeDelay);

    // G6
    tone(pinout, 1568);
    delay(2*timeDelay);

    tone(pinout, 0);
    delay(4*timeDelay);
  
    // F6#
    tone(pinout, 1480);
    delay(2*timeDelay);

    tone(pinout, 0);
    delay(4*timeDelay);
  
    // Second Bar
    // C6#
    tone(pinout, 1109);
    delay(2*timeDelay);

    tone(pinout, 0);
    delay(4*timeDelay);
  
    // D6
    tone(pinout, 1174);
    delay(2*timeDelay);

    tone(pinout, 0);
    delay(4*timeDelay);
  
    // A5#
    tone(pinout, 932);
    delay(2*timeDelay);

    tone(pinout, 0);
    delay(4*timeDelay);

    // B5
    tone(pinout, 988);
    delay(2*timeDelay);

    tone(pinout, 0);
    delay(4*timeDelay);
  
    //Third Bar
    // A5
    tone(pinout, 880);
    delay(2*timeDelay);

    tone(pinout, 0);
    delay(2*timeDelay);
  
    // G5#
    tone(pinout, 831);
    delay(2*timeDelay);

    tone(pinout, 0);
    delay(2*timeDelay);
  
    // G5
    tone(pinout, 784);
    delay(2*timeDelay);

    tone(pinout, 0);
    delay(2*timeDelay);
  
    // F5#
    tone(pinout, 740);
    delay(2*timeDelay);

    tone(pinout, 0);
    delay(2*timeDelay);
  
    // G5
    tone(pinout, 784);
    delay(2*timeDelay);

    tone(pinout, 0);
    delay(2*timeDelay);
  
    // G5#
    tone(pinout, 831);
    delay(2*timeDelay);

    tone(pinout, 0);
    delay(2*timeDelay);
  
    // Fourth Bar
    // A5
    tone(pinout, 880);
    delay(2*timeDelay);

    tone(pinout, 0);
    delay(4*timeDelay);
  
    // G5#
    tone(pinout, 831);
    delay(2*timeDelay);

    tone(pinout, 0);
    delay(4*timeDelay);
  
    // G5
    tone(pinout, 784);
    delay(2*timeDelay);

    tone(pinout, 0);
    delay(4*timeDelay);
  
    // G5#
    tone(pinout, 831);
    delay(2*timeDelay);

    tone(pinout, 0);
    delay(4*timeDelay);
  
    // Fifth Bar
    // B3
    tone(pinout, 247);
    delay(12*timeDelay);
  
    // C4
    tone(pinout, 262);
    delay(timeDelay);
  
    // D4
    tone(pinout, 294);
    delay(timeDelay);
  
    // B6
    tone(pinout, 1976);
    delay(2*timeDelay);

    // Rest
    tone(pinout, 0);
    delay(8*timeDelay);

    // Sixth Bar
    // Rest
    tone(pinout, 0);
    delay(12*timeDelay);
  
    // E6
    tone(pinout, 1319);
    delay(2*timeDelay);

    tone(pinout, 0);
    delay(2*timeDelay);
  
    // D6#
    tone(pinout, 1245);
    delay(2*timeDelay);

    tone(pinout, 0);
    delay(2*timeDelay);
  
    // D6
    tone(pinout, 1174);
    delay(2*timeDelay);

    tone(pinout, 0);
    delay(2*timeDelay);

    // Seventh Bar
    // Rest
    tone(pinout, 0);
    delay(24*timeDelay);
  
    // Eighth Bar
    tone(pinout, 0);
    delay(4*timeDelay);
  
    // D6
    tone(pinout, 1174);
    delay(2*timeDelay);
  
    // D6
    tone(pinout, 1174);
    delay(2*timeDelay);

    tone(pinout, 0);
    delay(4*timeDelay);
  
    // D6
    tone(pinout, 1174);
    delay(2*timeDelay);

    tone(pinout, 0);
    delay(2*timeDelay);

    // C6#
    tone(pinout, 1109);
    delay(2*timeDelay);

    tone(pinout, 0);
    delay(2*timeDelay);

    // C6
    tone(pinout, 1047);
    delay(2*timeDelay);

    tone(pinout, 0);
    delay(2*timeDelay);
  }*/
}
