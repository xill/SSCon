#ifndef TERMINAL_LISTENER_H
#define TERMINAL_LISTENER_H

#include <string>

class TerminalListener {

public:

	/** Called when a new terminal line is committed. 
	 *
	 * should return a string reactionary string to be displayed.
	 */
	virtual std::string onCommit(std::string) = 0;
};

#endif