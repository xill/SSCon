#ifndef FONTMANAGER_H
#define FONTMANAGER_H

#ifdef _WIN32
#	include <unordered_map>
#else
#	include <tr1/unordered_map>
#endif
#include <fstream>
#include <string>
#include <sstream>
#include <utility>
#include <vector>
#include "text_include.h"
#include "fontdata.h"
#include "fontmaps.h"

#define TERMINAL_FONT1	terminal_font1
#include				"terminal_font1.h"

struct ImageContainer {
	unsigned int width;
	unsigned int height;
	unsigned int bytes_per_pixel;
	unsigned int bytes;
	unsigned char *pixel_data;

	ImageContainer(unsigned int width, unsigned int height, unsigned int bytes_per_pixel, unsigned char *pixel_data)
	: width(width), height(height), bytes_per_pixel(bytes_per_pixel), pixel_data(pixel_data) , bytes(width*height*bytes_per_pixel)
	{}

	ImageContainer() : pixel_data(0) {}
	~ImageContainer() { delete pixel_data; }
};

class FontManager {

public:

	FontManager() 
		: font(0)
		, w_scale(12)
		, h_scale(16)
		, debug(false)
	{
		FontMap::getTerminalFont1_UV(uv_map);
		FontMap::getTerminalFont1_DIM(dim_map);
		printf("size of uv map was %zu \n",uv_map.size());
		printf("size of dim map was %zu \n",dim_map.size());

		font_image = new ImageContainer(TERMINAL_FONT1.width, TERMINAL_FONT1.height, TERMINAL_FONT1.bytes_per_pixel, &TERMINAL_FONT1.pixel_data[0]);
		convertBlackToAlpha(font_image);
		
		glGenTextures(1, &font);

		// Create Linear Filtered Texture
		glBindTexture(GL_TEXTURE_2D, font);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			
		glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);

		glTexImage2D(
			GL_TEXTURE_2D, 0, GL_RGBA, font_image->width, font_image->height, 0,
			GL_RGBA, GL_UNSIGNED_BYTE, font_image->pixel_data
		);
		/*
		if(font == 0){
			throw std::runtime_error("texture loading failed");
		}
		*/

		font_vertex = new GLfloat[12];

		font_vertex[0] = 0; font_vertex[1] = 0; font_vertex[2] = 0;
		font_vertex[3] = 1; font_vertex[4] = 0; font_vertex[5] = 0;
		font_vertex[6] = 1; font_vertex[7] = 1; font_vertex[8] = 0;
		font_vertex[9] = 0; font_vertex[10] = 1; font_vertex[11] = 0;
	}

	void releaseTexture(int texture_id);

	float w_scale,h_scale;

	std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) {
		std::stringstream ss(s);
		std::string item;
		while(std::getline(ss, item, delim)) {
			elems.push_back(item);
		}
		return elems;
	}


	std::vector<std::string> split(const std::string &s, char delim) {
		std::vector<std::string> elems;
		return split(s, delim, elems);
	}

	void readFontFile(std::string);

	void drawOnScreenFont(std::string,FontData);

	/**
	 * Call before starting to draw fonts on screen.
	 */
	void preDraw();

	void convertBlackToAlpha(ImageContainer *image);

private:
	bool debug;

	GLuint font;
	GLfloat* font_vertex;
	ImageContainer* font_image;
	std::tr1::unordered_map<std::string,GLfloat*> uv_map;
	std::tr1::unordered_map<std::string,std::pair<float,float>*> dim_map;
};

#endif
