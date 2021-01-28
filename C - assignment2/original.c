
#include <stdio.h> 
#include <string.h> 
#include <math.h> 

#define MAXVAL 99  
#define ORIGIN_X 000.0
#define ORIGIN_Y 000.0


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

int stage_one_part1 (speaker_t S[]);   
void stage_two (int s_lines, speaker_t S[], coord_t P[]);   
void stage_three (speaker_t S[]);  
double calc_distance (double x, double y);  
double calc_distance (double x, double y);
double individual_sound_level (double distance, double soundlevel);  
double power_calculation (double individual_soundlevel);  


int main () { 
	int i=0, s_lines=0;  
	speaker_t S[MAXVAL];  
	coord_t P[MAXVAL]; 
 

	printf("\nStage 1\n"); 
	printf("=========\n"); 
	s_lines = stage_one_part1(&S[i]);   

	printf("\nStage 2\n"); 
	printf("=========\n"); 
	stage_two(s_lines, &S[i], &P[i]);   

	printf("\nStage 3\n"); 
	printf("=========\n");  
	stage_three(&S[i]); 

} 

int stage_one_part1 (speaker_t S[]) {
	int i=0, s_lines=0;    
	double distance, individual_soundlevel, power, total, final; 


	while(scanf("S %lf %lf %lf\n", &S[i].x_coord, &S[i].y_coord, &S[i].sound_level) == 3) { 
		s_lines++; 	 
		i++; 
	}
	

	for(i=0; i<s_lines; i++) {
		distance = calc_distance(S[i].x_coord, S[i].y_coord); 
		individual_soundlevel = individual_sound_level(distance, S[i].sound_level);  
		power = power_calculation(individual_soundlevel);  
		total= total + power; 
	} 

	final = 10*log10(total); 

	printf("Number of loudspeakers: %d\n", s_lines);  
	printf("Sound level at (%5.2f , %5.2f) : %2.2f\n", ORIGIN_X, ORIGIN_Y, final);  

	return s_lines; 
} 


void stage_two (int s_lines, speaker_t S[], coord_t P[]) {
	int p_i=0, p_lines=0, s_i=0;     
	double distance, individual_soundlevel, power,total, final; 

	while(scanf("P %lf %lf\n", &P[p_i].x_coord, &P[p_i].y_coord) == 2) { 
		p_i++;  
		p_lines++;  
	}   


	while(scanf("S %lf %lf %lf\n", &S[s_i].x_coord, &S[s_i].y_coord, &S[s_i].sound_level) == 3) { 
		s_i++; 
	}

	for(p_i=0; p_i<p_lines; p_i++) {
		for(s_i=0; s_i<s_lines; s_i++) {
			distance = calc_distance( (S[s_i].x_coord - P[p_i].x_coord) , (S[s_i].y_coord - P[p_i].y_coord) ) ;   
			individual_soundlevel = individual_sound_level(distance, S[s_i].sound_level);  
			power = power_calculation(individual_soundlevel);  
			total= total + power;
		} 
		final = 10*log10(total); 
		printf("Sound level at (%f , %f) : %f \n", P[p_i].x_coord, P[p_i].y_coord, final );    
		total = 0; 
	}

} 

void stage_three (speaker_t S[]) {
	int s_lines = 4, counter=0, s_i=0; 
	double x_coord=4, y_coord=4; 

	while(scanf("S %lf %lf %lf\n", &S[s_i].x_coord, &S[s_i].y_coord, &S[s_i].sound_level) == 3) { 
		s_i++; 
	} 

	for(x)


} 

double calc_distance (double x, double y) {
	double result; 

	result = sqrt((pow(x,2)) + (pow(y,2)));  

	return result; 
}  

double individual_sound_level (double distance, double soundlevel) {
	double finalsoundlevel; 

	finalsoundlevel = soundlevel + 20*(log10(1/distance));  

	return finalsoundlevel; 
}

double power_calculation (double individual_soundlevel) {
	double power_calculation;

	power_calculation = pow(10, (individual_soundlevel/10));

	return power_calculation; 
}

