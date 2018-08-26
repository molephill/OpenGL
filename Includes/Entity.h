#pragma once

#include <Vectors.h>
#include <Matrices.h>

#include "Shader.hpp"

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
        
        // name
        std::string m_name;

		//
		bool m_transformChanged;

		// parent
		Entity* m_parent;

		// children
		Entity* m_childrenNode;
        Liar::Entity* m_nextChildNode;

		// model matrix
		Liar::Matrix4* m_transform;
		// invest matrix
		Liar::Matrix4* m_investtransform;

	public:
		Liar::Matrix4* GetTransform() { return m_transform; };

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
        Liar::Entity* AddChild(Liar::Entity*);
        Liar::Entity* AddModel(const std::string&);
        
        Liar::Entity* RemoveChild(Liar::Entity*);
        Liar::Entity* RemoveChild(const std::string&);
        
        bool RemoveAndDisposeChild(Liar::Entity*);
        bool RemoveAndDisposeChild(const std::string&);
        
        Liar::Entity* GetChildNode() { return m_childrenNode; };
        
        virtual void Render(Liar::Shader&);
        virtual void RenderChildren(Liar::Shader&, bool);

	public:
        void SetName(std::string name) { m_name = name; };
		friend std::ostream& operator<<(std::ostream& os, const Liar::Entity&);

	protected:
        void CalcTransform(bool calcInvert = true);
		virtual void DrawAxis(float);

	};
}

