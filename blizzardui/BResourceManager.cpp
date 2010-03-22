#include <BResourceManager.h>
#include <xmlParser.h>

BResourceManager::BResourceManager()
{
}
void BResourceManager::load(std::string fileName)
{
	XMLNode xmlRoot=XMLNode::openFileHelper("Blizzard.xml","BlizzardUI");
	XMLNode xmlHeader=xmlRoot.getChildNode("Header");
	if(xmlHeader.isEmpty())
	{
		//Log here
	}
	else
	{
		XMLNode xmlResources=xmlRoot.getChildNode("Resources");
		if(xmlResources.isEmpty())
		{
			//Log here
		}
		else
		{
			int numResources = xmlResources.nChildNode("Resources");
			int iResourceIterator = 0;
			XMLNode xmlIterator;
			for( ; iResourceIterator < numResources ; iResourceIterator++ )
			{
				xmlIterator = xmlResources.getChildNode("Resources", iResourceIterator);
				if(xmlIterator.isEmpty())
				{
					//Log here
				}
				else
				{
					std::string name = std::string(xmlIterator.getAttribute("name"));
					std::string file = std::string(xmlIterator.getAttribute("file"));
					SRImage* img = allocate<SRImage>();
					img->load(file.c_str());
					m_resourceMap[name] = img;
				}
			}
		}
	}
}
SRImage* BResourceManager::operator[](std::string imageName)
{
	return m_resourceMap[imageName];
}