#include "fontmanager.h"

#include <stdexcept>

void FontManager::releaseTexture(int texture_id){
	glDeleteTextures(1,&font);
}

void FontManager::readFontFile(std::string path)
{
	std::string line;
	std::ifstream myfile (path);
	if (myfile.is_open())
	{
		while ( myfile.good() )
		{
			getline (myfile,line);
			std::vector<std::string> elem = split(line,' ');

			if(elem.size() == 0) continue; // ignores empty lines.

			float x = atof(elem[2].c_str()),y = atof(elem[3].c_str()),w = atof(elem[4].c_str()),h = atof(elem[5].c_str());
			float dw = atof(elem[6].c_str()), dh = atof(elem[7].c_str());

			GLfloat *uv = new float[8]; 	
			uv[0] = x; uv[1] = y;
			uv[2] = x+w; uv[3] = y;
			uv[4] = x+w; uv[5] = y+h;
			uv[6] = x; uv[7] = y+h;
			uv_map[elem[1]] = uv;
			dim_map[elem[1]] = new Vec2f(dw/15.0f,dh/18.0f);
		}
		myfile.close();
		initialized = true;
	}
	else {
		initialized = false;
		std::cout << "Unable to open file";
	}
}

void FontManager::convertBlackToAlpha(ImageContainer *image)
{
	for (unsigned int i = 0; i < image->bytes; i += 4) {
		if (
			image->pixel_data[i]   < 0x55 &&
			image->pixel_data[i+1] < 0x55 &&
			image->pixel_data[i+2] < 0x55
		) {
			image->pixel_data[i+3] = 0x00;
			continue;
		} else {
			image->pixel_data[i]   = 0xff;
			image->pixel_data[i+1] = 0xff;
			image->pixel_data[i+2] = 0xff;
			image->pixel_data[i+3] = 0xff;
		}
	}
}

void FontManager::drawOnScreenFont(std::string s ,FontData f){
	if(s == "" || s == " ") {
		glTranslatef(f.shift_x,f.shift_y,0); 
		return;
	}

	glPushMatrix();

	float sx = f.font_scale_w*dim_map[s]->x;
	float sy = f.font_scale_h*dim_map[s]->y;

	glTranslatef(f.start_x,f.start_y+(f.font_scale_h-sy),0);
	glScalef(sx,sy,1);

	glTexCoordPointer(2,GL_FLOAT,0,uv_map[s]);
	glDrawArrays(GL_QUADS,0,4);

	glPopMatrix();

	glTranslatef(f.shift_x*dim_map[s]->x ,f.shift_y,0);
}

void FontManager::preDraw(){
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glVertexPointer(3,GL_FLOAT,0,font_vertex);
	glBindTexture(GL_TEXTURE_2D,font);
}