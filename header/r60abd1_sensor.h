#include "esphome.h"

class R60ABD1Sensor : public Component, public UARTDevice {
 public:
  Sensor *presence_sensor = new Sensor();
  Sensor *motion_sensor = new Sensor();
  Sensor *heartbeat_sensor = new Sensor();
  Sensor *respiratory_sensor = new Sensor();
  Sensor *sleep_quality_sensor = new Sensor();
  Sensor *bed_status_sensor = new Sensor();

  R60ABD1Sensor(UARTComponent *parent) : UARTDevice(parent) {}

  void setup() override {
    // ฟังก์ชันเริ่มต้น
  }

  void loop() override {
    static uint8_t buffer[128];
    static int index = 0;

    while (available()) {
      buffer[index++] = read();
      if (index >= 7 && buffer[index - 2] == 0x54 && buffer[index - 1] == 0x43) {
        processPacket(buffer, index);
        index = 0;
      }
    }
  }

  void processPacket(const uint8_t *bytes, int length) {
    if (length < 7) return;

    // Presence Detection
    if ((bytes[0] == 0x53) && (bytes[1] == 0x59) && (bytes[2] == 0x80) &&
        (bytes[3] == 0x01)) {
      int presence = bytes[6];
      presence_sensor->publish_state(presence);
    }

    // Motion Detection
    if ((bytes[0] == 0x53) && (bytes[1] == 0x59) && (bytes[2] == 0x80) &&
        (bytes[3] == 0x02)) {
      int motion = bytes[6];
      motion_sensor->publish_state(motion);
    }

    // Heartbeat Rate
    if ((bytes[0] == 0x53) && (bytes[1] == 0x59) && (bytes[2] == 0x85) &&
        (bytes[3] == 0x02)) {
      int heartbeat = bytes[6];
      heartbeat_sensor->publish_state(heartbeat);
    }

    // Respiratory Rate
    if ((bytes[0] == 0x53) && (bytes[1] == 0x59) && (bytes[2] == 0x81) &&
        (bytes[3] == 0x02)) {
      int respiratory = bytes[6];
      respiratory_sensor->publish_state(respiratory);
    }

    // Sleep Quality
    if ((bytes[0] == 0x53) && (bytes[1] == 0x59) && (bytes[2] == 0x84) &&
        (bytes[3] == 0x06)) {
      int sleep_quality = bytes[6];
      sleep_quality_sensor->publish_state(sleep_quality);
    }

    // Bed Status
    if ((bytes[0] == 0x53) && (bytes[1] == 0x59) && (bytes[2] == 0x84) &&
        (bytes[3] == 0x01)) {
      int bed_status = bytes[6];
      bed_status_sensor->publish_state(bed_status);
    }
  }
};
