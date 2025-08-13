#include "usb_reader.h"
#include "esphome/core/log.h"

namespace esphome {
namespace usb_reader {

static const char *const TAG = "usb_reader";

void USBReader::setup() {
  ESP_LOGI(TAG, "USB Reader setup completo");
}

void USBReader::loop() {
  if (!usb_channel_) return;

  while (usb_channel_->available()) {
    uint8_t c;
    usb_channel_->read_byte(&c);
    ESP_LOGD(TAG, "Ricevuto byte: 0x%02X", c);
    // Qui metti la tua logica di parsing
  }
}

}  // namespace usb_reader
}  // namespace esphome
