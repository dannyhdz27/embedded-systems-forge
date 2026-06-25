#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>

BLEServer* pServer = nullptr;
BLECharacteristic* proximityChar = nullptr;

const int trigPin = 2;
const int echoPin = 1;
long duration;
int distance;

void setup() {
  Serial.begin(115200);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);

  BLEDevice::init("Daniel_proximity_test");  // Device name here
  pServer = BLEDevice::createServer();

  BLEService* proxService = pServer->createService("180F");

  proximityChar = proxService->createCharacteristic(
    "2A19",
    BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_NOTIFY
  );
  proximityChar->addDescriptor(new BLE2902());

  proxService->start();

  BLEAdvertising* pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->addServiceUUID("180F");
  pAdvertising->start();

  Serial.println("BLE advertising started!");
  digitalWrite(LED_BUILTIN, LOW);
}

void loop() {
  updateDistance();
  digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
  delay(200);
}

void updateDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;

  Serial.print("Distance: ");
  Serial.println(distance);

  proximityChar->setValue(distance);
  proximityChar->notify();
}