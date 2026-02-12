#include <Src/Util/Data.hpp>
#include <Src/Util/Keys.hpp>
//#include "Data/App/FileExplore/Explorer.hpp"

LCD Display;

int ret;
char Buffer[100];

// Must be multi-thread since kernel will run tasks in the background such as keyboard management
void alter_main(){
	println("[Core] Core 2 runned");
	//Explorer MainExplorer;
	//MainExplorer.Run();
}

// TODO: implement refreshing when ShouldRefresh == true instead of always refreshing
bool ShouldRefresh = false;

int main() {
	stdio_init_all();
	sleep_ms(3000);

	println("[Init] Initializing LED GPIO");
	gpio_init(PICO_DEFAULT_LED_PIN);
	gpio_set_dir(PICO_DEFAULT_LED_PIN,true);

	println("[Init] Initializing LCD screen");
	lcd_init(&Display, 0x27, 0, 1, i2c0);

	UseableScreen = &Display;

	println("[Init] Displaying...");
	DisplayCredits(&Display);

	//println("[Init] Setting up keys..");
	//SetupKeys();

	//sleep_ms(10);

	multicore_launch_core1(*alter_main);

	println("[Kbd] Keyboard initialized");
	while (true) {
		//Scan();
		sleep_ms(1);
		// char Chars[CachedKeys];
		// uchar j = 0;
		// for (uchar i = 0; i < CachedKeys; i++){
		// 	Key Pressing = KeysPressing[i];
		// 	if (!Pressing.IsNull()){
		// 		Chars[j] = Pressing.GetChar();
		// 		j++;
		// 	}
		// }
		// for (uchar i = j; i < CachedKeys; i++){
		// 	Chars[i] = '\0';
		// }
		// DisplayStrings(&Display,
		// 	(std::string("Pressing: [") + std::to_string(NumKeysPressed) + "]").c_str(),
		// 	Chars
		// );
		// sleep_ms(1000);
	}

	return 0;
}