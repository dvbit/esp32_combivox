#pragma once

#include "esphome.h"
#include "esphome/components/usb_uart/usb_uart.h"
#include <string>

namespace esphome {
namespace usb_reader {

class USBReader : public Component {
 public:
  usb_uart::USBUartComponent *usb_channel;
  int *status_var;
  unsigned long *last_seen;
  std::string *zones_var;
  std::string *insert_var;
  esphome::text_sensor::TextSensor *zones_sensor;
  esphome::text_sensor::TextSensor *insert_sensor;

  void loop() override;
  void parse_line(const std::string &line);

  void set_usb_channel(uart::UARTComponent *chan) { usb_channel = chan; }
  void set_status_var(int *var) { status_var = var; }
  void set_last_seen(unsigned long *var) { last_seen = var; }
  void set_zones_var(std::string *var) { zones_var = var; }
  void set_insert_var(std::string *var) { insert_var = var; }
  void set_zones_sensor(esphome::text_sensor::TextSensor *sensor) { zones_sensor = sensor; }
  void set_insert_sensor(esphome::text_sensor::TextSensor *sensor) { insert_sensor = sensor; }
};

}  // namespace usb_reader
}  // namespace esphome
