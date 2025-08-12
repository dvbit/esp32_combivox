#include "usb_reader.h"
#include "esphome/core/log.h"

namespace esphome {
namespace usb_reader {

void USBReader::loop() {
  bool data_received = false;
  while (usb_channel->available()) {
    static std::string buffer;
    char c = usb_channel->read();
    data_received = true;
    if (c == '\n' || c == '\r') {
      if (!buffer.empty()) {
        ESP_LOGI("usb_in", "Ricevuto: %s", buffer.c_str());
        parse_line(buffer);
        buffer.clear();
      }
    } else {
      buffer.push_back(c);
    }
  }
  if (data_received) {
    *status_var = 2;
    *last_seen = millis();
  }
}

void USBReader::parse_line(const std::string &line) {
  if (line.size() > 10) {
    if (line[1] == '0' && line[2] == '1' && line[8] == '0' && line[9] == '6') {
      *zones_var = line;
      zones_sensor->publish_state(line);
    } else if (line[1] == '0' && line[2] == '1' && line[8] == '0' && line[9] == '2') {
      *insert_var = line;
      insert_sensor->publish_state(line);
    }
  }
}

}  // namespace usb_reader
}  // namespace esphome
