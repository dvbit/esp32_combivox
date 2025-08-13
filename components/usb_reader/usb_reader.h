#pragma once

#include "esphome/core/component.h"
#include "esphome/components/usb_uart/usb_uart.h"

namespace esphome {
namespace usb_reader {

class USBReader : public Component {
 public:
  void set_usb_channel(usb_uart::USBUartComponent *chan) { usb_channel_ = chan; }
  void set_status_var(int status) { status_var_ = status; }
  void set_last_seen(int last) { last_seen_ = last; }
  void set_zones_var(int zones) { zones_var_ = zones; }
  void set_insert_var(int insert) { insert_var_ = insert; }
  void set_zones_sensor(int sensor) { zones_sensor_ = sensor; }
  void set_insert_sensor(int sensor) { insert_sensor_ = sensor; }

  void setup() override;
  void loop() override {}  // Non serve più, gestiamo tutto in callback

 protected:
  void handle_incoming_byte(uint8_t byte);

  usb_uart::USBUartComponent *usb_channel_{nullptr};
  int status_var_{0};
  int last_seen_{0};
  int zones_var_{0};
  int insert_var_{0};
  int zones_sensor_{0};
  int insert_sensor_{0};
};

}  // namespace usb_reader
}  // namespace esphome
