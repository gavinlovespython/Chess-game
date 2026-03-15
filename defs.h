#ifndef DEFS_H
#define DEFS_H

#include <stdlib.h>

#define DEBUG

#ifndef DEBUG
#define ASSERT(n)
#else
#define ASSERT(n) \
if (!(n)) { \
printf("%s - Failed", #n); \
printf("On %s ", __DATE__); \
printf("At %s ", __TIME__); \
printf("In File %s ", __FILE__); \
printf("At Line %d\n", __LINE__); \
exit (1);}
#endif

typedef unsigned long long U64; // 64 bit number because it's 8x8 board

#define NAME "Vice 1.0"
#define BRD_SQ_NUM (120)

#define MAX_GAME_MOVES (2048)

// piece declaration
enum { EMPTY, wP, wN, wB, wR, wQ, wK, bP, bN, bB, bR, bQ, bK };

// board coordinate declaration
enum { FILE_A, FILE_B, FILE_C, FILE_D, FILE_E, FILE_F, FILE_G, FILE_H, FILE_NONE };
enum { RANK_1, RANK_2, RANK_3, RANK_4, RANK_5, RANK_6, RANK_7, RANK_8, RANK_NONE };

// colors used
enum { WHITE, BLACK, BOTH};

// board coordinate itself
enum {
  A1 = 21, B1, C1, D1, E1, F1, G1, H1,
  A2 = 31, B2, C2, D2, E2, F2, G2, h2,
  A3 = 41, B3, C3, D3, E3, F3, G3, h3,
  A4 = 51, B4, C4, D4, E4, F4, G4, h4,
  A5 = 61, B5, C5, D5, E5, F5, G5, h5,
  A6 = 71, B6, C6, D6, E6, F6, G6, h6,
  A7 = 81, B7, C7, D7, E7, F7, G7, h7,
  A8 = 91, B8, C8, D8, E8, F8, G8, h8, NO_SQ
};

enum { FALSE, TRUE };

// castling (1 2 4 8 changes each bits)
enum { WKCA = 1, WQKA = 2, BKCA = 4, BQCA = 8 };

// structure keeping track of match history in case of undo
// BEFORE the move was made
typedef struct {

  int move; // played move
  int castlePerm;
  int enPas;
  int fiftyMove;
  U64 posKey;

} S_UNDO;

// structure keeping track of board status
typedef struct {

  int pieces[BRD_SQ_NUM];
  // call in 64 bit, set 1 on the coordinate where pawn is.
  U64 pawns[3]; // 3 bit because Black, White, or Both

  // keep in track of where the king is
  int KingSq[2]; // 2 bit because it's either Black or White

  int side; // current side to move
  int enPas; // en passante
  int fiftyMove; // game drawn when 50 moves

  int ply; // number of half moves
  int hisPly; // total half moves (history)

  int castlePerm; // permission for castling

  U64 posKey; // Unique position key

  int pceNum[13]; // number of pieces including EMPTY
  int bigPce[3]; // pieces that aren't pawns
  int majPce[3]; // Rooks and Queens
  int minPce[3]; // Bishop and Knights

  S_UNDO history[MAX_GAME_MOVES];

  // piece list
  int pList[13][10]; // first index is piece type, second is number of that piece

} S_BOARD;

/* MACROS */
#define FR2SQ(f,r) ((21 + (f)) + ((r) * 10)) // rank number to 120 array number

/* GLOBALS */
extern int Sq120ToSq64[BRD_SQ_NUM];
extern int Sq64ToSq120[64];

/* FUNCTIONS */
extern void AllInit();

// init.c

#endif
