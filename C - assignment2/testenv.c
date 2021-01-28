// COMPLETING STAGE 2 - calculations  

#include <stdio.h> 
#include <string.h> 
#include <math.h> 

#define MAXVAL 99  
#define ORIGIN_X 0.0
#define ORIGIN_Y 0.0

struct test1 {
	char type[1]; 
	double x_coord;
	double y_coord;
	double sound_level; 
} s_speaker;     


struct test2 {
	char type[1]; 
	double x_coord;
	double y_coord;
} p_speaker;    



void stage_one_part1 (char type[1], double x_coord, double y_coord, double sound_level); 
void stage_two_part1 (char type[1], double x_coord, double y_coord); 
double calc_distance (double x, double y);  
double calc_distance (double x, double y);
double individual_sound_level (double distance, double soundlevel);  
double power_calculation (double individual_soundlevel);  


int main () {


	printf("\nStage 1\n"); 
	printf("=========\n");
	stage_one_part1(&s_speaker.type[1], s_speaker.x_coord, s_speaker.y_coord, s_speaker.sound_level );  	 
	
	printf("\nStage 2\n"); 
	printf("=========\n");
	stage_two_part1(&p_speaker.type[1], p_speaker.x_coord, p_speaker.y_coord);  	
} 

void stage_one_part1 (char type[1], double x_coord, double y_coord, double sound_level) {
	int s_lines=0; 
	char comp_s[] = "S";   
	double distance, total=0, individual_soundlevel, power, final; 

	
	while(scanf("%s %lf %lf %lf\n", &s_speaker.type[1], &s_speaker.x_coord, &s_speaker.y_coord, &s_speaker.sound_level) != EOF) {

		if(strcmp(comp_s, &s_speaker.type[1]) == 0) {
			distance = calc_distance(s_speaker.x_coord, s_speaker.y_coord); 
			individual_soundlevel = individual_sound_level(distance, s_speaker.sound_level);  
			power = power_calculation(individual_soundlevel);  
			total= total + power;
			s_lines++;   
		}
		break; 
	}

	final = 10*log10(total);


	printf("Number of loudspeakers: %d\n", s_lines); 
	printf("Sound level: %3.2f dB\n", final); 
	printf("\n"); 
} 

void stage_two_part1 (char type[1], double x_coord, double y_coord) {
	int p_lines=0; 
    char comp_p[] = "P";  
    double distance; 
	
	while(scanf("%s %lf %lf \n", &p_speaker.type[1], &p_speaker.x_coord, &p_speaker.y_coord) != EOF) {
		if(strcmp(comp_p, &p_speaker.type[1]) == 0) {
			printf("%f\n", p_speaker.x_coord);  
			printf("%f\n", p_speaker.y_coord);
			p_lines++;   
			distance = calc_distance(p_speaker.x_coord, p_speaker.y_coord); 
			printf("%f\n", distance); 
		}
	}

	// printf("Number of loudspeakers: %d\n", p_lines);  

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

