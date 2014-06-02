#ifndef		AMODEL_HH_
# define	AMODEL_HH_

# include	"AGameObject.hh"

class AModel: public AGameObject
{
    public:
	
	// Gonna throw an exception
	AModel(std::string const& modelPath);
	
	virtual ~AModel() {}
	virtual void draw(gdl::AShader & shader, gdl::Clock const& clock);
        
    protected:
        gdl::Model      _model;
        unsigned int 	_animIndex;
            
};

#endif		/* AMODEL_HH_ */