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

int  parseEvent(const char* line, Event* ev);
void inputEventsManually(Event* arr, int* n, int capacity, Stats* st);

int  addEvent(Event* arr, int* n, int capacity, const Event* ev, Stats* st);
void printStats(const Stats* st);
void outputEvents(Event* arr, int n);


int main() 
{
    setlocale(LC_ALL, "RUS");

    int choice = 0;
    int n = 0;
    Event cache[CAPACITY];
    Stats st = { 0, 0, 0 };

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
            inputEventsManually(cache, &n, CAPACITY, &st);
            break;
        }
        case 2:
        {
            if (n == 0) 
            {
                printf("Нет данных. Сначала введите записи (пункт 1).\n");
            }
            else 
            {
                outputEvents(cache, n);
                printf("\n");
                printStats(&st);
            }
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
// ОПРЕДЕЛЕНИЯ ФУНКЦИЙ
int parseEvent(const char* line, Event* ev) 
{
    if (line == NULL || ev == NULL) return 0;

    char node[MAX_NODE_LEN];
    int  h, m, hits, misses;

    int rc = sscanf(line, "%d:%d %63s %d %d", &h, &m, node, &hits, &misses);
    if (rc != 5) return 0;
    if (h < 0 || h > 23) return 0;
    if (m < 0 || m > 59) return 0;
    if (hits < 0 || misses < 0) return 0;

    ev->h = h;
    ev->m = m;
    strncpy(ev->node, node, MAX_NODE_LEN - 1);
    ev->node[MAX_NODE_LEN - 1] = '\0';
    ev->hits = hits;
    ev->misses = misses;
    return 1;
}

void inputEventsManually(Event* arr, int* n, int capacity, Stats* st) 
{
    int count = 0;
    printf("Сколько записей хотите ввести? ");
    if (scanf("%d", &count) != 1 || count <= 0) 
    {
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
        printf("Некорректное количество.\n");
        return;
    }
    getchar();

    for (int i = 0; i < count; i++) 
    {
        char line[MAX_LINE_LEN];
        printf("Запись №%d (формат чч:мм node hits misses): ", i + 1);
        if (!fgets(line, sizeof(line), stdin)) break;

        Event ev;
        if (!parseEvent(line, &ev)) 
        {
            printf("Ошибка формата. Запись пропущена.\n");
            continue;
        }
        if (!addEvent(arr, n, capacity, &ev, st)) 
        {
            printf("Запись не добавлена (места нет).\n");
        }
    }
    printf("Ввод завершён. Всего в кэше: %d\n", *n);
}

int addEvent(Event* arr, int* n, int capacity, const Event* ev, Stats* st) 
{
    if (arr == NULL || n == NULL || ev == NULL || st == NULL) return 0;

    st->received++;

    if (*n >= capacity) return 0;

    arr[*n] = *ev;
    (*n)++;
    st->added++;
    return 1;
}

void printStats(const Stats* st) 
{
    if (st == NULL) return;
    printf("Получено записей:        %d\n", st->received);
    printf("Отброшено как дубликаты: %d\n", st->dropped);
    printf("Записано в архив:        %d\n", st->added);
}

void outputEvents(Event* arr, int n) 
{
    if (arr == NULL || n <= 0) 
    {
        printf("Кэш пуст.\n");
        return;
    }
    printf("\nЗаписи DNS-кэша (%d):\n", n);
    for (int i = 0; i < n; i++) 
    {
        printf("  %d) %02d:%02d %s hits=%d misses=%d\n",
            i + 1, arr[i].h, arr[i].m, arr[i].node,
            arr[i].hits, arr[i].misses);
    }
}