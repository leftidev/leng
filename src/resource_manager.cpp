#include "resource_manager.h"

namespace leng {
TextureCache ResourceManager::_textureCache;

Texture ResourceManager::getTexture(std::string texturePath)
{
	return _textureCache.getTexture(texturePath);
}
}
