#include <SimpleTimer.h> 
#define BLYNK_PRINT Serial    // Comment this out to disable prints and save space
#include <SPI.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>
// const int pumpPin = 14; // GPI14-d5
// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "noXhC1A4M_gQEBAGHtXXJPiBjdtaIbag"; //Enter the Auth code which was send by Blink

// Your WiFi credentials.
// Set password to mnfor open networks.
char ssid[] = "vivo";  //Enter your WIFI Name
char pass[] = "123456789";  //Enter your WIFI Password



#define DHTPIN 2          // Digital pin 4

// Uncomment whatever type you're using!
#define DHTTYPE DHT11     // DHT 11
//#define DHTTYPE DHT22   // DHT 22, AM2302, AM2321
//#define DHTTYPE DHT21   // DHT 21, AM2301

DHT dht(DHTPIN, DHTTYPE);
SimpleTimer timer;

// This function sends Arduino's up time every second to Virtual Pin (5).
// In the app, Widget's reading frequency should be set to PUSH. This means
// that you define how often to send data to Blynk App.
void sendSensor()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature(); // or dht.readTemperature(true) for Fahrenheit
  int s = analogRead(A0);

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  Blynk.virtualWrite(V4,s);    //v4 is for soil moisture
  Blynk.virtualWrite(V5, h);  //V5 is for Humidity
  Blynk.virtualWrite(V6, t);  //V6 is for Temperature

    if(t > 27){
    Blynk.email("4nm21is079@nmamit.in", "Temperature Alert🌡️ ", "The current temperature in your area exceeds 26 degrees Celsius. Please take note and ensure your safety.");
  }
   
    if(s < 600){
    Blynk.email("4nm21is079@nmamit.in", "Rainfall Alert☔️", "The area where you are located is experiencing rainfall. Please take note and prioritize your safety.!!!");
    Blynk.notify("Rainfall Alert☔️");
    // Blynk.notify("Alert - Temperature over 26C!");
  }
}

void setup()
{
  Serial.begin(9600); // See the connection status in Serial Monitor
  Blynk.begin(auth, ssid, pass,IPAddress(117,236,190,213),8080);

  dht.begin();
  // pinMode(pumpPin, OUTPUT);

  // Setup a function to be called every second
  timer.setInterval(1000L, sendSensor);
}

void loop()
{
  Blynk.run(); // Initiates Blynk
  timer.run(); // Initiates SimpleTimer
}


// BLYNK_WRITE(V1)
// {
//   int pumpState = param.asInt();
//   Serial.println(pumpState); // Get value as integer
//   digitalWrite(pumpPin,pumpState);
// }