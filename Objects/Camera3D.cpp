#include "Camera3D.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Liar
{
	Camera3D::Camera3D(float nearClipping, float farClipping):Liar::Entity(),
		m_nearClipping(nearClipping), m_farClipping(farClipping),
		m_targetX(0.0f),m_targetY(0.0f),m_targetZ(0.0f),
		m_fov(60.0f),m_viewWidth(WINDOW_W),m_viewHeight(WINDOW_H),
		m_isPerspective(true),
		m_projection(new Liar::Matrix4())
	{
	}


	Camera3D::~Camera3D()
	{
		
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
			m_transform->Identity();
			m_transform->Translate(m_x, m_y, m_z);
			m_transform->Rotate(m_rotationX, m_rotationY, m_rotationZ);
            m_transform->LookAt(m_targetX, m_targetY, m_targetZ);

			std::cout << (*m_transform) << std::endl;

			// projection
			SetFrustum(m_fov, static_cast<float>(m_viewWidth / m_viewHeight), m_nearClipping, m_farClipping);

			std::cout << (*m_projection) << std::endl;

			// projection*viewMatrix
			(*m_projection) *= (*m_transform);

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
