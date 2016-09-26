#include <iostream>
#include <vector>
#include <algorithm>
#include <intrin.h>
using namespace std;
#pragma warning( disable : 4146 )
#include "types.h"
#include "util.h"
#include "search.h"
const char startBoard[2][8][9] = {
	{
	"........",
	"........",
	"........",
	".......Q",
	"..B.P...",
	"........",
	"PPPP.PPP",
	"RNB.K.NR"
	},
	{
	"R.BQKB.R",
	"PPPP.PPP",
	"..N..N..",
	"....P...",
	"........",
	"........",
	"........",
	"........"
	},
};
int main() {
	State state;
	for (int id = 0;id<2;++id) {
		for (int i = 0;i<8;++i) {
			for (int j = 0;j<8;++j) {
				switch (startBoard[id][i][j]) {
				case 'P':
					state.pieces[id][PAWN] |= gmsk(j, i);
					break;
				case 'R':
					state.pieces[id][ROOK] |= gmsk(j, i);
					break;
				case 'N':
					state.pieces[id][KNIGHT] |= gmsk(j, i);
					break;
				case 'B':
					state.pieces[id][BISHOP] |= gmsk(j, i);
					break;
				case 'Q':
					state.pieces[id][QUEEN] |= gmsk(j, i);
					break;
				case 'K':
					state.pieces[id][KING] |= gmsk(j, i);
					break;
				}
			}
		}
	}
	for (int id = 0;id<2;++id)
		for (int j = 0;j<6;++j)
			state.vis[id] |= state.pieces[id][j];
	alfabeta(state, 0, -INF, +INF, true);
	cout << "hojas: " << hojas << endl;
	printBoard(bestChild);
	getchar();
}