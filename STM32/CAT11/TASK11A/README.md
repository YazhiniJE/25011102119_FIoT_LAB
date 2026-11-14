EXPERIMENT DETAILS
EXP: CONTINUOUS ASSESSMENT 11
DATE: 22/10/2026 (to be confirmed)
NAME OF EXP: HTTP Server - STM32–Wemos Wi-Fi Modem Using AT Commands
HARDWARE SETUP / PLATFORM: Blue Pill development board + STM32F103C8T6 + ESP8266 + STM32CubeMX (MDK-ARM project)
TASK 11A : TCP Server Setup and IP Retrieval

1. Circuit Diagram
Configure the ESP8266 in station mode, connect to Wi-Fi, retrieve the assigned IP address and initialize the TCP server on port 80.

* Microcontroller / Board: Blue Pill development board + STM32F103C8T6.
* GPIO / Peripheral pins: PA2 / USART2_TX -> ESP8266 RX; PA3 / USART2_RX -> ESP8266 TX.
* Clock: HSE 8 MHz crystal on PD0-OSC_IN/PD1-OSC_OUT; PLL x9, SYSCLK 72 MHz.
* External components / Peripheral: Wemos D1 Mini (ESP8266).
* Power Supply: 3.3 V board logic, common ground; suitable module power supply.

![Circuit Diagram](circuit.png)

2. Core Logic / Pseudocode / Code Base
Working Principle: The STM32 communicates with the ESP8266 through USART2 at 115200 baud. A sequence of AT commands configures station mode, establishes Wi-Fi connectivity, retrieves the assigned IP address and starts a multi-connection TCP server on port 80.

AT Command Sequence:

* `AT` - Verify communication with the ESP8266.
* `AT+CWMODE=1` - Configure station mode.
* `AT+CWJAP` - Connect to the Wi-Fi network.
* `AT+CIFSR` - Retrieve the assigned IP address.
* `AT+CIPMUX=1` - Enable multiple TCP connections.
* `AT+CIPSERVER=1,80` - Start the TCP server on port 80.

Pseudocode:

1. Initialize HAL and configure the system clock.
2. Initialize GPIO and USART2.
3. Wait 2000 ms for ESP8266 startup.
4. Clear the UART receive buffer.
5. Transmit the AT command and receive its response.
6. Repeat for all six AT commands.
7. Complete Wi-Fi connection, IP retrieval and TCP server initialization.
8. Remain in the infinite loop with a 1000 ms delay.

Code Base:
The program is written in Embedded C using STM32 HAL (STM32CubeMX).

* `main.h` provides the project HAL declarations.
* `string.h` provides string comparison and buffer functions.
* `HAL_Init()` initializes the HAL library and SysTick timer.
* `SystemClock_Config()` configures the 72 MHz system clock.
* `MX_GPIO_Init()` initializes the required GPIO clocks.
* `MX_USART2_UART_Init()` configures USART2 at 115200 baud.
* `clear_buffer()` clears the receive buffer and resets its index.
* `memset()` clears the selected byte buffer.
* `receive_response()` collects modem responses until a completion condition or timeout occurs.
* `HAL_UART_Receive()` receives bytes from the ESP8266.
* `strstr()` identifies response markers within the received data.
* `strlen()` determines the length of AT commands.
* `HAL_UART_Transmit()` transmits AT commands through USART2.
* `HAL_Delay()` provides the required timing delays.

3. Inference
The program implements the communication and initialization stages required to establish an embedded TCP server using STM32 and ESP8266. The AT command sequence configures Wi-Fi connectivity, IP address retrieval and server initialization on port 80. Dynamic HTTP webpage generation is implemented separately in TASK11B.

Configuration correction: USART2 on PA2/PA3, 115200 baud, 8-N-1; HSE 8 MHz and 72 MHz system clock retained. Enter Wi-Fi credentials locally. Target compilation and hardware testing remain pending.