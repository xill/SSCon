#include "fontmanager.h"

#include <stdexcept>

void FontManager::releaseTexture(int texture_id){
	glDeleteTextures(1,&font);
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
	float extra_y = 0;

	// letters and characters which need to start from a lower point.
	if(s == "q" 
		|| s == "y"
		|| s == "p"
		|| s == "j"
		|| s == "g"
		|| s == "+"
		|| s == "-"
	) {
		extra_y = sy*0.25f;
	}

	glTranslatef(f.start_x,f.start_y+(f.font_scale_h-sy)+extra_y,0);
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