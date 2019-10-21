/* blink.c
 * you can build this with something like:
 * gcc -Wall blink.c -o blink -lbcm2835
 * sudo ./blink
*/
#include <bcm2835.h>

#define PIN 26
int main(int argc, char **argv)
{
    if (!bcm2835_init())return 1;
    bcm2835_gpio_fsel(PIN, BCM2835_GPIO_FSEL_OUTP);

    while (1)
    {
        bcm2835_gpio_write(PIN, HIGH);
        bcm2835_delay(500);
        bcm2835_gpio_write(PIN, LOW);
        bcm2835_delay(500);
    }
    bcm2835_close();
    return 0;
}
