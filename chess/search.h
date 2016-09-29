#pragma once
#include "types.h"
#include "heuristics.h"
#include "movegeneration.h"
#include <vector>
#include <algorithm>
using namespace std;
State bestChild;
int maxdepth = 6,hojas=0;
double alfabeta(State &state,
	int depth,
	double a,
	double b,
	bool maximizingPlayer) {
	if (depth == maxdepth) {
		++hojas;
		return heuristic(state, maximizingPlayer);
	}
	vector<State> children = generate(state, !maximizingPlayer);
	double v;
	if (maximizingPlayer) {
		v = -INF;
		for (int i = 0;i<children.size();++i) {
			double tv = alfabeta(children[i], depth + 1, a, b, false);
			if (v<tv) {
				v = tv;
				if (depth == 0) bestChild = children[i];
			}
			a = max(a, v);
			if (b <= a) break;
		}
	}
	else {
		v = INF;
		for (int i = 0;i<children.size();++i) {
			double tv = alfabeta(children[i], depth + 1, a, b, true);
			if (v>tv) {
				v = tv;
				if (depth == 0) bestChild = children[i];
			}
			b = min(b, v);
			if (b <= a) break;
		}
	}
	return v;
}