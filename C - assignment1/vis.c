#include <stdio.h>  

#include <stdio.h>  
#include <math.h> 

double toRadian (double x); 
double chordlength (double x, double y); 
double angle_distance (double x); 
double dist (double x, double y);  
int vis (double x); 


#define PI 3.14159 
#define REF_LAT -37.810592 
#define REF_LON 144.963123


int main () {
	double d, e,f,g; 
	int print; 

	d = dist(145.060689, -37.810373);  
	e = 15.45;  
	f = 22.05; 
	g = 28.94;

	printf("Distance to reference: %2.2lf |", d);  
	print = vis(d);  
	printf("\n");  
	printf("Distance to reference: %2.2lf |", e);  
	print = vis(e);  
	printf("\n");  
	printf("Distance to reference: %2.2lf |", f);  
	print = vis(f);  
	printf("\n");  
	printf("Distance to reference: %2.2lf |", g);  
	print = vis(g);  
	printf("\n"); 


}


int vis (double x) {
	int i=0, vis=0, counter=0;  

	for(i=0; i<= x; i++) {
		if (counter % 9 == 0 && counter != 0) {
			printf("+"); 
			counter = 0;  
		} else {
			printf("-"); 
			counter ++; 
		}
	}
	return vis; 
}

double toRadian (double x) {
	double toRadian; 
	toRadian = x*(PI/180); 

	return toRadian; 
} 

double chordlength (double location_lon, double location_lac) {
	double chordlength; 

	chordlength = pow((sin(toRadian(location_lac - REF_LAT)/2)),2) + cos(toRadian(REF_LAT)) * cos(toRadian(location_lac)) * pow((sin(toRadian(location_lon - REF_LON)/2)),2); 

	return chordlength;   

}  

double angle_distance (double chordlength) {
	double angle_distance; 

	angle_distance = 2*atan2(sqrt(chordlength), sqrt(1 - chordlength)); 

	return angle_distance; 
}

double dist (double x, double y) {
	double chord_length, ang_dist, dist; 

	
	chord_length = chordlength(x,y); 

	ang_dist = angle_distance(chord_length); 

	dist = 6371 * ang_dist; 


	return dist;
}
