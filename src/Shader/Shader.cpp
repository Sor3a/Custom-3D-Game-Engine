#include "Shader.h"
#include <fstream>
#include<string>
#include<sstream>
#include "../Renderer/Renderer.h"
std::tuple<std::string, std::string,std::string> Shader::ParseShader(const std::string& filePath)
{
    enum class ShaderType
    {
        None = -1, Vertex = 0, Fragment = 1,Geometry = 2
    };
    std::ifstream stream(filePath);
    std::stringstream ss[3];
    std::string line;
    ShaderType type = ShaderType::None;
    while (getline(stream, line))
    {
        if (line.find("#shader") != std::string::npos)
        {
            if (line.find("vertex") != std::string::npos)
            {
                type = ShaderType::Vertex;
            }
            else if (line.find("fragment") != std::string::npos)
            {
                type = ShaderType::Fragment;
            }
            else if (line.find("geometry") != std::string::npos)
                type = ShaderType::Geometry;
        }
        else
        {
            ss[(int)type] << line << "\n";
        }
    }
    return { ss[0].str(),ss[1].str(),ss[2].str() };
}
unsigned int Shader::CompileShader(unsigned int type, const std::string& source)
{
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (!result)
    {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)alloca(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);
       
        std::cout << "Failed to Compile " << (type == GL_VERTEX_SHADER ? "Vertex shader" : (type == GL_FRAGMENT_SHADER)? "Fragment Shader":"Geometry Shader") << std::endl;
        std::cout << message << std::endl;
        return 0;
    }
    return id;
}
unsigned int Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader,const std::string& geometryShader)
{
    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);
    unsigned int gs = CompileShader(GL_GEOMETRY_SHADER, geometryShader);


    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glAttachShader(program, gs);

    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}
unsigned int Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
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
}
Shader::Shader(const std::string& fileName):filePath(fileName),m_RenderID(0)
{
    auto [vertexShader, fragmentShader,geometryShader] = ParseShader(filePath);
    //std::cout << vertexShader << std::endl;
    if (geometryShader.size() > 1)
    {
        m_RenderID = CreateShader(vertexShader, fragmentShader, geometryShader);
        return;
    }
    m_RenderID = CreateShader(vertexShader, fragmentShader);

}

Shader::~Shader()
{
    GLCall(glDeleteProgram(m_RenderID));
}

void Shader::Bind() const
{
    glUseProgram(m_RenderID);
}
void Shader::UnBind() const
{
    GLCall(glUseProgram(0));
}
void Shader::setUniformMat4f(const std::string& Name, const glm::mat4& matrix)
{
    GLCall(Bind());
    
    GLCall(glUniformMatrix4fv(getUniformLocation(Name),1,GL_FALSE, &matrix[0][0]));
}
void Shader::setUniformMat3f(const std::string& Name, const glm::mat3& matrix, unsigned int Transpose)
{
    GLCall(Bind());
    GLCall(glUniformMatrix3fv(getUniformLocation(Name), 1, Transpose, &matrix[0][0]));
}
void Shader::setUniformVec3f(const std::string& Name, const glm::vec3& v)
{
    GLCall(Bind());
    GLCall(glUniform3f(getUniformLocation(Name),v.x,v.y,v.z));
}
void Shader::setUniformVec4f(const std::string& Name, const glm::vec4& v)
{
    GLCall(Bind());
    GLCall(glUniform4f(getUniformLocation(Name), v.x, v.y, v.z, v.w));
}
void Shader::setUniform1i(const std::string& Name, int v1)
{
    GLCall(Bind());
    GLCall(glUniform1i(getUniformLocation(Name), v1));
}
void Shader::setUniform1f(const std::string& Name, float v1)
{
    GLCall(Bind());
    GLCall(glUniform1f(getUniformLocation(Name), v1));
}
void Shader::setUniform4f(const std::string& Name, float v1, float v2, float v3, float v4)
{
    GLCall(Bind());
    GLCall(glUniform4f(getUniformLocation(Name), v1, v2, v3, v4));
}
int Shader::getUniformLocation(const std::string& Name)
{
    if (auto location_= UniformLocations.find(Name); location_ != UniformLocations.end())
    {
        return location_->second;
    }
    int loc = glGetUniformLocation(m_RenderID, Name.c_str());
    if (loc == -1)
        std::cout << "Warning no Uniform with this '" + Name + "' name" << std::endl;
    else
        UniformLocations.insert(std::make_pair(Name, loc));
    return loc;
}