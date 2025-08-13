#pragma once

#include "esphome/core/component.h"
#include "esphome/components/usb_uart/usb_uart.h"
#include "esphome/components/sensor/sensor.h"

namespace esphome {
namespace usb_reader {

class USBReader : public Component {
 public:
  void set_usb_channel(usb_uart::USBUartComponent *channel) { this->usb_channel_ = channel; }
  void set_zones_sensor(sensor::Sensor *s) { this->zones_sensor_ = s; }
  void set_insert_sensor(sensor::Sensor *s) { this->insert_sensor_ = s; }

  void setup() override;
  void loop() override;
  float get_setup_priority() const override { return setup_priority::LATE; }

 protected:
  usb_uart::USBUartComponent *usb_channel_{nullptr};
  sensor::Sensor *zones_sensor_{nullptr};
  sensor::Sensor *insert_sensor_{nullptr};
  std::string buffer_;
};

}  // namespace usb_reader
}  // namespace esphome
