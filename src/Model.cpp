#include <Model.hpp>
#include <iostream>


Model::Model(unsigned int numPoints, unsigned int numIndices, glm::vec4 color) : mNumPoints(numPoints), mNumIndices(numIndices), mvb(nullptr,sizeof(float) * 6 * numPoints), mib(nullptr,numIndices){


	//Position Vec 2
	mLayout.Push(GL_FLOAT,2);
	//Color Vec 4
	mLayout.Push(GL_FLOAT,4);
	mva.AddBuffer(mvb,mLayout);

	mData = (float*)malloc(sizeof(float) * numPoints * 6);

	for(int i = 0; i < numPoints; i++) {
		mData[i * 6 + 2] = color[0];
		mData[i * 6 + 3] = color[1];
		mData[i * 6 + 4] = color[2];
		mData[i * 6 + 5] = color[3];
	}

	mva.Unbind();
	mvb.Unbind();
	mib.Unbind();

}


Model::~Model(){

}

void Model::setPoints(float* newPoints){
	for(int i = 0; i < mNumPoints; i++) {
		mData[i * 6] = newPoints[2*i];
		mData[i * 6 + 1] = newPoints[2*i+1];
	}
	mvb.SetPoints((void*)mData,mNumPoints*6*sizeof(float));
}

void Model::setIndices(unsigned int* newIndices){

	mIndices = newIndices;
	mib.SetIndices(mIndices,mNumIndices);
}

const VertexArray* Model::getVertexArray() const {
	return &mva;
}
const IndexBuffer* Model::getIndexBuffer() const {
	return &mib;
}
