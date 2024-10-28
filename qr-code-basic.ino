#include <Arduino.h>
#include <esp_camera.h>
#include <ESP32QRCodeReader.h>

ESP32QRCodeReader reader(CAMERA_MODEL_AI_THINKER);

//const int redPin = 33;
const int goodPin = 15;
const int badPin = 14;
#define TX_PIN 12

void sendToESP32(const char* data) {
  Serial1.println(data); // Send the data via Serial to ESP-WROOM-32
}

void onQrCodeTask(void *pvParameters)
{
  struct QRCodeData qrCodeData;
  digitalWrite(goodPin, LOW);
  digitalWrite(badPin, LOW);
  while (true){
    if (reader.receiveQrCode(&qrCodeData, 100))
    {
      Serial.println("Found QRCode");
      if (qrCodeData.valid)
      {
        digitalWrite(goodPin, HIGH);
        Serial.print("Payload: ");
        Serial.println((const char *)qrCodeData.payload);
        sendToESP32((const char *)qrCodeData.payload);
        delay(5000);
        digitalWrite(goodPin, LOW);
        break;
      }
      else
      {
        Serial.print("Invalid: ");
        Serial.println((const char *)qrCodeData.payload);
        sendToESP32("Invalid Data");
        for (int i = 0; i <2; i++){
          digitalWrite(badPin, HIGH);
          delay(250);
          digitalWrite(badPin, LOW);
          delay(250);
        }
      }
    }
    vTaskDelay(100 / portTICK_PERIOD_MS);
  }
  xTaskCreate(onQrCodeTask, "onQrCode", 4 * 1024, NULL, 4, NULL);
}

void setup()
{
  pinMode(goodPin, OUTPUT);
  pinMode(badPin, OUTPUT);
  Serial.begin(115200);
  Serial1.begin(9600, SERIAL_8N1, -1, TX_PIN);  // Only TX on GPIO12 (to ESP-WROOM-32 RX)

  Serial.println();
  reader.setup();

  Serial.println("Setup QRCode Reader");

  reader.beginOnCore(1);

  Serial.println("Begin on Core 1");

  xTaskCreate(onQrCodeTask, "onQrCode", 4 * 1024, NULL, 4, NULL);
}

void loop()
{
  //delay(2000);
}