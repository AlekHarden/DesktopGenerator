//Library Includes
#include <GL/glew.h>

//Standard Includes
#include <string>
#include <iostream>

//Custom Includes
#include <Shader.hpp>


Shader::Shader(const std::string& vertexShaderFilePath,const std::string& fragmentShaderFilePath) : mRendererID(0){
	//Create Shader
	std::string vertexShader;
	std::string fragmentShader;
	// Error Handling for opening shader files
	try {
		vertexShader = ReadShaderFile(vertexShaderFilePath);
		fragmentShader = ReadShaderFile(fragmentShaderFilePath);
	} catch (std::string e) {
		std::cout << e;
	}
	mRendererID = CreateShader(vertexShader, fragmentShader);
}

Shader::~Shader(){

}

unsigned int Shader::GetUniformLocation(const std::string& name){
	int location = glGetUniformLocation(mRendererID, name.c_str());
	if( location == -1) {
		std::cout << "Warning: uniform '" << name << "' doesn't exist!" << std::endl;
	}
	return location;

}

void Shader::SetUniform4f(const std::string name, float v0, float v1, float v2, float v3){
	glUniform4f(GetUniformLocation(name),v0,v1,v2,v3);
}

void Shader::SetUniformMat4f(const std::string name, const glm::mat4& matrix){
	glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &matrix[0][0]);
}





void Shader::Bind() const {
	glUseProgram(mRendererID);
}

void Shader::Unbind() const {
	glUseProgram(0);

}

unsigned int Shader::CreateShader(const std::string vertexShader, const std::string fragmentShader) {
	unsigned int program = glCreateProgram();
	unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

	glAttachShader(program, vs);
	glAttachShader(program, fs);

	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vs);
	glDeleteShader(fs);

	return program;
};


unsigned int Shader::CompileShader(unsigned int type, const std::string& source) {
	unsigned int id = glCreateShader(type);
	const char *src = source.c_str();

	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);

	if (result == GL_FALSE) {
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char *message = new char[length];
		glGetShaderInfoLog(id, length, &length, message);
		std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader!" << std::endl;
		std::cout << message << std::endl;
		delete message;
		glDeleteShader(id);
		return 0;
	}

	return id;
}


std::string Shader::ReadShaderFile(std::string filepath) {

	char buffer[100];
	char cbullshit;
	std::string shaderSource;
	FILE *file = fopen(filepath.c_str(), "r");

	// Error checking
	if (file == NULL) throw("ERROR: File \"" + filepath + "\" does not exist\n");

	//fgetc eats first character so you have to set c bullshit and append it later
	while ((cbullshit = fgetc(file)) != EOF) {
		fgets(buffer, 100, file);
		shaderSource.push_back(cbullshit);
		shaderSource.append(buffer);
	}
	//std::cout << "SOURCE: \n" << shaderSource << std::endl;

	return shaderSource;
}
