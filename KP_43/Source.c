#define _CRT_SECURE_NO_DEPRECATE
#define _USE_MATH_DEFINES
#include <stdio.h>
#include <locale.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_NODE_LEN 64
#define MAX_LINE_LEN 256
#define CAPACITY     100

// СТРУКТУРЫ

typedef struct {
    int  h;
    int  m;
    char node[MAX_NODE_LEN];
    int  hits;
    int  misses;
} Event;

typedef struct {
    int received;
    int dropped;
    int added;
} Stats;

// ОБЪЯВЛЕНИЯ ФУНКЦИЙ

// пока нет 


int main() 
{
    setlocale(LC_ALL, "RUS");

    int choice = 0;

    char continued;

    while (choice != 7)
    {
        system("cls");
        printf("****************** Главное меню *****************\n");
        printf("1. Ввести записи DNS-кэша вручную;\n");
        printf("2. Вывести все записи;\n");
        printf("3. Найти запись с минимальным основным показателем (hits);\n");
        printf("4. Считать данные из файла;\n");
        printf("5. Записать информацию в файл (архив);\n");
        printf("6. Сортировать записи по hits (по убыванию);\n");
        printf("7. Завершение работы программы;\n");
        printf("*************************************************\n");

        printf("Выберите действие: \n");
        if (scanf("%d", &choice) != 1) 
        {
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
            choice = -1;
        }
        getchar();

        switch (choice)
        {
        case 1:
        {
            printf("Пункт 1 \n");
            break;
        }
        case 2:
        {
            printf("Пункт 2 \n");
            break;
        }
        case 3:
        {
            printf("Пункт 3 \n");
            break;
        }
        case 4:
        {
            printf("Пункт 4 \n");
            break;
        }
        case 5:
        {
            printf("Пункт 5 \n");
            break;
        }
        case 6:
        {
            printf("Пункт 6 \n");
            break;
        }
        case 7:
        {
            printf("Завершение работы программы. До свидания!\n");
            break;
        }
        default:
        {
            printf("Вы ввели некорректные данные, повторите попытку!\n");
            break;
        }
        }

        printf("\n");
        printf("\tПродолжить? (Да-введите любой символ, нет - n)\n");
        scanf("%c", &continued);
        printf("\n");
        if (continued == getchar() == 'n')
        {
            printf("\n");
            puts("   *********************************************************");
            break;
        }
    }

    return 0;
}
