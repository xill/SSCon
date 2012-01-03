#ifndef FONTDATA_H
#define FONTDATA_H

/**
 * Font data wrapper.
 *
 * Used by the fontmanager class to determine exactly how a font should be built.
 */
class FontData {

public:

	float font_scale_w,font_scale_h;
	float start_x,start_y;
	float shift_x,shift_y;
	float R,G,B,A;

	FontData() :
	font_scale_w(1)
	, font_scale_h(1)
	, start_x(0)
	, start_y(0)
	, shift_x(10)
	, shift_y(0)
	, R(1)
	, G(1)
	, B(1)
	, A(1)
	{}
};

#endif