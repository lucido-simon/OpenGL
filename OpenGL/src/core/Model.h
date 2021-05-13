#pragma once

#include "../VertexArray.h"
#include "../IndexBuffer.h"
#include <memory>

class Model
{
protected:
	std::shared_ptr<VertexArray> va;
	std::shared_ptr<IndexBuffer> ib;

public:
	Model(const VertexArray& va, const IndexBuffer& ib);

	void setVertexArray(const VertexArray& vertexArray);
	void setIndexBuffer(const IndexBuffer& indexBuffer);

	VertexArray& getVertexArray();
	IndexBuffer& getIndexBuffer();
};

