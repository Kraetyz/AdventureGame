//http://nehe.gamedev.net/tutorial/playing_avi_files_in_opengl/23001/
//Tutorial used for this AVI reader
#ifndef AVISTREAM_H
#define AVISTREAM_H

#include "../DebugLog.h"
#include <string>

#include <Windows.h>
#include <Vfw.h>

#include <GL\glew.h>
#include <GLFW\glfw3.h>

using namespace std;
#pragma comment (lib, "Vfw32.lib")

class AVIstream
{
private:
	const int TEXWIDTH = 1024; //If these are changed, don't forget to fix the Assembly code in flipIt()
	const int TEXHEIGHT = 1024;
	int	next = 0;				// Used For Animation
	int	frame = 0;			// Frame Counter
	AVISTREAMINFO psi;		// Pointer To A Structure Containing Stream Info
	PAVISTREAM pavi;		// Handle To An Open Stream
	PGETFRAME pgf;			// Pointer To A GetFrame Object
	BITMAPINFOHEADER bmih;	// Header Information For DrawDibDraw Decoding
	long lastframe;			// Last Frame Of The Stream
	int width;				// Video Width
	int height;				// Video Height
	char *pdata;			// Pointer To Texture Data
	int mpf;				// Will Hold Rough Milliseconds Per Frame

	HDRAWDIB hdd;						// Handle For Our Dib
	HBITMAP hBitmap;					// Handle To A Device Dependant Bitmap
	HDC hdc = CreateCompatibleDC(0);	// Creates A Compatible Device Context
	unsigned char* data = 0;			// Pointer To Our Resized Image

	void flipIt(void* buffer);
	void openAVI(std::string szFile);

	GLuint tex;
	void genTexture();
public:
	AVIstream(std::string filePath);
	~AVIstream();
	void GrabAVIFrame(float dT);

	GLuint getTex()
	{
		return tex;
	}
};

#endif