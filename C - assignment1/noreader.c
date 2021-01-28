#include <stdio.h>  
#include <math.h> 

#define MAXVAL 99  
#define PI 3.14159 
#define REF_LAT -37.810592 
#define REF_LON 144.963123

int reader (int unique_id[], double location_lon[], double location_lat[], int day[], int month[], int year[], int time[], char d[][10]);   
double toRadian (double x); 	 
double chordlength (double x, double y);  
double angle_distance (double x);  
int stage_one (int a, double b, double c, int d, int e, int f, int g);   
double dist (double x, double y) ; 
int stage_two (double b, double c);  
int vis (double x); 

// what if the reader was in the main and thus variables can be used ANYWHERE 


int main (int argc, char *argv[]) {
	int i=0,x, y, stageone, stagetwo, unique_id[MAXVAL], day[MAXVAL], month[MAXVAL], year[MAXVAL], time[MAXVAL]; 
	double location_lon[MAXVAL], location_lat[MAXVAL];   
	char d[MAXVAL][10]; 

			printf("\nStage 1\n");
			printf("==========\n"); 

			while(scanf("%d %lf %lf %d/%d/%d %d %s \n", &unique_id[i], &location_lon[i], &location_lat[i], &day[i], &month[i], &year[i], &time[i], &d[i][0]) != EOF) {
				if(i==0) {
					x = stage_one(unique_id[i], location_lon[i], location_lat[i], day[i], month[i], year[i], time[i]);  
					i++; 
				}
				if(i==11) {
					y = stage_two(location_lon[i], location_lat[i]); 
				}
			} 

			printf("\nStage 1\n");
			printf("==========\n"); 

		
			printf("\nStage 2\n"); 
 			printf("==========\n");  

 			stagetwo = stage_two(location_lon[i], location_lat[i]); 
 		

} 

int reader (int unique_id[], double location_lon[], double location_lat[], int day[], int month[], int year[], int time[], char d[][10]) {
	int i=0, x; 

		while(scanf("%d %lf %lf %d/%d/%d %d %s \n", &unique_id[i], &location_lon[i], &location_lat[i], &day[i], &month[i], &year[i], &time[i], &d[i][0]) != EOF) {
		x = stage_one(unique_id[i], location_lon[i], location_lat[i], day[i], month[i], year[i], time[i]);  
		i++; 
		} 
	
	return i;	
}   


int stage_two (double b, double c) {
	double distance;
	int print;   

	distance = dist(b,c); 
	print = vis(distance);

	printf("Distance to reference: %2.2lf |%d\n", distance, print);   

	return 0; 

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


int stage_one (int a, double b, double c, int d, int e, int f, int g) {
	printf("Accident: #%d\n", a); 
	printf("Location: <%lf , %lf> \n", b , c); 
	printf("Date: %d/%d/%d\n", d, e, f);  
	printf("Time: %d\n", g); 
	printf("Distance to reference: %2.2lf\n", dist(b,c)); 
	printf("\n"); 
	return 0; 
}


double toRadian (double x) {
	double toRadian; 
	toRadian = x*(PI/180); 

	return toRadian; 
} 

double chordlength (double location_lon, double location_lat) {
	double chordlength; 

	chordlength = pow((sin(toRadian(location_lat- REF_LAT)/2)),2) + cos(toRadian(REF_LAT)) * cos(toRadian(location_lat)) * pow((sin(toRadian(location_lon - REF_LON)/2)),2); 

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

