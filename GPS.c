#include "GPS.h"
# include "UART .h"
#include <string.h>
#include<math.h>
#include<stdlib.h>
float currentlong,currentlat;
char i=0;
char GPS_Logname[]="$GNRMC,";
char valid_data;
char f=1;
//char finished=0,flag=0;
char commacounter=0;
char lat[13];
char longitude[13];
//char *token;
char N_or_s;
char E_or_W;

char speed[20];

char a;

float toDegree(float L){
	int degree = (int)L/100;
	float minutes = L - (float) degree*100;
	return (degree + (minutes/60));
}

float toRadian(float value){
	return (value * PI /180);
}

float getDistance(float long1,float lat1,float long2,float lat2){
	float long1_rad = toRadian(toDegree(long1));
	float long2_rad = toRadian(toDegree(long2));
	float lat1_rad = toRadian(toDegree(lat1));
	float lat2_rad = toRadian(toDegree(lat2));
	
	float a = pow(sin((lat1_rad - lat2_rad)/2),2) + cos(lat1_rad) * cos(lat2_rad) * pow(sin((long1_rad - long2_rad)/2),2);
	float c = 2 * atan2(sqrt(a),sqrt(1-a));
	return EARTH_RADIUS * c;
}

void GPS_read(){
	commacounter=0;
	f=1;
	do{
			a=	UART2_readchar();
			if(a!=GPS_Logname[i]){
					i=0;
					continue;
			} 
			i++;
	}while(i!=7);
	
	while(1){
		if(f)	{
			char g=UART2_readchar();
			if(g==',')
			commacounter++;
		}
		
		switch(commacounter){
				case 1:
					{
				  valid_data=UART2_readchar();
				  f=1;
				break;}
	    	case 2 :
					{
	      	get_array(lat);		
          commacounter++;	f=0;
				  break;}
	    	case 3:{
		  	  N_or_s= UART2_readchar();
	        f=1;
				  break;}	
		    case 4:{
				  get_array(longitude);	
			    commacounter++;f=0; break;}
	    	case 5:{
			    E_or_W= UART2_readchar();
		    	f=1;
				  break;}
				case 6:
					{
			    get_array(speed);	
				  commacounter++;f=0;break;}
		}
				
		if(commacounter==7) break;				
						
						
		}
	
	if(valid_data=='A'){
		string_out(lat);
		string_out("\n");
		string_out(longitude);
		string_out("\n");
	if( N_or_s=='N')		currentlat=atof(lat);
			else     currentlat=-atof(lat);
	
			 
		
	if(E_or_W=='E')	currentlong=atof(longitude);
	else     currentlong=-atof(longitude);
		
	}
}
		
		
		
		


















