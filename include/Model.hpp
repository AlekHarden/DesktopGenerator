#ifndef MODEL_HPP
#define MODEL_HPP

#include <glm/glm.hpp>
#include <VertexArray.hpp>
#include <IndexBuffer.hpp>




class Model {

private:

float* mData;
unsigned int* mIndices;
VertexBuffer mvb;
IndexBuffer mib;
VertexArray mva;
VertexBufferLayout mLayout;

unsigned int mNumPoints;
unsigned int mNumIndices;


public:


Model(unsigned int numPoints, unsigned int numIndices, glm::vec4 color);

~Model();

void setPoints(float* newPoints);
void setIndices(unsigned int* newIndices);

const VertexArray* getVertexArray() const;
const IndexBuffer* getIndexBuffer() const;









};


#endif
