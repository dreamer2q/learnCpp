
#include <bits/stdc++.h>

using namespace std;

#define ElemType int
#define MAXSIZE 10
#define MAXROW 10

typedef struct {
    int i, j;  //i 行位置, j 列位置
    ElemType e;
} Triple;

typedef struct {
    Triple data[MAXSIZE + 1];
    int rows, columns, size;  // 行数，列数，非0元素数
    int rpos[MAXROW + 1];     //第一个非0元素所在data的位置
} TSMatrix;

int TransposeSMatrix(TSMatrix M, TSMatrix &T) {
    T.columns = M.rows;
    T.rows = M.columns;
    T.size = M.size;
    if (T.size) {
        int t = 1;
        for (int i = 1; i <= M.columns; i++) {
            for (int j = 1; j <= M.size; j++) {
                if (M.data[j].j == i) {
                    T.data[t].i = M.data[j].j;
                    T.data[t].j = M.data[j].i;
                    T.data[t].e = M.data[j].e;
                    t++;
                }
            }
        }
    }
    return 0;
}

int FastTransposeSMatrix(TSMatrix M, TSMatrix &T) {
    T.columns = M.rows;
    T.rows = M.columns;
    T.size = M.size;
    if (T.size) {
        int cpos[MAXSIZE], num[MAXSIZE];
        for (int i = 1; i <= M.size; i++) num[i] = 0;
        for (int i = 1; i <= M.size; i++) ++num[M.data[i].j];
        cpos[1] = 1;
        for (int i = 2; i <= M.size; i++) {
            cpos[i] = cpos[i - 1] + num[i - 1];
        }
        for (int p = 1; p <= M.size; p++) {
            int col = M.data[p].j;
            int q = cpos[col];
            T.data[q].e = M.data[p].e;
            T.data[q].i = M.data[p].j;
            T.data[q].j = M.data[p].i;
            ++cpos[col];
        }
    }
    return 0;
}

int MultiSMatrix(TSMatrix M, TSMatrix N, TSMatrix &Q) {
    if (M.columns != N.rows) return -1;  //矩阵大小不一致
    Q.rows = M.rows;
    Q.columns = N.columns;
    Q.size = 0;
    if (M.size * N.size != 0) {
        for (int arow = 1; arow <= M.rows; arow++) {
            int ctmp[MAXROW] = {0};
            Q.rpos[arow] = Q.size + 1;
            int tp;
            if (arow < M.rows) {
                tp = M.rpos[arow + 1];
            } else {
                tp = M.size + 1;
            }
            int t;
            for (int p = M.rpos[arow]; p < tp; p++) {
                int brow = M.data[p].j;
                if (brow < N.rows) {
                    t = N.rpos[brow + 1];
                } else {
                    t = N.size + 1;
                }
                for (int q = N.rpos[brow]; q < t; ++q) {
                    int ccol = N.data[q].j;
                    ctmp[ccol] += M.data[p].e * N.data[q].e;
                }
            }
            for (int ccol = 1; ccol <= Q.columns; ccol++) {
                if (ctmp[ccol]) {
                    if (++Q.size > MAXSIZE) return -1;
                    Q.data[Q.size].e = ctmp[ccol];
                    Q.data[Q.size].i = arow;
                    Q.data[Q.size].j = ccol;
                }
            }
        }
    }
    return 0;
}

void test() {
    // 3*2
    // 1 2
    // 0 2
    // 1 2
    TSMatrix A{
        data : {
            {},
            {1, 1, 1},
            {1, 2, 2},  // 1 2
            {2, 2, 2},  // 0 2
            {3, 1, 1},
            {3, 2, 2},  //1 2
        },
        rows : 3,
        columns : 2,
        size : 5,
        rpos : {
            0,
            1,
            3,
            4,
        },
    };

    // 2*3
    // 3 2 1
    // 0 1 0
    TSMatrix B{
        data : {
            {},
            {1, 1, 3},
            {1, 2, 2},
            {1, 3, 1},  //3 2 1
            {2, 2, 1},  //0 1 0
        },
        rows : 2,
        columns : 3,
        size : 4,
        rpos : {0, 1, 4},
    };

    TSMatrix C;

    TransposeSMatrix(A, C);
    FastTransposeSMatrix(B, C);
    MultiSMatrix(A, B, C);
    return;
}

int main() {
    test();
    return 0;
}