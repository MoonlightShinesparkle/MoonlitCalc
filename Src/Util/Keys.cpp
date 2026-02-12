#include "Keys.hpp"
#include "pico/bootrom.h"

//╔═══════════════════════════ Start of Key IO & setup functions ═══════════════════════════╗

	void SetKeyboardInput(uchar GPIO){
		SetAsInput(GPIO, false);
		gpio_pull_up(GPIO);
	}

	void SetupKeys(){
		for (uchar Inpin : KeyboardInputs){
			SetAsOutput(Inpin);
			gpio_put(Inpin,1);
		}
		for (uchar Outpin : KeyboardOutputs){
			SetKeyboardInput(Outpin);
		}
		SetKeyboardInput((uchar) ShiftIn);
		SetKeyboardInput((uchar) KbdModeIn);
	}

//╚════════════════════════════ End of Key IO & setup functions ════════════════════════════╝


//╔══════════════════════════════ Start of Key array functions ═════════════════════════════╗

	bool KeysPressed[KbdHeight][KbdWidth];
	Key KeysJustPressed[CachedKeys];
	Key KeysPressing[CachedKeys];
	uchar NumKeysPressed = 0;

	bool IsInKeyList(Key LookFor, Key In[CachedKeys], int &Position){
		bool Returnable = false;
		Position = -1;
		for (uchar i = 0; i < CachedKeys; i++){
			uchar Val = In[i];
			if (Val == LookFor){
				Returnable = true;
				Position = i;
				break;
			}
		}
		return Returnable;
	}

	bool IsInKeyList(Key LookFor, Key In[CachedKeys]){
		bool Returnable = false;
		for (uchar i = 0; i < CachedKeys; i++){
			uchar Val = In[i];
			if (Val == LookFor){
				Returnable = true;
				break;
			}
		}
		return Returnable;
	}
	
	void InsertInto(Key Insertable, Key In[CachedKeys]){
		for (uchar i = 0; i < CachedKeys; i++){
			if (In[i].IsNull()){
				In[i].Recreate(Insertable);
				break;
			}
		}
	}

	void ForceBootsel(){
		if (UseableScreen != nullptr){
			DisplayStrings(UseableScreen,"Entered bootsel","mode in USB");
		}
		gpio_put(PICO_DEFAULT_LED_PIN,0);
		reset_usb_boot(0,0);
	}

	Key Code = Key();

	void Scan(){
		NumKeysPressed = 0;
		uchar CurrXPos = 0;
		uchar CurrYPos = 0;
		const uchar KBMode = !gpio_get(ShiftIn)+(2*!gpio_get(KbdModeIn));

		for (uchar y : KeyboardInputs){
			CurrXPos = 0;

			gpio_put(y,0);
			sleep_us(15);
			
			for (uchar x : KeyboardOutputs){
				// Check if column is pressed in the current row
				bool Pressed = gpio_get(x) == 0;
				int KeyPos = 0;
				Code.Recreate(CurrXPos, CurrYPos, KBMode);

				if (Pressed){
					// Instantly toss to bootsel mode
					if (Code.GetChar() == KeyUpgrade){
						ForceBootsel();
					}
					
					// Normal key procedure
					if (IsInKeyList(Code, KeysJustPressed, KeyPos)){

						KeysJustPressed[KeyPos].Nullify();
						InsertInto(Code,KeysPressing);
						// Key pressing
						WhilePressed(Code.GetChar());

					} else if (!IsInKeyList(Code, KeysPressing)){

						// Key just got pressed
						OnKeyPressed(Code.GetChar());
						InsertInto(Code,KeysJustPressed);

					} else if (IsInKeyList(Code, KeysPressing)) {

						// Key pressing
						WhilePressed(Code.GetChar());

					}
					NumKeysPressed++;
				} else if (IsInKeyList(Code, KeysPressing, KeyPos)){

					// Key released
					OnKeyReleased(Code.GetChar());
					KeysPressing[KeyPos].Nullify();

				}

				KeysPressed[CurrYPos][CurrXPos] = Pressed;

				CurrXPos++;			
			}

			gpio_put(y,1);
			CurrYPos++;
		}

		// Check if keys are part of layout KBMode
		for (uchar c = 0; c < CachedKeys; c++){
			Key Btn = KeysPressing[c];
			if (Btn.IsNull()){
				continue;
			}
			if (!Btn.IsSameLayout(KBMode)){
				KeysPressing[c].Nullify();
			}
		}
	}
	
//╚═══════════════════════════════ End of Key array functions ══════════════════════════════╝