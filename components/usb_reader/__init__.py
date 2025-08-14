import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import uart
from esphome.const import CONF_ID

CODEOWNERS = ["@tuo_username"]

usb_reader_ns = cg.esphome_ns.namespace("usb_reader")
USBReader = usb_reader_ns.class_("USBReader", uart.UARTDevice, cg.PollingComponent)

CONF_ZONES_SENSOR = "zones_sensor"
CONF_INSERT_SENSOR = "insert_sensor"

CONFIG_SCHEMA = (
    cv.Schema(
        {
            cv.GenerateID(): cv.declare_id(USBReader),
            cv.Required(CONF_ZONES_SENSOR): cv.use_id(cg.Sensor),
            cv.Required(CONF_INSERT_SENSOR): cv.use_id(cg.Sensor),
        }
    )
    .extend(uart.UART_DEVICE_SCHEMA)
    .extend(cv.polling_component_schema("1s"))
)

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await uart.register_uart_device(var, config)

    zones_sensor = await cg.get_variable(config[CONF_ZONES_SENSOR])
    cg.add(var.set_zones_sensor(zones_sensor))

    insert_sensor = await cg.get_variable(config[CONF_INSERT_SENSOR])
    cg.add(var.set_insert_sensor(insert_sensor))
