#pragma once

#define LED_DELAY_MS 500

#include "pico/stdlib.h"
#include "pico/multicore.h"
#include <stdio.h>
//#include "hw_config.h"
//#include "f_util.h"
#include "ff.h"
#include <string>

#define println(str) printf("%s\n",str)

extern "C"{
	#include <lcd1602_i2c.h>
}

// SECTION - GPIO definitions

//╔═════════════════════════ Start of GPIO definitions ═════════════════════════╗

    /**
	 * @brief Turns a GPIO into an output pin
	 * @param GPIO GPIO to set
     */
    void SetAsOutput(uint GPIO);

    /**
     * @brief Turns a GPIO into an input pin
	 * @param GPIO GPIO to set
	 * @param PullDown Use pull down resistor
     */
    void SetAsInput(uint GPIO, bool PullDown);

//╚══════════════════════════ End of GPIO definitions ══════════════════════════╝

// !SECTION - GPIO definitions
// SECTION - LCD definitions

//╔═════════════════════════ Start of LCD definitions ══════════════════════════╗

    /**
	 * @brief Display that it was made by Moonlight shinesparkle
	 * @param Display Pointer to display
     */
    void DisplayCredits(LCD *Display);

    /**    
     * @brief Displays strings given into the screen, manages the cursor to achieve it
	 * @param Display Pointer to active LCD display
	 * @param TxtA String to show in the first line
	 * @param TxtB String to show in the second line
     */
    void DisplayStrings(LCD *Display, const char TxtA[], const char TxtB[]);

    /**
     * @brief Shortens a string into a given length, leaves it as is if <= Length
     * @param Text Text to shorten
     * @param Length Desired length
     * @return std::string
     */
    std::string TrimString(std::string Text, const unsigned char Length);

//╚══════════════════════════ End of LCD definitions ═══════════════════════════╝

// !SECTION - LCD definitions
// SECTION - SD definitions

//╔══════════════════════════ Start of SD definitions ══════════════════════════╗

    /**
     * @brief For On-Screen debugging, turns FResults into displayable errors
	 * @param i Given FRESULT
	 * @return Short string displayable in the LCD
     */
    const char *FResultToStr(FRESULT i);

    /**    
	 * @brief Prints into an SD Card with a new line
	 * @param Ptr Pointer to the file
	 * @param Formatted Formatted string
	 * @param ... Optional arguments for formatting
	 * @return Status of the operation
     */
    int f_println(FIL *Ptr, const char* Formatted, ...);

//╚══════════════════════════ End of SD definitions ════════════════════════════╝

// !SECTION - SD definitions
// SECTION - CompactVec2 definitions

//╔═════════════════════ Start of CompactVec2 definitions ══════════════════════╗

    /// @brief Class capable of storing an X and Y coordinate in a single byte
    class CompactVec2{
        private:
        /// @brief Internal unsigned char that holds the components
        unsigned char Value;

        public:
        /**
         * @brief Get the X component
	     * @return X component
         */
        unsigned char GetX();

        /**        
         * @brief Get the Y component
	     * @return Y component
         */
        unsigned char GetY();

        /**        
         * @brief Set X component of the value
	     * @param X X component
         */
        void SetX(unsigned char X);

        /**        
         * @brief Set Y component of the value
	     * @param Y Y component
         */
        void SetY(unsigned char Y);

        /**        
         * @brief Set both components of the value
	     * @param X X component
	     * @param Y Y component
         */
        void SetValues(unsigned char X, unsigned char Y);

        /**        
         * @brief Creates a Vector2 stored in a single byte
	     * @param X X component
	     * @param Y Y component
         */
        CompactVec2(unsigned char X, unsigned char Y);

        /// @brief Creates an empty CompactVec2
        inline CompactVec2() : CompactVec2(0,0){};
    };

//╚══════════════════════ End of CompactVec2 definitions ═══════════════════════╝

// !SECTION - CompactVec2 definitions