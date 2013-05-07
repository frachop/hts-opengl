#include "common.h"

namespace HTS_NAMESPACE {
namespace HTS_GL_NAMESPACE {

	//* ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	typedef std::map<std::string, CShader*> CShaderMap;

	//* ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	CShaders::CShaders()
	{
	}

	CShaders::~CShaders()
	{
		for (CShaderMap::iterator it= m_shaders.begin(); it != m_shaders.end(); ++it)
			delete (it->second);
	}

	bool CShaders::exists( const std::string & name ) const
	{
		CShaderMap::const_iterator it= m_shaders.find( name );
		return (it != m_shaders.end());
	}

	bool CShaders::add( CShader* pShader, const std::string & name )
	{
		if (pShader == NULL)
			return false;

		CShaderMap::iterator it= m_shaders.find( name );
		if (it != m_shaders.end())
			return false;

		m_shaders.insert( CShaderMap::value_type(name, pShader));
		return true;
	}

	CShader * CShaders::get(const std::string & name) const
	{
		CShaderMap::const_iterator it= m_shaders.find( name);
		if (it == m_shaders.end())
			return NULL;

		return it->second;
	};


	//* ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


}}
