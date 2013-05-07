#include "common.h"
namespace HTS_NAMESPACE {
namespace HTS_GL_NAMESPACE {

	// - //////////////////////////////////////////////////////////////////////////////////////////////

	CFrameBufferManager::CFrameBufferManager()
	{
	}

	CFrameBufferManager::~CFrameBufferManager()
	{
		ASSERT( m_used.empty() );

		// unbind
		glBindFramebufferEXT( GL_FRAMEBUFFER_EXT, 0); CHECK_GLERROR("glBindFramebufferEXT");
		CHECK_GLERROR("");

		for (std::set<FrameBuffer>::iterator it= m_availables.begin(); it != m_availables.end(); ++it) {
			FrameBuffer fb = *it;
			glDeleteFramebuffersEXT(1, &fb); CHECK_GLERROR("glDeleteFramebuffersEXT");
			TRACEFN("%i destroyed\n", int(fb));
			CHECK_GLERROR("");
		}

	}

	FrameBuffer CFrameBufferManager::get()
	{
		FrameBuffer fb= CFrameBuffer::INVALID_ID;

		if ( m_availables.empty() ) {
			glGenFramebuffersEXT( 1, &fb ); CHECK_GLERROR("glGenFramebuffersEXT");
			CHECK_GLERROR("");
			m_availables.insert(fb);
			TRACEFN("%i created\n", int(fb));
		}

		fb=  *( m_availables.begin() );
		m_availables.erase( fb );
		m_used.insert( fb );
		return fb;
	}

	void CFrameBufferManager::release(FrameBuffer fb)
	{
		// unbind
		glBindFramebufferEXT( GL_FRAMEBUFFER_EXT, 0); CHECK_GLERROR("glBindFramebufferEXT");
		CHECK_GLERROR("");

		ASSERT( m_used.find( fb ) != m_used.end() );
		ASSERT( m_availables.find( fb ) == m_availables.end() );
		m_used.erase( fb );
		m_availables.insert(fb);
	}
	// - //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	CFrameBufferManaged::CFrameBufferManaged(CFrameBufferManager & manager)
	:	m_oldBinded(0)
	,	m_manager( manager)
	,	m_fb( m_manager.get() )
	{
	}

	CFrameBufferManaged::CFrameBufferManaged(CFrameBufferManager & manager, const CTexture & t, DepthBuffer zBuffer)
	:	m_manager( manager)
	,	m_fb( m_manager.get() )
	{
		glGetIntegerv( GL_FRAMEBUFFER_BINDING_EXT, &m_oldBinded); CHECK_GLERROR("glGetIntegerv");
		CHECK_GLERROR("");

		attachColor( t );
		if (zBuffer)
			attachDepth( zBuffer );
	}

	CFrameBufferManaged::~CFrameBufferManaged()
	{
		m_manager.release(m_fb);
		if (m_oldBinded) {
			glBindFramebufferEXT( GL_FRAMEBUFFER_EXT, m_oldBinded);
			CHECK_GLERROR("");
		}
	}

	bool CFrameBufferManaged::attachColor( const CTexture & t, int index)
	{
	#ifndef NDEBUG
		if (!glIsTexture(t)) {
			std::cerr << "CFrameBufferManaged::attachColor "  << (int) t.id() << " is not a texture " << std::endl;
			return false;
		}
	#endif
		CHECK_GLERROR("Before");
		glBindFramebufferEXT( GL_FRAMEBUFFER_EXT, m_fb ); CHECK_GLERROR("glBindFramebufferEXT");
		glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT + index, t.target(), t, 0); CHECK_GLERROR("FrameBufferTexture2DEXT");
		const GLenum stat = glCheckFramebufferStatusEXT(GL_FRAMEBUFFER_EXT);
		CHECK_GLERROR("");

		switch(stat) {

			case GL_FRAMEBUFFER_UNSUPPORTED_EXT:
				std::cerr << __PRETTY_FUNCTION__  << " : GL_FRAMEBUFFER_UNSUPPORTED_EXT color buffer" << std::endl;
				return false;

			case GL_FRAMEBUFFER_COMPLETE_EXT:
				break;

			default:
				std::cerr << "programming error; will fail on all hardware" << std::endl;
				return false;
		};
		return true;
	}

	bool CFrameBufferManaged::attachDepth( DepthBuffer zBuffer)
	{
		CHECK_GLERROR("");
		glBindFramebufferEXT( GL_FRAMEBUFFER_EXT, m_fb ); CHECK_GLERROR("glBindFramebufferEXT");
		glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_RENDERBUFFER_EXT, zBuffer);
		const GLenum stat = glCheckFramebufferStatusEXT(GL_FRAMEBUFFER_EXT);
		CHECK_GLERROR("");

		switch(stat) {

			case GL_FRAMEBUFFER_UNSUPPORTED_EXT:
				std::cerr << __PRETTY_FUNCTION__  << " : GL_FRAMEBUFFER_UNSUPPORTED_EXT Depth buffer" << std::endl;
				return false;

			case GL_FRAMEBUFFER_COMPLETE_EXT:
				break;

			default:
				std::cerr << "programming error; will fail on all hardware" << std::endl;
				return false;
		};
		return true;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	///

	CAutoOffscreenRender::CAutoOffscreenRender( CFrameBufferManager & mng, const CTexture & dst, CColorf clearColor, DepthBuffer zBuffer )
	:	m_frameBuffer(mng, dst, zBuffer)
	{
		CHECK_GLERROR("0");
		const unsigned int w = dst.getWidth ();
		const unsigned int h = dst.getHeight();
		glClearColor( clearColor.r, clearColor.g, clearColor.b, clearColor.a );
		//glClearColor( clearColor.r, 1, clearColor.b, clearColor.a );
		glClear( GL_COLOR_BUFFER_BIT ); CHECK_GLERROR("glClear");

		glPushAttrib( GL_VIEWPORT_BIT );
		glMatrixMode( GL_MODELVIEW ); glPushMatrix(); glLoadIdentity();
		glMatrixMode( GL_PROJECTION); glPushMatrix(); glLoadIdentity();

			glOrtho(0.0, GLdouble(w), 0.0, GLdouble(h), -1.0, 1.0);
			glViewport(0,0, GLint(w), GLint(h) );
			glColor4f(1.f,1.f,1.f,1.f);

		CHECK_GLERROR("1");
	}

	CAutoOffscreenRender::~CAutoOffscreenRender()
	{
		CHECK_GLERROR("0");
		glMatrixMode( GL_PROJECTION); glPopMatrix();
		glMatrixMode( GL_MODELVIEW ); glPopMatrix();
		glPopAttrib();
		CHECK_GLERROR("1");
	}
}}
