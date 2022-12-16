#pragma once
#include <../Shader/Shader.h>
class Drawable {
public:
	inline virtual void Draw(Shader& shader) {};
};
