#ifndef TERMINAL_H
#define TERMINAL_H

#include "textbuilder/text_include.h"
#include "textbuilder/textfactory.h"
#include "terminallistener.h"
#include "math/vec2.h"
#include <string>
#include <vector>

#define STACK_CAPASITY 20

class Terminal
{
protected:
	

public:
	Terminal() 
		: keystring("")
		, indexPointer(-1)
		, isOpen(false)
		, shiftIsDown(false)
	{}

	Terminal(Vec2f dim) 
		: keystring("")
		, indexPointer(-1)
		, isOpen(false)
		, shiftIsDown(false)
		, dimension(dim)
	{}

	void setDimension(Vec2f dimension){ this->dimension = dimension; }

	void open() { isOpen = true; }
	void close() { isOpen = false; }

	bool update()
	{
		if(!isOpen) return false;
		{
			SDL_Event event;

			while (SDL_PollEvent(&event)) {
				onKeyEvent(event);
			}
		}

		return true;
	}

	void draw()
	{
		if(!isOpen) return;

		glPushMatrix();
		glPushAttrib(GL_ENABLE_BIT | GL_COLOR_BUFFER_BIT);

		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glLoadIdentity();

		glOrtho(
			0, dimension.x,
			dimension.y, 0,
			-1.0f, 1.0f);

		glMatrixMode(GL_MODELVIEW);

		glColor4f(0.1f,0.1f,0.1f,0.3f);
		glDisable(GL_TEXTURE_2D);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

		glBegin(GL_QUADS);
			glVertex2f(0,0);
			glVertex2f(dimension.x,0);
			glVertex2f(dimension.x,dimension.y);
			glVertex2f(0,dimension.y);
		glEnd();

		glPopMatrix();

		float starty = 5;
		for(int i = 0; i < string_stack.size(); ++i)
		{
			TextFactory::instance()->drawText(string_stack[i],5,starty);
			starty += 20;
		}

		TextFactory::instance()->drawText("/> " + keystring,5,starty);
		glPopAttrib();

		glMatrixMode(GL_PROJECTION);
		glPopMatrix();
		glMatrixMode(GL_MODELVIEW);
	}

	void commit(std::string line)
	{
		if(line == "") return;
		
		string_stack.push_back(line);
		key_stack.push_back(line);
		indexPointer = key_stack.size();

		if(listener != 0) {
			std::string s = listener->onCommit(keystring);
			if(s != "") string_stack.push_back(s);
		}

		while(string_stack.size() >= STACK_CAPASITY) {
			string_stack.erase(string_stack.begin());
		}
		keystring = "";
	}

	/**
	 * Moves the index pointer forward.
	 *
	 * return true if successful. else false.
	 */
	bool next()
	{
		if(key_stack.size() == 0) return false;
		
		if(indexPointer+1 >= key_stack.size()) { indexPointer = key_stack.size()-1; }
		else indexPointer++;

		keystring = key_stack[indexPointer];
		return true;
	}

	/**
	 * Moves the index pointer backward.
	 *
	 * return true if successful. else false.
	 */
	bool previous()
	{
		if(key_stack.size() == 0) return false;

		if(indexPointer-1 < 0) { indexPointer = 0; }
		else indexPointer--; 
		
		keystring = key_stack[indexPointer];
		return true;
	}

	void setListener(TerminalListener* listener) { this->listener = listener; }

private:
	Vec2f dimension;
	bool isOpen;
	std::string keystring;
	std::vector<std::string> string_stack;
	std::vector<std::string> key_stack;

	int indexPointer;
	bool shiftIsDown;

	TerminalListener* listener;

	void onKeyEvent(const SDL_Event &event) 
	{

		switch (event.type) {

		case SDL_KEYUP:
			switch (event.key.keysym.sym) {

			case SDLK_LSHIFT:
			case SDLK_RSHIFT: shiftIsDown = false; break;

			default:
				break;
			};
			break;

		case SDL_KEYDOWN:
			printf("%d \n",event.key.keysym.sym);
			switch (event.key.keysym.sym) {

			case SDLK_1: keystring.append((shiftIsDown)?"!":"1"); break;
			case SDLK_2: keystring.append((shiftIsDown)?"\"":"2"); break;
			case SDLK_3: keystring.append((shiftIsDown)?"#":"3"); break;
			case SDLK_4: keystring.append(/*(shiftIsDown)?"¤":*/"4"); break;
			case SDLK_5: keystring.append((shiftIsDown)?"%":"5"); break;
			case SDLK_6: keystring.append((shiftIsDown)?"&":"6"); break;
			case SDLK_7: keystring.append((shiftIsDown)?"/":"7"); break;
			case SDLK_8: keystring.append((shiftIsDown)?"(":"8"); break;
			case SDLK_9: keystring.append((shiftIsDown)?")":"9"); break;
			case SDLK_0: keystring.append((shiftIsDown)?"=":"0"); break;
			case SDLK_PLUS: keystring.append((shiftIsDown)?"?":"+"); break;

			case SDLK_q: keystring.append("q"); break;
			case SDLK_w: keystring.append("w"); break;
			case SDLK_e: keystring.append("e"); break;
			case SDLK_r: keystring.append("r"); break;
			case SDLK_t: keystring.append("t"); break;
			case SDLK_y: keystring.append("y"); break;
			case SDLK_u: keystring.append("u"); break;
			case SDLK_i: keystring.append("i"); break;
			case SDLK_o: keystring.append("o"); break;
			case SDLK_p: keystring.append("p"); break;

			case SDLK_a: keystring.append("a"); break;
			case SDLK_s: keystring.append("s"); break;
			case SDLK_d: keystring.append("d"); break;
			case SDLK_f: keystring.append("f"); break;
			case SDLK_g: keystring.append("g"); break;
			case SDLK_h: keystring.append("h"); break;
			case SDLK_j: keystring.append("j"); break;
			case SDLK_k: keystring.append("k"); break;
			case SDLK_l: keystring.append("l"); break;

			case SDLK_z: keystring.append("z"); break;
			case SDLK_x: keystring.append("x"); break;
			case SDLK_c: keystring.append("c"); break;
			case SDLK_v: keystring.append("v"); break;
			case SDLK_b: keystring.append("b"); break;
			case SDLK_n: keystring.append("n"); break;
			case SDLK_m: keystring.append("m"); break;

			case SDLK_LESS: keystring.append((shiftIsDown)?">":"<"); break;
			case SDLK_QUESTION: keystring.append("?"); break;
			case SDLK_PERIOD: keystring.append((shiftIsDown)?":":"."); break;
			case SDLK_COMMA: keystring.append((shiftIsDown)?";":","); break;

			case SDLK_KP_PLUS: keystring.append("+"); break;	
			case SDLK_KP_MINUS: keystring.append("-"); break;	

			case SDLK_SPACE: keystring.append(" "); break;
			case SDLK_LSHIFT:
			case SDLK_RSHIFT: shiftIsDown = true; break;

			case SDLK_BACKSPACE: if(keystring.size() > 0) keystring.erase(keystring.size()-1,1); break;
			case SDLK_HOME:
			case SDLK_BACKQUOTE:
			case SDLK_ESCAPE: close(); break;

			case SDLK_KP_ENTER:
			case SDLK_RETURN: commit(keystring); break;

			case SDLK_UP: previous(); break;
			case SDLK_DOWN: next(); break;

			default:
				break;
			};
			break;
		};
		std::cout << keystring << std::endl;
	}
};

#endif // TERMINAL_H
