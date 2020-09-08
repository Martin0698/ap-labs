#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int mystrlen(char *str){
    int tamano=0;

    while (str[tamano] != '\0')
    {
        tamano++;
    }
    
    return tamano;
}

char *mystradd(char *origin, char *addition){

    char *nuevo = malloc(mystrlen(origin)+ mystrlen(addition));

    int tamanio1 = mystrlen(origin);

    int tamanio2 = mystrlen(addition);

    for (int i = 0; i < tamanio1; i++)
    {
        nuevo[i] = origin[i];
    }

    int i = 0;

    for (int j = tamanio1; j < tamanio2 + tamanio1; j++)
    {
        nuevo[j] = addition[i];
        
        i++;
    }
    return nuevo;
    
    
}

int mystrfind(char *origin, char *substr){
    int limit = mystrlen(substr);

    int taminioorigen = mystrlen(origin);
    
    int counter = 0;
    
    for(int i = 0;i < taminioorigen;i++){

      if(*(origin+i) == *(substr+counter)){
        counter++;
      }
      else {
        i = i - counter + 1;
        counter = 0;
      }
      if(counter==limit) return i - counter + 1;
    }
    return -1;
}	
