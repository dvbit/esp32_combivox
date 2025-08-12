#include "esphome.h"
#include "usb_reader.h"
#include "esphome/components/uart/uart_component.h"
#include "esphome/core/log.h"
#include "esphome/core/component.h"

namespace esphome {
namespace usb_reader {

static const char *TAG = "usb_reader";

// USBReaderComponent estende USBReader con setup
class USBReaderComponent : public USBReader {
 public:
  void setup() override {
    ESP_LOGCONFIG(TAG, "Setting up USBReader component");
  }
};

// CONFIG_SCHEMA definisce i campi YAML accettati
static const auto USB_READER_SCHEMA = esphome::component_schema()
    .add_required<uart::UARTComponent *>("usb_channel")
    .add_required<int *>("status_var")
    .add_required<unsigned long *>("last_seen")
    .add_required<std::string *>("zones_var")
    .add_required<std::string *>("insert_var")
    .add_required<text_sensor::TextSensor *>("zones_sensor")
    .add_required<text_sensor::TextSensor *>("insert_sensor");

// Funzione che ESPHome chiama per registrare il componente dal YAML
void register_usb_reader(const std::shared_ptr<esphome::yaml::YamlNode> &node,
                         ComponentRegistry &registry) {
  auto comp = std::make_shared<USBReaderComponent>();

  comp->usb_channel = registry.get_component<uart::UARTComponent>(node->get("usb_channel")->as<std::string>());
  comp->status_var = registry.get_global<int>(node->get("status_var")->as<std::string>());
  comp->last_seen = registry.get_global<unsigned long>(node->get("last_seen")->as<std::string>());
  comp->zones_var = registry.get_global<std::string>(node->get("zones_var")->as<std::string>());
  comp->insert_var = registry.get_global<std::string>(node->get("insert_var")->as<std::string>());
  comp->zones_sensor = registry.get_component<text_sensor::TextSensor>(node->get("zones_sensor")->as<std::string>());
  comp->insert_sensor = registry.get_component<text_sensor::TextSensor>(node->get("insert_sensor")->as<std::string>());

  registry.add_component(comp);
}

}  // namespace usb_reader
}  // namespace esphome
