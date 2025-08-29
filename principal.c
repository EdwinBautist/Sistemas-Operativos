#include <stdio.h>
#include <string.h>
#include <regex.h>


int main(){ 
    char texto[50];
    char copia_texto[50];
    char *delimitador=" ";
    char *token;
    char nombre_archivo[20];





do{
    printf("Ingresa una opcion: ");
    printf("ejecutar nombre_proceso.asm\n");
    printf("$ ");
    fgets(texto, sizeof(texto), stdin);
    strcpy(copia_texto, texto);

if (strcmp(texto, "ejecutar a.asm\n")==0){
    printf("Admitido, iniciamos ejecucion\n");

    token = strtok(copia_texto, delimitador);

    while (token != NULL) { //hace el despliegue de los tokens
 
        /*if (token == "a.asm")
        {
            printf("%s\n", token);
        }*/
        printf("%s\n", token);
        printf("%c\n", *token);

       token = strtok(NULL, delimitador); //funciona con el while
    }

}
else if (strcmp(texto, "salir\n")==0){
    printf("Saliendo...\n");
}
//else if ((strcmp(texto, "ejecutar a.asm\n")==1) && (strcmp(texto, "salir\n")==1)){
else { printf("Intruccion invalida\n");
}

}while(strcmp(texto, "salir\n") != 0);

}