
#include<EEPROM.h>
#include <LiquidCrystal.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>



const char* mqtt_server = "broker.mqtt-dashboard.com";
String ssid, pass;
WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int value = 0;

void setup_wifi() {

  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, pass);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  randomSeed(micros());

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}


void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();


}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      client.publish("srihari/outTopic", "hello world");
      // ... and resubscribe
      client.subscribe("srihari/inTopic");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void boot_sequence(void);

LiquidCrystal lcd(D5, D6, D3, D2, D1, D0);
bool kill_switch;





void setup() {

  pinMode(D4,OUTPUT);
  analogWrite(D4, 200);
  
   attachInterrupt(digitalPinToInterrupt(D7), IntCallback, FALLING);
   Serial.begin(115200);
  lcd.begin(16, 2);

  EEPROM.begin(512);
  kill_switch = EEPROM.read(108);

    client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
 
}




void loop() {

if(kill_switch == false)
{ lcd.clear();
  lcd.setCursor(0, 1);

  lcd.print("Application      ");
   setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
  while(1)
  {
    if(kill_switch == false){
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  long now = millis();
  if (now - lastMsg > 2000) {
    lastMsg = now;
    ++value;
    snprintf (msg, 50, "hello world #%ld", value);
    Serial.print("Publish message: ");
    Serial.println(msg);
    client.publish("srihari/outTopic", msg);
  }

    }
  }
}


else if(kill_switch == true)
{
  boot_sequence();
}



}



void boot_sequence()
{
   String p;
   char q;

  Serial.println(" 'Welcome to the boot-Sequence' ");
  Serial.println("This only Runs ONCE when you boot-up for the first time or you hit the kill switch !");
  Serial.println();Serial.println();
  Serial.println("----------------------------------------------------------------------------------");

Serial.println(" ENter the SSID and password one after other in serial window to setup");

 again: Serial.print("Enter the ssid: ");
  while(!Serial.available());
  p = Serial.readString();

  ssid = p;
  Serial.println(ssid);

  Serial.print("Password please : ");
    while(!Serial.available());
  p = Serial.readString();
  pass= p;
  Serial.println(pass);


  Serial.println("Is the above entered info correct? To confirm enter 'yes' or 'no' to re-enter 'em");
    while(!Serial.available());
  q = Serial.read();
  if(q == 'y')
  {

    Serial.println(q);
      Serial.println(" Okay then, attempting to connect to Wi-Fi. Sitback and relax. ");
      
  }

 if(q == 'n')
  {
    Serial.println(q);
    Serial.println(" No probs.. mistakes happen. Please re-enter.. ");
    goto again;
  }
  lcd.clear();
  lcd.setCursor(0,0);

  lcd.print("ssid: ");
  lcd.println(ssid);
  lcd.setCursor(0,1);
  lcd.print("pass: ");
  lcd.print(pass);
       kill_switch = !kill_switch;
       EEPROM.write(108, kill_switch);
       EEPROM.commit();
  delay(3000);
  

  
  
}


void IntCallback()
{
  kill_switch = !kill_switch;
         EEPROM.write(108, kill_switch);
       EEPROM.commit();
}
