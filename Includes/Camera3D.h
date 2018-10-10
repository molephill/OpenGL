#pragma once

#include "LiarObjects.h"

#include <LiarVertexBuffer.h>
#include "Define.h"

namespace Liar
{
	class Camera3DCtrl
	{
	public:
		Camera3DCtrl();
		~Camera3DCtrl();

	private:
		float m_angleX;
		float m_angleY;
		float m_distanceZ;
		bool m_transformChanged;
		Liar::Matrix4* m_transform;

	public:
		Liar::Matrix4* GetTransform();

		void AddRotation(float, float);
		void AddZoom(float);
	};

	class Camera3D:public LiarDisplayObject
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

		Liar::Matrix4* m_projection;

		Liar::Camera3DCtrl* m_controller;

	public:
		// =================================================== 
		void SetViewSize(unsigned int, unsigned int, unsigned int, unsigned int);
		void ChangeMode(bool);

		void RotateCamera(float, float);
		void ZoomCamera(float);

		// ===================================================

		void Render();

		Liar::Matrix4* GetProjMatrix() const { return m_projection; };
		Liar::Matrix4* GetExtentionMatrix() const { return m_controller->GetTransform(); };

	private:
		void SetFrustum(float, float, float, float);
		void SetFrustum(float, float, float, float, float, float);

		void SetOrthoFrustum(float, float, float, float, float, float);

		void DrawFrustum(float l, float r, float b, float t, float n, float f);
		void ComputeFrustumVertices(float l, float r, float b, float t, float n, float f);
	};
}

