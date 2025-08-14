#pragma once

#include "esphome/core/component.h"
#include "esphome/components/usb_uart/usb_uart.h"
#include "esphome/components/sensor/sensor.h"
#include <string>

namespace esphome {
namespace usb_reader {

class USBReader : public Component {
 public:
  void set_usb_channel(usb_uart::USBUartChannel *usb_channel) { this->usb_channel_ = usb_channel; }
  void set_zones_sensor(sensor::Sensor *sensor) { this->zones_sensor_ = sensor; }
  void set_insert_sensor(sensor::Sensor *sensor) { this->insert_sensor_ = sensor; }

  void setup() override;
  void loop() override {}

 protected:
  usb_uart::USBUartChannel *usb_channel_{nullptr};
  sensor::Sensor *zones_sensor_{nullptr};
  sensor::Sensor *insert_sensor_{nullptr};
  std::string buffer_;
};

}  // namespace usb_reader
}  // namespace esphome
