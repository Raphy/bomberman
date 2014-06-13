/* 
 * File:   Configuration.hh
 * Author: svirch_n
 *
 * Created on 13 June 2014, 19:08
 */

#ifndef CONFIGURATION_HH
#define	CONFIGURATION_HH

class Configuration {
public:
    
    static int s_window_width;
    static int s_window_height;
    
private:

    static int WindowWidth() { return s_window_width; }
    static int WindowHeight() { return s_window_height; }
    
};

#endif	/* CONFIGURATION_HH */

