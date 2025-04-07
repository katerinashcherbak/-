#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>
#include <cstring>
#include <windows.h>
using namespace std;

const char ua[] = "абвгґдезийклмнопрстуфхц";
const char* en[] = {
    "a", "b", "v", "h", "g", "d", "e", "z", "y", "i", "k", "l", "m", "n",
    "o", "p", "r", "s", "t", "u", "f", "kh", "ts"
};
const int N = sizeof(ua) - 1;
void transliterate_ua_to_en_line(const char* line, FILE* out) {
    for (int i = 0; line[i] != '\0'; ++i) {
        bool found = false;
        char c = line[i];
        for (int j = 0; j < N; ++j) {
            if (tolower(c) == ua[j]) {
                fputs(en[j], out);
                found = true;
                break;
            }
        }
        if (!found) {
            fputc(c, out);
        }
    }
}

void transliterate_en_to_ua_line(const char* line, FILE* out) {
    int i = 0;
    while (line[i] != '\0') {
        bool found = false;
        for (int j = 0; j < N; ++j) {
            int len = strlen(en[j]);
            int match = 1;
            for (int k = 0; k < len; ++k) {
                if (line[i + k] != en[j][k]) {
                    match = 0;
                    break;
                }
            }
            if (match) {
                fputc(ua[j], out);
                i += len;
                found = true;
                break;
            }
        }
        if (!found) {
            fputc(line[i], out);
            ++i;
        }
    }
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    int choice;
    cout << "Меню транслітерації" << endl;
    cout << "1. Українська → Англійська" << endl;
    cout << "2. Англійська → Українська" << endl;
    cout << "Оберіть напрям транслітерації (1 або 2): ";
    cin >> choice;
    FILE* in = fopen("Input.txt", "r");
    FILE* out = fopen("Result.txt", "w");

    if (!in || !out) {
        cout << "Помилка відкриття або створення файлів" << endl;
        return 1;
    }

    char line[1024];  
    while (fgets(line, sizeof(line), in)) {
        if (choice == 1) {
            transliterate_ua_to_en_line(line, out);
        }
        else if (choice == 2) {
            transliterate_en_to_ua_line(line, out);
        }
        else {
            cout << "Невірний вибір!" << endl;
            fclose(in);
            fclose(out);
            return 1;
        }
    }

    fclose(in);
    fclose(out);

    cout << "Текст транслітеровано в файл Result.txt" << endl;
    return 0;
}
