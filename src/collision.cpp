#include "collision.h"

namespace leng {

    
bool doBoxesIntersect(Box a, Box b) {
    return (std::abs(a.x - b.x) * 2 <= (a.width + b.width)) &&
	(std::abs(a.y - b.y) * 2 <= (a.height + b.height));
}

    // Circular collision
bool doCirclesIntersect(Entity* agent, Entity* agent2) {
    // Minimum distance before there is a collision
    const float MIN_DISTANCE = agent->bb.radius.x * 2.0f;

    // Center position of this agent
    glm::vec2 centerPosA = agent2->bb.position + glm::vec2(agent2->bb.radius * 2.0f);
    // Center position of the parameter agent
    glm::vec2 centerPosB = agent->bb.position + glm::vec2(agent->bb.radius * 2.0f);

    // Distance vector between the two agents
    glm::vec2 distVec = centerPosA - centerPosB;
    
    // Length of the distance vector
    float distance = glm::length(distVec);

    // Depth of the collision
    float collisionDepth = MIN_DISTANCE - distance;

    // If collision depth > 0 then we did collide
    if (collisionDepth > 0) {
        return true;
    }
    return false;
}
    
// Circular collision
bool collideWithCircle(Entity* agent, Entity* agent2) {
    // Minimum distance before there is a collision
    const float MIN_DISTANCE = agent->bb.radius.x * 2.0f;

    // Center position of this agent
    glm::vec2 centerPosA = agent2->bb.position + glm::vec2(agent2->bb.radius * 2.0f);
    // Center position of the parameter agent
    glm::vec2 centerPosB = agent->bb.position + glm::vec2(agent->bb.radius * 2.0f);

    // Distance vector between the two agents
    glm::vec2 distVec = centerPosA - centerPosB;
    
    // Length of the distance vector
    float distance = glm::length(distVec);

    // Depth of the collision
    float collisionDepth = MIN_DISTANCE - distance;

    // If collision depth > 0 then we did collide
    if (collisionDepth > 0) {

        // Get the direction times the collision depth so we can push them away from each other
        glm::vec2 collisionDepthVec = glm::normalize(distVec) * collisionDepth;

        // Push them in opposite directions
        agent2->position+= collisionDepthVec / 2.0f;
        agent->position-= collisionDepthVec / 2.0f;

        return true;
    }
    return false;
}
    /*
    // AABB (Axis Aligned Bounding Box) collision
void collideWithTile(glm::vec2 tilePos) {

    const float TILE_RADIUS = (float)TILE_WIDTH / 2.0f;
    // The minimum distance before a collision occurs
    const float MIN_DISTANCE = AGENT_RADIUS + TILE_RADIUS;

    // Center position of the agent
    glm::vec2 centerAgentPos = _position + glm::vec2(AGENT_RADIUS);
    // Vector from the agent to the tile
    glm::vec2 distVec = centerAgentPos - tilePos;

    // Get the depth of the collision
    float xDepth = MIN_DISTANCE - abs(distVec.x);
    float yDepth = MIN_DISTANCE - abs(distVec.y);

    // If both the depths are > 0, then we collided
    if (xDepth > 0 && yDepth > 0) {

        // Check which collision depth is less
        if (std::max(xDepth, 0.0f) < std::max(yDepth, 0.0f)) {
            // X collsion depth is smaller so we push in X direction
            if (distVec.x < 0) {
                _position.x -= xDepth;
            } else {
                _position.x += xDepth;
            }
        } else {
            // Y collsion depth is smaller so we push in X direction
            if (distVec.y < 0) {
                _position.y -= yDepth;
            } else {
                _position.y += yDepth;
            }
        }
    }
}
    */

// AABB (Axis Aligned Bounding Box) collision
    bool collideWithTile(glm::vec2 position, int width, int height, Entity* agent2) {
    // The minimum distance before a collision occurs
	const float MIN_DISTANCE_X = width / 2.0f + agent2->width / 2.0f;
	const float MIN_DISTANCE_Y = height / 2.0f + agent2->height / 2.0f;

    // Vector from center of agent to center of tile
	glm::vec2 distVec = (position + glm::vec2(width / 2, height / 2)) - (agent2->position + glm::vec2(agent2->width / 2, agent2->height / 2));

    // Get the depth of the collision
    float xDepth = MIN_DISTANCE_X - abs(distVec.x);
    float yDepth = MIN_DISTANCE_Y - abs(distVec.y);

    // If both the depths are > 0, then we collided
    if (xDepth > 0 && yDepth > 0) {
        return true;
    }
    return false;
}
    
} // namespace leng
