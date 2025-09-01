#include <stdio.h>
#include <string.h>
#include "colors.h"

int main() { 
    char texto[50];
    char copia_texto[50];
    char *delimitador = " \n";
    char *token;
    char nombre_archivo[20];
    int comando_valido;
    
    do {
        printf("$ ");
        fgets(texto, sizeof(texto), stdin);
        strcpy(copia_texto, texto);

        if (strcmp(texto, "salir\n") == 0 || strcmp(texto, "Salir\n") == 0 || strcmp(texto, "SALIR\n") == 0) {
            printf(CIAN "Saliendo...\n");
            return 1;
        } else {
            comando_valido = 0;
            token = strtok(copia_texto, delimitador);
            
            // Primer token debe ser "ejecutar"
            if (token != NULL && strcmp(token, "ejecutar") == 0) { 
                // Segundo token debe ser el nombre del archivo
                token = strtok(NULL, delimitador);
                
                if (token != NULL) {
                    // Verificar extensión .asm
                    char *punto = strrchr(token, '.');
                    if (punto != NULL && strcmp(punto, ".asm") == 0) {
                        printf("Archivo válido: %s\n", token);
                        comando_valido = 1;
                         
                        // Aquí puedes procesar el archivo...
                        
                    } else {
                        printf("Error: El archivo debe tener extensión .asm\n");
                    }
                } else {
                    printf("Error: Falta el nombre del archivo\n");
                }
                
                // Verificar si hay tokens adicionales
                if (strtok(NULL, delimitador) != NULL) {
                    printf("Advertencia: Demasiados argumentos\n");
                }
            }
            
            if (!comando_valido && token != NULL) {
                printf("Instrucción no válida\n");
            }
        }
    } while (1);
    
    return 0;
}