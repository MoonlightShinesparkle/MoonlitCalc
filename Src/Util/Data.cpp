#include "Data.hpp"
#include <cstdarg>

// SECTION - CompactVec2

//╔═════════════════════ Start of CompactVec2 functions ════════════════════╗
//║ *- Get X and Y components of the value:									║
//║ Value = 0b  0000  0000													║
//║				└──┘  └──┘													║
//║				 X		Y													║

	unsigned char CompactVec2::GetX(){
		return (Value >> 4) & 0xF;
	}

	unsigned char CompactVec2::GetY(){
		return Value & 0xF;
	}

	void CompactVec2::SetX(unsigned char X){
		unsigned char Masked = Value & 0xF;
		Value = Masked | (X << 4);
	}

	void CompactVec2::SetY(unsigned char Y){
		unsigned char Masked = Value & 0xF0;
		Value = Masked | (Y & 0xF);
	}

	void CompactVec2::SetValues(unsigned char X, unsigned char Y){
		Value = (X << 4) | (Y & 0xF);
	}
	
	CompactVec2::CompactVec2(unsigned char X, unsigned char Y) : Value(0){
		SetValues(X,Y);
	}

//╚══════════════════════ End of CompactVec2 functions ═════════════════════╝

// !SECTION - CompactVec2
// SECTION - GPIO

//╔════════════════════════ Start of GPIO functions ════════════════════════╗

	void SetAsOutput(uint GPIO){
		gpio_init(GPIO);
		gpio_set_dir(GPIO, GPIO_OUT);
	}

	void SetAsInput(uint GPIO, bool PullDown = false){
		gpio_init(GPIO);
		gpio_set_dir(GPIO,GPIO_IN);
		if (PullDown){
			gpio_pull_down(GPIO);
		}
	}

//╚═════════════════════════ End of GPIO functions ═════════════════════════╝

// !SECTION - GPIO
// SECTION - LCD

//╔═════════════════════════ Start of LCD functions ════════════════════════╗

	void DisplayCredits(LCD *Display){
		DisplayStrings(Display, "Moonlit calc", "LUACalc");
		sleep_ms(2000);
		DisplayStrings(Display, "By Moonlight", "Shinesparkle");
		sleep_ms(2000);
	}

	void DisplayStrings(LCD *Display, const char TxtA[], const char TxtB[]){
		lcd_clear(Display);
		lcd_set_cursor_pos(Display,0,0);
		lcd_string(Display,TxtA);
		lcd_set_cursor_pos(Display,1,0);
		lcd_string(Display,TxtB);
	}

	std::string TrimString(std::string Text, const unsigned char Length){
		if (Text.length() > Length){
			Text.erase(Length);
		}
		return Text;
	}

//╚══════════════════════════ End of LCD functions ═════════════════════════╝

// !SECTION - LCD
// SECTION - SD

//╔═════════════════════════ Start of SD functions ═════════════════════════╗
	
	const char *FResultToStr(FRESULT i) {
		switch (i) {
			case FR_OK:
				return "Succeeded";
			case FR_DISK_ERR:
				return "Hard error in IO";
			case FR_INT_ERR:
				return "Assertion failed";
			case FR_NOT_READY:
				return "Phys cannot work";
			case FR_NO_FILE:
				return "File not found";
			case FR_NO_PATH:
				return "Path not found";
			case FR_INVALID_NAME:
				return "Invalid name";
			case FR_DENIED:
				return "Access denied";
			case FR_EXIST:
				return "Prohibited access";
			case FR_INVALID_OBJECT:
				return "Invalid object";
			case FR_WRITE_PROTECTED:
				return "Write protect";
			case FR_INVALID_DRIVE:
				return "Invalid drive no.";
			case FR_NOT_ENABLED:
				return "No work area";
			case FR_NO_FILESYSTEM:
				return "No valid FAT";
			case FR_MKFS_ABORTED:
				return "Aborted";
			case FR_TIMEOUT:
				return "Timeout";
			case FR_LOCKED:
				return "Locked";
			case FR_NOT_ENOUGH_CORE:
				return "Buffer not alloc";
			case FR_TOO_MANY_OPEN_FILES:
				return "Too many files";
			case FR_INVALID_PARAMETER:
				return "Invalid param";
			default:
				return "Unknown";
		}
	}

	int f_println(FIL *Ptr, const char* Formatted, ...){
		va_list Args;
		va_start(Args, Formatted);

		int Res = f_printf(Ptr,Formatted,Args);
		Res += f_putc('\n',Ptr);

		va_end(Args);

		return Res == 0? FR_OK : FR_INT_ERR;
	}

//╚══════════════════════════ End of SD functions ══════════════════════════╝

// !SECTION - SD