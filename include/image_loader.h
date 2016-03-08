#ifndef IMAGE_LOADER_H
#define IMAGE_LOADER_H

#include <string>

#include "leng.h"

namespace leng {
    
class ImageLoader {
public:
    static Texture loadImage(const std::string& path);
};

} // namespace leng

#endif // IMAGE_LOADER_H
