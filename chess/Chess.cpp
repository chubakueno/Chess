#include <iostream>
#include <vector>
#include <algorithm>
#include <intrin.h>
#include <sstream>
using namespace std;
#pragma warning( disable : 4146 )
#include "types.h"
#include "util.h"
#include "search.h"
#include "string"
const char startBoard[2][8][9] = {
	{
	"........",
	"........",
	"........",
	"........",
	"........",
	"........",
	"PPPPPPPP",
	"RNBQKBNR"
	},
	{
	"RNBQKBNR",
	"PPPPPPPP",
	"........",
	"........",
	"........",
	"........",
	"........",
	"........"
	},
};
vector<string> tokens;
void _tokenizeLine(){
	string str;
	getline(cin, str);
	stringstream ss(str);
	tokens.clear();
	while (ss >> str){
		tokens.push_back(str);
	}
}
void tokenizeLine(){
	while (true){
		_tokenizeLine();
		if (tokens.size() == 0 || tokens[0] == "setoption") continue;
		else break;
	}
}
string fenMove;
int main() {
	while (tokens.size() == 0 || tokens[0] != "uci"){
		tokenizeLine();
	}
	cout << "id name ChessUPC" << endl;
	cout << "id author Luis Rivera, Raul Bigoria, Gonzalo Nuñez Villar" << endl;
	cout << "uciok" << endl;
	tokenizeLine();
	if (!(tokens[0] == "isready")) return 0;
	//NO INFO
	cout << "readyok" << endl;
	tokenizeLine();
	if (!(tokens[0] == "ucinewgame")) return 0;
	tokenizeLine();
	if (!(tokens[0] == "isready")) return 0;
	cout << "readyok" << endl;
	tokenizeLine();
	if (!(tokens[0] == "position")) return 0;
	if (!(tokens[1] == "startpos")) return 0;
	if (!(tokens[2] == "moves")) return 0;
	fenMove = tokens[3];
	
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
	string playerMove=tokens[tokens.size()-1];
	bestChild = state;
	
	
		
		//system("cls");
		//printBoard(bestChild);
		
		//cout << endl << "Jugada: ";
		//cin >> playerMove;
		playerMove[0] = (int)(playerMove[0] - 'a'); playerMove[2] = (int)(playerMove[2] - 'a');
		playerMove[1] = (int)(playerMove[1] - 49); playerMove[3] = (int)(playerMove[3] - 49);
		movePlayer(state, playerMove[0], playerMove[1], playerMove[2], playerMove[3]);
		bestChild = state;
		tokenizeLine();
		if (!(tokens[0] == "go")) return 0;
		Bitboard aux = state.vis[0] | bestChild.vis[0];
		Bitboard old = bestChild.vis[0] ^ aux;
		aux = state.vis[0] ^ aux;
		unsigned long idx, idxold;
		_BitScanForward64(&idxold, old);
		_BitScanForward64(&idx, aux);
		int xold = idxold & 7, yold = idxold >> 3;
		int x = idx & 7, y = idx >> 3;
		alfabeta(bestChild, 0, -INF, +INF, true);
		cout << "bestmove " << char(xold + 'a') << yold + 1 << char(x + 'a') << y + 1 << endl;
		tokenizeLine();
	
		
		//cout << "hojas: " << hojas << endl;
		//printBoard(bestChild);
		state = bestChild;
	
		


	
	
	
	

	getchar();
}