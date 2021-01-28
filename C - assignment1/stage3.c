#include <stdio.h>  
#include <math.h> 
#include <string.h> 

#define MAXVAL 99  
#define PI 3.14159 
#define REF_LAT -37.810592 
#define REF_LON 144.963123

int reader (int unique_id[], double location_lon[], double location_lat[], int day[], int month[], int year[], int time[], char d[][10]);   
double toRadian (double x); 	 
double chordlength (double x, double y);  
double angle_distance (double x);  
void stage_one (int unique_id[], double location_lon[], double location_lat[], int day[], int month[], int year[], int time[]);   
double dist (double x, double y) ; 
void stage_two (int a, int unique_id[], double location_lon[], double location_lat[]); 
int vis (double x); 
void stage_three(int a, char d[][10]);    
int order (int a, int b, int c, int d, int e, int f, int g);  
int max_2_ints (int a, int b); 



int main (int argc, char *argv[]) {
	int accident, unique_id[MAXVAL], day[MAXVAL], month[MAXVAL], year[MAXVAL], time[MAXVAL]; 
	double location_lon[MAXVAL], location_lat[MAXVAL];   
	char d[MAXVAL][10]; 

			printf("\nStage 1\n");
			printf("==========\n"); 
	
			accident = reader(unique_id, location_lon, location_lat, day, month, year, time,d);  
			stage_one(unique_id,location_lon,location_lat,day,month,year,time);
		
			printf("\nStage 2\n"); 
 			printf("==========\n");  

 			stage_two(accident, unique_id, location_lon, location_lat); 
 		
 			printf("\nStage 3\n");
 			printf("==========\n");

 			stage_three(accident, d); 

} 

int reader (int unique_id[], double location_lon[], double location_lat[], int day[], int month[], int year[], int time[], char d[][10]) {
	int i=0;  

		while(scanf("%d %lf %lf %d/%d/%d %d %s \n", &unique_id[i], &location_lon[i], &location_lat[i], &day[i], &month[i], &year[i], &time[i], &d[i][0]) != EOF) {
		//x = stage_one(unique_id[i], location_lon[i], location_lat[i], day[i], month[i], year[i], time[i]);  
		i++; 
		} 
	
	return i;	
}   


void stage_two (int a, int unique_id[], double location_lon[], double location_lat[]) {
	double distance;
	int counter=0, print=0;   

	while (counter < a) {
		distance = dist(location_lon[counter],location_lat[counter]); 
		printf("Accident: %d, distance to reference: %05.2lf |", unique_id[counter], distance);  
		print = vis(distance);
		counter++; 
	}



	return; 

} 

void stage_three(int a, char d[][10]) {
	int counter=0,i=0, max_accidents=0, sun_counter=0, mon_counter=0, tues_counter=0, wed_counter=0, thur_counter=0, fri_counter=0, sat_counter=0;  
	char sun[] = "Sunday"; 
	char mon[] = "Monday"; 
	char tues[] = "Tuesday";   
	char wed[] = "Wednesday";  
	char thur[] = "Thursday";  
	char fri[] = "Friday"; 
	char sat[] = "Saturday"; 
	

	while(counter < a) {
		for(i=0; i<a; i++) {
			if(strcmp(sun, d[i]) == 0) {
				sun_counter++; 
			}  
			if(strcmp(mon, d[i]) == 0) {
				mon_counter++; 
			} 
			if(strcmp(tues, d[i]) == 0) {
				tues_counter++; 
			} 
			if(strcmp(wed, d[i]) == 0) {
				wed_counter++; 
			}
			if(strcmp(thur, d[i]) == 0) {
				thur_counter++; 
			} 
			if(strcmp(fri, d[i]) == 0) {
				fri_counter++; 
			} 
			if(strcmp(sat, d[i]) == 0) {
				sat_counter++; 
			} 
			counter++; 
		}  
	}

	max_accidents = order(sun_counter,mon_counter,tues_counter, wed_counter,thur_counter,fri_counter,sat_counter); 


	printf("Number of accidents: %d\n", a);  

	for(i=0; ;i++) {
		if(max_accidents == sun_counter) {
			printf("Day of the week with most accidents: %s (%d accidents(s))\n", sun, sun_counter); 
			break; 
		}
		if(max_accidents == mon_counter) {
			printf("Day of the week with most accidents: %s (%d accidents(s))\n", mon, mon_counter); 
			break; 
		}
		if(max_accidents == tues_counter) {
			printf("Day of the week with most accidents: %s (%d accidents(s))\n", tues, tues_counter); 
			break; 
		}
		if(max_accidents == wed_counter) {
			printf("Day of the week with most accidents: %s (%d accidents(s))\n", wed, wed_counter); 
			break; 
		}
		if(max_accidents == thur_counter) {
			printf("Day of the week with most accidents: %s (%d accidents(s))\n", thur, thur_counter); 
			break; 
		}
		if(max_accidents == fri_counter) {
			printf("Day of the week with most accidents: %s (%d accidents(s))\n", fri, fri_counter); 
			break; 
		}
		if(max_accidents == sat_counter) {
			printf("Day of the week with most accidents: %s (%d accidents(s))\n", sat, sat_counter); 
			break; 
		}
	}

	return; 
}  




int order (int a, int b, int c, int d, int e, int f, int g) { 

	int max_ab = max_2_ints(a,b); 
	int max_cd = max_2_ints(c,d);
	int max_ef = max_2_ints(e,f);   
	int max_efg = max_2_ints (max_ef, g); 
	int max_abcd = max_2_ints(max_ab, max_cd);  
	int max_abcdefg = max_2_ints(max_efg, max_abcd);  
	return max_abcdefg; 


} 

int max_2_ints (int a, int b) {
	int max; 
	if (a > b) {
		max = a; 
	} else {
		max = b; 
	}
	return max; 
}

int vis (double x) {
	int i=0, vis=0;   

	for(i=1; i<=ceil(x); i++) {
		if (i % 10 == 0 && i != 0) {
			printf("+"); 
		} else {
			printf("-"); 
		}
	}
	printf("\n"); 
	return vis; 
}


void stage_one (int unique_id[], double location_lon[], double location_lat[], int day[], int month[], int year[], int time[]) {
	printf("Accident: #%d\n", unique_id[0]); 
	printf("Location: <%0.6f , %0.6f> \n", location_lon[0], location_lat[0]);  // print out doubles use f
	printf("Date: %d/%d/%d\n", day[0], month[0], year[0]);  
	printf("Time: %02d\n", time[0]); 
	printf("Distance to reference: %05.2f\n", dist(location_lon[0],location_lat[0])); 
	printf("\n"); 
	return; 
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

