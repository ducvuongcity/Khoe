#include <SoftwareSerial.h>
#include <DHT.h>

#define RX 10
#define TX 11

#define DHTPIN 2
#define DHTTYPE DHT11

SoftwareSerial esp8266(RX, TX);
DHT dht(DHTPIN, DHTTYPE);

// Wi-Fi Settings
String ssid = "10BP5";
String password = "lethanhtung";

//server
String server = "192.168.1.71";
String port = "10101";

//serial port handler variables
String inputString = "";
boolean stringComplete = false;

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

void readSensor(int timeout) {
	static time = 0;
	timeout /= 10;
	if(++time == timeout) {
		float humi = dht.readHumidity();
		float temp = dht.readTemperature();

		if (isnan(humi) || isnan(temp)) {
			Serial.println("Failed to read from DHT sensor!");
			return;
		}

		Serial.print("Humidity: ");
		Serial.print(humi);
		Serial.print(" %\t");
		Serial.print("Temperature: ");
		Serial.print(temp);
		Serial.print(" *C\r\n");

		sendCommand("AT+CIPMUX=0", 2000);
		sendCommand("AT+CIPMODE=0", 2000);
		sendCommand("AT+CIPSTART=\"TCP\",\"" + server + "\"," + port, 5000);
		String data = "$[lat,105][lng,21][temp," + String(temp) + "][humi," + String(humi) + "]\r\n";
		String cmdCIPSEND = "AT+CIPSEND=" + String(data.length());
		sendCommand(cmdCIPSEND, 2000);
		sendCommand(data, 2000);
		time = 0;
	}
}

void esp8266RcvHandler() {
	if (stringComplete) {
		Serial.println(inputString);
		//compare & handle
		//---------------
		inputString = "";
		stringComplete = false;
	}
}

void setup() {
  Serial.begin(115200);
  esp8266Config();
  dht.begin();
}

void loop() {
  delay(10);
  printEsp8266RcvString();
  readSensor(2000);
}

void serialEvent() {
  while (Serial.available()) {
    char inChar = (char)Serial.read();
    inputString += inChar;
    if (inChar == '\n') {
      stringComplete = true;
    }
  }
}