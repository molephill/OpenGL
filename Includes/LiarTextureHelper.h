#pragma once

#include <iostream>
#include <fstream>

#include <glad/glad.h>

namespace Liar
{
    
#ifdef __APPLE__
    typedef unsigned long DWORD;
#endif
    
	// Minimum and maximum macros
#define max(a,b) (((a) > (b)) ? (a) : (b))
#define min(a,b) (((a) < (b)) ? (a) : (b))

#define DDPF_ALPHAPIXELS    0x000001
#define DDPF_ALPHA            0x000002
#define DDPF_FOURCC            0x000004
#define DDPF_RGB            0x000040
#define DDPF_YUV            0x000200
#define DDPF_LUMINANCE        0x020000

#define D3DFMT_DXT1    (('D'<<0)|('X'<<8)|('T'<<16)|('1'<<24))
#define D3DFMT_DXT3    (('D'<<0)|('X'<<8)|('T'<<16)|('3'<<24))
#define D3DFMT_DXT5    (('D'<<0)|('X'<<8)|('T'<<16)|('5'<<24))

	typedef struct
	{
		DWORD    dwSize;
		DWORD    dwFlags;
		DWORD    dwFourCC;
		DWORD    dwRGBBitCount;
		DWORD    dwRBitMask;
		DWORD    dwGBitMask;
		DWORD    dwBBitMask;
		DWORD    dwABitMask;
	} DDS_PIXELFORMAT;

#define DDSD_CAPS            0x000001
#define DDSD_HEIGHT            0x000002
#define DDSD_WIDTH            0x000004
#define DDSD_PITCH            0x000008
#define DDSD_PIXELFORMAT    0x001000
#define DDSD_MIPMAPCOUNT    0x020000
#define DDSD_LINEARSIZE        0x080000
#define DDSD_DEPTH            0x800000

	typedef struct
	{
		DWORD            dwSize;
		DWORD            dwFlags;
		DWORD            dwHeight;
		DWORD            dwWidth;
		DWORD            dwPitchOrLinearSize;
		DWORD            dwDepth;
		DWORD            dwMipMapCount;
		DWORD            dwReserved1[11];
		DDS_PIXELFORMAT    ddspf;
		DWORD            dwCaps;
		DWORD            dwCaps2;
		DWORD            dwCaps3;
		DWORD            dwCaps4;
		DWORD            dwReserved2;
	} DDS_HEADER;

	typedef struct
	{
		DWORD        dwMagic;
		DDS_HEADER    Header;
	} DDS_FILEHEADER;

	// For a compressed texture, the size of each mipmap level image is typically one-fourth the size of the previous, with a minimum of 8 (DXT1) or 16 (DXT2-5) bytes (for 
	// square textures). Use the following formula to calculate the size of each level for a non-square texture:
#define SIZE_OF_DXT1(width, height)    ( max(1, ( (width + 3) >> 2 ) ) * max(1, ( (height + 3) >> 2 ) ) * 8 )
#define SIZE_OF_DXT2(width, height)    ( max(1, ( (width + 3) >> 2 ) ) * max(1, ( (height + 3) >> 2 ) ) * 16 )


	typedef	struct
	{
		GLubyte	*imageData;
		GLuint	bpp;
		GLuint	width;
		GLuint	height;
		GLuint	texID;
		GLuint	type;
	} TGA_PIXELFORMAT;

	typedef struct
	{
		GLubyte Header[12];
	} TGA_HEADER;


	typedef struct
	{
		GLubyte		header[6];
		GLuint		bytesPerPixel;
		GLuint		imageSize;
		GLuint		temp;
		GLuint		type;
		GLuint		Height;
		GLuint		Width;
		GLuint		Bpp;
	} TGA;

	class LiarTextureHelper
	{
	public:
		static GLuint Load(const char*);
		static GLuint LoadDDS(const char*);
		static GLuint LoadTGA(const char*);

	private:
		static bool LoadUncompressedTGA(TGA_PIXELFORMAT * texture, TGA&, FILE * fTGA);
		static bool LoadCompressedTGA(TGA_PIXELFORMAT * texture, TGA&, FILE * fTGA);
	};
}

