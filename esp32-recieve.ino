#include <Arduino.h>

// HardwareSerial to communicate with ESP32-CAM
HardwareSerial espSerial(1);  // UART1 for receiving data from ESP32-CAM (RX: GPIO16, TX: not used)
const int camSerialRX = 19;
const int magneticSensorPin = 23;  // Set to the pin where the magnetic sensor is connected
int lastSensorState = 0;           // Assume the door is closed initially

void setup() {
  Serial.begin(115200);                                 // Debugging output via USB
  espSerial.begin(9600, SERIAL_8N1, camSerialRX, -1);  // Set UART1 baud rate and RX pin (only RX on GPIO9)

  pinMode(magneticSensorPin, INPUT_PULLUP);

  Serial.println("Waiting for data from ESP32-CAM...");
}

void loop() {
  lastSensorState = digitalRead(magneticSensorPin);
  // Check if the door is open or closed
  if (lastSensorState == LOW) {
    // The sensor is activated (door closed)
    Serial.println("Door Closed");
  } else {
    // The sensor is deactivated (door open)
    //Serial.println("Door Open");
  }

  //Serial.println(espSerial.available());
  if (espSerial.available()) {
    String receivedData = espSerial.readStringUntil('\n');  // Read incoming data from ESP32-CAM
    Serial.print("Received: ");
    Serial.println(receivedData);  // Print received data
    //delay(5000);
  }
  delay(500);
}