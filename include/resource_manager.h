#pragma once

#include <string>

#include "texture_cache.h"


namespace leng {
// This is a way to access all resources, such as models or textures
class ResourceManager {
public:
	static Texture getTexture(std::string texturePath);

private:
	static TextureCache _textureCache;
};
}
