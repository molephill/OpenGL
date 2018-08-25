#pragma once

#include <Vectors.h>
#include <Matrices.h>

namespace Liar
{
	class Entity
	{
	public:
		Entity();
		~Entity();

	protected:

		// pos
		float m_x;
		float m_y;
		float m_z;

		// rotation
		float m_rotationX;
		float m_rotationY;
		float m_rotationZ;

		// scale
		float m_scaleX;
		float m_scaleY;
		float m_scaleZ;

		//
		bool m_transformChanged;

		// parent
		Entity* m_parent;

		// children
		Entity* m_childrenList;

		// model matrix
		Liar::Matrix4* m_transform;
		// invest matrix
		Liar::Matrix4* m_investtransform;

	public:
		Liar::Matrix4* GetTransfomr() { return m_transform; };

		float GetX() const { return m_x; };
		float GetY() const { return m_y; };
		float GetZ() const { return m_z; };

		float GetRotationX() const { return m_rotationX; };
		float GetRotationY() const { return m_rotationY; };
		float GetRotationZ() const { return m_rotationZ; };

		float GetScaleX() const { return m_scaleX; };
		float GetScaleY() const { return m_scaleY; };
		float GetScaleZ() const { return m_scaleZ; };

	public:
		void SetX(float);
		void SetY(float);
		void SetZ(float);
		void SetPosition(float, float, float);
		void SetPosition(const Liar::Vector3D&);

		void SetRotationX(float);
		void SetRotationY(float);
		void SetRotationZ(float);
        void SetRotation(float);
		void SetRotation(float, float, float);
		void SetRotation(const Liar::Vector3D&);

		void SetScaleX(float);
		void SetScaleY(float);
		void SetScaleZ(float);
        void SetScale(float);
		void SetScale(float, float, float);
		void SetScale(const Liar::Vector3D&);
        
        void AddX(float);
        void AddY(float);
        void AddZ(float);
        void AddPosition(float, float, float);
        void AddPosition(const Liar::Vector3D&);
        
        void AddRotationX(float);
        void AddRotationY(float);
        void AddRotationZ(float);
        void AddRotation(float, float, float);
        void AddRotation(const Liar::Vector3D&);
        
        void AddScaleX(float);
        void AddScaleY(float);
        void AddScaleZ(float);
        void AddScale(float, float, float);
        void AddScale(const Liar::Vector3D&);

	public:
		void CalcTransform(bool calcInvert = true);
		
		friend std::ostream& operator<<(std::ostream& os, const Liar::Entity&);

	private:
		virtual void DrawAxis(float);

	};
}

