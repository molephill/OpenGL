#pragma once

#ifndef PLUGINS
#include <glad/glad.h>
#include <stb_image.h>
#endif // !PLUGINS

#include <iostream>
#include <fstream>

#define FOURCC_DXT1 0x31545844 // Equivalent to "DXT1" in ASCII
#define FOURCC_DXT3 0x33545844 // Equivalent to "DXT3" in ASCII
#define FOURCC_DXT5 0x35545844 // Equivalent to "DXT5" in ASCII

// For a compressed texture, the size of each mipmap level image is typically one-fourth the size of the previous, with a minimum of 8 (DXT1) or 16 (DXT2-5) bytes (for 
// square textures). Use the following formula to calculate the size of each level for a non-square texture:
#define SIZE_OF_DXT1(width, height)    ( max(1, ( (width + 3) >> 2 ) ) * max(1, ( (height + 3) >> 2 ) ) * 8 )
#define SIZE_OF_DXT2(width, height)    ( max(1, ( (width + 3) >> 2 ) ) * max(1, ( (height + 3) >> 2 ) ) * 16 )

namespace Liar
{
	class LiarTextureHelper
	{
	public:
		static GLuint Load(const char*);
		static GLuint LoadDDS(const char*);
		static GLuint LoadTGA(const char*);
	};
}

