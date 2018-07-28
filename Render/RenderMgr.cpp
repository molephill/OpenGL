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

#include <LiarMeshRead.h>
#include <AssetsMgr.hpp>

namespace Liar
{

	void Test()
	{
		//unsigned int indices[] = {
		//	0, 1, 3, // first triangle
		//	1, 2, 3  // second triangle
		//};

		//std::vector<Liar::LiarVertexBuffer*>* vertices2 = new std::vector<LiarVertexBuffer*>();
		//Liar::LiarVertexBuffer* v = new Liar::LiarVertexBuffer();
		//v->position->Set(0.5f, 0.5f, 0.0);
		//v->color->Set(1.0f, 0.0f, 0.0f);
		//v->normal->Set(1.0f, 0.0f, 0.0f);
		//v->uv->Set(1.0f, 1.0f);
		//vertices2->push_back(v);

		//Liar::LiarVertexBuffer* v1 = new Liar::LiarVertexBuffer();
		//v1->position->Set(0.5f, -0.5f, 0.0f);
		//v1->color->Set(0.0f, 1.0f, 0.0f);
		//v1->normal->Set(1.0f, 0.0f, 0.0f);
		//v1->uv->Set(1.0f, 0.0f);
		//vertices2->push_back(v1);

		//Liar::LiarVertexBuffer* v2 = new Liar::LiarVertexBuffer();
		//v2->position->Set(-0.5f, -0.5f, 0.0f);
		//v2->color->Set(0.0f, 0.0f, 1.0f);
		//v2->normal->Set(1.0f, 0.0f, 0.0f);
		//v2->uv->Set(0.0f, 0.0f);
		//vertices2->push_back(v2);

		//Liar::LiarVertexBuffer* v3 = new Liar::LiarVertexBuffer();
		//v3->position->Set(-0.5f, 0.5f, 0.0f);
		//v3->color->Set(1.0f, 1.0f, 0.0f);
		//v3->normal->Set(1.0f, 0.0f, 0.0f);
		//v3->uv->Set(0.0f, 1.0f);
		//vertices2->push_back(v3);

		//std::vector<unsigned int>* indices1 = new std::vector<unsigned int>();
		//size_t indicesLen = sizeof(indices) / sizeof(unsigned int);
		//for (size_t i = 0; i < indicesLen; ++i)
		//{
		//	indices1->push_back(indices[i]);
		//}

		//size_t indiceSize1 = indices1->size() * sizeof(unsigned int);

		//glGenVertexArrays(1, &m_VAO);
		//glGenBuffers(1, &m_VBO);
		//glGenBuffers(1, &m_EBO);

		//glBindVertexArray(m_VAO);

		//glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		////glBufferData(GL_ARRAY_BUFFER, buffSize3, vertices3->data(), GL_STATIC_DRAW);

		//size_t positionSize = sizeof(Liar::Vector3D);
		//size_t normalSize = sizeof(Liar::Vector3D);
		//size_t colorSize = sizeof(Liar::Vector3D);
		//size_t uvSize = sizeof(Liar::Vector2D);

		//size_t oneSize = positionSize + normalSize + colorSize + uvSize;
		//size_t vertexSize = vertices2->size();
		//size_t totalSize = vertexSize * oneSize;

		//size_t normalOffSize = positionSize;
		//size_t colorOffSize = positionSize + normalOffSize;
		//size_t uvOffSize = colorOffSize + colorSize;

		//glBufferData(GL_ARRAY_BUFFER, totalSize, nullptr, GL_STATIC_DRAW);
		//for (size_t i = 0; i < vertexSize; ++i)
		//{
		//	size_t start = i * oneSize;
		//	Liar::LiarVertexBuffer* buffData = vertices2->at(i);
		//	glBufferSubData(GL_ARRAY_BUFFER, start, positionSize, buffData->position);
		//	glBufferSubData(GL_ARRAY_BUFFER, start + normalOffSize, normalSize, buffData->normal);
		//	glBufferSubData(GL_ARRAY_BUFFER, start + colorOffSize, colorSize, buffData->color);
		//	glBufferSubData(GL_ARRAY_BUFFER, start + uvOffSize, uvSize, buffData->uv);
		//}

		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
		//glBufferData(GL_ELEMENT_ARRAY_BUFFER, indiceSize1, indices1->data(), GL_STATIC_DRAW);

		//// position attribute
		//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, oneSize, (void*)0);
		//glEnableVertexAttribArray(0);
		//// color attribute
		//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, oneSize, (void*)normalOffSize);
		//glEnableVertexAttribArray(1);
		//// color attribute
		//glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, oneSize, (void*)colorOffSize);
		//glEnableVertexAttribArray(2);
		//// texture coord attribute
		//glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, oneSize, (void*)uvOffSize);
		//glEnableVertexAttribArray(3);


		//unsigned int indices[] = {
		//	0, 1, 3, // first triangle
		//	1, 2, 3  // second triangle
		//};

		//m_testMesh = new Liar::LiarMesh();
		//std::vector<Liar::LiarVertexBuffer*>* vertices2 = m_testMesh->GetGeo()->GetBuffers();

		//Liar::LiarVertexBuffer* v = new Liar::LiarVertexBuffer();
		//v->position->Set(0.5f, 0.5f, 0.0);
		//v->color->Set(1.0f, 0.0f, 0.0f);
		//v->normal->Set(1.0f, 0.0f, 0.0f);
		//v->uv->Set(1.0f, 1.0f);
		//vertices2->push_back(v);

		//Liar::LiarVertexBuffer* v1 = new Liar::LiarVertexBuffer();
		//v1->position->Set(0.5f, -0.5f, 0.0f);
		//v1->color->Set(0.0f, 1.0f, 0.0f);
		//v1->normal->Set(1.0f, 0.0f, 0.0f);
		//v1->uv->Set(1.0f, 0.0f);
		//vertices2->push_back(v1);

		//Liar::LiarVertexBuffer* v2 = new Liar::LiarVertexBuffer();
		//v2->position->Set(-0.5f, -0.5f, 0.0f);
		//v2->color->Set(0.0f, 0.0f, 1.0f);
		//v2->normal->Set(1.0f, 0.0f, 0.0f);
		//v2->uv->Set(0.0f, 0.0f);
		//vertices2->push_back(v2);

		//Liar::LiarVertexBuffer* v3 = new Liar::LiarVertexBuffer();
		//v3->position->Set(-0.5f, 0.5f, 0.0f);
		//v3->color->Set(1.0f, 1.0f, 0.0f);
		//v3->normal->Set(1.0f, 0.0f, 0.0f);
		//v3->uv->Set(0.0f, 1.0f);
		//vertices2->push_back(v3);


		//m_testMesh->GetGeo()->SetBufferSize(4);

		//std::vector<unsigned int>* indices1 = m_testMesh->GetGeo()->GetIndices();
		//size_t indicesLen = sizeof(indices) / sizeof(unsigned int);
		//for (size_t i = 0; i < indicesLen; ++i)
		//{
		//indices1->push_back(indices[i]);
		//}
	}

	RenderMgr::RenderMgr():m_red(0.2f),m_green(0.3f),m_blue(0.3f)
	{
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		m_camera = new Liar::Camera3D();
		m_camera->SetPosition(0.0f, -25.0f, -25.0f);
		m_camera->SetRotationX(45.0f);
        m_camera->LookAt(0.0f, 0.0f, 0.0f);
		//m_camera->SetRotationX(26.0f);

		unsigned int indices[] = {
			0, 1, 3, // first triangle
			1, 2, 3  // second triangle
		};

		m_testMesh = new Liar::LiarMesh();
		std::vector<Liar::LiarVertexBuffer*>* vertices2 = m_testMesh->GetGeo()->GetBuffers();

		Liar::LiarVertexBuffer* v = new Liar::LiarVertexBuffer();
		v->position->Set(0.5f, 0.5f, 0.0);
		v->color->Set(1.0f, 0.0f, 0.0f);
		v->normal->Set(1.0f, 0.0f, 0.0f);
		v->uv->Set(1.0f, 1.0f);
		vertices2->push_back(v);

		Liar::LiarVertexBuffer* v1 = new Liar::LiarVertexBuffer();
		v1->position->Set(0.5f, -0.5f, 0.0f);
		v1->color->Set(0.0f, 1.0f, 0.0f);
		v1->normal->Set(1.0f, 0.0f, 0.0f);
		v1->uv->Set(1.0f, 0.0f);
		vertices2->push_back(v1);

		Liar::LiarVertexBuffer* v2 = new Liar::LiarVertexBuffer();
		v2->position->Set(-0.5f, -0.5f, 0.0f);
		v2->color->Set(0.0f, 0.0f, 1.0f);
		v2->normal->Set(1.0f, 0.0f, 0.0f);
		v2->uv->Set(0.0f, 0.0f);
		vertices2->push_back(v2);

		Liar::LiarVertexBuffer* v3 = new Liar::LiarVertexBuffer();
		v3->position->Set(-0.5f, 0.5f, 0.0f);
		v3->color->Set(1.0f, 1.0f, 0.0f);
		v3->normal->Set(1.0f, 0.0f, 0.0f);
		v3->uv->Set(0.0f, 1.0f);
		vertices2->push_back(v3);


		m_testMesh->GetGeo()->SetBufferSize(4);

		std::vector<unsigned int>* indices1 = m_testMesh->GetGeo()->GetIndices();
		size_t indicesLen = sizeof(indices) / sizeof(unsigned int);
		for (size_t i = 0; i < indicesLen; ++i)
		{
			indices1->push_back(indices[i]);
		}

		m_testMesh->Upload();

		Liar::LiarTexture* tex = AssetsMgr::GetInstance().GetTexture("E:/c++/VSOpenGL/OpenGL/Assets/Images/awesomeface.png");
		m_testMesh->GetMat()->GetTextures()->push_back(tex);
		m_testMesh->GetMat()->SetTexSize(1);

		//m_testModel = new Liar::Model();

#ifndef __APPLE__
        //m_testMesh = Liar::LiarMeshRead::ReadMesh("C:/Users/Administrator/Desktop/nanosuit/nano_legs.mesh");
		//m_testModel->AddMesh("C:/Users/Administrator/Desktop/nanosuit/nano_arms.mesh");
		/*m_testModel->AddMesh("C:/Users/Administrator/Desktop/nanosuit/nano_body.mesh");
		m_testModel->AddMesh("C:/Users/Administrator/Desktop/nanosuit/nano_hands.mesh");
		m_testModel->AddMesh("C:/Users/Administrator/Desktop/nanosuit/nano_helmet.mesh");
		m_testModel->AddMesh("C:/Users/Administrator/Desktop/nanosuit/nano_legs.mesh");
		m_testModel->AddMesh("C:/Users/Administrator/Desktop/nanosuit/nano_lights.mesh");
		m_testModel->AddMesh("C:/Users/Administrator/Desktop/nanosuit/nano_visor.mesh");*/
		m_shader = new Shader("E:/c++/VSOpenGL/OpenGL/Assets/Shaders/test1.vs",
			"E:/c++/VSOpenGL/OpenGL/Assets/Shaders/test1.fs");
#else
        m_testMesh = Liar::LiarMeshRead::ReadMesh("/Users/maowei/Downloads/C++/OpenGL/OpenGL/Assets/models/nanosuit/nano_legs.mesh");
		m_shader = new Shader("/Users/maowei/Downloads/C++/OpenGL/OpenGL/Assets/Shaders/test1.vs",
			"/Users/maowei/Downloads/C++/OpenGL/OpenGL/Assets/Shaders/test1.fs");
#endif // __APPLE__
        
       // m_testMesh->Upload();
		m_shader->Use();
		m_shader->SetInt("texture1", 0);
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

		//m_testModel->Render(*m_shader);

		m_testMesh->Render(*m_shader);

		/*glBindVertexArray(m_VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);*/
		//glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
    }
}
