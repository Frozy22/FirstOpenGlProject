#include "ObjParser.h"
#include <unordered_map>
#include "ServiceLocator.h"
#include "Assets.h"
#include <regex>
#include "Vector3Int.h"

bool ObjParser::TryParse(const string& assetPath, vector<Vertex>& vertices, vector<vector<unsigned int>>& indicesLayers)
{
    auto* assets = ServiceLocator::GetInstance()->Resolve<Assets>();
    auto str = assets->GetAssetStr(assetPath);

    if (str == "")
        return false;

    vector<Vector3> poses;
    vector<Vector3> normals;
    vector<Vector2> uvs;

    unordered_map<Vector3Int, int> vertMap;

    vertices.clear();
    indicesLayers.clear();
    int currentLayer = -1;

    regex lineRegex("\\\n");
    regex wordRegex("\\ ");
    regex splitRegex("\\/");

    vector <string> lines(sregex_token_iterator(str.begin(), str.end(), lineRegex, -1), sregex_token_iterator());

    for (auto& line : lines) 
    {
        vector<string> words(sregex_token_iterator(line.begin(), line.end(), wordRegex, -1), sregex_token_iterator());

        if (words[0] == "v") 
        {
            poses.push_back(Vector3(stof(words[1]), stof(words[2]), stof(words[3])));
        }
        else if (words[0] == "vn")
        {
            normals.push_back(Vector3(stof(words[1]), stof(words[2]), stof(words[3])));
        }
        else if (words[0] == "vt")
        {
            uvs.push_back(Vector2(stof(words[1]), stof(words[2])));
        }
        else if (words[0] == "usemtl") 
        {
            ++currentLayer;
            indicesLayers.push_back(vector<unsigned int>{});
        }
        else if (words[0] == "f") 
        {
            for (int i = 1; i <= 3; i++) 
            {
                vector<string> split(sregex_token_iterator(words[i].begin(), words[i].end(), splitRegex, -1), sregex_token_iterator());

                Vector3Int point{stoi(split[0]) - 1, stoi(split[1]) - 1, stoi(split[2]) - 1 };

                auto result = vertMap.find(point);

                if (result != vertMap.end())
                {
                    indicesLayers[currentLayer].push_back((*result).second);
                    continue;
                }
                
                vertMap[point] = static_cast<int>(vertices.size());
                vertices.push_back(Vertex(poses[point.x], normals[point.z], uvs[point.y]));
            }
        }
    }

    return true;
}

void ObjParser::Terminate()
{
}
