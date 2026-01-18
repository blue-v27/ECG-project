#include "OctTree.h"

OctreeNode::OctreeNode( BoundingBox& bounds, int depth) : m_bounds(bounds), m_depth(depth)
{
}

OctreeNode::~OctreeNode()
{
    for (OctreeNode* child : m_children)
    {
        delete child;
        child = nullptr;
    } 
}

void OctreeNode::Insert(GameObject* object)
{
    BoundingBox box = object->GetBoundingBox();

    if (!m_bounds.IsIntersecting(box))
        return;

    if (m_isLeaf)
    {
        m_objects.push_back(object);

        if (m_objects.size() > MAX_OBJECTS && m_depth < MAX_DEPTH)
        {
            Subdivide();

            for (GameObject* obj : m_objects)
            {
                int index = GetChildIndex(obj->GetBoundingBox());
                if (index != -1)
                    m_children[index]->Insert(obj);
            }

            m_objects.clear();
            m_isLeaf = false;
        }
    }
    else
    {
        int index = GetChildIndex(box);
        if (index != -1)
            m_children[index]->Insert(object);
    }
}
