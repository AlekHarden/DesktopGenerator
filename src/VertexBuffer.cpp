#include <GL/glew.h>

#include <stdlib.h>
#include <iostream>

#include <VertexBuffer.hpp>

VertexBuffer::VertexBuffer(){

}

VertexBuffer::VertexBuffer(void* data, unsigned int size){
	glGenBuffers(1, &mRendererID);
	glBindBuffer(GL_ARRAY_BUFFER,mRendererID);
	glBufferData(GL_ARRAY_BUFFER, size,(const void*) data, GL_DYNAMIC_DRAW);

}

VertexBuffer::VertexBuffer(VertexBuffer& vb){
	mRendererID = vb.mRendererID;
}


VertexBuffer::~VertexBuffer(){
	glDeleteBuffers(1,&mRendererID);
}

void VertexBuffer::Bind() const {
	glBindBuffer(GL_ARRAY_BUFFER,mRendererID);
}

void VertexBuffer::Unbind() const {
	glBindBuffer(GL_ARRAY_BUFFER,0);
}

void VertexBuffer::SetPoints(void* data, unsigned int size){
	glBindBuffer(GL_ARRAY_BUFFER,mRendererID);
	glBufferData(GL_ARRAY_BUFFER, size,(const void*) data, GL_DYNAMIC_DRAW);
	// //-------Print Data-------
	// std::cout << "Points: " << std::endl;
	// float* trash = static_cast <float*> (data);
	// for(int i = 0; i < size / (6 * sizeof(float)); i++) {
	// 	std::cout <<"[" << i << "] "<< trash[i * 6] << ", " << trash[i * 6 + 1] << " Color: " << trash[i * 6+2] << ", " << trash[i * 6+3] << ", "<< trash[i * 6+4] << ", "<< trash[i * 6+5] <<  std::endl;
	// }
}
void VertexBuffer::SetPoints(void* data, unsigned int offset, unsigned int size){
	// offset & size both in terms of bytes

	glBindBuffer(GL_ARRAY_BUFFER,mRendererID);
	std::cout << "offset: " << offset << std::endl;
	std::cout << "size: " << size <<  std::endl;

	glBufferSubData(GL_ARRAY_BUFFER, offset, size, (const void*)data);

}
