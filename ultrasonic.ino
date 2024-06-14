#include <WiFi.h>
#include <HTTPClient.h>

// Masukkan SSID dan Password WiFi Anda
const char* ssid = "WIJAYA 2A";
const char* password = "wijayahebat";

// URL server
const char* serverName = "http://localhost:5000/data";

// Definisi pin untuk HC-SR04
const int trigPin = 5;
const int echoPin = 18;

// Variabel untuk menyimpan waktu
long duration;
float distance;

void setup() {
  Serial.begin(115200);
  
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  // Menghubungkan ke WiFi
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Menghubungkan ke WiFi...");
  }
  Serial.println("Terhubung ke WiFi");
}

void loop() {
  // Mengambil jarak dari sensor ultrasonik
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  duration = pulseIn(echoPin, HIGH);
  distance = (duration * 0.034) / 2;
  
  // Menampilkan jarak pada Serial Monitor
  Serial.print("Jarak: ");
  Serial.print(distance);
  Serial.println(" cm");
  
  // Membuat HTTP POST request
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    
    http.begin(serverName);
    http.addHeader("Content-Type", "application/json");
    
    String httpRequestData = "{\"distance\":\"" + String(distance) + "\"}";
    
    int httpResponseCode = http.POST(httpRequestData);
    
    if (httpResponseCode > 0) {
      String response = http.getString();
      Serial.println(httpResponseCode);
      Serial.println(response);
    } else {
      Serial.print("Error on sending POST: ");
      Serial.println(httpResponseCode);
    }
    
    http.end();
  } else {
    Serial.println("Error in WiFi connection");
  }
  
  delay(10000); // Tunggu 10 detik sebelum mengirim data lagi
}
