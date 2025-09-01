#ifndef LEER_ARCHIVO_H
#define LEER_ARCHIVO_H

#include <stdio.h>

static inline void leerArchivo(const char *nombre_archivo) {

    char lineas_archivo[10]; // maximo nueve caracteres mas fin de cadena \0

    FILE *abrir_archivo = fopen(nombre_archivo, "r"); // Abrir en modo lectura

    if (abrir_archivo == NULL) { 
        printf("El archivo %s no existe, o no se pudo abrir\n", nombre_archivo);
        return;
    }

    printf("\nContenido del archivo %s:\n\n", nombre_archivo);


    while (fgets(lineas_archivo, sizeof(lineas_archivo), abrir_archivo)) {
        printf("%s", lineas_archivo);
    }
printf("\n"); // para que no se vea asi: ADD, Bx$, qguegue el salto de linea y ya 
    fclose(abrir_archivo);
}

#endif 
