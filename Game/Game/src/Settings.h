#ifndef SETTINGS_H
#define SETTINGS_H

class Settings
{
private:
	static int WIDTH;
	static int HEIGHT;
public:
	Settings(int w, int h);
	static int getWidth(){ return WIDTH; }
	static int getHeight(){ return HEIGHT; }
};
#endif