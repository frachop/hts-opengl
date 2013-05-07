#include "common.h"
//* /////////////////////////////////////////////////////////////////////////////

static inline bool isATICard(const std::string & strVendor ) {
	return (strVendor.find(std::string("ATI")) != std::string::npos); }

static inline bool isNVidiaCard(const std::string & strVendor ) {
	return (strVendor.find(std::string("NVidia")) != std::string::npos); }

namespace HTS_NAMESPACE {
namespace HTS_GL_NAMESPACE {

	//* /////////////////////////////////////////////////////////////////////////////

	bool CInfos::_isATICard()
	{
		const char* str = ( const char* )glGetString(GL_VENDOR);
		if (str == NULL)
			return false;

		return ::isATICard(str);
	}

	bool CInfos::_isNVidiaCard()
	{
		const char* str = ( const char* )glGetString(GL_VENDOR);
		if (str == NULL)
			return false;

		return ::isNVidiaCard(str);
	}

	//* /////////////////////////////////////////////////////////////////////////////

	CInfos::CInfos()
	:	m_redBits(0)
	,	m_greenBits(0)
	,	m_blueBits(0)
	,	m_alphaBits(0)
	,	m_depthBits(0)
	,	m_stencilBits(0)
	,	m_maxTexture2DSize(0)
	,	m_maxTexture3DSize(0)
	,	m_maxLights(0)
	,	m_maxAttribStacks(0)
	,   m_maxModelViewStacks(0)
	,	m_maxProjectionStacks(0)
	,	m_maxClipPlanes(0)
	,	m_maxTextureStacks(0)
	{
	}

	bool CInfos::get()
	{
		char* str = 0;
		char* tok = 0;

		// get vendor string
		str = (char*)glGetString(GL_VENDOR);
		if(str) m_vendor = str;                  // check NULL return value
		else return false;

		// get renderer string
		str = (char*)glGetString(GL_RENDERER);
		if(str) m_renderer = str;                // check NULL return value
		else return false;

		// get version string
		str = (char*)glGetString(GL_VERSION);
		if(str) m_version = str;                 // check NULL return value
		else return false;

		// get all extensions as a string
		str = (char*)glGetString(GL_EXTENSIONS);

		// split extensions
		if(str)
		{
			tok = strtok((char*)str, " ");
			while(tok)
			{
				m_extensions.push_back(tok);    // put a extension into struct
				tok = strtok(0, " ");               // next token
			}
		}
		else
		{
			return false;
		}

		// sort extension by alphabetical order
		std::sort(m_extensions.begin(), m_extensions.end());

		// get number of color bits
		glGetIntegerv(GL_RED_BITS, &m_redBits);
		glGetIntegerv(GL_GREEN_BITS, &m_greenBits);
		glGetIntegerv(GL_BLUE_BITS, &m_blueBits);
		glGetIntegerv(GL_ALPHA_BITS, &m_alphaBits);

		// get depth bits
		glGetIntegerv(GL_DEPTH_BITS, &m_depthBits);

		// get stecil bits
		glGetIntegerv(GL_STENCIL_BITS, &m_stencilBits);

		// get max number of lights allowed
		glGetIntegerv(GL_MAX_LIGHTS, &m_maxLights);

		// get max texture resolution
		glGetIntegerv(GL_MAX_TEXTURE_SIZE, &m_maxTexture2DSize);
		glGetIntegerv(GL_MAX_3D_TEXTURE_SIZE, &m_maxTexture3DSize);

		// get max number of clipping planes
		glGetIntegerv(GL_MAX_CLIP_PLANES, &m_maxClipPlanes);

		// get max modelview and projection matrix stacks
		glGetIntegerv(GL_MAX_MODELVIEW_STACK_DEPTH, &m_maxModelViewStacks);
		glGetIntegerv(GL_MAX_PROJECTION_STACK_DEPTH, &m_maxProjectionStacks);
		glGetIntegerv(GL_MAX_ATTRIB_STACK_DEPTH, &m_maxAttribStacks);

		// get max texture stacks
		glGetIntegerv(GL_MAX_TEXTURE_STACK_DEPTH, &m_maxTextureStacks);

		return true;
	}

	bool CInfos::isATICard() const
	{
		return ::isATICard(m_vendor);
	}

	bool CInfos::isNVidiaCard() const
	{
		return ::isNVidiaCard(m_vendor);
	}

	///////////////////////////////////////////////////////////////////////////////
	// check if the video card support a certain extension
	///////////////////////////////////////////////////////////////////////////////
	bool CInfos::isExtensionSupported(const std::string& ext)
	{
		// search corresponding extension
		std::vector<std::string>::const_iterator iter = m_extensions.begin();
		std::vector<std::string>::const_iterator endIter = m_extensions.end();

		while(iter != endIter)
		{
			if(ext == *iter)
				return true;
			else
				++iter;
		}
		return false;
	}



	///////////////////////////////////////////////////////////////////////////////
	// print OpenGL info to screen and save to a file
	///////////////////////////////////////////////////////////////////////////////
	void CInfos::print(bool bWithExt)
	{
		std::stringstream ss;

		ss << std::endl; // blank line
		ss << "OpenGL Driver Info" << std::endl;
		ss << "==================" << std::endl;
		ss << "Vendor: " << m_vendor << std::endl;
		ss << "Version: " << m_version << std::endl;
		ss << "Renderer: " << m_renderer << std::endl;

		ss << std::endl;
		ss << "Color Bits(R,G,B,A): (" << m_redBits << ", " << m_greenBits
		   << ", " << m_blueBits << ", " << m_alphaBits << ")\n";
		ss << "Depth Bits: " << m_depthBits << std::endl;
		ss << "Stencil Bits: " << m_stencilBits << std::endl;

		ss << std::endl;
		ss << "Max Texture 2D Size: " << m_maxTexture2DSize << "x" << m_maxTexture2DSize << std::endl;
		ss << "Max Texture 3D Size: " << m_maxTexture3DSize << "x" << m_maxTexture3DSize << "x" << m_maxTexture3DSize << std::endl;
		ss << "Max Lights: " << m_maxLights << std::endl;
		ss << "Max Clip Planes: " << m_maxClipPlanes << std::endl;
		ss << "Max Modelview Matrix Stacks: " << m_maxModelViewStacks << std::endl;
		ss << "Max Projection Matrix Stacks: " << m_maxProjectionStacks << std::endl;
		ss << "Max Attribute Stacks: " << m_maxAttribStacks << std::endl;
		ss << "Max Texture Stacks: " << m_maxTextureStacks << std::endl;

		ss << std::endl;
		ss << "Total Number of Extensions: " << m_extensions.size() << std::endl;
		if (bWithExt) {

			ss << "==============================" << std::endl;

			for(unsigned int i = 0; i < m_extensions.size(); ++i)
				ss << m_extensions.at(i) << std::endl;

			ss << "======================================================================" << std::endl;
		}
		std::cout << ss.str() << std::endl;
	}

}}
