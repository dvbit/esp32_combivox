#include "usb_reader.h"
#include "esphome/core/log.h"

namespace esphome {
namespace usb_reader {

static const char *const TAG = "usb_reader";

void USBReader::setup() {
  ESP_LOGI(TAG, "USB Reader setup complete");
}

void USBReader::loop() {
  if (this->usb_channel_ == nullptr)
    return;

  while (true) {
    int c = this->usb_channel_->read();
    if (c < 0)  // nessun dato disponibile
      break;

    if (c == '\n') {
      ESP_LOGD(TAG, "Received line: %s", this->buffer_.c_str());
      // Parsing esempio: "Z:3,I:1"
      size_t z_pos = this->buffer_.find("Z:");
      size_t i_pos = this->buffer_.find("I:");

      if (z_pos != std::string::npos && this->zones_sensor_ != nullptr) {
        int z_val = atoi(this->buffer_.substr(z_pos + 2).c_str());
        this->zones_sensor_->publish_state(z_val);
      }

      if (i_pos != std::string::npos && this->insert_sensor_ != nullptr) {
        int i_val = atoi(this->buffer_.substr(i_pos + 2).c_str());
        this->insert_sensor_->publish_state(i_val);
      }

      this->buffer_.clear();
    } else {
      this->buffer_ += static_cast<char>(c);
    }
  }
}


}  // namespace usb_reader
}  // namespace esphome
