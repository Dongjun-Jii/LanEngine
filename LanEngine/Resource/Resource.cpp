#include "Defines.h"
#include "Resource.h"

namespace Lan
{
	Resource::Resource(void * buffer, tsize len, tstring path, tstring extension) :
		m_Path(path),
		m_Extension(extension)
	{
		
	}

	Resource::~Resource()
	{
		
	}

	const tstring& Resource::getExtension() const
	{
		return m_Extension;
	}

	const tstring& Resource::getPath() const
	{
		return m_Path;
	}
}