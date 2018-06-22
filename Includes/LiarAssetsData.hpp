
//
//  TextureData.hpp
//  OpenGL
//
//  Created by 毛伟 on 2018/6/10.
//  Copyright © 2018年 lier. All rights reserved.
//

#ifndef LiarAssetsData_hpp
#define LiarAssetsData_hpp

#include <string>
#include <iostream>
#include <stb_image.h>

namespace Liar
{
	class LiarBaseAssetsData
	{
	public:
		LiarBaseAssetsData(std::string& path);
		~LiarBaseAssetsData();

	protected:
		int m_refCount;
		std::string m_path;

	public:
		void IncRefCount() { ++m_refCount; };
		int Release() { return --m_refCount; };
		bool CheckSamePath(const std::string& val) { return val == m_path; };
	};


	// ==============   texture_data ================
	class LiarTextureData:public LiarBaseAssetsData
	{
	public:
		LiarTextureData(std::string&, int);
		~LiarTextureData();

	private:
		int m_width;
		int m_height;
		int m_nrChannels;
		int m_rgb_mod;
		unsigned char* m_data;

	public:
	public:
		int GetWidth() const { return m_width; };
		int GetHeight() const { return m_height; };
		int GetNrChannels() const { return m_nrChannels; };
		int GetRgbMod() const { return m_rgb_mod; };
		unsigned char* GetData() const { return m_data; };
	};

	// ==============   texture2d  ================
	class LiarTexture2D :public LiarBaseAssetsData
	{
	public:
		LiarTexture2D(std::string&, int, int, int);
		~LiarTexture2D();

	private:
		unsigned int m_id;

		int m_wrapMod;
		int m_levMod;

	public:
		void UpLoad();
	};
}

#endif /* LiarAssetsData_hpp */

