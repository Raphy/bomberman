/* 
 * File:   Configuration.hh
 * Author: svirch_n
 *
 * Created on 13 June 2014, 19:08
 */

#ifndef CONFIGURATION_HH
#define	CONFIGURATION_HH

class Configuration {
private:
    
    static int s_window_width;
    static int s_window_height;
    static float s_fov_horizontal;
    
public:

    static int WindowWidth() { return s_window_width; }
    static int WindowHeight() { return s_window_height; }
    static float FOV() { return s_fov_horizontal; }
    
};

#endif	/* CONFIGURATION_HH */

