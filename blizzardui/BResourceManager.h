#ifndef BRESOURCEMANAGER_H
#define BRESOURCEMANAGER_H
#include <Crystal.h>
#include <Shard.h>
#include <map>
#include <string>

class BResourceManager
{
public:
	SRImage* operator[](std::string imageName);
	BResourceManager();
	void load(std::string fileName);
private:
protected:
	std::map<std::string, SRImage*> m_resourceMap;
};
#endif