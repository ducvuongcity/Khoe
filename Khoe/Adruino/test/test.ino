#include <DHT.h>
#include <SoftwareSerial.h>

#define PIN_ESP_RX        10
#define PIN_ESP_TX        11
#define PIN_DHT		        2
#define DHTTYPE DHT11
#define PIN_DUST_LEDPOWER	12
#define PIN_DUST_ANALOG		A0
#define PIN_RAIN_DIGITAL	5

#define TIME_SAMPLING     280
#define TIME_DELTA        40
#define TIME_SLEEP        9680

#define VOLT_AREF         5
#define DEFAULT_LAT       "105.8431605"
#define DEFAULT_LNG       "21.0065189"

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
  pinMode(PIN_DUST_LEDPOWER, OUTPUT);
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
  Serial.print("Humidity: ");
  Serial.print(humi);
  Serial.print(" %\t");
	return humi;
}

float getTemperature() {
	float temp = dht.readTemperature();
	if(isnan(temp)) {
		Serial.println("Failed to read temp from DHT sensor!");
		return -1;
	}
  Serial.print("Temperature: ");
  Serial.print(temp);
  Serial.print(" *C\r\n");
	return temp;
}

bool isRain() {
	bool rain = digitalRead(PIN_RAIN_DIGITAL);
	//Serial.println("Is Rain: " + ((rain == HIGH) ? "false" : "true"));
	return rain;
}

float getDust() {
  digitalWrite(PIN_DUST_LEDPOWER, LOW);          // turn on LED
  delayMicroseconds(TIME_SAMPLING);      // waiting
  float voMeasured = analogRead(PIN_DUST_ANALOG); // read the dust value
  delayMicroseconds(TIME_DELTA);
  digitalWrite(PIN_DUST_LEDPOWER, HIGH); // turn the LED off
  delayMicroseconds(TIME_SLEEP);
  float calcVoltage = voMeasured * (VOLT_AREF / 1024.0);
  float dust = (0.172 * calcVoltage - 0.0999)*1000;
 
  Serial.print("Raw Signal Value (0-1023): ");
  Serial.print(voMeasured);
 
  Serial.print(" - Voltage: ");
  Serial.print(calcVoltage);
  Serial.print("V");
 
  Serial.print(" - Dust Density: ");
  Serial.print(m_dust);
  Serial.println("ug/m3");

  return dust;
}

void sendToServer() {
  sendCommand("AT+CIPMUX=0", 2000);
  sendCommand("AT+CIPMODE=0", 2000);
  sendCommand("AT+CIPSTART=\"TCP\",\"" + server + "\"," + port, 5000);
  String data = "$[lat," + String(DEFAULT_LAT) + "][lng," + String(DEFAULT_LNG) + "][temp," + String(m_temp) + "][humi," + String(m_humi) + "][rain," + String(m_isRain) + "][dust," + String(m_dust) + "]\r\n";
  String cmdCIPSEND = "AT+CIPSEND=" + String(data.length());
  sendCommand(cmdCIPSEND, 2000);
  sendCommand(data, 2000);
}

void setup() {
  Serial.begin(115200);
  esp8266Config();
  dhtSensorConfig();
  rainSensorConfig();
  dustSensorConfig();
}

void loop() {
  delay(1000);
  m_temp = getTemperature();
  m_humi = getHumidity();
  m_isRain = isRain();
  m_dust = getDust();
  sendToServer();
}
