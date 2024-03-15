#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <malloc.h>
#include <math.h>

void printmatrix(int, int, float **);
void randmatrix(int, int, float **);
void avgstr(int, int, float **, float);
void firsthalf(int, int, float **);
void seccondhalf(int, int, float **);
void gauss(int, int, float **);

int main()
{

    int choice, i, j, N, value;

    printf("Что вы хотите сделать?\n 1 - Привести матрицу, состоящуюю из коэффициентов системы линейных уравнений, к треугольному(Ступенчатому) виду.\n 2 - Найти количество строк, среднее арифметической элементов которых меньше заданной величины.\n 3 - Определить сумму элементов каждого столбца левой половины и сумму элементов каждого четного столбца правой половины матрицы а.\n 4 - Сформировать результирующий одномерный массив, элементами которого являются строчные суммы тех строк, которые начинаются с k идущих подряд положительных чисел.\n 5 - завершить программу.\n");
    scanf("%d", &choice);
    switch (choice)
    {
    case 1:
    {
        int m, n;
        srand(time(NULL));
        printf("Введите количество переменных:\n");
        scanf("%d", &N);
        m = N;
        n = N + 1;
        float **mas = (float **)malloc(m * sizeof(float *));
        for (i = 0; i < m; i++)
        {
            *(mas + i) = (float *)malloc(n * sizeof(float));
        }
        printf("Будет задана матрица %d-ого порядка.\n Введите коэффициенты уравнений(заполняется сверху-вниз, слева-направо)\n", N);

        for (i = 0; i < m; i++)
        {
            for (j = 0; j < n; j++)
            {
                *(*(mas + i) + j) = rand() % 1000 - 500;
            }
        }
        printf("\n");
        printmatrix(m, n, mas);

        gauss(m, n, mas);

        printmatrix(m, n, mas);

        free(mas);
    }
    break;

    case 2:
    {
        int m, n, count;
        float summ, num, mid;
        printf("Введите размер матрицы:\nm: ");
        scanf("%d", &m);
        printf("n: ");
        scanf("%d", &n);
        srand(time(NULL));
        float **mas = (float **)malloc(m * sizeof(float *)); // задание матрицы
        for (i = 0; i < m; i++)
        {
            *(mas + i) = (float *)malloc(n * sizeof(float));
        }
        randmatrix(m, n, mas);
        printmatrix(m, n, mas);

        printf("Введите число, которое не должно превышать среднее арифметическое элементов строки матрицы: ");
        scanf("%f", &num);
        avgstr(m, n, mas, num);

        for (i = 0; i < m; i++)
        {
            free(*(mas + i));
        }
        free(mas);
    }
    break;

    case 3:
    {
        srand(time(NULL));
        int n = 1;
        // задание случайного n, кратного 4.
        for (i;; i++)
        {
            if (n % 4 == 0 && n != 0)
            {
                break;
            }
            else
            {
                n = rand() % 12 + 1;
            }
        }

        int m = rand() % 12 + 1;
        // вывод m,n
        printf("m=%d, n=%d\n", m, n);
        // инициализация массива
        float **mas = (float **)malloc(m * sizeof(float *));
        for (i = 0; i < m; i++)
        {
            *(mas + i) = (float *)malloc(n * sizeof(float));
        }
        // заполнение массива числами
        for (i = 0; i < m; i++)
        {
            for (j = 0; j < n; j++)
            {
                *(*(mas + i) + j) = rand() % 1000 - 500;
            }
        }

        printmatrix(m, n, mas);

        firsthalf(m, n, mas);
        printf("\n");
        seccondhalf(m, n, mas);
        free(mas);
    }
    break;

    case 4:
    {
        srand(time(NULL));
        int m = rand() % 5 + 3;
        int n = rand() % 5 + 3;

        int l, count, countmas;
        int k;
        float summ;

        float **mas = (float **)malloc(m * sizeof(float *));
        for (i = 0; i < m; i++)
        {
            *(mas + i) = (float *)malloc(n * sizeof(float));
        }

        float *mas1 = (float *)malloc(count * sizeof(float *));

        for (i = 0; i < m; i++)
        {
            for (j = 0; j < n; j++)
            {
                *(*(mas + i) + j) = rand() % 20 - 10;
            }
        }
        printmatrix(m, n, mas);

        printf("Введите количество положительных элементов в начале строки k:");
        scanf("%d", &k);

        countmas = 0;
        for (i = 0; i < m; i++)
        {
            summ = 0;
            count = 0;
            for (j = 0; j < n; j++)
            {
                if (count < k && *(*(mas + i) + j) > 0)
                {
                    summ += *(*(mas + i) + j);
                    count += 1;
                }
                else if (count >= k)
                {
                    summ += *(*(mas + i) + j);
                }
                else if (count < k && *(*(mas + i) + j) <= 0)
                {
                    summ = 0;
                    break;
                }
            }

            if (summ != 0)
            {
                printf("сумма %d-ой строки: %f\n", i, summ);
                countmas += 1;
            }
            else if (count < k && summ == 0)
            {
                printf("сумма %d-ой строки равна: %f\n", i, summ);
            }
            printf("count: %d\n\n", count);

            if (count == k)
            {
                *(mas1 + l) = summ;
                l += 1;
            }
        }

        printf("Итоговый массив: \n");
        for (i = 0; i < countmas; i++)
        {
            printf("%f ", *(mas1 + i));
        }

        free(mas);
        free(mas1);
    }
    break;

    case 5:
    {
        exit(1);
    }
    break;

    default:
    {
        break;
    }
    }
}

void printmatrix(int m, int n, float **mas)
{
    int i, j;
    printf("Ваша матрица:\n"); // вывод прямоугольной матрицы
    for (i = 0; i < m; i++)
    {
        for (j = 0; j < n; j++)
        {
            if (j < (n - 1))
            {
                printf("%.2lf ", *(*(mas + i) + j));
            }
            else
            {
                printf("%.2lf \n", *(*(mas + i) + j));
            }
        }
    }
}

void randmatrix(int m, int n, float **mas)
{
    int a, b, i, j;
    printf("Введите диапазон генерации:");
    scanf("%d %d", &a, &b);
    for (i = 0; i < m; i++) // рандомная генерация матрицы
    {
        for (j = 0; j < n; j++)
        {
            if (a < 0)
            {
                *(*(mas + i) + j) = rand() % (2 * b) + a;
            }
            else
            {
                *(*(mas + i) + j) = rand() % b;
            }
        }
    }
}

void avgstr(int m, int n, float **mas, float num)
{
    int i, j, count;
    float summ, mid;
    count = 0;
    for (i = 0; i < m; i++)
    {
        summ = 0;
        for (j = 0; j < n; j++)
        {
            summ += *(*(mas + i) + j);
            mid = summ / n;
        }
        if (mid <= num)
        {
            count += 1;
            printf("Сумма %d-ой строки: %.2f\n", i + 1, mid);
        }
    }
    printf("Число таких строк: %d\n", count);
}

void firsthalf(int m, int n, float **mas)
{
    int i, j;
    int half = n / 2;
    float summ;

    for (j = 0; j < half; j++)
    {
        summ = 0;
        for (i = 0; i < m; i++)
        {
            summ += *(*(mas + i) + j);
        }
        printf("Сумма %d-ого столбца в первой половине: %f\n", j, summ);
    }
}

void seccondhalf(int m, int n, float **mas)
{
    int i, j, half;
    int count = 0;
    float summ;
    for (j = half; j < n; j++)
    {
        summ = 0;
        if (j % 2 == 0)
        {
            for (i = 0; i < m; i++)
            {
                summ += *(*(mas + i) + j);
            }
            count += 1;
            printf("Сумма %d-ого четного столбца с индексом(%d)(считая от середины матрицы) во второй половине: %lf\n", count, j - half, summ);
        }
    }
}

void gauss(int m, int n, float **mas)
{

    float *temp;
    float temp2;
    int i, j;

    for (i = 0; i < m - 1; i++) // поднимает строку, первый элемент которой равен единице, на первую позицию, а нулю - на одну вниз
    {
        for (j = 0; j < 1; j++)
        {
            temp = 0;
            if (*(*(mas + i + 1) + j) == 1 || *(*(mas + i + 1) + j) == -1)
            {
                temp = *(mas + i + 1);
                *(mas + i + 1) = *(mas + 0);
                *(mas + 0) = temp;
            }
            else if (*(*(mas + i) + j) == 0)
            {
                temp = *(mas + i);
                *(mas + i) = *(mas + i + 1);
                *(mas + i + 1) = temp;
            }
        }
    }

    for (i = 1; i < m - 1; i++) // спускает строку на единицу, если a[n][n] элемент матрицы равен 0
    {
        for (j = 1; j < n - 2; j++)
        {
            temp = 0;
            if (j == i && *(*(mas + i) + j) == 0)
            {
                temp = *(mas + i);
                *(mas + i) = *(mas + i + 1);
                *(mas + i + 1) = temp;
            }
        }
    }

    float a, b, c; // основной метод гаууса
    int count;
    for (i = 1; i < m; i++)
    {
        for (j = 0; j < i; j++)
        {
            printf("\n c = %f\n", c);
            for (count = 0; count < n - 1; count++)
            {

                a = *(*(mas + 0) + count);
                b = *(*(mas + i) + j);
                c = b / a;

                if (c == *(*(mas + i) + j))
                {
                    *(*(mas + i) + j) += -1 * c;
                }
                else if (c == -1 * *(*(mas + i) + j))
                {
                    *(*(mas + i) + j) += c;
                }
                else if (c == 1)
                {
                    *(*(mas + i) + j) += -1 * *(*(mas + i) + j);
                }
                else if (c == -1)
                {
                    *(*(mas + i) + j) += a;
                }
                else  {
                    *(*(mas + i) + j) += -1 * a * c;
                }
            }
        }
    }
}