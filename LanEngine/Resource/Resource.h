#pragma once
#include "../Defines.h"

namespace Lan
{
	class ResourceManager;
	class Resource
	{
	public:
		friend ResourceManager;
		Resource(void * buffer, tsize len, tstring path, tstring extension);
		virtual ~Resource();

		const tstring& getExtension() const;
		const tstring& getPath() const;

	private:
		tstring m_Extension;
		tstring m_Path;
	};

}