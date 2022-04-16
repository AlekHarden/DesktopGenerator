#ifndef INDEXBUFFER_HPP
#define INDEXBUFFER_HPP
class IndexBuffer {
private:
unsigned int mCount;
unsigned int mRendererID;

public:
IndexBuffer();
IndexBuffer(const IndexBuffer& i);
IndexBuffer(const unsigned int *data, unsigned int count);
void SetIndices(const unsigned int *data, unsigned int count);

~IndexBuffer();

void Bind() const;
void Unbind() const;

unsigned int getID() const {
	return mRendererID;
}
unsigned int GetCount() const {
	return mCount;
}
};
#endif
