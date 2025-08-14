import esphome.config_validation as cv
import esphome.codegen as cg
from esphome.const import CONF_ID

DEPENDENCIES = ["usb_uart"]

usb_reader_ns = cg.esphome_ns.namespace("usb_reader")
USBReader = usb_reader_ns.class_("USBReader", cg.Component)

CONF_USB_CHANNEL = "usb_channel"
CONF_ZONES_SENSOR = "zones_sensor"
CONF_INSERT_SENSOR = "insert_sensor"

CONFIG_SCHEMA = cv.Schema({
    cv.GenerateID(): cv.declare_id(USBReader),
    cv.Required(CONF_USB_CHANNEL): cv.use_id(cg.Component),
    cv.Optional(CONF_ZONES_SENSOR): cv.use_id(cg.Sensor),
    cv.Optional(CONF_INSERT_SENSOR): cv.use_id(cg.Sensor),
}).extend(cv.COMPONENT_SCHEMA)

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)

    usb_channel = await cg.get_variable(config[CONF_USB_CHANNEL])
    cg.add(var.set_usb_channel(usb_channel))

    if CONF_ZONES_SENSOR in config:
        sensor_var = await cg.get_variable(config[CONF_ZONES_SENSOR])
        cg.add(var.set_zones_sensor(sensor_var))

    if CONF_INSERT_SENSOR in config:
        sensor_var = await cg.get_variable(config[CONF_INSERT_SENSOR])
        cg.add(var.set_insert_sensor(sensor_var))
