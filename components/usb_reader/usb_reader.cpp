#include "usb_reader.h"
#include "esphome/core/log.h"

namespace esphome {
namespace usb_reader {

static const char *TAG = "usb_reader";

void USBReader::setup() {
  if (this->usb_channel_ != nullptr) {
    auto callback = this {
      if (direction == esphome::uart::UARTDirection::UART_DIRECTION_RX) {
        if (c == '\n' || c == '\r') {
          if (!buffer_.empty()) {
            ESP_LOGD(TAG, "Received line: %s", buffer_.c_str());
            size_t z_pos = buffer_.find("Z:");
            size_t i_pos = buffer_.find("I:");
            if (z_pos != std::string::npos && this->zones_sensor_ != nullptr) {
              int z_val = atoi(buffer_.substr(z_pos + 2).c_str());
              this->zones_sensor_->publish_state(z_val);
            }
            if (i_pos != std::string::npos && this->insert_sensor_ != nullptr) {
              int i_val = atoi(buffer_.substr(i_pos + 2).c_str());
              this->insert_sensor_->publish_state(i_val);
            }
            buffer_.clear();
          }
        } else {
          buffer_ += static_cast<char>(c);
        }
      }
    };
    this->usb_channel_->add_debug_callback(std::move(callback));
  }
}

void USBReader::loop() {
  // Nothing to do here since we use the debug callback
}

}  // namespace usb_reader
}  // namespace esphome
