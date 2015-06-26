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
	vec4 getBorders()
	{
		return borders;
	}

	void setColor(float r, float g, float b, float a)
	{
		color = vec4(r, g, b, a);
	}
};

#endif