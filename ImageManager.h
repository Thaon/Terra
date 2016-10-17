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

	//single image G&S
	int GetSize() { return ilGetInteger(IL_IMAGE_SIZE_OF_DATA); }
	ILubyte* GetBytes() { return ilGetData(); }
};

