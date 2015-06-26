#ifndef OVERWORLD_H
#define OVERWORLD_H

#include "../DebugLog.h"
#include "../Engine/TextObject.h"
#include "../Engine/BoxObject.h"
#include <string>
#include <vector>
#include <fstream>

#include <glm/glm.hpp>

#include "DialogueTree.h"
#include "../Engine/AVIstream.h"
#include "../Engine/TextObject.h"

using namespace std;
using namespace glm;

class Overworld
{
private:
public:
	Overworld();
	~Overworld();
};

#endif