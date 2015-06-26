#ifndef SCENE_H
#define SCENE_H

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

class Scene
{
private:
	string charName;
	DialogueTree* tree;
	AVIstream* background;
	TextObject* characterName;

	vector<BoxObject*> sceneBoxes;
	BoxObject* charBox;
	BoxObject* textBox;
	void clearBoxes();
	void setupBoxes();

	bool intersectWithSceneBox(int index, vec2 mousePos);
public:
	Scene(string scenePath);
	~Scene();

	AVIstream* getBackground();
	vector<TextObject*> getText();
	vector<BoxObject*> getBoxes();

	void sceneClick(int x, int y);

	void update(int mx, int my);
};

#endif