#include <DHT.h>

#define DHT_PIN   4
#define DHT_TYPE  DHT11
#define MQ_PIN    34

DHT dht(DHT_PIN, DHT_TYPE);

void setup() {
  Serial.begin(115200);
  dht.begin();
  analogReadResolution(12);          // 0-4095
  analogSetPinAttenuation(MQ_PIN, ADC_11db);
  Serial.println("temp_C,hum_pct,mq135_raw");
}

void loop() {
  float t = dht.readTemperature();
  float h = dht.readHumidity();

  // Promedio de 10 muestras para reducir ruido del ADC
  long suma = 0;
  for (int i = 0; i < 10; i++) { suma += analogRead(MQ_PIN); delay(10); }
  int mq = suma / 10;

  if (isnan(t) || isnan(h)) {
    Serial.println("Lectura DHT11 invalida");
  } else if (mq == 0) {
    Serial.println("MQ-135 en cero");
  } else {
    Serial.printf("%.1f,%.1f,%d\n", t, h, mq);
  }
  delay(2000);   // DHT11 no admite lecturas mas rapidas que 1 Hz
}