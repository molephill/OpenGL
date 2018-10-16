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

	unsigned int loadTexture(char const * path)
	{
		unsigned int textureID;
		glGenTextures(1, &textureID);

		int width, height, nrComponents;
		unsigned char *data = stbi_load(path, &width, &height, &nrComponents, 0);
		if (data)
		{
			GLenum format;
			if (nrComponents == 1)
				format = GL_RED;
			else if (nrComponents == 3)
				format = GL_RGB;
			else if (nrComponents == 4)
				format = GL_RGBA;

			glBindTexture(GL_TEXTURE_2D, textureID);
			glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			stbi_image_free(data);
		}
		else
		{
			std::cout << "Texture failed to load at path: " << path << std::endl;
			stbi_image_free(data);
		}

		return textureID;
	}

	void RenderMgr::InitTest()
	{
		glGenVertexArrays(1, &m_vertexArrayID);
		glBindVertexArray(m_vertexArrayID);

		glGenBuffers(1, &m_vertexbuffer);
		glBindBuffer(GL_ARRAY_BUFFER, m_vertexbuffer);

		m_indices = new std::vector<int>();

		float l = 0.5f;
		float w = 0.5f;
		float h = 0.5f;

		float vertices[] = {
			-l, -w, -h,
			l, -w, -h,
			-l, w, -h,
			l, w, -h,

			-l, -w, h,
			l, -w, h,
			-l, w, h,
			l, w, h
		};

		m_indices->push_back(0);
		m_indices->push_back(2);
		m_indices->push_back(3);
		m_indices->push_back(3);
		m_indices->push_back(1);
		m_indices->push_back(0);

		m_indices->push_back(4);
		m_indices->push_back(5);
		m_indices->push_back(7);
		m_indices->push_back(7);
		m_indices->push_back(6);
		m_indices->push_back(4);

		m_indices->push_back(0);
		m_indices->push_back(1);
		m_indices->push_back(5);
		m_indices->push_back(5);
		m_indices->push_back(4);
		m_indices->push_back(0);

		m_indices->push_back(1);
		m_indices->push_back(3);
		m_indices->push_back(7);
		m_indices->push_back(7);
		m_indices->push_back(5);
		m_indices->push_back(1);

		m_indices->push_back(3);
		m_indices->push_back(2);
		m_indices->push_back(6);
		m_indices->push_back(6);
		m_indices->push_back(7);
		m_indices->push_back(3);

		m_indices->push_back(2);
		m_indices->push_back(0);
		m_indices->push_back(4);
		m_indices->push_back(4);
		m_indices->push_back(6);
		m_indices->push_back(2);

		m_indiceSize = m_indices->size();

		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		// 3. 设定顶点属性指针
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(0);

		int indiceSize1 = m_indiceSize * sizeof(unsigned int);
		glGenBuffers(1, &m_elementbuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_elementbuffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indiceSize1, GetIndicesData()->data(), GL_STATIC_DRAW);

		// first, configure the cube's VAO (and VBO)
		//glGenVertexArrays(1, &cubeVAO);
		//glGenBuffers(1, &VBO);

		//glBindBuffer(GL_ARRAY_BUFFER, VBO);
		//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		//glBindVertexArray(cubeVAO);
		//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
		//glEnableVertexAttribArray(0);
		//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
		//glEnableVertexAttribArray(1);
		//glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
		//glEnableVertexAttribArray(2);

		//// second, configure the light's VAO (VBO stays the same; the vertices are the same for the light object which is also a 3D cube)
		//unsigned int lightVAO;
		//glGenVertexArrays(1, &lightVAO);
		//glBindVertexArray(lightVAO);

		//glBindBuffer(GL_ARRAY_BUFFER, VBO);
		//// note that we update the lamp's position attribute's stride to reflect the updated buffer data
		//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
		//glEnableVertexAttribArray(0);

		//// load textures (we now use a utility function to keep the code more organized)
		//// -----------------------------------------------------------------------------
		//diffuseMap = loadTexture(AssetsMgr::GetPath("Images/container2.png").c_str());
		//specularMap = loadTexture(AssetsMgr::GetPath("Images/container2_specular.png").c_str());

		//// shader configuration
		//// --------------------
		//m_shader->Use();
		//m_shader->SetInt("material.diffuse", 0);
		//m_shader->SetInt("material.specular", 1);

	}

	void RenderMgr::BuildTest()
	{
		// directional light
		Liar::LiarShaderProgram& lightingShader = *m_shader;
		lightingShader.SetInt("numPointLights", 4);
		lightingShader.SetInt("numSpotLights", 1);
		lightingShader.SetVec3("dirLight.color", 1.0f, 1.0f, 1.0f);
		lightingShader.SetVec3("dirLight.direction", -0.2f, -1.0f, -0.3f);
		lightingShader.SetVec3("dirLight.ambient", 0.05f, 0.05f, 0.05f);
		lightingShader.SetVec3("dirLight.diffuse", 0.4f, 0.4f, 0.4f);
		lightingShader.SetVec3("dirLight.specular", 0.5f, 0.5f, 0.5f);
		// point light 1
		lightingShader.SetVec3("pointLights[0].color", 1.0f, 1.0f,1.0f);
		lightingShader.SetVec3("pointLights[0].position", 0.7f, 0.2f, 2.0f);
		lightingShader.SetVec3("pointLights[0].ambient", 0.05f, 0.05f, 0.05f);
		lightingShader.SetVec3("pointLights[0].diffuse", 0.8f, 0.8f, 0.8f);
		lightingShader.SetVec3("pointLights[0].specular", 1.0f, 1.0f, 1.0f);
		lightingShader.SetFloat("pointLights[0].constant", 1.0f);
		lightingShader.SetFloat("pointLights[0].linear", 0.09f);
		lightingShader.SetFloat("pointLights[0].quadratic", 0.032f);
		// point light 2
		lightingShader.SetVec3("pointLights[1].color", 1.0f, 1.0f, 1.0f);
		lightingShader.SetVec3("pointLights[1].position", 2.3f, -3.3f, -4.0f);
		lightingShader.SetVec3("pointLights[1].ambient", 0.05f, 0.05f, 0.05f);
		lightingShader.SetVec3("pointLights[1].diffuse", 0.8f, 0.8f, 0.8f);
		lightingShader.SetVec3("pointLights[1].specular", 1.0f, 1.0f, 1.0f);
		lightingShader.SetFloat("pointLights[1].constant", 1.0f);
		lightingShader.SetFloat("pointLights[1].linear", 0.09f);
		lightingShader.SetFloat("pointLights[1].quadratic", 0.032f);
		// point light 3
		lightingShader.SetVec3("pointLights[2].color", 1.0f, 1.0f, 1.0f);
		lightingShader.SetVec3("pointLights[2].position", -4.0f, 2.0f, -12.0f);
		lightingShader.SetVec3("pointLights[2].ambient", 0.05f, 0.05f, 0.05f);
		lightingShader.SetVec3("pointLights[2].diffuse", 0.8f, 0.8f, 0.8f);
		lightingShader.SetVec3("pointLights[2].specular", 1.0f, 1.0f, 1.0f);
		lightingShader.SetFloat("pointLights[2].constant", 1.0f);
		lightingShader.SetFloat("pointLights[2].linear", 0.09f);
		lightingShader.SetFloat("pointLights[2].quadratic", 0.032f);
		// point light 4
		lightingShader.SetVec3("pointLights[3].color", 1.0f, 1.0f, 1.0f);
		lightingShader.SetVec3("pointLights[3].position", 0.0f, 0.0f, -3.0f);
		lightingShader.SetVec3("pointLights[3].ambient", 0.05f, 0.05f, 0.05f);
		lightingShader.SetVec3("pointLights[3].diffuse", 0.8f, 0.8f, 0.8f);
		lightingShader.SetVec3("pointLights[3].specular", 1.0f, 1.0f, 1.0f);
		lightingShader.SetFloat("pointLights[3].constant", 1.0f);
		lightingShader.SetFloat("pointLights[3].linear", 0.09f);
		lightingShader.SetFloat("pointLights[3].quadratic", 0.032f);
		// spotLight
		lightingShader.SetVec3("spotLights[0].color", 1.0f, 1.0f, 0.0f);
		lightingShader.SetVec3("spotLights[0].position", m_camera->GetX(), m_camera->GetY(), m_camera->GetZ());
		lightingShader.SetVec3("spotLights[0].direction", 0.0f, 1.0f, 0.0f);
		lightingShader.SetVec3("spotLights[0].ambient", 0.0f, 0.0f, 0.0f);
		lightingShader.SetVec3("spotLights[0].diffuse", 1.0f, 1.0f, 1.0f);
		lightingShader.SetVec3("spotLights[0].specular", 1.0f, 1.0f, 1.0f);
		lightingShader.SetFloat("spotLights[0].constant", 1.0f);
		lightingShader.SetFloat("spotLights[0].linear", 0.09f);
		lightingShader.SetFloat("spotLights[0].quadratic", 0.032f);
		lightingShader.SetFloat("spotLights[0].cutOff", glm::cos(glm::radians(12.5f)));
		lightingShader.SetFloat("spotLights[0].outerCutOff", glm::cos(glm::radians(15.0f)));


		// ============================================== test2 ==========================================

		//// directional light
		//Liar::LiarShaderProgram& lightingShader = *m_shader;
		//lightingShader.SetInt("numPointLights", 4);
		//lightingShader.SetInt("numSpotLights", 1);
		//lightingShader.SetVec3("dirLight.baseLight.color", 1.0f, 1.0f, 1.0f);
		//lightingShader.SetVec3("dirLight.direction", -0.2f, -1.0f, -0.3f);
		//lightingShader.SetVec3("dirLight.baseLight.ambient", 0.05f, 0.05f, 0.05f);
		//lightingShader.SetVec3("dirLight.baseLight.diffuse", 0.4f, 0.4f, 0.4f);
		//lightingShader.SetVec3("dirLight.baseLight.specular", 0.5f, 0.5f, 0.5f);
		//// point light 1
		//lightingShader.SetVec3("pointLights[0].baseLight.color", 1.0f, 1.0f,1.0f);
		//lightingShader.SetVec3("pointLights[0].position", 0.7f, 0.2f, 2.0f);
		//lightingShader.SetVec3("pointLights[0].baseLight.ambient", 0.05f, 0.05f, 0.05f);
		//lightingShader.SetVec3("pointLights[0].baseLight.diffuse", 0.8f, 0.8f, 0.8f);
		//lightingShader.SetVec3("pointLights[0].baseLight.specular", 1.0f, 1.0f, 1.0f);
		//lightingShader.SetFloat("pointLights[0].constant", 1.0f);
		//lightingShader.SetFloat("pointLights[0].linear", 0.09f);
		//lightingShader.SetFloat("pointLights[0].quadratic", 0.032f);
		//// point light 2
		//lightingShader.SetVec3("pointLights[1].baseLight.color", 1.0f, 1.0f, 1.0f);
		//lightingShader.SetVec3("pointLights[1].position", 2.3f, -3.3f, -4.0f);
		//lightingShader.SetVec3("pointLights[1].baseLight.ambient", 0.05f, 0.05f, 0.05f);
		//lightingShader.SetVec3("pointLights[1].baseLight.diffuse", 0.8f, 0.8f, 0.8f);
		//lightingShader.SetVec3("pointLights[1].baseLight.specular", 1.0f, 1.0f, 1.0f);
		//lightingShader.SetFloat("pointLights[1].constant", 1.0f);
		//lightingShader.SetFloat("pointLights[1].linear", 0.09f);
		//lightingShader.SetFloat("pointLights[1].quadratic", 0.032f);
		//// point light 3
		//lightingShader.SetVec3("pointLights[2].baseLight.color", 1.0f, 1.0f, 1.0f);
		//lightingShader.SetVec3("pointLights[2].position", -4.0f, 2.0f, -12.0f);
		//lightingShader.SetVec3("pointLights[2].baseLight.ambient", 0.05f, 0.05f, 0.05f);
		//lightingShader.SetVec3("pointLights[2].baseLight.diffuse", 0.8f, 0.8f, 0.8f);
		//lightingShader.SetVec3("pointLights[2].baseLight.specular", 1.0f, 1.0f, 1.0f);
		//lightingShader.SetFloat("pointLights[2].constant", 1.0f);
		//lightingShader.SetFloat("pointLights[2].linear", 0.09f);
		//lightingShader.SetFloat("pointLights[2].quadratic", 0.032f);
		//// point light 4
		//lightingShader.SetVec3("pointLights[3].baseLight.color", 1.0f, 1.0f, 1.0f);
		//lightingShader.SetVec3("pointLights[3].position", 0.0f, 0.0f, -3.0f);
		//lightingShader.SetVec3("pointLights[3].baseLight.ambient", 0.05f, 0.05f, 0.05f);
		//lightingShader.SetVec3("pointLights[3].baseLight.diffuse", 0.8f, 0.8f, 0.8f);
		//lightingShader.SetVec3("pointLights[3].baseLight.specular", 1.0f, 1.0f, 1.0f);
		//lightingShader.SetFloat("pointLights[3].constant", 1.0f);
		//lightingShader.SetFloat("pointLights[3].linear", 0.09f);
		//lightingShader.SetFloat("pointLights[3].quadratic", 0.032f);
		//// spotLight
		//lightingShader.SetVec3("spotLights[0].pointLight.baseLight.color", 1.0f, 1.0f, 0.0f);
		//lightingShader.SetVec3("spotLights[0].pointLight.position", m_camera->GetX(), m_camera->GetY(), m_camera->GetZ());
		//lightingShader.SetVec3("spotLights[0].direction", 0.0f, 1.0f, 0.0f);
		//lightingShader.SetVec3("spotLights[0].pointLight.baseLight.ambient", 0.0f, 0.0f, 0.0f);
		//lightingShader.SetVec3("spotLights[0].pointLight.baseLight.diffuse", 1.0f, 1.0f, 1.0f);
		//lightingShader.SetVec3("spotLights[0].pointLight.baseLight.specular", 1.0f, 1.0f, 1.0f);
		//lightingShader.SetFloat("spotLights[0].pointLight.constant", 1.0f);
		//lightingShader.SetFloat("spotLights[0].pointLight.linear", 0.09f);
		//lightingShader.SetFloat("spotLights[0].pointLight.quadratic", 0.032f);
		//lightingShader.SetFloat("spotLights[0].cutOff", glm::cos(glm::radians(12.5f)));
		//lightingShader.SetFloat("spotLights[0].outerCutOff", glm::cos(glm::radians(15.0f)));
	}

	void RenderMgr::RenderTest()
	{
		// positions all containers
		//glm::vec3 cubePositions[] = {
		//	glm::vec3(0.0f,  0.0f,  0.0f),
		//	glm::vec3(2.0f,  5.0f, -15.0f),
		//	glm::vec3(-1.5f, -2.2f, -2.5f),
		//	glm::vec3(-3.8f, -2.0f, -12.3f),
		//	glm::vec3(2.4f, -0.4f, -3.5f),
		//	glm::vec3(-1.7f,  3.0f, -7.5f),
		//	glm::vec3(1.3f, -2.0f, -2.5f),
		//	glm::vec3(1.5f,  2.0f, -2.5f),
		//	glm::vec3(1.5f,  0.2f, -1.5f),
		//	glm::vec3(-1.3f,  1.0f, -1.5f)
		//};
		//// bind diffuse map
		//glActiveTexture(GL_TEXTURE0);
		//glBindTexture(GL_TEXTURE_2D, diffuseMap);
		//// bind specular map
		//glActiveTexture(GL_TEXTURE1);
		//glBindTexture(GL_TEXTURE_2D, specularMap);

		//// render containers
		//glBindVertexArray(cubeVAO);
		//for (unsigned int i = 0; i < 10; i++)
		//{
		//	// calculate the model matrix for each object and pass it to shader before drawing
		//	Liar::Matrix4 model;
		//	model.Translate(cubePositions[i].x, cubePositions[i].y, cubePositions[i].z);
		//	/*model = glm::translate(model, cubePositions[i]);
		//	float angle = 20.0f * i;
		//	model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));*/
		//	m_shader->SetMat4("model", model);

		//	glDrawArrays(GL_TRIANGLES, 0, 36);
		//}

		Liar::Matrix4 model;
		m_shader->SetMat4("model", model);
		glBindVertexArray(m_vertexArrayID);
		glDrawElements(GL_TRIANGLES, m_indiceSize, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

	}

	RenderMgr::RenderMgr():
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
		m_shader = new Liar::LiarShaderProgram();
		//m_shader->LinkProgram(AssetsMgr::GetPath("Shaders/test1.vs"), AssetsMgr::GetPath("Shaders/test1.fs"));
		//m_shader->LinkProgram(AssetsMgr::GetPath("Shaders/base/base.vs"), AssetsMgr::GetPath("Shaders/base/base.fs"));
		m_shader->LinkProgram(AssetsMgr::GetPath("Shaders/use/light/lighting1.vs"), AssetsMgr::GetPath("Shaders/use/light/lighting1.fs"));
		//InitTest();

		Liar::Model* model = new Liar::Model();
		model->SetName("anim");
		model->Load(AssetsMgr::GetPath("models/anim/anim.model").c_str());
		model->SetY(-20);
		model->SetScale(0.2);
		m_rootNode->AddChild(model);

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

		m_lightsMgr->LightEffect(*m_shader);

		//BuildTest();
		//RenderTest();

        //m_rootNode->AddRotation(0.0f, 0.1f, 0.0f);
        m_rootNode->Render(*m_shader);

		m_lightsMgr->Render(*m_camera);

//        m_testModel->Render(*m_shader);

		//m_testMesh->Render(*m_shader);
    }
}
