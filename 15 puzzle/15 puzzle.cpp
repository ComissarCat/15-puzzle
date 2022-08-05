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
void swap_up(int** array, int length, bool& moved);
void swap_down(int** array, int length, bool& moved);
void swap_left(int** array, int length, bool& moved);
void swap_right(int** array, int length, bool& moved);

int main()
{
    setlocale(LC_ALL, "Russian");

    int length = 3, number_of_moves = 0;
    bool win = false;
    int** array = create_field(length);
    draw_field(array, length, number_of_moves);
    do
    {        
        move(array, length, number_of_moves, win);
    } while (not win);
    cout << "\n\nеее побiда";

    return 0;
}

int** create_field(int length)
{
    srand(time(NULL));
    int* temp_array = new int[length * length];
    int** array = new int* [length];    
    for (int i = 0; i < length; i++)
    {
        array[i] = new int[length];
    }
    for (int i = 0; i < length * length; i++)
    {
        temp_array[i] = i;
    }    
    for (int i = 0; i < rand() % 91 + 10; i++)
    {
        swap(temp_array[rand() % (length * length)], temp_array[rand() % (length * length)]);
    }    
    for (int i = 0; i < length * length - 1; i++)
    {
        if (not temp_array[i]) swap(temp_array[i], temp_array[length * length - 1]);
    }    
    int chaos = 0;    
    for (int i = 0; i < length * length - 1; i++)
    {
        for (int j = i + 1; j < length * length - 1; j++)
        {
            if (temp_array[i] > temp_array[j]) chaos++;
        }
    }
    if (chaos % 2) swap(temp_array[length * length - 3], temp_array[length * length - 2]);
    for (int i = 0, k = 0; i < length; i++)
    {
        for (int j = 0; j < length; j++, k++)
        {
            array[i][j] = temp_array[k];
        }
    }
    delete[] temp_array;
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
            case (0x4B): swap_left(array, length, moved);
                break;
            case 0x48: swap_up(array, length, moved);            
                break;
            case 0x4D: swap_right(array, length, moved);
                break;
            case 0x50: swap_down(array, length, moved);
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

void swap_up(int** array, int length, bool& moved)
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
}

void swap_down(int** array, int length, bool& moved)
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
}

void swap_left(int** array, int length, bool& moved)
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
}

void swap_right(int** array, int length, bool& moved)
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
}