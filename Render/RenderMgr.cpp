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
#include "Global.hpp"
#include "AssetsMgr.hpp"


namespace Liar
{

	#define MODEL(path) （"" + BASE_PATH + "models/")

	RenderMgr::RenderMgr():m_red(0.2f),m_green(0.3f),m_blue(0.3f)
	{
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		glCullFace(GL_BACK);
		glEnable(GL_CULL_FACE);
		glEnable(GL_DEPTH_TEST);
        
#ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

		m_camera = new Liar::Camera3D();
		m_camera->SetPosition(0.0f, -10.0f, -10.0f);
        //m_camera->SetRotationX(45.0f);
        m_camera->LookAt(0.0f, 1.0f, 0.0f);
		//m_camera->SetRotationX(26.0f);

//        m_testModel = Liar::LiarPluginRead::ReadModel(AssetsMgr::GetPath("models/nano/nano.model"));
//        m_testModel = Liar::LiarPluginRead::ReadModel(AssetsMgr::GetPath("models/dog/dd.model"));
        //m_testModel = Liar::LiarPluginRead::ReadModel(AssetsMgr::GetPath("models/laddy/laddy.model"));
        m_testModel = Liar::LiarPluginRead::ReadModel(AssetsMgr::GetPath("models/dva/dav.model"));
		//m_testModel = new Liar::Model();
		//m_testModel->AddMesh("C:/Users/Administrator/Desktop/test/test_box001.mesh", "E:/c++/VSOpenGL/OpenGL/Assets/Images/");
		//m_testModel->AddMeshByObj("C:/Users/Administrator/Desktop/test/ttt.obj", "E:/c++/VSOpenGL/OpenGL/Assets/Images/awesomeface.png");

		//m_testModel = Liar::AssimpMgr::LoadModel("C:/Users/Administrator/Desktop/nanosuit/nanosuit.obj");
		m_testModel->SetZ(30.0f);
        m_testModel->SetScale(0.05);

		//std::cout << *m_testModel << std::endl;
		m_shader = new Shader(AssetsMgr::GetPath("Shaders/test1.vs"), AssetsMgr::GetPath("Shaders/test1.fs"));
	}

    RenderMgr::~RenderMgr()
    {

    }

	void RenderMgr::SetSize(unsigned int w, unsigned int h)
	{
		glViewport(0, 0, w, h);
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
		m_shader->SetMat4("projection", *(m_camera->GetMatrix()));

		m_testModel->Render(*m_shader);

		//m_testMesh->Render(*m_shader);

		/*glBindVertexArray(m_VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);*/
		//glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
    }
}
