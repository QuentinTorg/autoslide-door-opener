// ESP32 serial1 and serial2 hardware loop back test

// see https://circuits4you.com/2018/12/31/esp32-hardware-serial2-example/
/* There are three serial ports on the ESP known as U0UXD, U1UXD and U2UXD.
 *
 * U0UXD is used to communicate with the ESP32 for programming and during reset/boot.
 * U1UXD is unused and can be used for your projects. Some boards use this port for SPI Flash access though
 * U2UXD is unused and can be used for your projects.
*/

// working for serial 1
#define RXD1 5
#define TXD1 18
#define RTSD1 19

// working for serial 2
#define RXD2 16  // for loopback jumper these pins
#define TXD2 17
#define RTSD2 4


void setup()
{
    // Note the format for setting a serial port is as follows: Serial2.begin(baud-rate, protocol, RX pin, TX pin);
    Serial.begin(115200);
    Serial.println("ESP32 hardware serial test on Serial1 and Serial2");
    Serial.println("Serial Txd is on pin: "+String(TX));
    Serial.println("Serial Rxd is on pin: "+String(RX));
    delay(10);

    Serial1.begin(9600, SERIAL_8N1, RXD1, TXD1);
    while (!Serial1)
    {
        delay(10);
    }
    if (!Serial1.setPins(-1, -1, -1, RTSD1)) {
        Serial.print("Failed to set serial1 rts pins");
    }
    Serial.println("Serial1 Txd1 is on pin: "+String(TXD1));
    Serial.println("Serial1 Rxd1 is on pin: "+String(RXD1));
    delay(10);
    if (Serial1.setMode(UART_MODE_RS485_HALF_DUPLEX))
    {
        Serial.println("Failed to set Serial1 mode");
    }
    delay(10);


    Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2);
    while (!Serial2)
    {
        delay(10);
    }
    if (!Serial2.setPins(-1, -1, -1, RTSD2)) {
        Serial.print("Failed to set serial2 rts pins");
    }
    Serial.println("Serial2 Txd2 is on pin: "+String(TXD2));
    Serial.println("Serial2 Rxd2 is on pin: "+String(RXD2));
    delay(10);
    if (Serial2.setMode(UART_MODE_RS485_HALF_DUPLEX))
    {
        Serial.println("Failed to set Serial2 mode");
    }
    delay(10);
}

void loop() //Choose Serial1 or Serial2 as required
{
    Serial1.println("printing on serial 1");
    delay(1);
    while (Serial2.available()) {
        Serial.println("Serial2 = " + Serial2.readStringUntil('\n'));
        delay(1);
    }
        delay(1000);

//    Serial2.println("printing on serial 2");
//    while (Serial2.available()) {
//        Serial.println("Serial2 = " + Serial2.readStringUntil('\n'));
//    }


///    while (Serial.available())
//    {
//        String s = Serial.readStringUntil('\n');
//        if(s.charAt(0)=='1')
//        {
//            Serial1.print( s);
//        }
//    }
}














///*
//  This Sketch demonstrates how to use the Hardware Serial peripheral to communicate over an RS485 bus.
//
//  Data received on the primary serial port is relayed to the bus acting as an RS485 interface and vice versa.
//
//  UART to RS485 translation hardware (e.g., MAX485, MAX33046E, ADM483) is assumed to be configured in half-duplex
//  mode with collision detection as described in
//  https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/peripherals/uart.html#circuit-a-collision-detection-circuit
//
//  To use the script open the Arduino serial monitor (or alternative serial monitor on the Arduino port). Then,
//  using an RS485 tranciver, connect another serial monitor to the RS485 port. Entering data on one terminal
//  should be displayed on the other terminal.
//*/
////#include "hal/uart_types.h"
//
//#define RS485_1_RX_PIN  16
//#define RS485_1_TX_PIN  17
//
//#define RS485_2_RX_PIN  0
//#define RS485_2_TX_PIN  4
//
//#define terminal Serial0
//#define RS485_1 Serial1
//#define RS485_2 Serial2
//
//void setup() {
//  pinMode(2, OUTPUT);
//
//  terminal.begin(115200);
//  while (!terminal) {
//    delay(10);
//  }
//  terminal.println("initialized terminal");
//  delay(10);
//
//
//  // Certain versions of Arduino core don't define MODE_RS485_HALF_DUPLEX and so fail to compile.
//  // By using UART_MODE_RS485_HALF_DUPLEX defined in hal/uart_types.h we work around this problem.
//  // If using a newer IDF and Arduino core you can omit including hal/uart_types.h and use MODE_RS485_HALF_DUPLEX
//  // defined in esp32-hal-uart.h (included during other build steps) instead.
//
//  RS485_1.begin(9600, SERIAL_8N1, RS485_1_RX_PIN, RS485_1_TX_PIN);
//  terminal.println("began rs485_1");
//  while (!RS485_1) {
//    terminal.println("FAIL rs485_1 init");
//    delay(10);
//  }
//  terminal.println("connected rs485_1");
//  if (!RS485_1.setMode(UART_MODE_RS485_HALF_DUPLEX)) {
//    terminal.println("Failed to set RS485_1 mode");
//  }
//  terminal.println("set half duplex rs485_1");
//  delay(10);
//
//  RS485_2.begin(9600, SERIAL_8N1, RS485_2_RX_PIN, RS485_2_TX_PIN);
//  terminal.println("began rs485_2");
//  while (!RS485_2) {
//    terminal.println("FAIL rs485_2 init");
//    delay(10);
//  }
//  terminal.println("connected rs485_2");
//  if (!RS485_2.setMode(UART_MODE_RS485_HALF_DUPLEX)) {
//      terminal.println("Failed to set RS485_2 mode");
//  }
//  terminal.println("set half duplex rs485_2");
//  delay(10);
//
//}
//int count=0;
//void loop() {
//  terminal.println("tests");
//
//  RS485_2.println(count, HEX);
//
//  delay(5);
////  if (RS485_2.available()) {
////    //RS485_2.read();
////    terminal.write(RS485_2.read());
////  }
//
//  delay(1000);
//}
