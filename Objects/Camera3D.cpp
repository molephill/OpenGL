#include "Camera3D.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include "AssetsMgr.hpp"

namespace Liar
{
	Camera3D::Camera3D(float nearClipping, float farClipping):
		m_x(0.0f),m_y(0.0f),m_z(0.0f), m_transformChanged(true),
        m_viewMatrix(new Liar::Matrix4()),
		m_nearClipping(nearClipping), m_farClipping(farClipping),
		m_targetX(0.0f),m_targetY(0.0f),m_targetZ(0.0f),
		m_fov(60.0f),m_viewWidth(WINDOW_W),m_viewHeight(WINDOW_H),
		m_isPerspective(true),
		m_projection(new Liar::Matrix4())
	{
	}


	Camera3D::~Camera3D()
	{
        delete m_viewMatrix;
        delete m_projection;
	}

	void Camera3D::AddX(float x)
	{
		if (x != 0)
		{
			m_x += x;
			m_transformChanged = true;
		}
	}

	void Camera3D::AddY(float y)
	{
		if (y != 0)
		{
			m_y += y;
			m_transformChanged = true;
		}
	}

	void Camera3D::AddZ(float z)
	{
		if (z != 0)
		{
			m_z += z;
			m_transformChanged = true;
		}
	}

	void Camera3D::AddPosition(float x, float y, float z)
	{
		if (x != 0 || y != 0 || z != 0)
		{
			m_x += x;
			m_y += y;
			m_z += z;
			m_transformChanged = true;
		}
	}

	void Camera3D::AddPosition(const Liar::Vector3D& v)
	{
		AddPosition(v.x, v.y, v.z);
	}

	void Camera3D::SetPosition(float x, float y, float z)
	{
		if (m_x != x || m_y != y || m_z != z)
		{
			m_x = x;
			m_y = y;
			m_z = z;
			m_transformChanged = true;
		}
	}

	void Camera3D::SetPosition(const Liar::Vector3D& v)
	{
		SetPosition(v.x, v.y, v.z);
	}

	void Camera3D::LookAt(float x, float y, float z)
	{
		if (m_targetX != x || m_targetY != y || m_targetZ != z)
		{
			m_targetX = x;
			m_targetY = y;
			m_targetZ = z;
			m_transformChanged = true;
		}
	}

	void Camera3D::SetViewSize(unsigned int x, unsigned int y, unsigned int w, unsigned int h)
	{
		glViewport((GLsizei)x, (GLsizei)y, (GLsizei)w, (GLsizei)h);
		if (m_viewWidth != w || m_viewHeight != h)
		{
			m_viewWidth = w;
			m_viewHeight = h;
			m_transformChanged = true;
		}
	}

	void Camera3D::ChangeMode(bool mode)
	{
		if (m_isPerspective != mode)
		{
			m_isPerspective = mode;
			m_transformChanged = true;
		}
	}

	///////////////////////////////////////////////////////////////////////////////
	// set a symmetric perspective frustum with 4 params similar to gluPerspective
	// (vertical field of view, aspect ratio, near, far)
	///////////////////////////////////////////////////////////////////////////////
	void Camera3D::SetFrustum(float fovY, float aspectRatio, float front, float back)
	{
		float tangent = tanf(fovY / 2 * DEG2RAD);   // tangent of half fovY
		float height = front * tangent;           // half height of near plane
		float width = height * aspectRatio;       // half width of near plane

		// params: left, right, bottom, top, near, far
		if (m_isPerspective)
		{
			SetFrustum(-width, width, -height, height, front, back);
		}
		else
		{
			SetOrthoFrustum(-width, width, -height, height, front, back);
		}
	}

	///////////////////////////////////////////////////////////////////////////////
	// set a perspective frustum with 6 params similar to glFrustum()
	// (left, right, bottom, top, near, far)
	// Note: this is for row-major notation. OpenGL needs transpose it
	///////////////////////////////////////////////////////////////////////////////
	void Camera3D::SetFrustum(float l, float r, float b, float t, float n, float f)
	{
		(*m_projection)[0] = 2 * n / (r - l);
		(*m_projection)[5] = 2 * n / (t - b);
		(*m_projection)[8] = (r + l) / (r - l);
		(*m_projection)[9] = (t + b) / (t - b);
		(*m_projection)[10] = -(f + n) / (f - n);
		(*m_projection)[11] = -1.0f;
		(*m_projection)[14] = -(2 * f * n) / (f - n);
		(*m_projection)[15] = 0.0f;
	}

	///////////////////////////////////////////////////////////////////////////////
	// set a orthographic frustum with 6 params similar to glOrtho()
	// (left, right, bottom, top, near, far)
	///////////////////////////////////////////////////////////////////////////////
	void Camera3D::SetOrthoFrustum(float l, float r, float b, float t, float n, float f)
	{
		(*m_projection)[0] = 2 / (r - l);
		(*m_projection)[5] = 2 / (t - b);
		(*m_projection)[10] = -2 / (f - n);
		(*m_projection)[12] = -(r + l) / (r - l);
		(*m_projection)[13] = -(t + b) / (t - b);
		(*m_projection)[14] = -(f + n) / (f - n);
	}

	void Camera3D::Render()
	{
		if (m_transformChanged)
		{
			m_viewMatrix->Identity();
			m_viewMatrix->Translate(m_x, m_y, m_z);
			m_viewMatrix->LookAt(m_targetX, m_targetY, m_targetZ);
            
            glm::vec3 position = glm::vec3(m_x, m_y, m_z);
            glm::vec3 target = glm::vec3(m_targetX, m_targetY, m_targetZ);
            glm::vec3 worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
            // 1. Position = known
            // 2. Calculate cameraDirection
            glm::vec3 zaxis = glm::normalize(position - target);
            // 3. Get positive right axis vector
            glm::vec3 xaxis = glm::normalize(glm::cross(glm::normalize(worldUp), zaxis));
            // 4. Calculate camera up vector
            glm::vec3 yaxis = glm::cross(zaxis, xaxis);
            
            // Create translation and rotation matrix
            // In glm we access elements as mat[col][row] due to column-major layout
            glm::mat4 translation(1.0f); // Identity matrix by default
            translation[3][0] = position.x; // Third column, first row
            translation[3][1] = position.y;
            translation[3][2] = position.z;
            glm::mat4 rotation(1.0f);
            rotation[0][0] = xaxis.x; // First column, first row
            rotation[1][0] = xaxis.y;
            rotation[2][0] = xaxis.z;
            rotation[0][1] = yaxis.x; // First column, second row
            rotation[1][1] = yaxis.y;
            rotation[2][1] = yaxis.z;
            rotation[0][2] = zaxis.x; // First column, third row
            rotation[1][2] = zaxis.y;
            rotation[2][2] = zaxis.z;
            
            Liar::AssetsMgr::PrintMat4(rotation*translation);
            
            std::cout << "============" << std::endl;
            
			std::cout << (*m_viewMatrix) << std::endl;

			// projection
			SetFrustum(m_fov, static_cast<float>(m_viewWidth / m_viewHeight), m_nearClipping, m_farClipping);

			std::cout << (*m_projection) << std::endl;

			m_transformChanged = false;
		}
	}

	///////////////////////////////////////////////////////////////////////////////
	// compute 8 vertices of frustum
	///////////////////////////////////////////////////////////////////////////////
	void Camera3D::ComputeFrustumVertices(float l, float r, float b, float t, float n, float f)
	{
		//float ratio;
		//float farLeft;
		//float farRight;
		//float farBottom;
		//float farTop;

		//// perspective mode
		//if (m_isPerspective)
		//{
		//	ratio = f / n;
		//}
		//else
		//{
		//	// orthographic mode
		//	ratio = 1;
		//}
		//farLeft = l * ratio;
		//farRight = r * ratio;
		//farBottom = b * ratio;
		//farTop = t * ratio;

		//// compute 8 vertices of the frustum
		//// near top right
		//frustumVertices[0].x = r;
		//frustumVertices[0].y = t;
		//frustumVertices[0].z = -n;

		//// near top left
		//frustumVertices[1].x = l;
		//frustumVertices[1].y = t;
		//frustumVertices[1].z = -n;

		//// near bottom left
		//frustumVertices[2].x = l;
		//frustumVertices[2].y = b;
		//frustumVertices[2].z = -n;

		//// near bottom right
		//frustumVertices[3].x = r;
		//frustumVertices[3].y = b;
		//frustumVertices[3].z = -n;

		//// far top right
		//frustumVertices[4].x = farRight;
		//frustumVertices[4].y = farTop;
		//frustumVertices[4].z = -f;

		//// far top left
		//frustumVertices[5].x = farLeft;
		//frustumVertices[5].y = farTop;
		//frustumVertices[5].z = -f;

		//// far bottom left
		//frustumVertices[6].x = farLeft;
		//frustumVertices[6].y = farBottom;
		//frustumVertices[6].z = -f;

		//// far bottom right
		//frustumVertices[7].x = farRight;
		//frustumVertices[7].y = farBottom;
		//frustumVertices[7].z = -f;

		//// compute normals
		//frustumNormals[0] = (frustumVertices[5] - frustumVertices[1]).cross(frustumVertices[2] - frustumVertices[1]);
		//frustumNormals[0].normalize();

		//frustumNormals[1] = (frustumVertices[3] - frustumVertices[0]).cross(frustumVertices[4] - frustumVertices[0]);
		//frustumNormals[1].normalize();

		//frustumNormals[2] = (frustumVertices[6] - frustumVertices[2]).cross(frustumVertices[3] - frustumVertices[2]);
		//frustumNormals[2].normalize();

		//frustumNormals[3] = (frustumVertices[4] - frustumVertices[0]).cross(frustumVertices[1] - frustumVertices[0]);
		//frustumNormals[3].normalize();

		//frustumNormals[4] = (frustumVertices[1] - frustumVertices[0]).cross(frustumVertices[3] - frustumVertices[0]);
		//frustumNormals[4].normalize();

		//frustumNormals[5] = (frustumVertices[7] - frustumVertices[4]).cross(frustumVertices[5] - frustumVertices[4]);
		//frustumNormals[5].normalize();
	}

	///////////////////////////////////////////////////////////////////////////////
	// draw frustum with 6 params (left, right, bottom, top, near, far)
	///////////////////////////////////////////////////////////////////////////////
	void Camera3D::DrawFrustum(float l, float r, float b, float t, float n, float f)
	{
		//ComputeFrustumVertices(l, r, b, t, n, f);

		//float colorLine1[4] = { 0.7f, 0.7f, 0.7f, 0.7f };
		//float colorLine2[4] = { 0.2f, 0.2f, 0.2f, 0.7f };
		//float colorPlane1[4] = { 0.5f, 0.5f, 0.5f, 0.4f };

		//// draw lines
		//glDisable(GL_LIGHTING);
		//glDisable(GL_CULL_FACE);
		//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		//// draw the edges around frustum
		//if (projectionMode == 0)
		//{
		//	glBegin(GL_LINES);
		//	glColor4fv(colorLine2);
		//	glVertex3f(0, 0, 0);
		//	glColor4fv(colorLine1);
		//	glVertex3fv(&frustumVertices[4].x);

		//	glColor4fv(colorLine2);
		//	glVertex3f(0, 0, 0);
		//	glColor4fv(colorLine1);
		//	glVertex3fv(&frustumVertices[5].x);

		//	glColor4fv(colorLine2);
		//	glVertex3f(0, 0, 0);
		//	glColor4fv(colorLine1);
		//	glVertex3fv(&frustumVertices[6].x);

		//	glColor4fv(colorLine2);
		//	glVertex3f(0, 0, 0);
		//	glColor4fv(colorLine1);
		//	glVertex3fv(&frustumVertices[7].x);
		//	glEnd();
		//}
		//else
		//{
		//	glColor4fv(colorLine1);
		//	glBegin(GL_LINES);
		//	glVertex3fv(&frustumVertices[0].x);
		//	glVertex3fv(&frustumVertices[4].x);
		//	glVertex3fv(&frustumVertices[1].x);
		//	glVertex3fv(&frustumVertices[5].x);
		//	glVertex3fv(&frustumVertices[2].x);
		//	glVertex3fv(&frustumVertices[6].x);
		//	glVertex3fv(&frustumVertices[3].x);
		//	glVertex3fv(&frustumVertices[7].x);
		//	glEnd();
		//}

		//glColor4fv(colorLine1);
		//glBegin(GL_LINE_LOOP);
		//glVertex3fv(&frustumVertices[4].x);
		//glVertex3fv(&frustumVertices[5].x);
		//glVertex3fv(&frustumVertices[6].x);
		//glVertex3fv(&frustumVertices[7].x);
		//glEnd();

		//glColor4fv(colorLine1);
		//glBegin(GL_LINE_LOOP);
		//glVertex3fv(&frustumVertices[0].x);
		//glVertex3fv(&frustumVertices[1].x);
		//glVertex3fv(&frustumVertices[2].x);
		//glVertex3fv(&frustumVertices[3].x);
		//glEnd();

		//glEnable(GL_CULL_FACE);
		//glEnable(GL_LIGHTING);

		//// frustum is transparent.
		//// Draw the frustum faces twice: backfaces first then frontfaces second.
		//for (int i = 0; i < 2; ++i)
		//{
		//	if (i == 0)
		//	{
		//		// for inside planes
		//		//glCullFace(GL_FRONT);
		//		//glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
		//	}
		//	else
		//	{
		//		// draw outside planes
		//		glCullFace(GL_BACK);
		//		glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE);
		//	}

		//	glColor4fv(colorPlane1);
		//	glBegin(GL_QUADS);
		//	// left
		//	glNormal3fv(&frustumNormals[0].x);
		//	glVertex3fv(&frustumVertices[1].x);
		//	glVertex3fv(&frustumVertices[5].x);
		//	glVertex3fv(&frustumVertices[6].x);
		//	glVertex3fv(&frustumVertices[2].x);
		//	// right
		//	glNormal3fv(&frustumNormals[1].x);
		//	glVertex3fv(&frustumVertices[0].x);
		//	glVertex3fv(&frustumVertices[3].x);
		//	glVertex3fv(&frustumVertices[7].x);
		//	glVertex3fv(&frustumVertices[4].x);
		//	// bottom
		//	glNormal3fv(&frustumNormals[2].x);
		//	glVertex3fv(&frustumVertices[2].x);
		//	glVertex3fv(&frustumVertices[6].x);
		//	glVertex3fv(&frustumVertices[7].x);
		//	glVertex3fv(&frustumVertices[3].x);
		//	// top
		//	glNormal3fv(&frustumNormals[3].x);
		//	glVertex3fv(&frustumVertices[0].x);
		//	glVertex3fv(&frustumVertices[4].x);
		//	glVertex3fv(&frustumVertices[5].x);
		//	glVertex3fv(&frustumVertices[1].x);
		//	// front
		//	glNormal3fv(&frustumNormals[4].x);
		//	glVertex3fv(&frustumVertices[0].x);
		//	glVertex3fv(&frustumVertices[1].x);
		//	glVertex3fv(&frustumVertices[2].x);
		//	glVertex3fv(&frustumVertices[3].x);
		//	// back
		//	glNormal3fv(&frustumNormals[5].x);
		//	glVertex3fv(&frustumVertices[7].x);
		//	glVertex3fv(&frustumVertices[6].x);
		//	glVertex3fv(&frustumVertices[5].x);
		//	glVertex3fv(&frustumVertices[4].x);
		//	glEnd();
	}
}
