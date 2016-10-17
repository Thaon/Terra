#include "stdafx.h"
#include "ImageManager.h"


ImageManager::ImageManager()
{
	m_imagesDictionary = std::map<ILuint, std::string>();
}


ImageManager::~ImageManager()
{
}

ILuint ImageManager::GetImage(std::string imageName)
{
	for (auto image : m_imagesDictionary)
	{
		if (image.second == imageName)
		{
			//binding it to the FSM
			ilBindImage(image.first);
			return image.first;
		}
	}
	printf("Could not find requested image :(");
	return -1;
}

void ImageManager::AddImage(std::string fileName, std::string name)
{
	//generating image
	ILuint ImageName;
	ilGenImages(m_images, &ImageName);
	m_imagesDictionary.emplace(m_images, name);
	//binding it
	ilBindImage(m_images);
	//loading it properly
	Load(fileName.c_str());
	m_images++;

}

void ImageManager::Load(const char* fileName)
{
	std::cout << (const ILstring)fileName << std::endl;

	ILboolean result = ilLoadImage((const ILstring)fileName);

	if (result == true)
	{
		printf("the image loaded successfully\n");
	}
	else
	{
		printf("The image failed to load\n");

		ILenum err = ilGetError();
		printf("the error %d\n", err);
		printf("string is %s\n", ilGetString(err));
	}
}
