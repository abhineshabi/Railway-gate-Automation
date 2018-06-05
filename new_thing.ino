#include <ESP8266WiFi.h>

const char* ssid     = "RTR";
const char* password = "41404140";
const int ledPin = 13;      // led connected to digital pin 13
const int knockSensor = A0; // the piezo is connected to analog pin 0
const int threshold = 10;
char buffer[10];

const char* host = "api.thingspeak.com";
char thingSpeakAddress[] = "api.thingspeak.com";

String writeAPIKey = "7OZA0UCFWYJPYVHK";
const int updateThingSpeakInterval = 30 * 1000;      // Time interval in milliseconds to update ThingSpeak (number of seconds * 1000 = interval)

// Variable Setup
long lastConnectionTime = 0; 
boolean lastConnected = false;
int failedCounter = 0;
int sensorReading = 0;      // variable to store the value read from the sensor pin
int ledState = LOW; 

float myvalue = 1234;
// Initialize Arduino Ethernet Client
WiFiClient client;

void setup()
{
  // Start Serial for debugging on the Serial Monitor
  Serial.begin(9600);

  // Start Ethernet on Arduino
  //startEthernet();
   failedCounter = 0;

  client.stop();

  Serial.println("Connecting Arduino to network...");
  Serial.println();  

  delay(1000);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  delay(1000);
}

void loop()
{
  // Read value from Analog Input Pin 0
 // String analogValue0 = String(myvalue++, DEC);
 sensorReading = analogRead(knockSensor);

  // if the sensor reading is greater than the threshold:
  if (sensorReading >= threshold) {
    // toggle the status of the ledPin:
    ledState = !ledState;
    // update the LED pin itself:
    digitalWrite(ledPin, ledState);
    // send the string "Knock!" back to the computer, followed by newline
    Serial.println("Knock!");
        Serial.println(sensorReading);
  }
     String   my = dtostrf(sensorReading, 4, 1, buffer);
         
  // Print Update Response to Serial Monitor
  if (client.available())
  {
    char c = client.read();
    Serial.print(c);
  }

  // Disconnect from ThingSpeak
  if (!client.connected() && lastConnected)
  {
    Serial.println("...disconnected");
    Serial.println();

    client.stop();
  }

  // Update ThingSpeak
  //if(!client.connected() && (millis() - lastConnectionTime > updateThingSpeakInterval))
  //{
   // updateThingSpeak(my);
 // }
 
// Check if Arduino Ethernet needs to be restarted
//  if (failedCounter > 3 ) {startEthernet();}

 // lastConnected = client.connected();
//}
}
void updateThingSpeak(String tsData)
{
  if (client.connect(thingSpeakAddress, 80))
  {         
    client.print("POST /update HTTP/1.1\n");
    client.print("Host: api.thingspeak.com\n");
    client.print("Connection: close\n");
    client.print("X-THINGSPEAKAPIKEY: "+writeAPIKey+"\n");
    client.print("Content-Type: application/x-www-form-urlencoded\n");
    client.print("Content-Length: ");
    client.print(tsData.length());
    client.print("\n\n");

    client.print(tsData);

    lastConnectionTime = millis();

    if (client.connected())
    {
      Serial.println("Connecting to ThingSpeak...");
      Serial.println();

      failedCounter = 0;
    }
    else
    {
      failedCounter++;

      Serial.println("Connection to ThingSpeak failed ("+String(failedCounter, DEC)+")");   
      Serial.println();
    }

  }
  else
  {
    failedCounter++;

    Serial.println("Connection to ThingSpeak Failed ("+String(failedCounter, DEC)+")");   
    Serial.println();

    lastConnectionTime = millis(); 
  }
}

/*void startEthernet()
{
   failedCounter = 0;

  client.stop();

  Serial.println("Connecting Arduino to network...");
  Serial.println();  

  delay(1000);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  delay(1000);
}*/
