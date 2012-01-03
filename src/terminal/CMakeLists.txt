set(TERMINAL_Headers
	terminal.h
	terminallistener.h
)

set(TERMINAL_Sources
	${TERMINAL_Headers}
	terminal.cpp
)

add_library(terminal ${TERMINAL_Sources})
