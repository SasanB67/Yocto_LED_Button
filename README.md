LED Button Project (Raspberry Pi + Yocto)
What it does:
The LED is on while the push button is held and off when it's released.

Hardware:

Part	GPIO	Physical pin	Wiring
LED	GPIO17	Pin 11	GPIO17 → 220–330 Ω resistor → LED (+, long leg) → LED (−) → GND
Button	GPIO27	Pin 13	GPIO27 → button → GND
Ground	—	Pin 6, 9, 14…	shared GND
The button uses the Pi's internal pull-up, so no external resistor is needed. Released = 1, pressed = 0.
LED pin set to 1 = on, 0 = off.
