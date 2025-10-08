#include <WiFi.h>
#include <HTTPClient.h>

#define WIFI_SSID "GNXS-39E458"
#define Wifi_PASSWORD "Pann_123"

int parking1 = digitalRead(5); 
int parking2 = digitalRead(18);
int parking3 = digitalRead(19); 
int parking4 = digitalRead(21);


void setup()
{
  pinMode(2, OUTPUT);
  pinMode(5, INPUT);
  pinMode(18, INPUT);
  pinMode(19, INPUT);
  pinMode(21, INPUT);
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
  if (digitalRead(5) != parking1 || digitalRead(13) != parking3 || digitalRead(18) != parking2 || digitalRead(21) != parking4)
  {
    Serial.println("data changed ");
    parking1 = digitalRead(5);
    parking3 = digitalRead(13);
    parking2 = digitalRead(18);
    parking4 = digitalRead(21);
    String query = "Slot_1=" + String(digitalRead(5)) + "&Slot_3=" + String(digitalRead(19)) + "&Slot_2=" + String(digitalRead(18)) + "&Slot_4=" + String(digitalRead(21));
    String url = "http://parking-server-8sj1.onrender.com/updateParking?" + query;
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
