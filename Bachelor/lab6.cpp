#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <cstdlib>

using namespace std;

int main() {
    // Принудительно устанавливаем кодировку UTF-8 для консоли Windows, чтобы избежать появления квадратиков
    system("chcp 65001 > nul");

    // База данных слов: английские слова и их русские эквиваленты
    const int DB_SIZE = 4;
    const char* eng_words[DB_SIZE] = { "THIS", "IS", "A", "TABLE" };
    const char* rus_words[DB_SIZE] = { "ETO", "", "", "STOL" }; // Можно заменить на "ЭТО" и "СТОЛ"

    char input[256];
    char result[512] = ""; // Результирующая строка для перевода

    // Ввод предложения с клавиатуры (слова разделены символом '_')
    cout << "Enter an English sentence (words separated by '_'): ";
    cin.getline(input, 256);

    // Разделение строки на отдельные слова с помощью функции strtok
    char* word = strtok(input, "_");
    bool first_word = true;

    while (word != nullptr) {
        const char* translated = word; // По умолчанию оставляем исходное английское слово, если оно не найдено в базе

        // Поиск введенного слова в базе данных
        for (int i = 0; i < DB_SIZE; i++) {
            if (strcmp(word, eng_words[i]) == 0) {
                translated = rus_words[i];
                break;
            }
        }

        // Если перевод существует и длина не равна нулю, добавляем его в результирующую строку
        if (strlen(translated) > 0) {
            if (!first_word) {
                strcat(result, "_"); // Добавляем символ подчеркивания между словами
            }
            strcat(result, translated);
            first_word = false;
        }

        // Переход к следующему слову в предложении
        word = strtok(nullptr, "_");
    }

    // Вывод итогового результата перевода
    cout << "Translation: " << result << endl;

    return 0;
}