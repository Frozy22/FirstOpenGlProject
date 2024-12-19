#include "Mesh.h"
#include <GL/glew.h>
#include "Exceptions.h"

void Mesh::SetupMesh()
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

    // vertex positions
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    // vertex normals
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
    // vertex texture coords
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));

    glBindVertexArray(0);

    EBOs.resize(indicesLayers.size());

    for (auto i = 0; i < indicesLayers.size(); i++) 
    {
        auto& indices = indicesLayers[i];
        auto* EBO = &EBOs[i];

        glGenBuffers(1, EBO);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
    }

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

Mesh::Mesh(vector<Vertex> vertices, vector<vector<unsigned int>> indicesLayers)
{
    this->vertices = vertices;
    this->indicesLayers = indicesLayers;

    SetupMesh();
}

void Mesh::Draw(int layerIndex)
{
    CHECK_INDEX_RANGE(0, indicesLayers.size(), layerIndex);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOs[layerIndex]);
    glDrawElements(GL_TRIANGLES, indicesLayers[layerIndex].size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

Mesh::~Mesh()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(EBOs.size(), &EBOs[0]);
}
