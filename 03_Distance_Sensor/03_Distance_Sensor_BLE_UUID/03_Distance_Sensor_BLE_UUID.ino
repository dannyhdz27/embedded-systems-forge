#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>

/*
  Custom UUIDs

  These replace the standard Battery Service UUIDs:
  - 180F = Battery Service
  - 2A19 = Battery Level

  Since this project is measuring distance, we define our own
  custom service and characteristic UUIDs.
*/
#define DISTANCE_SERVICE_UUID "7e3a6d30-8b9e-4d4e-be5c-20d1b7c57f10"
#define DISTANCE_CHAR_UUID    "7e3a6d31-8b9e-4d4e-be5c-20d1b7c57f10"


BLEServer* pServer = nullptr;

BLECharacteristic* proximityChar = nullptr;


const int trigPin = 2;
const int echoPin = 1;

// Stores the echo pulse duration in microseconds
long duration;

// Stores the calculated distance in centimeters
int distance;

void setup() {
  // Start Serial communication for debugging on the Serial Monitor
  Serial.begin(115200);

  // Configure the ultrasonic sensor pins
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT);  

  // Configure built-in LED as an output
  pinMode(LED_BUILTIN, OUTPUT);

  
    //Initialize BLE device.
  BLEDevice::init("distance_sensor_test");

  // Create a BLE server on the ESP32
  pServer = BLEDevice::createServer();

  /*
    Create a BLE service using a custom UUID.
    A service groups related BLE data.
    In this case, the service represents our distance sensor.
  */
  BLEService* proxService = pServer->createService(DISTANCE_SERVICE_UUID);

  /*
    Create a BLE characteristic using a custom UUID.

    A characteristic holds a specific value.
    In this case, it holds the measured distance.

    PROPERTY_READ:
      Allows the phone to manually read the current value.

    PROPERTY_NOTIFY:
      Allows the ESP32 to automatically send updated values
      to the phone when the distance changes.
  */
  proximityChar = proxService->createCharacteristic(
    DISTANCE_CHAR_UUID,
    BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_NOTIFY
  );

  /*
    Add BLE2902 descriptor.

    This enables notifications so that a phone app like nRF Connect
    can subscribe to live updates.
  */
  proximityChar->addDescriptor(new BLE2902());

  // Start the BLE service
  proxService->start();

  /*
    Start advertising.

    Advertising means the ESP32 announces itself so that
    the phone can find it during a BLE scan.
  */
  BLEAdvertising* pAdvertising = BLEDevice::getAdvertising();

  // Advertise the custom distance sensor service UUID
  pAdvertising->addServiceUUID(DISTANCE_SERVICE_UUID);

  // Helps make the device more visible during scanning
  pAdvertising->setScanResponse(true);

  // Start BLE advertising
  BLEDevice::startAdvertising();

  Serial.println("BLE advertising started!");

  digitalWrite(LED_BUILTIN, LOW);
}

void loop() {
  // Measure distance and send it over BLE
  updateDistance();

  // Toggle built-in LED to show that the program is running
  digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));

  // Wait 200 ms before next measurement
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

  // Convert the distance into a string. Sending it as text makes it easier to read in nRF Connect.
  String distanceString = String(distance) + " cm";

 
   // Store the distance string in the BLE characteristic.
  
  proximityChar->setValue(distanceString.c_str());

  proximityChar->notify();
}