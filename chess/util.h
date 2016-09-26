#pragma once
#include "types.h"
inline Bitboard gmsk(int x, int y) {
	return 1ULL << ((y << 3) + x);
}
void printBoard(State state) {
	Bitboard full[6];
	for (int i = 0;i<6;++i)
		full[i] = state.pieces[0][i] | state.pieces[1][i];
	for (int p = 1;p<2;++p) {
		for (int i = 0;i<8;++i) {
			for (int j = 0;j<8;++j) {
				if ((full[PAWN] >> (8 * i + j)) & 1) cout << "P";
				else if ((full[KNIGHT] >> (8 * i + j)) & 1) cout << "N";
				else if ((full[ROOK] >> (8 * i + j)) & 1) cout << "R";
				else if ((full[BISHOP] >> (8 * i + j)) & 1) cout << "B";
				else if ((full[KING] >> (8 * i + j)) & 1) cout << "K";
				else if ((full[QUEEN] >> (8 * i + j)) & 1) cout << "Q";
				else cout << ".";
			}
			cout << endl;
		}
	}
	cout << endl;
}