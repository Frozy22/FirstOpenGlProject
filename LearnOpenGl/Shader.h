#pragma once

#include <string>
#include <map>

using namespace std;

class Shader
{
private:
    // the program ID
    unsigned int id;

    mutable map<string, int> locations;

    void DbgCheckUniformLocation(int location) const;

public:
    // constructor reads and builds the shader
    Shader(const string& vertexAssetPath, const string& fragmentAssetPath);
    ~Shader();

    // use/activate the shader
    void Use();

    int GetUniformLocation(const string& name) const;

    // utility uniform functions by name
    void SetBool(const string& name, bool value) const;
    void SetInt(const string& name, int value) const;
    void SetFloat(const string& name, float value) const;

    // utility uniform functions by location
    void SetBool(int location, bool value) const;
    void SetInt(int location, int value) const;
    void SetFloat(int location, float value) const;
};

