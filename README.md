#### ESPHOME-MicRadar-R60ABD1-MMWARE-SENSOR
---
![image alt](https://github.com/Niwun-githup/MicRadar-R60ABD1-FOR-ESPHOME/blob/5f91e4ab1d5da18389b4a467d33bcd33ff1bbcb3/R6ABD1.jpg)

The display of sensor values ​​(e.g. Bed Status, Heartbeat Rate, Motion Sensor, Presence Sensor, Respiratory Rate, and Sleep Quality) in Home Assistant can be described as follows:
1. Bed Status: A value of 0 means no "Out of Bed" status is detected. A value of 1 means "In Bed".
2. Heartbeat Rate: Displays the heart rate of a person in the area that the sensor can detect (in BPM: Beats Per Minute). A value of 67 means a normal heart rate.
3. Motion Sensor: A value of 1 means movement is detected in the area covered by the sensor. A value of 0 means there is no movement.
4. Presence Sensor: A value of 1 means there is a person in the area that the sensor can detect. A value of 0 means there is no person in the area.
5. Respiratory Rate: A value of 16 means the respiratory rate of a person in the area (in RPM: Respirations Per Minute).
6. Sleep Quality: A value of 0 means there is no information about sleep quality. This value may require additional calculations (or data from additional sensors) to obtain an accurate value.
---   
#### Connection techniques MicRadar-R60ABD1 + SEEED STUDIO XIAO ESP32C6
![image alt](https://github.com/Niwun-githup/MicRadar-R60ABD1-FOR-ESPHOME/blob/5f91e4ab1d5da18389b4a467d33bcd33ff1bbcb3/ESP32C6_R60ABD1.JPG)

## Installation
Download the file in header : r60abd1_sensor.h and copy it to esphome (/homeassistant/esphome/header/r60abd1_sensor.h) in your main Home Assistant config/esphome folder
```
/header/r60abd1_sensor.h
```
In the Home Assistant add-on, click ESPHome > Open the web GUI and create a new device by selecting the "Continue" option and giving it a name, e.g.: Then paste the code: r60abd1-espc6-sensor.yaml and edit it.
```
R60abd1-espc6-sensor.yaml


substitutions:
  device_name: "mr60abd1-mmwave-sensor"
  device_name_pretty: "mr60abd1-mmwave-sensor"
  ssid: !secret wifi_ssid
  wifi_password: !secret wifi_password
  uart_tx_pin: GPIO17
  uart_rx_pin: GPIO16

esphome:
  name: r60abd1-espc6-sensor
  friendly_name: R60ABD1-ESPC6-SENSOR
  includes:
    - header/r60abd1_sensor.h
  

esp32:
  board: esp32-c6-devkitm-1
  flash_size: 4MB
  variant: esp32c6
  framework:
    type: esp-idf
    version: "5.3.0"
    platform_version: 6.8.1
    sdkconfig_options:
      CONFIG_ESPTOOLPY_FLASHSIZE_4MB: y
      
# Enable logging
logger:
  logs:
    level: DEBUG
  
  

# Enable Home Assistant API
api:
  encryption:
    key: ".................................."

ota:
  - platform: esphome
    password: "..............................."

wifi:
  ssid: !secret wifi_ssid
  password: !secret wifi_password
  use_address: xxx.xxx.xxx.xxx.

  # Enable fallback hotspot (captive portal) in case wifi connection fails
  ap:
    ssid: "..............."
    password: ".............."

captive_portal:
# UART configuration for communication with the sensor
uart:
  id: uart_bus
  tx_pin: GPIO17
  rx_pin: GPIO16
  baud_rate: 115200

sensor:
  - platform: custom
    lambda: |-
      auto r60_sensor = new R60ABD1Sensor(id(uart_bus));
      App.register_component(r60_sensor);
      return {r60_sensor->presence_sensor,
              r60_sensor->motion_sensor,
              r60_sensor->heartbeat_sensor,
              r60_sensor->respiratory_sensor,
              r60_sensor->sleep_quality_sensor,
              r60_sensor->bed_status_sensor};
    sensors:
      - name: "Presence Sensor"
      - name: "Motion Sensor"
      - name: "Heartbeat Rate"
      - name: "Respiratory Rate"
      - name: "Sleep Quality"
      - name: "Bed Status"
       
```
