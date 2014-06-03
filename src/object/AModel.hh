#ifndef		AMODEL_HH_
# define	AMODEL_HH_

# include	"AGameObject.hh"

class AModel: public AGameObject
{
    public:
	
	virtual ~AModel() {}
	virtual void draw(gdl::AShader & shader, gdl::Clock const& clock);
        
    protected:
        // Gonna throw an exception
        AModel(std::string const& modelPath, std::string const& id);
        gdl::Model      _model;
            
};

#endif		/* AMODEL_HH_ */