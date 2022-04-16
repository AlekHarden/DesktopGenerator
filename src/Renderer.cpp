#include <Renderer.hpp>
#include <iostream>

void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib,const Shader& shader) const {
	shader.Bind();
	va.Bind();
	ib.Bind();
	glDrawElements( GL_TRIANGLES,ib.GetCount(), GL_UNSIGNED_INT, nullptr);
}

void Renderer::Draw(const Model& model,const Shader& shader) const {
	shader.Bind();
	(*model.getVertexArray()).Bind();
	(*model.getIndexBuffer()).Bind();
	glDrawElements( GL_TRIANGLES,(*model.getIndexBuffer()).GetCount(), GL_UNSIGNED_INT, nullptr);
}

void Renderer::Clear() {
	glClear(GL_COLOR_BUFFER_BIT);
}
