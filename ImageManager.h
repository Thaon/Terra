#pragma once

#include "Common.h"

class ImageManager
{
private:
	ILuint m_images; //will keep track of the images we have
	std::map<ILuint, std::string> m_imagesDictionary;
	
	//single image related members
	int m_index, m_size, m_width, m_height;

	//and methods
	void Load(const char* fileName);

public:
	ImageManager();
	~ImageManager();

	//getters and setters
	ILuint GetImage(std::string);
	void AddImage(std::string fileName, std::string name);

	//single image related methods
	void Save(int size, char* imageData, std::string fileName);

	//single image G&S
	int GetSize() { return ilGetInteger(IL_IMAGE_SIZE_OF_DATA); }
	int GetWidth() { return ilGetInteger(IL_IMAGE_WIDTH); }
	int GetHeight() { return ilGetInteger(IL_IMAGE_HEIGHT); }
	const char* GetBytes();
};

