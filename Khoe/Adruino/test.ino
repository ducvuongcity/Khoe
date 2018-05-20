#include <DHT.h>
#include <SoftwareSerial.h>

#define PIN_ESP_RX 10
#define PIN_ESP_TX 11
#define PIN_DHT		2
#define DHTTYPE DHT11
#define PIN_DUST_LEDPOWER	12
#define PIN_DUST_ANALOG		6
#define PIN_RAIN_DIGITAL	5

SoftwareSerial esp8266(PIN_ESP_RX, PIN_ESP_TX);

// Wi-Fi Settings
String ssid = "10BP5";
String password = "lethanhtung";

//server
String server = "192.168.1.71";
String port = "10101";

//sensor
DHT dht(PIN_DHT, DHTTYPE);
float m_humi, m_temp, m_dust;
bool m_isRain;

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

void dhtSensorConfig() {
  dht.begin();
}

void dustSensorConfig() {
  
}

void rainSensorConfig() {
	m_isRain = false;
	pinMode(PIN_RAIN_DIGITAL, INPUT);
}

float getHumidity() {
	float humi = dht.readHumidity();
	if(isnan(humi)) {
		Serial.println("Failed to read humi from DHT sensor!");
		return -1;
	}
	return humi;
}

float getTemperature() {
	float temp = dht.readTemperature();
	if(isnan(temp)) {
		Serial.println("Failed to read temp from DHT sensor!");
		return -1;
	}
	return temp;
}

bool isRain() {
	bool rain = digitalRead(PIN_RAIN_DIGITAL);
	if(HIGH == rain)
		Serial.print("Is Rain: true\n");
	else 
		Serial.print("Is Rain: false\n");
	return 
}

void printDebugLog() {
	Serial.print("Humidity: ");
	Serial.print(m_humi);
	Serial.print(" %\t");
	Serial.print("Temperature: ");
	Serial.print(m_temp);
	Serial.print(" *C\r\n");
}

void sendToServer() {
  sendCommand("AT+CIPMUX=0", 2000);
  sendCommand("AT+CIPMODE=0", 2000);
  sendCommand("AT+CIPSTART=\"TCP\",\"" + server + "\"," + port, 5000);
  String data = "$[lat,105][lng,21][temp," + String(m_temp) + "][humi," + m_humi + "]\r\n";
  String cmdCIPSEND = "AT+CIPSEND=" + String(data.length());
  sendCommand(cmdCIPSEND, 2000);
  sendCommand(data, 2000);
}

void setup() {
  Serial.begin(115200);
  //esp8266Config();
  rainSensorConfig();
}

void loop() {
  delay(1000);
  
  isRain();
  //printDebugLog();
  //sendToServer();
}
