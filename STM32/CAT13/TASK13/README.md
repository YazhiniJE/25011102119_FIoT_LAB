EXPERIMENT DETAILS
EXP: CONTINUOUS ASSESSMENT 13
DATE: 23/10/2026
NAME OF EXP: Sensor Interfacing(BME280) – STM32(Debug) – ESP8266(Wi-Fi) HTTP – Node Analytics
HARDWARE SETUP / PLATFORM: Blue Pill development board + STM32F103C8T6 + BME280 + ESP8266 + STM32CubeMX (MDK-ARM project)
TASK 13 : Next step – Node-RED

1. Circuit Diagram
Update the three sets of statistics and show them in the debug sidebar to demonstrate 13 with the shown signals.

* Microcontroller / Board: Blue Pill development board + STM32F103C8T6.
* GPIO / Peripheral pins: PB6 / I2C1_SCL -> BME280 SCL, 4.7k pull-up to 3.3V; PB7 / I2C1_SDA -> BME280 SDA, 4.7k pull-up to 3.3V; PA2 / USART2_TX -> ESP8266 / Wemos RX; PA3 / USART2_RX -> ESP8266 / Wemos TX.
* Clock: HSE 8 MHz crystal on PD0-OSC_IN/PD1-OSC_OUT; PLL x9, SYSCLK 72 MHz.
* External components / Peripheral: BME280 SCL, 4.7k pull-up to 3.3V; BME280 SDA, 4.7k pull-up to 3.3V; ESP8266 / Wemos RX; ESP8266 / Wemos TX.
* Power Supply: 3.3 V board logic, common ground; board regulator / USB supply.

![Circuit Diagram](circuit.png)

2. Core Logic / Pseudocode / Code Base
Working Principle: The firmware serves the same real sensor JSON needed by the analytics stage. flows.json polls that endpoint and retains a count, minimum, maximum, sum and average for each accepted measurement in Node-RED context.

Pseudocode:

1. Run the sensor HTTP server on the board.
2. Import flows.json and set SENSOR_HTTP_URL to its reachable endpoint.
3. Poll every five seconds and reject unsuccessful or nonnumeric readings.
4. Update the three sets of statistics and show them in the debug sidebar.

Code Base:
The program is written in Embedded C using STM32 HAL (STM32CubeMX).

* `main.h` provides the project HAL declarations in this program.
* `string.h` provides string length, comparison and buffer functions in this program.
* `bme280.h` declares the Bosch sensor API in this program.
* `stdio.h` provides the formatted text functions in this program.
* `user_i2c_read()` adapts the Bosch read callback to HAL here.
* `HAL_I2C_Mem_Read()` reads sensor registers through hi2c1 here.
* `user_i2c_write()` adapts the Bosch write callback to HAL here.
* `HAL_I2C_Mem_Write()` writes sensor registers through hi2c1 here.
* `user_delay_us()` rounds the Bosch microsecond delay request up to a HAL millisecond wait here.
* `HAL_Delay()` waits for the programmed millisecond interval here.
* `clear_buffer()` clears the receive text and its index here.
* `memset()` clears the selected byte buffer here.
* `receive_response()` collects modem replies until the saved stop condition or timeout here.
* `HAL_UART_Receive()` receives bytes with the requested timeout here.
* `strstr()` finds the request or modem response marker here.
* `send_http_response()` constructs and sends this task HTTP reply here.
* `bme280_get_sensor_data()` obtains compensated sensor channel values here.
* `snprintf()` formats text within a stated buffer size here.
* `strlen()` counts actual string bytes for serial or HTTP length here.
* `HAL_UART_Transmit()` sends bytes on the selected UART handle here.
* `bme280_init()` reads sensor calibration through the supplied callbacks here.
* `bme280_set_sensor_settings()` applies the saved oversampling and filter settings here.
* `bme280_set_sensor_mode()` selects normal sensor operation here.
* `flows.json` polls HTTP and its function node updates `statistics` in context using each accepted sensor sample.

3. Inference
The statistics come from accepted live samples rather than fixed example values. This task extends the sensor endpoint with running analytics; no measured statistics have been invented.
