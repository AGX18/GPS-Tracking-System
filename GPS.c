#include<math.h>
#include<stdlib.h>
float currentlong,currentlat;
char i=0;
char GPS_Logname[]="$GNRMC,";
char valid_data;
char f=1;
char commacounter=0;
char lat[13];
char longitude[13];
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
	//check if we recieve thr right log name
	do{
			a=	UART2_readchar();
			if(a!=GPS_Logname[i]){
			i=0;
			continue;// recieve the data again till all chars of log name recieved right
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
				case 1: // recieve A or V
				{
				  valid_data=UART2_readchar();
				  f=1;// to recieve char again
				break;}
	    	case 2 : // to recieve a latitude
					{
	      	get_array(lat);		//to store latitude in char array
                   commacounter++;	
	                 f=0;   //to not to recive a char after this step as we recieved a comma in get_arrray and comma counter is already incremented
				  break;}
	    	case 3:{   // to recieve N or S
		  	  N_or_s= UART2_readchar();
	        f=1;       //to recieve char again
				  break;}	
		    case 4:{  //to recieve a longitude
				  get_array(longitude);	  //to store  longitude in char array   
			    commacounter++;
				f=0;    //to not to recive a char after this step as we recieved a comma in get_arrray and comma counter is already incremented
				break;}
	    	case 5:{  // to recieve E or W
			    E_or_W= UART2_readchar();
		    	f=1;   //to recieve char again
				  break;}
				case 6:   // to recieve speed
					{    
			    get_array(speed);	 //to store speed in char array
				  commacounter++;
					f=0; // //to not to recive a char after this step as we recieved a comma in get_arrray and comma counter is already incremented
					break;}
		}
				
		if(commacounter==7) break;				
						
						
		}
	
	if(valid_data=='A'){
		string_out(lat);
		string_out("\n");
		string_out(longitude);
		string_out("\n");
	if( N_or_s=='N')	currentlat=atof(lat);   //to convert latitude(char array) into float
			else     currentlat=-atof(lat);
	
			 
		
	if(E_or_W=='E')	currentlong=atof(longitude);    //to convert longitude(char array) into float
	else     currentlong=-atof(longitude);
		
	}
}
		
	

