#pragma once
#include <functional>

template <typename Argtype>

/// @brief Represents an executable function that invokes in certain conditions
class Event {

	using Proxy = std::function<void(Argtype)>;
	
	protected:
	
	/// @brief Executable function represented by the event
	Proxy Executable;

	public:
	
	/**
	 * @brief Binds a function to the event
	 * @param Connectable Function to bind
	 */
	inline void Connect(Proxy Connectable){
		Executable = std::forward<Proxy>(Connectable);
	};

	/**
	 * @brief Runs a binded function
	 * @param Arg Argument to pass into the function
	 */
	inline void Run(Argtype Arg){
		if (Executable){
			Executable(Arg);
		}
	};

	/// @brief Unbinds the function from the event
	inline void Disconnect(){
		Executable = nullptr;
	};

	/**
	 * @brief Proxy for Run
	 * @param Arg Argument to pass into Run
	 */
	void operator()(Argtype Arg) {
		Run(Arg);
	};
};