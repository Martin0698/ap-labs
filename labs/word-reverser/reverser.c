#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void invertir(char *caracteres, int tamanno){
    int ptamano= tamanno;
    char *invertido= malloc( tamanno* sizeof(char));
    for (int i = tamanno-1; i >= 0; i--)
    {
        invertido[tamanno-(i+1)]= caracteres[i];
        /* code */
    }

    for (int i = 0; i < ptamano; i++)
    {
        printf("%c", invertido[i]);
        /* code */
    }
    printf("\n");
    
    
}

int main(){
    int caracter;
    char letras[60];
    int tamano= 0;

    while ((caracter=getchar()) != EOF)
    {
        /* code */
        
        if (caracter != '\n')
        {
            letras[tamano++]= caracter;
            /* code */
            //printf("%c", caracter);

        }
        else
        {
            /* code */
            invertir(letras, tamano);
            tamano=0;
        }
        
    }
    
    return 0;
}

