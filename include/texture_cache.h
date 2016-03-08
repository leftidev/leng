#pragma once

#include <map>

#include "leng.h"

namespace leng {
    
class TextureCache {
public:
	TextureCache();
	~TextureCache();

	Texture getTexture(std::string texturePath);

private:
	std::map<std::string, Texture> _textureMap;
};
}
