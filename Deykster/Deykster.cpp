
#include <stdlib.h>
#include <math.h>
#include <iosfwd>
#include <limits.h>

const int N = 6;


/**
Realizatsiya algoritma Deykstry.
Nahodit kratchayshee rasstoyanie ot odnoy iz vershin grafa do vseh ostal'nyh.         
*/
int main() {
    int predok[N], nach = 0, D[N];
    bool flag[N];
    /* Пример графа взят из Википедии, в качестве наглядного примера
     * http://ru.wikipedia.org/wiki/Алгоритм_Дейкстры
     */
    int A[N][N] = {
        {0, 7, 9, 14, INT16_MAX, INT16_MAX},
        {7, 0, 10, INT16_MAX, INT16_MAX, 15},
        {9, 10, 0, 2, INT16_MAX, 11},
        {14, INT16_MAX, 2, 0, 9, INT16_MAX},
        {INT16_MAX, INT16_MAX, INT16_MAX, 9, 0, 6},
        {INT16_MAX, 15, 11, INT16_MAX, 6, 0}
    };

    for (int i = 0; i < N; i++) {
        predok[i] = nach;
        flag[i] = false;
        D[i] = A[nach][i];
    }

	/**
Poka izvestno tol'ko odno rasstoyanie:
ot vershiny nach  do nee zhe, ravnoe 0.
*/
    flag[nach] = true;
    predok[nach] = 0;
    for (int i = 0; i < N - 1; i++) {
        int k = 0;
        int minras = INT16_MAX;
        // Находим минимальное расстояние до непомеченных вершин
        for (int j = 0; j < N; j++) {
            if (!flag[j] && minras > D[j]) {
                minras = D[j];
                k = j;
            }
        }
        // Вершина k помечается просмотренной
        flag[k] = true;
        for (int j = 0; j < N; j++) {
            /* Если для вершины j еще не найдено кратчайшее расстояние от
             * нач. и из вершины k по дуге A[k][j] путь в j короче
             * чем найденное ранее, то запоминаем его.
             */
            if (!flag[j] && D[j] > D[k] + A[k][j]) {
                D[j] = D[k] + A[k][j];
                predok[j] = k;
            }
        }
    }

    puts("Rasstoyaniya:");
    for (int i = 0; i < N; i++) {
        printf("Ot %d do %d: %d\n", nach, i, D[i]);
    }

    puts("");
    puts("IIYTb:");
   
	/**
Vyvodim put' zadom na pered:
  v kazhdoy yacheyke massiva predok hranitsya
  nomer predyduschey yacheyki - vershiny kratchayshego puti.
  Naprimer, predyduschaya vershina dlya vershiny 5 = predok[5]   
*/
    for (int i = N; i > nach + 1; i--) {
        printf("Ot %d do %d: ", i - 1, nach);
        for (int j = i - 1; j > nach;) {
            printf("%d ", j);
            j = predok[j];
        }
        printf("%d\n", nach);
    }

    return (EXIT_SUCCESS);
}