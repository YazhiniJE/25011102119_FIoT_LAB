import os
import sys
import tempfile

os.environ['MPLCONFIGDIR'] = tempfile.mkdtemp()

from circuits import draw

REPO_ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))

def generate_all():
    print("Generating all circuit schematics...")
    
    # --- 8051 CAT2 ---
    draw(
        path=os.path.join(REPO_ROOT, "8051", "CAT2", "circuit.png"),
        title="Continuous Assessment 2: Bare-Metal LED Blink & Delay Library",
        board="8051 Development Kit",
        mcu="AT89S52",
        peripherals=[
            {
                'name': 'LED Indicator (P1.0)',
                'pins': [
                    ('P1.0', 'Anode (via 330Ω)', 'gpio'),
                    ('GND', 'Cathode', 'gnd')
                ]
            },
            {
                'name': 'Power & Reset Circuit',
                'pins': [
                    ('VCC (Pin 40)', '+5V DC Rail', 'power'),
                    ('GND (Pin 20)', 'Ground Rail', 'gnd'),
                    ('RST (Pin 9)', '10uF Cap / 10k Resistor', 'gpio')
                ]
            }
        ],
        bottom_text="11.0592 MHz Crystal (Pins 18, 19 with 33pF caps) | VCC Pin 40 = +5V | GND Pin 20 = 0V"
    )

    # --- 8051 CAT3 ---
    draw(
        path=os.path.join(REPO_ROOT, "8051", "CAT3", "circuit.png"),
        title="Continuous Assessment 3: LED Pattern Generator & Button Controller",
        board="8051 Development Kit",
        mcu="AT89S52",
        peripherals=[
            {
                'name': '4x Output Pattern LEDs',
                'pins': [
                    ('P1.1', 'LED 1 Anode (via 330Ω)', 'gpio'),
                    ('P1.3', 'LED 2 Anode (via 330Ω)', 'gpio'),
                    ('P1.5', 'LED 3 Anode (via 330Ω)', 'gpio'),
                    ('P1.7', 'LED 4 Anode (via 330Ω)', 'gpio'),
                    ('GND', 'Common Cathodes', 'gnd')
                ]
            },
            {
                'name': 'Mode Switch (Matrix Button)',
                'pins': [
                    ('P2.0', 'Keypad Row 1 Terminal', 'gpio'),
                    ('P2.5', 'Keypad Column 2 Terminal', 'gpio')
                ]
            },
            {
                'name': 'Power Supply',
                'pins': [
                    ('VCC (Pin 40)', '+5V DC Supply', 'power'),
                    ('GND (Pin 20)', 'Circuit Ground', 'gnd')
                ]
            }
        ],
        bottom_text="11.0592 MHz Crystal | 4 Operating Modes (Running, Binary, Alternate, Flash) | +5V VCC"
    )

    # --- 8051 CAT4 ---
    draw(
        path=os.path.join(REPO_ROOT, "8051", "CAT4", "circuit.png"),
        title="Continuous Assessment 4: HMI with Matrix Keypad, LEDs & 7-Segment",
        board="8051 Development Kit",
        mcu="AT89S52",
        peripherals=[
            {
                'name': '4x4 Matrix Keypad',
                'pins': [
                    ('P2.7', 'Row 1', 'gpio'),
                    ('P2.6', 'Row 2', 'gpio'),
                    ('P2.5', 'Row 3', 'gpio'),
                    ('P2.4', 'Row 4', 'gpio'),
                    ('P2.3', 'Col 1', 'gpio'),
                    ('P2.2', 'Col 2', 'gpio'),
                    ('P2.1', 'Col 3', 'gpio'),
                    ('P2.0', 'Col 4', 'gpio')
                ]
            },
            {
                'name': 'Common Anode 7-Segment Display',
                'pins': [
                    ('P0.0 - P0.6', 'Segments A - G', 'gpio'),
                    ('P0.7', 'Segment DP', 'gpio'),
                    ('VCC', 'Common Anode Rail', 'power')
                ]
            },
            {
                'name': '4x Function Output LEDs',
                'pins': [
                    ('P1.1', 'LED 1 Anode', 'gpio'),
                    ('P1.3', 'LED 2 Anode', 'gpio'),
                    ('P1.5', 'LED 3 Anode', 'gpio'),
                    ('P1.7', 'LED 4 Anode', 'gpio'),
                    ('GND', 'Common Cathode', 'gnd')
                ]
            }
        ],
        bottom_text="11.0592 MHz Crystal | Port 0 External 10kΩ Pull-Up Resistor Array | +5V VCC | 0V GND"
    )

    # --- 8051 CAT5 ---
    draw(
        path=os.path.join(REPO_ROOT, "8051", "CAT5", "circuit.png"),
        title="Continuous Assessment 5: Hardware Timer0 Timing & Pulse Generation",
        board="8051 Development Kit",
        mcu="AT89S52",
        peripherals=[
            {
                'name': 'Timing Indicator LED',
                'pins': [
                    ('P1.1', 'LED Anode (via 330Ω)', 'gpio'),
                    ('GND', 'LED Cathode', 'gnd')
                ]
            },
            {
                'name': 'Frequency / Scope Test Point',
                'pins': [
                    ('P1.1', 'Square Wave / Pulse Output', 'gpio'),
                    ('GND', 'Scope Ground Reference', 'gnd')
                ]
            },
            {
                'name': 'Power Supply',
                'pins': [
                    ('VCC (Pin 40)', '+5V DC Regulated', 'power'),
                    ('GND (Pin 20)', 'System Ground', 'gnd')
                ]
            }
        ],
        bottom_text="11.0592 MHz Crystal | Timer 0 Mode 1 (16-bit, TH0=0xF1, TL0=0x99, 200 counts = 1s toggle)"
    )

    # --- 8051 CAT6 ---
    draw(
        path=os.path.join(REPO_ROOT, "8051", "CAT6", "circuit.png"),
        title="Continuous Assessment 6: UART Driver & Serial Debugging (9600 Baud)",
        board="8051 Development Kit",
        mcu="AT89S52",
        peripherals=[
            {
                'name': 'USB-to-UART / MAX232 Transceiver',
                'pins': [
                    ('P3.1 (TXD)', 'RXD (USB Bridge / PC)', 'uart'),
                    ('P3.0 (RXD)', 'TXD (USB Bridge / PC)', 'uart'),
                    ('GND', 'Common Ground', 'gnd')
                ]
            },
            {
                'name': 'Power Supply',
                'pins': [
                    ('VCC (Pin 40)', '+5V DC Supply', 'power'),
                    ('GND (Pin 20)', 'Circuit Ground', 'gnd')
                ]
            }
        ],
        bottom_text="11.0592 MHz Crystal | 9600 Baud, 8-N-1 (Timer 1 Mode 2, TH1=0xFD) | PuTTY Console"
    )

    # --- 8051 CAT7 ---
    draw(
        path=os.path.join(REPO_ROOT, "8051", "CAT7", "circuit.png"),
        title="Continuous Assessment 7: 16x2 LCD Driver Development & Keypad Movement",
        board="8051 Development Kit",
        mcu="AT89S52",
        peripherals=[
            {
                'name': '16x2 HD44780 LCD (4-bit Mode)',
                'pins': [
                    ('P3.2', 'RS (Register Select)', 'gpio'),
                    ('P3.3', 'EN (Enable Strobe)', 'gpio'),
                    ('P3.4', 'D4 (Data Bit 4)', 'gpio'),
                    ('P3.5', 'D5 (Data Bit 5)', 'gpio'),
                    ('P3.6', 'D6 (Data Bit 6)', 'gpio'),
                    ('P3.7', 'D7 (Data Bit 7)', 'gpio'),
                    ('GND', 'RW (GND) & VSS (Pin 1)', 'gnd'),
                    ('VCC', 'VDD (Pin 2) & Backlight A', 'power')
                ]
            },
            {
                'name': '4x4 Keypad (Task 7C Movement)',
                'pins': [
                    ('P2.7 - P2.4', 'Keypad Rows 1 - 4', 'gpio'),
                    ('P2.3 - P2.0', 'Keypad Columns 1 - 4', 'gpio')
                ]
            }
        ],
        bottom_text="11.0592 MHz Crystal | 4-bit LCD Initialization | 10k Contrast Potentiometer | +5V VCC"
    )

    # --- STM32 CAT8 ---
    draw(
        path=os.path.join(REPO_ROOT, "STM32", "CAT8", "circuit.png"),
        title="Continuous Assessment 8: STM32 GPIO Bring-Up & Switch-Controlled LED",
        board="STM32 Blue Pill",
        mcu="STM32F103C8T6",
        peripherals=[
            {
                'name': 'External Push Button Switch',
                'pins': [
                    ('PA3', 'Switch Signal (Pull-Up)', 'gpio'),
                    ('GND', 'Switch Ground', 'gnd')
                ]
            },
            {
                'name': 'External Output LED',
                'pins': [
                    ('PA4', 'LED Anode (via 330Ω)', 'gpio'),
                    ('GND', 'LED Cathode', 'gnd')
                ]
            },
            {
                'name': 'On-Board LED Indicator',
                'pins': [
                    ('PC13', 'On-board LED (Active-Low)', 'gpio')
                ]
            },
            {
                'name': 'Power & Debug (ST-LINK)',
                'pins': [
                    ('3.3V', '+3.3V DC Rail', 'power'),
                    ('GND', 'Common Ground', 'gnd')
                ]
            }
        ],
        bottom_text="8 MHz HSE Crystal (72 MHz SYSCLK) | Non-blocking HAL_GetTick() Timing | VDD = 3.3V"
    )

    # --- STM32 CAT9 ---
    draw(
        path=os.path.join(REPO_ROOT, "STM32", "CAT9", "circuit.png"),
        title="Continuous Assessment 9: STM32 UART Command Controlled LED",
        board="STM32 Blue Pill",
        mcu="STM32F103C8T6",
        peripherals=[
            {
                'name': 'USB-to-UART Adapter (CP2102/CH340)',
                'pins': [
                    ('PA9 (USART1_TX)', 'RXD of USB Adapter', 'uart'),
                    ('PA10 (USART1_RX)', 'TXD of USB Adapter', 'uart'),
                    ('GND', 'Common Ground', 'gnd')
                ]
            },
            {
                'name': 'Command-Controlled LEDs',
                'pins': [
                    ('PC13', 'On-Board LED (Active-Low)', 'gpio'),
                    ('PA4', 'External Breadboard LED', 'gpio')
                ]
            },
            {
                'name': 'Power Supply',
                'pins': [
                    ('3.3V', '+3.3V Regulated VDD', 'power'),
                    ('GND', 'System Ground', 'gnd')
                ]
            }
        ],
        bottom_text="115200 Baud / 9600 Baud 8-N-1 | Commands: LED ON, LED OFF, LED TOGGLE | USART1"
    )

    # --- STM32 CAT10 ---
    draw(
        path=os.path.join(REPO_ROOT, "STM32", "CAT10", "circuit.png"),
        title="Continuous Assessment 10: STM32-Wemos Wi-Fi Modem & HTTP Server",
        board="STM32 Blue Pill + Wemos D1 Mini",
        mcu="STM32F103C8T6",
        peripherals=[
            {
                'name': 'Wemos D1 Mini (ESP8266 Modem)',
                'pins': [
                    ('PA2 (USART2_TX)', 'RX (Wemos ESP8266)', 'uart'),
                    ('PA3 (USART2_RX)', 'TX (Wemos ESP8266)', 'uart'),
                    ('5V', '5V Power Rail (Wemos)', 'power'),
                    ('GND', 'Common Ground', 'gnd')
                ]
            },
            {
                'name': 'Serial Debug Console (USART1)',
                'pins': [
                    ('PA9 (USART1_TX)', 'RXD of PC Serial Terminal', 'uart'),
                    ('PA10 (USART1_RX)', 'TXD of PC Serial Terminal', 'uart')
                ]
            },
            {
                'name': 'Status Indicator',
                'pins': [
                    ('PC13', 'Connection Status LED', 'gpio')
                ]
            }
        ],
        bottom_text="ESP8266 AT Commands (115200 Baud) | TCP Server Port 80 | HTTP 200 OK 'STM32 IoT Node'"
    )

    # --- STM32 CAT11 ---
    draw(
        path=os.path.join(REPO_ROOT, "STM32", "CAT11", "circuit.png"),
        title="Continuous Assessment 11: NUCLEO-F401RE GPIO & User Input Programming",
        board="ST NUCLEO-F401RE",
        mcu="STM32F401RET6",
        peripherals=[
            {
                'name': 'On-Board User LED (LD2)',
                'pins': [
                    ('PA5', 'Green User LED (Active-High)', 'gpio')
                ]
            },
            {
                'name': 'On-Board User Button (B1)',
                'pins': [
                    ('PC13', 'Blue Push Button (Active-Low)', 'gpio'),
                    ('GND', 'Internal Pull-Up Circuit', 'gnd')
                ]
            },
            {
                'name': 'ST-LINK V2-1 Virtual COM Port',
                'pins': [
                    ('PA2 (USART2_TX)', 'VCP RX (ST-Link USB)', 'uart'),
                    ('PA3 (USART2_RX)', 'VCP TX (ST-Link USB)', 'uart')
                ]
            },
            {
                'name': 'Power Distribution',
                'pins': [
                    ('+3.3V', 'VDD Regulated Supply', 'power'),
                    ('GND', 'Board Common Ground', 'gnd')
                ]
            }
        ],
        bottom_text="84 MHz ARM Cortex-M4 | LD2 on PA5 | B1 on PC13 | Non-blocking HAL_GetTick() Edge Logic"
    )

    # --- STM32 CAT12 ---
    draw(
        path=os.path.join(REPO_ROOT, "STM32", "CAT12", "circuit.png"),
        title="Continuous Assessment 12: BME280 Sensor Interfacing via I2C & Bosch API",
        board="ST NUCLEO-F401RE",
        mcu="STM32F401RET6",
        peripherals=[
            {
                'name': 'Bosch BME280 Environmental Sensor',
                'pins': [
                    ('PB8 (I2C1_SCL)', 'SCL (Serial Clock)', 'i2c'),
                    ('PB9 (I2C1_SDA)', 'SDA (Serial Data)', 'i2c'),
                    ('3.3V', 'VCC / VIN (Sensor Power)', 'power'),
                    ('GND', 'Sensor Ground Rail', 'gnd')
                ]
            },
            {
                'name': 'ST-LINK VCP Telemetry Console',
                'pins': [
                    ('PA2 (USART2_TX)', 'VCP Telemetry Output', 'uart'),
                    ('PA3 (USART2_RX)', 'VCP Telemetry Input', 'uart')
                ]
            },
            {
                'name': 'On-Board Activity Indicator',
                'pins': [
                    ('PA5', 'LD2 Sampling Activity LED', 'gpio')
                ]
            }
        ],
        bottom_text="I2C1 Standard Mode (100 kHz) | BME280 Address 0x76 | Bosch Sensor API (T, P, H Readings)"
    )

    # --- STM32 CAT13 ---
    draw(
        path=os.path.join(REPO_ROOT, "STM32", "CAT13", "circuit.png"),
        title="Continuous Assessment 13: BME280 I2C & MQTT Publisher via ESP8266",
        board="ST NUCLEO-F401RE + ESP8266 Modem",
        mcu="STM32F401RET6",
        peripherals=[
            {
                'name': 'Bosch BME280 Sensor (I2C1)',
                'pins': [
                    ('PB8 (I2C1_SCL)', 'SCL Clock Line', 'i2c'),
                    ('PB9 (I2C1_SDA)', 'SDA Data Line', 'i2c'),
                    ('3.3V', 'Sensor Supply VDD', 'power'),
                    ('GND', 'Sensor Ground', 'gnd')
                ]
            },
            {
                'name': 'ESP8266 Wi-Fi Module (USART1)',
                'pins': [
                    ('PA9 (USART1_TX)', 'RX (ESP8266 Module)', 'uart'),
                    ('PA10 (USART1_RX)', 'TX (ESP8266 Module)', 'uart'),
                    ('5V', 'Module VCC (5V Rail)', 'power'),
                    ('GND', 'Common Ground', 'gnd')
                ]
            },
            {
                'name': 'ST-LINK Telemetry & Status',
                'pins': [
                    ('PA2 (USART2_TX)', 'Telemetry Serial Monitor', 'uart'),
                    ('PA5', 'MQTT Publish Status (LD2)', 'gpio')
                ]
            }
        ],
        bottom_text="MQTT Broker: broker.emqx.io:1883 | Payload: JSON {'temperature', 'humidity', 'pressure'}"
    )

    print("All circuit schematics generated successfully!")

if __name__ == '__main__':
    generate_all()

