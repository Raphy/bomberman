
#ifndef RECTANGLE_HH_
# define RECTANGLE_HH_

#include <glm/glm.hpp>

// top-left position and scale of an area.
class Rectangle {

private:
    glm::vec3 m_position;
    glm::vec3 m_scale;

public:
    Rectangle() : m_position(0,0,0), m_scale(0,0,0) {}

    Rectangle(glm::vec3 const& position, glm::vec3 const& scale)
        : m_position(position), m_scale(scale) {}

    Rectangle(double x, double y, double w, double h)
        : m_position(x, 0, y), m_scale(w, 0, h) {}

    Rectangle(Rectangle const& other)
        : m_position(other.m_position), m_scale(other.m_scale) {}

    glm::vec3 const& getPosition() const { return m_position; }
    glm::vec3 const& getScale() const { return m_scale; }

    double getX() const { return m_position.x; }
    double getX2() const { return m_position.x + m_scale.x; }
    double getY() const { return m_position.z; }
    double getY2() const { return m_position.z + m_scale.z; }
    double getW() const { return m_scale.x; }
    double getH() const { return m_scale.z; }

    // Check if a rectangle overlap an other rectangle.
    bool overlapping(Rectangle const& other) const {
       return getX() <= other.getX2() && getX2() >= other.getX() &&
            getY() <= other.getY2() && getY2() >= other.getY();
    }
};


#endif // !RECTANGLE_HH_