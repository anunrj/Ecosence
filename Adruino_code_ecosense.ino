

#include <WiFiClientSecure.h>
#include<WiFi.h>
#include <PubSubClient.h> // install with Library Manager, I used v2.6.0
#include<DHT.h>
#include <WebServer.h>
const char* ssid = "Galaxy Note20 5G8a40";
const char* password = "efjh7617";

const char* awsEndpoint = "a1rhvl16narn7t-ats.iot.us-east-1.amazonaws.com"; //AWS IoT Core--> Settings (Device data endpoint)

// xxxxxxxxxx-certificate.pem.crt
static const char certificate_pem_crt[] PROGMEM = R"KEY(
-----BEGIN CERTIFICATE-----
MIIDWjCCAkKgAwIBAgIVAIFl07gCiqeGXl5B7SyPxUfwiPwsMA0GCSqGSIb3DQEB
CwUAME0xSzBJBgNVBAsMQkFtYXpvbiBXZWIgU2VydmljZXMgTz1BbWF6b24uY29t
IEluYy4gTD1TZWF0dGxlIFNUPVdhc2hpbmd0b24gQz1VUzAeFw0yNDA5MjIxMzU1
NDRaFw00OTEyMzEyMzU5NTlaMB4xHDAaBgNVBAMME0FXUyBJb1QgQ2VydGlmaWNh
dGUwggEiMA0GCSqGSIb3DQEBAQUAA4IBDwAwggEKAoIBAQDCsi54Bl2ypV6SLycL
TQWoGwwT2AWhYjAUurCBXhzUFsY1OCX8u0WfvZf7YQTj9mby3OfC2DoRkYiv3KjT
Q2nPk7U+m2RGx24I0vUlhjurgyov0ItS5qAYhU6y8z0fn4Ekn1VyZSMbxdIZjs/P
Bd39ZEspe7Ns527neLntNwiQvKgX6eJO5ruEYU3jyVGP/Cgo9jdD3px0T5QeOebF
bpyk7BBDcU+Cdv3Q3v6dNpBGf4m0/PYiDl5YrWMHBrd1jRfY56L03v9Iigmj2quH
xznPoCWAElomVVTox4wVB7j5DXO5caI6Uo+PUFLyVlqU75UaaUBVvsr7Z0BkVW3q
RcVvAgMBAAGjYDBeMB8GA1UdIwQYMBaAFM0mW8pnkvhFdmEgNSEq7J3mVKoFMB0G
A1UdDgQWBBTtPspNpV73yN5q/BvMkCZrVokjxzAMBgNVHRMBAf8EAjAAMA4GA1Ud
DwEB/wQEAwIHgDANBgkqhkiG9w0BAQsFAAOCAQEASnmzK4KYaYhJ0NzBO8WNomQW
qML7JczXAhpdOnBsg8MgX5IZdL0WtufHULtxNBsQ9+gMRigkBUJD2IC6mcwZkXwb
0N4s1+j01gQqsBKjnyaWZq2f2xbJy9ZqE6oGDj4lLHirfqoA6j6Cd0doenistC8x
KoaEA5DiMgyuv2ZevqtmItU9KjZb2U3UDxsuLEjp/fVaqkqtIWmaI2u/Ra9Jj2eg
PShNYC8FVSRxjAz/QC7BmqImWwsbzW4gtjndUwb5pdsUswe85W2wTwXxHhAOabDu
js0DdEcMAgs7kfUac9r5uEnR8mUwtLzLtmVuGBHIwsqZHaGzB/8FfPf2Afr8nQ==
-----END CERTIFICATE-----
)KEY";

// xxxxxxxxxx-private.pem.key
static const char private_pem_key[] PROGMEM = R"KEY(
-----BEGIN RSA PRIVATE KEY-----
MIIEpQIBAAKCAQEAwrIueAZdsqVeki8nC00FqBsME9gFoWIwFLqwgV4c1BbGNTgl
/LtFn72X+2EE4/Zm8tznwtg6EZGIr9yo00Npz5O1PptkRsduCNL1JYY7q4MqL9CL
UuagGIVOsvM9H5+BJJ9VcmUjG8XSGY7PzwXd/WRLKXuzbOdu53i57TcIkLyoF+ni
Tua7hGFN48lRj/woKPY3Q96cdE+UHjnmxW6cpOwQQ3FPgnb90N7+nTaQRn+JtPz2
Ig5eWK1jBwa3dY0X2Oei9N7/SIoJo9qrh8c5z6AlgBJaJlVU6MeMFQe4+Q1zuXGi
OlKPj1BS8lZalO+VGmlAVb7K+2dAZFVt6kXFbwIDAQABAoIBAQCcc0AiFMOARaCs
CZXvX9I21p0q6QEFQPhv/+DL5At4ZmCZ7WehIf99sIWLa9fZM2xgpiDakpR+/5p9
7uv+8AH72q7fA1FeCu2hy5tQrwAN/5WL3KHIWSi265Bk/k7UtYC6JAsupJTEwX7m
KLtWmVlcQBah3BQ/Y+3btUh6lSmd24Pd+Hk2AIhuYksp3J+8JI/J+e/AFaBlB90y
LkgJJaJj6ESkKQXusIcyRti80EpbdN8tjaiF/uFfLBDXKdcCNU7tNFdP/3mXm372
OJGLAVUmdp4AOxRv216Ue7tfWJgOowgzpW0JfUQIbAymsJ1Jn+QrhYGQYewPcMnO
civqPmdxAoGBAPACjPa7Bn+ruWP9oBWLhv14rGTZdE6lqbe8EH/46EMri+KmVUEC
yG7ESG1Gm2aBp08p/wz7fYNfJZqMJVmm/ktiNFKj8RKDcAtPMXq9N/gViQRLWJdI
+9EsgUXeebp/we2ivg1KL3Y7nnA8N1C1P7KPJ0GhlvLZejbNUifRXctZAoGBAM+q
yV7U+1oLOi00f6qucubdLVUWNaBykpSl45rYOOKjGGWDpheINfrUlBBu8Mzf5AOF
4PZolln6+hUB1LFVupO7b2Cb37zBp5M2goHSraDNH2fpT2boVjE9DF/a4l28UcQm
4YuFwp5BUwpUo+5uhRMB0lDO52YGtZmtMu4l9iYHAoGAd88eJRBJdzP28KYr4nVr
Jl612AYBHD1wUkqsBeXvs5AqXTLg/fnwqfKLoRkM/AeeyFLTgdyM1CaL8/Eft/g3
mtPkAJjb/3zjUpHuxjFsngfKBP3DtIl3Qvyvb3xWUbXyzbhenO26cY/jUG2Ow1gm
+vChDQ8n9gSAEJk/+KZ35skCgYEAlp76+2ti+4ZVJeCEEJoDAOu/K422S6+OHX7M
vMzDRa6hzU9VMpA7BrkUw26T/SUOzndWGaL2GkFtDbuMNytE7k3ulJW6C8Ax+RZ6
Rgs2oADnHIkebDdr/L6YsRWjRfWHIMxKntXfuMUMo9uMIy3KG2Ug1DedomSPZu02
mYCzLhUCgYEAmkq1u+HCsVxVMl9vgDKaUKYUhGIlYXqwunQN+niWlrr/xcBYG+E/
T1ha7qpBxVjb9cMln1GVht1J4If0RAxuxW3VmvBncO1X5kedgsMQn3IRp5STJ0k2
huf7DH+h/Q74ScE97T64QQsqReD6zMnH9vH/7X8UbIRrkUl/fIkpYyU=
-----END RSA PRIVATE KEY-----

)KEY";

/* root CA found at:
  https://www.amazontrust.com/repository/AmazonRootCA1.pem
  fungible between regions, I dont care if you use mine below or paste in your own.
*/
static const char rootCA[] PROGMEM = R"EOF(
-----BEGIN CERTIFICATE-----
MIIDQTCCAimgAwIBAgITBmyfz5m/jAo54vB4ikPmljZbyjANBgkqhkiG9w0BAQsF
ADA5MQswCQYDVQQGEwJVUzEPMA0GA1UEChMGQW1hem9uMRkwFwYDVQQDExBBbWF6
b24gUm9vdCBDQSAxMB4XDTE1MDUyNjAwMDAwMFoXDTM4MDExNzAwMDAwMFowOTEL
MAkGA1UEBhMCVVMxDzANBgNVBAoTBkFtYXpvbjEZMBcGA1UEAxMQQW1hem9uIFJv
b3QgQ0EgMTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBALJ4gHHKeNXj
ca9HgFB0fW7Y14h29Jlo91ghYPl0hAEvrAIthtOgQ3pOsqTQNroBvo3bSMgHFzZM
9O6II8c+6zf1tRn4SWiw3te5djgdYZ6k/oI2peVKVuRF4fn9tBb6dNqcmzU5L/qw
IFAGbHrQgLKm+a/sRxmPUDgH3KKHOVj4utWp+UhnMJbulHheb4mjUcAwhmahRWa6
VOujw5H5SNz/0egwLX0tdHA114gk957EWW67c4cX8jJGKLhD+rcdqsq08p8kDi1L
93FcXmn/6pUCyziKrlA4b9v7LWIbxcceVOF34GfID5yHI9Y/QCB/IIDEgEw+OyQm
jgSubJrIqg0CAwEAAaNCMEAwDwYDVR0TAQH/BAUwAwEB/zAOBgNVHQ8BAf8EBAMC
AYYwHQYDVR0OBBYEFIQYzIU07LwMlJQuCFmcx7IQTgoIMA0GCSqGSIb3DQEBCwUA
A4IBAQCY8jdaQZChGsV2USggNiMOruYou6r4lK5IpDB/G/wkjUu0yKGX9rbxenDI
U5PMCCjjmCXPI6T53iHTfIUJrU6adTrCC2qJeHZERxhlbI1Bjjt/msv0tadQ1wUs
N+gDS63pYaACbvXy8MWy7Vu33PqUXHeeE6V/Uq2V8viTO96LXFvKWlJbYK8U90vv
o/ufQJVtMVT8QtPHRh8jrdkPSHCa2XV4cdFyQzR1bldZwgJcJmApzyMZFo6IQ6XU
5MsI+yMRQ+hDKXJioaldXgjUkK642M4UwtBV8ob2xJNDd2ZhwLnoQdeXeGADbkpy
rqXRfboQnoZsG4q5WTP468SQvvG5
-----END CERTIFICATE-----
)EOF";

#define DHTPIN 5
#define DHTTYPE DHT22
#define LIGHT_PIN 2
const int soilMoisturePin = 32;
const int ldrPin = 34;  // GPIO pin connected to the LDR
WebServer server(80); // HTTP server on port 80

DHT dht(DHTPIN, DHTTYPE);

WiFiClientSecure wiFiClient;
void msgReceived(char* topic, byte* payload, unsigned int len);
PubSubClient pubSubClient(awsEndpoint, 8883, msgReceived, wiFiClient); 

void setup() {
  Serial.begin(115200); delay(50); Serial.println();
  pinMode(LIGHT_PIN, OUTPUT);  
  //pinMode(ldrPin, INPUT);
  analogSetAttenuation(ADC_11db);
  Serial.println("ESP32 AWS IoT DHT22 and soil moisture Example");
  Serial.printf("SDK version: %s\n", ESP.getSdkVersion());

  Serial.print("Connecting to "); Serial.print(ssid);
  WiFi.begin(ssid, password);
  WiFi.waitForConnectResult();
  Serial.print(", WiFi connected, IP address: "); Serial.println(WiFi.localIP());

  wiFiClient.setCACert(rootCA);
  wiFiClient.setCertificate(certificate_pem_crt);
  wiFiClient.setPrivateKey(private_pem_key);
  dht.begin();

  // Start Web Server
  server.on("/", handleRoot);
  server.on("/data", handleSensorData);
  server.begin();
}

unsigned long lastPublish;
int msgCount;

void loop() {

  pubSubCheckConnect();
  server.handleClient();

   //If you need to increase buffer size, you need to change MQTT_MAX_PACKET_SIZE in PubSubClient.h
   char sensorData[150];

  float temperature =  dht.readTemperature(); //fake number range, adjust as you like
  float humidity =  dht.readHumidity();
  float sensorValue = analogRead(soilMoisturePin);
  float analogValue = analogRead(ldrPin);
  
  float lightValue = map(analogValue, 0, 4095, 0, 100); // Scale to a 0-100 range
  
  float moisturePercent = map(sensorValue, 3500, 500, 0, 100);
  

   if (isnan(temperature) || isnan(humidity)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  

  
  //long float format, takes up a lot of the allocated char buffer
  // sprintf(fakeData,  "{\"uptime\":%lu,\"temp\":%f,\"humid\":%f}", millis() / 1000, var1, var2);
  
  //shorter float format, saves space, makes AWS services slightly easier
  sprintf(sensorData,  "{\"uptime\":%lu,\"temp\":%.0f,\"humid\":%.0f,\"soil_moisture\":%.0f,\"light_intensity\":%.0f}", millis() / 1000, temperature, humidity,moisturePercent,lightValue);
 


  if (millis() - lastPublish > 10000) {
  boolean rc = pubSubClient.publish("outTopic", sensorData);
    Serial.print("Published, rc="); Serial.print( (rc ? "OK: " : "FAILED: ") );
    Serial.println(sensorData);
    lastPublish = millis();

    
  }
  if (lightValue < 30) {
    digitalWrite(LIGHT_PIN, HIGH);  // Turn on light
   // Serial.println("Light intensity low, turning ON light.");
  } else {
    digitalWrite(LIGHT_PIN, LOW);   // Turn off light
    //Serial.println("Light intensity sufficient, turning OFF light.");
  }
}
void handleRoot() {
  String html = "<!DOCTYPE html><html><head><style>";
  html += "body { font-family: Arial, sans-serif; background-image: url('https://images.unsplash.com/photo-1501004318641-b39e6451bec6');";
  html += "background-size: cover; background-position: center; color: #333; margin: 0; padding: 0;";
  html += "display: flex; justify-content: center; align-items: flex-start; height: 100vh; padding-top: 20px; }";

  html += ".main-container { width: 100%; max-width: 400px; text-align: center; background-color: rgba(255, 255, 255, 0.85);";
  html += "padding: 20px; border-radius: 10px; box-shadow: 0px 0px 15px rgba(0, 0, 0, 0.1); position: relative; }";

  html += ".header { font-size: 28px; color: #0073e6; margin-bottom: 20px; text-shadow: 1px 1px 3px rgba(0, 0, 0, 0.2); }";

  //html += ".logo { position: absolute; top: 10px; left: 10px; width: 50px; height: 50px; border-radius: 50%; }";

  html += "#data { font-size: 18px; color: #333; line-height: 1.6; text-align: left; }";

  html += ".data-item { display: flex; align-items: center; justify-content: space-between; padding: 10px 0; font-size: 1.3rem; }";

  html += ".data-item .label { display: flex; align-items: center; }";
  html += ".icon { margin-right: 8px; font-size: 1.5rem; color: #0073e6; }";

  html += "</style>";
  
  // Font Awesome for icons
  html += "<script src='https://cdnjs.cloudflare.com/ajax/libs/font-awesome/5.15.4/js/all.min.js' crossorigin='anonymous'></script>";
  html += "</head><body><div class='main-container'>";
  
  // Logo
  //html += "<img src='data:logo/jpeg;base64,BASE64_ENCODED_STRING_HERE' alt='Logo' class='logo'>"; // replace with actual Base64 string
  
  // Header
  html += "<div class='header'>Ecosense PolyHouse 1</div>";
  html += "<div id='data'>";

  // Temperature section
  html += "<div class='data-item'><div class='label'><i class='fas fa-thermometer-half icon'></i><strong>Temperature:</strong></div>";
  html += "<span id='temperature'>Loading...</span> &deg;C</div>";

  // Humidity section
  html += "<div class='data-item'><div class='label'><i class='fas fa-tint icon'></i><strong>Humidity:</strong></div>";
  html += "<span id='humidity'>Loading...</span> %</div>";

  // Soil Moisture section
  html += "<div class='data-item'><div class='label'><i class='fas fa-water icon'></i><strong>Soil Moisture:</strong></div>";
  html += "<span id='moisture'>Loading...</span> %</div>";

  // Light Intensity section
  html += "<div class='data-item'><div class='label'><i class='fas fa-lightbulb icon'></i><strong>Light Intensity:</strong></div>";
  html += "<span id='light'>Loading...</span> %</div>";
  
  html += "</div></div>";
  
  // JavaScript for data fetching
  html += "<script>";
  html += "setInterval(() => { fetch('/data').then(res => res.json()).then(data => {";
  html += "document.getElementById('temperature').innerHTML = `${data.temp}`;";
  html += "document.getElementById('humidity').innerHTML = `${data.humid}`;";
  html += "document.getElementById('moisture').innerHTML = `${data.soil_moisture}`;";
  html += "document.getElementById('light').innerHTML = `${data.light_intensity}`;";
  html += "}); }, 5000);";
  html += "</script></body></html>";

  server.send(200, "text/html", html);
}





void handleSensorData() {
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();
  float soilMoisture = analogRead(soilMoisturePin);
  float lightIntensity = analogRead(ldrPin);
  
  String jsonData = "{\"temp\":" + String(temperature) +
                    ",\"humid\":" + String(humidity) +
                    ",\"soil_moisture\":" + String(map(soilMoisture, 3500, 500, 0, 100)) +
                    ",\"light_intensity\":" + String(map(lightIntensity, 0, 4095, 0, 100)) + "}";
                    
  server.send(200, "application/json", jsonData);
}

void msgReceived(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message received on "); Serial.print(topic); Serial.print(": ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}

void pubSubCheckConnect() {
  if ( ! pubSubClient.connected()) {
    Serial.print("PubSubClient connecting to: "); Serial.print(awsEndpoint);
    while ( ! pubSubClient.connected()) {
      Serial.print(".");
      pubSubClient.connect("ESPthingXXXX");
      delay(1000);
    }
    Serial.println(" connected");
    pubSubClient.subscribe("inTopic");
  }
  pubSubClient.loop();
}


