#define _CRT_SECURE_NO_WARNINGS
#include "Header.h"

bool check()
{
    wchar_t decode_arr[256] = { L'\0' };
    wchar_t input_arr[256] = { L'\0' };
    FILE* decode = fopen("decode.txt", "r");
    FILE* input = fopen("input.txt", "r");
    fgetws(decode_arr, 256, decode);
    fgetws(input_arr, 256, input);
    wchar_t temp = L'х';
    for (int i = 0; i < wcslen(decode_arr); i++)
    {
        if (decode_arr[i] == L'х')
        {
            for (int j = i; j < wcslen(decode_arr); j++)
            {
                decode_arr[j] = decode_arr[j + 1];
            }
        }
    }
    for (int i = 0; i < wcslen(input_arr); i++)
    {
        if (input_arr[i] != decode_arr[i])
        {
            fclose(decode);
            fclose(input);
            return false;
        }
    }
    fclose(decode);
    fclose(input);
    return true;

}

void array_index(int* index_arr, wchar_t matrix[6][6], wchar_t code[256])
{
    for (int i = 0; i < wcslen(code) * 2; i++)
    {
        index_arr[i] = -1;
    }
    for (int i = 0; i < wcslen(code); i++) {
        for (int j = 0; j < 6; j++) {
            for (int k = 0; k < 6; k++) {
                if (code[i] == matrix[j][k]) {
                    for (int h = 0; h < wcslen(code) * 2; h += 2)
                    {
                        if (index_arr[h] == -1)
                        {
                            index_arr[h] = j;
                            index_arr[h + 1] = k;
                            break;
                        }
                    }

                }
            }
        }
    }
}

void Encode(int* index, wchar_t matrix[6][6], int len, FILE* output)
{
    int a = 0, b = 0;

    for (int i = 0; i <= len - 3; i += 4)
    {
        a = index[i + 3] + 1;
        // ���� �� ����� ������

        if (index[i] == index[i + 2] && a < 5)
        {

            fwprintf(output, L"%c%c", matrix[index[i]][index[i + 1] + 1], matrix[index[i + 2]][a]);
        }
        // ���� �� ����� ������ � � ����
        if (index[i] == index[i + 2] && a >= 5)
        {
            a = 0;

            fwprintf(output, L"%c%c", matrix[index[i]][index[i + 1] + 1], matrix[index[i + 2]][a]);
        }
        b = index[i + 2] + 1;
        // ���� � ����� �������
        if (index[i + 1] == index[i + 3] && b < 5)
        {

            fwprintf(output, L"%c%c", matrix[index[i] + 1][index[i + 1]], matrix[b][index[i + 3]]);
        }
        // ���� � ����� ������� � � ����
        if (index[i + 1] == index[i + 3] && b >= 5)
        {
            b = 0;

            fwprintf(output, L"%c%c", matrix[index[i] + 1][index[i + 1]], matrix[b][index[i + 3]]);
        }

        if (index[i] != index[i + 2] && index[i + 1] != index[i + 3])
        {
            fwprintf(output, L"%c%c", matrix[index[i + 2]][index[i + 1]], matrix[index[i]][index[i + 3]]);
        }

    }

}

void Decode(int* index, wchar_t matrix[6][6], int len, FILE* output)
{
    int a = 0, b = 0;
    for (int i = 0; i <= len - 3; i += 4)
    {
        // ���� �� ����� ������
        a = index[i + 3] - 1;
        if (index[i] == index[i + 2] && a >= 0)
        {
            fwprintf(output, L"%c%c", matrix[index[i]][index[i + 1] - 1], matrix[index[i + 2]][a]);
        }
        // ���� �� ����� ������ � � ����
        if (index[i] == index[i + 2] && a < 0)
        {
            a = 4;
            fwprintf(output, L"% c % c", matrix[index[i]][index[i + 1] - 1], matrix[index[i + 2]][a]);
        }
        // ���� � ����� �������
        b = index[i + 2] - 1;
        if (index[i + 1] == index[i + 3] && b >= 0)
        {
            fwprintf(output, L"%c%c", matrix[index[i] - 1][index[i + 1]], matrix[b][index[i + 3]]);
        }
        // ���� � ����� ������� � � ����
        if (index[i + 1] == index[i + 3] && b < 0)
        {
            b = 4;
            fwprintf(output, L"%c%c", matrix[index[i] - 1][index[i + 1]], matrix[b][index[i + 3]]);
        }

        if (index[i] != index[i + 2] && index[i + 1] != index[i + 3])
        {
            fwprintf(output, L"%c%c", matrix[index[i + 2]][index[i + 1]], matrix[index[i]][index[i + 3]]);
        }
    }

}