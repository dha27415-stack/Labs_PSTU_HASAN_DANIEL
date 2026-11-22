#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>

using namespace std;

// Структура "Стадион" (Вариант 23)
struct Stadium {
    char name[60];      // название
    int year;           // год постройки
    int courts;         // количество площадок
    char sports[100];   // виды спорта
};

// Вспомогательная функция ввода одной структуры с клавиатуры
Stadium inputStadium() {
    Stadium s;
    cout << "Enter stadium name: ";
    cin.getline(s.name, 60);
    if (strlen(s.name) == 0) {
        cin.getline(s.name, 60);
    }

    cout << "Enter year built: ";
    cin >> s.year;

    cout << "Enter number of courts: ";
    cin >> s.courts;

    cin.ignore();
    cout << "Enter sports types: ";
    cin.getline(s.sports, 100);

    return s;
}

// 1. Функция формирования двоичного файла
void createFile(const char* filename, int count) {
    FILE* fp = fopen(filename, "wb");
    if (fp == NULL) {
        perror("Error opening file for writing");
        return;
    }

    for (int i = 0; i < count; ++i) {
        cout << "\n--- Stadium #" << (i + 1) << " ---\n";
        Stadium s = inputStadium();
        size_t written = fwrite(&s, sizeof(Stadium), 1, fp);
        if (written != 1 || ferror(fp)) {
            perror("Error writing record to file");
            fclose(fp);
            return;
        }
    }

    if (fclose(fp) != 0) {
        perror("Error closing file after writing");
    }
}

// 2. Функция печати содержимого двоичного файла
void printFile(const char* filename) {
    FILE* fp = fopen(filename, "rb");
    if (fp == NULL) {
        perror("Error opening file for reading");
        return;
    }

    Stadium s;
    int index = 1;
    bool hasRecords = false;

    cout << "\n=== Binary File Content ===\n";
    while (fread(&s, sizeof(Stadium), 1, fp) == 1) {
        hasRecords = true;
        cout << index++ << ". Name: " << s.name
            << " | Year: " << s.year
            << " | Courts: " << s.courts
            << " | Sports: " << s.sports << endl;
    }

    if (ferror(fp)) {
        perror("Error reading record from file");
    }
    else if (!hasRecords) {
        cout << "File is empty.\n";
    }

    if (fclose(fp) != 0) {
        perror("Error closing file after reading");
    }
}

// 3. Функция поиска индекса (1-based) элемента с указанным номером
int findByNumber(const char* filename, int targetNumber) {
    if (targetNumber <= 0) return -1;

    FILE* fp = fopen(filename, "rb");
    if (fp == NULL) {
        perror("Error opening file for search");
        return -1;
    }

    Stadium s;
    int currentIndex = 1;
    int foundIndex = -1;

    while (fread(&s, sizeof(Stadium), 1, fp) == 1) {
        if (currentIndex == targetNumber) {
            foundIndex = currentIndex;
            break;
        }
        currentIndex++;
    }

    if (ferror(fp)) {
        perror("Error during file search");
    }

    fclose(fp);
    return foundIndex;
}

// 4. Функция удаления всех элементов, у которых год постройки меньше заданного
void deleteOlderThanYear(const char* filename, int minYear) {
    FILE* src = fopen(filename, "rb");
    if (src == NULL) {
        perror("Error opening source file for deletion");
        return;
    }

    const char* tempName = "temp_delete.bin";
    FILE* dst = fopen(tempName, "wb");
    if (dst == NULL) {
        perror("Error creating temporary file for deletion");
        fclose(src);
        return;
    }

    Stadium s;
    int deletedCount = 0;

    while (fread(&s, sizeof(Stadium), 1, src) == 1) {
        if (s.year >= minYear) {
            if (fwrite(&s, sizeof(Stadium), 1, dst) != 1 || ferror(dst)) {
                perror("Error writing to temporary file");
                fclose(src);
                fclose(dst);
                remove(tempName);
                return;
            }
        }
        else {
            deletedCount++;
        }
    }

    if (ferror(src)) {
        perror("Error reading source file during deletion");
    }

    fclose(src);
    fclose(dst);

    if (remove(filename) != 0) {
        perror("Error removing original file");
        return;
    }
    if (rename(tempName, filename) != 0) {
        perror("Error renaming temporary file");
        return;
    }

    cout << "Deleted records count: " << deletedCount << endl;
}

// 5. Функция добавления 2 элементов перед элементом с указанным номером
void insertTwoBeforeNumber(const char* filename, int targetNumber) {
    int pos = findByNumber(filename, targetNumber);
    if (pos == -1) {
        cout << "Element with number " << targetNumber << " not found. No insertion performed.\n";
        return;
    }

    FILE* src = fopen(filename, "rb");
    if (src == NULL) {
        perror("Error opening source file for insertion");
        return;
    }

    const char* tempName = "temp_insert.bin";
    FILE* dst = fopen(tempName, "wb");
    if (dst == NULL) {
        perror("Error creating temporary file for insertion");
        fclose(src);
        return;
    }

    Stadium s;
    int currentIndex = 1;
    bool inserted = false;

    while (fread(&s, sizeof(Stadium), 1, src) == 1) {
        if (currentIndex == pos && !inserted) {
            cout << "\nEnter 2 new stadiums to insert before #" << targetNumber << ":\n";
            for (int k = 0; k < 2; ++k) {
                cout << "--- New Stadium #" << (k + 1) << " ---\n";
                Stadium newS = inputStadium();
                if (fwrite(&newS, sizeof(Stadium), 1, dst) != 1 || ferror(dst)) {
                    perror("Error writing new stadium to temporary file");
                    fclose(src);
                    fclose(dst);
                    remove(tempName);
                    return;
                }
            }
            inserted = true;
        }

        if (fwrite(&s, sizeof(Stadium), 1, dst) != 1 || ferror(dst)) {
            perror("Error copying existing stadium to temporary file");
            fclose(src);
            fclose(dst);
            remove(tempName);
            return;
        }
        currentIndex++;
    }

    if (ferror(src)) {
        perror("Error reading source file during insertion");
    }

    fclose(src);
    fclose(dst);

    if (remove(filename) != 0) {
        perror("Error removing original file after insertion");
        return;
    }
    if (rename(tempName, filename) != 0) {
        perror("Error renaming temporary file after insertion");
        return;
    }

    cout << "Successfully inserted 2 elements before #" << targetNumber << ".\n";
}

int main() {
    const char* filename = "stadiums.bin";
    int count = 0;

    cout << "Enter initial number of stadiums (at least 5): ";
    cin >> count;
    if (count < 5) {
        cout << "Please enter at least 5 stadiums according to instructions.\n";
        return 1;
    }

    // 1. Формирование файла
    createFile(filename, count);

    // 2. Печать исходного файла
    printFile(filename);

    // 3. Удаление элементов с годом постройки меньше заданного
    int minYear = 0;
    cout << "\nEnter minimum year (delete stadiums built BEFORE this year): ";
    cin >> minYear;
    deleteOlderThanYear(filename, minYear);
    printFile(filename);

    // 4. Добавление 2 элементов перед элементом с указанным номером
    int targetNum = 0;
    cout << "\nEnter target record number to insert 2 elements BEFORE: ";
    cin >> targetNum;
    insertTwoBeforeNumber(filename, targetNum);
    printFile(filename);

    return 0;
}