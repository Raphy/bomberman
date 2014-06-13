
#ifndef QUAD_TREE_HH_
# define QUAD_TREE_HH_

# include <list>
# include <iostream>

# include "Rectangle.hh"
# include "AGameObject.hh"

/*
    indexes of sub nodes (for m_nodes[]): 
        -------------
        |     |     |
        |  0  |  1  |
        |-----|-----|
        |     |     |
        |  2  |  3  |
        -------------

    -1 => the current and father of sub nodes (this).
*/

// The magic data structure. See wikipedia. 
class QuadTree {

private:
    // The maximum number of objects that a node can contains
    // before splitting it self.
    static const size_t MAX_OBJECTS = 50; 

    // List of objects contained in the node.
    std::list<AGameObject*> m_objects;
    // The bounds of the node (the area).
    Rectangle m_bounds;
    // The 4 liked nodes (nodes are null if the node is a leaf).
    QuadTree *m_nodes[4];

    // spit the node (must be a leaf) in 4 nodes. 
    // Be sure to clear the node before to call it.
    void split();
    // Get the index of the node which contains this area,
    // or -1 (if the area does not fit in any node). In the last
    // case, the object is stored in the parent node.
    int getIndex(Rectangle const& area);

public:
    // Construct the QuadTree with the given bounds.
    QuadTree(Rectangle const& bounds);
    // Clear the current node and his child recursively.
    void clear();
    // Insert an object in the quad tree
    // (the correct node is found with a recursive search).
    void insert(AGameObject& object);
    // Fill the given list with all objects which are near
    // to the given area (and potentially in collision with).
    std::list<AGameObject*>& retrieve(
        std::list<AGameObject*>& list, Rectangle const& area);

    // Remove an object.
    bool removeObject(AGameObject& obj);
    // Remove an object whose the position has changed.
    // The old collider has to be specified.
    bool removeObject(AGameObject& obj, Rectangle const& old);
    // Update the position of an object whose the position has changed.
    // If the object isn't in the quad tree, return false and the object
    // is NOT inserted.
    bool updateObject(AGameObject& obj, Rectangle const& old);
};

#endif // !QUAD_TREE_HH_