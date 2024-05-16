#ifndef _GPS_
#define _GPS_

#include <math.h>
#include "Systick.h"
#define EARTH_RADIUS 6371
#define PI 3.14159265359
 extern float currentlong,currentlat;

extern char GPS_Logname[];

//extern char finished,flag;



//extern char *token;



extern char a;
extern char valid_data;
extern char f;
extern char i;
extern char commacounter;
extern char lat[13];
extern char longitude[13];
//extern char *token;
extern char N_or_s;
extern char E_or_W;

extern char speed[20];
 
 

//function to get longitude and latitude in degrees
float toDegree(float L);

//function to convert angles from degrees to radians
float toRadian(float value);

//function to get the distance between two points in meters
float getDistance(float long1,float lat1,float long2,float lat2);

// function to get longtitude  and latitude
void GPS_read();




#endif