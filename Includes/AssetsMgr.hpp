//
//  TextureDataMgr.hpp
//  OpenGL
//
//  Created by 毛伟 on 2018/6/10.
//  Copyright © 2018年 lier. All rights reserved.
//

#ifndef TextureDataMgr_hpp
#define TextureDataMgr_hpp

#include <stdio.h>

#include <string>
#include <vector>

#ifndef __APPLE__
#include <functional>
#endif // !__APPLE__

#include <LiarMesh.h>
#include <LiarMaterial.h>
#include <LiarPluginRead.h>
#include <LiarShader.h>
#include <LiarSkeleton.h>

#include <map>

namespace Liar
{
    // 资源路径
#ifdef __APPLE__
    const static std::string BASE_PATH = "/Users/maowei/Downloads/C++/OpenGL/OpenGL/Assets/";
#else
    const static std::string BASE_PATH = "E:/c++/VSOpenGL/OpenGL/Assets/";
#endif
    
    class AssetsMgr
    {
    public:
		static AssetsMgr& GetInstance() 
		{  
			//全局访问点
			static InstanceCreator creator;  //有non-local static对象依赖时确保初始化顺序。
			return *m_instance;
		}
        
	private:
		AssetsMgr();
		AssetsMgr(const AssetsMgr &);
		~AssetsMgr();

		struct InstanceCreator 
		{  
			//真正负责单例的构造和析构
			InstanceCreator() 
			{
				AssetsMgr::m_instance = new AssetsMgr;
			}

			~InstanceCreator() 
			{
				delete AssetsMgr::m_instance;
				AssetsMgr::m_instance = nullptr;
			}
		};

		struct InstanceConfirm 
		{  
			//没有non-loacl static对象依赖时，保证在main函数前初始化
			InstanceConfirm() 
			{
				AssetsMgr::GetInstance();
			}
		};

	private:
		friend struct InstanceCreator;
		friend struct InstanceConfirm;
		static AssetsMgr* m_instance;
		static InstanceConfirm m_confirm;  //最后保证main函数之前完成初始化

	public:
		Liar::LiarTexture* GetTexture(const char*);
		Liar::LiarTexture* GetTexture(const std::string&);

		Liar::LiarBaseShader* GetBaseShader(const char*);
		Liar::LiarBaseShader* GetBaseShader(const std::string&);

		Liar::LiarShaderProgram* GetShaderProgrom(const char*, const char*, const char*);
		Liar::LiarShaderProgram* GetShaderProgrom(const std::string&, const std::string&, const std::string&);

		void ReleaseShaderProgram(Liar::LiarShaderProgram*);
		void ReleaseShaderProgram(const char*);
		void ReleaseShaderProgram(const std::string&);

		Liar::LiarGeometry* GetGeometryData(const char*);
		bool ReleaseGeometryData(Liar::LiarGeometry*);

		/*Liar::LiarSkeleton* GetSkeleton(const char*);
		Liar::LiarSkeleton* GetSkeleton(const std::string&);*/
        
        static std::string GetPath(const char*);

        static void PrintMat4(const glm::mat4&);

	private:
		std::vector<Liar::LiarTexture*>* m_allTextures;
		std::vector<Liar::LiarBaseShader*>* m_allShaders;
		std::vector<Liar::LiarShaderProgram*>* m_allPrograms;
		std::vector<Liar::LiarSkeleton*>* m_allSkeletons;
		std::map<const char*, Liar::LiarGeometry*>* m_mapGeometeries;
    };

	
}

#endif /* TextureDataMgr_hpp */
