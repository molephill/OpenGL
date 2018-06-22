
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

namespace Liar
{
	class LiarBaseAssetsData
	{
	public:
		LiarBaseAssetsData();
		~LiarBaseAssetsData();

	protected:
		int m_refCount;
		std::string m_path;

	public:
		void IncRefCount() { ++m_refCount; };
		int Release() { return --m_refCount; };
		bool CheckSamePath(const std::string& val) { return val == m_path; };
	};
}

#endif /* LiarAssetsData_hpp */

