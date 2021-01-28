#include <stdio.h>  

int order (int a, int b, int c, int d, int e, int f, int g);  
int max_2_ints (int a, int b); 

int main () {
	int result, a,b,c,d,e,f,g; 

	a=2, b=3, c=6, d=9, e=10, f=13, g=16;   

	result = order(a,b,c,d,e,f,g);  

	printf("%d\n", result); 

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