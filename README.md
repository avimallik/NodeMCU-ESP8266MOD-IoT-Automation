# 🏠 NodeMCU IoT Home Automation System

A simple yet powerful home automation solution using **ESP8266/NodeMCU**.  
This project enables wireless control of home appliances (lights, fan, etc.) over Wi-Fi, via an HTTP web server and RESTful endpoints.  
Integrates seamlessly with the **ARM Robolox/Enigma Robolox** Android application.

---

## ✨ Features

- **Wi-Fi based control**: Remotely switch appliances ON/OFF using any device/browser on your network or the Android app.
- **Self-configuring Wi-Fi (WiFiManager)**: Easily connect NodeMCU to any Wi-Fi network, no hardcoding required.
- **Web dashboard**: Simple interface for toggling appliances.
- **Multiple devices supported**: Controls room light, mirror light, bed light, and fan (DC motor).
- **REST-style endpoints**: Easily integrate with custom apps.

---
## 📊 Algorithm
![Dashboard](https://github.com/user-attachments/assets/ebd184e3-8ce1-4de3-b3a8-0c7739e8a898)
---
## 📷 Schematic
![Dashboard](https://github.com/user-attachments/assets/2e68c3e2-d6f2-4d73-ab55-7830dd9b16cd)
---

## 📶 Hardware & Pinout

- **Platform:** NodeMCU ESP8266
- **Room Light:** D5
- **Mirror Light:** D6
- **Bed Light:** D7
- **Fan (Motor):** D3 (Plus), D4 (Minus)
- **Power:** 5V relay modules or direct low-voltage load (as per your circuit)

| Appliance      | NodeMCU Pin |
| -------------- | ----------- |
| Room Light     | D5          |
| Mirror Light   | D6          |
| Bed Light      | D7          |
| Fan +ve        | D3          |
| Fan -ve        | D4          |

**Note:** Use relay modules or opto-isolators for safe AC appliance switching.

---

## 🚀 Getting Started

### 1. Hardware Setup

- Connect each appliance (or relay controlling it) to the specified NodeMCU pins.
- Power your NodeMCU via USB or 5V.

### 2. Flashing the Code

- Open the `.ino` file in Arduino IDE.
- Install required libraries:
  - `ESP8266WiFi`
  - `ESP8266WebServer`
  - `DNSServer`
  - `WiFiManager`
- Compile and upload the code to your NodeMCU.

### 3. Wi-Fi Configuration

- On first boot, NodeMCU will create a Wi-Fi hotspot named `AutoConnectAP`.
- Connect to this hotspot using your phone or PC.
- A captive portal will appear. Choose your home Wi-Fi and enter credentials.
- NodeMCU will reboot and join your network.

### 4. Using the Web Server

- Open the Serial Monitor to find the assigned IP, or check your router.
- In any browser (or in the Android app), visit:  
  `http://<NodeMCU_IP>/`
- Use the buttons to toggle Room Light, Mirror Light, or Fan.

---

## 🌐 API Endpoints

| Endpoint            | Action                          | Response      |
|---------------------|---------------------------------|--------------|
| `/`                 | Main web dashboard (HTML)       | Web page     |
| `/room_light`       | Toggle Room Light               | `"0"`/`"1"`  |
| `/mirror_light`     | Toggle Mirror Light             | `"0"`/`"1"`  |
| `/fan`              | Toggle Fan (ON/OFF)             | `"0"`/`"1"`  |
| `/status`           | Get status of all appliances    | JSON string  |

**Example `/status` response:**  
```json
{'rl':'1','ml':'0','bl':'0','fan':'1'}

