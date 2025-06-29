
#include <ModbusSerial.h>

#define RS485_RX_PIN  16
#define RS485_TX_PIN  5
#define RS485 Serial1

void setup()
{
    Serial.begin(9600);
    while (!Serial)
    {
        delay(10);
    }

    Serial.println("initializing rs485");
    RS485.begin(9600, SERIAL_8N1, RS485_RX_PIN, RS485_TX_PIN);

    while (!RS485)
    {
        delay(10);
    }

    Serial.println("setting half duplex mode");
    if (!RS485.setMode(UART_MODE_RS485_HALF_DUPLEX))
    {
        Serial.println("Failed to set RS485 mode");
    }

    Serial.println("initialized ESP32");
}

void loop()
{
}
