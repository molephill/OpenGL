#pragma once

#include <string>
#include <vector>
#include <glad/glad.h>

#include <LiarVertexBuffer.h>
#include <LiarRefrence.h>

namespace Liar
{
	class LiarGeometry:public Liar::LiarReference
	{
	public:
		LiarGeometry();
		~LiarGeometry();

	protected:
		unsigned int m_vertexArrayID;
		unsigned int m_vertexbuffer;
		unsigned int m_elementbuffer;

		Liar::LiarMeshRawData* m_rawData;
		int m_indiceSize;

	public:
		void Upload();
		void Render();
		void SetRawData(Liar::LiarMeshRawData*);
		friend std::ostream& operator<<(std::ostream& os, const Liar::LiarGeometry& m);

	protected:
		virtual void ReleaseSourceData();
		virtual void UploadSub();

		virtual int GetIndicesSize() const;
		virtual std::vector<int>* GetIndicesData() const;

		virtual size_t NumTriangles();
	};
}

