#ifndef SHADER_HPP
#define SHADER_HPP
#include <string>
#include <glm/glm.hpp>


class Shader {
private:
std::string ReadShaderFile(std::string filepath);
unsigned int mRendererID;
unsigned int GetUniformLocation(const std::string& name);
unsigned int CreateShader(const std::string vertexShader, const std::string fragmentShader);
unsigned int CompileShader(unsigned int type, const std::string& source);
public:
Shader(const std::string& vertexShader,const std::string& fragmentShader);
~Shader();

void Bind() const;
void Unbind() const;

void SetUniform4f(const std::string name, float v0, float v1, float v2, float v3);
void SetUniformMat4f(const std::string name, const glm::mat4& matrix);




};

#endif
