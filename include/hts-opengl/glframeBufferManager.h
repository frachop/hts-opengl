namespace HTS_NAMESPACE {
namespace HTS_GL_NAMESPACE {

	// - //////////////////////////////////////////////////////////////////////////////////////////////

	class CFrameBufferManager
	{
	public:
		CFrameBufferManager();
		virtual ~CFrameBufferManager();

	public:
		FrameBuffer get();
		void release(FrameBuffer frameBuffer);

	private:
		std::set<FrameBuffer> m_availables;
		std::set<FrameBuffer> m_used;
	};

	// - //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	class CFrameBufferManaged
	{
	public:
		CFrameBufferManaged(CFrameBufferManager & manager);
		CFrameBufferManaged(CFrameBufferManager & manager, const CTexture & t, DepthBuffer zBuffer = 0);
		~CFrameBufferManaged();

	public:
		operator FrameBuffer() const { return m_fb; }

	public: // helpers
		bool attachColor( const CTexture & t, int index= 0);
		bool attachDepth( DepthBuffer zBuffer);

	private:
		GLint m_oldBinded;
		CFrameBufferManager & m_manager;
		FrameBuffer m_fb;
	};

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	///

	class CAutoOffscreenRender
	{
	public:
		CAutoOffscreenRender( CFrameBufferManager & mng, const CTexture & dst, CColorf clearColor= CColorf(0.f, 0.f, 0.f, 0.f), DepthBuffer zBuffer = 0);
		virtual ~CAutoOffscreenRender();

	protected:
		CFrameBufferManaged m_frameBuffer;
	};


}}
