#pragma once
#include "types.h"
#include <intrin.h>
#include "movegeneration.h"
const double ReinfeldValues[6] = { 1,5,9,3,3,1000 };
double getmaterial(State &state, int id) {
	double material = 0;
	for (int i = 0;i<6;++i)
		material += ReinfeldValues[i] * __popcnt64(state.pieces[id][i]);
	return material;
}

int detectpiece(State &state,int id,int nx,int ny)
{
	for (int i = 0; i < 6; i++)
	{
		if (state.pieces[!id][i] & gmsk(nx, ny))
		{
			return ReinfeldValues[i];
		}
	}
	
}
double calcMoves(State &state, int id)
{
	double capt = 0;
	double moves = 0;
	Bitboard pieces, piece;
	//ROOK,QUEEN,BISHOP move generation
	for (int p = 1; p <= 3; ++p) {
		pieces = state.pieces[id][p];
		while (piece = pieces&(-pieces)) {
			unsigned long ind;
			_BitScanForward64(&ind, pieces);
			int x = ind & 7, y = ind >> 3;
			for (int j = slidesIdx[p - 1][0]; j<slidesIdx[p - 1][1]; ++j) {
				for (int i = 1; i<8; ++i) {
					State tmp = state;
					int nx = x + i*slideDisp[j][0];
					int ny = y + i*slideDisp[j][1];
					int retval = movePiece(tmp, id, p, x, y, nx, ny);
					if (retval)moves++;
					if (retval == CAPTURE)
						capt += detectpiece(state, id, nx, ny);
					
					if (retval != EMPTY) break;
				}
			}
			pieces ^= piece;
		}
	}

	//KNIGHT,KING move generation

	pieces = state.pieces[id][4];
	while (piece = pieces&(-pieces)) {
		unsigned long ind;
		_BitScanForward64(&ind, pieces);
		int x = ind & 7, y = ind >> 3;
		for (int j = 0; j<8; ++j) {
			State tmp = state;
			int nx = x + jumpDisp[0][j][0]; int ny = y + jumpDisp[0][j][1];
			int retval = movePiece(tmp, id, 4, x, y, nx,ny );
			if (retval)moves++;
			if (retval == CAPTURE)
				capt += detectpiece(state, id, nx, ny);
			
		}
		pieces ^= piece;
	}
	return moves+capt/2;
}
double heuristic(State &state, int id) {
	double material = getmaterial(state, id) - getmaterial(state, !id);
	double moves = calcMoves(state, id);
	return material+moves;
}