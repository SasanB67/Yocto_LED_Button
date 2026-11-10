LED Button Project (Raspberry Pi + Yocto)
What it does:
The LED is on while the push button is held and off when it's released.

Hardware:


LED	(GPIO17-Pin11)	    wiring: GPIO17 → 220–330 Ω resistor → LED (+, long leg) → LED (−) → GND

Button	(GPIO27-Pin13)	wiring: GPIO27 → button → GND

The button uses the Pi's internal pull-up, so no external resistor is needed. Released = 1, pressed = 0.
LED pin set to 1 = on, 0 = off.
