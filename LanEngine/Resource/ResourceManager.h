#pragma once
#include "../Utils/Utils.h"
#include "../Defines.h"
#include <map>
#include <functional>
#include "Resource.h"
#include "ResourceFactory.h"

namespace Lan
{
	class ResourceManager final : public Singleton<ResourceManager>
	{
	public:
		friend Singleton<ResourceManager>;

		/* 리소스의 타입 추가
		 * extension : 확장자, factory : 해당 리소스를 생성하는 팩토리
		 * ResourceFactory<ResourceType>::GetInstance()로 넣으면 됨
		 */
		void AddResourceType(tstring extension, Factory& factory);

		bool LoadResource(tstring name);
		//bool loadSet(tstring name);

		void UnloadResource(tstring name);
		//void unloadSet(tstring name);

		//void moveSet(tstring unloadingSet, tstring loadingSet);

		Resource* GetResource(tstring name);

	private:
		ResourceManager();
		~ResourceManager();

		void ParseRes(tstring dataString);
		void InsertPath(tstring& rawName, tstring& rawPath, std::map<tstring, tstring> & val);
	
		std::map<tstring, Resource *> m_Resources;
		std::map<tstring, Factory *> m_Factories;
		std::map<tstring, tstring> m_Paths;
	};
}

#include "ResourceFactory.inl"