# EXP: CONTINUOUS ASSESSMENT 15

| Field | Details |
|---|---|
| **Project Title** | Sensor vs Chennai Weather Intelligence & Recommendations |
| **Date of Execution** | 05/11/2026 |
| **Hardware Platform** | STM32 NUCLEO-F401RE (ARM Cortex-M4) + BME280 Environmental Sensor + ESP8266 Wi-Fi Modem |
| **Course** | 25CS2741 – Fundamentals of Internet of Things + Lab |
| **Student Name** | Yazhini JE |
| **Register Number** | 25011102119 |
| **Cloud & Analytics Stack** | Public MQTT Broker (`broker.emqx.io:1883`), OpenWeather API, Node-RED Environmental Intelligence Engine |

---

## 1. Project Overview & Scope
This project designs and implements an end-to-end edge-to-cloud environmental intelligence system. An STM32 NUCLEO-F401RE microcontroller interfaces with a Bosch BME280 sensor to continuously acquire high-precision microclimate metrics (ambient temperature, barometric pressure, and relative humidity). Telemetry is formatted into lightweight JSON packets and published via an ESP8266 Wi-Fi modem to an MQTT broker. 

In the cloud/host analytics layer, a Node-RED flow ingests real-time sensor measurements alongside regional meteorological data fetched from the OpenWeather API for Chennai city. The system performs comparative statistical analysis, tracks 24-hour diurnal trends across multi-series charts, and drives an automated rule-based advisory engine (Clothes Drying Estimator) computing material-specific drying durations for cotton, polyester, and nylon garments.

---

## 2. Hardware Platform & Circuit Diagram

### Hardware Components
- **Development Board:** STMicroelectronics NUCLEO-F401RE
- **Microcontroller:** STM32F401RET6 (ARM Cortex-M4 32-bit RISC core with FPU @ 84 MHz)
- **Environmental Sensor:** Bosch Sensortec BME280 (I2C Digital Temperature, Humidity, and Pressure sensor)
- **Wi-Fi Modem:** ESP8266 (running Espressif standard AT command firmware)
- **Communication Buses:** I2C1 (PB6/PB7) @ 100 kHz, USART1 (PA9/PA10) @ 115200 baud
- **Power Rails:** +3.3V DC for BME280, +5V / +3.3V DC for ESP8266, Common System GND

### Pin Mapping Table
| STM32 Pin | Peripheral / Signal | Connected Module | Module Pin | Description |
|---|---|---|---|---|
| **PB6** | I2C1_SCL | Bosch BME280 | SCL | I2C Serial Clock (100 kHz Standard Mode) |
| **PB7** | I2C1_SDA | Bosch BME280 | SDA | I2C Serial Bidirectional Data (I2C address: `0x76`) |
| **PA9** | USART1_TX | ESP8266 Wi-Fi | RXD | Asynchronous Serial Transmit (115200 bps, 8N1) |
| **PA10** | USART1_RX | ESP8266 Wi-Fi | TXD | Asynchronous Serial Receive (115200 bps, 8N1) |
| **PA5** | GPIO Output | On-Board LED LD2 | Anode | User status and telemetry heartbeat indicator |
| **+3.3V** | Power Rail | BME280 Sensor | VCC | Regulated 3.3V power supply |
| **+5V / +3.3V** | Power Rail | ESP8266 Module | VIN / VCC | Primary power input for RF transceiver |
| **GND** | System Ground | BME280 & ESP8266 | GND | Common ground reference bus |

### Circuit Diagram
![Circuit Diagram](circuit.png)

*Figure 1: Verified hardware schematic interconnecting STM32 NUCLEO-F401RE, BME280 (I2C1 PB6/PB7), and ESP8266 modem (USART1 PA9/PA10).*

---

## 3. Node-RED Environmental Intelligence Dashboard

The live dashboard is rendered using Node-RED Dashboard widgets and organized into functional monitoring and recommendation sections:

![Node-RED Dashboard Telemetry](dashboard.png)

*Figure 2: Real-time Node-RED Dashboard displaying Clothes Drying Estimator recommendations, Local Sensor telemetry gauges, Chennai OpenWeather gauges, and 24-hour comparative trend curves.*

### 1. Clothes Drying Estimator (Advisory Output)
The advisory engine calculates drying durations based on ambient temperature ($31.2^\circ\text{C}$) and relative humidity ($58\%$), accounting for moisture retention properties:
* **Cotton garments:** `3 h 19 min` (High moisture absorption, natural cellulose fiber requires sustained evaporation).
* **Polyester garments:** `1 h 40 min` (Hydrophobic synthetic polymer fibers retain minimal water).
* **Nylon garments:** `1 h 15 min` (Thin synthetic weave with rapid moisture dissipation).

### 2. Local Environment (Sensor Readings)
Live telemetry acquired from the on-campus Bosch BME280 sensor:
* **Temperature:** `31.2 °C` (Gauge range: 0 to 50 °C)
* **Barometric Pressure:** `1008 hPa` (Gauge range: 950 to 1050 hPa)
* **Relative Humidity:** `58 %` (Gauge range: 0 to 100 %)

### 3. Chennai Live Weather (OpenWeather API Readings)
Concurrent regional meteorological baseline for Chennai city:
* **Temperature:** `33.4 °C` (Gauge range: 0 to 50 °C)
* **Barometric Pressure:** `1007 hPa` (Gauge range: 950 to 1050 hPa)
* **Relative Humidity:** `66 %` (Gauge range: 0 to 100 %)

### 4. Real-Time Comparative Metrics (Sensor vs Regional Baseline)
| Metric | Local Sensor (BME280) | Regional City (OpenWeather) | Variance ($\Delta$) | Technical Interpretation |
|---|:---:|:---:|:---:|---|
| **Temperature** | 31.2 °C | 33.4 °C | **-2.2 °C** | Local microclimate is 2.2 °C cooler than regional city urban core. |
| **Barometric Pressure** | 1008 hPa | 1007 hPa | **+1.0 hPa** | Strong agreement within $\pm 1\,\text{hPa}$, consistent with coastal sea-level baseline. |
| **Relative Humidity** | 58 % | 66 % | **-8.0 %** | Local ambient air is 8 % drier, significantly enhancing evaporative rates. |

### 5. 24-Hour Comparative Multi-Series Trend Charts
* **Temperature (°C) [24–38 °C range]:** Both curves trace characteristic diurnal heating cycles. The local sensor peaks at approximately 33 °C around midday, remaining consistently 1.5–2.5 °C below central Chennai, demonstrating shading and campus ventilation benefits.
* **Pressure (hPa) [1002–1012 hPa range]:** Demonstrates semidiurnal atmospheric tidal oscillations (two crests at ~10:00 and ~22:00, two troughs at ~04:00 and ~16:00). Both local and API trends track identically.
* **Humidity (%) [40–80 % range]:** Shows an inverse relationship to ambient temperature. Regional coastal air maintains higher humidity (60–80%), whereas local sensor readings drop to 50–58% during maximum solar insolation hours.

---

## 4. Node-RED Telemetry Flow Architecture

![Node-RED Flow Architecture](nodered_flow.png)

*Figure 3: Node-RED stream processing pipeline showing dual data acquisition streams, formatting logic, drying time estimator rule engine, and dashboard routing.*

### Flow Components & Processing Steps
1. **Local Sensor Ingestion Pipeline (Top Branch):**
   * `Every 10 s` Inject Node triggers periodic polling of the ESP8266 gateway.
   * `Sensor node (ESP8266)` HTTP/MQTT request node captures the raw sensor response.
   * `Parse sensor reply` Function Node deserializes JSON into `temperature`, `pressure`, and `humidity` payloads and fans out across multiple outputs:
     * Outputs 1, 2, 3 route to `Local Temperature`, `Local Pressure`, and `Local Humidity` UI gauge nodes.
     * Output 4 routes to the `Drying time estimator` rule engine.
     * Output 5 routes to `Chart feed: 1 per minute` delay/rate-limiter node &rarr; `Split for charts` &rarr; multi-series chart widgets.
2. **Drying Time Estimator Rule Engine:**
   * Receives normalized temperature and humidity.
   * Evaluates empirical drying formulas based on ambient vapor pressure deficit ($VPD$) and fabric moisture regain factors.
   * Emits formatted duration strings (`3 h 19 min`, `1 h 40 min`, `1 h 15 min`) to UI text cards for Cotton, Polyester, and Nylon.
3. **Regional Weather API Ingestion Pipeline (Bottom Branch):**
   * `Every 10 min` Inject Node triggers the baseline weather query.
   * `Build OpenWeather URL` constructs the REST request with Chennai coordinates and API parameters.
   * `OpenWeather` HTTP Request Node queries the external OpenWeather API service.
   * `Parse Chennai weather` extracts `main.temp`, `main.pressure`, and `main.humidity`.
   * Telemetry routes to `Chennai Temperature`, `Chennai Pressure`, and `Chennai Humidity` gauges, as well as the shared multi-series charts.

---

## 5. Subtask Project Directory

The complete Keil µVision project workspace, CubeMX `.ioc` hardware configuration, and source files are maintained under:

- **[TASK15: Weather Intelligence Firmware & Project Files](TASK15/)**
  - CubeMX Configuration: [`Weather_MQTT.ioc`](TASK15/Weather_MQTT.ioc)
  - Keil Project Workspace: [`MDK-ARM/Weather_MQTT.uvprojx`](TASK15/MDK-ARM/Weather_MQTT.uvprojx)
  - Primary Firmware: [`Core/Src/main.c`](TASK15/Core/Src/main.c)
  - Bosch BME280 Driver: [`Core/Src/bme280.c`](TASK15/Core/Src/bme280.c) / [`Core/Inc/bme280.h`](TASK15/Core/Inc/bme280.h)

---

## 6. Technical Inferences
1. **Microclimate vs Regional Macroclimate:** The verified $-2.2^\circ\text{C}$ temperature difference and $-8\%$ humidity variance confirm that local indoor/campus microclimates exhibit distinct thermal and hygrometric behaviors from generalized metropolitan weather reports.
2. **Evaporative Drying Kinetics:** The Clothes Drying Estimator accurately demonstrates that fabric drying rates are predominantly governed by relative humidity and the vapor pressure deficit. Synthetic hydrophobic fibers dry in less than half the time required by high-regain hydrophilic cotton ($1\,\text{h}\,15\,\text{min}$ vs $3\,\text{h}\,19\,\text{min}$).
3. **Atmospheric Tidal Consistency:** The 24-hour barometric pressure comparison exhibits near-perfect correlation with regional meteorological readings ($1008\,\text{hPa}$ vs $1007\,\text{hPa}$), verifying accurate calibration and compensation in the BME280 driver.
4. **Resilient Edge-to-Cloud Decoupling:** Decoupling edge data acquisition (STM32 HAL), communication translation (ESP8266), and analytics (Node-RED) ensures high reliability, non-blocking telemetry streaming, and modular extensibility.

