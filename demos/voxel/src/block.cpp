#include "block.h"

namespace leng {
    
Block::Block() {}

Block::~Block() {}

bool Block::isActive() {
    if(active) {
	return true;
    } else {
	return false;
    }
}

void Block::setActive(bool Active) {
    active = Active;
}

} // namespace leng
