.PHONY: all test clean


scorer:
	g++ -std=c++17 -O2 scorer scorer.cpp