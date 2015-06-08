#ifndef BOXOBJECT_H
#define BOXOBJECT_H

#include "../DebugLog.h"
#include <string>
#include <vector>

#include <glm/glm.hpp>

using namespace std;
using namespace glm;

class BoxObject
{
private:
	vec4 color;
	vec4 borders;
	float quad[12];
public:
	BoxObject(){};
	BoxObject(vec2 topRight, vec2 botLeft, int thickness, vec4 &color);
	~BoxObject();
	void getBoxAttributes(vec4 &color, vec4 &borders, float* &quad);
};

#endif