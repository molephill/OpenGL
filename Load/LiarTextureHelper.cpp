#include "LiarTextureHelper.h"


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


	GLuint LiarTextureHelper::LoadDDS(const char * filename)
	{
		/* try to open the file */
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
			std::cout << "Error::loadDDs, format is not dds :" << filename << std::endl;
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
		unsigned int format = 0;
		switch (fourCC)
		{
		case FOURCC_DXT1:
			//format = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
			format = GL_RGB;
			break;
		case FOURCC_DXT3:
			//format = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
			format = GL_RGBA;
			break;
		case FOURCC_DXT5:
			//format = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
			format = GL_RGBA;
			break;
		default:
			delete[] buffer;
			return 0;
		}

		// Create one OpenGL texture
		GLuint textureID = 0;
		glGenTextures(1, &textureID);

		// "Bind" the newly created texture : all future texture functions will modify this texture
		glBindTexture(GL_TEXTURE_2D, textureID);
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

		//unsigned int blockSize = (format == GL_COMPRESSED_RGBA_S3TC_DXT1_EXT) ? 8 : 16;
		unsigned int blockSize = (format == GL_RGB) ? 8 : 16;
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
	
	GLuint LiarTextureHelper::LoadTGA(const char* fileName)
	{
		GLubyte		TGAheader[12] = { 0,0,2,0,0,0,0,0,0,0,0,0 };	// Uncompressed TGA Header
		GLubyte		TGAcompare[12];								// Used To Compare TGA Header
		GLubyte		header[6];									// First 6 Useful Bytes From The Header
		GLuint		bytesPerPixel;								// Holds Number Of Bytes Per Pixel Used In The TGA File
		GLuint		imageSize;									// Used To Store The Image Size When Setting Aside Ram
		GLuint		temp;										// Temporary Variable
		GLuint		type = GL_RGBA;								// Set The Default GL Mode To RBGA (32 BPP)

		FILE* file;												// Open The TGA File
#ifndef __APPLE__	
		fopen_s(&file, fileName, "rb+");
#else
		file = fopen(fileName, "rb+");
#endif			

		if (file == NULL ||										// Does File Even Exist?
			fread(TGAcompare, 1, sizeof(TGAcompare), file) != sizeof(TGAcompare) ||	// Are There 12 Bytes To Read?
			memcmp(TGAheader, TGAcompare, sizeof(TGAheader)) != 0 ||	// Does The Header Match What We Want?
			fread(header, 1, sizeof(header), file) != sizeof(header))				// If So Read Next 6 Header Bytes
		{
			if (file == NULL)								// Did The File Even Exist? *Added Jim Strong*
			{
				return 0;									// Return False
			}
			else
			{
				fclose(file);									// If Anything Failed, Close The File
				return 0;									// Return False
			}
		}

		GLuint width = header[1] * 256 + header[0];			// Determine The TGA Width	(highbyte*256+lowbyte)
		GLuint height = header[3] * 256 + header[2];			// Determine The TGA Height	(highbyte*256+lowbyte)

																//OpenGL中纹理只能使用24位或者32位的TGA图像
		if (width <= 0 ||								// Is The Width Less Than Or Equal To Zero
			height <= 0 ||								// Is The Height Less Than Or Equal To Zero
			(header[4] != 24 && header[4] != 32))					// Is The TGA 24 or 32 Bit?
		{
			fclose(file);										// If Anything Failed, Close The File
			return false;										// Return False
		}

		GLuint bpp = header[4];							// Grab The TGA's Bits Per Pixel (24 or 32)
		bytesPerPixel = bpp / 8;						// Divide By 8 To Get The Bytes Per Pixel
		imageSize =width*height*bytesPerPixel;	// Calculate The Memory Required For The TGA Data

		GLubyte* imageData = (GLubyte *)malloc(imageSize);		// Reserve Memory To Hold The TGA Data

		if (imageData == NULL ||							// Does The Storage Memory Exist?
			fread(imageData, 1, imageSize, file) != imageSize)	// Does The Image Size Match The Memory Reserved?
		{
			if (imageData != NULL)						// Was Image Data Loaded
				free(imageData);						// If So, Release The Image Data

			fclose(file);										// Close The File
			return 0;										// Return False
		}

		//RGB数据格式转换，便于在OpenGL中使用
		for (GLuint i = 0; i<int(imageSize); i += bytesPerPixel)		// Loop Through The Image Data
		{														// Swaps The 1st And 3rd Bytes ('R'ed and 'B'lue)
			temp = imageData[i];							// Temporarily Store The Value At Image Data 'i'
			imageData[i] = imageData[i + 2];	// Set The 1st Byte To The Value Of The 3rd Byte
			imageData[i + 2] = temp;					// Set The 3rd Byte To The Value In 'temp' (1st Byte Value)
		}

		fclose(file);											// Close The File

		GLuint textureID = 0;
														// Build A Texture From The Data
		glGenTextures(1, &textureID);					// Generate OpenGL texture IDs

		glBindTexture(GL_TEXTURE_2D, textureID);			// Bind Our Texture

		if (bpp == 24)									// Was The TGA 24 Bits
		{
			type = GL_RGB;										// If So Set The 'type' To GL_RGB
		}

		glTexImage2D(GL_TEXTURE_2D, 0, type, width, height, 0, type, GL_UNSIGNED_BYTE, imageData);
		free(imageData);

		return textureID;
	}
}
