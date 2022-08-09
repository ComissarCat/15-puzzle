#include <iostream>
#include <conio.h>
#include <string>
#include <algorithm>
#include <time.h>
#include <Windows.h>
#include <ctime>

using namespace std;

int** create_field(int length);
void randomize_field(int* temp_array, int length);
void manual_randomize_field(int** array, int* temp_array, int length);
void draw_field(int** array, int length, int& number_of_moves);
void move(int** array, int length, int& number_of_moves, bool& win, int direction, bool& moved);
void check(int** array, int length, bool& win);
void swap_up(int** array, int length, bool& moved);
void swap_down(int** array, int length, bool& moved);
void swap_left(int** array, int length, bool& moved);
void swap_right(int** array, int length, bool& moved);
void player_input(int** array, int length, int& number_of_moves, bool& win, bool& exit);
void menu();
void move_values_from_temp_array(int* temp_array, int** array, int length);

int main()
{
    setlocale(LC_ALL, "Russian");

    menu();

    return 0;
}

void menu()
{
    string bufer;
    do
    {
        system("cls");
        int length = 0, number_of_moves = 0;
        bool win = false, exit = false;
        do
        {
            cout << "Выберите размер поля или выход из игры (small, big, exit): ";
            getline(cin, bufer);
        } while (bufer != "small\0" and bufer != "big\0" and bufer != "exit\0");
        if (bufer == "small\0") length = 3;
        else if (bufer == "big\0") length = 4;
        if (bufer != "exit")
        {
            int** array = create_field(length);
            draw_field(array, length, number_of_moves);
            clock_t start = clock();
            do
            {
                player_input(array, length, number_of_moves, win, exit);
            } while (not win and not exit);
            clock_t end = clock();
            int seconds = (end - start) / CLOCKS_PER_SEC;
            int minutes = 0, hours = 0;
            if (seconds > 60)
            {
                minutes = seconds / 60;
                seconds %= 60;
                if (minutes > 60) hours = minutes / 60;
                minutes %= 60;
            }
            cout << "\n\nПрошло времени: " << hours << ":" << minutes << ":" << seconds;
            if (win) cout << "\n\nПеремога, двух мнений быть не может\n\n";
            else cout << "\n\nЗрада\n\n";
            system("pause");
        }
    } while (bufer != "exit\0");
}

int** create_field(int length)
{    
    int* temp_array = new int[length * length];
    int** array = new int* [length];
    string answer;
    for (int i = 0; i < length; i++)
    {
        array[i] = new int[length];
    }    
    for (int i = 0; i < length * length; i++)
    {
        temp_array[i] = 0;
    }
    move_values_from_temp_array(temp_array, array, length);
    do
    {
        cout << "Размешать поле случайным образом? y/n ";
        getline(cin, answer);
    } while (answer != "y\0" and answer != "n\0");
    if (answer == "y\0")
    {
        randomize_field(temp_array, length);
        move_values_from_temp_array(temp_array, array, length);
    }
    else manual_randomize_field(array, temp_array, length);    
    delete[] temp_array;
    return array;
}

void move_values_from_temp_array(int* temp_array, int** array, int length)
{
    for (int i = 0, k = 0; i < length; i++)
    {
        for (int j = 0; j < length; j++, k++)
        {
            array[i][j] = temp_array[k];
        }
    }
}

void randomize_field(int* temp_array, int length)
{
    srand(time(NULL));
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
        if (not temp_array[i])
        {
            swap(temp_array[i], temp_array[length * length - 1]);
            break;
        }
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
}

void manual_randomize_field(int** array, int* temp_array, int length)
{
    int number_of_moves = 0;    
    for (int i = 0; i < length * length-1; i++)
    {
        draw_field(array, length, number_of_moves);
        cout << "\n\nВводите числа от 1 до " << length * length - 1 << ", чтобы заполнить поле слева направо сверху вниз: ";
        do
        {
            cin >> temp_array[i];
        } while (temp_array[i] < 1 or temp_array[i] > length * length - 1);
        for (int j = 0; j < i; j++)
        {
            if (temp_array[i] == temp_array[j])
            {
                cout << "\n\nЧисло уже занято";
                Sleep(1000);
                temp_array[i] = 0;
                i--;
                break;
            }
        }
        move_values_from_temp_array(temp_array, array, length);
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
    move_values_from_temp_array(temp_array, array, length);
}

void draw_field(int** array, int length, int& number_of_moves)
{
    system("cls");
    if (number_of_moves) cout << "Количество сделанных ходов: " << number_of_moves << "\n\n";
    else cout << "\n\n";
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

void player_input(int** array, int length, int& number_of_moves, bool& win, bool& exit)
{
    int key;
    bool moved = false;
    for (;;)
    {
        key = _getch();
        switch (key)
        {
        case 0x48: key = 1;
            break;
        case 0x50: key = 2;
            break;
        case 0x4B: key = 3;
            break;
        case 0x4D: key = 4;
            break;
        case 0x1B: key = 0;
            break;
        }
        if (not key)
        {
            exit = true;
            break;
        }
        if (key >= 1 and key <= 4) move(array, length, number_of_moves, win, key, moved);
        if (moved) break;
    }
}

void move(int** array, int length, int& number_of_moves, bool& win, int direction, bool& moved)
{
    switch (direction)
    {
    case 1: swap_up(array, length, moved);
        break;
    case 2: swap_down(array, length, moved);
        break;
    case 3: swap_left(array, length, moved);
        break;
    case 4: swap_right(array, length, moved);
        break;
    }
    if (moved)
    {
        number_of_moves++;
        draw_field(array, length, number_of_moves);
        check(array, length, win);
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
