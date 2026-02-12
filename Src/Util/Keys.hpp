#pragma once

#define uchar unsigned char
#define KbdWidth 5
#define KbdHeight 6
#define ShiftIn 13
#define KbdModeIn 14
#define CachedKeys 10

#include <Src/Util/Data.hpp>
#include <Src/Util/Events/Event.hpp>

//╔════════════════════════════════════ Start of constants ════════════════════════════════════╗
//║ *- Specific keys																		   ║

	/// @brief Enter key
	const uchar KeyEnter = 6;

	/// @brief Space key
	const uchar KeySpace = ' ';

	/// @brief Delete key
	const uchar KeyDelete = 127;

	/// @brief ESC key
	const uchar KeyEsc = 27;

	/// @brief Execute key; Return
	const uchar KeyExec = 23;

	/// @brief Tabulation key
	const uchar KeyTab = '\t';

	/// @brief Bootsel mode key
	const uchar KeyUpgrade = 0b11011101;

//║ *- Arrow keys																			   ║

	/// @brief Left arrow key
	const uchar KeyLeft = 0b10100001;

	/// @brief Up arrow key
	const uchar KeyUp = 0b10100010;

	/// @brief Down arrow key
	const uchar KeyDown = 0b10100011;

	/// @brief Right arrow key
	const uchar KeyRight = 0b10100100;

//╚═════════════════════════════════════ End of constants ═════════════════════════════════════╝

//╔════════════════════════════════════ Start of key class ════════════════════════════════════╗

	/// @brief Information container for keys
	class Key{
		protected:

		/// @brief Position within the button matrix
		CompactVec2 Position;

		/// @brief Layout of the keyboard: Shift, Keyboard, Shift+Keyboard, None
		uchar Layout;

		/// @brief Defines key useability
		bool Viable = true;

		public:
		/**
		 * @brief Creates a prepositioned key
		 * @param X X position
		 * @param Y Y position
		 * @param Layout Current layout
		 */
		inline Key(uchar X, uchar Y, uchar Layout){
			Position = CompactVec2(X,Y);
			this->Layout = Layout;
		}

		/// @brief Creates a null key
		inline Key() : Key(0,0,0){
			Nullify();
		}

		/**
		 * @brief Returns the char equivalent of the key
		 * @return Char equivalent of the key
		 */
		uchar GetChar();

		/**
		 * @brief Returns key equivalence
		 * @param Eq Key to compare to
		 * @return Equivalence
		 * @note Null keys can't be equal to other keys
		 */
		inline bool operator ==(Key Eq){
			return !IsNull() && !Eq.IsNull() && (((uchar) Eq) == GetChar());
		}

		/**
		 * @brief Check if the key belongs to a given layout
		 * @param Comp Layout
		 * @return Key existance within given layout
		 */
		inline bool IsSameLayout(uchar Comp){
			return Comp == Layout;
		}

		/// @brief Another access to GetChar()
		inline operator uchar(){
			return GetChar();
		}

		/// @brief Removes viability
		inline void Nullify(){
			Viable = false;
		}

		/**
		 * @brief Checks if the key has been nullified
		 * @return Key being null
		 */
		inline bool IsNull(){
			return !Viable;
		}

		/**
		 * @brief Regenerates key, giving a viability
		 * @param X X position in the keyboard
		 * @param Y Y position in the keyboard
		 * @param Layout Layout of the keyboard
		 */
		inline void Recreate(uchar X, uchar Y, uchar Layout){
			Position.SetValues(X,Y);
			this->Layout = Layout;
			Viable = true;
		}

		/// @brief Copies another key's layout, giving a viability
		/// @param Other Key whose values will be copied
		inline void Recreate(Key Other){
			Recreate(Other.Position.GetX(),Other.Position.GetY(),Other.Layout);
		}
	};

//╚═════════════════════════════════════ End of key class ═════════════════════════════════════╝

//╔═════════════════════════════════════ Start of keyboard ════════════════════════════════════╗

	/// @brief LCD proxy
	inline LCD* UseableScreen = nullptr;
	inline Event<uchar> OnKeyPressed;
	inline Event<uchar> WhilePressed;
	inline Event<uchar> OnKeyReleased;

	/**
	 * @brief Creates Fn keys
	 * @param C Number of the key
	 * @return The Fn key #C
	 */
	inline uchar Fn(uchar C){
		return 0b10000000 | C;
	}

	/**
	 * @brief Creates a Sh key
	 * @param C Number of the key
	 * @return The Shortcut key #C
	 */
	inline uchar Sh(uchar C){
		return 0b11000000 | C;
	}

//║ *- Keyboard layout																 		   ║
//║ *- 4 layouts are possible based on if shift/keyboard are active					 		   ║

	/**
	 * @brief A tridimensional array which holds the available layouts, composed of:
	 * @brief - Keyboard layout
	 * @brief - Rows of uchar arrays within the layout
	 * @brief - UChars representing every key within the row
	 * @note The layouts are as follows
	 * @note 0 - Regular
	 * @note 1 - Shift
	 * @note 2 - Keyboard
	 * @note 3 - Shift-Keyboard
	 */
	const uchar Layouts[4][KbdHeight][KbdWidth]{
		// Regular layout (+0 +0)
		{{KeyEsc,Fn(1),Fn(2),Fn(3),KeyDelete},
		{KeyTab,Fn(4),Fn(5),Fn(6),Fn(7)},
		{Sh(1),Sh(2),Sh(3),Sh(4),KeyExec},
		{Sh(5),Sh(6),Sh(7),Sh(8),KeyEnter},
		{Sh(9),KeyLeft,KeyUp,KeyDown,KeyRight},
		{KeyUpgrade,KeySpace,KeySpace,KeySpace,KeyEnter}},

		// Shift layout (+1 +0)
		{{'1','2','3','4','5'},
		{'6','7','8','9','0'},
		{'(',')','[',']','^'},
		{'{','}','+','-','%'},
		{'*','/','?','!','#'},
		{'~','_','"','\'','='}},

		// Keyboard Layout (+0 +2)
		{{'q','w','e','r','t'},
		{'y','u','i','o','p'},
		{'a','s','d','f','g'},
		{'h','j','k','l','z'},
		{'x','c','v','b','n'},
		{'m',KeySpace,KeySpace,KeySpace,KeyEnter}},

		// Shift keyboardLayout (+1 +2)
		{{'Q','W','E','R','T'},
		{'Y','U','I','O','P'},
		{'A','S','D','F','G'},
		{'H','J','K','L','Z'},
		{'X','C','V','B','N'},
		{'M',KeyLeft,KeyUp,KeyDown,KeyEnter}}
	};

	/**
	 * @brief Obtains a key's char
	 * @return Key char or null character if null
	 */
	inline uchar Key::GetChar(){
		return IsNull()? '\0' : Layouts[Layout][Position.GetY()][Position.GetX()];
	}

	/**
	 * @brief Adds pull up resistors to SetAsInput function
	 * @param GPIO 
	 */
	void SetKeyboardInput(uchar GPIO);

//║ *- Inpin & Outpin are keyboard based													   ║
//║	   KBD							 Pico													   ║
//║	 ╔═════╗						╔════╗													   ║
//║	 ╠═════╣			Inpin		║	 ║													   ║
//║	 ║	   ║ <┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅ ║	 ║													   ║
//║	 ║	   ║ ┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅> ║	 ║													   ║
//║	 ╚═════╝			Outpin		╚════╝													   ║
//║																							   ║

	/**
	 * @brief List of keyboard outputs (Outpins)
	 * @note Outpins are keyboard orientated; they send signals to the pico
	 */
	const uchar KeyboardOutputs[KbdWidth]{
		2,3,4,5,6
	};

	/**
	 * @brief List of keyboard inputs (Inpins)
	 * @note Inpins are keyboard orientated; they recieve signals from the pico
	 */
	const uchar KeyboardInputs[KbdHeight]{
		7,8,9,10,11,12
	};

	/// @brief Sets input and output pins to drive the keyboard
	void SetupKeys();

	/// @brief Map of pressed keys as booleans
	extern bool KeysPressed[KbdHeight][KbdWidth];

	/// @brief Number of keys currently pressed
	extern uchar NumKeysPressed;

	/// @brief Keys get added here when just pressed
	extern Key KeysJustPressed[CachedKeys];

	/// @brief Keys get added here when pressing
	extern Key KeysPressing[CachedKeys];

	/// @brief Scans through the keyboard to check for keys, updates them in all arrays/values
	void Scan();

	/**
	 * @brief Checks if a key exists in an array of length CachedKeys
	 * @param LookFor Key to look for
	 * @param In Array to look into
	 * @param Position Position of LookFor in In or -1
	 * @return Existance of LookFor in In
	 */
	bool IsInKeyList(Key LookFor, Key In[CachedKeys], int &Position);
	 

	/**
	 * @brief Checks if a key exists in an array of length CachedKeys
	 * @param LookFor Key to look for
	 * @param In Array to look into
	 * @return Existance of LookFor in In
	 */
	bool IsInKeyList(Key LookFor, Key In[CachedKeys]);

	/**
	 * @brief Attempts to insert the given key into an array
	 * @param Insertable Key to insert
	 * @param In List to insert into
	 */
	void InsertInto(Key Insertable, Key In[CachedKeys]);

	/// @brief Forces the pico to enter bootsel mode without requiring pressing "BOOTSEL"
	void ForceBootsel();

//╚══════════════════════════════════════ End of keyboard ═════════════════════════════════════╝