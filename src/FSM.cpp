/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "Particle.h"
#line 1 "/Users/darwinwang/Documents/IoT/FSM/src/FSM.ino"
void turnNorthGreen();
void turnEastGreen();
void setup();
void loop();
#line 1 "/Users/darwinwang/Documents/IoT/FSM/src/FSM.ino"
SYSTEM_THREAD(ENABLED)

#include "MQTT.h"

enum States
{
  NORTH,
  EAST
};
States currentState = NORTH;

void callback(char *topic, byte *payload, unsigned int length);

MQTT client("lab.thewcl.com", 1883, callback);

void turnNorthGreen()
{
  client.publish("eastLight", "1");
  delay(5000);
  client.publish("eastLight", "0");
  client.publish("northLight", "2");
}

void turnEastGreen()
{
  client.publish("northLight", "1");
  delay(5000);
  client.publish("northLight", "0");
  client.publish("eastLight", "2");
}
void callback(char *topic, byte *payload, unsigned int length)
{
  char p[length + 1];
  memcpy(p, payload, length);
  p[length] = NULL;

  if (String(p).equals("1"))
  {
    currentState = NORTH;
  }
  else if (String(p).equals("0"))
  {
    currentState = EAST;
  }

  switch (currentState)
  {
  case NORTH:
    turnNorthGreen();
    break;
  case EAST:
    turnEastGreen();
    break;
  }
}

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  if (client.isConnected())
  {
    client.subscribe("roadSensors");
    client.loop();
  }
  else
  {
    client.connect(System.deviceID());
    client.publish("eastLight", "0");
    client.publish("northLight", "2");
  }
}