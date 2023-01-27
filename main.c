#include "funciones.c"

int menu();
void manual();

int main()
{
  int opc, res;
  polinomios *pol;
  mat *matriz;
  float a[100][100], b[100][100], c[100][100], d[100][100], e[100][100];
  int m, n, p, q, op;
  float escalar;
  int signo = 1;
  int i = 0, j = 0, r = 0, t = 0, x = 0, y = 0;
  float determinante, det_adjunta;
  int movimiento_columnas, movimiento_filas;

  do
  {
    menu();
    fflush(stdin);
    scanf("%d", &opc);
    system("cls");

    switch (opc)
    {
      while (total_polinomios <= 0 && opc != 1 && opc != 2 && opc != 8)
      {
      case 1:
        pol = crear_polinomio();
        break;
      case 2:
        pol = obtener_polinomios();
        break;
      case 3:
        imprime_polinomios(pol);
        suma(pol);

        break;
      case 4:
        imprime_polinomios(pol);
        resta(pol);
        break;
      case 5:
        imprime_polinomios(pol);
        multiplicacion_escalar(pol);
        break;
      case 6:
        imprime_polinomios(pol);
        multiplicacion(pol);
        break;
      case 7:
        imprime_polinomios(pol);
        division(pol);
        break;
      case 8:
        printf("--------------------------------------------------\n");
        printf("\t>>>>>>>Guardado de Matriz<<<<<<\n");
        printf("--------------------------------------------------\n\n");
        matriz = crear_matriz();
        break;
      case 9:
        printf("--------------------------------------------------\n");
        printf("\t>>>>>>>Suma de Matrices<<<<<<\n");
        printf("--------------------------------------------------\n\n");
        printf("\n");
        printf("Ingrese las dimensiones de la Matriz A: ");
        scanf("%d", &m);
        scanf("%d", &n);
        leer_matriz(m, n, a);
        printf("Ingrese las dimensiones de la Matriz B: ");
        scanf("%d", &p);
        scanf("%d", &q);
        leer_matriz(p, q, b);
        if (m == p && n == q)
        {
          suma_matriz(m, n, a, b, c);
          printf("Matriz C  resultante de sumar Matriz A + Matriz B\n");
          imprimir_matriz(m, n, c);
        }
        else
        {
          printf("No se puede realizar la operación suma de matrices \n");
          printf("Ingrese dimensiones correctas \n");
          printf("Las dimensiones de ambas matrices deben ser iguales \n");
        }
        break;
      case 10:
        printf("┌----------------------------------------------|\n");
        printf("|              RESTA DE MATRICES             |\n");
        printf("|----------------------------------------------┘\n\n");
        printf("\n");
        printf("Ingrese las dimensiones de la Matriz A: ");
        scanf("%d", &m);
        scanf("%d", &n);
        leer_matriz(m, n, a);
        printf("Ingrese las dimensiones de la Matriz B: ");
        scanf("%d", &p);
        scanf("%d", &q);
        leer_matriz(p, q, b);
        if (m == p && n == q)
        {
          resta_matriz(m, n, a, b, c);
          printf("Matriz C  resultante de restar Matriz A - Matriz B\n");
          imprimir_matriz(m, n, c);
        }
        else
        {
          printf("No se puede realizar la operacion resta de matrices \n");
          printf("Ingrese dimensiones correctas \n");
          printf("Las dimensiones de ambas matrices deben ser iguales \n");
        }
        break;
      case 11:
        printf("┌----------------------------------------------|\n");
        printf("|              MULTIPLICACION DE MATRICES             |\n");
        printf("|----------------------------------------------┘\n\n");
        printf("\n");
        printf("Ingrese las dimensiones de la Matriz A: ");
        scanf("%d", &m); // filas
        scanf("%d", &n); // columnas
        leer_matriz(m, n, a);
        printf("Ingrese las dimensiones de la Matriz B: ");
        scanf("%d", &p); // filas
        scanf("%d", &q); // columnas
        leer_matriz(p, q, b);
        if (n == p)
        {
          multiplicacion_matriz(m, n, q, a, b, c);
          printf("Matriz C  resultante de multiplicar Matriz A * Matriz B \n");
          imprimir_matriz(m, q, c);
        }
        else
        {
          printf("No se puede realizar la multiplicacion de matrices \n");
          printf("Ingrese dimensiones correctas de acuerdo a la multiplicacion de matrices \n");
        }
        break;

      case 12:
        printf("┌----------------------------------------------|\n");
        printf("|              MULTIPLICACION DE MATRICES POR ESCALAR             |\n");
        printf("|----------------------------------------------┘\n\n");
        printf("\n");
        printf("Ingrese las dimensiones de la Matriz A: ");
        scanf("%d", &m);
        scanf("%d", &n);
        leer_matriz(m, n, a);
        printf("Ingrese el escalar: ");
        scanf("%f", &escalar);
        multiescalar_matriz(m, n, a, escalar, c);
        printf("Matriz C  resultante de multiplicar Matriz A * %.2f \n", escalar);
        imprimir_matriz(m, n, c);
        break;
      case 13:
        printf("Transpuesta de una Matriz \n");
        printf("\n");
        printf("Ingrese las dimensiones de la Matriz A: ");
        scanf("%d", &m);
        scanf("%d", &n);
        leer_matriz(m, n, a);
        transpuesta_matriz(m, n, a, b);
        printf("Matriz Transpuesta \n");
        imprimir_matriz(n, m, b);
        break;
      case 14:
        printf("Determinante de una Matriz \n");
        printf("\n");
        printf("Ingrese las dimensiones de la Matriz A: ");
        scanf("%d", &m);
        scanf("%d", &n);
        leer_matriz(m, n, a);
        if (m == 2 && n == 2)
        { // si es una matriz 2x2 llama a la funcion detrminante_matriz
          determinante = determinante_matriz(m, n, a);
        }
        else
        {
          // si la matriz no es 2x2 llama a la funcion ampliar matriz para obtener todas sus diagonales
          ampliar_matriz(m, n, a, b);
          determinante = determinante_matriz(m, n, b);
        }
        printf("Determinante Matriz A = %.2f \n", determinante);
        break;

      case 15:
        printf("┌----------------------------------------------|\n");
        printf("|              MATRIZ ADJUNTA             |\n");
        printf("|----------------------------------------------┘\n\n");
        printf("\n");
        printf("Ingrese las dimensiones de la Matriz A: ");
        scanf("%d", &m);
        scanf("%d", &n);
        leer_matriz(m, n, a);
        for (movimiento_filas = 0; movimiento_filas < m; movimiento_filas++)
        {
          for (movimiento_columnas = 0; movimiento_columnas < n; movimiento_columnas++)
          {
            r = 0;
            for (i = 0; i < m; i++)
            {
              t = 0;
              for (j = 0; j < n; j++)
              {
                if (i != movimiento_filas && j != movimiento_columnas)
                {
                  b[r][t] = a[i][j];
                  t++;
                  if (t == n - 1)
                  {
                    t = 0;
                    r++;
                  }
                }
              }
            }
            det_adjunta = determinante_adjunta(m - 1, n - 1, b, signo);
            c[x][y] = det_adjunta;
            y++;
            if (y == n)
            {
              y = 0;
              x++;
            }
            signo = signo * -1;
          }
        }
        printf("Matriz Adjunta \n");
        imprimir_matriz(m, n, c);
        break;

      case 16:
        printf("┌----------------------------------------------|\n");
        printf("|              MATRIZ INVERSA             |\n");
        printf("|----------------------------------------------┘\n\n");
        printf("\n");
        printf("Ingrese las dimensiones de la Matriz A: ");
        scanf("%d", &m);
        scanf("%d", &n);
        if (m == n && n == m)
        {
          leer_matriz(m, n, a);
          if (m != 2 && n != 2)
          {
            if (m == 2 && n == 2)
            {
              determinante = determinante_matriz(m, n, a);
            }
            else
            {
              // si la matriz no es 2x2 se llama la funcion ampliar matriz
              ampliar_matriz(m, n, a, b);
              determinante = determinante_matriz(m, n, b);
            }
            if (determinante != 0)
            {
              transpuesta_matriz(m, n, a, c);
              for (movimiento_filas = 0; movimiento_filas < m; movimiento_filas++)
              {
                for (movimiento_columnas = 0; movimiento_columnas < n; movimiento_columnas++)
                {
                  r = 0;
                  for (i = 0; i < m; i++)
                  {
                    t = 0;
                    for (j = 0; j < n; j++)
                    {
                      if (i != movimiento_filas && j != movimiento_columnas)
                      {
                        d[r][t] = c[i][j];
                        t++;
                        if (t == n - 1)
                        {
                          t = 0;
                          r++;
                        }
                      }
                    }
                  }
                  det_adjunta = determinante_adjunta(m - 1, n - 1, d, signo);
                  e[x][y] = det_adjunta;
                  y++;
                  if (y == n)
                  {
                    y = 0;
                    x++;
                  }
                  signo = signo * -1;
                }
              }
              printf("Matriz Inversa \n");
              imprimir_matriz(m, n, e);
            }
            else
            {
              printf("La matriz ingresada no tiene inversa \n");
            }
          }
          else
          {
            determinante = determinante_matriz(m, n, a);
            if (determinante == 0)
            {
              printf("La matriz ingresada no tiene matriz inversa \n");
            }
            else
            {
              b[1][1] = a[0][0];
              b[0][0] = a[1][1];
              b[0][1] = a[0][1] * -1;
              b[1][0] = a[1][0] * -1;
              division_determinante(m, n, b, determinante);
              printf("Matriz Inversa \n");
              imprimir_matriz(m, n, b);
            }
          }
        }
        else
        {
          printf("Las dimensiones de la matriz debe ser cuadrada \n");
        }
        break;
      case 17:
        manual();
      case 18:
        printf("Calculadora terminada!\n\n");
        break;
      default:
        printf("Introduzca una opcion valida\n\n");
      }
    }
    if (opc != 18)
    {
      system("pause");
      system("cls");
    }
  } while (opc != 18);

  return 0;
}

int menu()
{
  char nombre[20];
  int opc;

  printf("┌--------------------------------------------------|\n");
  printf("|             CALCULADORA DE POLINOMIOS            |\n");
  printf("|--------------------------------------------------┘\n\n");
  printf("\t \t ■ Presiona el numero de la que quieres y presiona la tecla enter ■ \n\n ");
  printf("1. Crear/Guardar polinomios\n");
  printf("2. Obtener polinomios de archivo\n");
  printf("3. Suma polinomios\n");
  printf("4. Resta polinomios\n");
  printf("5. Multiplicacion por un escaclar\n");
  printf("6. Multiplicacion\n");
  printf("7. Division\n");
  printf("\n");
  printf("┌--------------------------------------------------|\n");
  printf("|             CALCULADORA DE MATRICES              |\n");
  printf("|--------------------------------------------------┘\n\n");
  printf("8. Crear Matriz\n");
  printf("9. Suma de Matrices \n");
  printf("10. Resta de Matrices \n");
  printf("11. Multiplicacion de Matrices \n");
  printf("12. Multiplicacion de una Matriz por un Escalar \n");
  printf("13. Transpuesta de una Matriz \n");
  printf("14. Determinante de una Matriz \n");
  printf("15. Matriz Adjunta \n");
  printf("16. Matriz Inversa \n");
  printf("17. Manual de Usuario! \n");
  printf("18. Salir\n");
  printf("\n%s Elige una operación del menu:", nombre);
  return opc;
}

void manual()
{
  int usuario;
  do
  {
    printf("┌--------------------------------------------------------|\n");
    printf("|                    MANUAL DE USUARIO                   |\n");
    printf("|--------------------------------------------------------┘\n\n");
    printf("\t \t ■ Presiona el numero de la que quieres y presiona la tecla enter ■ \n\n ");
    printf("1. Crear/Guardar polinomios\n");
    printf("2. Obtener polinomios de archivo\n");
    printf("3. Suma polinomios\n");
    printf("4. Resta polinomios\n");
    printf("5. Multiplicacion por un escaclar\n");
    printf("6. Multiplicacion\n");
    printf("7. Division\n");
    printf("8. Ejemplo de guardar matriz\n");
    printf("9. Suma de Matrices \n");
    printf("10. Resta de Matrices \n");
    printf("11. Multiplicacion de Matrices \n");
    printf("12. Multiplicacion de una Matriz por un Escalar \n");
    printf("13. Transpuesta de una Matriz \n");
    printf("14. Determinante de una Matriz \n");
    printf("15. Matriz Adjunta \n");
    printf("16. Matriz Inversa \n");
    printf("17. Salir\n");
    printf("18. Ya no necesito ayuda \n");
    printf("Seleccione una opcion: ");
    scanf("%d", &usuario);

    // Menu de Usuario
    switch (usuario)
    {
    case 1:
      printf("----------------------------------------------\n");
      printf("Crear o guardar polinomio                 \n");
      printf("----------------------------------------------\n\n");
      printf("- Paso 1: \n");
      printf("\t* Primero Ingresa el numero de polinomios que quieres crear y da enter. \n ");
      printf("- Paso 2: \n");
      printf("\t* Para cada uno de los polinomios que quieres crear: \n ");
      printf("\t*Ingresa la cantidad de coeficientes de tu polinomio y da enter. \n ");
      printf("\t* Para cada coeficiente:  \n ");
      printf("\t* Ingresa el coeficiente y da enter.  \n ");
      printf("\t* Ingresa el exponente y da enter.  \n ");
      printf("- Paso 3: \n");
      printf("\t* En pantalla apareceran los polinomios ingresados ordenados por sus exponentes de mayor a menor. \n ");
      printf("- Paso 4: \n");
      printf("\t*Ingresa un numero para obtener la operacion");
      printf("\t\t Presiona cualquier tecla. \n ");
      break;
    case 2:
      printf("----------------------------------------------\n");
      printf("\tObtener el Polinomio \n");
      printf("----------------------------------------------\n\n");
      printf("- Paso 1: \n");
      printf("*En pantalla apareceran los polinomios ingresados ordenados por sus exponentes de mayor a menor. \n ");
      printf("- Paso 2:\n");
      printf("* Ingresa un numero para obtener la operacion\n");
      printf("\t -- Presiona cualquier tecla. \n ");
      break;
    case 3:
      printf("----------------------------------------------\n");
      printf("Suma de Polinomios\n");
      printf("----------------------------------------------\n\n");
      printf("- Paso 1: \n");
      printf(" * Con base en los polinomios previamente ingresados que aparecen en pantalla: \n ");
      printf(" * Escribe el numero del primer polinomio y da enter. \n ");
      printf(" *  Escribe el numero del segundo polinomio y da enter. \n ");
      printf(" - Paso 2: \n");
      printf(" *  En pantalla aparecera el resultado de la suma. \n ");
      printf(" - Paso 3: \n");
      printf(" * Ingresa un numero para obtener la operacion");
      printf("-- Presiona cualquier tecla.-- \n ");
      break;

      break;
    case 4:
      printf("----------------------------------------------\n");
      printf(" Resta de Polinomios\n");
      printf("----------------------------------------------\n\n");
      printf("- Paso 1: \n");
      printf(" * Con base en los polinomios previamente ingresados que aparecen en pantalla: \n ");
      printf(" * Escribe el numero del primer polinomio y da enter. \n ");
      printf(" *  Escribe el numero del segundo polinomio y da enter. \n ");
      printf(" - Paso 2: \n");
      printf(" *  En pantalla aparecera el resultado de la resta. \n ");
      printf(" - Paso 3: \n");
      printf(" * Ingresa un numero para obtener la operacion");
      printf(" \t--Presiona cualquier tecla.-- \n ");
      break;
    case 5:
      printf("----------------------------------------------\n");
      printf(" Multiplicacion por escalar \n");
      printf("----------------------------------------------\n\n");
      printf("- Paso 1: \n");
      printf(" * Con base en los polinomios previamente ingresados que aparecen en pantalla: \n ");
      printf(" * Escribe el numero del polinomio y da enter. \n ");
      printf("- Paso 2: \n");
      printf(" * Escribe el escalar y da enter \n ");
      printf("- Paso 3: \n");
      printf(" * En pantalla aparecera el resultado de la multiplicacion. \n ");
      printf("- Paso 4: \n");
      printf(" \t--Presiona cualquier tecla para continuar-- \n ");
      break;
    case 6:
      printf("----------------------------------------------\n");
      printf(" Multiplicacion de Polinomios \n");
      printf("----------------------------------------------\n\n");
      printf("- Paso 1: \n");
      printf("  * Con base en los polinomios previamente ingresados que aparecen en pantalla: \n ");
      printf("  * Escribe el numero del primer polinomio y da enter. \n ");
      printf("  *  Escribe el numero del segundo polinomio y da enter. \n ");
      printf("- Paso 2: \n");
      printf("  *  En pantalla aparecera el resultado de la multiplicacion. \n ");
      printf("- Paso 3: \n");
      printf("  * Ingresa un numero para obtener la operacion");
      printf("-- Presiona cualquier tecla.-- \n ");
      break;
    case 7:
      printf("----------------------------------------------\n");
      printf(" Division sintetica\n");
      printf("----------------------------------------------\n\n");
      printf(" - Paso 1: \n");
      printf("\t * Con base en los polinomios previamente ingresados que aparecen en pantalla: \n ");
      printf("\t * Escribe el numero del DIVISOR y da enter. \n ");
      printf("\t * Escribe el numero del DIVIDENDO y da enter. \n ");
      printf(" - Paso 2: \n");
      printf("\t * En pantalla aparecera el resultado de la division. \n ");
      printf("\t - Paso 3: \n");
      printf("\t * Presiona cualquier tecla. \n ");
      break;
    case 8:
      printf("----------------------------------------------\n");
      printf("Guardar y Crear Matriz\n");
      printf("----------------------------------------------\n\n");

      printf("- Paso 1: Este es una opcion para guardar matriz\n");
      printf("\n");
      printf("- Paso 2: Se te solicitará que ingreses las dimensiones de las matrices a operar, a lo que debes escribirlas con el siguiente formato: 2 2 para una matriz de 2 columnas y 2 filas, 3 2 para una matriz 3 columnas y 2 filas, entre otras opciones \n");
      printf("\n");
      printf("- Paso 3: Da click al botón ENTER en ingresa valor por valor de la matriz en el formato columnas y filas [i][j] respectivamente \n");
      printf("Si tienes alguna duda acerca de la forma de ingresar los datos de la matriz puedes seleccionar la opción 0 del menú y de forma didactica observar la forma en que se guardan los datos en la matriz. \n ");
      break;
    case 9:
      printf("----------------------------------------------\n");
      printf(" Suma de Matrices\n");
      printf("----------------------------------------------\n\n");
      printf("- Paso 1: Suma de Matrices\n");
      printf("\n");
      printf("- Paso 2: Se te solicitará que ingreses las dimensiones de las matrices a operar, a lo que debes escribirlas con el siguiente formato: 2 2 para una matriz de 2 columnas y 2 filas, 3 2 para una matriz 3 columnas y 2 filas, entre otras opciones \n");
      printf("\n");
      printf("- Paso 3: Da click al botón ENTER en ingresa valor por valor de la matriz en el formato columnas y filas [i][j] respectivamente \n");
      printf("Si tienes alguna duda acerca de la forma de ingresar los datos de la matriz puedes seleccionar la opción 0 del menú y de forma didactica observar la forma en que se guardan los datos en la matriz. \n ");
      printf("\n *Se reflejara la suma de las matrices ingresadas...\n");
      break;
    case 10:
      printf("----------------------------------------------\n");
      printf(" Resta de Matrices \n");
      printf("----------------------------------------------\n\n");
      printf("- Paso 1: Resta de Matrices\n");
      printf("\n");
      printf("- Paso 2: Se te solicitará que ingreses las dimensiones de las matrices a operar, a lo que debes escribirlas con el siguiente formato: 2 2 para una matriz de 2 columnas y 2 filas, 3 2 para una matriz 3 columnas y 2 filas, entre otras opciones \n");
      printf("\n");
      printf("- Paso 3: Da click al botón ENTER en ingresa valor por valor de la matriz en el formato columnas y filas [i][j] respectivamente \n");
      printf("Si tienes alguna duda acerca de la forma de ingresar los datos de la matriz puedes seleccionar la opción 0 del menú y de forma didactica observar la forma en que se guardan los datos en la matriz. \n ");
      printf("\n *Se reflejara la resta de las matrices ingresadas...\n");
      break;
    case 11:
      printf("----------------------------------------------\n");
      printf(" Multiplicacion de Matrices \n");
      printf("----------------------------------------------\n\n");
      printf("- Paso 1: Este es la opcion de Multiplicacion de Matrices\n");
      printf("\n");
      printf("- Paso 2: Se te solicitará que ingreses las dimensiones de las matrices a operar, a lo que debes escribirlas con el siguiente formato: 2 2 para una matriz de 2 columnas y 2 filas, 3 2 para una matriz 3 columnas y 2 filas, entre otras opciones \n");
      printf("\n");
      printf("- Paso 3: Da click al botón ENTER en ingresa valor por valor de la matriz en el formato columnas y filas [i][j] respectivamente \n");
      printf("Si tienes alguna duda acerca de la forma de ingresar los datos de la matriz puedes seleccionar la opción 0 del menú y de forma didactica observar la forma en que se guardan los datos en la matriz. \n ");
      printf("\n *Se reflejara la multiplicacion de las matrices ingresadas...\n");
      break;
    case 12:
      printf("----------------------------------------------\n");
      printf(" Multiplicacion Matriz por escalar \n");
      printf("----------------------------------------------\n\n");
      printf("- Paso 1: Este es la opcion de Multiplicacion de Matriz por Escalar\n");
      printf("\n");
      printf("- Paso 2: Se te solicitará que ingreses las dimensiones de las matrices a operar, a lo que debes escribirlas con el siguiente formato: 2 2 para una matriz de 2 columnas y 2 filas, 3 2 para una matriz 3 columnas y 2 filas, entre otras opciones \n");
      printf("\n");
      printf("- Paso 3: Da click al botón ENTER en ingresa valor por valor de la matriz en el formato columnas y filas [i][j] respectivamente \n");
      printf("\t*Se ingresa el valor del escalar");
      printf("Si tienes alguna duda acerca de la forma de ingresar los datos de la matriz puedes seleccionar la opción 0 del menú y de forma didactica observar la forma en que se guardan los datos en la matriz. \n ");
      printf("\n *Se reflejara la multiplicacion de las matriz por el escalar...\n");
      break;
    case 13:
      printf("- Paso 1: Este es la opcion de Matriz Transpuesta\n");
      printf("\n");
      printf("- Paso 2: Se te solicitará que ingreses las dimensiones de las matrices a operar, a lo que debes escribirlas con el siguiente formato: 2 2 para una matriz de 2 columnas y 2 filas, 3 2 para una matriz 3 columnas y 2 filas, entre otras opciones \n");
      printf("\n");
      printf("- Paso 3: Da click al botón ENTER en ingresa valor por valor de la matriz en el formato columnas y filas [i][j] respectivamente \n");
      printf("\t*En este caso solo se ingresa las dimesiones de una matriz ");
      printf("Si tienes alguna duda acerca de la forma de ingresar los datos de la matriz puedes seleccionar la opción 0 del menú y de forma didactica observar la forma en que se guardan los datos en la matriz. \n ");
      printf("\n *Se reflejara la Matriz con los valores ingresados...\n");
      break;

    case 14:
      printf("----------------------------------------------\n");
      printf(" Matriz Determinante \n");
      printf("----------------------------------------------\n\n");
      printf("- Paso 1: Este es la opcion Determinante de una Matriz\n");
      printf("\n");
      printf("- Paso 2: Se te solicitará que ingreses las dimensiones de las matrices a operar, a lo que debes escribirlas con el siguiente formato: 2 2 para una matriz de 2 columnas y 2 filas, 3 2 para una matriz 3 columnas y 2 filas, entre otras opciones \n");
      printf("\n");
      printf("- Paso 3: Da click al botón ENTER en ingresa valor por valor de la matriz en el formato columnas y filas [i][j] respectivamente \n");
      printf("\t*En este caso solo se ingresa las dimesiones de una matriz ");
      printf("Si tienes alguna duda acerca de la forma de ingresar los datos de la matriz puedes seleccionar la opción 0 del menú y de forma didactica observar la forma en que se guardan los datos en la matriz. \n ");
      printf("\n *Se reflejara la matriz determinante...\n");
      break;

    case 15:
      printf("----------------------------------------------\n");
      printf(" Matriz Adjunta\n");
      printf("----------------------------------------------\n\n");
      printf("- Paso 1: Este es la opcion Matriz Adjunta\n");
      printf("\n");
      printf("- Paso 2: Se te solicitará que ingreses las dimensiones de las matrices a operar, a lo que debes escribirlas con el siguiente formato: 2 2 para una matriz de 2 columnas y 2 filas, 3 2 para una matriz 3 columnas y 2 filas, entre otras opciones \n");
      printf("\n");
      printf("- Paso 3: Da click al botón ENTER en ingresa valor por valor de la matriz en el formato columnas y filas [i][j] respectivamente \n");
      printf("\t*En este caso solo se ingresa las dimesiones de una matriz ");
      printf("Si tienes alguna duda acerca de la forma de ingresar los datos de la matriz puedes seleccionar la opción 0 del menú y de forma didactica observar la forma en que se guardan los datos en la matriz. \n ");
      printf("\n *Se reflejara la matriz adjunta...\n");
      break;
    case 16:
      printf("----------------------------------------------\n");
      printf(" Multiplicacion Inversa \n");
      printf("----------------------------------------------\n\n");
      printf("- Paso 1: Este es la opcion Matriz Inversa\n");
      printf("\n");
      printf("- Paso 2: Se te solicitará que ingreses las dimensiones de las matrices a operar, a lo que debes escribirlas con el siguiente formato: 2 2 para una matriz de 2 columnas y 2 filas, 3 2 para una matriz 3 columnas y 2 filas, entre otras opciones \n");
      printf("\n");
      printf("- Paso 3: Da click al botón ENTER en ingresa valor por valor de la matriz en el formato columnas y filas [i][j] respectivamente \n");
      printf("\t*En este caso solo se ingresa las dimesiones de una matriz ");
      printf("Si tienes alguna duda acerca de la forma de ingresar los datos de la matriz puedes seleccionar la opción 0 del menú y de forma didactica observar la forma en que se guardan los datos en la matriz. \n ");
      printf("\n *Se reflejara la matriz inversa...\n");

    case 17:
      printf("┌----------------------------------------------|\n");
      printf("|              QUIERO SALIR :C             |\n");
      printf("|----------------------------------------------┘\n\n");
      printf("- Paso 1: \n");
      printf("\t*Para terminar con la ejecucion del programa escribe el numero 17 y da enter uwu \n ");
      break;

    case 18:
      printf("Gracias por preguntar \n");
      break;

    default:
      printf("Introduzca una opcion valida\n\n");
    }
    if (usuario != 18)
    {
      system("pause");
      system("cls");
    }
  } while (usuario != 18);
}