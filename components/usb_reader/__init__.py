import esphome.codegen as cg
import esphome.config_validation as cv
from esphome import core
from esphome.components import uart, text_sensor

usb_reader_ns = cg.esphome_ns.namespace("usb_reader")
USBReader = usb_reader_ns.class_("USBReader", cg.Component)

CONFIG_SCHEMA = cv.Schema({
    cv.GenerateID(): cv.declare_id(USBReader),

    cv.Required("usb_channel"): cv.use_id(uart.UARTComponent),
    cv.Required("status_var"): cv.string,       # Nome variabile globale int
    cv.Required("last_seen"): cv.string,        # Nome variabile globale unsigned long
    cv.Required("zones_var"): cv.string,        # Nome variabile globale string
    cv.Required("insert_var"): cv.string,       # Nome variabile globale string
    cv.Required("zones_sensor"): cv.use_id(text_sensor.TextSensor),
    cv.Required("insert_sensor"): cv.use_id(text_sensor.TextSensor),
}).extend(cv.COMPONENT_SCHEMA)

async def to_code(config):
    var = cg.new_Pvariable(config[core.CONF_ID])

    # Collegamento UART
    usb_comp = await cg.get_variable(config["usb_channel"])
    cg.add(var.usb_channel(usb_comp))  # qui serve un setter, se non c'è dobbiamo fare var.usb_channel = usb_comp

    # Variabili globali: al momento le passiamo come stringhe
    cg.add(var.status_var(config["status_var"]))
    cg.add(var.last_seen(config["last_seen"]))
    cg.add(var.zones_var(config["zones_var"]))
    cg.add(var.insert_var(config["insert_var"]))

    # Sensori di testo
    zones_sens = await cg.get_variable(config["zones_sensor"])
    cg.add(var.zones_sensor(zones_sens))
    insert_sens = await cg.get_variable(config["insert_sensor"])
    cg.add(var.insert_sensor(insert_sens))

    await cg.register_component(var, config)
