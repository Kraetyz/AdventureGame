#include "StorylineTest.h"

int Storyline::test = 0;
int Storyline::test2 = 0;

int Storyline::getVariable(string name)
{
	if (name == "TEST")
		return test;
	else if (name == "TEST2")
		return test2;
}

void Storyline::increaseVariable(string name, int val)
{
	if (name == "TEST")
		test += val;
	else if (name == "TEST2")
		test2 += val;
}