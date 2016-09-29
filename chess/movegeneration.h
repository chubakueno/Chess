#pragma once
#include "types.h"
#include "util.h"
#include <vector>
using namespace std;
const int jumpDisp[2][8][2] = {
	{
		{ -2,-1 },
		{ -1,-2 },
		{ -2,+1 },
		{ -1,+2 },
		{ +2,-1 },
		{ +1,-2 },
		{ +2,+1 },
		{ +1,+2 },
	},
	{
		{ -1,-1 },
		{ -1,+0 },
		{ -1,+1 },
		{ +0,-1 },
		{ +0,+1 },
		{ +1,-1 },
		{ +1,+0 },
		{ +1,+1 },
	}
};
const int slideDisp[8][2] = {
	{ -1,+0 },
	{ +1,+0 },
	{ +0,-1 },
	{ +0,+1 },
	{ -1,-1 },
	{ -1,+1 },
	{ +1,-1 },
	{ +1,+1 },
};
const int slidesIdx[3][2] = {
	{ 0,4 },//ROOK
	{ 0,8 },//QUEEN
	{ 4,8 },//BISHOP
};
int movePiece(State& state, int id, int p, int x, int y, int nx, int ny) {
	if (nx<0 || nx>7 || ny<0 || ny>7) return INVALID;
	Bitboard act = gmsk(nx, ny), old = gmsk(x, y);
	if (state.vis[id] & act) return INVALID;
	int rval = EMPTY;
	if (state.vis[!id] & act) {
		state.vis[!id] &= ~act;
		for (int i = 0;i<6;++i)
			state.pieces[!id][i] &= ~act;
		rval = CAPTURE;
	}
	state.pieces[id][p] ^= old | act;
	state.vis[id] ^= old | act;
	return rval;
}

void movePlayer(State& state,int x,int y,int nx,int ny)
{
	int p;
	for (int i = 0; i < 6; i++)
	{
		if (state.pieces[1][i] & gmsk(x, y))
		{

			p = i;
			break;
		}
	}
	movePiece(state,1, p, x, y, nx, ny);
}
vector<State> generate(State state, int id) {
	vector<State> states;
	Bitboard pieces, piece;
	//ROOK,QUEEN,BISHOP move generation
	for (int p = 1;p <= 3;++p) {
		pieces = state.pieces[id][p];
		while (piece = pieces&(-pieces)) {
			unsigned long ind;
			_BitScanForward64(&ind, pieces);
			int x = ind & 7, y = ind >> 3;
			for (int j = slidesIdx[p - 1][0];j<slidesIdx[p - 1][1];++j) {
				for (int i = 1;i<8;++i) {
					State tmp = state;
					int retval = movePiece(tmp, id, p, x, y, x + i*slideDisp[j][0], y + i*slideDisp[j][1]);
					if (retval) states.push_back(tmp);
					if (retval != EMPTY) break;
				}
			}
			pieces ^= piece;
		}
	}
	//PAWN move generation
	pieces = state.pieces[id][PAWN];
	while (piece = pieces&(-pieces)) {
		unsigned long ind;
		_BitScanForward64(&ind, pieces);
		int x = ind & 7, y = ind >> 3;
		State tmp = state;
		int disp = id == 0 ? -1 : 1;
		int ny = y + disp;
		if (ny >= 0 && ny<8) {
			if (x>0 && movePiece(tmp, id, PAWN, x, y, x - 1, ny) == CAPTURE)
				states.push_back(tmp);
			tmp = state;
			if (x<7 && movePiece(tmp, id, PAWN, x, y, x + 1, ny) == CAPTURE)
				states.push_back(tmp);
			tmp = state;
			if (movePiece(tmp, id, PAWN, x, y, x, ny) == EMPTY) {
				states.push_back(tmp);
				tmp = state;
				if (((id == 0 && y == 6) || (id == 1 && y == 1)) &&
					movePiece(tmp, id, PAWN, x, y, x, y + 2 * disp) == EMPTY)
					states.push_back(tmp);
			}
		}
		pieces ^= piece;
		
	}
	//KNIGHT,KING move generation
	for (int p = 4;p <= 5;++p) {
		pieces = state.pieces[id][p];
		while (piece = pieces&(-pieces)) {
			unsigned long ind;
			_BitScanForward64(&ind, pieces);
			int x = ind & 7, y = ind >> 3;
			for (int j = 0;j<8;++j) {
				State tmp = state;
				if (movePiece(tmp, id, p, x, y, x + jumpDisp[p - 4][j][0], y + jumpDisp[p - 4][j][1]))
					states.push_back(tmp);
			}
			pieces ^= piece;
		}
	}
	return states;
}