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
    
    static int s_camera_width;
    static int s_camera_height;
    
private:

    static int CameraWidth() { return s_camera_width; }
    static int CameraHeight() { return s_camera_height; }
    
};

#endif	/* CONFIGURATION_HH */

