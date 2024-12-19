#pragma once
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include "IService.h"

#define ASSETS_LOCAL_PATH "\\Resources\\"

class Assets : public IService
{
private:
	std::string assetsPath;

public:
	Assets(const std::string& exePath);
	void Terminate();

	std::string GetAssetPath(const std::string& localPath);
	std::string GetAssetStr(const std::string& localPath);
};

