#include "esphome/core/schema.h"
#include "esphome/core/log.h"
#include "usb_reader.h"

namespace esphome {
namespace usb_reader {

using namespace esphome::schema;

static const auto USB_READER_SCHEMA = inherit_component_schema()
    .required("usb_channel", id_reference<usb_uart::USBUartComponent>())
    .required("status_var", id_reference<globals::GlobalsComponent<int>>())
    .optional("last_seen", id_reference<globals::GlobalsComponent<int>>())
    .optional("zones_var", id_reference<globals::GlobalsComponent<int>>())
    .optional("insert_var", id_reference<globals::GlobalsComponent<int>>());

class USBReaderFactory : public ComponentFactory {
 public:
  USBReaderFactory() : ComponentFactory("usb_reader", USB_READER_SCHEMA) {}

  ComponentPtr create(const yaml::YamlNode &config) override {
    auto comp = make_unique<USBReader>();
    comp->set_usb_channel(config.require_id<usb_uart::USBUartComponent>("usb_channel"));
    comp->set_status_var(config.require_id<globals::GlobalsComponent<int>>("status_var"));

    if (config.has("last_seen"))
      comp->set_last_seen_var(config.require_id<globals::GlobalsComponent<int>>("last_seen"));
    if (config.has("zones_var"))
      comp->set_zones_var(config.require_id<globals::GlobalsComponent<int>>("zones_var"));
    if (config.has("insert_var"))
      comp->set_insert_var(config.require_id<globals::GlobalsComponent<int>>("insert_var"));

    return comp;
  }
};

static USBReaderFactory factory;

}  // namespace usb_reader
}  // namespace esphome
