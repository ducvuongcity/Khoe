#include <DHT.h>
#include <SoftwareSerial.h>

#define RX 10
#define TX 11

SoftwareSerial esp8266(RX, TX);

#define DHTPIN 2     // what pin we're connected to
#define DHTTYPE DHT11   // DHT 11

// Wi-Fi Settings
String ssid = "10BP5";
String password = "lethanhtung";

//server
String server = "192.168.1.71";
String port = "10101";

DHT dht(DHTPIN, DHTTYPE);

void sendCommand(String command, int timeout) {
  Serial.println("Send Command: " + command);
  esp8266.println(command);
  delay(timeout);
}

void esp8266Config() {
  esp8266.begin(115200);
  sendCommand("AT", 2000);
  sendCommand("AT+CWMODE=1", 2000);
  sendCommand("AT+CWJAP=\"" + ssid + "\",\"" + password + "\"", 7000);
}

void setup() {
  Serial.begin(115200);
  esp8266Config();
  dht.begin();
}

void loop() {
  delay(2000);

  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.print(" *C\r\n");

  sendCommand("AT+CIPMUX=0", 2000);
  sendCommand("AT+CIPMODE=0", 2000);
  sendCommand("AT+CIPSTART=\"TCP\",\"" + server + "\"," + port, 5000);
  String data = "$[lat,105][lng,21][temp," + String(t) + "][humi," + h + "]\r\n";
  String cmdCIPSEND = "AT+CIPSEND=" + String(data.length());
  sendCommand(cmdCIPSEND, 2000);
  sendCommand(data, 2000);
}
