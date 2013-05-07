namespace HTS_NAMESPACE {
namespace HTS_GL_NAMESPACE {

	inline GLint CShader::getParamLocation( const std::string & pName) const
	{
		if (!isValid()) return -1;
		return glGetUniformLocation(m_program, static_cast<const GLchar *>(pName.c_str()));
	}

	//* ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	template<>
	inline bool CShader::set<int>( const std::string & pName, const int & v0, const int & v1, const int & v2, const int & v3 ) const
	{
		const GLint iP= getParamLocation(pName);
		if (iP < 0) return false;
		glUniform4i(iP, v0, v1, v2, v3);CHECK_GLERROR("");
		return true;
	}

	template<>
	inline bool CShader::set<int>( const std::string & pName, const int & v0, const int & v1, const int & v2 ) const
	{
		const GLint iP= getParamLocation(pName);
		if (iP < 0) return false;
		glUniform3i(iP, v0, v1, v2);CHECK_GLERROR("");
		return true;
	}

	template<>
	inline bool CShader::set<int>( const std::string & pName, const int & v0, const int & v1 ) const
	{
		const GLint iP= getParamLocation(pName);
		if (iP < 0) return false;
		glUniform2i(iP, v0, v1);CHECK_GLERROR("");
		return true;
	}

	template<>
	inline bool CShader::set<int>( const std::string & pName, const int & v) const
	{
		const GLint iP= getParamLocation(pName);
		if (iP < 0) return false;
		glUniform1i(iP, static_cast<GLint>(v));CHECK_GLERROR("");
		return true;
	}

	template<>
	inline bool CShader::set<CVector4i>( const std::string & pName, const CVector4i & v) const
	{
		return set<int>(pName, v[0], v[1], v[2], v[3]); CHECK_GLERROR("");
	}

	template<>
	inline bool CShader::set<CVector3i>( const std::string & pName, const CVector3i & v) const
	{
		return set<int>(pName, v[0], v[1], v[2]); CHECK_GLERROR("");
	}

	template<>
	inline bool CShader::set<CVector2i>( const std::string & pName, const CVector2i & v) const
	{
		return set<int>(pName, v[0], v[1]); CHECK_GLERROR("");
	}

	//* ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	template<>
	inline bool CShader::set<float>( const std::string & pName, const float & v0, const float & v1, const float & v2, const float & v3 ) const
	{
		const GLint iP= getParamLocation(pName);
		if (iP < 0) return false;
		glUniform4f(iP, v0, v1, v2, v3);CHECK_GLERROR("");
		return true;
	}

	template<>
	inline bool CShader::set<float>( const std::string & pName, const float & v0, const float & v1, const float & v2 ) const
	{
		const GLint iP= getParamLocation(pName);
		if (iP < 0) return false;
		glUniform3f(iP, v0, v1, v2);CHECK_GLERROR("");
		return true;
	}

	template<>
	inline bool CShader::set<float>( const std::string & pName, const float & v0, const float & v1 ) const
	{
		const GLint iP= getParamLocation(pName);
		if (iP < 0) return false;
		glUniform2f(iP, v0, v1);CHECK_GLERROR("");
		return true;
	}

	template<>
	inline bool CShader::set<float>( const std::string & pName, const float & v) const
	{
		const GLint iP= getParamLocation(pName);
		if (iP < 0) return false;
		glUniform1f(iP, static_cast<GLfloat>(v));CHECK_GLERROR("");
		return true;
	}

	template<>
	inline bool CShader::set<CVector4f>( const std::string & pName, const CVector4f & v) const
	{
		return set<float>(pName, v[0], v[1], v[2], v[3]); CHECK_GLERROR("");
	}

	template<>
	inline bool CShader::set<CVector3f>( const std::string & pName, const CVector3f & v) const
	{
		return set<float>(pName, v[0], v[1], v[2]); CHECK_GLERROR("");
	}

	template<>
	inline bool CShader::set<CVector2f>( const std::string & pName, const CVector2f & v) const
	{
		return set<float>(pName, v[0], v[1]); CHECK_GLERROR("");
	}

	//* ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	template<>
	inline bool CShader::set<double>( const std::string & pName, const double & v0, const double & v1, const double & v2, const double & v3 ) const
	{
		return set<float>(pName, static_cast<float>(v0), static_cast<float>(v1), static_cast<float>(v2), static_cast<float>(v3));
	}

	template<>
	inline bool CShader::set<double>( const std::string & pName, const double & v0, const double & v1, const double & v2 ) const
	{
		return set<float>(pName, static_cast<float>(v0), static_cast<float>(v1), static_cast<float>(v2));
	}

	template<>
	inline bool CShader::set<double>( const std::string & pName, const double & v0, const double & v1 ) const
	{
		return set<float>(pName, static_cast<float>(v0), static_cast<float>(v1));
	}

	template<>
	inline bool CShader::set<double>( const std::string & pName, const double & v) const
	{
		return set<float>(pName, static_cast<float>(v));
	}

	template<>
	inline bool CShader::set<CVector4d>( const std::string & pName, const CVector4d & v) const
	{
		return set<double>(pName, v[0], v[1], v[2], v[3]);
	}

	template<>
	inline bool CShader::set<CVector3d>( const std::string & pName, const CVector3d & v) const
	{
		return set<double>(pName, v[0], v[1], v[2]);
	}

	template<>
	inline bool CShader::set<CVector2d>( const std::string & pName, const CVector2d & v) const
	{
		return set<double>(pName, v[0], v[1]);
	}

	//* ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	template<>
	inline bool CShader::setArray<float>( const std::string & pName, int count, const float * v) const
	{
		const GLint iP= getParamLocation(pName);
		if (iP < 0) return false;
		glUniform1fv(iP, static_cast<const GLint>(count), static_cast<const GLfloat*>(v));CHECK_GLERROR("");
		return true;
	}
	template<>
	inline bool CShader::setArray<CVector2f>( const std::string & pName, int count, const CVector2f * v) const
	{
		const GLint iP= getParamLocation(pName);
		if (iP < 0) return false;
		glUniform2fv(iP, static_cast<const GLint>(count), (const GLfloat*)(v));CHECK_GLERROR("");
		return true;
	}
	template<>
	inline bool CShader::setArray<CVector3f>( const std::string & pName, int count, const CVector3f * v) const
	{
		const GLint iP= getParamLocation(pName);
		if (iP < 0) return false;
		glUniform3fv(iP, static_cast<const GLint>(count), (const GLfloat*)(v));CHECK_GLERROR("");
		return true;
	}
	template<>
	inline bool CShader::setArray<CVector4f>( const std::string & pName, int count, const CVector4f * v) const
	{
		const GLint iP= getParamLocation(pName);
		if (iP < 0) return false;
		glUniform4fv(iP, static_cast<const GLint>(count), (const GLfloat*)(v));CHECK_GLERROR("");
		return true;
	}

	//* ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	template<>
	inline bool CShader::setArray<int>( const std::string & pName, int count, const int * v) const
	{
		const GLint iP= getParamLocation(pName);
		if (iP < 0) return false;
		glUniform1iv(iP, static_cast<const GLint>(count), static_cast<const GLint*>(v));CHECK_GLERROR("");
		return true;
	}
	template<>
	inline bool CShader::setArray<CVector2i>( const std::string & pName, int count, const CVector2i * v) const
	{
		const GLint iP= getParamLocation(pName);
		if (iP < 0) return false;
		glUniform2iv(iP, static_cast<const GLint>(count), (const GLint*)(v));CHECK_GLERROR("");
		return true;
	}
	template<>
	inline bool CShader::setArray<CVector3i>( const std::string & pName, int count, const CVector3i * v) const
	{
		const GLint iP= getParamLocation(pName);
		if (iP < 0) return false;
		glUniform3iv(iP, static_cast<const GLint>(count), (const GLint*)(v));CHECK_GLERROR("");
		return true;
	}
	template<>
	inline bool CShader::setArray<CVector4i>( const std::string & pName, int count, const CVector4i * v) const
	{
		const GLint iP= getParamLocation(pName);
		if (iP < 0) return false;
		glUniform4iv(iP, static_cast<const GLint>(count), (const GLint*)(v));CHECK_GLERROR("");
		return true;
	}

}}
