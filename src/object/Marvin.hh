#include  "AModel.hh"
#include  <map>

class Marvin;
typedef void (Marvin::*inputFunction)(gdl::Clock const&);

class Marvin: public AModel
{
public:
 Marvin(): AModel("./build/assets/marvin.fbx") {}
 virtual ~Marvin() {}

 virtual bool initialize();
	virtual void update(gdl::Clock const& clock, gdl::Input& input);

private:

  std::map<int, inputFunction> _inputs;

	void onUpPressed(gdl::Clock const& clock);
  void onDownPressed(gdl::Clock const& clock);
  void onLeftPressed(gdl::Clock const& clock);
  void onRightPressed(gdl::Clock const& clock);
};