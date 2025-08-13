import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import usb_uart, text_sensor
import esphome

DEPENDENCIES = ["usb_uart", "text_sensor"]

usb_reader_ns = cg.esphome_ns.namespace("usb_reader")
USBReader = usb_reader_ns.class_("USBReader", cg.Component)

CONFIG_SCHEMA = cv.Schema({
    cv.Required("usb_channel"): cv.use_id(usb_uart.USBUartComponent),
    cv.Required("status_var"): cv.id(),
    cv.Required("last_seen"): cv.id(),
    cv.Required("zones_var"): cv.id(),
    cv.Required("insert_var"): cv.id(),
    cv.Required("zones_sensor"): cv.use_id(text_sensor.TextSensor),
    cv.Required("insert_sensor"): cv.use_id(text_sensor.TextSensor),
}).extend(cv.COMPONENT_SCHEMA)

async def to_code(config):
    var = cg.new_Pvariable(config["id"])
    await cg.register_component(var, config)

    usb_ch = await cg.get_variable(config["usb_channel"])
    cg.add(var.set_usb_channel(usb_ch))

    cg.add(var.set_status_var(config["status_var"]))
    cg.add(var.set_last_seen(config["last_seen"]))
    cg.add(var.set_zones_var(config["zones_var"]))
    cg.add(var.set_insert_var(config["insert_var"]))

    zones_sens = await cg.get_variable(config["zones_sensor"])
    cg.add(var.set_zones_sensor(zones_sens))

    insert_sens = await cg.get_variable(config["insert_sensor"])
    cg.add(var.set_insert_sensor(insert_sens))
