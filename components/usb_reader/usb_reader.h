#pragma once

#include "esphome/core/component.h"
#include "esphome/components/usb_uart/usb_uart.h"
#include "esphome/components/sensor/sensor.h"

namespace esphome {
namespace usb_reader {

class USBReader : public usb_uart::USBUartDevice, public Component {
 public:
  void set_zones_sensor(sensor::Sensor *sensor) { zones_sensor_ = sensor; }
  void set_insert_sensor(sensor::Sensor *sensor) { insert_sensor_ = sensor; }

  void loop() override;

 protected:
  std::string buffer_;
  sensor::Sensor *zones_sensor_{nullptr};
  sensor::Sensor *insert_sensor_{nullptr};
};

}  // namespace usb_reader
}  // namespace esphome
