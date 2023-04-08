#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <conio.h>
#include <windows.h> 
#include <locale.h>

#define MAX_WORDS 1000
#define MAX_WORD_LENGTH 1000
#define PAGE_SIZE 1000

void printText(char words[MAX_WORDS][MAX_WORD_LENGTH], int totalWords) {
    int currentPage = 0;
    int remainingWords = totalWords;
    while (remainingWords > 0) {
        int wordsToPrint = remainingWords > PAGE_SIZE ? PAGE_SIZE : remainingWords;
        for (int i = 0; i < wordsToPrint; i++) {
            printf("%s ", words[currentPage * PAGE_SIZE + i]);
        }
        printf("\n");
        currentPage++;
        remainingWords -= wordsToPrint;
    }
}

void setConsoleTextColor(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

int main() {
    setlocale(LC_ALL, "Rus");
    printf("Добро пожаловать в игру скорости печати на языке C!\n");
    printf("Введите слова, предложенные ниже, как можно быстрее и точнее.\n");

    printf("Нажмите Enter, чтобы начать...\n");
    getchar();

    FILE* file = fopen("text.txt", "r"); // Имя файла с текстом или набором слов
    if (file == NULL) {
        printf("Ошибка открытия файла.\n");
        return 1;
    }

    char words[MAX_WORDS][MAX_WORD_LENGTH];
    int totalWords = 0;
    while (totalWords < MAX_WORDS && fgets(words[totalWords], MAX_WORD_LENGTH, file) != NULL) {
        // Удаляем символ новой строки из считанного слова
        words[totalWords][strcspn(words[totalWords], "\n")] = '\0';
        totalWords++;
    }

    fclose(file);

    printf("\nТекст:\n");
    printText(words, totalWords);

    int totalWordsTyped = 0;
    int totalWordsCorrect = 0;
    int currentCharIndex = 0;

    clock_t startTime = clock(); // Засекаем время начала игры

    printf("%s: ", words[totalWordsTyped]);
    char userInput[MAX_WORD_LENGTH];
    char currentChar;

    do {
        currentChar = getch();
        if (currentChar == words[totalWordsTyped][currentCharIndex]) {
            setConsoleTextColor(10); // Зеленый цвет
            printf("%c", currentChar);
            setConsoleTextColor(15); // Возвращаем белый цвет
            currentCharIndex++;
        }
        else {
            setConsoleTextColor(12); // Красный цвет
            printf("%c", currentChar);
            setConsoleTextColor(15); // Возвращаем белый цвет
            currentCharIndex++;
        }

        if (currentCharIndex == strlen(words[totalWordsTyped])) {
            printf("\n");
            if (strcmp(userInput, words[totalWordsTyped]) == 0) {
                totalWordsCorrect++;
            }
            totalWordsTyped++;
            currentCharIndex = 0;
            if (totalWordsTyped < totalWords) {
                printf("%s: ", words[totalWordsTyped]);
            }
        }

    } while (totalWordsTyped < totalWords);

    clock_t endTime = clock(); // Засекаем время окончания игры

    double totalTime = (double)(endTime - startTime) / CLOCKS_PER_SEC;
    double accuracy = (double)totalWordsCorrect / totalWords * 100;
    double speed = (double)totalWords / totalTime * 60;

    printf("\n\nИгра окончена!\n");
    printf("Общее время: %.2f сек\n", totalTime);
    printf("Точность: %.2f%%\n", accuracy);
    printf("Скорость: %.2f слов/мин\n", speed);

    return 0;
}
