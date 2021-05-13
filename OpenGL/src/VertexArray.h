#pragma once
#include "VertexBufferLayout.h"
#include "VertexBuffer.h"
#include "GLErrorManager.h"

class VertexArray
{
private:
	unsigned int m_RendererID;

public:
	VertexArray();
	~VertexArray();
		

	void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);
	void Bind() const;
	void Unbind() const;

};