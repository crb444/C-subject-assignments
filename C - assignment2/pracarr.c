/* This program allows the analysis of Loudspeaker sound patterns over a given 
* region. The data inputted into the program correspond to individual locations 
* of loudspeakers and their sound levels. Both are then utilised to calculate 
* the aggregate sound level at the origin and a number of other observation 
* points. Finally, the program calculates the overall sound level of various 
* coordinates in a given region, using this information to draw a sound map. 
*
* Created by: Chamira Balasuriya (cbalassuriya@student.unimelb.edu.au)
* For COMP20005 - September 2017  
* Last edited: Wednesday 18th October 2017 
*
* C programming is fun! 
*/

#include <stdio.h> 
#include <string.h> 
#include <math.h> 

/* A list of constants that will be utilised in the program. MAXVAL indicates 
* the maximum number of loudspeakers and observation points specified. ORIGIN_X 
* and ORIGIN_Y are the coordinates of the origin point. 
*/

#define MAXVAL 99   
#define ORIGIN_X 0.0
#define ORIGIN_Y 0.0

/* Definition of structures that will be used in the following program. The 
* first shall be used for the data for the loudspeakers, the second shall be 
* used for the observation points, while the last is to be used to specify 
* the initial coordinates of the grid, which shall be used in a loop to  
* construct the soundmap. 
*/ 

typedef struct {
	double x_coord;
	double y_coord;
	double sound_level; 
} speaker_t;  

typedef struct {
	double x_coord;
	double y_coord;
} coord_t;           

typedef struct {
	double x_coord;
	double y_coord;
} region_t; 

int stage_printer(int x); 
int stage_one (speaker_t S[]);   
void stage_two (int s_lines, speaker_t S[], coord_t P[]);   
void stage_three (int s_lines, speaker_t S[]);  
void stage_four (int s_lines, speaker_t S[]);  
double calc_distance (double x, double y);  
double calc_distance (double x, double y);
double individual_sound_level (double distance, double soundlevel);  
double power_calculation (double individual_soundlevel);  


int main (int argc, char *argv[]) { 

	int i=0, s_lines=0, stage_number=1;  

	speaker_t S[MAXVAL];  

	coord_t P[MAXVAL]; 
 
	stage_number = stage_printer(stage_number);
	s_lines = stage_one(&S[i]);   

	stage_number = stage_printer(stage_number+1); 
	stage_two(s_lines, &S[i], &P[i]);   

	stage_number = stage_printer(stage_number+1); 
	stage_three(s_lines, &S[i]);  

	stage_number = stage_printer(stage_number+1); 
	stage_four(s_lines, &S[i]);  

} 

/* This function has the role of printing out the headings for each of the 
* stages. 
*/

int stage_printer(int stage_number) {

	int i; 

	if (stage_number==1) {
		
		printf("\nStage %d\n", stage_number);
	 	
	 	for (i=0; i<10; i++) {
	 		printf("="); 
	 	} 

	 	printf("\n"); 
	} 

	if (stage_number==2) {
		
		printf("\nStage %d\n", stage_number); 
 		
 		for (i=0; i<10; i++) {
	 		printf("="); 
	 	} 

	 	printf("\n");   
	} 

	if (stage_number==3) {
		
		printf("\nStage %d\n", stage_number);
 		
 		for (i=0; i<10; i++) {
	 		printf("="); 
	 	}

	 	printf("\n");  
	} 

	if (stage_number==4) {
		
		printf("\nStage %d\n", stage_number);
 		
 		for (i=0; i<10; i++) {
	 		printf("="); 
	 	} 

	 	printf("\n");  
	}

	return stage_number; 
}

/* This is the function for the first stage. It has the role of inputting 
* loudspeaker data into a struct array and calculating the aggregate sound level 
* at the origin, whilst also counting the number of loudspeakers in this 
* particular set of data. This nummber is crucial for later stages of the 
* program. 
*/

int stage_one (speaker_t S[]) {

	int i=0, s_lines=0;    

	double distance, individual_soundlevel, power, total, final; 


	while(scanf("S %lf %lf %lf\n", &S[i].x_coord, &S[i].y_coord, 
		&S[i].sound_level) == 3) {  

		s_lines++; 	 
		i++; 

	}
	
/* This part of stage one calculates the aggregate sound level at the origin 
* by utilising functions that calculate distance and individual sound levels.
* The 'total' variable adds up all the contributions of the individual 
* loudspeakers, while the variable 'final' calculates the log.  
*/

	for(i=0; i<s_lines; i++) {
		
		distance = calc_distance(S[i].x_coord, S[i].y_coord); 
		
		individual_soundlevel = individual_sound_level(distance, 
			S[i].sound_level);   


/* The condition below makes sure that if the individual sound level is 0, it is 
* not added into the aggregate sound level equation. This is due to the fact 
* that a base to the exponent of 0 will yield 1 - which will give incorrect 
* values. 
*/ 

		if (individual_soundlevel == 0 ) {
			break; 
		}
		
		power = power_calculation(individual_soundlevel);  
		
		total= total + power; 
	} 

	final = 10*log10(total); 

	printf("Number of loudspeakers: %02d\n", s_lines);  

	printf("Sound level at (%05.1f, %05.1f): %2.2f dB\n", ORIGIN_X, ORIGIN_Y, 
		final);  

	return s_lines; 
} 

/* This function has the role of calculating the aggregate sound level for 
* different observation points. 
*/

void stage_two (int s_lines, speaker_t S[], coord_t P[]) {
	
	int p_i=0, p_lines=0, s_i=0;     
	
	double distance, individual_soundlevel, power,total, final; 

/* The following code reads in the values of the observation points and saves
* them into the relevant struct array. 
*/	
	while(scanf("P %lf %lf\n", &P[p_i].x_coord, &P[p_i].y_coord) == 2) { 
		
		p_i++;  
		p_lines++;  

	}   


	while(scanf("S %lf %lf %lf\n", &S[s_i].x_coord, &S[s_i].y_coord, 
		&S[s_i].sound_level) == 3) { 

		s_i++; 

	}

/* The loop cycles through each of the observation points and calculates the 
* aggregate sound level at those points for each of the loudspeakers. 
*/

	for(p_i=0; p_i<p_lines; p_i++) {
		
		for(s_i=0; s_i<s_lines; s_i++) {
			
			distance = calc_distance( (S[s_i].x_coord - P[p_i].x_coord) , 
				(S[s_i].y_coord - P[p_i].y_coord) ) ;   
			
			individual_soundlevel = individual_sound_level(distance, 
				S[s_i].sound_level);   

			if (individual_soundlevel == 0 ) {
				break; 
			}
			
			power = power_calculation(individual_soundlevel);  
			
			total= total + power;
		} 
		
		final = 10*log10(total); 
		
		printf("Sound level at (%06.2f, %06.2f) : %2.2f dB \n", P[p_i].x_coord, 
			P[p_i].y_coord, final );    
		
		total = 0; 
	}

} 


/* This stage calculates the overall sound level of a given region of 
* (312m x 312m) at every 4m grid point, using the loudspeakers specified in 
* Stage 1. The stage counts the numbers of points sampled and then calculates 
* the percentage of points that have a sound level equal to or less than 55 dB. 
*/ 

void stage_three (int s_lines, speaker_t S[]) {
	
	int counter=0, s_i=0, points_sampled=0; 
	
	double distance, individual_soundlevel, power,total, final, percentage; 
	
/* Declaration of variables into struct region_t.
*/	

	region_t stage_three; 

	stage_three.x_coord = 4.0;
	
	stage_three.y_coord = 4.0; 


	while(scanf("S %lf %lf %lf\n", &S[s_i].x_coord, &S[s_i].y_coord, 
		&S[s_i].sound_level) == 3) { 

		s_i++; 
	
	}

/* The following loop determines aggregate sound levels by starting from the 
* bottom left corner of the grid at (4,4) and then increasing in y-increments 
* of 4. After reading a y-value of 308, the next x-value is tested and the 
* process is repeated. An ongoing counter increases If the sound level is 55 db 
* or less, which is utilised to calculate the percentage of points from the 
* total number of points sampled that fall into this condition. 
*/

	while(stage_three.x_coord  <= 308.0) {
		
		for(stage_three.y_coord = 4.0; stage_three.y_coord <= 308.0; 
			stage_three.y_coord = stage_three.y_coord + 4.0) {
			
			for(s_i=0; s_i<s_lines; s_i++) {
				
				distance = calc_distance( (S[s_i].x_coord - stage_three.x_coord)
				 , (S[s_i].y_coord - stage_three.y_coord) ) ;   
				
				individual_soundlevel = individual_sound_level(distance, 
					S[s_i].sound_level);   

				if (individual_soundlevel == 0 ) {
					break; 
				}

				power = power_calculation(individual_soundlevel);  
				
				total= total + power; 
			}  

			final = 10*log10(total); 


			if(final <= 55.0) {
				counter++;
			} 

			points_sampled++; 

 			total=0;    

		}

		stage_three.x_coord = stage_three.x_coord + 4.0;

	} 

	percentage = (double) counter/points_sampled *100; 

	printf("%d points sampled\n", points_sampled); 
	
	printf("%04d points (%05.2f%%) have sound level <= 55 db \n", counter, 
		percentage); 

	printf("\n"); 
}  

/* The following is the function for stage four which has the role of analysing 
* region of space starting from x = 2.0 to x = 310.0 and from y = 4.0 to 
* y = 308.0. X-values are incremented by increments of + 4, while Y-values are 
* incremented by values of - 8. As a result, the aggregate sound level for a  
* total of 78 x 39 points is calculated and depending on the level, a character 
* is mapped. 
*/

void stage_four (int s_lines, speaker_t S[]) {
	
	int s_i=0; 

	double distance, individual_soundlevel, power,total, final;  
	
/* Declaration of variables into struct region_t.
*/	
	region_t stage_four; 
	
	stage_four.x_coord = 2.0;
	
	stage_four.y_coord = 308.0; 
	
	while(scanf("S %lf %lf %lf\n", &S[s_i].x_coord, &S[s_i].y_coord, 
		&S[s_i].sound_level) == 3) { 

		s_i++;

	}


/* As mapping is completed from top to bottom, this loop starts at the top left 
* with (x,y) coordinates (2.0, 308.0). After calculation of the aggregate sound 
* level, the x-values are then incremented by + 4 until 310.0. After 
* calculations for x-value 310.0, the y-value increments by - 8. 
*/

	while(stage_four.y_coord >= 4) {
		
		for(stage_four.x_coord = 2.0; stage_four.x_coord <= 310.0; 
			stage_four.x_coord = stage_four.x_coord+ 4.0) {

			for(s_i=0; s_i<s_lines; s_i++) {
				
				distance = calc_distance( (S[s_i].x_coord - stage_four.x_coord), 
					(S[s_i].y_coord - stage_four.y_coord ) ) ;  

				individual_soundlevel = individual_sound_level(distance, 
					S[s_i].sound_level);   

				if (individual_soundlevel == 0 ) {
					break; 
				}

				power = power_calculation(individual_soundlevel);  
				
				total= total + power; 
			}  

			final = 10*log10(total); 

/* The following conditional prints out the relevant character on the sound map 
* depending on the value of the calculated aggregate sound level for the 
* particular set of coordinates being tested. 
*/ 

			if(final >= 100.0) {
				
				printf("+"); 
			
			} else if (final < 100.00 && final >= 90) {
				
				printf(" "); 
			
			} else if (final < 90.00 && final >= 80) {
				
				printf("8");
			
			} else if (final < 80.00 && final >= 70) {
				
				printf(" ");
			
			} else if (final < 70.00 && final >= 60) {
				
				printf("6"); 
			
			} else if (final < 60.00 && final >= 56) {
				
				printf(" ");
			
			} else if (final <= 55.00 && final >= 0) {
				
				printf("-"); 

			} 

/* Key step to make sure the values are reset after calculations for one set 
* of coordinates or else values shall keep adding on top of one another. 
*/ 
			total=0; 

			final=0; 

		}

/* The code below is what determines transition into the next line, where there 
* is an incrementation of the y-value by - 8. 
*/ 		
		printf("\n"); 

		stage_four.y_coord  = stage_four.y_coord - 8.0; 

	} 
	printf("\n"); 
}

/* This function calculates the distance between a given (x,y) coordinate and
* the origin or also between two (x,y) coordinates. 
*/

double calc_distance (double x, double y) {
	
	double result; 

	result = sqrt((pow(x,2)) + (pow(y,2)));  

	return result; 
}  

/* This function calculates the individual sound level, through inputs of the 
* distance and the soundlevel of the loudspeaker.
*/ 

double individual_sound_level (double distance, double soundlevel) {
	
	double finalsoundlevel; 

	finalsoundlevel = soundlevel + 20*(log10(1/distance));   

/* This condition makes that thhat is if the finalsoundlevel yields a negative 
* number, it is just equated to 0. 
*/ 

	if (finalsoundlevel < 0) {
		
		finalsoundlevel = 0; 
	}

	return finalsoundlevel; 
}

/* This function has the role of performing the power function that is outlined
* in the aggregate sound level equation. 
*/ 

double power_calculation (double individual_soundlevel) {
	
	double power_calculation;

	power_calculation = pow(10, (individual_soundlevel/10));

	return power_calculation; 
}

