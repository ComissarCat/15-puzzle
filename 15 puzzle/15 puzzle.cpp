#include <iostream>
#include <conio.h>
#include <math.h>
#include <algorithm>
#include <time.h>
#include <Windows.h>

using namespace std;

int** create_field(int length);
void draw_field(int** array, int length, int& number_of_moves);
void move(int** array, int length, int& number_of_moves, bool& win);
void check(int** array, int length, bool& win);

int main()
{
    setlocale(LC_ALL, "Russian");

    int length = 3, number_of_moves = 0;
    bool win = false;
    int** array = create_field(length);
    draw_field(array, length, number_of_moves);
    do
    {
        Sleep(500);
        move(array, length, number_of_moves, win);
    } while (not win);
    cout << "\n\nеее побiда";

    return 0;
}

int** create_field(int length)
{    
    srand(time(NULL));
    int** array = new int* [length];
    for (int i = 0; i < length; i++)
    {
        array[i] = new int[length];
    }
    for (int i = 0, k = 0; i < length; i++)
    {
        for (int j = 0; j < length; j++, k++)
        {
            array[i][j] = k;
        }
    }
    for (int i = 0; i < rand() % 91 + 10; i++)
    {
        swap(array[rand() % length][rand() % length], array[rand() % length][rand() % length]);
    }
    int chaos = 0;
    for (int i = 0; i < length; i++)
    {
        for (int j = 0; j < length; j++)
        {
            int k = array[i][j];
            for (int l = i; l < length; l++)
            {
                for (int m = j + 1; m < length; m++)
                {
                    if (k > array[i][j]) chaos++;
                }
            }
        }
    }
    if (chaos % 2) swap(array[length - 1][length - 2], array[length - 1][length - 1]);
    return array;
}

void draw_field(int** array, int length, int& number_of_moves)
{
    system("cls");
    cout << "Количество сделанных ходов: " << number_of_moves << "\n\n";
    for (int i = 0; i < length; i++)
    {
        cout << "+";
        for (int j = 0; j < length; j++)
        {
            cout << "---+";
        }
        cout << "\n|";
        for (int j = 0; j < length; j++)
        {
            if (array[i][j] < 10) cout << " ";
            if (not array[i][j]) cout << "  ";
            if (array[i][j]) cout << " " << array[i][j];
            cout << "|";
        }
        cout << endl;
    }
    cout << "+";
    for (int j = 0; j < length; j++)
    {
        cout << "---+";
    }
}

void move(int** array, int length, int& number_of_moves, bool& win)
{
    int k1, k2;
    bool moved = false;
    for (;;)
    {
        k1 = _getch();
        if (k1 == 0xE0 || k1 == 0x00)
        {
            k2 = _getch();
            switch (k2)
            {
            case (0x4B): // Влево
            {                
                for (int i = 0; i < length; i++)
                {
                    for (int j = 0; j < length; j++)
                    {
                        if (not (array[i][j]) and ((j + 1) < length))
                        {
                            swap(array[i][j], array[i][j + 1]);
                            moved = true;                            
                            break;
                        }
                        if (moved) break;
                    }
                }
            };
                break;
            case 0x48: // Вверх
            {                
                for (int i = 0; i < length; i++)
                {
                    for (int j = 0; j < length; j++)
                    {
                        if (not (array[i][j]) and ((i + 1) < length))
                        {
                            swap(array[i][j], array[i + 1][j]);
                            moved = true;                            
                            break;
                        }
                        if (moved) break;
                    }
                }
            };
                break;
            case 0x4D: // Вправо
            {                
                for (int i = 0; i < length; i++)
                {
                    for (int j = 0; j < length; j++)
                    {
                        if (not (array[i][j]) and ((j - 1) >= 0))
                        {
                            swap(array[i][j], array[i][j - 1]);
                            moved = true;                            
                            break;
                        }
                        if (moved) break;
                    }
                }
            };
                break;
            case 0x50: // Вниз
            {                
                for (int i = 0; i < length; i++)
                {
                    for (int j = 0; j < length; j++)
                    {
                        if (not (array[i][j]) and ((i - 1) >= 0))
                        {
                            swap(array[i][j], array[i - 1][j]);
                            moved = true;
                            break;
                        }
                        if (moved) break;
                    }
                }
            };
                break;
            }
        }
        if (moved)
        {
            number_of_moves++;
            draw_field(array, length, number_of_moves);
            check(array, length, win);
            break;
        }
    }
}

void check(int** array, int length, bool& win)
{    
    if (array[0][0] == 1 and array[length - 1][length - 1] == 0)
    {
        win = true;
        for (int i = 0, k = 1; i < length; i++)
        {
            for (int j = 0; j < length; j++, k++)
            {
                if ((i == length - 1) and (j == length - 1)) break;
                if (array[i][j] != k)
                {
                    win = false;
                    break;
                }
            }
            if (not win) break;
        }        
    }
}