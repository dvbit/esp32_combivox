#include "usb_reader.h"
#include "esphome/components/usb_uart/usb_uart.h"
#include "esphome/core/log.h"

namespace esphome {
namespace usb_reader {

static const char *TAG = "usb_reader";

void USBReader::loop() {
  // Qui puoi leggere dal canale usb_channel->available(), etc.
}

void USBReader::parse_line(const std::string &line) {
  ESP_LOGD(TAG, "Received line: %s", line.c_str());
}

}  // namespace usb_reader
}  // namespace esphome
