#ifndef TEXTURE_CACHE_H
#define TEXTURE_CACHE_H

#include <map>

#include "leng.h"

namespace leng {
    
class TextureCache {
public:
	TextureCache();
	~TextureCache();

	Texture getTexture(const std::string& texturePath);

private:
	std::map<std::string, Texture> textureMap;
};

} // namespace leng

#endif // TEXTURE_CACHE_H
