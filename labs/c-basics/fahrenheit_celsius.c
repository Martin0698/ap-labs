#include <stdio.h>
#include <stdlib.h>
   /*int LOWER  ;       lower limit of table 
   int UPPER  ;      upper limit 
   int STEP   ;       step size 
   */

/* print Fahrenheit-Celsius table */

int main(int argc, char *argv[])
{
    if(argc == 4){
        int fahr;
    
        int LOWER  = atoi(argv[1]);
        int UPPER = atoi(argv[2]);
        int STEP = atoi(argv[3]);

        for (fahr = LOWER; fahr <= UPPER; fahr = fahr + STEP)
        printf("Fahrenheit: %3d, Celcius: %6.1f\n", fahr, (5.0/9.0)*(fahr-32));

         
    }
    else if(argc == 2){
		
        int fahr = atoi(argv[1]);
		printf("Fahrenheit: %3d, Celcius: %6.1f\n", fahr, (5.0/9.0)*(fahr-32));

	}

    
    return 0;
}
