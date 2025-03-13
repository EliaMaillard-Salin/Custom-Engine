#include "pch.h"
#include "OBJLoader.h"
#include "Geometry.h"
#include <fstream>

Geometry* OBJLoader::LoadOBJ(const char* filePath, DirectX::XMFLOAT4 color)
{
	Geometry* pGeometry = new Geometry();
	std::ifstream objFile(filePath);
	std::string line;

	std::vector<DirectX::XMFLOAT3> allPositions;
	std::vector<DirectX::XMFLOAT2> allUVs;

	int indicesCount = 0;

	while(!objFile.eof())
	{
		std::getline(objFile, line);

		if (line[0] == 'v')
		{
			
			if (line[1] == ' ') // positions
			{
				std::string posStr;
				for (int i = 2; i < line.size(); i++)
					posStr.push_back(line[i]);

				std::vector<std::string> separatedPos = SplitString(posStr, ' ');
				char* pEnd;
				float x = std::strtof(separatedPos[0].c_str(), &pEnd);
				float y = std::strtof(separatedPos[1].c_str(), &pEnd);
				float z = std::strtof(separatedPos[2].c_str(), &pEnd);

				allPositions.push_back(DirectX::XMFLOAT3(x, y, z));

			}
		
			if (line[1] == 't') // UVs
			{
				std::string uvStr;
				for (int i = 3; i < line.size(); i++)
					uvStr.push_back(line[i]);

				std::vector<std::string> separatedPos = SplitString(uvStr, ' ');
				char* pEnd;
				float u = std::strtof(separatedPos[0].c_str(), &pEnd);
				float v = std::strtof(separatedPos[1].c_str(), &pEnd);

				allUVs.push_back(DirectX::XMFLOAT2(u, 1-v));
			}

			if (line[1] == 'n')
			{
				// Normals
			}
		
		}




		else if (line[0] == 'f')
		{
			std::string facesStr;
			for (int i = 2; i < line.size(); i++)
				facesStr.push_back(line[i]);

			std::vector<std::string> separatedFaces = SplitString(facesStr, ' ');
			std::vector<std::vector<std::string>> separatedIndex;
			for (int i = 0; i < separatedFaces.size(); i++)
				separatedIndex.push_back(SplitString(separatedFaces[i], '/'));
			

			for (int i = 0; i < separatedIndex.size(); i++)
			{
				int pos = std::stoi(separatedIndex[i][0]);
				int uvs = std::stoi(separatedIndex[i][1]);
				int norm = std::stoi(separatedIndex[i][2]);

				pGeometry->positions.push_back(DirectX::XMFLOAT3(allPositions[pos - 1]));
				pGeometry->colors.push_back(color);
				pGeometry->UVs.push_back(DirectX::XMFLOAT2(allUVs[uvs - 1]));
				pGeometry->indexes.push_back(indicesCount);
				indicesCount += 1;
			}
		
		}
	
	}

	pGeometry->indiceNumber = indicesCount;

	return pGeometry;
}

std::vector<std::string> OBJLoader::SplitString(std::string string, char separator)
{
	std::vector<std::string> res;
	
	std::string temp;

	for (int i = 0 ; i < string.size(); i++)
	{
		if (string[i] == separator)
		{
			res.push_back(std::string(temp));
			temp.clear();
			continue;
		}
		temp.push_back(string[i]);
	}
	if (!temp.empty())
	{
		res.push_back(std::string(temp));
		temp.clear();
	}

	return res;
}
