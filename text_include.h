#ifndef GRAPHICS_INCLUDE_H
#define GRAPHICS_INCLUDE_H

#ifdef _WIN32
#	define NOMINMAX
#	include <windows.h>
#endif

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_opengl.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include <iostream>

#ifndef GL_TABLE_TOO_LARGE
#ifdef GL_TABLE_TOO_LARGE_EXT
#define GL_TABLE_TOO_LARGE GL_TABLE_TOO_LARGE_EXT
#else
#define GL_TABLE_TOO_LARGE 0x8031
#endif
#endif

#endif // GRAPHICS_INCLUDE_H
