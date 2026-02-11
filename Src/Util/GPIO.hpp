// GPIO management file, allows simple setup of GPIO pins
#include "pico/stdlib.h"

/// @brief Defines which resistor to use in a pin: PullUp/PullDown/None
enum ResistorMode{
	/// @brief Should not set up a resistor
	None,
	/// @brief Use a pull up resistor
	PullUp,
	/// @brief Use a pull down resistor
	PullDown
};

/// @brief Turns a GPIO into a input pin
/// @param GPIO Pin to prepare
/// @param Mode What resistor to use in the pin
void SetAsInput(uint GPIO, ResistorMode Mode);

/// @brief Turns a GPIO into a output pin
/// @param GPIO Pin to prepare
/// @param Mode What resistor to use in the pin
void SetAsOutput(uint GPIO, ResistorMode Mode);

/// @brief Sets up the resistor in a GPIO pin
/// @param GPIO Pin to set
/// @param Mode What resistor to use in the pin
void SetResistor(uint GPIO, ResistorMode Mode);