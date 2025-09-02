#include <stdio.h>
#include <string.h>

// Registros válidos exactos
int esRegistroValido(const char *reg) {
    return (strcmp(reg, "Ax") == 0 ||
            strcmp(reg, "Bx") == 0 ||
            strcmp(reg, "Cx") == 0 ||
            strcmp(reg, "Dx") == 0);
}

// Quita coma final si existe, p.ej. "Ax," -> "Ax". Devuelve 1 si quitó, 0 si no había.
int quitaComaFinal(char *s) {
    size_t len = strlen(s);
    if (len > 0 && s[len - 1] == ',') {
        s[len - 1] = '\0';
        return 1;
    }
    return 0;
}


int main(){
    const char *ruta = "a.asm";
    FILE *f = fopen(ruta, "r");
    if (!f) {
        perror("No se pudo abrir instrucciones.txt");
        return 1;
    }

    char linea[256];
    int numLinea = 0;
    int huboError = 0;
    int okCount = 0;

    while (fgets(linea, sizeof(linea), f)) {
        numLinea++;

        // Copia para tokenizar (strtok modifica la cadena)
        char work[256];
        strcpy(work, linea);

        // Delimitadores: espacios, tabs, retornos, nueva línea. ¡No coma!
        char *tok = strtok(work, " \t\r\n");
        if (!tok) {
            // línea vacía: continuamos
            continue;
        }

        // Clasificar instrucción (MAYÚSCULAS estrictas)
        int instruccion3 = 0; // MOV/ADD/SUB/MUL/DIV
        int instruccion2 = 0; // INC/DEC

        if (strcmp(tok, "MOV") == 0 || strcmp(tok, "ADD") == 0 ||
            strcmp(tok, "SUB") == 0 || strcmp(tok, "MUL") == 0 ||
            strcmp(tok, "DIV") == 0) {
            instruccion3 = 1;
        } else if (strcmp(tok, "INC") == 0 || strcmp(tok, "DEC") == 0) {
            instruccion2 = 1;
        } else {
            printf("Error en línea %d: Instrucción desconocida (%s). Use MAYÚSCULAS.\n",
                   numLinea, tok);
            huboError = 1;
            continue; // seguimos con la siguiente línea
        }

        // Leer registro (puede venir "Ax" o "Ax,")
        char *regTok = strtok(NULL, " \t\r\n");
        if (!regTok) {
            printf("Error en línea %d: Falta el registro.\n", numLinea);
            huboError = 1;
            continue;
        }

        // ¿Trae coma pegada al final?
        int teniaComaPegada = quitaComaFinal(regTok);

        // Validar nombre del registro
        if (!esRegistroValido(regTok)) {
            printf("Error en línea %d: Registro inválido (%s). Use Ax/Bx/Cx/Dx.\n",
                   numLinea, regTok);
            huboError = 1;
            continue;
        }

        if (instruccion2) {
            // INC/DEC: NO deben llevar coma ni valor
            if (teniaComaPegada) {
                printf("Error en línea %d: %s %s NO debe llevar coma.\n",
                       numLinea, tok, regTok);
                huboError = 1;
                continue;
            }
            // No debe haber más tokens (nada después del registro)
            char *extra = strtok(NULL, " \t\r\n");
            if (extra) {
                printf("Error en línea %d: %s %s NO debe llevar valor ni coma extra.\n",
                       numLinea, tok, regTok);
                huboError = 1;
                continue;
            }

            printf("Línea %d válida: %s %s\n", numLinea, tok, regTok);
            okCount++;
            continue;
        }

        // Instrucciones de 3 elementos
        char *valorTok = NULL;

        if (teniaComaPegada) {
            // Caso "Ax," <- el siguiente token debe ser el valor
            valorTok = strtok(NULL, " \t\r\n");
            if (!valorTok) {
                printf("Error en línea %d: Falta el valor numérico después de la coma.\n",
                       numLinea);
                huboError = 1;
                continue;
            }
        } else {
            // No traía la coma pegada al registro; el siguiente token debe ser ","
            char *comaTok = strtok(NULL, " \t\r\n");
            if (!comaTok || strcmp(comaTok, ",") != 0) {
                printf("Error en línea %d: Falta la coma entre el registro y el valor.\n",
                       numLinea);
                huboError = 1;
                continue;
            }
            // Luego debe venir el valor
            valorTok = strtok(NULL, " \t\r\n");
            if (!valorTok) {
                printf("Error en línea %d: Falta el valor numérico después de la coma.\n",
                       numLinea);
                huboError = 1;
                continue;
            }
        }

        // Validar que el valor sea solo dígitos (entero no negativo), a la antigua
        int esNumero = 1;
        for (int i = 0; valorTok[i] != '\0'; i++) {
            if (valorTok[i] < '0' || valorTok[i] > '9') {
                esNumero = 0;
                break;
            }
        }
        if (!esNumero) {
            printf("Error en línea %d: Valor no numérico (%s). Use solo dígitos 0-9.\n",
                   numLinea, valorTok);
            huboError = 1;
            continue;
        }

        // No debe haber nada más
        char *extra = strtok(NULL, " \t\r\n");
        if (extra) {
            printf("Error en línea %d: Sobran elementos al final de la instrucción.\n",
                   numLinea);
            huboError = 1;
            continue;
        }

        printf("Línea %d válida: %s %s, %s\n", numLinea, tok, regTok, valorTok);
        okCount++;
    }

    if (!huboError) {
        printf("Todas las líneas son válidas.\n");
    } else {
        printf("Validación terminada: %d línea(s) válida(s), hubo errores en otras líneas.\n",
               okCount);
    }

    fclose(f);
    return 0;
}
