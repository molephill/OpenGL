#pragma once

#include <Vectors.h>
#include <Matrices.h>

#include <LiarShader.h>

namespace Liar
{
    class LiarContainerObject;
    
    class LiarDisplayObject
    {
    public:
        LiarDisplayObject();
        virtual ~LiarDisplayObject();
        
    protected:
        Liar::Vector3D* m_position;
        Liar::Vector3D* m_rotation;
        Liar::Vector3D* m_scale;
        std::string m_name;
        
        bool m_transformChanged;
        // model matrix
        Liar::Matrix4* m_transform;
        // invest matrix
        Liar::Matrix4* m_investtransform;
        
        // parent
        Liar::LiarContainerObject* m_parent;
        // children
        Liar::LiarDisplayObject* m_childrenNode;
        Liar::LiarDisplayObject* m_nextChildNode;
        
    public:
        Liar::Matrix4* GetTransform() const { return m_transform; };
        
        Liar::LiarContainerObject* GetParent() const { return m_parent; };
        void SetParent(Liar::LiarContainerObject* v) { m_parent = v; };
        
        std::string& GetName() {return m_name;};
        void SetName(const std::string& name) { m_name = name; };
        
        Liar::LiarDisplayObject* GetChildNode() const { return m_childrenNode; };
        void SetChildNode(Liar::LiarDisplayObject* v) { m_childrenNode = v; };
        
        Liar::LiarDisplayObject* GetNextChildNode() const { return m_nextChildNode; };
        void SetNextChildNode(Liar::LiarDisplayObject* v) { m_nextChildNode = v; };
        
        float GetX() const { return m_position->x; };
        float GetY() const { return m_position->y; };
        float GetZ() const { return m_position->z; };
        
        float GetRotationX() const { return m_rotation->x; };
        float GetRotationY() const { return m_rotation->y; };
        float GetRotationZ() const { return m_rotation->z; };
        
        float GetScaleX() const { return m_scale->x; };
        float GetScaleY() const { return m_scale->y; };
        float GetScaleZ() const { return m_scale->z; };
        
    protected:
        virtual bool CalcTransform(bool combineParent = false, bool calcInvert = true);
        
    public:
        virtual void SetX(float);
        virtual void SetY(float);
        virtual void SetZ(float);
        virtual void SetPosition(float, float, float);
        virtual void SetPosition(const Liar::Vector3D&);
        
        virtual void SetRotationX(float);
        virtual void SetRotationY(float);
        virtual void SetRotationZ(float);
        virtual void SetRotation(float);
        virtual void SetRotation(float, float, float);
        virtual void SetRotation(const Liar::Vector3D&);
        
        virtual void SetScaleX(float);
        virtual void SetScaleY(float);
        virtual void SetScaleZ(float);
        virtual void SetScale(float);
        virtual void SetScale(float, float, float);
        virtual void SetScale(const Liar::Vector3D&);
        
        virtual void AddX(float);
        virtual void AddY(float);
        virtual void AddZ(float);
        virtual void AddPosition(float, float, float);
        virtual void AddPosition(const Liar::Vector3D&);
        
        virtual void AddRotationX(float);
        virtual void AddRotationY(float);
        virtual void AddRotationZ(float);
        virtual void AddRotation(float, float, float);
        virtual void AddRotation(const Liar::Vector3D&);
        
        virtual void AddScaleX(float);
        virtual void AddScaleY(float);
        virtual void AddScaleZ(float);
        virtual void AddScale(float, float, float);
        virtual void AddScale(const Liar::Vector3D&);
        
        virtual bool Render(Liar::LiarShaderProgram&, bool combineParent = false);
    };
    
    // ====================== container =========================== //
    class LiarContainerObject:public LiarDisplayObject
	{
	public:
		LiarContainerObject();
		~LiarContainerObject();
        
    public:
        virtual Liar::LiarDisplayObject* AddChild(Liar::LiarDisplayObject*);
        
        virtual Liar::LiarDisplayObject* RemoveChild(Liar::LiarDisplayObject*);
        virtual Liar::LiarDisplayObject* RemoveChild(const std::string&);
        
        virtual bool RemoveAndDisposeChild(Liar::LiarDisplayObject*);
        virtual bool RemoveAndDisposeChild(const std::string&);
        
        Liar::LiarDisplayObject* GetChildNode() { return m_childrenNode; };
        
		virtual bool Render(Liar::LiarShaderProgram&, bool combineParent = false);

	public:
		friend std::ostream& operator<<(std::ostream& os, const Liar::LiarContainerObject&);

	protected:
		virtual void RenderChildren(Liar::LiarShaderProgram&, bool combineParent = false);
		virtual void DrawAxis(float size = 2.5f);

	};
}

