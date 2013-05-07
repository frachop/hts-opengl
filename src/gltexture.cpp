#include "common.h"
namespace HTS_NAMESPACE {
namespace HTS_GL_NAMESPACE {

	/*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/

	CTexture::CTexture()
	:	m_id(INVALID_TEXTURE_ID)
	,	m_target(INVALID_TEXTURE_TARGET)
	,	m_w( 0 ), m_h( 0 ), m_d(0)
	{
	}

	CTexture::CTexture( const CTexture & src)
	:	m_id(src.m_id)
	,	m_target(src.m_target)
	,	m_w( src.m_w ), m_h( src.m_h ), m_d(src.m_d)
	{
	}

	CTexture::CTexture(GLenum target, Texture id, unsigned int w, unsigned int h, unsigned int d)
	:	m_id(id)
	,	m_target(target)
	,	m_w( w ), m_h( h ), m_d(d)
	{
		_updateSize();
	}

	CTexture::~CTexture()
	{
		//destroy();
	}

	CTexture & CTexture::operator=( const CTexture & src)
	{
		if (this != &src) {
			m_id = src.m_id;
			m_target = src.m_target;
			m_w = src.m_w;
			m_h = src.m_h;
			m_d = src.m_d;
		}
		return (*this);
	}

	void CTexture::_updateSize()
	{
		GLint res = 0;
		if ((m_w == 0) || (m_h == 0)) {
			if (isValidId()) {
				bind();
				if (m_w == 0) {
					glGetTexLevelParameteriv(m_target,0, GL_TEXTURE_WIDTH, &res);
					CHECK_GLERROR("\n");
					m_w = res;
				}
				if (m_h == 0) {
					glGetTexLevelParameteriv(m_target,0, GL_TEXTURE_HEIGHT, &res);
					CHECK_GLERROR("\n");
					m_h = res;
				}
				if (m_d == 0) {
					glGetTexLevelParameteriv(m_target,0, GL_TEXTURE_DEPTH, &res);
					CHECK_GLERROR("\n");
					m_d = res;
				}
				unbind();
			}
		}
	}

	Texture CTexture::attach(GLenum target, Texture id, unsigned int w, unsigned int h, unsigned int d)
	{
		Texture res= m_id;
		m_id = id;
		m_target = target;
		m_w = w;
		m_h = h;
		m_d = d;
		_updateSize();
		return res;
	}


	void CTexture::destroy()
	{
		if (isValidId()) {
			TRACEFN("deleting texture %i\n", m_id);
			glDeleteTextures( 1, &m_id );
			CHECK_GLERROR("\n");
			m_id = INVALID_TEXTURE2D_ID;
			m_w = m_h = m_d= 0;
		}
	}

	Texture CTexture::gen()
	{
		destroy();
		glGenTextures(1, &m_id);
		TRACEFN("%i\n", m_id);
		return m_id;
	}

	Texture CTexture::setMinMaxFilters(GLint textureMinMaxFilter) const {
		ASSERT( isValidId() );
		bind();
		glTexParameteri(m_target, GL_TEXTURE_MIN_FILTER, textureMinMaxFilter); CHECK_GLERROR("glTexParameteri");
		glTexParameteri(m_target, GL_TEXTURE_MAG_FILTER, textureMinMaxFilter); CHECK_GLERROR("glTexParameteri");
		unbind();
		return m_id;
	}

	Texture CTexture::setWrapMode(GLint textureWrapST) const {
		ASSERT( isValidId() );
		bind();
		glTexParameteri(m_target, GL_TEXTURE_WRAP_S, textureWrapST); CHECK_GLERROR("glTexParameteri");
		glTexParameteri(m_target, GL_TEXTURE_WRAP_T, textureWrapST); CHECK_GLERROR("glTexParameteri");
		unbind();
		return m_id;
	}

	Texture1D CTexture::create1D(
			unsigned int w,
			GLenum target,
			GLenum internalFormat,
			GLenum format,
			GLenum type,
			const GLvoid * pixels,
			GLint textureMinMaxFilter,
			GLint textureWrapST
		) {
		texImage1D(w, target, internalFormat, format, type, pixels);
		setWrapMode(textureWrapST);
		setMinMaxFilters(textureMinMaxFilter);
		return m_id;

	}

	Texture1D CTexture::texImage1D(
			unsigned int w,
			GLenum target,
			GLenum internalFormat,
			GLenum format,
			GLenum type,
			const GLvoid * pixels
		) {

		ASSERT(w);

		if (!isValidId())
			gen();

		m_target= target;

		bind();
		glTexImage1D(m_target, 0, internalFormat, w, 0, format, type, pixels );    CHECK_GLERROR("glTexImage1D");
		unbind();
		m_w = w; m_h = m_d= 0;
		return m_id;
	}


	Texture2D CTexture::create2D(
			unsigned int w, unsigned int h,
			GLenum target,
			GLenum internalFormat,
			GLenum format,
			GLenum type,
			const GLvoid * pixels,
			GLint textureMinMaxFilter,
			GLint textureWrapST
		) {
		texImage2D(w,h, target, internalFormat, format, type, pixels);
		setWrapMode(textureWrapST);
		setMinMaxFilters(textureMinMaxFilter);
		return m_id;

	}

	Texture2D CTexture::texImage2D(
			unsigned int w, unsigned int h,
			GLenum target,
			GLenum internalFormat,
			GLenum format,
			GLenum type,
			const GLvoid * pixels
		) {

		ASSERT((w) && (h));

		if (!isValidId())
			gen();

		m_target= target;

		bind();
		glTexImage2D(m_target, 0, internalFormat, w, h, 0, format, type, pixels );    CHECK_GLERROR("glTexImage2D");
		unbind();
		m_w = w; m_h = h; m_d= 0;
		return m_id;
	}

	Texture3D CTexture::create3D(
			unsigned int w, unsigned int h, unsigned int d,
			GLenum target,
			GLenum internalFormat,
			GLenum format,
			GLenum type,
			const GLvoid * pixels,
			GLint textureMinMaxFilter,
			GLint textureWrapST
		) {
		texImage3D(w,h,d, target, internalFormat, format, type, pixels);
		setWrapMode(textureWrapST);
		setMinMaxFilters(textureMinMaxFilter);
		return m_id;
	}

	Texture3D CTexture::texImage3D(
			unsigned int w, unsigned int h, unsigned int d,
			GLenum target,
			GLenum internalFormat,
			GLenum format,
			GLenum type,
			const GLvoid * pixels
		) {

		ASSERT((w) && (h) && (d));

		if (!isValidId())
			gen();

		m_target= target;

		bind();
		glTexImage3D(m_target, 0, internalFormat, w, h, d, 0, format, type, pixels );    CHECK_GLERROR("glTexImage3D");
		unbind();
		m_w = w; m_h = h; m_d= d;
		return m_id;
	}

	Texture CTexture::create(
			unsigned int w, unsigned int h, unsigned int d,
			GLenum target,
			GLenum internalFormat,
			GLenum format,
			GLenum type,
			const GLvoid * pixels,
			GLint textureMinMaxFilter,
			GLint textureWrapST
		) {

		if (d)
			return create3D(w,h,d,target,internalFormat,format,type,pixels,textureMinMaxFilter,textureWrapST);

		if (h)
			return create2D(w,h,target,internalFormat,format,type,pixels,textureMinMaxFilter,textureWrapST);

		ASSERT(w);
		return create1D(w,target,internalFormat,format,type,pixels,textureMinMaxFilter,textureWrapST);
	}

	bool CTexture::exportToTmpFileAuto( const std::string & name, GLenum format, GLenum type ) const
	{

	#ifndef NDEBUG
		if (!IS_VALID_TEXTURE_ID(m_id))
			return false;

		static int i(0);
		return HTS_NAMESPACE::HTS_GL_NAMESPACE::exportTextureToFile(target(), id(),
				HTS_NAMESPACE::string::format("/tmp/%i_id[%i]_%ix%i_%s.raw",i++, m_id, m_w, m_h, name.c_str()),format, type);

	#else
		(void)name; (void)format; (void)type;
	#endif
		return true;
	}



	void CTexture::bind() const {
		if ( IS_VALID_TEXTURE_ID(m_id) ) {
			//glEnable( m_target ); CHECK_GLERROR("glEnable texture target");
			glBindTexture( m_target, m_id);
			CHECK_GLERROR("glBindTexture");
		}
	}
	void CTexture::unbind() const {
		if ( IS_VALID_TEXTURE_ID(m_id) ) {
			// ASSERT( glIsTexture(m_id) );
			CHECK_GLERROR("AVANT glBindTexture !!!!!");
			glBindTexture( m_target, 0);
			CHECK_GLERROR("glBindTexture");
		}
	}

}}
