/* This program allows the analysis of VicRoad traffic accident reports. 
* The data inputted into the program takes accident location, date and time to 
* further additional analysis. 
* Created by: Chamira Balasuriya (cbalassuriya@student.unimelb.edu.au)
* For COMP20005 - September 2017  
*
* C programming is fun! 
*/


#include <stdio.h>  
#include <math.h> 
#include <string.h> 


/* A list of constants that shall be utilised in the program. MAXVAL indicates
* the maximum number of records that can be inputted into the program. PI
* is the value used for calculations for stage one. REF_LAT and REF_LON are the 
* longitude and latitude of Melbourne Central which is taken as the reference 
* point.   
*/

#define MAXVAL 99  
#define PI 3.14159 
#define REF_LAT -37.810592 
#define REF_LON 144.963123 
#define HAVERSINE_CONSTANT 6371

int reader (int unique_id[], double location_lon[], double location_lat[], 
int day[], int month[], int year[], int time[], char d[][10]);   
double toRadian (double x); 	 
double chordlength (double location_lon, double location_lat);  
double angle_distance (double x);  
void stage_one (int unique_id[], double location_lon[], double location_lat[], 
int day[], int month[], int year[], int time[]);   
double distance_calc (double location_lon, double location_lat); 
void stage_two (int a, int unique_id[], double location_lon[], 
double location_lat[]); 
int distance_graph (double x); 
void stage_three(int a, char d[][10]);    
int max_7_ints (int a, int b, int c, int d, int e, int f, int g);  
int max_2_ints (int a, int b); 
int stage_printer(int x); 



int main (int argc, char *argv[]) {
	int stage_number=1, accident, unique_id[MAXVAL], day[MAXVAL], month[MAXVAL], 
	year[MAXVAL], time[MAXVAL]; 
	double location_lon[MAXVAL], location_lat[MAXVAL];   
	char d[MAXVAL][10]; 

		stage_number = stage_printer(stage_number); 

		accident = reader(unique_id, location_lon, location_lat, day, month, 
		year, time,d);  
		stage_one(unique_id,location_lon,location_lat,day,month,year,time);

		stage_number = stage_printer(stage_number+1); 
 		stage_two(accident, unique_id, location_lon, location_lat); 
 		
 			
		stage_number = stage_printer(stage_number+1); 
		stage_three(accident, d); 
}

/* This function has the role of printing the headings for the different stages  
*/

int stage_printer(int stage_number) {
	int i; 

	if (stage_number==1) {
		printf("Stage 1\n");
	 	for (i=0; i<10; i++) {
	 		printf("="); 
	 	} 
	 	printf("\n"); 
	} 
	if (stage_number==2) {
		printf("Stage 2\n"); 
 		for (i=0; i<10; i++) {
	 		printf("="); 
	 	} 
	 	printf("\n");   
	} 
	if (stage_number==3) {
		printf("\nStage 3\n"); 
 		for (i=0; i<10; i++) {
	 		printf("="); 
	 	} 
	 	printf("\n");  
	}
	return stage_number; 
}

/* This function is the reader function that will have the role of reading the
* input data and saving data into its corresponding arrays   
*/

int reader (int unique_id[], double location_lon[], double location_lat[], 
		int day[], int month[], int year[], int time[], char d[][10]) {

		int i=0;  

		while(scanf("%d %lf %lf %d/%d/%d %d %s \n", &unique_id[i], 
		&location_lon[i], &location_lat[i], &day[i], &month[i], &year[i], 
		&time[i], &d[i][0]) != EOF) {
		
		i++; 

		} 
	
	return i;	
}   

/* This is the function for the first stage of the program. This has the 
* purpose of presenting the raw data from the reader function of the first 
* accident in a organised manner. 
*/

void stage_one (int unique_id[], double location_lon[], double location_lat[], 
	int day[], int month[], int year[], int time[]) {

	printf("Accident: #%d\n", unique_id[0]); 

	printf("Location: <%0.6f, %0.6f>\n", location_lon[0], location_lat[0]); 

	printf("Date: %d/%d/%d\n", day[0], month[0], year[0]);  

	printf("Time: %02d\n", time[0]); 

	printf("Distance to reference: %05.2f\n", distance_calc(location_lon[0],
		location_lat[0])); 
	printf("\n"); 
	return; 
} 

/* This function for the second stage has input parameters of; the total
* number of accidents, unique id's, longitude and latitude of each accident
*/

void stage_two (int accidents, int unique_id[], double location_lon[], double 
	location_lat[]) {

	double distance;
	int counter=0, print=0;   

	while (counter < accidents) {
		distance = distance_calc(location_lon[counter],location_lat[counter]); 

		printf("Accident: #%d, distance to reference: %05.2lf |", 
		unique_id[counter], distance);  

		print = distance_graph(distance);

		counter++; 
	}

	return; 

} 

/* This function for the final stage has the input parameters; total number 
* of accidents and the days of the accidents that were read through the 
* reader function 
*/ 

void stage_three(int accidents, char d[][10]) {
	int counter=0,i=0, max_accidents=0, sun_counter=0, mon_counter=0, 
	tues_counter=0, wed_counter=0, thur_counter=0, fri_counter=0, sat_counter=0;  
	
	char days_of_week [] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday",
	"Saturday"}; 


/* The code below is a while loop that compares the days of the raw data, with 
* the declared char variables above. Each time there is a match, it adds a 
* value (+1) to that particular days counter. The loops ends upon reaching
* variable 'a' which corresponds to the number of accidents (inputted in the 
* main function). 
*/	

	while(counter < accidents) {
		for(i=0; i<accidents; i++) {
			if(strcmp(days_of_week[0], d[i]) == 0) {
				sun_counter++; 
			}  
			if(strcmp(days_of_week[1], d[i]) == 0) {
				mon_counter++; 
			} 
			if(strcmp(days_of_week[2], d[i]) == 0) {
				tues_counter++; 
			} 
			if(strcmp(days_of_week[3], d[i]) == 0) {
				wed_counter++; 
			}
			if(strcmp(days_of_week[4], d[i]) == 0) {
				thur_counter++; 
			} 
			if(strcmp(days_of_week[5], d[i]) == 0) {
				fri_counter++; 
			} 
			if(strcmp(days_of_week[6], d[i]) == 0) {
				sat_counter++; 
			} 
			counter++; 
		}  
	}

/* The values for the accident counters for the particular days are put through
* the following function which returns the greatest value. 
*/
	max_accidents = max_7_ints(sun_counter,mon_counter,tues_counter, wed_counter
	,thur_counter,fri_counter,sat_counter); 

/* Prints out the total number of accidents, which has been processed by the 
* reader function in previous steps.
*/ 

	printf("Number of accidents: %d\n", accidents);  

/* Loop compares the maximum number of accidents against the accident counters
* for each individual day which was worked out earlier. It then runs through 
* a series of if statements in a loop to determine which day had the most 
* accidents. 
*/ 

	for(i=0; ;i++) {
		if(max_accidents == sun_counter) {
			printf("Day of week with the most accidents: %s (%d accident(s))\n"
			, days_of_week[0], sun_counter); 
			break; 
		}
		if(max_accidents == mon_counter) {
			printf("Day of week with the most accidents: %s (%d accident(s))\n"
			, days_of_week[1], mon_counter); 
			break; 
		}
		if(max_accidents == tues_counter) {
			printf("Day of week with the most accidents: %s (%d accident(s))\n"
			, days_of_week[2], tues_counter); 
			break; 
		}
		if(max_accidents == wed_counter) {
			printf("Day of week with the most accidents: %s (%d accident(s))\n"
			, days_of_week[3], wed_counter); 
			break; 
		}
		if(max_accidents == thur_counter) {
			printf("Day of week with the most accidents: %s (%d accident(s))\n"
			, days_of_week[4], thur_counter); 
			break; 
		}
		if(max_accidents == fri_counter) {
			printf("Day of week with the most accidents: %s (%d accident(s))\n"
			, days_of_week[5], fri_counter); 
			break; 
		}
		if(max_accidents == sat_counter) {
			printf("Day of week with the most accidents: %s (%d accident(s))\n"
			, days_of_week[6], sat_counter); 
			break; 
		}
	}

	return; 
}  


/* This function takes in seven inputs (for the seven days) and returns the 
* greatest value. The values are essentially the counter variables that have
* counted the number of accidents in a particular day. 
*/

int max_7_ints (int a, int b, int c, int d, int e, int f, int g) { 

	int max_ab = max_2_ints(a,b); 
	int max_cd = max_2_ints(c,d);
	int max_ef = max_2_ints(e,f);   
	int max_efg = max_2_ints (max_ef, g); 
	int max_abcd = max_2_ints(max_ab, max_cd);  
	int max_abcdefg = max_2_ints(max_efg, max_abcd);  

	return max_abcdefg; 
} 

/* A basic function that takes two integers as inputs, compares them and returns
the one of higher value. 
*/

int max_2_ints (int a, int b) {
	int max; 
	if (a > b) {
		max = a; 
	} else {
		max = b; 
	}
	return max; 
}

/* The following functions are related to the visual graph of Stage 2.
*/

int distance_graph (double distance) {
	int i=0, distance_graph=0;   


/* A for loop is used to print out the lines and corresponding '+'. 
* values are rounded using the 'ceil' function that is standard to C
*/ 

	for(i=1; i<=ceil(distance); i++) {
		if (i % 10 == 0 && i != 0) {
			printf("+"); 
		} else {
			printf("-"); 
		}
	}
	printf("\n"); 
	return distance_graph; 
}

/* The following functions are related to the calculation section of Stage 1.
* These calculations are based on the Haversine formula. 
* The function below converts the longitude and latitude values into radians.
*/

double toRadian (double x) {
	double toRadian; 
	toRadian = x*(PI/180); 

	return toRadian; 
} 

/* This function calculates the chord length between the chosen accident and 
* the reference point. The inputs of longitude and latitude are taken and
* converted into radians using the function defined above. 
*/ 

double chordlength (double location_lon, double location_lat) {
	double chordlength; 

	chordlength = pow((sin(toRadian(location_lat- REF_LAT)/2)),2) + 
	cos(toRadian(REF_LAT)) * cos(toRadian(location_lat)) * 
	pow((sin(toRadian(location_lon - REF_LON)/2)),2); 

	return chordlength;   

}  

/* This function takes the chordlength and calculates the angle distance by
* taking the chordlength as the input parameter from the function above. 
*/

double angle_distance (double chordlength) {
	double angle_distance; 

	angle_distance = 2*atan2(sqrt(chordlength), sqrt(1 - chordlength)); 

	return angle_distance; 
}

/* This is the final function for the calculations, which calculates the 
* distance between the location of the accident and the reference point
*/

double distance_calc (double location_lon, double location_lat) {
	double chord_length, ang_dist, dist; 

	
	chord_length = chordlength(location_lon,location_lat); 

	ang_dist = angle_distance(chord_length); 

	dist = HAVERSINE_CONSTANT * ang_dist; 


	return dist;
}

