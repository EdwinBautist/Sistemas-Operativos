#include<stdio.h>

int main()

{
    char ejecutar[20];
 
    printf("Ingresa una opción:\n");
    printf("\nejecutar nombre_archivo.asm\n");
    printf("\nsalir\n");
    fgets(ejecutar, sizeof(ejecutar), stdin);



    printf("%s\n", ejecutar);
    
    return 0;
}   
