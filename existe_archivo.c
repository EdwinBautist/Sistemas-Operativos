#include <stdio.h>
#include <string.h>

int main(){

    char nombre_archivo[10];
    printf("Ingresa el nombre del archivo: \n");
    fgets(nombre_archivo, sizeof(nombre_archivo), stdin);

    // Eliminar el carácter de salto de línea que agrega fgets
    nombre_archivo[strcspn(nombre_archivo, "\n")] = 0;

    printf("Archivo a verificar existencia: %s\n", nombre_archivo);

    //PROCESO PARA ABRIR ARCHIVO
    // tiene que ser un apuntador afuercitas 
    FILE *abrir_archivo;
    abrir_archivo = fopen(nombre_archivo, "r"); // r para abrir en modo lectura

    if (abrir_archivo == NULL) { // es decir, NO EXISTE EN EL DIRECTORIO
        printf("El archivo %s no existe, o no se pudo abrir \n", nombre_archivo);


        // aqui dentro deberiamos tener un ciclo para que no se cierre 
        return 1; // salir con error, termina el programa 
    }
    printf("Contenido del archivo '%s':\n\n", nombre_archivo);
    char lineas_archivo[10];
    //ciclo para leer el contenido del archivo
        while (fgets(lineas_archivo, sizeof(lineas_archivo), abrir_archivo)) {
        printf("%s", lineas_archivo);  // imprimir línea tal cual
    }

    fclose(abrir_archivo);  // cerrar archivo
}