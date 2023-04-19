//
// Created by BEAST on 17.04.2023.
//

#include "heuristics.h"

using namespace std;


int abs(int x) {
    return x > 0 ? x : -x;
}


int ManhattanDistance::distance(std::array<std::array<char, 4>, 4> state) {
    int distance = 0;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (state[i][j] == 0) continue;
            int x = (state[i][j] - 1) / 4;
            int y = (state[i][j] - 1) % 4;
            distance += abs(x - i) + abs(y - j);
        }
    }
    return distance;
}

int LinearConflict::distance(std::array<std::array<char, 4>, 4> state) {
    return 0;
}

int WalkingDistance::distance(std::array<std::array<char, 4>, 4> state) {
    int  space, num1, num2, idx1, idx2, inv1, inv2, wd1, wd2;
    int  id1, id2, lowb1, lowb2, i, j, work[BOARD_WIDTH];
    int  cnvp[] = { 0, 4, 8,12, 1, 5, 9,13, 2, 6,10,14, 3, 7,11,15};
    unsigned long long  table;
    int  CONV[16] = {       /* 縦横変換テーブル */
            0,
            1, 5, 9,13,
            2, 6,10,14,
            3, 7,11,15,
            4, 8,12
    };
    int BOARD[16];
    for(i = 0; i < 4; i++){
        for(j = 0; j < 4; j++){
            BOARD[i * 4 + j] = state[i][j];
        }
    }

    /* 解の存在チェック */
    for (space=0; BOARD[space]; space++);
    inv1 = (BOARD_WIDTH - 1) - space / BOARD_WIDTH;
    for (i=0; i<BOARD_SIZE; i++) {
        if (BOARD[i] == 0) continue;
        for (j=i+1; j<BOARD_SIZE; j++)
            if (BOARD[j] && BOARD[j]<BOARD[i]) inv1++;
    }

    /* 初期 IDX1 for WD */
    table = 0;
    for (i=0; i<BOARD_WIDTH; i++) {
        for (j=0; j<BOARD_WIDTH; j++) work[j] = 0;
        for (j=0; j<BOARD_WIDTH; j++) {
            num1 = BOARD[i * BOARD_WIDTH + j];
            if (num1 == 0) continue;
            work[(num1 - 1) >> 2]++;
        }
        for (j=0; j<BOARD_WIDTH; j++)
            table = (table << 3) | work[j];
    }
    for (idx1=0; WDPTN[idx1]!=table; idx1++);

    /* 初期 IDX2 for WD */
    table = 0;
    for (i=0; i<BOARD_WIDTH; i++) {
        for (j=0; j<BOARD_WIDTH; j++) work[j] = 0;
        for (j=0; j<BOARD_WIDTH; j++) {
            num2 = CONV[BOARD[j * BOARD_WIDTH + i]];
            if (num2 == 0) continue;
            work[(num2 - 1) >> 2]++;
        }
        for (j=0; j<BOARD_WIDTH; j++)
            table = (table << 3) | work[j];
    }
    for (idx2=0; WDPTN[idx2]!=table; idx2++);

    /* 初期 INV1 for ID */
    inv1 = 0;
    for (i=0; i<BOARD_SIZE; i++) {
        num1 = BOARD[i];
        if (!num1) continue;
        for (j=i+1; j<BOARD_SIZE; j++) {
            num2 = BOARD[j];
            if (num2 && num2<num1) inv1++;
        }
    }

    /* 初期 INV2 for ID */
    inv2 = 0;
    for (i=0; i<BOARD_SIZE; i++) {
        num1 = CONV[BOARD[cnvp[i]]];
        if (!num1) continue;
        for (j=i+1; j<BOARD_SIZE; j++) {
            num2 = CONV[BOARD[cnvp[j]]];
            if (num2 && num2<num1) inv2++;
        }
    }

    /* 初期 LowerBound */
    wd1 = WDTBL[idx1];
    wd2 = WDTBL[idx2];
    id1 = IDTBL[inv1];
    id2 = IDTBL[inv2];
    lowb1 = (wd1 > id1)? wd1: id1;
    lowb2 = (wd2 > id2)? wd2: id2;

    return lowb1 + lowb2;
}

WalkingDistance::WalkingDistance() {
    int   i, j, k, nextd;
    unsigned long long int   table;
    char  *filename = "puz15wd.db";
    FILE  *fp;

    /* IDTBL[] */
    for (i=0; i<106; i++)
        IDTBL[i] = (char)((i / 3) + (i % 3));

    /* WDPTN[], WDTBL[], WDLNK[][][] */
    fp = fopen(filename, "rb");
    for (i=0; i<WDTBL_SIZE; i++) {
        /* WDPTN */
        table = 0;
        for (j=0; j<8; j++)
            table = (table << 8) | getc(fp);
        WDPTN[i] = table;
        /* WDTBL */
        WDTBL[i] = (char)getc(fp);
        /* WDLNK */
        for (j=0; j<2; j++)
            for (k=0; k<4; k++) {
                nextd = getc(fp);
                WDLNK[i][j][k] = (short)((nextd << 8) | getc(fp));
            }
    }
    fclose(fp);
}
