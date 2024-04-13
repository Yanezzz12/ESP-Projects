#include <ESP8266WiFi.h>
#include <Espalexa.h>

//Wifi 
#define   WiFiName  "Totalplay-7DA5"
#define   WiFiPwd   "7DA56049BTEyd989"

//Callback functions
void LightAction(uint8_t brightness);

Espalexa EchoMyz;

//Pins
const int redLedPin = 12;
const int blueLedPin = 14;
const int greenLedPin = 16;
const int relayPin = 5;

//Variables
int counter = 0;

void setup() 
{
  Serial.begin(115200); 
  
  //Pin Setup
  pinMode(redLedPin, OUTPUT); 
  pinMode(blueLedPin, OUTPUT);  
  pinMode(greenLedPin, OUTPUT);  
  pinMode(relayPin, OUTPUT);
  Serial.println();

  //Begin WiFi
  WiFi.begin(WiFiName, WiFiPwd);

  //Connecting to WiFi...
  Serial.print("Connecting to ");
  Serial.print(WiFiName);

  //Loop continuously while WiFi is not connected
  while(WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    Connecting();
    counter++;

    if(counter > 90)
      Error();   
  }

  Correct();

  Serial.println();
  Serial.print("Connected! IP address: ");
  Serial.println(WiFi.localIP());

  EchoMyz.addDevice("Lampara Escritorio", LightAction);
  EchoMyz.begin();

  Action();
  Correct();
}

unsigned long previousMillis = 0;
unsigned long interval = 30000;
void loop() 
{
  unsigned long currentMillis = millis();

  if ((WiFi.status() != WL_CONNECTED) && (currentMillis - previousMillis >=interval))
  {
    WiFi.disconnect();
    WiFi.reconnect();
    previousMillis = currentMillis;
  }

  EchoMyz.loop();
  delay(1);
}

void LightAction(uint8_t brightness)
{
  if(brightness)
  {
    Action();
    digitalWrite(relayPin, 1);
  } 
  else
  {
    Action();
    digitalWrite(relayPin, 0);
  }
}

void Error()
{
  short interval = 100;
  short repetitions = 5;

  for(int i = 0; i < repetitions; i++)
  {
    digitalWrite(redLedPin, HIGH);
    delay(interval);
    digitalWrite(redLedPin, LOW);
    delay(interval);
  }

  delay(10000);
  ESP.restart();
}

void Connecting()
{
  short interval = 100;

  digitalWrite(blueLedPin, HIGH);
  delay(interval);
  digitalWrite(blueLedPin, LOW);
  delay(interval);
}

void Action()
{
  short interval = 70;
  short repetitions = 2;

  for(int i = 0; i < repetitions; i++)
  {
    digitalWrite(blueLedPin, HIGH);
    delay(interval);
    digitalWrite(blueLedPin, LOW);
    delay(interval);
  }
}

void Correct()
{
  short interval = 100;
  short repetitions = 3;

  for(int i = 0; i < repetitions; i++)
  {
    digitalWrite(greenLedPin, HIGH);
    delay(interval);
    digitalWrite(greenLedPin, LOW);
    delay(interval);
  }
}
