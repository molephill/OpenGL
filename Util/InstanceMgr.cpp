#include "InstanceMgr.hpp"

namespace Liar
{

	InstanceMgr::InstanceMgr()
	{
	}


	InstanceMgr::~InstanceMgr()
	{
	}

	template <typename T, typename K>
	map<K, std::shared_ptr<T>> AssetsMgr<T, K>::m_assetsMap;
}
