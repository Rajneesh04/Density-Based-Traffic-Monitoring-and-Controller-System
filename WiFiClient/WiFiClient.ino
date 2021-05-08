#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include <SoftwareSerial.h>
SoftwareSerial s(D1, D2);

const char* ssid     = "A*";
const char* password = "12345678";

char mqttUserName[] = "Rajneesh";
char mqttPass[] = "CO7PBA297KGVXIFW";
char writeAPIKey[] = "72LLDQUZUDOZLCNO";
long channelID = 1191280;
int fieldNumber = 1;
static const char dictionary[] = "0123456789"
                               "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                               "abcdefghijklmnopqrstuvwxyz";


//
int sensor_count[4] = {0,0,0,0};

WiFiClient client;
PubSubClient mqttClient(client);
const char* server = "mqtt.thingspeak.com";

unsigned long lastConnectionTime = 0;
const unsigned long postingInterval = 8L * 1000L;
int data1 = 0;
int data2 = 0;

bool json_serial() {
  s.write(50);
  StaticJsonBuffer<1000> jsonBuffer;
  JsonObject& root = jsonBuffer.parseObject(s);

  if (root == JsonObject::invalid()) {
    Serial.println("Invalid...");
    return false;
  }
  sensor_count[0] = root["data1"];
  sensor_count[1] = root["data2"];
  sensor_count[2] = root["data3"];
  sensor_count[3] = root["data4"];
  Serial.println("Json received and parsed");
  root.prettyPrintTo(Serial);
  Serial.println("");
  Serial.println("------------xxxxxxx-----------");
  return true;
}


void setup() {
  digitalWrite(LED_BUILTIN,HIGH);
  Serial.begin(9600);
  s.begin(9600);
  while (!Serial) {
    Serial.println("...");
    continue;
  }
  // We start by connecting to a WiFi network

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  mqttClient.setServer(server, 1883);
}

void publishData() {
  if (!mqttClient.connected()) {
    reconnect();
  }
  mqttClient.loop();

  if (millis() - lastConnectionTime > postingInterval) {
    mqttPublishFeed();
  }
}
void loop() {
  if (json_serial()) {
    publishData();
  }
  
}

void reconnect() {
  char clientID[9];
  while (!mqttClient.connected()) {
    Serial.print("Attempting MQTT connection......");
    for (int i = 0; i < 8; i++) {
      clientID[i] = dictionary[random(51)];
    }
    clientID[8] = '\0';
    if (mqttClient.connect(clientID, mqttUserName, mqttPass)) {
      Serial.println("connected");
    } else {
      Serial.println("failed, rc=");
      Serial.println(mqttClient.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

void mqttPublishFeed() {

  String data = String("field1=") + String(sensor_count[0], DEC) + "&field2=" + String(sensor_count[1], DEC) + 
                      "&field3=" + String(sensor_count[2], DEC) + "&field4=" + String(sensor_count[3], DEC);
  int len = data.length();
  const char *massageBuffer;
  massageBuffer = data.c_str();
  Serial.println("massageBuffer");
  Serial.println(massageBuffer);

  String topicString = "channels/" + String(channelID) + "/publish/" + String(writeAPIKey);
  len = topicString.length();
  const char *topicBuffer;
  topicBuffer = topicString.c_str();
  mqttClient.publish(topicBuffer, massageBuffer);
  lastConnectionTime = millis();
}
