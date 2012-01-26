set(SSCon_Headers
# textbuilder
	textfactory.h
	fontmanager.h
	terminal_font1.h
	text_include.h
	fontdata.h
	fontmaps.h
	
# terminal
	terminal.h
	terminallistener.h
)

set(SSCon_Sources
	${SSCon_Headers}
# textbuilder
	textfactory.cpp
	fontmanager.cpp
	fontmaps.cpp
	
# terminal
	terminal.cpp
)

add_library(SSCon ${SSCon_Sources})
