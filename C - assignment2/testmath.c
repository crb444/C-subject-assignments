#include <stdio.h> 
#include <math.h>

double calc_distance (double x, double y);  
double sound_level (double distance, double soundlevel); 


int main () {
	double x,y,c, distance, finalsoundlevel; 

	x = 72.0-51.0; 
	y = 190.0-201.0; 
	c = 95;   

	distance = calc_distance(x,y);  

	finalsoundlevel = sound_level(distance, c);  

	printf("\nDistaance is: %f\n", distance); 

	printf("Final sound level: %f\n", finalsoundlevel);  

}

double calc_distance (double x, double y) {
	double result; 

	result = sqrt((pow(x,2)) + (pow(y,2)));  

	return result; 
} 

double sound_level (double distance, double soundlevel) {
	double finalsoundlevel; 

	finalsoundlevel = soundlevel + 20*(log10(1/distance));  

	return finalsoundlevel; 
}

