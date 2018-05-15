#include "GraphFactory.h"

GraphFactory::GraphFactory()
	:
	path("./data/image/")
{}

int GraphFactory::CreateGraph(const char* fileName) {
	int handle = LoadGraph(fileName);
	return handle;
}

int GraphFactory::GetGraph(const char* fileName) {
	string file = path + fileName;
	auto it = pool.find(file);
	if (it != pool.end())
		return it->second;
	int newGraph = CreateGraph(file.c_str());
	pool.insert(make_pair(file, newGraph));
	return newGraph;
}