#pragma once
const enum class MutationType {
	SWAP = 0,
	INVERSION = 1,
};
const enum class CrossoverType {
	ORDERED = 0,
	CYCLE = 1
};

const enum class SelectionType {
	TOURNAMENT = 0,
	ROULETTE = 1
};