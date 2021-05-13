#include "Model.h"

Model::Model(const VertexArray& va, const IndexBuffer& ib)
{
	this->va = std::make_shared<VertexArray>(va);
	this->ib = std::make_shared<IndexBuffer>(ib);
}

void Model::setVertexArray(const VertexArray& vertexArray)
{
	*va = vertexArray;
}

void Model::setIndexBuffer(const IndexBuffer& indexBuffer)
{
	*ib = indexBuffer;
}

VertexArray& Model::getVertexArray()
{
	return *va;
}

IndexBuffer& Model::getIndexBuffer()
{
	return *ib;
}
