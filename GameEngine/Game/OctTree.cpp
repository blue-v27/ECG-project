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

void OctreeNode::Subdivide()
{
    glm::vec3 center = m_bounds.GetCenter();
    glm::vec3 offset = m_bounds.GetOffset();

    for (int i = 0; i < 8; i++)
    {
        glm::vec3 newCenter = center;
        newCenter.x += (i & 1) ? offset.x * 0.5f : -offset.x * 0.5f;
        newCenter.y += (i & 2) ? offset.y * 0.5f : -offset.y * 0.5f;
        newCenter.z += (i & 4) ? offset.z * 0.5f : -offset.z * 0.5f;

        BoundingBox childBounds;
        childBounds.SetWorldMin(newCenter - offset * 0.5f);
        childBounds.SetWorldMax(newCenter + offset * 0.5f);

        m_children[i] = new OctreeNode(childBounds, m_depth + 1);
    }
}