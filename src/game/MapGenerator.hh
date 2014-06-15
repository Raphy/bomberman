/*
 * File:   MapGenerator.hh
 * Author: parejo_p
 *
 * Created on 11 June 2014, 19:17
 */

#ifndef         MAPGENERATOR_HH
# define        MAPGENERATOR_HH

# include       <list>
# include       <utility>
# include       <vector>
# include       "AGameObject.hh"

class MapGenerator
{
    public:
        MapGenerator();
        virtual ~MapGenerator();

        std::pair<std::list<AGameObject*>, std::list<AGameObject*>> Generate(int width, int height);
        
    private:
        int                               _width;
        int                               _height;
        std::vector<std::pair<int, int>>  _frontier;
        std::vector<std::vector<char>> *  _field;
        std::vector<std::pair<int, int>>  _extra;
        std::pair<std::list<AGameObject*>, std::list<AGameObject*>> _objects;
        
        void Dig(int y, int x);
        bool Check(int y, int x);
        void Harden(int y, int x);
        void setExtra(int y, int x);
        std::pair<std::list<AGameObject*>, std::list<AGameObject*>> ToList();
};
#endif   /* MAPGENERATOR_HH */


//~ Formatted by Jindent --- http://www.jindent.com