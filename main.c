#define _CRT_SECURE_NO_WARNINGS

#include "Header.h"

int main()
{
    setlocale(LC_ALL, "");

    FILE* file_input = fopen("input.txt","r");
    FILE* file_output = fopen("output.txt", "w");
    FILE* file_keyword = fopen("keyword.txt", "r");
    FILE* file_decode = fopen("decode.txt", "w");

    wchar_t keyword[256] = { L'\0' };
    wchar_t code[256] = { L'\0' };

    wchar_t alphabet[] = L"абвгдеёжзийклмнопрстуфхцчшщъьыэюя";

    wchar_t matrix[6][6] = { '\0' };

    int x = 1;

    fgetws(keyword, 256, file_keyword);
    fgetws(code, 256, file_input);

    wprintf(L"Кодовое слово - %ls", keyword);

    fclose(file_input);
    fclose(file_keyword);
    if (x != 1 && x != 2)
    {
        wprintf(L"value entered incorrectly");
        exit(0);
    }

    int q = 0;
    while (q == 0)
    {
        for (int i = 0; i < wcslen(keyword); i++)
        {
            if (iswupper(keyword[i]))
                keyword[i] = towlower(keyword[i]);
        }
        for (int i = 0; i < wcslen(keyword); i++)
        {
            if (iswalpha(keyword[i]))
                q = 1;
            else
            {
                wprintf(L"Символ %c не поддерживается (позиция %d) ", keyword[i], i + 1);
                q = 0;
                break;
            }
        }
    }

    for (int i = 1; i < wcslen(keyword); i++)
    {
        if (keyword[i - 1] == keyword[i])
        {
            wcscpy(&keyword[i], &keyword[i + 1]);
            i--;
        }
    }

    // удаление букв ключевого слова из алфавита
    for (int i = 0; i < wcslen(keyword); i++)
    {
        for (int j = 0; j < wcslen(alphabet); j++)
        {
            if (keyword[i] == alphabet[j])
                wcscpy(&alphabet[j], &alphabet[j + 1]);
        }
    }

    // ввод данных в массив
    wprintf(L"\nkey matrix: \n");
    int k = 0, m = 0;
    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 6; j++)
        {
            if (k < wcslen(keyword))
            {
                matrix[i][j] = keyword[k];
            }
            if (k >= wcslen(keyword))
            {
                matrix[i][j] = alphabet[m];
                m++;
            }
            k++;
        }
    }

    // вывод массива
    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 6; j++)
        {
            wprintf(L"%c ", matrix[i][j]);
        }
        wprintf(L"\n");
    }

    int p = 0;

    while (p == 0) 
    {
        // проверка на верхний регистр
        for (int i = 0; i < wcslen(code); i++) {
            if (iswupper(code[i])) code[i] = towlower(code[i]);
        }

        // проверка на посторонние символы
        for (int i = 0; i < wcslen(code); i++) {
            if (iswalpha(code[i])) p = 1;
            else {
                wprintf(L"Символ %c не поддерживается (позиция %d) ", code[i], i + 1);
                p = 0;
                break;
            }
        }
    }

    // обработка дублирования в биграмме 
    for (int i = 0; i < wcslen(code); i++) {
        if (code[i] == code[i + 1])
        {
            for (int j = wcslen(code) - 1; j > i; j--)
            {
                code[j + 1] = code[j];
            }
            code[i + 1] = L'х';
        }

    }

    if (wcslen(code) % 2 != 0)
    {
        code[wcslen(code) + 1 ] = L'х';
    }



    for (int i = 0; i < wcslen(code); i = i + 2)
    {
        wprintf(L"%c %c\t", code[i], code[i + 1]);
    }


    wprintf(L"\n");
    int len = wcslen(code);
    int* index_arr = (int*)malloc((wcslen(code) * 2) * sizeof(int));
    wchar_t* decode_arr = (wchar_t*)malloc((wcslen(code) * 2) * sizeof(wchar_t));
    for (int i = 0; i < wcslen(code) * 2; i++)
    {
        index_arr[i] = -1;
    }

    array_index(index_arr, matrix, code);
    for (int h = 0; h < wcslen(code) * 2; h += 2)
    {
        wprintf(L"строка - %d столбец - %d\n", index_arr[h], index_arr[h + 1]);
    }
    Encode(index_arr, matrix, len * 2, file_output);
    fclose(file_output);
    FILE* file_output__ = fopen("output.txt", "r");
    fgetws(code, 256, file_output__);
    fclose(file_output__);
    for (int i = 0; i < wcslen(code) * 2; i++)
    {
        index_arr[i] = -1;
    }
    array_index(index_arr, matrix, code);
    Decode(index_arr, matrix, len*2, file_decode);
    fclose(file_decode);

    if (check() == true)
    {
        wprintf(L"\nКодирование - декодирование прошло успешно\n");
    }
    else
    {
        wprintf(L"\nПроизошла ошибка в кодирование - декодирование\n");
    }
    wchar_t* temp_arr = (wchar_t*)malloc(256 * sizeof(wchar_t));


    FILE* input__ = fopen("input.txt", "r");
    FILE* output__ = fopen("output.txt", "r");
    FILE* decode__ = fopen("decode.txt", "r");
    for (int i = 0; i < 256; i++)
    {
        temp_arr[i] = L'\0';
    }
    fgetws(temp_arr,256, input__);
    wprintf(L"\nВводимое слово - % ls\n", temp_arr);
    for (int i = 0; i < 256; i++)
    {
        temp_arr[i] = L'\0';
    }
    fgetws(temp_arr, 256, output__);
    wprintf(L"Зашифровонное слово - %ls\n", temp_arr);
    for (int i = 0; i < 256; i++)
    {
        temp_arr[i] = L'\0';
    }
    fgetws(temp_arr, 256, decode__);
    wprintf(L"Дешифровонное слово - %ls\n", temp_arr);
    printf("\nend\n");
    free(temp_arr);
    fclose(input__);
    fclose(output__);
    fclose(decode__);
    free(index_arr);
    free(decode_arr);
    fclose(file_output);

}