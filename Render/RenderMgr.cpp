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

namespace Liar
{
	class TestVertex
	{
	public:
		Liar::Vector3D position;
		Liar::Vector3D normal;
		Liar::Vector3D color;
		Liar::Vector2D uv;
	};

	RenderMgr::RenderMgr():m_red(0.2f),m_green(0.3f),m_blue(0.3f)
	{
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		m_camera = new Liar::Camera3D();
		m_camera->SetPosition(0, 0.0f, 10.0f);
		//m_camera->SetRotationX(26.0f);


		float vertices[] = {
			// positions          // colors								// texture coords
			0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
			0.5f, -0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
			-0.5f, -0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
			-0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
		};
		unsigned int indices[] = {
			0, 1, 3, // first triangle
			1, 2, 3  // second triangle
		};

		std::vector<Liar::LiarVertexBuffer*>* vertices2 = new std::vector<LiarVertexBuffer*>();
		Liar::LiarVertexBuffer* v = new Liar::LiarVertexBuffer();
		v->position->Set(0.5f, 0.5f, 0.0);
		v->color->Set(1.0f, 0.0f, 0.0f);
		v->normal->Set(1.0f, 0.0f, 0.0f);
		v->uv->Set(1.0f, 1.0f);
		vertices2->push_back(v);

		Liar::LiarVertexBuffer* v1 = new Liar::LiarVertexBuffer();
		v1->position->Set(0.5f, -0.5f, 0.0f);
		v1->color->Set(1.0f, 1.0f, 0.0f);
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


		// ==============================================================================
		std::vector<Liar::TestVertex>* vertices3 = new std::vector<TestVertex>();
		Liar::TestVertex v3_1;
		v3_1.position.Set(0.5f, 0.5f, 0.0);
		v3_1.color.Set(1.0f, 0.0f, 0.0f);
		v3_1.normal.Set(1.0f, 0.0f, 0.0f);
		v3_1.uv.Set(1.0f, 1.0f);
		vertices3->push_back(v3_1);

		Liar::TestVertex v3_2;
		v3_2.position.Set(0.5f, -0.5f, 0.0f);
		v3_2.color.Set(1.0f, 1.0f, 0.0f);
		v3_2.normal.Set(1.0f, 0.0f, 0.0f);
		v3_2.uv.Set(1.0f, 0.0f);
		vertices3->push_back(v3_2);

		Liar::TestVertex v3_3;
		v3_3.position.Set(-0.5f, -0.5f, 0.0f);
		v3_3.color.Set(0.0f, 0.0f, 1.0f);
		v3_3.normal.Set(1.0f, 0.0f, 0.0f);
		v3_3.uv.Set(0.0f, 0.0f);
		vertices3->push_back(v3_3);

		Liar::TestVertex v3_4;
		v3_4.position.Set(-0.5f, 0.5f, 0.0f);
		v3_4.color.Set(1.0f, 1.0f, 0.0f);
		v3_4.normal.Set(1.0f, 0.0f, 0.0f);
		v3_4.uv.Set(0.0f, 1.0f);
		vertices3->push_back(v3_4);
		// ==============================================================================


		std::vector<float>* vertices1 = new std::vector<float>();
		size_t len = sizeof(vertices) / sizeof(float);
		for (size_t i = 0; i < len; ++i)
		{
			vertices1->push_back(vertices[i]);
		}

		std::vector<unsigned int>* indices1 = new std::vector<unsigned int>();
		size_t indicesLen = sizeof(indices) / sizeof(unsigned int);
		for (size_t i = 0; i < indicesLen; ++i)
		{
			indices1->push_back(indices[i]);
		}

		size_t buffSize = sizeof(vertices);
		size_t buffSize1 = vertices1->size() * sizeof(float);
		
		//size_t one = sizeof(Liar::Vector3D) * 3 + sizeof(Liar::Vector2D);
		size_t one = sizeof(Liar::LiarVertexBuffer);
		size_t buffSize2 = vertices2->size() * one;

		size_t one1 = sizeof(Liar::TestVertex);
		size_t buffSize3 = vertices3->size() * one1;

		size_t indiceSize = sizeof(indices);
		size_t indiceSize1 = indices1->size() * sizeof(unsigned int);

		glGenVertexArrays(1, &m_VAO);
		glGenBuffers(1, &m_VBO);
		glGenBuffers(1, &m_EBO);

		glBindVertexArray(m_VAO);

		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		glBufferData(GL_ARRAY_BUFFER, buffSize3, vertices3->data(), GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indiceSize1, indices1->data(), GL_STATIC_DRAW);

		//// position attribute
		//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)0);
		//glEnableVertexAttribArray(0);
		//// color attribute
		//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(3 * sizeof(float)));
		//glEnableVertexAttribArray(1);
		//// color attribute
		//glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(6 * sizeof(float)));
		//glEnableVertexAttribArray(2);
		//// texture coord attribute
		//glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(9 * sizeof(float)));
		//glEnableVertexAttribArray(3);

		/*size_t n_offset = offsetof(TestVertex, normal);
		size_t c_offset = offsetof(TestVertex, color);
		size_t u_offset = offsetof(TestVertex, uv);*/

		size_t n_offset = offsetof(LiarVertexBuffer, normal);
		size_t c_offset = offsetof(LiarVertexBuffer, color);
		size_t u_offset = offsetof(LiarVertexBuffer, uv);

		size_t setSize = one;

		size_t step1 = GL_UNSIGNED_BYTE;
		size_t step2 = GL_BYTE;
		size_t step3 = GL_FLOAT;

		// position attribute
		glVertexAttribPointer(0, 4, GL_UNSIGNED_BYTE, GL_FALSE, setSize, (void*)0);
		glEnableVertexAttribArray(0);
		// color attribute
		glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_FALSE, setSize, (void*)n_offset);
		glEnableVertexAttribArray(1);
		// color attribute
		glVertexAttribPointer(2, 4, GL_UNSIGNED_BYTE, GL_FALSE, setSize, (void*)c_offset);
		glEnableVertexAttribArray(2);
		// texture coord attribute
		glVertexAttribPointer(3, 4, GL_UNSIGNED_BYTE, GL_FALSE, setSize, (void*)u_offset);
		glEnableVertexAttribArray(3);

		/*m_testMesh = Liar::LiarMeshRead::ReadMesh("C:/Users/Administrator/Desktop/nanosuit/nano_visor.mesh");
		m_testMesh->Upload();*/

		

#ifndef __APPLE__
		m_shader = new Shader("E:/c++/VSOpenGL/OpenGL/Assets/Shaders/test1.vs",
			"E:/c++/VSOpenGL/OpenGL/Assets/Shaders/test1.fs");
#else
		m_shader = new Shader("/Users/maowei/Downloads/C++/OpenGL/OpenGL/Assets/Shaders/test.vs",
			"/Users/maowei/Downloads/C++/OpenGL/OpenGL/Assets/Shaders/test.fs");
#endif // __APPLE__
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

		//m_testMesh->Render(*m_shader);

		glBindVertexArray(m_VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		//glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
    }
}
