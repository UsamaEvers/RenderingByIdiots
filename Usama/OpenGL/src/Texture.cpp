#include "../inc/Texture.h"
#include "../inc/stb_image.h"

TextureManager* TextureManager::instance;	

TextureManager::TextureManager()
{

}

void TextureManager::InitTextureManager()
{
	instance = new TextureManager();
}

bool TextureManager::i_GenTexture(std::string textName, bool alphaEnable)
{

	allTextures[textName] = 0;

	if (!alphaEnable)
	{
		glGenBuffers(1, &allTextures[textName]);
		glBindTexture(GL_TEXTURE_2D, allTextures[textName]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		stbi_set_flip_vertically_on_load(true);

		int width, height, nrChannels;
		unsigned char* data = stbi_load(textName.c_str(), &width, &height, &nrChannels, 0);
		if (data)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else
		{
			std::cout << "Failed to load texture" << std::endl;
			return false;
		}
		stbi_set_flip_vertically_on_load(false);
		stbi_image_free(data);
	}
	else
	{
		glGenTextures(1, &allTextures[textName]);
		glBindTexture(GL_TEXTURE_2D, allTextures[textName]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		stbi_set_flip_vertically_on_load(true);

		int width, height, nrChannels;
		unsigned char* data = stbi_load(textName.c_str(), &width, &height, &nrChannels, 0);
		if (data)
		{
			// note that the awesomeface.png has transparency and thus an alpha channel, so make sure to tell OpenGL the data type is of GL_RGBA
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else
		{
			std::cout << "Failed to load texture" << std::endl;
			return false;
		}
		stbi_set_flip_vertically_on_load(false);
		stbi_image_free(data);
	}
	return true;
}

GLuint TextureManager::CheckIfTextureExists(std::string textName, bool alphaEnable)
{
	assert(instance);
	return instance->i_CheckIfTextureExists(textName, alphaEnable);
}

GLuint TextureManager::i_CheckIfTextureExists(std::string textName, bool alphaEnable)
{
	if (allTextures.find(textName) == allTextures.end())
		assert(i_GenTexture(textName, alphaEnable));

	return allTextures.at(textName);
}
