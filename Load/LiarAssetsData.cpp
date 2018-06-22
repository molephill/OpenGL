#include "LiarAssetsData.hpp"

namespace Liar
{
	LiarBaseAssetsData::LiarBaseAssetsData()
		:m_refCount(1)
	{
	}


	LiarBaseAssetsData::~LiarBaseAssetsData()
	{
	}

	// ======================= texture_data =======================
	LiarTextureData::LiarTextureData(std::string& path, int type) :m_path(path), m_rgb_mod(type)
	{
		m_data = stbi_load(m_path.c_str(), &m_width, &m_height, &m_nrChannels, 0);
	}

	LiarTextureData::~LiarTextureData()
	{
		stbi_image_free(m_data);
	}
}
