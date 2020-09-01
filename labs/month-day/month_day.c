#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

bool bisiesto= false;
int c_month[]={0,31,59,90,120,151,181,212,243,273,304,334,365};
int cb_month[]={0,31,60,91,121,152,182,213,244,274,305,335,366};


/* month_name:  return name of n-th month */
char *month_name(int n) {

   static char *name[] = {
       "Illegal month",
       "January", "February", "March",
       "April", "May", "June",
       "July", "August", "September",
       "October", "November", "December"
   };

   return (n < 1 || n > 12) ? name[0] : name[n];
}


/* month_day function's prototype*/
void month_day(int year, int yearday, int *pmonth, int *pday){
    
    
    for (int i = 0; i < 12; i++)
    {
        if(bisiesto){
            if(yearday >= cb_month[i] && yearday <= cb_month[i+1]){
                *pday= yearday - cb_month[i];
                *pmonth= i+1;
                printf("%s %d, %d", month_name(*pmonth),*pday,year);
                break;
            }
        }
        else
        {
            if(yearday >= c_month[i] && yearday <= c_month[i+1]){
                *pday= yearday - c_month[i];
                *pmonth= i+1;
                printf("%s %d, %d", month_name(*pmonth),*pday,year);
                break;
            }
        }
        
    }  
}



int main(int argc, char *argv[]) {

    if(argc == 3){
        int year= atoi(argv[1]);
        int day= atoi(argv[2]);
        

        if ((year%4 ==0  && year%100 != 0) || year%400 ==0)
        {
            if(day >=0 && day <= 366)
            {
                bisiesto=true;
                int *pmonth = malloc(sizeof(int));
                int *pday = malloc(sizeof(int));
                month_day(year,day, pmonth, pday);

            }
            else
            {
                printf("Día ingresado fuera del rango 0-366 \n");
            }
            
        }
        else
        {
            if(day >=0 && day <= 365){
                int *pmonth = malloc(sizeof(int));
                int *pday = malloc(sizeof(int));
                month_day(year,day, pmonth, pday);

            }
            else
            {
                printf("Día ingresado fuera del rango 0-365 \n");
            }
            
        }
        
        
    }
    else
    {
        printf("Ingrese los valores requeridos \n");
    }
    
    return 0;
}
