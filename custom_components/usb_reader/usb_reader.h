#pragma once

#include "esphome.h"
#include <string>

namespace esphome {
namespace usb_reader {

class USBReader : public Component {
 public:
  uart::UARTComponent *usb_channel;
  int *status_var;
  unsigned long *last_seen;
  std::string *zones_var;
  std::string *insert_var;
  esphome::text_sensor::TextSensor *zones_sensor;
  esphome::text_sensor::TextSensor *insert_sensor;

  void loop() override;
  void parse_line(const std::string &line);
};

}  // namespace usb_reader
}  // namespace esphome
