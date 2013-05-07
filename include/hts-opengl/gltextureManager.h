namespace HTS_NAMESPACE {
namespace HTS_GL_NAMESPACE {
	//* /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	class CTextureManagerKey
	{
	public:
		GLenum    m_target;
		GLint     m_w, m_h, m_d; // width, height, depth
		GLint     m_internalFormat;
		GLenum    m_format;
		GLenum    m_type;

	public:
		CTextureManagerKey(GLenum target=0, GLint w=0, GLint h=0, GLint d=0, GLint internalFormat= 0, GLenum format= 0, GLenum type= 0)
		:	m_target(target), m_w(w), m_h(h), m_d(d), m_internalFormat(internalFormat), m_format(format), m_type(type) {}

		bool operator<( const CTextureManagerKey & b) const;
	};

	//* /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	class CTextureManagerImpl;
	class CTextureManager
	:	public CObservable
	{
	public:
		enum {
			NOTIFY_GETNEW = 0x0f,
			NOTIFY_GET,
			NOTIFY_RELEASED,
			NOTIFY_CREATENEW,
			NOTIFY_DELETING,
			NOTIFY_DELETED,
		};

	public:
		CTextureManager();
		virtual ~CTextureManager();
		void purgeAll();

	public:
		bool isManaged( Texture2D id ) const;
		CTexture get( GLenum target, unsigned int w, GLint internalFormat, GLenum format, GLenum type );
		CTexture get( GLenum target, unsigned int w, unsigned int h, GLint internalFormat, GLenum format, GLenum type );
		CTexture get( GLenum target, unsigned int w, unsigned int h, unsigned int d, GLint internalFormat, GLenum format, GLenum type );

	public:
		bool get( Texture id ); // increment refcount
		bool release( Texture id );// decrement refcount
		int refCount( Texture id ) const ; // renvoie < 0 si non managée

	public:
		CTextureManagerKey getInfos(Texture id) const;
		size_t getAllManaged(std::set<Texture> & all) const;

	private:
		std::auto_ptr<CTextureManagerImpl> m_pImpl;
	};

	//* /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}}
