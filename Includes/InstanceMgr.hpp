﻿//
//  LiarObject.hpp
//  OpenGL
//
//  Created by 毛伟 on 2018/6/16.
//  Copyright © 2018年 lier. All rights reserved.
//

#ifndef InstanceMgr_hpp
#define InstanceMgr_hpp

#include <map>
#include <string>
#include <memory>
using namespace std;

#include "TextureData.hpp"

namespace Liar
{
	enum LiarAssetsType
	{
		MATERIAL,
		GEOMETORY
	};

	class InstanceMgr
	{
	public:
		InstanceMgr();
		~InstanceMgr();

	private:

	};

	template<>
	class AssetsMgr<TextureData*>
	{
	public:
		template<>
		static std::shared_ptr<TextureData*><const std::string> Instance(LiarAssetsType key)
	};

	// ===================================== assets ====================================================
	template < typename T, typename K = LiarAssetsType>
	class AssetsMgr
	{
	public:
		template<typename... Args>
		static std::shared_ptr<T> Instance(K key, Args&&... args)
		{
			return GetInstance(key, std::forward<Args>(args)...);
		}
	private:
		template<typename Key, typename... Args>
		static std::shared_ptr<T> GetInstance(Key key, Args&&...args)
		{
			std::shared_ptr<T> instance = nullptr;
			auto it = m_map.find(key);
			if (it == m_map.end())
			{
				instance = std::make_shared<T>(std::forward<Args>(args)...);
				m_map.emplace(key, instance);
			}
			else
			{
				instance = it->second;
			}

			return instance;
		}

	private:
		AssetsMgr(void);
		AssetsMgr(const AssetsMgr&);
	private:
		static map<K, std::shared_ptr<T>> m_assetsMap;
	};

	// ===================================== assets ====================================================

	template < typename T, typename K = string>
	class Multiton
	{
	public:
		template<typename... Args>
		static std::shared_ptr<T> Instance(const K& key, Args&&... args)
		{
			return GetInstance(key, std::forward<Args>(args)...);
		}

		template<typename... Args>
		static std::shared_ptr<T> Instance(K&& key, Args&&... args)
		{
			return GetInstance(key, std::forward<Args>(args)...);
		}
	private:
		template<typename Key, typename... Args>
		static std::shared_ptr<T> GetInstance(Key&& key, Args&&...args)
		{
			std::shared_ptr<T> instance = nullptr;
			auto it = m_map.find(key);
			if (it == m_map.end())
			{
				instance = std::make_shared<T>(std::forward<Args>(args)...);
				m_map.emplace(key, instance);
			}
			else
			{
				instance = it->second;
			}

			return instance;
		}

	private:
		Multiton(void);
		//virtual ~Multiton(void);
		Multiton(const Multiton&);
		//Multiton& operator = (const Multiton&);
	private:
		static map<K, std::shared_ptr<T>> m_map;
	};

	/*template <typename T, typename K>
	map<K, std::shared_ptr<T>> Multiton<T, K>::m_map;*/
}

#endif /* InstanceMgr_hpp */