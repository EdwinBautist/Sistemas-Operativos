#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(){

    char cadena[10];
    char buffer[100];
    fgets(buffer, sizeof(buffer), stdin); // Lee del teclado hasta 99 caracteres + '\0'
    printf("%s\n", buffer);
    fputs(buffer, stdout); // Escribe el contenido del buffer en pantalla
}