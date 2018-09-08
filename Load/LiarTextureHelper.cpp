#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>

#include "LiarTextureHelper.h"

//#define SIMPLEDDS 1 

namespace Liar
{
	GLuint LiarTextureHelper::Load(const char* filename)
	{
		int width = 0, height = 0, nrComponents = 0;
		GLuint textureID = 0;
		unsigned char *data = stbi_load(filename, &width, &height, &nrComponents, 0);
		if (data)
		{
			GLenum format = GL_RGB;
			if (nrComponents == 1)
            {
				format = GL_RED;
            }
			else if (nrComponents == 3)
            {
				format = GL_RGB;
            }
			else if (nrComponents == 4)
            {
				format = GL_RGBA;
            }

			glGenTextures(1, &textureID);
			glBindTexture(GL_TEXTURE_2D, textureID);
			glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);

			stbi_image_free(data);

			return textureID;
		}
		else
		{
			return 0;
		}
	}

#ifdef SIMPLEDDS

#define FOURCC_DXT1 0x31545844 // Equivalent to "DXT1" in ASCII
#define FOURCC_DXT3 0x33545844 // Equivalent to "DXT3" in ASCII
#define FOURCC_DXT5 0x35545844 // Equivalent to "DXT5" in ASCII

	GLuint LiarTextureHelper::LoadDDS(const char * filename)
	{
		std::ifstream file(filename, std::ios::in | std::ios::binary);
		if (!file) {
			std::cout << "Error::loadDDs, could not open:"
				<< filename << "for read." << std::endl;
			return 0;
		}

		/* verify the type of file */
		char filecode[4];
		file.read(filecode, 4);
		if (strncmp(filecode, "DDS ", 4) != 0) {
			std::cout << "Error::loadDDs, format is not dds :"
				<< filename << std::endl;
			file.close();
			return 0;
		}

		/* get the surface desc */
		char header[124];
		file.read(header, 124);

		unsigned int height = *(unsigned int*)&(header[8]);
		unsigned int width = *(unsigned int*)&(header[12]);
		unsigned int linearSize = *(unsigned int*)&(header[16]);
		unsigned int mipMapCount = *(unsigned int*)&(header[24]);
		unsigned int fourCC = *(unsigned int*)&(header[80]);


		char * buffer = NULL;
		unsigned int bufsize;
		/* how big is it going to be including all mipmaps? */
		bufsize = mipMapCount > 1 ? linearSize * 2 : linearSize;
		buffer = new char[bufsize];
		file.read(buffer, bufsize);
		/* close the file pointer */
		file.close();

		unsigned int components = (fourCC == FOURCC_DXT1) ? 3 : 4;
		unsigned int format;
		switch (fourCC)
		{
		case FOURCC_DXT1:
			format = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
			break;
		case FOURCC_DXT3:
			format = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
			break;
		case FOURCC_DXT5:
			format = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
			break;
		default:
			delete[] buffer;
			return 0;
		}

		// Create one OpenGL texture
		GLuint textureID;
		glGenTextures(1, &textureID);

		// "Bind" the newly created texture : all future texture functions will modify this texture
		glBindTexture(GL_TEXTURE_2D, textureID);
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

		unsigned int blockSize = (format == GL_COMPRESSED_RGBA_S3TC_DXT1_EXT) ? 8 : 16;
		unsigned int offset = 0;

		/* load the mipmaps */
		for (unsigned int level = 0; level < mipMapCount && (width || height); ++level)
		{
			unsigned int size = ((width + 3) / 4)*((height + 3) / 4)*blockSize;
			glCompressedTexImage2D(GL_TEXTURE_2D, level, format, width, height,
				0, size, buffer + offset);

			offset += size;
			width /= 2;
			height /= 2;

			// Deal with Non-Power-Of-Two textures. This code is not included in the webpage to reduce clutter.
			if (width < 1) width = 1;
			if (height < 1) height = 1;

		}

		delete[] buffer;

		return textureID;
	}
#else

GLuint LiarTextureHelper::LoadDDS(const char * filename)
{
	FILE    *fp;
	int     size;
	void    *pBuffer;

#ifndef __APPLE__	
	fopen_s(&fp, filename, "rb");
#else
	fp = fopen(filename, "rb");
#endif	
	if (!fp) {
		return 0;
	}

	fseek(fp, 0, SEEK_END);
	size = ftell(fp);
	fseek(fp, 0, SEEK_SET);

	pBuffer = malloc(size);
	if (!pBuffer) {
		fclose(fp);
		return 0;
	}

	if (fread(pBuffer, size, 1, fp) != 1) {
		free(pBuffer);
		fclose(fp);
		return 0;
	}

	fclose(fp);

	DDS_FILEHEADER    *header;
	DWORD             compressFormat;
	GLuint            texnum;
	GLvoid            *data;
	GLsizei           imageSize;

	header = (DDS_FILEHEADER *)pBuffer;

	if (header->dwMagic != 0x20534444) {
		printf("bad dds file\n");
		return 0;
	}

	if (header->Header.dwSize != 124) {
		printf("bad header size\n");
		return 0;
	}

	if (!(header->Header.dwFlags & DDSD_LINEARSIZE)) {
		printf("bad file type\n");
		return 0;
	}

	if (!(header->Header.ddspf.dwFlags & DDPF_FOURCC)) {
		printf("bad pixel format\n");
		return 0;
	}

	compressFormat = header->Header.ddspf.dwFourCC;

	if (compressFormat != D3DFMT_DXT1 &&
		compressFormat != D3DFMT_DXT3 &&
		compressFormat != D3DFMT_DXT5) {
		printf("bad compress format\n");
		return 0;
	}

	data = (GLvoid *)(header + 1);    // header data skipped

	glGenTextures(1, &texnum);
	glBindTexture(GL_TEXTURE_2D, texnum);

	switch (compressFormat)
	{
	case D3DFMT_DXT1:
		imageSize = SIZE_OF_DXT1(header->Header.dwWidth, header->Header.dwHeight);
		glCompressedTexImage2DARB(GL_TEXTURE_2D, 0, GL_COMPRESSED_RGB_S3TC_DXT1_EXT, header->Header.dwWidth, header->Header.dwHeight, 0, imageSize, data);
		break;
	case D3DFMT_DXT3:
		imageSize = SIZE_OF_DXT2(header->Header.dwWidth, header->Header.dwHeight);
		glCompressedTexImage2DARB(GL_TEXTURE_2D, 0, GL_COMPRESSED_RGBA_S3TC_DXT3_EXT, header->Header.dwWidth, header->Header.dwHeight, 0, imageSize, data);
		break;
	case D3DFMT_DXT5:
		imageSize = SIZE_OF_DXT2(header->Header.dwWidth, header->Header.dwHeight);
		glCompressedTexImage2DARB(GL_TEXTURE_2D, 0, GL_COMPRESSED_RGBA_S3TC_DXT5_EXT, header->Header.dwWidth, header->Header.dwHeight, 0, imageSize, data);
		break;
	}
	glGenerateMipmap(GL_TEXTURE_2D);

	free(pBuffer);
	return texnum;
}

#endif // SIMPLEDDS

	GLuint LiarTextureHelper::LoadTGA(const char* filename)
	{
		FILE * fTGA;

#ifndef __APPLE__	
		fopen_s(&fTGA, filename, "rb+");
#else
		fTGA = fopen(filename, "rb+");
#endif	

		if (fTGA == NULL)
		{
			return 0;
		}


		TGA_HEADER tgaheader;

		GLubyte uTGAcompare[12] = { 0,0,2, 0,0,0,0,0,0,0,0,0 };
		GLubyte cTGAcompare[12] = { 0,0,10,0,0,0,0,0,0,0,0,0 };

		if (fread(&tgaheader, sizeof(TGA_HEADER), 1, fTGA) == 0)
		{
			if (fTGA != NULL)
			{
				fclose(fTGA);
			}
			return 0;
		}

		TGA tga;
		TGA_PIXELFORMAT* texture = new TGA_PIXELFORMAT();
		
		GLuint textureID = 0;

		if (memcmp(uTGAcompare, &tgaheader, sizeof(tgaheader)) == 0)
		{
			if (LoadUncompressedTGA(texture, tga, fTGA))
			{
				glGenTextures(1, &textureID);
				glTexImage2D(GL_TEXTURE_2D, 0, texture->bpp / 8, texture->width, texture->height, 0, texture->type, GL_UNSIGNED_BYTE, texture->imageData);
				glGenerateMipmap(GL_TEXTURE_2D);
			}
			delete texture;
			return textureID;
		}
		else if (memcmp(cTGAcompare, &tgaheader, sizeof(tgaheader)) == 0)
		{
			if (LoadCompressedTGA(texture, tga, fTGA))
			{
				glGenTextures(1, &textureID);
				glTexImage2D(GL_TEXTURE_2D, 0, texture->bpp / 8, texture->width, texture->height, 0, texture->type, GL_UNSIGNED_BYTE, texture->imageData);
				glGenerateMipmap(GL_TEXTURE_2D);
			}
			if(texture->imageData) free(texture->imageData);
			delete texture;
			return textureID;
		}
		else
		{
			fclose(fTGA);
			if (texture->imageData) free(texture->imageData);
			delete texture;
			return 0;
		}
	}

	bool LiarTextureHelper::LoadUncompressedTGA(TGA_PIXELFORMAT* texture, TGA& tga, FILE * fTGA)
	{
		if (fread(tga.header, sizeof(tga.header), 1, fTGA) == 0)
		{
			if (fTGA != NULL)
			{
				fclose(fTGA);
			}
			return false;
		}

		texture->width = tga.header[1] * 256 + tga.header[0];
		texture->height = tga.header[3] * 256 + tga.header[2];
		texture->bpp = tga.header[4];
		tga.Width = texture->width;
		tga.Height = texture->height;
		tga.Bpp = texture->bpp;

		if ((texture->width <= 0) || (texture->height <= 0) || ((texture->bpp != 24) && (texture->bpp != 32)))
		{
			if (fTGA != NULL)
			{
				fclose(fTGA);
			}
			return false;
		}

		if (texture->bpp == 24)
			texture->type = GL_RGB;
		else
			texture->type = GL_RGBA;

		tga.bytesPerPixel = (tga.Bpp / 8);
		tga.imageSize = (tga.bytesPerPixel * tga.Width * tga.Height);
		texture->imageData = (GLubyte *)malloc(tga.imageSize);

		if (texture->imageData == NULL)
		{
			fclose(fTGA);
			return false;
		}

		if (fread(texture->imageData, 1, tga.imageSize, fTGA) != tga.imageSize)
		{
			if (texture->imageData != NULL)
			{
				free(texture->imageData);
			}
			fclose(fTGA);
			return false;
		}

		// Byte Swapping Optimized By Steve Thomas
		for (GLuint cswap = 0; cswap < (int)tga.imageSize; cswap += tga.bytesPerPixel)
		{
			texture->imageData[cswap] ^= texture->imageData[cswap + 2] ^=
				texture->imageData[cswap] ^= texture->imageData[cswap + 2];
		}

		fclose(fTGA);
		return true;
	}

	bool LiarTextureHelper::LoadCompressedTGA(TGA_PIXELFORMAT* texture, TGA& tga, FILE * fTGA)
	{
		if (fread(tga.header, sizeof(tga.header), 1, fTGA) == 0)
		{
			if (fTGA != NULL)
			{
				fclose(fTGA);
			}
			return false;
		}

		texture->width = tga.header[1] * 256 + tga.header[0];
		texture->height = tga.header[3] * 256 + tga.header[2];
		texture->bpp = tga.header[4];
		tga.Width = texture->width;
		tga.Height = texture->height;
		tga.Bpp = texture->bpp;

		if ((texture->width <= 0) || (texture->height <= 0) || ((texture->bpp != 24) && (texture->bpp != 32)))
		{
			if (fTGA != NULL)
			{
				fclose(fTGA);
			}
			return false;
		}

		if (texture->bpp == 24)
			texture->type = GL_RGB;
		else
			texture->type = GL_RGBA;

		tga.bytesPerPixel = (tga.Bpp / 8);
		tga.imageSize = (tga.bytesPerPixel * tga.Width * tga.Height);
		texture->imageData = (GLubyte *)malloc(tga.imageSize);

		if (texture->imageData == NULL)
		{
			fclose(fTGA);
			return false;
		}

		GLuint pixelcount = tga.Height * tga.Width;
		GLuint currentpixel = 0;
		GLuint currentbyte = 0;
		GLubyte * colorbuffer = (GLubyte *)malloc(tga.bytesPerPixel);

		do
		{
			GLubyte chunkheader = 0;

			if (fread(&chunkheader, sizeof(GLubyte), 1, fTGA) == 0)
			{
				if (fTGA != NULL)
				{
					fclose(fTGA);
				}
				if (texture->imageData != NULL)
				{
					free(texture->imageData);
				}
				return false;
			}

			if (chunkheader < 128)
			{
				chunkheader++;
				for (short counter = 0; counter < chunkheader; counter++)
				{
					if (fread(colorbuffer, 1, tga.bytesPerPixel, fTGA) != tga.bytesPerPixel)
					{
						if (fTGA != NULL)
						{
							fclose(fTGA);
						}

						if (colorbuffer != NULL)
						{
							free(colorbuffer);
						}

						if (texture->imageData != NULL)
						{
							free(texture->imageData);
						}

						return false;
					}

					texture->imageData[currentbyte] = colorbuffer[2];
					texture->imageData[currentbyte + 1] = colorbuffer[1];
					texture->imageData[currentbyte + 2] = colorbuffer[0];

					if (tga.bytesPerPixel == 4)
					{
						texture->imageData[currentbyte + 3] = colorbuffer[3];
					}

					currentbyte += tga.bytesPerPixel;
					currentpixel++;

					if (currentpixel > pixelcount)
					{
						if (fTGA != NULL)
						{
							fclose(fTGA);
						}

						if (colorbuffer != NULL)
						{
							free(colorbuffer);
						}

						if (texture->imageData != NULL)
						{
							free(texture->imageData);
						}

						return false;
					}
				}
			}
			else
			{
				chunkheader -= 127;
				if (fread(colorbuffer, 1, tga.bytesPerPixel, fTGA) != tga.bytesPerPixel)
				{
					if (fTGA != NULL)
					{
						fclose(fTGA);
					}

					if (colorbuffer != NULL)
					{
						free(colorbuffer);
					}

					if (texture->imageData != NULL)
					{
						free(texture->imageData);
					}

					return false;
				}

				for (short counter = 0; counter < chunkheader; counter++)
				{
					texture->imageData[currentbyte] = colorbuffer[2];
					texture->imageData[currentbyte + 1] = colorbuffer[1];
					texture->imageData[currentbyte + 2] = colorbuffer[0];

					if (tga.bytesPerPixel == 4)
					{
						texture->imageData[currentbyte + 3] = colorbuffer[3];
					}

					currentbyte += tga.bytesPerPixel;
					currentpixel++;
					if (currentpixel > pixelcount)
					{
						if (fTGA != NULL)
						{
							fclose(fTGA);
						}

						if (colorbuffer != NULL)
						{
							free(colorbuffer);
						}

						if (texture->imageData != NULL)
						{
							free(texture->imageData);
						}

						return false;
					}
				}
			}
		} while (currentpixel < pixelcount);
		fclose(fTGA);
		return true;
	}

}
