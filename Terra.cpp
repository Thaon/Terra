#include "stdafx.h"
#include "Common.h"
#include "ImageManager.h"

// some DevIL usage taken from: https://bobobobo.wordpress.com/2009/03/02/how-to-use-openil-to-generate-and-save-an-image/

int main()
{
	ilInit();
	printf("DevIL has been initialized\n");

	ImageManager manager = ImageManager();

	manager.AddImage("IMG/Grass.png", "grass");
	manager.AddImage("IMG/Grass2.png", "grass2");
	
	int id = manager.GetImage("grass");
	int size = manager.GetSize();
	int width = manager.GetWidth();
	int height = manager.GetHeight();

	std::cout << "image number: " << id << ", size is: " << size << " bytes, and is " << width << " X " << height << std::endl;

	id = manager.GetImage("grass2");
	size = manager.GetSize();
	width = manager.GetWidth();
	height = manager.GetHeight();

	std::cout << "image number: " << id << ", size is: " << size << " bytes, and is " << width << " X " << height << std::endl;

	//LOADING DONE, LET'S START MAKING STUFF!!!
	std::cout << "getting tiles in memory" << std::endl;
	manager.GetImage("grass");
	std::cout << "getting bytes" << std::endl;
	const char* grass = manager.GetBytes();
	const int tileSize = 8;
	std::cout << "done" << std::endl;
	const int imageSize = tileSize * tileSize * 4; //4 8X8 images together

	std::cout << "Now creating the image" << std::endl;
	char* image = (char*)malloc(imageSize * sizeof(char)); 

	std::cout << "Now creating the big picture" << std::endl;

	//building the final image
	//char finalImage[imageSize];
	std::string finalImage = grass;
	finalImage += grass;
	finalImage += grass;
	finalImage += grass;

	/*strcpy_s(finalImage, grass);
	strcat_s(finalImage, grass);
	strcat_s(finalImage, grass);
	strcat_s(finalImage, grass);*/

	std::cout << "Now painting the image" << std::endl;

	for (int i = 0; i < imageSize; i++)
	{
		image[i] = finalImage[i];
	}

	//int color = 0;

	//for (int x = 0; x < 64; x++)
	//{
	//	image[x] = color;
	//	std::cout << color << " - ";
	//	color++;
	//	//color == 0 ? color = 255 : color = 0; //alternate color between black and white
	//}

	std::cout << "Now saving the image" << std::endl;

	char* im = new char[imageSize];

	for (int i = 0 ; i < imageSize ; i++)
	{
		im[i] = finalImage[i];
	}

	manager.Save(8 * 2, im, "output.png");

	//// generate image data as just array of bytes.
	//// get width and height of your desktop
	//int width = GetSystemMetrics(SM_CXVIRTUALSCREEN);
	//int height = GetSystemMetrics(SM_CYVIRTUALSCREEN);

	//int bytesToUsePerPixel = 3;  // RGB
	//							 // we coulda used 4, if we wanted a "transparency" component,
	//							 // but we don't want this png to use trans.

	//							 // duh, the size of a byte is obviously ONE BYTE,
	//							 // but this is just a formality to PERHAPS
	//							 // make the code a bit more clear.
	//int sizeOfByte = sizeof(unsigned char);

	//// So this computation gets the size
	//// that the image data array should be.
	//// (width*height)   *   (#bytes to use per pixel) really.
	//int theSize = width * height * sizeOfByte * bytesToUsePerPixel;

	//unsigned char * imData = (unsigned char*)malloc(theSize);

	//for (int i = 0; i < theSize; i++)
	//{
	//	imData[i] = i % 255;
	//}


	//// Let's make an image now.
	//// the next line "generates an image" within the
	//// DevIL STATE MACHINE.

	//// DevIL is cool because it has this concept of
	//// your "currently selected image".

	//// So, when you call all the DevIL library functions,
	//// (such as ilTexImage to change an images properties),
	//// notice how there's no passing of any big data struct,
	//// pointer to an image, or anything like that.

	//// That's because the ONLY reference YOU get
	//// as the user of the OpenIL API IS this INT
	//// value:
	//ILuint imageID = ilGenImage();

	//// there.  We just created a NEW image (which will start out
	//// to being 1x1 pixels or something like that)
	//// our REFERENCE to this 1x1 pixel image IS
	//// the integer number imageID.

	//// NOW, we "select-in" the image we just generated
	//// as the one we're currently working on.
	//ilBindImage(imageID);

	//// From HENCE FORTH (until we call ilBindImage() again)
	//// WE ARE WORKING ON "imageID".  ANY calls to
	//// ilTexImage, or ilGetInteger, or WHATEVER are in
	//// reference to the LAST IMAGE WE LAST BOUND.

	//// So the new image we just created is rather.. empty.
	//printf("New image!  width=%d,  height=%d,  bpp=%d\n",

	//	ilGetInteger(IL_IMAGE_WIDTH),
	//	ilGetInteger(IL_IMAGE_HEIGHT),
	//	ilGetInteger(IL_IMAGE_BPP)
	//);

	//printf("About to tex up your image\n");
	//ilTexImage(

	//	width,
	//	height,

	//	1,  // OpenIL supports 3d textures!  but we don't want it to be 3d.  so
	//		// we just set this to be 1

	//	3,  // 3 channels:  one for R , one for G, one for B

	//	IL_RGB,  // duh, yeah use rgb!  coulda been rgba if we wanted trans

	//	IL_UNSIGNED_BYTE,  // the type of data the imData array contains (next)

	//	imData  // and the array of bytes represneting the actual image data

	//);

	//printf("Your image was texxed\n");

	//printf("Now width=%d,  height=%d,  bpp=%d\n",

	//	ilGetInteger(IL_IMAGE_WIDTH),
	//	ilGetInteger(IL_IMAGE_HEIGHT),
	//	ilGetInteger(IL_IMAGE_BPP)
	//);

	//// allow openIL to overwrite the file
	//// we created last time
	//ilEnable(IL_FILE_OVERWRITE);

	//// actually save out as png
	//ilSave(IL_PNG, _T("output.png"));

	//system("PAUSE");

	//// now try saving as jpg
	//ilSave(IL_JPG, _T("output.jpg"));

	//// now save as bmp
	//ilSave(IL_BMP, _T("output.bmp"));


	//// Look at the file sizes!  For this TYPE
	//// of image, png is the best because its
	//// flat colors repeated.

	//// On my mahcin eht png is 94KB and the BMP is 11000kB!
	//// the jpg comes out at 3000kb.

	//// PNG RULES!!

	//// lets give another example where jpg will
	//// be better...

	//// cahnge im data to being just pure noise
	//for (int i = 0; i < theSize; i++)
	//{
	//	imData[i] = rand() % 255;
	//}


	//// now set the data in the image with this new data array
	//ilSetData(imData);

	//// save again

	//// actually save out as png
	//ilSave(IL_PNG, _T("outputNoise.png"));

	//// now try saving as jpg
	//ilSave(IL_JPG, _T("outputNoise.jpg"));

	//// now save as bmp
	//ilSave(IL_BMP, _T("outputNoise.bmp"));


	//// Wowo!   So for this last test, PNG was
	//// worse than jpg and bmp!  that's remarkable.
	//// I actually didn't know that coudl happen.

	printf("and done \n");
	system("PAUSE");

}