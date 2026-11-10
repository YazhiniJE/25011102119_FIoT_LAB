import os
import shutil
import re

repo_stm = r"C:\IoT-Lab\25011102119_FIoT_LAB\STM32"
iot_lab = r"C:\IoT-Lab"

EXCLUDE_EXTS = {'.o', '.d', '.crf', '.htm', '.dep', '.uvguix', '.uvgui', '.uvopt', '.uvoptx', '.axf', '.map', '.lnp', '.lst', '.m51', '.bak'}
EXCLUDE_DIRS = {'DebugConfig', 'RTE', '.settings'}

def clean_copy_stm32_project(src_dir, dst_dir):
    os.makedirs(dst_dir, exist_ok=True)
    for root, dirs, files in os.walk(src_dir):
        dirs[:] = [d for d in dirs if d not in EXCLUDE_DIRS and not d.startswith('.')]
        rel = os.path.relpath(root, src_dir)
        cur_dst = os.path.join(dst_dir, rel) if rel != '.' else dst_dir
        os.makedirs(cur_dst, exist_ok=True)
        for f in files:
            ext = os.path.splitext(f)[1].lower()
            if any(f.endswith(ex) for ex in ['.uvgui.yazhi', '.uvguix.yazhi', '.build_log.htm']) or ext in EXCLUDE_EXTS:
                continue
            src_file = os.path.join(root, f)
            dst_file = os.path.join(cur_dst, f)
            shutil.copy2(src_file, dst_file)
            
            # sanitize any WiFi passwords in code
            if ext in ('.c', '.h'):
                with open(dst_file, 'r', encoding='utf-8', errors='ignore') as rf:
                    content = rf.read()
                
                # sanitize AT+CWJAP
                content = re.sub(r'AT\+CWJAP=\\"[^\\"]+\\",\\"[^\\"]+\\"', 'AT+CWJAP=\\"YOUR_WIFI_SSID\\",\\"YOUR_WIFI_PASSWORD\\"', content)
                content = re.sub(r'ESP8266_wifiConnect\(\s*"[^"]+"\s*,\s*"[^"]+"\s*\)', 'ESP8266_wifiConnect("YOUR_WIFI_SSID", "YOUR_WIFI_PASSWORD")', content)
                
                with open(dst_file, 'w', encoding='utf-8') as wf:
                    wf.write(content)

print("Starting clean copy of STM32 projects...")

# CAT8: Task 8A
cat8_a = os.path.join(repo_stm, 'CAT8', 'TASK_8A_GPIO_Input_Output')
clean_copy_stm32_project(os.path.join(iot_lab, r'STM32F103\Ex8\Ex8A'), cat8_a)
print("Copied CAT8 Task 8A")

# CAT8: Task 8B (derived with debounced toggle)
cat8_b = os.path.join(repo_stm, 'CAT8', 'TASK_8B_Event_Based_Control')
clean_copy_stm32_project(os.path.join(iot_lab, r'STM32F103\Ex8\Ex8A'), cat8_b)
# Update main.c in 8B for debounced toggle on PA3 switch & PA4 LED
b_main = os.path.join(cat8_b, 'Core', 'Src', 'main.c')
with open(b_main, 'r', encoding='utf-8', errors='ignore') as f:
    b_code = f.read()
old_while = """  while (1)
  {
		if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_3)== GPIO_PIN_RESET){
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);
		}
		else{
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);
		}
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  /* USER CODE END 3 */
}"""

new_while_b = """  /* USER CODE BEGIN 2 */
  uint8_t prev = GPIO_PIN_SET;
  uint32_t press_t = 0;
  /* USER CODE END 2 */

  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
    uint8_t cur = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_3);
    uint32_t now = HAL_GetTick();

    if (prev == GPIO_PIN_SET && cur == GPIO_PIN_RESET) {
        press_t = now;
    }

    // Toggle once per press; presses shorter than 30 ms are debounce noise
    if (prev == GPIO_PIN_RESET && cur == GPIO_PIN_SET) {
        if (now - press_t >= 30) {
            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_4);
            HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
        }
    }
    prev = cur;
  }
  /* USER CODE END 3 */
}"""
if old_while in b_code:
    b_code = b_code.replace(old_while, new_while_b)
    with open(b_main, 'w', encoding='utf-8') as f:
        f.write(b_code)
print("Configured CAT8 Task 8B logic")

# CAT8: Task 8C (short vs long press)
cat8_c = os.path.join(repo_stm, 'CAT8', 'TASK_8C_Short_Press_vs_Long_Press')
clean_copy_stm32_project(os.path.join(iot_lab, r'STM32F103\Ex8\Ex8A'), cat8_c)
c_main = os.path.join(cat8_c, 'Core', 'Src', 'main.c')
with open(c_main, 'r', encoding='utf-8', errors='ignore') as f:
    c_code = f.read()
new_while_c = """  /* USER CODE BEGIN 2 */
  uint8_t prev = GPIO_PIN_SET;
  uint32_t press_t = 0;
  uint8_t blink = 0;
  uint32_t blink_t = 0;
  /* USER CODE END 2 */

  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
    uint8_t cur = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_3);
    uint32_t now = HAL_GetTick();

    if (prev == GPIO_PIN_SET && cur == GPIO_PIN_RESET) {
        press_t = now;
    }

    if (prev == GPIO_PIN_RESET && cur == GPIO_PIN_SET) {
        if (now - press_t >= 1000) {
            // Long press >= 1s: toggle continuous blink mode
            blink = !blink;
        } else if (now - press_t >= 30) {
            // Short press < 1s: toggle LED state
            if (!blink) {
                HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_4);
                HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
            } else {
                blink = 0; // stop blink mode on short press
            }
        }
    }
    prev = cur;

    if (blink && (now - blink_t >= 250)) {
        HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_4);
        HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
        blink_t = now;
    }
  }
  /* USER CODE END 3 */
}"""
if old_while in c_code:
    c_code = c_code.replace(old_while, new_while_c)
    with open(c_main, 'w', encoding='utf-8') as f:
        f.write(c_code)
print("Configured CAT8 Task 8C logic")

# CAT9: Task 9A
cat9_a = os.path.join(repo_stm, 'CAT9', 'TASK_9A_Basic_UART_Communication')
clean_copy_stm32_project(os.path.join(iot_lab, r'STM32F103\Ex9\Ex9_UART'), cat9_a)
print("Copied CAT9 Task 9A")

# CAT9: Task 9B (string commands)
cat9_b = os.path.join(repo_stm, 'CAT9', 'TASK_9B_String_Based_Application_Logic')
clean_copy_stm32_project(os.path.join(iot_lab, r'STM32F103\Ex9\Ex9_UART'), cat9_b)
b9_main = os.path.join(cat9_b, 'Core', 'Src', 'main.c')
with open(b9_main, 'r', encoding='utf-8', errors='ignore') as f:
    b9_code = f.read()

# Add string include and command parser logic
old_9_while = """  while (1)
  {
		HAL_UART_Transmit(&huart1,&c,1,HAL_MAX_DELAY);
		HAL_Delay(1000);
		HAL_UART_Receive(&huart1, &c,1,HAL_MAX_DELAY);
		HAL_Delay(1000);
	
		
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }"""

new_9_while = """  /* USER CODE BEGIN 2 */
  uint8_t ch;
  char buf[64];
  uint8_t lastInd = 0;
  /* USER CODE END 2 */

  while (1)
  {
    if (HAL_UART_Receive(&huart1, &ch, 1, HAL_MAX_DELAY) == HAL_OK) {
        HAL_UART_Transmit(&huart1, &ch, 1, HAL_MAX_DELAY); // Echo character back
        if (ch == '\\r' || ch == '\\n') {
            if (lastInd > 0) {
                buf[lastInd] = '\\0';
                if (!strcmp(buf, "LED ON")) {
                    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);
                    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);
                } else if (!strcmp(buf, "LED OFF")) {
                    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);
                    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);
                } else if (!strcmp(buf, "LED TOGGLE")) {
                    HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
                    HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_4);
                }
                lastInd = 0;
            }
        } else {
            if (lastInd < 63) {
                buf[lastInd++] = ch;
            }
        }
    }
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }"""

if old_9_while in b9_code:
    b9_code = b9_code.replace(old_9_while, new_9_while)
    b9_code = b9_code.replace('/* USER CODE BEGIN Includes */', '/* USER CODE BEGIN Includes */\n#include <string.h>')
    with open(b9_main, 'w', encoding='utf-8') as f:
        f.write(b9_code)
print("Configured CAT9 Task 9B logic")

# CAT10: Tasks 10A, 10C, 10D
cat10_a = os.path.join(repo_stm, 'CAT10', 'TASK_10A_AT_Commands')
cat10_c = os.path.join(repo_stm, 'CAT10', 'TASK_10C_TCP_Server')
cat10_d = os.path.join(repo_stm, 'CAT10', 'TASK_10D_HTTP_Response')
clean_copy_stm32_project(os.path.join(iot_lab, r'STM32F103\Ex10\Wemos'), cat10_a)
clean_copy_stm32_project(os.path.join(iot_lab, r'STM32F103\Ex10\Task-10C'), cat10_c)
clean_copy_stm32_project(os.path.join(iot_lab, r'STM32F103\Ex10\Http response'), cat10_d)
print("Copied CAT10 tasks")

# CAT11: NUCLEO_GPIO_BringUp
cat11_dst = os.path.join(repo_stm, 'CAT11', 'NUCLEO_GPIO_BringUp')
clean_copy_stm32_project(os.path.join(iot_lab, r'STM32 Nucleo\Led-Blink'), cat11_dst)
# Populate main.c in CAT11
c11_main = os.path.join(cat11_dst, 'Core', 'Src', 'main.c')
with open(c11_main, 'r', encoding='utf-8', errors='ignore') as f:
    c11_code = f.read()

c11_while_old = """  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }"""

c11_while_new = """  /* USER CODE BEGIN 2 */
  uint8_t prev = GPIO_PIN_SET;
  uint32_t press_t = 0;
  uint8_t blink = 0;
  uint32_t blink_t = 0;
  /* USER CODE END 2 */

  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
    uint8_t cur = HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13);
    uint32_t now = HAL_GetTick();

    if (prev == GPIO_PIN_SET && cur == GPIO_PIN_RESET) {
        press_t = now;
    }

    if (prev == GPIO_PIN_RESET && cur == GPIO_PIN_SET) {
        if (now - press_t >= 500) {
            // Long press >= 500 ms: toggle blink mode
            blink = !blink;
        } else if (now - press_t >= 30) {
            // Short press: toggle LED and remember state
            if (!blink) {
                HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
            }
        }
    }
    prev = cur;

    if (blink && (now - blink_t >= 200)) {
        HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
        blink_t = now;
    }
  }"""
if c11_while_old in c11_code:
    c11_code = c11_code.replace(c11_while_old, c11_while_new)
    with open(c11_main, 'w', encoding='utf-8') as f:
        f.write(c11_code)
print("Configured CAT11 logic")

# CAT12: NUCLEO_BME280_I2C
cat12_dst = os.path.join(repo_stm, 'CAT12', 'NUCLEO_BME280_I2C')
clean_copy_stm32_project(os.path.join(iot_lab, r'STM32 Nucleo\Lab13-BME280\MQTT'), cat12_dst)
print("Copied CAT12 NUCLEO BME280 I2C project")

# CAT13: NUCLEO_BME280_ESP8266_MQTT
cat13_dst = os.path.join(repo_stm, 'CAT13', 'NUCLEO_BME280_ESP8266_MQTT')
clean_copy_stm32_project(os.path.join(iot_lab, r'STM32 Nucleo\ES_Proj\Weather_MQTT'), cat13_dst)
print("Copied CAT13 NUCLEO BME280 ESP8266 MQTT project")

print("All STM32 projects cleanly set up and sanitized!")

