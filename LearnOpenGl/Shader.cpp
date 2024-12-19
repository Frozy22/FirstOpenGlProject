#include "Shader.h"
#include <GL/glew.h>
#include "ServiceLocator.h"
#include "Assets.h"

int Shader::GetUniformLocation(const string& name) const
{
    auto result = locations.find(name);

    if (result != locations.end())
        return (*result).second;
    
    int location = glGetUniformLocation(id, name.c_str());
    locations[name] = location;

    return location;
}

void Shader::DbgCheckUniformLocation(int location) const
{
    for (auto const& [key, val] : locations)
    {
        if (val == location)
            return;
    }

    throw "EXCEPTION::SHADER::INVALID_UNIFORM_LOCATION";
}

Shader::Shader(const string& vertexAssetPath, const string& fragmentAssetPath)
{
    printf("INFO::SHADER::INITIALIZE");
    printf("INFO::SHADER::VERTEX::LOAD_FROM: %s", vertexAssetPath.c_str());
    printf("INFO::SHADER::FRAGMENT::LOAD_FROM: %s", fragmentAssetPath.c_str());

    Assets* assets = ServiceLocator::GetInstance()->Resolve<Assets>();

    // 1. retrieve the vertex/fragment source code from filePath
    string vertexCode = assets->GetAssetStr(vertexAssetPath);
    string fragmentCode = assets->GetAssetStr(fragmentAssetPath);

    if (vertexCode == "" || fragmentCode == "")
    {
        printf("ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ");
        return;
    }

    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();

    // 2. compile shaders
    unsigned int vertex, fragment;
    int success;
    char infoLog[512];

    // vertex Shader
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);

    // print compile errors if any
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);

    if (success == false)
    {
        glGetShaderInfoLog(vertex, 512, NULL, infoLog);
        printf("ERROR::SHADER::VERTEX::COMPILATION_FAILED\n%s", infoLog);
    };

    // similiar for Fragment Shader
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);

    // print compile errors if any
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);

    if (success == false)
    {
        glGetShaderInfoLog(fragment, 512, NULL, infoLog);
        printf("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n%s", infoLog);
    };

    // shader Program
    id = glCreateProgram();
    glAttachShader(id, vertex);
    glAttachShader(id, fragment);
    glLinkProgram(id);

    // print linking errors if any
    glGetProgramiv(id, GL_LINK_STATUS, &success);

    if (success == false)
    {
        glGetProgramInfoLog(id, 512, NULL, infoLog);
        printf("ERROR::SHADER::PROGRAM::LINKING_FAILED\n %s", infoLog);
    }

    // delete the shaders as they're linked into our program now and no longer necessary
    glDeleteShader(vertex);
    glDeleteShader(fragment);

    printf("INFO::SHADER::INITIALIZED");
}

Shader::~Shader()
{
    glDeleteProgram(id);
}

void Shader::Use()
{
    glUseProgram(id);
}

/// UTILITY UNIFORM VALUES BY NAME
void Shader::SetBool(const string& name, bool value) const
{
    int location = GetUniformLocation(name);
    glUniform1i(location, (int)value);
}

void Shader::SetInt(const string& name, int value) const
{
    int location = GetUniformLocation(name);
    glUniform1i(location, value);
}

void Shader::SetFloat(const string& name, float value) const
{
    int location = GetUniformLocation(name);
    glUniform1f(location, value);
}

/// UTILITY UNIFORM VALUES BY LOCATION
void Shader::SetBool(int location, bool value) const
{
    DbgCheckUniformLocation(location);
    glUniform1i(location, (int)value);
}

void Shader::SetInt(int location, int value) const
{
    DbgCheckUniformLocation(location);
    glUniform1i(location, value);
}

void Shader::SetFloat(int location, float value) const
{
    DbgCheckUniformLocation(location);
    glUniform1f(location, value);
}