#pragma once

#include "esphome/core/component.h"
#include "esphome/components/usb_uart/usb_uart.h"
#include "esphome/components/globals/globals_component.h"

namespace esphome {
namespace usb_reader {

class USBReader : public Component {
 public:
  void set_usb_channel(usb_uart::USBUartComponent *chan) { usb_channel_ = chan; }
  void set_status_var(globals::GlobalsComponent<int> *status) { status_var_ = status; }
  void set_last_seen_var(globals::GlobalsComponent<int> *last_seen) { last_seen_var_ = last_seen; }
  void set_zones_var(globals::GlobalsComponent<int> *zones) { zones_var_ = zones; }
  void set_insert_var(globals::GlobalsComponent<int> *insert) { insert_var_ = insert; }

  void loop() override;
  void setup() override;

 protected:
  usb_uart::USBUartComponent *usb_channel_{nullptr};
  globals::GlobalsComponent<int> *status_var_{nullptr};
  globals::GlobalsComponent<int> *last_seen_var_{nullptr};
  globals::GlobalsComponent<int> *zones_var_{nullptr};
  globals::GlobalsComponent<int> *insert_var_{nullptr};
};

}  // namespace usb_reader
}  // namespace esphome
