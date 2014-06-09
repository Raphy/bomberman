#ifndef EXCEPTION_HH_
# define EXCEPTION_HH_

# include <exception>
# include <sstream>
# include <iostream>

class Exception : public std::exception {

private:
    std::ostringstream m_ss;

public:
    Exception(std::string const& msg="");
    Exception(Exception const& other);

    virtual ~Exception() throw() {};
    virtual const char* what() const throw();

    std::ostream& getStream();
};

#endif // !EXCEPTION_HH_