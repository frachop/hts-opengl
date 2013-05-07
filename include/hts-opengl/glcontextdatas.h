namespace HTS_NAMESPACE {
namespace HTS_GL_NAMESPACE {
	// * ////////////////////////////////////////////////////////////////////////////

	class CContextDatas
	{
	public:
		CContextDatas();
		virtual ~CContextDatas();

	public:
		virtual bool init();

	public:
		CFrameBufferManager & getFrameBufferManager() { return m_fbManager; }
		const CFrameBufferManager & getFrameBufferManager() const { return m_fbManager; }

		CTextureManager & getTextureManager() { return m_texManager; }
		const CTextureManager & getTextureManager() const { return m_texManager; }

		CShaders & getGLShaders() { return m_glShaders; }
		const CShaders & getGLShaders() const { return m_glShaders; }

	private:
		CFrameBufferManager m_fbManager ;
		CTextureManager     m_texManager;
		CShaders            m_glShaders ;

	#ifndef EZGL_NOCG

	public:
		CShaders & getShaders() { return m_shaders; }
		const CShaders & getShaders() const { return m_shaders; }

	private:
		CShaders m_shaders  ;

	#endif //EZGL_NOCG


	};

	// * ////////////////////////////////////////////////////////////////////////////

	class CContextDatasAccess
	{
	public:
		CContextDatasAccess( CContextDatas & gl ) : m_gl(gl) {}

	public:
		const CContextDatas & gl() const { return m_gl; }
		CContextDatas & gl() { return m_gl; }
		const CTextureManager & getTextureManager() const { return gl().getTextureManager(); }
		CTextureManager & getTextureManager() { return gl().getTextureManager(); }
		const CFrameBufferManager & getFrameBufferManager() const { return gl().getFrameBufferManager(); }
		CFrameBufferManager & getFrameBufferManager() { return gl().getFrameBufferManager(); }

	private:
		CContextDatas & m_gl;
	};

}}
