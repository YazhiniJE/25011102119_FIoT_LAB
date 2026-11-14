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

*Figure 3: Node-RED stream processing pipeline showing dual MQTT/HTTP ingestion branches, Drying Time & Formatting rule engine, OpenWeatherMap Chennai branch, and dashboard widget routing.*

### Flow Components & Processing Steps

**Top Branch — Local BME280 Sensor via MQTT:**
1. `BME280 MQTT` (`mqtt in`) node subscribes to topic `/yazhini` on `broker.emqx.io:1883` and receives JSON telemetry: `{"status":"success","temperature":XX,"humidity":XX,"pressure":XX}`.
2. An `inject` node provides test payload (temperature 23.95 °C, humidity 70.46 %, pressure 1016.44 hPa) for offline debugging without live hardware.
3. `Drying Time & Formatting` (8-output Function Node) validates the payload, normalizes pressure if raw Pa > 2000, computes a humidity/temperature drying factor, and routes:
   - **Port 0 (top):** `val(t)` → `Temperature` text widget (Live Temperature display) + `debug 3`
   - **Port 1:** `val(t)` → `Temp Gauge` (UI gauge, 0–50 °C)
   - **Port 2:** `val(h)` → `Humidity Gauge` (UI gauge, 0–100 %)
   - **Port 3:** `{payload:t, topic:'Temperature (°C)'}` → `Temp History` (time-series chart)
   - **Port 4:** `hours(4.5)` → `Cotton Time` text widget
   - **Port 5:** `hours(1.5)` → `Nylon Time` text widget
   - **Port 6:** `hours(2)` → `Polyester Time` text widget
   - **Port 7 (bottom):** `val(pr)` → `Pressure` gauge (UI gauge, 950–1050 hPa)
4. `debug 2` node captures the raw MQTT payload for troubleshooting.

**Bottom Branch — Chennai OpenWeather API:**
1. `inject openapi` node fires immediately on deploy, then repeats every 10 minutes (600 s).
2. `OpenWeatherMap Chennai` (`http request`) node fetches live JSON from `api.openweathermap.org` for Chennai, IN.
3. `Extract OWM Data` (4-output Function Node) validates `main.temp`, `main.humidity`, `main.pressure` and routes:
   - **Port 0 (top):** `Condition: <description>` → `Chennai Weather Display` text widget
   - **Port 1:** Chennai temperature → `Temperature` gauge (Chennai group)
   - **Port 2:** Chennai humidity → `Humidity` gauge (Chennai group)
   - **Port 3:** Chennai pressure → `Pressure` gauge (Chennai group)
4. `debug 4` node captures the raw OWM HTTP response for troubleshooting.

**Node-RED Flow JSON:** [`flow.json`](flow.json) — ready to import directly into Node-RED via *Import → Clipboard*.

---

## 5. Subtask Project Directory

The complete Keil µVision project workspace, CubeMX `.ioc` hardware configuration, and source files are maintained under:

- **[TASK15: Weather Intelligence Firmware & Project Files](TASK15/)**
  - CubeMX Configuration: [`Weather_MQTT.ioc`](TASK15/Weather_MQTT.ioc)
  - Keil Project Workspace: [`MDK-ARM/Weather_MQTT.uvprojx`](TASK15/MDK-ARM/Weather_MQTT.uvprojx)
  - Primary Firmware: [`Core/Src/main.c`](TASK15/Core/Src/main.c)
  - Bosch BME280 Driver: [`Core/Src/bme280.c`](TASK15/Core/Src/bme280.c) / [`Core/Inc/bme280.h`](TASK15/Core/Inc/bme280.h)
  - Node-RED Flow: [`flow.json`](TASK15/flow.json)

- **Node-RED Flow JSON (root CAT15):** [`flow.json`](flow.json) — import via Node-RED → *Hamburger Menu → Import → Clipboard*

---

## 6. Technical Inferences
1. **Microclimate vs Regional Macroclimate:** The verified $-2.2^\circ\text{C}$ temperature difference and $-8\%$ humidity variance confirm that local indoor/campus microclimates exhibit distinct thermal and hygrometric behaviors from generalized metropolitan weather reports.
2. **Evaporative Drying Kinetics:** The Clothes Drying Estimator accurately demonstrates that fabric drying rates are predominantly governed by relative humidity and the vapor pressure deficit. Synthetic hydrophobic fibers dry in less than half the time required by high-regain hydrophilic cotton ($1\,\text{h}\,15\,\text{min}$ vs $3\,\text{h}\,19\,\text{min}$).
3. **Atmospheric Tidal Consistency:** The 24-hour barometric pressure comparison exhibits near-perfect correlation with regional meteorological readings ($1008\,\text{hPa}$ vs $1007\,\text{hPa}$), verifying accurate calibration and compensation in the BME280 driver.
4. **Resilient Edge-to-Cloud Decoupling:** Decoupling edge data acquisition (STM32 HAL), communication translation (ESP8266), and analytics (Node-RED) ensures high reliability, non-blocking telemetry streaming, and modular extensibility.

