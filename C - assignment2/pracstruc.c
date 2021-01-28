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

void stage_one_part1 (int s_lines,  char type[1], double x_coord, double y_coord, double sound_level); 
double calc_distance (double x, double y);  
double individual_sound_level (double distance, double soundlevel);  
double power_calculation (double individual_soundlevel);   
int reader (int lines); 


int main () {
	int s_lines=0, p_lines=0;
	char comp_s[] = "S";   
	char comp_p[] = "P";

	while(scanf("%s %lf %lf %lf\n", &s_speaker.type[1], &s_speaker.x_coord, &s_speaker.y_coord, &s_speaker.sound_level) != EOF) {
		if(strcmp(comp_s, &s_speaker.type[1]) == 0) {		
			s_lines++; 
			stage_one_part1(s_lines, &s_speaker.type[1], s_speaker.x_coord, s_speaker.y_coord, s_speaker.sound_level );  	 
			}
		if(strcmp(comp_p, &s_speaker.type[1]) == 0) {		
			p_lines++; 	
			}  
		}  

	printf("Stage 1\n"); 
	printf("=========\n");
	

	printf("\n"); 
	printf("S Lines read: %d\n", s_lines); 
	printf("P Lines read: %d\n", p_lines);
} 

void stage_one_part1 (int s_lines,  char type[1], double x_coord, double y_coord, double sound_level) {
	printf("%f\n", x_coord); 	  
}


