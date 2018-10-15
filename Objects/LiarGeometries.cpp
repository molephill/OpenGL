#include "LiarGeometries.h"

namespace Liar
{
	// =============================== Geometory ===============================
	LiarGeometry::LiarGeometry():
		Liar::LiarReference(),
		m_vertexArrayID(0), m_elementbuffer(0), m_vertexbuffer(0),
		m_indiceSize(0),
		m_rawData(nullptr)
	{
	}

	LiarGeometry::~LiarGeometry()
	{
		if (m_vertexArrayID > 0) glDeleteBuffers(1, &m_vertexArrayID);
		if (m_vertexbuffer > 0) glDeleteBuffers(1, &m_vertexbuffer);
		if (m_elementbuffer > 0) glDeleteBuffers(1, &m_elementbuffer);
	}

	std::ostream& operator<<(std::ostream& os, const Liar::LiarGeometry& m)
	{
		return os;
	}

	void LiarGeometry::SetRawData(Liar::LiarMeshRawData* data)
	{
		m_rawData = data;
		if (m_rawData)
		{
			m_indiceSize = m_rawData->GetIndices()->size();
			Upload();
		}
	}

	void LiarGeometry::Upload()
	{
		glGenVertexArrays(1, &m_vertexArrayID);
		glBindVertexArray(m_vertexArrayID);

		glGenBuffers(1, &m_vertexbuffer);
		glBindBuffer(GL_ARRAY_BUFFER, m_vertexbuffer);

		UploadSub();

		int indiceSize1 = GetIndicesSize() * sizeof(unsigned int);
		glGenBuffers(1, &m_elementbuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_elementbuffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indiceSize1, GetIndicesData()->data(), GL_STATIC_DRAW);

		ReleaseSourceData();
	}

	int LiarGeometry::GetIndicesSize() const
	{
		return m_indiceSize;
	}

	std::vector<int>* LiarGeometry::GetIndicesData() const
	{
		return m_rawData->GetIndices();
	}

	size_t LiarGeometry::NumTriangles()
	{
		return m_rawData->GetFaces()->size();
	}

	void LiarGeometry::Render()
	{
		// draw mesh
		glBindVertexArray(m_vertexArrayID);
		glDrawElements(GL_TRIANGLES, m_indiceSize, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}

	void LiarGeometry::UploadSub()
	{
		int positionSize = Liar::LiarVertexBuffer::GetPositionSize();
		int normalSize = Liar::LiarVertexBuffer::GetNormalSize();
		int colorSize = Liar::LiarVertexBuffer::GetColorSize();
		int uvSize = Liar::LiarVertexBuffer::GetUVSize();

		int positionOffSize = Liar::LiarVertexBuffer::GetPositionOffSize();
		int normalOffSize = Liar::LiarVertexBuffer::GetNormalOffSize();
		int colorOffSize = Liar::LiarVertexBuffer::GetColorOffSize();
		int uvOffSize = Liar::LiarVertexBuffer::GetUVOffSize();

		bool normal = m_rawData->HasNorm();
		bool color = m_rawData->HasColor();
		bool uv = m_rawData->HasTexCoord();

		int oneSize = positionSize;
		if (normal)
		{
			oneSize += normalSize;
		}
		else
		{
			normalSize = 0;
		}
		normalOffSize = positionOffSize + normalSize;

		if (uv)
		{
			oneSize += uvSize;
		}
		else
		{
			uvSize = 0;
		}
		uvOffSize = normalOffSize + uvSize;

		if (color)
		{
			oneSize += colorSize;
		}
		else
		{
			colorSize = 0;
		}
		colorOffSize = uvOffSize + normalSize;

		size_t bufferSize = NumTriangles();
		size_t totalSize = bufferSize * oneSize;

		glBufferData(GL_ARRAY_BUFFER, totalSize, nullptr, GL_STATIC_DRAW);
		for (size_t i = 0; i < bufferSize; ++i)
		{
			Liar::LiarFaceDefine* tmp = m_rawData->GetFaces()->at(i);
			size_t start = i * oneSize;
			glBufferSubData(GL_ARRAY_BUFFER, start + positionOffSize, positionSize, m_rawData->GetPos(tmp->positionIndex));
			if (normal) glBufferSubData(GL_ARRAY_BUFFER, start + normalOffSize, normalSize, m_rawData->GetNorm(tmp->normalIndex));
			if (uv) glBufferSubData(GL_ARRAY_BUFFER, start + uvOffSize, uvSize, m_rawData->GetTexCoord(tmp->texCoordIndex));
			if (color) glBufferSubData(GL_ARRAY_BUFFER, start + colorOffSize, colorSize, m_rawData->GetColor(tmp->colorIndex));
		}

		unsigned int curId = 0;
		// position attribute
		glVertexAttribPointer(curId, 3, GL_FLOAT, GL_FALSE, oneSize, (void*)positionOffSize);
		glEnableVertexAttribArray(curId);
		++curId;

		// normal attribute
		if (normal)
		{
			glVertexAttribPointer(curId, 3, GL_FLOAT, GL_FALSE, oneSize, (void*)normalOffSize);
			glEnableVertexAttribArray(curId);
			++curId;
		}

		// texture coord attribute
		if (uv)
		{
			glVertexAttribPointer(curId, 3, GL_FLOAT, GL_FALSE, oneSize, (void*)uvOffSize);
			glEnableVertexAttribArray(curId);
			++curId;
		}

		// color attribute
		if (color)
		{
			glVertexAttribPointer(curId, 3, GL_FLOAT, GL_FALSE, oneSize, (void*)colorOffSize);
			glEnableVertexAttribArray(curId);
		}

		// skin anim info
		bool skin = m_rawData->HasSkin();
	}

	void LiarGeometry::ReleaseSourceData()
	{
		
	}

	// =============================== Geometory ===============================
}
