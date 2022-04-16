#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <VertexArray.hpp>
#include <IndexBuffer.hpp>
#include <Shader.hpp>
#include <Model.hpp>


class Renderer {


public:
void Draw(const VertexArray& va, const IndexBuffer& ib,const Shader& shader) const;
void Draw(const Model& model, const Shader& shader) const;

void Clear();

};

#endif
