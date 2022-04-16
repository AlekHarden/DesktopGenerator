#include <GL/glew.h>

#include <iostream>

#include <IndexBuffer.hpp>



IndexBuffer::IndexBuffer(){

}
IndexBuffer::IndexBuffer(const IndexBuffer& i){
	mRendererID = i.mRendererID;
	std::cout << "mRendererID (copy): "<< mRendererID<< std::endl;

}

IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count) : mCount(count) {
	glGenBuffers(1, &mRendererID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mRendererID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_DYNAMIC_DRAW);
}

IndexBuffer::~IndexBuffer(){
	glDeleteBuffers(1,&mRendererID);
}

void IndexBuffer::Bind() const {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,mRendererID);
}

void IndexBuffer::Unbind() const {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
}

void IndexBuffer::SetIndices(const unsigned int *data, unsigned int count){
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mRendererID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_DYNAMIC_DRAW);
	mCount = count;
	// // ------- Print Data -------
	// std::cout << "Indicies: "<< std::endl;
	//
	// for(int i = 0; i < count/3; i++) {
	// 	std::cout << data[i * 3] << ", " << data[i * 3 + 1] << ", " << data[i * 3 + 2] << std::endl;
	// }
	// std::cout << std::endl;
}
