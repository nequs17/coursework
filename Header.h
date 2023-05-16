#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>
#include <wchar.h>
#include <TCHAR.H>
#include <stdbool.h>

bool check();
void array_index(int* index_arr, wchar_t matrix[6][6], wchar_t code[256]);
void Encode(int* index, wchar_t matrix[6][6], int len, FILE* output);
void Decode(int* index, wchar_t matrix[6][6], int len, FILE* output);