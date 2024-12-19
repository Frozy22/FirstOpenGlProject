#pragma once
#include "IService.h"
#include <vector>
#include <string>
#include "Vertex.h"

using namespace std;

class ObjParser : public IService
{
public:
	bool TryParse(const string& assetPath, vector<Vertex>& vertices, vector<vector<unsigned int>>& indicesLayers);
	void Terminate();
};

