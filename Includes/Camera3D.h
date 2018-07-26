#pragma once

#include "Entity.h"

#include <LiarVertexBuffer.h>
#include "Define.h"

namespace Liar
{
	class Camera3D:public Entity
	{
	public:
		Camera3D(float nearCliping = 0.1f, float farClipping = 100.0f);
		~Camera3D();

	private:
		bool m_isPerspective;

		float m_nearClipping;
		float m_farClipping;
		float m_fov;
		unsigned int m_viewWidth;
		unsigned int m_viewHeight;

		float m_targetX;
		float m_targetY;
		float m_targetZ;

		Liar::Matrix4* m_projection;

	public:
		// ===================================================
		void SetViewSize(unsigned int, unsigned int, unsigned int, unsigned int);
		void LookAt(float, float, float);
		void ChangeMode(bool);
		// ===================================================

		void Render();

		Liar::Matrix4* GetMatrix() const { return m_projection; };

	private:
		void CalcPerspective();

		void SetFrustum(float, float, float, float);
		void SetFrustum(float, float, float, float, float, float);

		void SetOrthoFrustum(float, float, float, float, float, float);

		void DrawFrustum(float l, float r, float b, float t, float n, float f);
		void ComputeFrustumVertices(float l, float r, float b, float t, float n, float f);
	};
}

