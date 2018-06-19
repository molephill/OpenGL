
#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "ViewPort.h"
#include "LiarObject.hpp"

namespace Liar
{
    
    class Camera:
        public LiarObject
	{
	public:
		Camera();
        Camera(float, float, float);
		~Camera();

	private:
		ViewPort* m_viewPort;

		glm::vec3 m_front;
        glm::vec3 m_right;
		glm::vec3 m_worldUp;
        
		// 矩阵
		glm::mat4 m_matrix;
        
        // 限定
        bool m_constrainPitch;

	public:
        // ===================================================
        virtual void SetRotation(const glm::vec3&);
        virtual void SetRotation(float, float, float);
        // ===================================================
        virtual void AddRotation(const glm::vec3&);
        virtual void AddRotation(float, float, float);
		// ===================================================
		void SetFront(const glm::vec3&);
		void SetFront(float, float, float);
		// ===================================================
		void SetWorldUp(const glm::vec3&);
		void SetWorldUp(float, float, float);
		// ===================================================
		void SetSize(unsigned int, unsigned int);
		void SetViewParams(float n, float f, float fov = CAMERA_FOV, CAMERA_TYPE type = CAMERA_TYPE::PERPECTIVE);
        // ===================================================
        void SetFov(float);
        void AddFov(float);
        void SetType(CAMERA_TYPE);
        // ===================================================
        void MoveForward(MOVE_DIRECTION);

	public:
		// ===================================================
		ViewPort* GetViewPort() { return m_viewPort; };
		glm::mat4& GetPerspective();
		glm::mat4& GetViewMatrix();
        bool GetConstrainPitch() { return m_constrainPitch; };
        void SetConstrainPitch(bool v) { m_constrainPitch = v; };

        void Render();
	};
}

#endif /* CAMERA_HPP */
