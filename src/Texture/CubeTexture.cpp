#include "CubeTexture.h"
#include"../vendor/stb_Image/stb_Image.h"


void CubeTexture::Texture_Filtre(unsigned int FilterMood)
{
	GLCall(glBindTexture(GL_TEXTURE_CUBE_MAP, RendererID));
	GLCall(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, FilterMood));
	GLCall(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, FilterMood));
}
void CubeTexture::Clamping_Texture(unsigned int ClampValue, float* borderColor)
{
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, ClampValue);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, ClampValue);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, ClampValue);
}
CubeTexture::CubeTexture(const std::vector<std::string>& faces)
{
	glGenTextures(1, &RendererID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, RendererID);

	int width, height, nrChannels;
	for (unsigned int i = 0; i < faces.size(); i++)
	{
		unsigned char* data = stbi_load(faces[i].c_str(), &width, &height,&nrChannels, 0);
		stbi_set_flip_vertically_on_load(false);
		if (data)
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB,
				width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			stbi_image_free(data);
		}
		else
		{
			std::cout << "Cubemap failed to load at path: " << faces[i]
				<< std::endl;
			stbi_image_free(data);
		}
	}
	//Texture_Filtre()
	Texture_Filtre(GL_LINEAR);
	Clamping_Texture(GL_CLAMP_TO_EDGE,nullptr);
}
CubeTexture::CubeTexture(unsigned int width, unsigned int height)
{
	glGenTextures(1, &RendererID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, RendererID);
	for (unsigned int i = 0; i < 6; ++i)
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_DEPTH_COMPONENT,
			width, height, 0, GL_DEPTH_COMPONENT,
			GL_FLOAT, NULL);

	Texture_Filtre(GL_NEAREST);
	Clamping_Texture(GL_CLAMP_TO_EDGE, nullptr);
	UnBind();
}
void CubeTexture::Bind(unsigned int slot) const
{
	glActiveTexture(GL_TEXTURE0+ slot);
	GLCall(glBindTexture(GL_TEXTURE_CUBE_MAP, RendererID));

}
void CubeTexture::UnBind() const
{
	GLCall(glBindTexture(GL_TEXTURE_CUBE_MAP, 0));
}