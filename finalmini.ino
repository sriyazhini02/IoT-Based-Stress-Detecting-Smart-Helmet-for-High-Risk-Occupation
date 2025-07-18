#include <Wire.h>
#include "MAX30100_PulseOximeter.h"
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <SoftwareSerial.h>
#include <DHT.h>

// Define Pins
#define RX_PIN 12  // SIM800C RX 
#define TX_PIN 11  // SIM800C TX 
#define DHTPIN 2   // DHT11 Sensor connected to Pin 2
#define FALL_THRESHOLD 3.5  // Adjust this based on sensitivity
#define DHTTYPE DHT11  // Define DHT sensor type
#define GAS_SENSOR_PIN A0  // MQ135 Gas Sensor connected to A0
#define GAS_THRESHOLD 600  // Adjust based on calibration


// Initialize Components
SoftwareSerial sim800c(TX_PIN, RX_PIN);  // TX, RX
PulseOximeter pox;
Adafruit_MPU6050 mpu;
DHT dht(DHTPIN, DHTTYPE);

uint32_t lastBeat = 0;
float BPM = 0;
bool fallDetected = false;

// Function to send SMS
void sendSMS(String message) {
    Serial.println("Sending SMS...");
    sim800c.println("AT+CMGF=1");  
    delay(100);
    sim800c.println("AT+CMGS=\"+919489361959\"");  
    delay(100);
    sim800c.print(message);
    delay(100);
    sim800c.write(26); 
    delay(1000);
    Serial.println("Message Sent!");
}

// Pulse Oximeter Callback
void onBeatDetected() {
    Serial.println("Beat detected!");
}

void setup() {
    Serial.begin(9600);
    sim800c.begin(9600);
    Wire.begin();

    Serial.println("Initializing...");

    // Initialize MAX30100
    if (!pox.begin()) {
        Serial.println("FAILED to initialize MAX30100!");
    } else {
        Serial.println("MAX30100 Initialized.");
    }
    pox.setOnBeatDetectedCallback(onBeatDetected);

    // Initialize MPU6050
    if (!mpu.begin()) {
        Serial.println("Failed to initialize MPU6050!");
    } else {
        Serial.println("MPU6050 Initialized.");
    }

    // Initialize DHT11
    dht.begin();
    Serial.println("DHT11 Initialized.");

    Serial.println("SIM800C Initializing...");
    delay(1000);
}

void loop() {
    // Read Temperature & Humidity
    float temp = dht.readTemperature();
    float humidity = dht.readHumidity();
    
    int gasValue = analogRead(GAS_SENSOR_PIN);
    Serial.print("🛢 Gas Value: ");
    Serial.println(gasValue);


    if (isnan(temp) || isnan(humidity)) {
        Serial.println("⚠️ Failed to read from DHT sensor!");
    } else {
        Serial.print("🌡 Temperature: ");
        Serial.print(temp);
        Serial.print("°C  |  💧 Humidity: ");
        Serial.print(humidity);
        Serial.println("%");
    }
    

    // Read Pulse Oximeter
    pox.update();
    BPM = pox.getHeartRate();

    

    // Check BPM Threshold
    if (BPM > 120 || BPM < 50) {
        Serial.println("⚠️ Stress Detected! Sending Alert SMS...");
        sendSMS("Stress Detected! Urgent Help Needed! Location: https://maps.google.com/?q=<LAT>,<LON>");
        delay(5000);  // Delay to avoid spam
    }

    // Read MPU6050 Acceleration
    sensors_event_t a, g, temp_sensor;
    mpu.getEvent(&a, &g, &temp_sensor);

    // Check Fall Detection
    float acceleration = sqrt(a.acceleration.x * a.acceleration.x +
                              a.acceleration.y * a.acceleration.y +
                              a.acceleration.z * a.acceleration.z);

    if (acceleration > FALL_THRESHOLD) {
        Serial.println("🚨 Fall Detected! Sending Emergency SMS...");
        sendSMS("Fall Detected! Urgent Help Needed! Location: https://maps.google.com/?q=<LAT>,<LON>");
        delay(5000);  // Delay to avoid spam
    }
    if (gasValue > GAS_THRESHOLD) {
    Serial.println("⚠️ High Toxic Gas Level Detected! Sending Alert SMS...");
    sendSMS("Toxic Gas Level High! Urgent Help Needed! Location: https://maps.google.com/?q=<LAT>,<LON>");
    delay(5000);  // Delay to avoid spam



    delay(5000); // Main loop delay
}  
}