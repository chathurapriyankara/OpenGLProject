#include "ShaderLoader.hpp"
#include <iostream>
#include <fstream>
#include <vector>

std::string ShaderLoader::readShader(const char *fileName) {
    std::string shaderCode;
    std::ifstream file(fileName,std::ios::in);
    if(!file.good()) {
        std::cout << "Can't read file" << fileName << std::endl;
        std::terminate();
    }
    file.seekg(0,std::ios::end);
    shaderCode.resize((unsigned int)file.tellg());
    file.seekg(0, std::ios::beg);
    file.read(&shaderCode[0], shaderCode.size());
    file.close();
    return shaderCode;
}

GLuint ShaderLoader::createShader(GLenum shaderType, std::string source, const char *shaderName) {
    int compileResult = 0;
    GLuint shader = glCreateShader(shaderType);
    const char *shaderCodePtr = source.c_str();
    const int shaderCodeSize = source.size();
    
    glShaderSource(shader, 1, &shaderCodePtr, &shaderCodeSize);
    glCompileShader(shader);
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compileResult);
    
    if(compileResult == GL_FALSE) {
        int infoLogLength = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);
        std::vector<char> shaderLog(infoLogLength);
        glGetShaderInfoLog(shader,infoLogLength, NULL, &shaderLog[0]);
        std::cout<<"Error compiling shader: " << shaderName << std::endl <<&shaderLog[0] << std::endl;
        return 0;
    }
    
    return shader;
}

GLuint ShaderLoader::createProgram(const char* vertexShaderFileName, const char* fragmentShaderFileName) {
    std::string vertexShaderCode = readShader(vertexShaderFileName);
    std::string fragmentShaderCode = readShader(fragmentShaderFileName);
    
    GLuint vertexShader = createShader(GL_VERTEX_SHADER, vertexShaderCode, "vertex shader");
    GLuint fragmentShader = createShader(GL_FRAGMENT_SHADER, fragmentShaderCode, "fragment shader");
    
    int linkResult = 0;
    GLuint program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    
    glLinkProgram(program);
    glGetProgramiv(program, GL_LINK_STATUS, &linkResult);
    
    if(linkResult == GL_FALSE) {
        int infoLogLength = 0;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLength);
        std::vector<char> programLog(infoLogLength);
        
        glGetProgramInfoLog(program, infoLogLength, NULL, &programLog[0]);
        std::cout<<"Shader Loader : LINK ERROR" << std::endl << &programLog[0] << std::endl;
        return 0;
    }
    return program;
}
