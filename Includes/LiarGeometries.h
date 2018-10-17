#pragma once

#include <string>
#include <vector>
#include <glad/glad.h>

#include <LiarVertexBuffer.h>
#include <LiarRefrence.h>
#include <Define.h>

namespace Liar
{
	class LiarGeometry:public Liar::LiarReference
	{
	public:
		LiarGeometry();
		~LiarGeometry();

	protected:
		Liar::uint m_vertexArrayID;
		Liar::uint m_vertexbuffer;
		Liar::uint m_elementbuffer;

		Liar::LiarMeshRawData* m_rawData;
		int m_indiceSize;

	public:
		void Upload();
		void Render();
		void SetRawData(Liar::LiarMeshRawData*);
		Liar::LiarMeshRawData* GetRawData() { return m_rawData; };

		Liar::uint GetVertexArrayID() const { return m_vertexArrayID; };

		friend std::ostream& operator<<(std::ostream& os, const Liar::LiarGeometry& m);

	protected:
		virtual void ReleaseSourceData();
		virtual void UploadSub();

		int GetIndicesSize() const { return m_indiceSize; };
		virtual std::vector<int>* GetIndicesData() const;

		virtual size_t NumTriangles();
	};
}

