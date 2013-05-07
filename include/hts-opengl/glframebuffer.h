namespace HTS_NAMESPACE {
namespace HTS_GL_NAMESPACE {

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	///

	class CFrameBuffer
	{
	public:
		enum { INVALID_ID = (FrameBuffer) -1 };

	public:
		CFrameBuffer(bool bAutoDeleteTextures = true);
		virtual ~CFrameBuffer();
		operator FrameBuffer() const { return m_frameBuffer; }

	public:
		bool isAutoDeleteTextures() const { return m_bAutoDeleteTextures; }
		void setAutoDeleteTextures(bool bSet) { m_bAutoDeleteTextures = bSet; }

	public:
		bool create();
		bool isCreated() const { return (m_frameBuffer != INVALID_ID); }
		bool attach(const CTexture * t, unsigned short index= 0);
		void destroy();

	public:
		void bind();
		static void unbind();
		bool bindTexture( unsigned short index = 0 );

	public:
		CTexture * getTexture(unsigned short index= 0) const;
		bool getFrameFufferSize(unsigned short index, int & width, int & height) const;

	protected:
		FrameBuffer m_frameBuffer;
		bool m_bAutoDeleteTextures;
		typedef std::map<unsigned short, const CTexture *> CTextureList;
		CTextureList m_textures;
	
	private:
		CFrameBuffer(const CFrameBuffer & ); // no impl.
		CFrameBuffer & operator=(const CFrameBuffer & src); // no impl.
	};

}}
