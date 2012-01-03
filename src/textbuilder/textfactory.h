#ifndef TEXTFACTORY_H
#define TEXTFACTORY_H

#ifdef _WIN32
#	include <unordered_map>
#else
#	include <tr1/unordered_map>
#endif

#include "textbuilder/text_include.h"
#include "textbuilder/fontmanager.h"

class TextFactory
{
public:
	static TextFactory* instance(){
		if(m_instance == 0){
			m_instance = new TextFactory();
		}
		return m_instance;
	}

	~TextFactory(){
		delete m_fontbuilder;
	}

	const static int TERMINAL_FONT_1;

	void drawText(std::string text, float x = 0, float y = 0);

protected:

private:
	TextFactory(int fontkey = 0);

	static TextFactory* m_instance;
	FontManager* m_fontbuilder;
	FontData m_fontdata;
};

#endif // TEXTFACTORY_H
