#ifndef VERTEXBUFFERLAYOUT_HPP
#define VERTEXBUFFERLAYOUT_HPP

#define GLEW_STATIC
#include <vector>
#include <GL/glew.h>

struct VertexBufferElement {
	unsigned int type;
	unsigned int count;
	unsigned char normalized;

	static unsigned int GetSizeOfType(unsigned int type){
		switch(type){
			case GL_FLOAT: return 4;
			case GL_UNSIGNED_INT: return 4;
		}

		return 0;
	}
};

class VertexBufferLayout {
private:
	std::vector<VertexBufferElement> mElements;
	unsigned int mStride;
public:
	VertexBufferLayout() : mStride(0) {};


	void Push(unsigned int type,unsigned int count){
		switch(type){
			case GL_FLOAT:
				mElements.push_back({GL_FLOAT,count,GL_FALSE});
				mStride += count * VertexBufferElement::GetSizeOfType(GL_FLOAT);
				return;
			case GL_UNSIGNED_INT:
				mElements.push_back({GL_UNSIGNED_INT,count,GL_FALSE});
				mStride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_INT);
				return;
		}
	};

	// template <> void Push <unsigned int> (unsigned int count){
	// 	mElements.push_back({GL_FLOAT,count,GL_FALSE});
	// 	mStride += VertexBufferElement::GetSizeOfType(GL_FLOAT);
	// }

	inline const std::vector<VertexBufferElement> GetElements() const {return mElements;}
	inline unsigned int GetStride() const { return mStride; }


};

#endif
