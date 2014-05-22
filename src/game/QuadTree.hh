
#ifndef QUAD_TREE_HH_
# define QUAD_TREE_HH_

# include <list>
# include <cstdlib>

# include "Rectangle.hh"
# include "AGameObject.hh"

/*
    indexes: 
        -------------
        |     |     |
        |  0  |  1  |
        |-----|-----|
        |     |     |
        |  2  |  3  |
        -------------
*/

class QuadTree {

private:
    static const size_t MAX_OBJECTS = 10; 

    std::list<AGameObject*> m_objects;
    Rectangle m_bounds;
    QuadTree *m_nodes[4];

    // Be sure to clear the node before to call it.
    void split();
    int getIndex(Rectangle const& area);

public:
    QuadTree(Rectangle const& bounds);
    void clear();
    void insert(AGameObject* object);
    std::list<AGameObject*>& retrieve(
        std::list<AGameObject*>& list, Rectangle const& area);
};

#endif // !QUAD_TREE_HH_