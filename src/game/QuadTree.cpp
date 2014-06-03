
#include "QuadTree.hh"


QuadTree::QuadTree(Rectangle const& bounds)
    : m_objects(), m_bounds(bounds)
{
    memset(m_nodes, 0, sizeof(m_nodes));
}

void QuadTree::clear() {
    m_objects.clear();

    for (int i = 0; i < 4; i++) {
        if (m_nodes[i] != NULL) {
            m_nodes[i]->clear();
            delete m_nodes[i];
            m_nodes[i] = NULL;
        }
    }
}

void QuadTree::insert(AGameObject& object) {
    // if node is not a leaf.
    if (m_nodes[0] != NULL) {
        int index = this->getIndex(object.getCollider());
        if (index != -1) {
            m_nodes[index]->insert(object);
            return ;
        }
    }

    m_objects.push_back(&object);

    if (m_objects.size() > MAX_OBJECTS && m_nodes[0] == NULL) {
        this->split();
        auto it = m_objects.begin();
        while (it != m_objects.end()) {
            int index = this->getIndex((*it)->getCollider());
            if (index != -1) {
                m_nodes[index]->insert(**it);
                m_objects.erase(it++);
            }
            else {
                it++;
            }
        }
    }
}

std::list<AGameObject*>& QuadTree::retrieve(
    std::list<AGameObject*>& list, Rectangle const& area) {

    if (m_nodes[0] != NULL) {
        int index = this->getIndex(area);
        if (index != -1) {
          m_nodes[index]->retrieve(list, area);
        }
    }
    list.insert(list.end(), m_objects.begin(), m_objects.end());
    return list;
}

void QuadTree::split() {
    double new_w = m_bounds.getW() / 2;
    double new_h = m_bounds.getH() / 2;
    double x = m_bounds.getX();
    double y = m_bounds.getY();

    m_nodes[0] = new QuadTree(Rectangle(x,          y,          new_w, new_h));
    m_nodes[1] = new QuadTree(Rectangle(x,          y + new_h,  new_w, new_h));
    m_nodes[2] = new QuadTree(Rectangle(x + new_w,  y,          new_w, new_h));
    m_nodes[3] = new QuadTree(Rectangle(x + new_w,  y + new_h,  new_w, new_h));
}

int QuadTree::getIndex(Rectangle const& area) {
    double mid_w = m_bounds.getX() + m_bounds.getW() / 2;
    double mid_h = m_bounds.getY() + m_bounds.getH() / 2;

    bool top_fit = (area.getY2() < mid_h);
    bool bottom_fit = (area.getY() > mid_h);

    bool left_fit = (area.getX2() < mid_w);
    bool right_fit = (area.getX() > mid_w);

    int index = -1;
    if (top_fit) {
        if (left_fit) {
            index = 0;
        }
        else if (right_fit) {
            index = 1;
        }
    }
    else if (bottom_fit) {
        if (left_fit) {
            index = 2;
        }
        else if (right_fit) {
            index = 3;
        }        
    }
    return index;
}

bool QuadTree::removeObject(AGameObject& obj, Rectangle const& collider) {
    if (m_nodes[0] != NULL) {
        int index = getIndex(collider);
        if (index != -1) {
            return m_nodes[index]->removeObject(obj, collider);            
        }
    }

    size_t size = m_objects.size();
    m_objects.remove_if([&](AGameObject* pobj) { return pobj == &obj; });
    return m_objects.size() < size;
}

bool QuadTree::removeObject(AGameObject& obj) {
    return removeObject(obj, obj.getCollider());
}

bool QuadTree::updateObject(AGameObject& obj, Rectangle const& old) {
    if (!removeObject(obj, old)) {
        return false;
    }

    insert(obj);
    return true;
}
