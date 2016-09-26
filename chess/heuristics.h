#pragma once
#include "types.h"
#include <intrin.h>
const double ReinfeldValues[6] = { 1,5,9,3,3,1000 };
double getmaterial(State &state, int id) {
	double material = 0;
	for (int i = 0;i<6;++i)
		material += ReinfeldValues[i] * __popcnt64(state.pieces[id][i]);
	return material;
}
double heuristic(State &state, int id) {
	double material = getmaterial(state, id) - getmaterial(state, !id);
	return material;
}