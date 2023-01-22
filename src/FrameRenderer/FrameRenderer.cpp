
#include "FrameRenderer.h"

FrameRenderer::FrameRenderer():
	s_Quade("res/shaders/basic3.shader"),
	quadeBuffer(quadVertices,6*4* sizeof(float)),
	screenTexture(NULL)
{
	s_Quade.setUniform1i("screenTexture", 0);
	quadeLayout.push<float>(2);
	quadeLayout.push<float>(2);
	quadeArray.AddBuffer(quadeBuffer, quadeLayout);
	
	rbo.DepthStencilRBO();
	fb.AttachTexture(screenTexture.GetID());
	fb.AttachRBO_Depth_Stencil(rbo.getID());
	fb.CheckIfComplete();

	fb.UnBind();
}
void FrameRenderer::Draw()
{
	glDisable(GL_DEPTH_TEST);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	//Renderer::GetInstance()->Clear();
	s_Quade.Bind();

	screenTexture.Bind();
	Renderer::GetInstance()->Draw(quadeArray);
}