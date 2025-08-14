import esphome.config_validation as cv
import esphome.codegen as cg
from esphome.components import usb_uart, sensor
from esphome.const import CONF_ID

CODEOWNERS = ["@marcob79"]

usb_reader_ns = cg.esphome_ns.namespace("usb_reader")
USBReader = usb_reader_ns.class_("USBReader", usb_uart.USBUartDevice, cg.Component)

CONF_ZONES_SENSOR = "zones_sensor"
CONF_INSERT_SENSOR = "insert_sensor"

CONFIG_SCHEMA = cv.Schema({
    cv.GenerateID(): cv.declare_id(USBReader),
    cv.Required(CONF_ZONES_SENSOR): cv.use_id(sensor.Sensor),
    cv.Required(CONF_INSERT_SENSOR): cv.use_id(sensor.Sensor),
}).extend(usb_uart.usb_uart_device_schema())

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await usb_uart.register_usb_uart_device(var, config)

    zones = await cg.get_variable(config[CONF_ZONES_SENSOR])
    cg.add(var.set_zones_sensor(zones))

    insert = await cg.get_variable(config[CONF_INSERT_SENSOR])
    cg.add(var.set_insert_sensor(insert))
