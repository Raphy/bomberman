#include "AWidget.hh"

class Button : public AWidget
{
public:
  Button(bool cursor, const std::string& path, glm::vec3 pos, glm::vec3 scale);
  ~Button();

  bool initialize();
  void update(gdl::Clock const& clock, gdl::Input& input);
  void draw(gdl::AShader & shader, gdl::Clock const& clock);

protected:
  bool _cursor;
  AWidget *c;


  /* pointeur sur le bouttton */

};

