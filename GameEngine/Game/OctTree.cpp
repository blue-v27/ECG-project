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
    glm::vec3 half = m_bounds.GetOffset() * 0.5f;

    glm::vec3 childCenters[8];

    childCenters[0] = center + glm::vec3(-half.x, -half.y, -half.z);
    childCenters[1] = center + glm::vec3(half.x, -half.y, -half.z);
    childCenters[2] = center + glm::vec3(-half.x, half.y, -half.z);
    childCenters[3] = center + glm::vec3(half.x, half.y, -half.z);

    childCenters[4] = center + glm::vec3(-half.x, -half.y, half.z);
    childCenters[5] = center + glm::vec3(half.x, -half.y, half.z);
    childCenters[6] = center + glm::vec3(-half.x, half.y, half.z);
    childCenters[7] = center + glm::vec3(half.x, half.y, half.z);

    for (int i = 0; i < 8; i++)
    {
        BoundingBox childBounds;

        childBounds.SetWorldMin(childCenters[i] - half);
        childBounds.SetWorldMax(childCenters[i] + half);

        m_children[i] = new OctreeNode(childBounds, m_depth + 1);
    }

    m_isLeaf = false;
}

int OctreeNode::GetChildIndex(BoundingBox& box)
{
    for (int i = 0; i < 8; i++)
    {
        if (m_children[i]->m_bounds.IsIntersecting(box))
            return i;
    }
    return -1;
}

void OctreeNode::Query(BoundingBox& range, std::vector<GameObject*>& results)
{
    if (!m_bounds.IsIntersecting(range))
        return;

    if (m_isLeaf)
    {
        for (auto* obj : m_objects)
            results.push_back(obj);
    }
    else
    {
        for (auto* child : m_children)
            if (child)
                child->Query(range, results);
    }
}


