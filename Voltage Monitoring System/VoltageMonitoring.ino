#include <DHT.h>  // Including library for dht
 
#include <ESP8266WiFi.h>    //ESP Library
 
String apiKey = "BM9261BGCAQ11L2J";     //  Enter your Write API key from ThingSpeak
 
const char *ssid =  "Anonymous";     // Wifi SSID Name
const char *pass =  "booksbuddha@";    //WIFI Passphrase
const char* server = "api.thingspeak.com";    //Server Name
 
#define DHTPIN D2         //pin where the dht22 is connected

#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321

DHT dht(DHTPIN, DHTTYPE);
 
WiFiClient client;    //Connect to the Internet
int analogInput = A0; //Defining the Port for the analog signal
float vout = 0.0;       // Setting up the containeers and defining the data type
float vin = 0.0;
float R1 = 30000.0; //  
float R2 = 7500.0; // 
float value = 0;


void setup() 
{
       Serial.begin(9600);
       delay(10);
       dht.begin();
       pinMode(analogInput, INPUT);     //Defining the port Type
       
       Serial.println("Connecting to ");
       Serial.println(ssid);
 
 
       WiFi.begin(ssid, pass);
 
      while (WiFi.status() != WL_CONNECTED)  //Checking whether the wifi is connected
     {
            delay(500);
            Serial.print(".");
     }
      Serial.println("");
      Serial.println("WiFi connected");
       Serial.println("Your IP is");
       Serial.println((WiFi.localIP().toString()));
}
 
void loop() 
{

      // Reading temperature or humidity
      
      float h = dht.readHumidity();

      // Read temperature as Celsius (the default)
      float t = dht.readTemperature();
         // read the value at analog input
       value = analogRead(analogInput);
       vout = (value * 5.0) / 1024.0; // Converting the voltage values to the accurate using the resistor values of the vcc sensor
        vin = vout / (R2/(R1+R2)); 
              if (isnan(h) || isnan(t))    //Comparing the temperature and humidity values
                 {
                     Serial.println("Failed to read from DHT sensor!");
                      return;
                 }
 
                         if (client.connect(server,80))   //   "184.106.153.149" or api.thingspeak.com
                      {  

                             
                            //Sending the values to the things server in the respective configured fields
                             String postStr = apiKey;
                             postStr +="&field1=";
                             postStr += String(t);
                             postStr +="&field2=";
                             postStr += String(h);
                             postStr +="&field3=";
                             postStr += String(vin);
                             postStr += "\r\n\r\n";
 
                             client.print("POST /update HTTP/1.1\n");
                             client.print("Host: api.thingspeak.com\n");
                             client.print("Connection: close\n");
                             client.print("X-THINGSPEAKAPIKEY: "+apiKey+"\n");
                             client.print("Content-Type: application/x-www-form-urlencoded\n");
                             client.print("Content-Length: ");
                             client.print(postStr.length());
                             client.print("\n\n");
                             client.print(postStr);

                                                         
                             //Displaying the values in the serial montor mode with baud rate of 9600
                             Serial.print("Temperature: ");
                             Serial.print(t);
                             Serial.print(" degrees Celcius, Humidity: ");
                             Serial.print(h);
                             Serial.print(",  INPUT V= "); 
                             Serial.print(vin,2);
                             Serial.println("%. Send to Thingspeak.");

                        }
          client.stop();
 
          Serial.println("Waiting...");
  
  // thingspeak needs minimum 15 sec delay between updates
  delay(1000);
}
