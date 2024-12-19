#pragma once
#include <string>
#include <vector>
#include "Vertex.h"

using namespace std;

class Mesh
{
private:
    vector<Vertex> vertices;
    vector<vector<unsigned int>> indicesLayers;

    unsigned int VBO;
    unsigned int VAO;
    vector<unsigned int> EBOs;

    void SetupMesh();
    
public:
    // constructor reads and builds the shader
    Mesh(vector<Vertex> vertices, vector<vector<unsigned int>> indicesLayers);

    void Draw(int layerIndex);

    ~Mesh();
};

