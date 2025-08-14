#pragma once

#include "esphome/core/component.h"
#include "esphome/components/uart/uart.h"
#include "esphome/components/sensor/sensor.h"

namespace esphome {
namespace usb_reader {

class USBReader : public uart::UARTDevice, public PollingComponent {
 public:
  void loop() override;
  void update() override {}  // No periodic updates needed

  void set_zones_sensor(sensor::Sensor *sensor) { this->zones_sensor_ = sensor; }
  void set_insert_sensor(sensor::Sensor *sensor) { this->insert_sensor_ = sensor; }

 protected:
  sensor::Sensor *zones_sensor_{nullptr};
  sensor::Sensor *insert_sensor_{nullptr};
  std::string buffer_;
};

}  // namespace usb_reader
}  // namespace esphome
