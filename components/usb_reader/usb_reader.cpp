#include "usb_reader.h"
#include "esphome/core/log.h"
#include <cstdlib>

namespace esphome {
namespace usb_reader {

static const char *const TAG = "usb_reader";

void USBReader::loop() {
  uint8_t c;
  while (this->read_byte(&c)) {
    if (c == '\n' || c == '\r') {
      if (!buffer_.empty()) {
        ESP_LOGD(TAG, "Received line: %s", buffer_.c_str());

        size_t z_pos = buffer_.find("Z:");
        size_t i_pos = buffer_.find("I:");

        if (z_pos != std::string::npos && zones_sensor_ != nullptr) {
          int z_val = atoi(buffer_.substr(z_pos + 2).c_str());
          zones_sensor_->publish_state(z_val);
        }

        if (i_pos != std::string::npos && insert_sensor_ != nullptr) {
          int i_val = atoi(buffer_.substr(i_pos + 2).c_str());
          insert_sensor_->publish_state(i_val);
        }

        buffer_.clear();
      }
    } else {
      buffer_ += static_cast<char>(c);
    }
  }
}

}  // namespace usb_reader
}  // namespace esphome
