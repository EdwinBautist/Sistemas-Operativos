#include <stdio.h>
#include <string.h>
#include "interprete.h"

int main()
{

    char texto[50];
    char copia_texto[50];
    int bandera;

    do
    {
        printf("$ ");
        fgets(texto, sizeof(texto), stdin);
        interprete(copia_texto);

    } while (bandera != 1);

    return 0;
}