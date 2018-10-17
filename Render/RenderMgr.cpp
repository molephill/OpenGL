//
//  RenderMgr.cpp
//  OpenGL
//
//  Created by 毛伟 on 2018/5/20.
//  Copyright © 2018年 lier. All rights reserved.
//

#include "RenderMgr.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <LiarPluginRead.h>
#include <AssetsMgr.hpp>
#include "Global.hpp"

#include <stb_image.h>
#include <gtc/matrix_transform.hpp>

#include <LiarPolygon.h>
#include <LiarModel.h>
#include <LiarRectSprite.h>

namespace Liar
{
	RenderMgr::RenderMgr():
		Liar::ILiarRenderParameter(),
        m_red(0.2f),m_green(0.3f),m_blue(0.3f),
        m_rootNode(new Liar::LiarContainerObject())
		,m_lightsMgr(new Liar::LightsMgr())
	{
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		/*glCullFace(GL_BACK);
		glEnable(GL_CULL_FACE);*/
		glEnable(GL_DEPTH_TEST);
        
#ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

		m_camera = new Liar::Camera3D();
		m_camera->SetPosition(0.0f, 0.0f, 50.0f);
		m_camera->SetName("mainCamera");
		m_rootNode->SetName("root");
        
        //m_rootNode->SetRotationX(-45.0f);
        
        // dog
//        Liar::Entity* anim = m_rootNode->AddModel(AssetsMgr::GetPath("models/anim/anim.model"), AssetsMgr::GetPath("models/anim/bird.skeleton").c_str());
//        //anim->SetPosition(0, -200.0f, -300);
//        anim->SetName("anim");
        
        //Liar::LiarDisplayObject* nano = m_rootNode->AddModel(AssetsMgr::GetPath("models/nano/nano.model"));
        ////nano->SetY(-20.0f);
        //nano->SetName("nano");

		/*Liar::Entity* tb = Liar::LiarPluginRead::ReadModel(
			"C:/Users/Administrator/Desktop/model/tb/tb.model", "E:/c++/VSOpenGL/OpenGL/Assets/Images/");
		tb->SetPosition(0.0f, 0.0f, 380.0f);
		m_rootNode->AddChild(tb);*/

		/*Liar::Entity* laddy = m_rootNode->AddModel("models/laddy/laddy.model");
		laddy->SetPosition(10.0f, 0, 380.0f);
		laddy->SetScale(0.01);
		laddy->SetName("laddy");*/

		/*Liar::Entity* dva = m_rootNode->AddModel(AssetsMgr::GetPath("models/dva/dav.model"));
		dva->SetPosition(0, 0, -880.0f);
		dva->SetScale(0.01);
		dva->SetName("dva");*/

//        m_testModel = Liar::LiarPluginRead::ReadModel(AssetsMgr::GetPath("models/nano/nano.model"));
//        m_testModel = Liar::LiarPluginRead::ReadModel(AssetsMgr::GetPath("models/dog/dd.model"));
        //m_testModel = Liar::LiarPluginRead::ReadModel(AssetsMgr::GetPath("models/laddy/laddy.model"));
//        m_testModel = Liar::LiarPluginRead::ReadModel(AssetsMgr::GetPath("models/dva/dav.model"));
		//m_testModel = new Liar::Model();
		//m_testModel->AddMesh("C:/Users/Administrator/Desktop/test/test_box001.mesh", "E:/c++/VSOpenGL/OpenGL/Assets/Images/");
		//m_testModel->AddMeshByObj("C:/Users/Administrator/Desktop/test/ttt.obj", "E:/c++/VSOpenGL/OpenGL/Assets/Images/awesomeface.png");

		//m_testModel = Liar::AssimpMgr::LoadModel("C:/Users/Administrator/Desktop/nanosuit/nanosuit.obj");
//        m_testModel->SetZ(30.0f);
//        m_testModel->SetScale(0.5);

		//std::cout << *m_testModel << std::endl;
		//m_shader = new Shader(AssetsMgr::GetPath("Shaders/test1.vs"), AssetsMgr::GetPath("Shaders/test1.fs"));
		//m_shader->LinkProgram(AssetsMgr::GetPath("Shaders/test1.vs"), AssetsMgr::GetPath("Shaders/test1.fs"));
		//m_shader->LinkProgram(AssetsMgr::GetPath("Shaders/base/base.vs"), AssetsMgr::GetPath("Shaders/base/base.fs"));
		m_shader = Liar::AssetsMgr::GetInstance().GetShaderProgrom("root_shader",
			AssetsMgr::GetPath("Shaders/use/light/lighting1.vs").c_str(), AssetsMgr::GetPath("Shaders/use/light/lighting1.fs").c_str());

		//InitTest();

		/*Liar::Model* model = new Liar::Model();
		model->SetName("anim");
		model->Load(AssetsMgr::GetPath("models/anim/anim.model").c_str());
		model->SetY(-20);
		model->SetScale(0.2);
		m_rootNode->AddChild(model);*/

		Liar::LiarRectSprite* recSprite = new Liar::LiarRectSprite();
		recSprite->AddTexture(Liar::AssetsMgr::GetPath("Images/test.png").c_str());
		recSprite->SetScale(50.0f);
		recSprite->SetRotationX(-90);
		m_rootNode->AddChild(recSprite);
	}

    RenderMgr::~RenderMgr()
    {
        delete m_rootNode;
    }

	void RenderMgr::SetSize(unsigned int w, unsigned int h)
	{
		glViewport(0, 0, w, h);
		glScissor(0, 0, w, h);
	}
    
    void RenderMgr::Render()
    {
		glClearColor(m_red, m_green, m_blue, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);;

#ifdef RENDER_MOD_LINE
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
#endif
		m_camera->Render();
		m_shader->Use();
		m_shader->SetMat4("projection", *(m_camera->GetProjMatrix()));
		m_shader->SetMat4("viewMatrix", *(m_camera->GetTransform()));
		m_shader->SetMat4("viewExtentionMatrix", *(m_camera->GetExtentionMatrix()));
		m_shader->SetVec3("viewPos", m_camera->GetX(), m_camera->GetY(), m_camera->GetZ());

		m_lightsMgr->LightEffect(this);

		//BuildTest();
		//RenderTest();

        //m_rootNode->AddRotation(0.0f, 0.1f, 0.0f);
        m_rootNode->Render(this);

		m_lightsMgr->Render(this);

//        m_testModel->Render(*m_shader);

		//m_testMesh->Render(*m_shader);
    }
}
