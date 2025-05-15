#include <iostream>
#include <thread>
#include <chrono>
#include <locale>
#include <windows.h>

using namespace std;

// Вывод в терминал
void printArray(int numbers[], int array_size, int highlight1 = -1, int highlight2 = -1, bool sorted = false, bool swapped = false){
    cout << "\33[2K\r"; // Очищает строку
    for (int i = 0; i < array_size; ++i) {
        if (i == highlight1 || i == highlight2){
            if (swapped){
                cout << "\033[1;33m" << numbers[i] << "\033[0m "; // Жёлтый цвет
            }else{
                cout << "\033[1;31m" << numbers[i] << "\033[0m "; // Красный цвет
            }
        }else if (sorted){
            cout << "\033[1;32m" << numbers[i] << "\033[0m "; // Зелёный цвет
        }else{
            cout << numbers[i] << " "; // Обычный вывод
        }
    }
    this_thread::sleep_for(chrono::milliseconds(500)); // Задержка 500 мс
}

// Алгоритмы

void bubbleSort(int numbers[], int array_size){
    for (int step = 0; step < array_size - 1; step++){
        for(int next_step = 0; next_step < array_size - step - 1; next_step++){
            printArray(numbers, array_size, next_step, next_step + 1); // Выводит промежуточный результат
            if(numbers[next_step] > numbers[next_step + 1]){
                int temp = numbers[next_step];
                numbers[next_step] = numbers[next_step + 1];
                numbers[next_step + 1] = temp;
                printArray(numbers, array_size, next_step, next_step + 1, false, true); // Выводит промежуточный результат
            }
        }
    }
    printArray(numbers, array_size, -1, -1, true);
}

void shellSort(int numbers[], int array_size){
    for (int gap = array_size / 2; gap > 0; gap /= 2){
        for (int i = gap; i < array_size; i++){
            bool swapped = false;
            int temp = numbers[i];
            int j = i;
            printArray(numbers, array_size, i, i - gap);
            for (j; j >= gap; j -= gap){
                if(gap && numbers[j - gap] > temp){
                    swapped = true;
                    numbers[j] = numbers[j - gap];
                }else{
                    break;
                }
            }
            numbers[j] = temp;
            if (swapped){
                printArray(numbers, array_size, i, i - gap, false, true);
            }
        }
    }
    printArray(numbers, array_size, -1, -1, true);
}

void selectionSort(int numbers[], int array_size){
    for (int step = 0; step < array_size - 1; step++){
        int min_idx = step;
        for (int next_step = step + 1; next_step < array_size; next_step++){
            printArray(numbers, array_size, min_idx, next_step);
            if (numbers[next_step] < numbers[min_idx]){
                min_idx = next_step;
            }
        }
        if(min_idx != step){
            int temp = numbers[min_idx];
            numbers[min_idx] = numbers[step];
            numbers[step] = temp;
            printArray(numbers, array_size, min_idx, step, false, true);
        }
    }
    printArray(numbers, array_size, -1, -1, true);
}

void bogoSort(int numbers[], int array_size){
    while (true){
        bool sorted = true;
        for (int i = 0; i < array_size - 1; i++){
            if (numbers[i] > numbers[i + 1]){
                sorted = false;
                break;
            }
        }
        if (sorted){
            printArray(numbers, array_size, -1, -1, true);
            break;
        }

        for (int i = 0; i < array_size; i++){
            int random_index = rand() % array_size;
            printArray(numbers, array_size, i, random_index);
            int temp = numbers[i];
            numbers[i] = numbers[random_index];
            numbers[random_index] = temp;
            printArray(numbers, array_size, i, random_index, false, true);
        }
    }
}

int main() {
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
    setlocale(LC_ALL, ".UTF8");

    int numbers[] = {1, 8, 9, 7, 4, 5, 3, 2, 6};
    int array_size = sizeof(numbers) / sizeof(numbers[0]);
    char choice = 'N';

    cout << "Ввести собственный массив чисел? (Y, N - default): ";
    cin >> choice;

    if(choice == 'Y'){
        cout << "Введите количество чисел: ";
        cin >> array_size;
        cout << "Введите числа через пробел: ";
        for (int i = 0; i < array_size; i++){
            cin >> numbers[i];
        }
        cout << "Введённый массив: [ ";
        for (int i = 0; i < array_size; i++){
            cout << numbers[i] << " ";
        }
        cout << "]" << endl;
    }

    choice = '0';

    cout << "Выберите алгоритм сортировки (0 - Bubble Sort - default, 1 - Shell Sort, 2 - Selection Sort, 3 - Bogo Sort): " << endl;
    cin >> choice;
    switch (choice) {
        case '0':
            cout << "Bubble Sort" << endl;
            bubbleSort(numbers, array_size);
            break;
        case '1':
            cout << "Shell Sort" << endl;
            shellSort(numbers, array_size);
            break;
        case '2':
            cout << "Selection Sort" << endl;
            selectionSort(numbers, array_size);
            break;
        case '3':
            cout << "Bogo Sort" << endl;
            bogoSort(numbers, array_size);
            break;
        default:
            cout << "Неверный выбор. Используется Bubble Sort по умолчанию." << endl;
            bubbleSort(numbers, array_size);
    }
    return 0;
}