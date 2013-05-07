#include "common.h"

namespace HTS_NAMESPACE {
namespace HTS_GL_NAMESPACE {
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	///

	CFrameBuffer::CFrameBuffer(bool bAutoDeleteTextures)
	:	m_frameBuffer(INVALID_ID)
	,	m_bAutoDeleteTextures(bAutoDeleteTextures)
	{
	}
	
	CFrameBuffer::~CFrameBuffer() {
		destroy();
	}
	
	void CFrameBuffer::destroy() {

		unbind();

		if (isAutoDeleteTextures())
			for (CTextureList::const_iterator it= m_textures.begin(); it != m_textures.end(); ++it)
				delete (it->second);

		m_textures.clear();

		if (m_frameBuffer) {
			glDeleteFramebuffersEXT(1, &m_frameBuffer);
			m_frameBuffer = INVALID_ID;
		}
		
	}
	
	bool CFrameBuffer::create() {
		destroy();
		glGenFramebuffersEXT( 1, &m_frameBuffer ); CHECK_GLERROR("glGenFramebuffersEXT");
		return true;
	}
	
	void CFrameBuffer::bind() {
		glBindFramebufferEXT( GL_FRAMEBUFFER_EXT, m_frameBuffer ); CHECK_GLERROR("glBindFramebufferEXT");
	}
	
	void CFrameBuffer::unbind() {
		glBindFramebufferEXT( GL_FRAMEBUFFER_EXT, 0); CHECK_GLERROR("glBindFramebufferEXT");
	}
	
	bool CFrameBuffer::attach(const CTexture * t, unsigned short index) {
		if (t == NULL)
			return false;

		const GLint level = 0;

		bind();

		glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT + index, t->target(), t->id(), level);
		CHECK_GLERROR("FrameBufferTexture2DEXT");
	
		const GLenum stat = glCheckFramebufferStatusEXT(GL_FRAMEBUFFER_EXT);

		unbind();

		bool bOk = false;
		switch(stat) {

			case GL_FRAMEBUFFER_UNSUPPORTED_EXT:
				std::cout << __PRETTY_FUNCTION__  << " : GL_FRAMEBUFFER_UNSUPPORTED_EXT" << std::endl;
				break;

			case GL_FRAMEBUFFER_COMPLETE_EXT:
				bOk = true;
				m_textures[index] = t;
				break;

			default:
				std::cout << "programming error; will fail on all hardware" << std::endl;
				break;
		};

		return bOk;
	}
	
	
	CTexture * CFrameBuffer::getTexture(unsigned short index) const {
		CTextureList::const_iterator it= m_textures.find(index);
		if (it == m_textures.end())
			return NULL;
			
		return (CTexture *) (it->second);
	}

	bool CFrameBuffer::bindTexture( unsigned short index ) {
		
		const CTexture * pTexture= getTexture(index);
		if (pTexture == NULL)
			return false;

		// unbind all texture's target
		glBindTexture( pTexture->target(), 0 );   CHECK_GLERROR("glBindTexture");
		
		bind();
		
		glDrawBuffer(GL_COLOR_ATTACHMENT0_EXT + index);    CHECK_GLERROR("glDrawBuffer");
		return true;
	}
	
	
	bool CFrameBuffer::getFrameFufferSize(unsigned short index, int & width, int & height) const {
		const CTexture * pTexture= getTexture(index);
		if (pTexture == NULL) {
			width = height= 0;
			return false;
		}

		width = pTexture->getWidth();
		height= pTexture->getHeight();
		return true;
	}
	
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	///
	
	#if 0
	
	bool CFrameBuffer::attach(const CTexture & t, unsigned int index) {
		const GLint level = 0;

		bind();

		FrameBufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT + index, t.target(), t.id(), level);
		CHECK_GLERROR("FrameBufferTexture2DEXT");
	
		const GLenum stat = glCheckFramebufferStatusEXT(GL_FRAMEBUFFER_EXT);
		unbind();

		bool bOk = false;
		switch(stat) {

			case GL_FRAMEBUFFER_UNSUPPORTED_EXT:
				cout << __PRETTY_FUNCTION__  << " : GL_FRAMEBUFFER_UNSUPPORTED_EXT" << endl;
				break;

			case GL_FRAMEBUFFER_COMPLETE_EXT:
				bOk = true;
				m_textures[index] = &t;
				break;

			default:
				cout<<"programming error; will fail on all hardware"<<endl;
				break;
		};
			
		return bOk;
	}

	bool CFrameBuffer::bindTexture( unsigned int index ) {
		std::map<unsigned short, const CTexture *>::const_iterator it= m_textures.find(index);
		if (it == m_textures.end())
			return false;
		
		glBindTexture( m_textures[index]->target(), 0 );   CHECK_GLERROR("glBindTexture");
		bind();
		glDrawBuffer(GL_COLOR_ATTACHMENT0_EXT + index);    CHECK_GLERROR("glDrawBuffer");
		return true;
	}

	bool CFrameBuffer::getFrameFufferSize(unsigned int index, int & width, int & height) const {
		std::map<unsigned short, const CTexture *>::const_iterator it= m_textures.find(index);
		if (it == m_textures.end())
			return false;

		width = (it->second)->getWidth();
		height= (it->second)->getHeight();
		return true;
	}
	#endif
	
}}
