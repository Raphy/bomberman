
#include "Exception.hh"

Exception::Exception(std::string const& msg) : m_ss(msg) {
}

Exception::Exception(Exception const& other) : m_ss(other.m_ss.str()) {
}

std::ostream& Exception::getStream() {
    return m_ss;
}

const char* Exception::what() const throw() {
    return m_ss.str().c_str();
}