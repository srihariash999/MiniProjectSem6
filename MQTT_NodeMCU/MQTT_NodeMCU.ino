
#include <ESP8266WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"



#define WLAN_SSID       "Redmi4"
#define WLAN_PASS       "namaste99"

/************************* Adafruit.io Setup *********************************/

#define AIO_SERVER      "m16.cloudmqtt.com"
#define AIO_SERVERPORT  12094                  // use 8883 for SSL
#define AIO_USERNAME    "uzlbcslv"
#define AIO_KEY         "L_Sxi8ZtDdkZ"


#define LED LED_BUILTIN

/************ Global State ******************/


WiFiClient client;



Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_USERNAME, AIO_KEY);






/****************************** Feeds ***************************************/





Adafruit_MQTT_Subscribe incoming = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "incoming");

Adafruit_MQTT_Publish outgoing = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "outgoing");













/*************************** Sketch Code ************************************/


#define MQTT_CONN_KEEPALIVE 300

void MQTT_connect();

void setup() {

  pinMode(D4,OUTPUT);
   pinMode(D5,OUTPUT);
   pinMode(LED,OUTPUT);

  Serial.begin(115200);
  delay(10);


  Serial.println(); Serial.println();
  
  Serial.print("Connecting to ");
  Serial.println(WLAN_SSID);

  WiFi.begin(WLAN_SSID, WLAN_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  Serial.println("WiFi connected");
  Serial.println("IP address: "); Serial.println(WiFi.localIP());


  mqtt.subscribe(&incoming);

  

}

   int x =0;
void loop() {

  MQTT_connect();



  Adafruit_MQTT_Subscribe *subscription;
  
  while ((subscription = mqtt.readSubscription(10000))) {


    if (subscription == &incoming) {
      Serial.print(F("incoming msg: "));
      Serial.println((char *)incoming.lastread);
      
    } 
  
  }


    while(Serial.available())
    {
    uint32_t p = Serial.read();
  Serial.print(F("\nSending photocell val "));
  Serial.print(p);
  Serial.print("...");
  if (! outgoing.publish(p)) {
    Serial.println(F("Failed"));
  } else {
    Serial.println(F("OK!"));
  }
      
    }




  

  // ping the server to keep the mqtt connection alive
  if(! mqtt.ping()) {
    mqtt.disconnect();
  }

}


void MQTT_connect() {
  int8_t ret;


  if (mqtt.connected()) {
    return;
  }

  Serial.print("Connecting to MQTT... ");

  uint8_t retries = 3;
  while ((ret = mqtt.connect()) != 0) { // connect will return 0 for connected
       Serial.println(mqtt.connectErrorString(ret));
       Serial.println("Retrying MQTT connection in 5 seconds...");
       mqtt.disconnect();
       delay(5000);  // wait 5 seconds
       retries--;
       if (retries == 0) {
         // basically die and wait for WDT to reset me
         while (1);
       }
  }
  Serial.println("MQTT Connected!");
}
