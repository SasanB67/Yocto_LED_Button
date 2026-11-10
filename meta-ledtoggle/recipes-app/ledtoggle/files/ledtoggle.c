/*
 * ledtoggle - LED is on while the button is held, off when released.
 *   LED    : GPIO17 (pin 11) -> 220-330 ohm resistor -> LED -> GND
 *   Button : GPIO27 (pin 13) -> button -> GND (internal pull-up)
 */
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/gpio.h>

static int request_line(int chip, int pin, int flags)
{
    struct gpiohandle_request req = { .lineoffsets = { pin }, .lines = 1, .flags = flags };
    if (ioctl(chip, GPIO_GET_LINEHANDLE_IOCTL, &req) < 0) { perror("gpio"); _exit(1); }
    return req.fd;
}

int main(void)
{
    int chip = open("/dev/gpiochip0", O_RDONLY);
    if (chip < 0) { perror("/dev/gpiochip0"); return 1; }

    int led = request_line(chip, 17, GPIOHANDLE_REQUEST_OUTPUT);
    int btn = request_line(chip, 27, GPIOHANDLE_REQUEST_INPUT | GPIOHANDLE_REQUEST_BIAS_PULL_UP);

    struct gpiohandle_data in, out = { .values = { 0 } };

    ioctl(led, GPIOHANDLE_SET_LINE_VALUES_IOCTL, &out);   /* start with LED off */

    for (;;) {
        ioctl(btn, GPIOHANDLE_GET_LINE_VALUES_IOCTL, &in);
        int on = in.values[0] ? 0 : 1;     /* pressed = 0 (pull-up) -> LED on */
        if (on != out.values[0]) {
            out.values[0] = on;
            ioctl(led, GPIOHANDLE_SET_LINE_VALUES_IOCTL, &out);
        }
        usleep(20000);                     /* poll every 20 ms */
    }
}
