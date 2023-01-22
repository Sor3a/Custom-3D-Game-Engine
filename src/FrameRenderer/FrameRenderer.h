#pragma once
#include "../FrameBuffer/FrameBuffer.h"
#include "../Shader/Shader.h"
#include "../VertexAraay/VertexArray.h"
#include "../Texture/Texture.h"
#include "../FrameBuffer/RenderBufferObject.h"

class FrameRenderer
{
    float quadVertices[24] = {
        // positions // texCoords
        -1.0f, 1.0f, 0.0f, 1.0f,
        -1.0f, -1.0f, 0.0f, 0.0f,
        1.0f, -1.0f, 1.0f, 0.0f,
        -1.0f, 1.0f, 0.0f, 1.0f,
        1.0f, -1.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 1.0f, 1.0f
    };
	FrameBuffer fb;
	Shader s_Quade;
	VertexArray quadeArray;
	VertexBufferLayout quadeLayout;
	VertexBuffer quadeBuffer;
    Texture screenTexture;
    RenderBufferObject rbo;
public:
	FrameRenderer();
    inline void Bind() { fb.Bind(); }
    inline void UnBind() { fb.UnBind(); }
    void Draw();
};
