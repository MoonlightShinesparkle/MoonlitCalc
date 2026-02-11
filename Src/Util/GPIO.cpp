#include "GPIO.hpp"

void SetResistor(uint GPIO, ResistorMode Mode = None) {
	switch (Mode) {
		case (ResistorMode::PullDown):
			gpio_pull_down(GPIO);
			break;
		case (ResistorMode::PullUp):
			gpio_pull_up(GPIO);
			break;
		default:
			break;
	}
}

void SetAsInput(uint GPIO, ResistorMode Mode = None) {
	gpio_init(GPIO);
	gpio_set_dir(GPIO,false);
	SetResistor(GPIO,Mode);
}

void SetAsOutput(uint GPIO, ResistorMode Mode = None) {
	gpio_init(GPIO);
	gpio_set_dir(GPIO,true);
	SetResistor(GPIO,Mode);
}