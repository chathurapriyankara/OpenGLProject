#include <GL/glew.h>
#include <string>

class ShaderLoader {
    public:
        GLuint createProgram(const char* vertexShaderFileName, const char* fragmentShaderFileName);
    private:
    std::string readShader(const char *fileName);
    GLuint createShader(GLenum shaderType, std::string source, const char* shaderName);
};
