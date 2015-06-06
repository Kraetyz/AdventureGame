#ifndef SCENE_H
#define SCENE_H

#include "../DebugLog.h"
#include "../Engine/TextObject.h"
#include <string>
#include <vector>
#include <fstream>

#include <glm/glm.hpp>

#include "DialogueTree.h"
#include "../Engine/AVIstream.h"
#include "../Engine/TextObject.h"

using namespace std;
using namespace glm;

class Scene
{
private:
	DialogueTree* tree;
	AVIstream* background;
	TextObject* characterName;
public:
	Scene();
	~Scene();

	AVIstream* getBackground();
	vector<TextObject*> getText();

	void sceneClick(int x, int y);
};

#endif