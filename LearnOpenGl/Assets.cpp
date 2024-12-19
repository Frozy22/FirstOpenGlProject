#include "Assets.h"

Assets::Assets(const std::string& exePath)
{
	auto sepIndex = exePath.find_last_of('\\');
	auto path = exePath.substr(0, sepIndex);

	assetsPath = std::string{ path + ASSETS_LOCAL_PATH };
}

void Assets::Terminate()
{
	assetsPath = "";
}

std::string Assets::GetAssetPath(const std::string& localPath)
{
	return std::string{ assetsPath + localPath };
}

std::string Assets::GetAssetStr(const std::string& localPath)
{
    std::string assetPath = Assets::GetAssetPath(localPath);

    std::string result;
    std::ifstream assetFile;

    // ensure ifstream objects can throw exceptions:
    assetFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try
    {
        // open files
        assetFile.open(assetPath);

        std::stringstream assetStream;

        // read file's buffer contents into streams
        assetStream << assetFile.rdbuf();

        // close file handlers
        assetFile.close();

        // convert stream into string
        result = assetStream.str();
    }
    catch (std::ifstream::failure e)
    {
        std::cout << "ERROR::ASSETS::FILE_NOT_SUCCESFULLY_READ" << std::endl;
        return "";
    }

    return result;
}
