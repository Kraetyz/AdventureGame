#include "AVIstream.h"

AVIstream::AVIstream(std::string filePath)
{
	hdd = DrawDibOpen();
	openAVI(string("Media/AVI/").append(filePath)); // Open The AVI File

	// Create The Texture
	genTexture();
}

void AVIstream::genTexture()
{
	glGenTextures(1, &tex);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, tex);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);	// Set Texture Max Filter
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);	// Set Texture Min Filter
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, TEXWIDTH, TEXHEIGHT, 0, GL_BGR, GL_UNSIGNED_BYTE, data);
	glBindTexture(GL_TEXTURE_2D, 0);
}

/*void AVIstream::flipIt(void* buffer)                       // Flips The Red And Blue Bytes (256x256)
{
	void* b = buffer;                       // Pointer To The Buffer
	__asm                               // Assembler Code To Follow
	{
		mov ecx, 1024 * 1024                    // Set Up A Counter (Dimensions Of Memory Block)
			mov ebx, b                      // Points ebx To Our Data (b)
		label :                          // Label Used For Looping
		mov al, [ebx + 0]                  // Loads Value At ebx Into al
			mov ah, [ebx + 2]                  // Loads Value At ebx+2 Into ah
			mov[ebx + 2], al                  // Stores Value In al At ebx+2
			mov[ebx + 0], ah                  // Stores Value In ah At ebx

			add ebx, 3                   // Moves Through The Data By 3 Bytes
			dec ecx                     // Decreases Our Loop Counter
			jnz label                   // If Not Zero Jump Back To Label
	}
}*/

void AVIstream::openAVI(std::string szFile)
{
	AVIFileInit();			
	std::wstring stemp = std::wstring(szFile.begin(), szFile.end());
	LPCWSTR file = stemp.c_str();// Opens The AVIFile Library

	// Opens The AVI Stream
	if (AVIStreamOpenFromFile(&pavi, file, streamtypeVIDEO, 0, OF_READ, NULL) != 0)
	{
		// An Error Occurred Opening The Stream
		MessageBox(HWND_DESKTOP, (LPCWSTR)"Failed To Open The AVI Stream", (LPCWSTR)"Error", MB_OK | MB_ICONEXCLAMATION);
	}

	AVIStreamInfo(pavi, &psi, sizeof(psi));						// Reads Information About The Stream Into psi
	width = psi.rcFrame.right - psi.rcFrame.left;					// Width Is Right Side Of Frame Minus Left
	height = psi.rcFrame.bottom - psi.rcFrame.top;					// Height Is Bottom Of Frame Minus Top

	lastframe = AVIStreamLength(pavi);							// The Last Frame Of The Stream

	mpf = AVIStreamSampleToTime(pavi, lastframe) / lastframe;		// Calculate Rough Milliseconds Per Frame
	
	bmih.biSize = sizeof(BITMAPINFOHEADER);					// Size Of The BitmapInfoHeader
	bmih.biPlanes = 1;											// Bitplanes	
	bmih.biBitCount = 24;										// Bits Format We Want (24 Bit, 3 Bytes)
	bmih.biWidth = TEXWIDTH;											// Width We Want (256 Pixels)
	bmih.biHeight = TEXHEIGHT;										// Height We Want (256 Pixels)
	bmih.biCompression = BI_RGB;								// Requested Mode = RGB

	hBitmap = CreateDIBSection(hdc, (BITMAPINFO*)(&bmih), DIB_RGB_COLORS, (void**)(&data), NULL, NULL);
	SelectObject(hdc, hBitmap);								// Select hBitmap Into Our Device Context (hdc)

	pgf = AVIStreamGetFrameOpen(pavi, NULL);						// Create The PGETFRAME	Using Our Request Mode
	if (pgf == NULL)
	{
		// An Error Occurred Opening The Frame
		MessageBox(HWND_DESKTOP, file, (LPCWSTR)"Error", MB_OK | MB_ICONEXCLAMATION);
	}
}

void AVIstream::GrabAVIFrame(float dT)									// Grabs A Frame From The Stream
{
	next += dT * 1000;											// Increase next Based On The Timer
	frame = next / mpf;												// Calculate The Current Frame

	if (frame >= lastframe)										// Are We At Or Past The Last Frame?
	{
		frame = 0;												// Reset The Frame Back To Zero (Start Of Video)
		next = 0;													// Reset The Animation Timer (next)
	}

	LPBITMAPINFOHEADER lpbi;									// Holds The Bitmap Header Information
	lpbi = (LPBITMAPINFOHEADER)AVIStreamGetFrame(pgf, frame);	// Grab Data From The AVI Stream
	pdata = (char *)lpbi + lpbi->biSize + lpbi->biClrUsed * sizeof(RGBQUAD);	// Pointer To Data Returned By AVIStreamGetFrame

	// Convert Data To Requested Bitmap Format
	DrawDibDraw(hdd, hdc, 0, 0, TEXWIDTH, TEXHEIGHT, lpbi, pdata, 0, 0, width, height, 0);

	// Update The Texture
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, tex);
	glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, TEXWIDTH, TEXHEIGHT, GL_BGR, GL_UNSIGNED_BYTE, data);
	glBindTexture(GL_TEXTURE_2D, 0);
}

AVIstream::~AVIstream()
{
	DeleteObject(hBitmap);										// Delete The Device Dependant Bitmap Object
	DrawDibClose(hdd);											// Closes The DrawDib Device Context
	AVIStreamGetFrameClose(pgf);								// Deallocates The GetFrame Resources
	AVIStreamRelease(pavi);										// Release The Stream
	AVIFileExit();												// Release The File

	glDeleteTextures(1, &tex);
}