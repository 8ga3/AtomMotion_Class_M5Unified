#include <Arduino.h>
#include <M5Unified.h>
#include <AtomMotion_Class.hpp>

m5::AtomMotion Motion;
bool moving = false;
xSemaphoreHandle CtlSemaphore;

void GetStatus() {
  Serial.printf("Servo Channel %d: %d \n", 1, Motion.ReadServoPulse(1));
  Serial.printf("Servo Channel %d: %d \n", 3, Motion.ReadServoPulse(3));
}

void TaskMotion(void *pvParameters) {
  const std::uint16_t CENTER = 1500;
  const std::uint16_t CHx_MAX = 290;

  while (1) {
    if (moving) {
      Motion.SetServoPulse(1, CENTER - CHx_MAX);
      Motion.SetServoPulse(3, CENTER + CHx_MAX);
    }
    else {
      Motion.SetServoPulse(1, CENTER);
      Motion.SetServoPulse(3, CENTER);
    }

    GetStatus();
    vTaskDelay(1000 / portTICK_RATE_MS);
  }
}

void setup() {
  auto cfg = M5.config();
  M5.begin(cfg);

  vSemaphoreCreateBinary(CtlSemaphore);
  xTaskCreatePinnedToCore(TaskMotion, "TaskMotion", 4096, NULL, 2, NULL, 0);
}

void loop() {
  delay(1);
  M5.update();
  if (M5.BtnA.wasPressed()) {
    moving = !moving;
  }
}
