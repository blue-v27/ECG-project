#pragma once
#include "vector"
#include <glm.hpp>
#include <gtx\transform.hpp>
#include <gtc\matrix_transform.hpp>
#include <gtc\type_ptr.hpp>
#include "GameObject.h"

class OctreeNode
{
private:
    #define MAX_OBJECTS 8
    #define MAX_DEPTH   6

    BoundingBox m_bounds;
    std::vector<GameObject*> m_objects;

    OctreeNode* m_children[8]{ nullptr };
    bool m_isLeaf = true;
    int  m_depth;

public:
    OctreeNode(BoundingBox& bounds, int depth = 0);
    ~OctreeNode();

    void Insert(GameObject* object);
    void Query(BoundingBox& range, std::vector<GameObject*>& results);
    void Subdivide();
    int  GetChildIndex(BoundingBox& box);
    
};
