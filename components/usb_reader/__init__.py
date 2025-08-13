import esphome.config_validation as cv
import esphome.codegen as cg
from esphome.const import CONF_ID
from esphome.components import usb_uart, sensor

CONF_USB_CHANNEL = "usb_channel"
CONF_ZONES_SENSOR = "zones_sensor"
CONF_INSERT_SENSOR = "insert_sensor"

usb_reader_ns = cg.esphome_ns.namespace("usb_reader")
USBReader = usb_reader_ns.class_("USBReader", cg.Component)

CONFIG_SCHEMA = cv.Schema(
    {
        cv.GenerateID(): cv.declare_id(USBReader),
        cv.Required(CONF_USB_CHANNEL): cv.use_id(usb_uart.USBUartComponent),
        cv.Required(CONF_ZONES_SENSOR): cv.use_id(sensor.Sensor),
        cv.Required(CONF_INSERT_SENSOR): cv.use_id(sensor.Sensor),
    }
).extend(cv.COMPONENT_SCHEMA)


async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)

    usb_channel = await cg.get_variable(config[CONF_USB_CHANNEL])
    cg.add(var.set_usb_channel(usb_channel))

    zones_sensor_var = await cg.get_variable(config[CONF_ZONES_SENSOR])
    cg.add(var.set_zones_sensor(zones_sensor_var))

    insert_sensor_var = await cg.get_variable(config[CONF_INSERT_SENSOR])
    cg.add(var.set_insert_sensor(insert_sensor_var))
