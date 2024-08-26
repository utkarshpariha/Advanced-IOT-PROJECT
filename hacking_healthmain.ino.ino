#include <WiFi.h>
#include <PubSubClient.h>
// #include <TensorFlowLite.h>
// Define your Wi-Fi credentials, Ubidots token, and other constants
#define WIFISSID "Galaxy"
#define PASSWORD "87654321"
#define TOKEN "BBFF-oQY7PYoihiAyaXqzsALIQ2tOykeJtJ"
#define MQTT_CLIENT_NAME "nikutkkus"
#define VARIABLE_LABEL "sensor"
#define DEVICE_LABEL "esp32"
#define SENSOR A0

// #include <tensorflow/lite/micro/all_ops_resolver.h>
// #include <tensorflow/lite/micro/micro_error_reporter.h>
// #include <tensorflow/lite/micro/micro_interpreter.h>
// #include "tensorflow/lite/schema/schema_generated.h"
// #include "tensorflow/lite/version.h"
// #include "cmsis_gcc.h"
// Include your .tflite model file
// #include "your_model(1).tflite"
// #include "C:\Users\parih\.arduinoIDE\hacking_healthmain.ino\utkarsh.tflite"


// void app_main() {
//     tflite::MicroErrorReporter micro_error_reporter;
//     tflite::ErrorReporter* error_reporter = &micro_error_reporter;
    
//     const tflite::Model* model = tflite::GetModel(your_model);
//     if (model == nullptr) {
//         error_reporter->Report("Model not found");
//         return;
//     }

    // // Initialize TensorFlow Lite interpreter and allocate tensors
    // static tflite::MicroInterpreter* interpreter = nullptr;
    // static tflite::AllOpsResolver op_resolver;
    // static const int tensor_arena_size = 2 * 1024;
    // static uint8_t tensor_arena[tensor_arena_size];
    
    // interpreter = new tflite::MicroInterpreter(model, op_resolver, tensor_arena, tensor_arena_size, error_reporter);
    
    // if (interpreter != nullptr) {
    //     interpreter->AllocateTensors();
    // } else {
    //     error_reporter->Report("Interpreter not initialized");
    //     return;
    // }

    // Perform inference with your input data
// 

// Global variables for signal conditioning
float baseline = 0.0;
float filteredValue = 0.0;

// Define a filter object (e.g., a simple moving average filter)
const int filterSize = 10;
float filterValues[filterSize] = {0};
int filterIndex = 0;

char mqttBroker[] = "industrial.api.ubidots.com";
char payload[100];
char topic[150];
char str_sensor[10];

WiFiClient ubidots;
PubSubClient client(ubidots);

void callback(char* topic, byte* payload, unsigned int length) {
// Handle MQTT callback, if needed
char p[length + 1];
memcpy(p, payload, length);
p[length] = NULL;
Serial.write(payload, length);
Serial.println(topic);
}

void reconnect() {
  // Reconnect to MQTT, if disconnected
   while (!client.connected()) {
    Serial.println("Attempting MQTT connection...");
    
    // Attemp to connect
    if (client.connect(MQTT_CLIENT_NAME, TOKEN, "")) {
      Serial.println("Connected");
    } else {
      Serial.print("Failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 2 seconds");
      // Wait 2 seconds before retrying
      delay(2000);

}}}

void setup() {
  Serial.begin(115200);
  WiFi.begin(WIFISSID, PASSWORD);
  pinMode(SENSOR, INPUT);

  // Calculate the baseline
  for (int i = 0; i < filterSize; i++) {
    baseline += analogRead(SENSOR);
    delay(10); // Adjust this delay as needed
  }
  baseline /= filterSize;

  Serial.println();
  Serial.print("Waiting for WiFi...");

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println("");
  Serial.println("WiFi Connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  client.setServer(mqttBroker, 1883);
  client.setCallback(callback);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }

  // Read the sensor value
  int rawValue = analogRead(SENSOR);

  // Apply baseline correction
  float correctedValue = rawValue - baseline;

  // Apply filtering (simple moving average)
  filteredValue -= filterValues[filterIndex];
  filterValues[filterIndex] = correctedValue;
  filteredValue += filterValues[filterIndex];

  filterIndex = (filterIndex + 1) % filterSize;

  // Implement software-based digital filters for noise reduction (e.g., Butterworth filter)

  // Ensure the correct sampling rate (adjust the delay as needed to meet your requirements)

  // Implement data logging for real-time and offline analysis

  // Build the MQTT payload
  sprintf(topic, "%s%s", "/v1.6/devices/", DEVICE_LABEL);
  sprintf(payload, "%s", "");
  sprintf(payload, "{\"%s\":", VARIABLE_LABEL);
  dtostrf(filteredValue, 4, 2, str_sensor);
  sprintf(payload, "%s {\"value\": %s}}", payload, str_sensor);
  Serial.println("Team healthbot your data is publishing on cloud");

  // Publish data to Ubidots
  client.publish(topic, payload);

  client.loop();

  // Print the filtered sensor value to the Serial Plotter

  Serial.print("Filtered Sensor Value: ");
  Serial.println(filteredValue);

  delay(500); // Adjust the delay to control the sampling rate
}

