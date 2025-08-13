#include "usb_reader.h"
#include "esphome/core/log.h"

namespace esphome {
namespace usb_reader {

static const char *const TAG = "usb_reader";

static const uint8_t PACKET_START = 0xA0;
static const size_t MAX_PACKET_SIZE = 64;

void USBReader::setup() {
  if (usb_channel_ != nullptr) {
    usb_channel_->add_on_data_callback([this](const uint8_t *data, size_t len) {
      for (size_t i = 0; i < len; i++) {
        this->handle_incoming_byte(data[i]);
      }
    });
    ESP_LOGI(TAG, "USBReader attached to USB UART");
  } else {
    ESP_LOGE(TAG, "USB channel not set!");
  }
}

// Buffer per accumulare i dati
uint8_t buffer_[MAX_PACKET_SIZE];
size_t buffer_pos_ = 0;
bool packet_started_ = false;

void USBReader::handle_incoming_byte(uint8_t byte) {
  if (!packet_started_) {
    if (byte == PACKET_START) {
      packet_started_ = true;
      buffer_pos_ = 0;
      buffer_[buffer_pos_++] = byte;
    }
    return;
  }

  buffer_[buffer_pos_++] = byte;

  // Evitiamo overflow
  if (buffer_pos_ >= MAX_PACKET_SIZE) {
    ESP_LOGW(TAG, "Packet overflow, resetting buffer");
    packet_started_ = false;
    buffer_pos_ = 0;
    return;
  }

  // Lunghezza attesa dal secondo byte
  if (buffer_pos_ == 2) {
    // Non facciamo nulla, aspettiamo pacchetto completo
  }

  // Controllo se pacchetto completo
  if (buffer_pos_ > 2 && buffer_pos_ == buffer_[1]) {
    // Pacchetto completo → parsing
    parse_packet(buffer_, buffer_pos_);

    // Reset per il prossimo pacchetto
    packet_started_ = false;
    buffer_pos_ = 0;
  }
}

void USBReader::parse_packet(uint8_t *data, size_t len) {
  if (len < 4) {
    ESP_LOGW(TAG, "Packet too short");
    return;
  }

  uint8_t checksum = 0;
  for (size_t i = 0; i < len - 1; i++) {
    checksum ^= data[i];
  }
  if (checksum != data[len - 1]) {
    ESP_LOGW(TAG, "Checksum mismatch");
    return;
  }

  uint8_t cmd = data[2];
  ESP_LOGD(TAG, "Valid packet CMD=0x%02X len=%d", cmd, len);

  // Esempio di comandi dalla centrale
  switch (cmd) {
    case 0x10: // Stato connessione
      status_var_ = data[3];
      ESP_LOGI(TAG, "Status updated: %d", status_var_);
      break;

    case 0x20: // Zone
      zones_var_ = data[3];
      ESP_LOGI(TAG, "Zones updated: %d", zones_var_);
      break;

    case 0x30: // Inserimento
      insert_var_ = data[3];
      ESP_LOGI(TAG, "Insert status updated: %d", insert_var_);
      break;

    default:
      ESP_LOGD(TAG, "Unknown CMD 0x%02X", cmd);
      break;
  }
}

}  // namespace usb_reader
}  // namespace esphome
