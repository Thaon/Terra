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

void ImageManager::Save(int size, char* imageData, std::string fileName)
{
	int bytesToUsePerPixel = 3;  // RGB
	int sizeOfByte = sizeof(unsigned char);
	int imageSize = size * sizeOfByte * bytesToUsePerPixel;
	ILuint imageID = ilGenImage();// +m_images;
	ilBindImage(imageID);
	printf("New image!  width=%d,  height=%d,  bpp=%d\n",
		ilGetInteger(IL_IMAGE_WIDTH),
		ilGetInteger(IL_IMAGE_HEIGHT),
		ilGetInteger(IL_IMAGE_BPP)
	);

	//texxing the image
	ilTexImage(size, size, 1, 3, IL_RGB, IL_UNSIGNED_BYTE, imageData);

	printf("Now width=%d,  height=%d,  bpp=%d\n",
		ilGetInteger(IL_IMAGE_WIDTH),
		ilGetInteger(IL_IMAGE_HEIGHT),
		ilGetInteger(IL_IMAGE_BPP)
	);

	//enable overwriting
	ilEnable(IL_FILE_OVERWRITE);
	//save
	ilSave(IL_PNG, "output.png");
}

const char* ImageManager::GetBytes()
{
	const char* data;
	int size = GetSize();
	data = reinterpret_cast<const char*>(ilGetData());

	return data;
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
