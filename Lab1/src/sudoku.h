#ifndef SUDOKU_H
#define SUDOKU_H

const int MaxNumOfNode =3241;
const int MaxColumns = 400;
const int kRow = 100, kCol = 200, kBox = 300, N = 81;
void trans(const char in[N], int* target);
bool dancing(int*);
bool solved();

#endif
