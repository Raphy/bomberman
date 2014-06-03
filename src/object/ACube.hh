/*
 * File:   ACube.hh
 * Author: svirch_n
 *
 * Created on 28 May 2014, 18:00
 */

#ifndef ACUBE_HH
#define ACUBE_HH

#include "AGeometry.hh"

class ACube: public AGeometry
{
    public:
        virtual ~ACube() {};

        protected:
            ACube(std::string const& id);
};
#endif   /* ACUBE_HH */


//~ Formatted by Jindent --- http://www.jindent.com
