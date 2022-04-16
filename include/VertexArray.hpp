#ifndef VERTEXARRAY_HPP
#define VERTEXARRAY_HPP

#define GLEW_STATIC
#include <GL/glew.h>
#include <VertexBufferLayout.hpp>
#include <VertexBuffer.hpp>


class VertexArray {
private:
unsigned int mRendererID;
public:

VertexArray();
~VertexArray();

void Bind() const;
void Unbind() const;

void AddBuffer(const VertexBuffer& vb,const VertexBufferLayout& layout);

unsigned int getID() const {
	return mRendererID;
}


};



#endif
