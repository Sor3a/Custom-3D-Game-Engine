#include"Renderer.h"
#include<iostream>
#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_glfw.h"
#include "ImGui/imgui_impl_opengl3.h"
void GLClearError()
{
	while (glGetError() != GL_NO_ERROR);
}


bool GLLogCall(const char* function, const char* file, int line)
{
	while (auto error = glGetError())
	{
		std::cout << "[OpenGL Error] (" << error << "): " << function << " " << line << ":" << file << std::endl;
		return false;
	}
	return true;

}


Renderer* Renderer::instance = nullptr;

const Renderer* Renderer::GetInstance()
{
	if (instance == nullptr)
		instance = new Renderer();

	return instance;

}
void Renderer::Clear() const
{
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

}
void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib) const
{
	//shader.Bind();
	//s.setUniform4f("vertexColor", 0.8, 0.1, 0.5, 0.6);
	//std::cout << "done" << std::endl;
	va.Bind();

	ib.Bind();
	//std::cout << ib.getCount() << std::endl;
	GLCall(glDrawElements(GL_TRIANGLES, ib.getCount(), GL_UNSIGNED_INT,nullptr));
}
void Renderer::Draw(const VertexArray& va) const
{
	//shader.Bind();
	//s.setUniform4f("vertexColor", 0.8, 0.1, 0.5, 0.6);
	va.Bind();
	GLCall(glDrawArrays(GL_TRIANGLES, 0, va.getNumberOfVertexs()));
	//std::cout << va.getNumberOfVertexs() << std::endl;
}
void Renderer::Blend() const
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Renderer::Enable() const
{
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
}

void Renderer::Disable() const
{
	glDisable(GL_CULL_FACE);
	glDisable(GL_DEPTH_TEST);
}

void Renderer::StartRenderingImGui() const
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

void Renderer::EndRendering(GLFWwindow* window) const
{
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	/* Swap front and back buffers */
	glfwSwapBuffers(window);

	/* Poll for and process events */
	glfwPollEvents();
}
void Renderer::ShutDownRendering() const
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
	glfwTerminate();
}