<div align="center">
  <h1> 🪴 Watering monitor 🚿 </h1>
  <p>A compilation of arduino projects I've done</p>
</div>

## 📃 Description
My first project for arduino, a system that monitors moisture, displays the information on a screen and irrigates when needed.

## 🔮 Features
- Displays the current moisture on the screen
- Multi-language support
- Easy usage through a joystick
- Toggleable automatic irrigation
- Allow customize minimum moisture percent and sample interval

## 📝 Requirements
- Arduino board (I used an Arduino UNO)
- Capacitive soil moisture sensor
- LCD 20x4
- Analog joystick
- 5V Relay module with optocoupler
- 3~6V Submersible mini water pump
- Breadboard (Just to abuse power and ground rails)
- 5V Power supply (I used a PowerBank)

## 🔮 Features
- Displays the current moisture on the screen
- Multi-language support
- Easy usage through a joystick
- Toggleable automatic irrigation
- Allow customize minimum moisture percent and sample interval

## 📚 Libraries/Dependencies
- [LCDMenuLib2](https://github.com/Jomelo/LCDMenuLib2)
- [LCD_I2C](https://github.com/blackhack/LCD_I2C)
- [neotimer](https://github.com/jrullan/neotimer)

## ⚡Circuit
<div align="center">
  <img src="https://raw.githubusercontent.com/IvanCraft623/arduino-projects/main/watering-monitor/circuit.png" width="75%">
</div>

## 🕹️ Usage
- It will start at the main screen where the moisture percentage is displayed, to access the menu press the joystick button.

- To move through the menu use the joystick, incomplete texts can be scrolled by moving the joystick to the right.

- To enter or select an option use the joystick button.

- When selecting the "Min moisture" or "Sample interval" options, you can modify the values by moving the joystick left(decrease) or right(increase). To save, press the joystick button again.

- To return to the main screen you can use the option at the bottom of the menu or after a few seconds of inactivity it will return automatically.