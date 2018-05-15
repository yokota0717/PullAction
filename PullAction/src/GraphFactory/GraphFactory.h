#pragma once
#include "DxLib.h"
#include <map>
#include <string>
#include <memory>

using namespace std;


class GraphFactory {
	string path;
	map<string, int> pool;

	int CreateGraph(const char*);

public:
	GraphFactory();
	int GetGraph(const char*);
};