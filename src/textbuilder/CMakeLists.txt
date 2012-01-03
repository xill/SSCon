set(TEXTBUILDER_Headers
	textfactory.h
	fontmanager.h
	terminal_font1.h
	text_include.h
	fontdata.h
)

set(TEXTBUILDER_Sources
	${TEXTBUILDER_Headers}
	textfactory.cpp
	fontmanager.cpp
)

add_library(textbuilder ${TEXTBUILDER_Sources})
