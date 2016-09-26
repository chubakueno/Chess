#pragma once
const double INF = 1e18;
typedef unsigned __int64 Bitboard;
enum {
	PAWN,
	ROOK,
	QUEEN,
	BISHOP,
	KNIGHT,
	KING,
};
enum {
	INVALID,
	EMPTY,
	CAPTURE,
};
struct State {
	Bitboard pieces[2][6];
	Bitboard vis[2];
	State() {
		memset(pieces, 0, sizeof pieces);
		memset(vis, 0, sizeof vis);
	}
};