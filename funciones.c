#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "funciones.h"

int total_polinomios = 0;

polinomios *crear_polinomio()
{
    int i, j, band = 0; // Esta función hace uso de banderas
    polinomios *pol;
    int tot_p, tot_term;

    total_polinomios = 0;

    do
    {
        // Pregunta cuántos polinomios se desea crear
        printf("Introduzca la cantidad de polinomios a crear: ");
        scanf("%d", &tot_p);
        system("cls");

        // Condición para establecer el número de polinomios que acepta la memoria
        // Si ya está llena la memoria suelta advertencia
        if ((total_polinomios + tot_p) > 10)
        {
            printf("Memoria llena, no se pueden guardar esos polinomios\nEspacio libre: %d Polinomios", (10 - total_polinomios));
            system("pause");
            system("cls");
        }
        else
        {
            band = 1;                                               // Establezco la bandera como verdadero
            pol = (polinomios *)malloc(tot_p * sizeof(polinomios)); // Reservo la memoria para guardar os polinomios
            for (i = 0; i < tot_p; i++)
            {
                // Pido los polinomios
                // Pido la cantidad de coheficientes que se desea y la estructura de cada término
                printf("Cantidad de Polinomios %d: ", (i + 1));
                scanf("%d", &tot_term);
                system("cls");

                pol[i].tot_term = tot_term;
                pol[i].term = (terminos *)malloc(tot_term * sizeof(terminos));

                for (j = 0; j < tot_term; j++)
                {
                    printf("Coeficiente %d: ", (j + 1));
                    scanf("%f", &pol[i].term[j].coef);

                    printf("Exponente %d: ", (j + 1));
                    scanf("%d", &pol[i].term[j].exp);
                    system("cls");
                }
                system("cls");

                total_polinomios++;
            }
        }
    } while (band != 1); // Repetir el ciclo mientras la bandera sea Falso

    // Ordenamiento Burbuja

    for (i = 0; i < tot_p; i++)
    {
        for (int k = 0; k < pol[i].tot_term; k++)
        {
            for (j = 0; j < pol[i].tot_term - 1; j++)
            {
                if (pol[i].term[j].exp < pol[i].term[j + 1].exp)
                {
                    terminos temporal;
                    temporal.coef = pol[i].term[j].coef;
                    temporal.exp = pol[i].term[j].exp;
                    pol[i].term[j].exp = pol[i].term[j + 1].exp;
                    pol[i].term[j].coef = pol[i].term[j + 1].coef;
                    pol[i].term[j + 1].exp = temporal.exp;
                    pol[i].term[j + 1].coef = temporal.coef;
                }
            }
        }
    }

    printf("--------------------------------------------------\n");
    printf("*              POLINOMIOS CREADOS                *\n");
    printf("--------------------------------------------------\n\n");

    FILE *archivo;
    archivo = fopen("archivo.txt", "w+"); // Se abre un archivo en modo de lectura y escritura

    for (i = 0; i < tot_p; i++)
    {
        // El número de polinomio
        printf("%d)  ", (i + 1));

        // Escribo mis polinomios en el archivo

        for (j = 0; j < pol[i].tot_term; j++)
        {
            if (j == (pol[i].tot_term - 1))
            {
                printf("%.3f X^%d\n", pol[i].term[j].coef, pol[i].term[j].exp);
                fprintf(archivo, "%f,%d\n", pol[i].term[j].coef, pol[i].term[j].exp);
            }
            else
            {
                printf("%.3f X^%d + ", pol[i].term[j].coef, pol[i].term[j].exp);
                fprintf(archivo, "%f,%d,", pol[i].term[j].coef, pol[i].term[j].exp);
            }
        }
    }
    fclose(archivo); // Cierro el archivo
    printf("\n\nPolinomios creados en archivo de manera exitosa\n\n");

    return pol;
}

polinomios *obtener_polinomios()
{
    polinomios *pol;

    printf("--------------------------------------------------\n");
    printf(" Obteniendo Polinomio\n");
    printf("--------------------------------------------------\n\n");
    FILE *archivo;
    int i, j, ext, tot_exp, tot_coef;
    int exp[10][50], tot_term[10];
    float coef[10][50];
    char datos[10][100];
    // Abrimos el archivo

    archivo = fopen("archivo.txt", "r");

    if (archivo != NULL)
    {
        total_polinomios = 0;

        while (feof(archivo) == 0) // Hasta donde llega el fichero si no es 0
        {
            // Leer cadenas desde el archivo
            fgets(datos[total_polinomios], 100, archivo);

            /**
             *  ----------------------------------------------------------------------------
             *
             * ----------------------------------------------------------------------------------------
             **/

            char *tok1 = strtok(datos[total_polinomios], ",");
            if (tok1 != NULL)
            {
                ext = 0;
                tot_exp = 0;
                tot_coef = 0;
                while (tok1 != NULL)
                {
                    if (ext == 0)
                    {
                        tot_term[total_polinomios] = atoi(tok1); // atoi convierte cadena a entero
                    }
                    else if (ext % 2 == 0)
                    {
                        exp[total_polinomios][tot_exp] = atoi(tok1);
                        tot_exp++;
                    }
                    else
                    {
                        coef[total_polinomios][tot_coef] = atoi(tok1);
                        tot_coef++;
                    }

                    ext++;
                    tok1 = strtok(NULL, ","); // Para que la cadena continue dividiendose se pone en los argumentos NULL
                }
            }

            if (tot_term[total_polinomios] > 0)
            {
                total_polinomios++;
            }
        }
        fclose(archivo);

        pol = (polinomios *)malloc(total_polinomios * sizeof(polinomios));
        for (i = 0; i < total_polinomios; i++)
        {
            pol[i].term = (terminos *)malloc(tot_term[i] * sizeof(terminos));
            pol[i].tot_term = tot_term[i];

            for (j = 0; j < tot_term[i]; j++)
            {
                pol[i].term[j].coef = coef[i][j];
                pol[i].term[j].exp = exp[i][j];
            }
        }
        printf("Polinomio Obtenido!\n\n");
    }
    else
    {
        // Advertencia en caso de que no haya archivo
        printf("No hay ningun archivo\n\n");
        return NULL;
    }

    /**
     * ------------------------------------------------------------
     *         Mostramos los polinomios de la memoria
     * ------------------------------------------------------------
     **/

    printf("--------<<Polinomios Creados>---------------\n");
    for (i = 0; i < total_polinomios; i++)
    {
        printf("%d)  ", (i + 1));
        for (j = 0; j < pol[i].tot_term; j++)
        {
            if (j == (pol[i].tot_term - 1))
            {
                printf("%.3f X^%d\n", pol[i].term[j].coef, pol[i].term[j].exp);
            }
            else
            {
                printf("%.3f X^%d + ", pol[i].term[j].coef, pol[i].term[j].exp);
            }
        }
    }
    printf("\n\n");

    return pol;
}

void imprime_polinomios(polinomios *pol)
{
    printf("┌----------------------------------------------|\n");
    printf("|              POLINOMIO                       |\n");
    printf("|----------------------------------------------┘\n\n");
    for (int i = 0; i < total_polinomios; i++)
    {
        printf("%d) ", (i + 1));
        for (int j = 0; j < pol[i].tot_term; j++)
        {
            if (j == (pol[i].tot_term - 1))
            {
                printf("%.3f X^%d\n", pol[i].term[j].coef, pol[i].term[j].exp);
            }
            else
            {
                printf("%.3f X^%d + ", pol[i].term[j].coef, pol[i].term[j].exp);
            }
        }
    }

    printf("\n\n");
}

void suma(polinomios *pol)
{
    /**
     * En el caso de esta función las banderas se usan como un switch
     * Cuando la bandera es igual a cero es que los exponentes son diferentes y no suma los coheficientes
     * Caso contrario, la bandera es verdadera, los exponentes son iguales y los coheficientes se suman
     **/

    int i, j, k, band, pol1, pol2;
    polinomios *sum;
    float suma_coef[100];
    int suma_exp[100];
    int total_coef = 0;
    int aun;
    FILE *archivo;
    archivo = fopen("guardar.txt", "w+");

    printf("┌----------------------------------------------|\n");
    printf("|              SUMA DE POLINOMIOS              |\n");
    printf("|----------------------------------------------┘\n\n");

    // Resibe que polinomios se van a sumar
    printf("Ingresa el polinomio a sumar:\n\n");
    printf("Selecciona el polinomio 1: ");
    scanf("%d", &pol1);
    pol1--;

    printf("Selecciona el polinomio 2: ");
    scanf("%d", &pol2);
    pol2--;

    for (i = 0; i < pol[pol1].tot_term; i++)
    {
        band = 0;
        for (j = 0; j < pol[pol2].tot_term; j++)
        {
            if (pol[pol1].term[i].exp == pol[pol2].term[j].exp)
            {
                band = 1;
                // La bandera es verdadera cuando los exponentes de los coheficientes son los mismos
            }
        }
    }

    // Reservo memoria para el resultado de la suma
    sum = (polinomios *)malloc(1 * sizeof(polinomios));

    for (i = 0; i < pol[pol1].tot_term; i++)
    {
        suma_exp[i] = pol[pol1].term[i].exp;
        suma_coef[i] = pol[pol1].term[i].coef;
    }
    total_coef = pol[pol1].tot_term;

    for (i = 0; i < pol[pol2].tot_term; i++)
    {
        band = 0;
        for (j = 0; j < pol[pol1].tot_term; j++)
        {
            if (suma_exp[j] == pol[pol2].term[i].exp)
            {
                suma_coef[j] = suma_coef[j] + pol[pol2].term[i].coef;
                band = 1;
            }
        }
        if (band == 0)
        {
            suma_coef[total_coef] = pol[pol2].term[i].coef;
            suma_exp[total_coef] = pol[pol2].term[i].exp;
            total_coef = total_coef + 1;
        }
    }
    printf("\n\nEl Resultado es:\n");

    for (j = 0; j < total_coef; j++)
    {
        if (j == (total_coef - 1))
        {
            printf("%.3f X^%d\n\n", suma_coef[j], suma_exp[j]);
            fprintf(archivo, "%f,%d\n\n", suma_coef[j], suma_exp[j]);
        }
        else
        {
            printf("%.3f X^%d + ", suma_coef[j], suma_exp[j]);
            fprintf(archivo, "%f,%d + ", suma_coef[j], suma_exp[j]);
        }
    }

    printf("Guardando resultado\n");
    fclose(archivo); // Cierro el archivo
    printf("\n\nPolinomios guardados en archivo de manera exitosa\n\n");
}

void resta(polinomios *pol)
{
    // Igual a la suma pero con diferente signo

    int i, j, k, band, pol1, pol2;
    float resta_coef[100];
    int resta_exp[100];
    int total_coef = 0;
    FILE *archivo;
    archivo = fopen("guardar.txt", "w+");

    printf("┌----------------------------------------------|\n");
    printf("|              RESTA DE POLINOMIOS              |\n");
    printf("|----------------------------------------------┘\n\n");
    printf("Polinomios a restar:\n\n");
    printf("Selecciona el polinomio 1: ");
    scanf("%d", &pol1);
    pol1--;

    printf("Selecciona el polinomio 2: ");
    scanf("%d", &pol2);
    pol2--;

    for (i = 0; i < pol[pol1].tot_term; i++)
    {
        band = 0;
        for (j = 0; j < pol[pol2].tot_term; j++)
        {
            if (pol[pol1].term[i].exp == pol[pol2].term[j].exp)
            {
                band = 1;
            }
        }
    }

    for (i = 0; i < pol[pol1].tot_term; i++)
    {
        resta_exp[i] = pol[pol1].term[i].exp;
        resta_coef[i] = pol[pol1].term[i].coef;
    }
    total_coef = pol[pol1].tot_term;

    for (i = 0; i < pol[pol2].tot_term; i++)
    {
        band = 0;
        for (j = 0; j < pol[pol1].tot_term; j++)
        {
            if (resta_exp[j] == pol[pol2].term[i].exp)
            {
                resta_coef[j] = resta_coef[j] - pol[pol2].term[i].coef;
                band = 1;
            }
        }
        if (band == 0)
        {

            resta_coef[total_coef] = pol[pol2].term[i].coef;
            resta_exp[total_coef] = pol[pol2].term[i].exp;
            total_coef = total_coef + 1;
        }
    }
    printf("\n\nResultado:\n");
    for (j = 0; j < total_coef; j++)
    {
        if (j == (total_coef - 1))
        {
            printf("%.3f X^%d\n\n", resta_coef[j], resta_exp[j]);
            fprintf(archivo, "%f,%d + ", resta_coef[j], resta_exp[j]);
        }
        else
        {
            printf("%.3f X^%d + ", resta_coef[j], resta_exp[j]);
            fprintf(archivo, "%f,%d + ", resta_coef[j], resta_exp[j]);
        }
    }
    printf("Guardando resultado\n");
    fclose(archivo); // Cierro el archivo
    printf("\n\nPolinomios guardados en archivo de manera exitosa\n\n");
}

void multiplicacion_escalar(polinomios *pol)
{
    int opc;
    float val;
    FILE *archivo;
    archivo = fopen("guardar.txt", "w+");

    printf("┌----------------------------------------------|\n");
    printf("|              MULTIPLICACION ESCALAR              |\n");
    printf("|----------------------------------------------┘\n\n");

    printf("Ingresa el polinomio a multiplicar:\n\n");
    printf("Selecciona el polinomio: ");
    scanf("%d", &opc);

    printf("Introduce el valor del escalar: ");
    scanf("%f", &val);
    // Recibo el escalar
    float res;
    printf("\n\nEl Resultado es: \n");
    for (int i = 0; i < pol[(opc - 1)].tot_term; i++)
    {
        res = val * pol[(opc - 1)].term[i].coef;
        printf("%.3f X^%d   ", res, pol[(opc - 1)].term[i].exp);
        fprintf(archivo, "%.3f X^%d   ", res, pol[(opc - 1)].term[i].exp);
    }
    printf("\n\n");
    printf("Guardando resultado\n");
    fclose(archivo); // Cierro el archivo
    printf("\n\nPolinomios guardados en archivo de manera exitosa\n\n");
}

void multiplicacion(polinomios *pol)
{
    int i, j, opc1, opc2;
    float res[100] = {0};
    FILE *archivo;
    archivo = fopen("guardar.txt", "w+");

    printf("┌----------------------------------------------|\n");
    printf("|              MULTIPLICACION DE POLINOMIOS              |\n");
    printf("|----------------------------------------------┘\n\n");

    printf("Selecciona el polinomio 1: ");
    scanf("%d", &opc1);
    opc1--;

    printf("Selecciona el polinomio 2: ");
    scanf("%d", &opc2);
    opc2--;
    system("cls");

    for (i = 0; i < pol[opc1].tot_term; i++)
    {
        for (j = 0; j < pol[opc2].tot_term; j++)
        {
            res[(pol[opc1].term[i].exp + pol[opc2].term[j].exp)] += (pol[opc1].term[i].coef * pol[opc2].term[j].coef);
        }
    }

    printf("\n\nEl Resultado es: \n");
    for (i = 99; i >= 0; i--)
    {
        if (res[i] != 0)
        {
            printf("%.3f X^%d   ", res[i], i);
            fprintf(archivo, "%.3f X^%d ", res[i], i);
        }
    }
    printf("\n\n");
    printf("Guardando resultado\n");
    fclose(archivo); // Cierro el archivo
    printf("\n\nPolinomios guardados en archivo de manera exitosa\n\n");

    printf("\n\n");
}

void division(polinomios *pol)
{
    int i, j, pol1, pol2;
    float division_coef[100];
    int division_exp[100];
    float div_res_coef[100];
    int div_res_exp[100];
    float temp_coef[100];
    int temp_exp[100];
    float residuo_coef;
    int residuo_exp;
    int total = 0;
    int cont = 0;
    FILE *archivo;
    archivo = fopen("guardar.txt", "w+");

    printf("┌----------------------------------------------|\n");
    printf("|              DIVISION DE POLINOMIOS              |\n");
    printf("|----------------------------------------------┘\n\n");

    printf("Ingresa Polinomios a dividir:\n\n");

    printf("Selecciona el polinomio divisor: ");
    scanf("%d", &pol1);
    pol1--;

    printf("Selecciona el polinomio dividendo: ");
    scanf("%d", &pol2);
    pol2--;

    total = pol[pol1].term[0].exp + 1;
    cont = 0;
    i = 0;
    do
    {

        if (i != 0)
        {
            if (division_exp[i - 1] - 1 == pol[pol1].term[cont].exp)
            {
                division_exp[i] = pol[pol1].term[cont].exp;
                division_coef[i] = pol[pol1].term[cont].coef;
                i++;
                cont++;
            }
            else
            {
                division_exp[i] = division_exp[i - 1] - 1;
                division_coef[i] = 0;
                i++;
            }
        }
        else
        {
            division_exp[i] = pol[pol1].term[cont].exp;
            division_coef[i] = pol[pol1].term[cont].coef;
            i++;
            cont++;
        }
    } while (cont < total - 1);

    cont = 0;
    do
    {
        div_res_coef[cont] = division_coef[cont] / pol[pol2].term[0].coef;
        div_res_exp[cont] = division_exp[cont] - pol[pol2].term[0].exp;
        j = 0;
        int k = cont;
        for (i = 0; i < pol[pol2].tot_term; i++)
        {
            temp_coef[k] = division_coef[k] - (div_res_coef[cont] * pol[pol2].term[j].coef);
            if (division_exp[k] == (div_res_exp[cont] + pol[pol2].term[j].exp))
                temp_exp[k] = division_exp[k];
            residuo_coef = temp_coef[k];
            residuo_exp = temp_exp[k];
            division_coef[k] = temp_coef[k];
            division_exp[k] = temp_exp[k];
            j++;
            k++;
        }
        cont++;
    } while (cont < total - 1);
    cont = total - 2;
    printf("\n\nEl Resultado :\n");
    for (j = 0; j < total - 1; j++)
    {
        printf("%.3f X^%d + ", div_res_coef[j], div_res_exp[j]);
    }
    printf("%.3f X^%d + ", div_res_coef[j], div_res_exp[j]);
    for (j = 0; j < pol[pol2].tot_term; j++)
    {
        if (j == (pol[pol2].tot_term - 1))
        {
            printf("%.3f X^%d )\n\n", pol[pol2].term[j].coef, pol[pol2].term[j].exp);
            fprintf(archivo, "%.3f X^%d )\n\n", pol[pol2].term[j].coef, pol[pol2].term[j].exp);
        }
        else
        {
            printf("%.3f X^%d + ", pol[pol2].term[j].coef, pol[pol2].term[j].exp);
            fprintf(archivo, "%.3f X^%d + ", pol[pol2].term[j].coef, pol[pol2].term[j].exp);
        }

        printf("\n\n");
        printf("Guardando resultado\n");
        fclose(archivo); // Cierro el archivo
    }
    printf("\n\nPolinomios guardados en archivo de manera exitosa\n\n");

    printf("\n\n");
}

/*Matrices*/
void leer_matriz(int m, int n, float a[100][100])
{
    printf("Ingresa los datos de la Matriz \n");
    for (int j = 0; j < n; j++)
    {
        for (int i = 0; i < m; i++)
        {
            printf("Ingrese el elemento de la posicion [%d][%d]:", i + 1, j + 1);
            scanf("%f", &a[i][j]);
        }
    }
    printf("\n");
}

void suma_matriz(int m, int n, float a[100][100], float b[100][100], float c[100][100])
{
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            c[i][j] = a[i][j] + b[i][j];
        }
    }
}

void resta_matriz(int m, int n, float a[100][100], float b[100][100], float c[100][100])
{
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            c[i][j] = a[i][j] - b[i][j];
        }
    }
}

void multiescalar_matriz(int m, int n, float a[100][100], float escalar, float c[100][100])
{
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            c[i][j] = escalar * a[i][j];
        }
    }
}

void multiplicacion_matriz(int m, int n, int q, float a[100][100], float b[100][100], float c[100][100])
{
    int x = 0, y = 0, z = 0;
    float suma = 0;
    for (int i = 0; i < m; i++)
    {
        for (int t = 0; t < q; t++)
        {
            for (int j = 0; j < n; j++)
            {
                suma = suma + (a[i][j] * b[x][t]);
                x++;
            }
            c[y][z] = suma;
            x = 0;
            z++;
            suma = 0;
        }
        x = 0;
        z = 0;
        y++;
    }
}

void ampliar_matriz(int m, int n, float a[100][100], float b[100][100])
{
    int x = 0;
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < m; j++)
        {
            b[i][j] = a[i][j];
        }
    }
    for (int i = m; i < m + m - 1; i++)
    {
        for (int j = 0; j < n; j++)
        {
            b[i][j] = a[x][j];
        }
        x++;
    }
}

float determinante_matriz(int m, int n, float b[100][100])
{
    float determinante;
    int i = 0, auxiliar = 0, d1 = 0, d2 = 0, temp = 1;
    if (m == 2 && n == 2)
    {
        d1 = b[0][0] * b[1][1];
        d2 = b[0][1] * b[1][0];
        determinante = d1 - d2;
    }
    else
    {
        // Diagonal 1
        for (int count = 0; count < m; count++)
        {
            for (int j = 0; j < n; j++)
            {
                auxiliar = b[count + i][j];
                temp *= auxiliar;
                i++;
            }
            i = 0;
            d1 += temp;
            temp = 1;
        }
        // Diagonal 2
        i = 0;
        for (int count = 0; count < m; count++)
        {
            for (int j = n - 1; j >= 0; j--)
            {
                auxiliar = b[count + i][j];
                temp *= auxiliar;
                i++;
            }
            i = 0;
            d2 += temp;
            temp = 1;
        }
        determinante = d1 - d2;
    }
    return determinante;
}

float determinante_adjunta(int m, int n, float e[100][100], int signos)
{
    float det_adjunta = 0;
    int i = 0, determinante = 0;
    int aux, d1 = 0, d2 = 0, temp = 1;
    if (m == 2 && n == 2)
    {
        d1 = e[0][0] * e[1][1];
        d2 = e[0][1] * e[1][0];
        det_adjunta = ((signos) * ((d1) - (d2)));
    }
    else
    {
        // Diagonal 1
        for (int count = 0; count < m; count++)
        {
            for (int j = 0; j < n; j++)
            {
                aux = e[count + i][j];
                temp *= aux;
                i++;
            }
            i = 0;
            d1 += temp;
            temp = 1;
        }
        // Diagonal 2
        i = 0;
        for (int count = 0; count < m; count++)
        {
            for (int j = n - 1; j >= 0; j--)
            {
                aux = e[count + i][j];
                temp *= aux;
                i++;
            }
            i = 0;
            d2 += temp;
            temp = 1;
        }
        det_adjunta = (signos * ((d1) - (d2)));
    }
    return det_adjunta;
}

void transpuesta_matriz(int m, int n, float a[100][100], float b[100][100])
{
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            b[j][i] = a[i][j];
        }
    }
}

void division_determinante(int m, int n, float f[100][100], int determinante_matriz)
{
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            f[i][j] = f[i][j] / determinante_matriz;
        }
    }
}

void imprimir_matriz(int m, int n, float a[100][100])
{
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%.2f ", a[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

mat *crear_matriz()
{
    int i, j, band = 0; // Esta función hace uso de banderas
    mat *matriz;
    int tot_m;
    int total_matrices;
    total_matrices = 0;

    // Pregunta cuántas matrices se desea crear
    printf("Introduzca la cantidad de matrices a crear: ");
    scanf("%d", &tot_m);
    system("cls");

    // Condición para establecer el número de polinomios que acepta la memoria
    // Si ya está llena la memoria suelta advertencia
    if ((total_matrices + tot_m) > 10)
    {
        printf("Memoria llena, no se pueden guardar esos matrices\nEspacio libre: %d matrices", (10 - total_matrices));
        system("pause");
    }
    else
    {
        band = 1; // Establezco la bandera como verdadero
        matriz = (mat *)malloc(tot_m * sizeof(mat));

        for (i = 0; i < tot_m; i++)
        {
            // Pido las matrices
            // Pido la cantidad de columnas y filas "dimensiones"
            printf("\nIntroduzca la la dimension de su matriz");
            printf("\nIngresa los datos de la Matriz \n");
            scanf("%d", &matriz->n);
            scanf("%d", &matriz->m);
            for (int j = 0; j < matriz->n; j++)
            {
                for (int i = 0; i < matriz->m; i++)
                {
                    printf("Ingrese el elemento de la posicion [%d][%d]:", i + 1, j + 1);
                    scanf("%f", &matriz->a[i][j]);
                }
            }

            printf("\n");
            for (int i = 0; i < matriz->m; i++)
            {
                for (int j = 0; j < matriz->n; j++)
                {
                    printf("%.2f ", matriz->a[i][j]);
                }
                printf("\n");
            }
            printf("\n");
        }

        printf("┌----------------------------------------------|\n");
        printf("|              MATRICES CREADAS               |\n");
        printf("|----------------------------------------------┘\n\n");

        FILE *archivo;
        archivo = fopen("matriz.txt", "w+");

        for (i = 0; i < tot_m; i++)
        {
            // El número de matriz
            printf("%d)", (i + 1));
            for (j = 0; j < matriz[i].a[i][j]; j++)
            {
                for (int i = 0; i < matriz->m; i++)
                {
                    for (int j = 0; j < matriz->n; j++)
                    {

                        printf("%.2f ", matriz->a[i][j]);
                        fprintf(archivo, "%.2f ", matriz->a[i][j]);
                    }
                }
            }
            fclose(archivo); // Cierro el archivo
            printf("\n\nMatrices creados en archivo de manera exitosa\n\n");
        }
        return 0;
    }
}
