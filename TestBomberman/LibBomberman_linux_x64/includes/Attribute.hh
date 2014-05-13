
#ifndef ATTRIBUTE_HH_
# define ATTRIBUTE_HH_

# include <OpenGL.hh>

# include <set>

typedef unsigned char byte;

namespace gdl
{
  struct Attribute
  {
    size_t nbrByte;
    size_t nbrComponent;
    size_t offset;
    GLenum type;
    Attribute(size_t nbrByte, size_t nbrComponent, GLenum type);
    ~Attribute(void);
    Attribute(Attribute const &copy);
    Attribute &operator=(Attribute const &r);
  };
};

#endif /*!ATTRIBUTE_HH_*/
