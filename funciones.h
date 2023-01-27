#ifndef __FUNCIONES_H__
#define __FUNCIONES_H__

// Estructuras

// Terminos Polinomio
typedef struct
{
    float coef;
    int exp;
} terminos;

// Polinomio
typedef struct
{
    int tot_term;
    terminos *term;
} polinomios;

// Funciones para la Memoria

polinomios *crear_polinomio();
polinomios *obtener_polinomios();
void guardarpoli(polinomios *pol);
void imprime_polinomios(polinomios *pol);

// Operaciones de polinomios
void suma(polinomios *pol);
void resta(polinomios *pol);
void multiplicacion_escalar(polinomios *pol);
void multiplicacion(polinomios *pol);
void division(polinomios *pol);
// Guardado

// Estructura para matriz
typedef struct
{
    int n;
    int m;
    float a[100][100];

} mat;
// Funciones de Memoria
mat *crear_matriz();
// operaciones
void leer_matriz(int m, int n, float a[100][100]);
void suma_matriz(int m, int n, float a[100][100], float b[100][100], float c[100][100]);
void resta_matriz(int m, int n, float a[100][100], float b[100][100], float c[100][100]);
void multiescalar_matriz(int m, int n, float a[100][100], float escalar, float b[100][100]);
void multiplicacion_matriz(int m, int n, int q, float a[100][100], float b[100][100], float c[100][100]);
void ampliar_matriz(int m, int n, float a[100][100], float b[100][100]);
float determinante_matriz(int m, int n, float b[100][100]);
float determinante_adjunta(int m, int n, float e[100][100], int signos);
void transpuesta_matriz(int m, int n, float a[100][100], float c[100][100]);
void division_determinante(int m, int n, float f[100][100], int determinante_matriz);
void imprimir_matriz(int m, int n, float a[100][100]);

#endif
