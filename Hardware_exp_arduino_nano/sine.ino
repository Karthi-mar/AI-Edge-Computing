#include <Arduino.h>
#include <ArduTFLite.h> // Using ArduTFLite for TensorFlow Lite inference
#include "tensorflow/lite/micro/micro_interpreter.h"
#include "tensorflow/lite/micro/all_ops_resolver.h"
#include "tensorflow/lite/schema/schema_generated.h"
#include "sinewave_model.h" // Include the generated TFLite model files

// Define tensor arena size
constexpr int kTensorArenaSize = 2 * 1024;
uint8_t tensor_arena[kTensorArenaSize];

// TensorFlow Lite model variables
tflite::MicroInterpreter* interpreter;
const tflite::Model* model;
tflite::AllOpsResolver resolver;

void setup() {
  Serial.begin(115200);
  while (!Serial);  // Wait for the Serial Monitor to open (only necessary for some boards)

  // Load TensorFlow Lite model
  model = tflite::GetModel("sinewave_model");
  if (model->version() != TFLITE_SCHEMA_VERSION) {
    Serial.println("Model schema version mismatch!");
    while (1);
  }

  static tflite::MicroInterpreter static_interpreter(model, resolver, tensor_arena, kTensorArenaSize);
  interpreter = &static_interpreter;

  if (interpreter->AllocateTensors() != kTfLiteOk) {
    Serial.println("AllocateTensors() failed");
    while (1);
  }
}


void loop() {
  for (float input_value = 0.0; input_value <= 2 * PI; input_value += 0.1) {
    float* input = interpreter->input(0)->data.f;
    *input = input_value;

    if (interpreter->Invoke() != kTfLiteOk) {
      Serial.println("Invoke() failed!");
      return;
    }

    float* output = interpreter->output(0)->data.f;

    Serial.print("Input (radians): ");
    Serial.print(input_value);
    Serial.print(" Predicted Sine Output: ");
    Serial.println(*output);

    Serial.print("Actual Sine: ");
    Serial.println(sin(input_value));

    delay(500);
}
}