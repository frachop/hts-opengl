namespace HTS_NAMESPACE {
namespace HTS_GL_NAMESPACE {
	/*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/

	class CTexture
	{
	public:
		CTexture();
		CTexture(const CTexture & src);
		CTexture(GLenum target, Texture id, unsigned int w = 0, unsigned int h = 0, unsigned int d= 0);
		CTexture & operator=(const CTexture & src); // Attention destroy n'est pas appelé avant l'affectation
		virtual ~CTexture(); // n'appel pas destroy !!!!

	public:
		operator Texture() const { return m_id; }

	public:
		bool isValidId() const;

	public:
		Texture attach(const CTexture & src) { Texture result = m_id; (*this) = src; return result; }  // Attention destroy n'est pas appelé avant l'affectation
		Texture attach(GLenum target, Texture id, unsigned int w = 0, unsigned int h = 0, unsigned int d= 0);  // Attention destroy n'est pas appelé avant l'affectation
		Texture detach() { const Texture res = m_id; m_id = INVALID_TEXTURE_ID; return res; }

	public:
		void destroy();
		Texture gen();

		Texture1D create1D(
				unsigned int w,
				GLenum target  = GL_TEXTURE_1D,
				GLenum internalFormat = GL_RGBA8,
				GLenum format  = GL_RGBA,
				GLenum type    = GL_UNSIGNED_BYTE,
				const GLvoid * pixels = NULL,
				GLint textureMinMaxFilter = GL_NEAREST,
				GLint textureWrapST = GL_CLAMP
			);

		Texture1D texImage1D(
				unsigned int w,
				GLenum target  = GL_TEXTURE_1D,
				GLenum internalFormat = GL_RGBA8,
				GLenum format  = GL_RGBA,
				GLenum type    = GL_UNSIGNED_BYTE,
				const GLvoid * pixels = NULL
			);

		Texture2D create2D(
				unsigned int w, unsigned int h,
				GLenum target  = GL_TEXTURE_RECTANGLE_ARB,
				GLenum internalFormat = GL_RGBA8,
				GLenum format  = GL_RGBA,
				GLenum type    = GL_UNSIGNED_BYTE,
				const GLvoid * pixels = NULL,
				GLint textureMinMaxFilter = GL_NEAREST,
				GLint textureWrapST = GL_CLAMP
			);

		Texture2D texImage2D(
				unsigned int w, unsigned int h,
				GLenum target  = GL_TEXTURE_RECTANGLE_ARB,
				GLenum internalFormat = GL_RGBA8,
				GLenum format  = GL_RGBA,
				GLenum type    = GL_UNSIGNED_BYTE,
				const GLvoid * pixels = NULL
			);

		Texture3D create3D(
				unsigned int w, unsigned int h, unsigned int d,
				GLenum target  = GL_TEXTURE_3D,
				GLenum internalFormat = GL_RGBA8,
				GLenum format  = GL_RGBA,
				GLenum type    = GL_UNSIGNED_BYTE,
				const GLvoid * pixels = NULL,
				GLint textureMinMaxFilter = GL_NEAREST,
				GLint textureWrapST = GL_CLAMP
			);

		Texture3D texImage3D(
				unsigned int w, unsigned int h, unsigned int d,
				GLenum target  = GL_TEXTURE_3D,
				GLenum internalFormat = GL_RGBA8,
				GLenum format  = GL_RGBA,
				GLenum type    = GL_UNSIGNED_BYTE,
				const GLvoid * pixels = NULL
			);

		Texture create(
				unsigned int w, unsigned int h, unsigned int d,
				GLenum target,
				GLenum internalFormat = GL_RGBA8,
				GLenum format  = GL_RGBA,
				GLenum type    = GL_UNSIGNED_BYTE,
				const GLvoid * pixels = NULL,
				GLint textureMinMaxFilter = GL_NEAREST,
				GLint textureWrapST = GL_CLAMP
			);

		Texture setMinMaxFilters(GLint textureMinMaxFilter = GL_LINEAR) const;
		Texture setWrapMode(GLint textureWrapST= GL_CLAMP) const;

	public:
		CSizei getSize() const { return CSizei( (int) getWidth (), (int) getHeight() ); }
		unsigned int getWidth () const { return m_w; }
		unsigned int getHeight() const { return m_h; }
		unsigned int getDepth () const { return m_d; }
		GLenum target() const { return m_target; }
		Texture id() const { return m_id; }

	public:
		void bind() const;
		void unbind() const;

	public:
		bool exportToFile( const std::string & path, GLenum format= GL_RGBA, GLenum type= GL_UNSIGNED_BYTE ) const;
		bool exportToTmpFileAuto( const std::string & name, GLenum format= GL_RGBA, GLenum type= GL_UNSIGNED_BYTE ) const;

	private:
		void _updateSize();

	protected:
		Texture2D m_id     ;
		GLenum      m_target ;
		unsigned int m_w, m_h, m_d;
	};

	/*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/

	inline bool CTexture::isValidId() const {
		if (!IS_VALID_TEXTURE_ID(m_id))
			return false;

		//if (!glIsTexture(m_id)) return false;

		return true;
	}
}}
