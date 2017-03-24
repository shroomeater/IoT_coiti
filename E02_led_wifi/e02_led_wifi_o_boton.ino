#include <ESP8266WiFi.h>

const char*ssid = "SOLTEC 2,5G";
const char* password = "10081971";
int LED = D4;
WiFiServer server(80);

void setup() {
Serial.begin(115200);
delay(1500);
pinMode(LED, OUTPUT);
digitalWrite(LED, LOW);

Serial.println();
Serial.println();
Serial.print("Conectando con: ");
Serial.println(ssid);
WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
  delay(500);
  Serial.print(".");
  }

Serial.println("");
Serial.println("WiFi conectado");
server.begin();
Serial.println("Servidor iniciado");
Serial.println(WiFi.localIP());
}

void loop() {

WiFiClient client = server.available();
if (!client) {return;}
Serial.println("Nuevo cliente");

while(!client.available()){delay(1);}

String req = client.readStringUntil('\r');
Serial.println(req);
client.flush();
int val;

if (req.indexOf("/gpio/0") != -1) val = LOW;

else if (req.indexOf("/gpio/1") != -1) val = HIGH;

else {
  Serial.println("Solicitud Inválida");
  client.stop();
  return;
  }

digitalWrite(LED, val);
client.flush();
String s = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE HTML>\r\n<html>\r\nGPIO tiene el valor: ";
s += (val)?"high":"low";
//añadido 23/03/2017
s+="<br><a href='/gpio/1'>Encender</a>";
s+="<br><a href='/gpio/0'>Apagar</a>";
s += "</html>\n";
client.print(s);
delay(1);
Serial.println("Client disonnected");
}
