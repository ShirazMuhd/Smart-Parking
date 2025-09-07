#include <WiFi.h>
#include <HTTPClient.h>

#define WIFI_SSID "network46"
#define Wifi_PASSWORD "9539056214"

int parking1 = digitalRead(14); 
int parking2 = digitalRead(34);
int parking3 = digitalRead(27); 
int parking4 = digitalRead(35);


void setup()
{
  pinMode(2, OUTPUT);
  pinMode(34, INPUT);
  pinMode(35, INPUT);
  Serial.begin(9600);
  WiFi.begin(WIFI_SSID, Wifi_PASSWORD);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.println("Connecting to Wi-Fi...");
    blink();
  }

  Serial.println("Connected to Wifi!");
  
 
}
 
void loop()
{
  if (digitalRead(14) != parking1 || digitalRead(27) != parking3 || digitalRead(34) != parking2 || digitalRead(35) != parking4)
  {
    Serial.println("data changed ");
    parking1 = digitalRead(14);
    parking3 = digitalRead(27);
    parking2 = digitalRead(34);
    parking4 = digitalRead(35);
    String query = "Slot_1=" + String(digitalRead(14)) + "&Slot_3=" + String(digitalRead(27)) + "&Slot_2=" + String(digitalRead(34)) + "&Slot_4=" + String(digitalRead(35));
    String url = "http://192.168.43.147:3001/updateParking?" + query;
    sendHttp(url);
  }
  delay(1000);
};

void sendHttp(String URL)
{
  HTTPClient http;
  http.begin(URL);

  int httpCode = http.GET();

  if (httpCode > 0)
  {
    String response = http.getString();
    Serial.println(response);
  }
  else{
    Serial.println("Error sending POST request");
  }

  // Clean up
  http.end();
}

void blink()
{
  digitalWrite(2, LOW);
  delay(500);
  digitalWrite(2, HIGH);
  delay(500);
}
