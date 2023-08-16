
#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "Mobily_Fiber_2.4G";
const char* password = "C91777A3";
const String url = "http://192.168.100.44/web1/lastV.php";
String payload = "";
int leftPin = 25;
int rightPin = 27;
int forwardPin = 12;
int backwardPin = 14;
int stopPin = 26;
void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  pinMode(leftPin, OUTPUT);
  pinMode(rightPin, OUTPUT);
  pinMode(forwardPin, OUTPUT);
  pinMode(backwardPin, OUTPUT);
  pinMode(stopPin, OUTPUT);
  Serial.println("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.print("OK! IP=");
  Serial.println(WiFi.localIP());

  Serial.print("Fetching " + url + "... ");


}

void loop() {
  HTTPClient http;
  http.begin(url);
  int httpResponseCode = http.GET();
  if (httpResponseCode > 0) {
    Serial.print("HTTP ");
    Serial.println(httpResponseCode);
    payload = http.getString();
    Serial.println();
    Serial.println(payload);
    if(payload == "Forward"){
      digitalWrite(forwardPin, HIGH);
      digitalWrite(backwardPin, LOW);
      digitalWrite(rightPin, LOW);
      digitalWrite(leftPin, LOW);
      digitalWrite(stopPin, LOW);
    }
    else if(payload == "Stop"){
      digitalWrite(forwardPin, LOW);
      digitalWrite(backwardPin, LOW);
      digitalWrite(rightPin, LOW);
      digitalWrite(leftPin, LOW);
      digitalWrite(stopPin, HIGH);
    }
    else if(payload == "Right"){
      digitalWrite(forwardPin, LOW);
      digitalWrite(backwardPin, LOW);
      digitalWrite(rightPin, HIGH);
      digitalWrite(leftPin, LOW);
      digitalWrite(stopPin, LOW);
    }
    else if(payload == "Left"){
      digitalWrite(forwardPin, LOW);
      digitalWrite(backwardPin, LOW);
      digitalWrite(rightPin, LOW);
      digitalWrite(leftPin, HIGH);
      digitalWrite(stopPin, LOW);
    }
    else if(payload == "Backward"){
      digitalWrite(forwardPin, LOW);
      digitalWrite(backwardPin, HIGH);
      digitalWrite(rightPin, LOW);
      digitalWrite(leftPin, LOW);
      digitalWrite(stopPin, LOW);
    }
  }
  else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
    Serial.println(":-(");
  }
  delay(100);
}

