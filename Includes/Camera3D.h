#pragma once

#include "Entity.h"

#include <LiarVertexBuffer.h>
#include "Define.h"

namespace Liar
{
	class Camera3D
	{
	public:
		Camera3D(float nearCliping = 1.0f, float farClipping = 1000.0f);
		~Camera3D();

	private:
		bool m_isPerspective;

		float m_nearClipping;
		float m_farClipping;
		float m_fov;
		unsigned int m_viewWidth;
		unsigned int m_viewHeight;

        Liar::Matrix4* m_viewMatrix;

		float m_x;
		float m_y;
		float m_z;
		bool m_transformChanged;

		float m_targetX;
		float m_targetY;
		float m_targetZ;

		Liar::Matrix4* m_projection;

	public:
		// =================================================== 
		void SetViewSize(unsigned int, unsigned int, unsigned int, unsigned int);
		void LookAt(float, float, float);
		void ChangeMode(bool);

		void AddX(float);
		void AddY(float);
		void AddZ(float);
		void AddPosition(float, float, float);
		void AddPosition(const Liar::Vector3D&);
		void SetPosition(float, float, float);
		void SetPosition(const Liar::Vector3D&);
		// ===================================================

		void Render();

		Liar::Matrix4* GetProjMatrix() const { return m_projection; };
		Liar::Matrix4* GetViewMatrix() const { return m_viewMatrix;}

	private:
		void SetFrustum(float, float, float, float);
		void SetFrustum(float, float, float, float, float, float);

		void SetOrthoFrustum(float, float, float, float, float, float);

		void DrawFrustum(float l, float r, float b, float t, float n, float f);
		void ComputeFrustumVertices(float l, float r, float b, float t, float n, float f);
	};
}

