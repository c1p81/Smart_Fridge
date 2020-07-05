/*
 * Hackathon 
 * Arduino Client per Google Cloud
 * 
 * versione per Arduino Yun 
 * #include <Process.h>

void setup() {
  Bridge.begin();
  Serial.begin(9600);
  while (!Serial);
  runCurl();

}

void loop() {
  Serial.println("Looping!");
    runCurl();
}

void runCurl() {
  Process p;        
  p.begin("curl");  
  p.addParameter("-s");
  p.addParameter("-X POST");
  p.addParameter("-H \"Content-Type: application/json\"");
  p.addParameter("-H \"apikey: kepwmQuI3wvtjifH7yt0g2yfnhqTMxl4\"");
  p.addParameter("--data \"apikey: kepwmQuI3wvtjifH7yt0g2yfnhqTMxl4\"");   
  p.addParameter("https://hackathon.tim.it/gcloudvision/v1/images:annotate"); 
  p.run();      

  while (p.available()>0) {
    char c = p.read();
    Serial.print(c);
  }
  Serial.flush();
}
 * 
 * 
 */ 
#include <SPI.h>
#include <WiFiNINA.h>
#include <HttpClient.h>


#include "arduino_secrets.h" 
///////please enter your sensitive data in the Secret tab/arduino_secrets.h
char ssid[] = SECRET_SSID;        // your network SSID (name)
char pass[] = SECRET_PASS;    // your network password (use for WPA, or use as key for WEP)
int keyIndex = 0;            // your network key Index number (needed only for WEP)

int status = WL_IDLE_STATUS;

char server[] = "https://hackathon.tim.it";    

const char kHostname[] = "https://hackathon.tim.it";
const char kPath[] = "/sms/mt";

WiFiClient client;

void setup() {
  Serial.begin(9600);
  while (!Serial) {
  }

  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("Communication with WiFi module failed!");
    while (true);
  }

  String fv = WiFi.firmwareVersion();
  if (fv < WIFI_FIRMWARE_LATEST_VERSION) {
    Serial.println("Please upgrade the firmware");
  }

  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    status = WiFi.begin(ssid, pass);

    delay(10000);
  }
  Serial.println("Connected to wifi");
  printWifiStatus();

  Serial.println("\nStarting connection to server...");
  // if you get a connection, report back via serial:

 
  if (client.connect(server, 80)) {
    Serial.println("connected to server");
    // Make a HTTP request:
    client.println("POST /sms/mt");
    client.println("Content-Type: application/json");
    client.println("apikey: xxxxxxxxxxxxxxxxxxxxxxxxxx");
    
    client.println("{'address' : 'tel:+39xxxxxxxxxxxxxxxxxx', 'message' : 'Hackathon TIM Arduino'}");
    client.println("Host: https://hackathon.tim.it");
    client.println("Connection: close");
    client.println();
  }
}

void loop() {
  // if there are incoming bytes available
  // from the server, read them and print them:
  while (client.available()) {
    char c = client.read();
    Serial.write(c);
  }

  // if the server's disconnected, stop the client:
  if (!client.connected()) {
    Serial.println();
    Serial.println("disconnecting from server.");
    client.stop();

    // do nothing forevermore:
    while (true);
  }
}


void printWifiStatus() {
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}
