#include "textfactory.h"

TextFactory* TextFactory::m_instance = 0;
const int TextFactory::TERMINAL_FONT_1 = 0;

TextFactory::TextFactory(int fontkey) 
{
	m_fontbuilder = new FontManager();
	if(fontkey == TERMINAL_FONT_1){
		m_fontbuilder->readFontFile("res/font/terminal_font1.txt");
		m_fontdata.font_scale_w = 12;
		m_fontdata.font_scale_h = 15;
		m_fontdata.shift_x = 12;
	}
}

void TextFactory::drawText(std::string text, float x, float y)
{
	glPushMatrix();
	glTranslatef(x,y,0);
	glPushAttrib(GL_ENABLE_BIT | GL_COLOR_BUFFER_BIT | GL_TEXTURE_BIT);
	glPushClientAttrib(GL_CLIENT_ALL_ATTRIB_BITS);

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	glColor4f(m_fontdata.R,m_fontdata.G,m_fontdata.B,m_fontdata.A);

	m_fontbuilder->preDraw();
	const char* strdata = text.c_str();

	for (int i = 0; i < text.length(); ++i){
		std::stringstream ss;
		std::string s;
		ss << strdata[i];
		ss >> s;
		m_fontbuilder->drawOnScreenFont(s,m_fontdata);
	}

	glPopClientAttrib();
	glPopAttrib();
	glPopMatrix();
}