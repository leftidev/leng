#include <iostream>

#include "image_loader.h"
#include "texture_cache.h"


namespace leng {

TextureCache::TextureCache() {
}


TextureCache::~TextureCache() {
}

Texture TextureCache::getTexture(std::string texturePath) {
	// Lookup the texture and see if its in the map.
	auto mit = _textureMap.find(texturePath);

	// check if its not in the map
	if (mit == _textureMap.end()) {
		// Load the texture
		Texture newTexture = ImageLoader::loadImage(texturePath);

		// Insert it into the map
		_textureMap.insert(make_pair(texturePath, newTexture));

		return newTexture;
	}
	return mit->second;
}
}
