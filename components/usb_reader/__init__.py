import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import usb_uart, text_sensor, globals
from esphome.const import CONF_ID

DEPENDENCIES = ["usb_uart", "text_sensor", "globals"]

usb_reader_ns = cg.esphome_ns.namespace("usb_reader")
USBReader = usb_reader_ns.class_("USBReader", cg.Component)

CONF_USB_CHANNEL = "usb_channel"
CONF_STATUS_VAR = "status_var"
CONF_LAST_SEEN = "last_seen"
CONF_ZONES_VAR = "zones_var"
CONF_INSERT_VAR = "insert_var"
CONF_ZONES_SENSOR = "zones_sensor"
CONF_INSERT_SENSOR = "insert_sensor"

CONFIG_SCHEMA = cv.Schema({
    cv.GenerateID(): cv.declare_id(USBReader),
    cv.Required(CONF_USB_CHANNEL): cv.use_id(usb_uart.USBUartComponent),
    cv.Required(CONF_STATUS_VAR): cv.use_id(globals.GlobalsComponent),
    cv.Required(CONF_LAST_SEEN): cv.use_id(globals.GlobalsComponent),
    cv.Required(CONF_ZONES_VAR): cv.use_id(globals.GlobalsComponent),
    cv.Required(CONF_INSERT_VAR): cv.use_id(globals.GlobalsComponent),
    cv.Required(CONF_ZONES_SENSOR): cv.use_id(text_sensor.TextSensor),
    cv.Required(CONF_INSERT_SENSOR): cv.use_id(text_sensor.TextSensor),
}).extend(cv.COMPONENT_SCHEMA)

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)

    usb_comp = await cg.get_variable(config[CONF_USB_CHANNEL])
    cg.add(var.set_usb_channel(usb_comp))

    status_var = await cg.get_variable(config[CONF_STATUS_VAR])
    cg.add(var.set_status_var(status_var))

    last_seen = await cg.get_variable(config[CONF_LAST_SEEN])
    cg.add(var.set_last_seen(last_seen))

    zones_var = await cg.get_variable(config[CONF_ZONES_VAR])
    cg.add(var.set_zones_var(zones_var))

    insert_var = await cg.get_variable(config[CONF_INSERT_VAR])
    cg.add(var.set_insert_var(insert_var))

    zones_sensor_var = await cg.get_variable(config[CONF_ZONES_SENSOR])
    cg.add(var.set_zones_sensor(zones_sensor_var))

    insert_sensor_var = await cg.get_variable(config[CONF_INSERT_SENSOR])
    cg.add(var.set_insert_sensor(insert_sensor_var))
