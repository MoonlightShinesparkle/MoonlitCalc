#include "pico/stdlib.h"
#include "pico/multicore.h"
#include "Util/GPIO.hpp"
#include <stdio.h>
#include <string>
#include "hardware/i2c.h"
#define uchar unsigned char
#define elseif else if

uchar ProgramAddress = 0b10100000;
uchar ReadAddress = 0b010100001;

void ShowUChar(const uchar &Val){
	printf("Value: %02X\n",Val);
}

/// @brief Sets up pins and board functions
void Setup() {
	printf("Meow\n");
	SetAsInput(0,ResistorMode::PullUp);
	SetAsOutput(1,ResistorMode::PullUp);
	gpio_set_function(0,GPIO_FUNC_I2C);
	gpio_set_function(1,GPIO_FUNC_I2C);

	i2c_init(i2c0,4000);

	SetAsOutput(PICO_DEFAULT_LED_PIN,ResistorMode::PullDown);

	printf("Setup I2C and pins!\n");
	gpio_put(PICO_DEFAULT_LED_PIN,1);
}

/// @brief Core 0 main method
/// @return Error code, 0 in success
int main() {
	stdio_init_all();
	sleep_ms(5000);
	printf("Mrow\n");
	Setup();
	sleep_ms(1000);

	uchar Recipient = 0;
	
	printf("Status: %u\n",i2c_read_blocking(i2c0,ProgramAddress,&Recipient,1,true));

	ShowUChar(Recipient);
}

// screen /dev/cu.usbmodem101