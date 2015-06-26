#ifndef STORYLINE_H
#define STORYLINE_H

#include <string>

using namespace std;

class Storyline
{
private:
	static int test;
	static int test2;
public:
	static int getVariable(string name);
	static void increaseVariable(string name, int val);
};

#endif