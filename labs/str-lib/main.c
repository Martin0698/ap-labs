#include <stdio.h>
#include "strlib.c"


int main(int argc, char *argv[]) {
    
    if(argc == 4){

    
      
         if(strcmp(argv[1], "-add")== 0)
         {
             
            int tm = mystrlen(argv[2]);
            char *nuevo= mystradd(argv[2], argv[3]);

            printf("tamanio inicial: %i \n", tm);
            printf("string concatenado: %s \n", nuevo);
         }

         else if (strcmp(argv[1], "-find")== 0)
         {
             printf("El string se encontro [%s]   en la posicion [%d]\n", argv[3],mystrfind(argv[2],argv[3]));
  
         }
         

    }
    
    else
    {
        printf("tiene un exceso o menos entradas de las requeridas \n");
    }
    
    return 0;
}
