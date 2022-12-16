#pragma once

#include <GL/glew.h>
#include"../VertexAraay/VertexArray.h"
#include"../IndexBuffer/IndexBuffer.h"
#include"../Shader/Shader.h"
#define ASSERT(x) if(!(x)) __debugbreak();

#define GLCall(x) GLClearError();\
                    x;\
                    ASSERT(GLLogCall(#x,__FILE__,__LINE__))

void GLClearError();

bool GLLogCall(const char* function, const char* file, int line);;





class Renderer
{
    static Renderer* instance;
public:
    
    //Renderer(Renderer& other) = delete;
    void operator=(const Renderer&) = delete;
    static const Renderer* GetInstance();
    void Draw(const VertexArray& va, const IndexBuffer& ib) const;
    void Draw(const VertexArray& va) const;
    void Enable() const;
    void Disable() const;
    void Clear() const;
    void Blend() const;
    void StartRenderingImGui() const;
    void EndRendering(GLFWwindow*) const;
    void ShutDownRendering() const;
};














