import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import usb_uart
from esphome.const import CONF_ID

CONF_USB_CHANNEL = "usb_channel"
CONF_STATUS_VAR = "status_var"
CONF_LAST_SEEN = "last_seen"
CONF_ZONES_VAR = "zones_var"
CONF_INSERT_VAR = "insert_var"
CONF_ZONES_SENSOR = "zones_sensor"
CONF_INSERT_SENSOR = "insert_sensor"

usb_reader_ns = cg.esphome_ns.namespace("usb_reader")
USBReader = usb_reader_ns.class_("USBReader", cg.Component)

CONFIG_SCHEMA = cv.Schema(
    {
        cv.GenerateID(): cv.declare_id(USBReader),
        cv.Required(CONF_USB_CHANNEL): cv.use_id(usb_uart.USBUartComponent),
        cv.Optional(CONF_STATUS_VAR): cv.declare_variable_id(int),
        cv.Optional(CONF_LAST_SEEN): cv.declare_variable_id(int),
        cv.Optional(CONF_ZONES_VAR): cv.declare_variable_id(int),
        cv.Optional(CONF_INSERT_VAR): cv.declare_variable_id(int),
        cv.Optional(CONF_ZONES_SENSOR): cv.declare_variable_id(int),
        cv.Optional(CONF_INSERT_SENSOR): cv.declare_variable_id(int),
    }
).extend(cv.COMPONENT_SCHEMA)


async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)

    chan = await cg.get_variable(config[CONF_USB_CHANNEL])
    cg.add(var.set_usb_channel(chan))

    if CONF_STATUS_VAR in config:
        cg.add(var.set_status_var(config[CONF_STATUS_VAR]))
    if CONF_LAST_SEEN in config:
        cg.add(var.set_last_seen(config[CONF_LAST_SEEN]))
    if CONF_ZONES_VAR in config:
        cg.add(var.set_zones_var(config[CONF_ZONES_VAR]))
    if CONF_INSERT_VAR in config:
        cg.add(var.set_insert_var(config[CONF_INSERT_VAR]))
    if CONF_ZONES_SENSOR in config:
        cg.add(var.set_zones_sensor(config[CONF_ZONES_SENSOR]))
    if CONF_INSERT_SENSOR in config:
        cg.add(var.set_insert_sensor(config[CONF_INSERT_SENSOR]))
