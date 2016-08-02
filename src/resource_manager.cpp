#include "resource_manager.h"

namespace leng {
    
TextureCache ResourceManager::textureCache;

Texture ResourceManager::getTexture(std::string texturePath)
{
	return textureCache.getTexture(texturePath);
}
    
} // namespace leng
