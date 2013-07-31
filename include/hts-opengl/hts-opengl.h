#ifndef HTS_OPENGL_H_
#define HTS_OPENGL_H_ 1

/*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/

#include <hts-core/hts-core.h>

/*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/

#define GL_GLEXT_PROTOTYPES
#define GLX_GLXEXT_PROTOTYPES
#define GLX_VERSION_1_4

#ifdef __APPLE__
#	include <OpenGL/OpenGL.h>
#	include <OpenGL/gl.h>		// Header File For The OpenGL32 Library
#	ifndef NDEBUG
#		include <OpenGL/glu.h>		// for checkGlError
#	endif
#else
#	include <GL/gl.h>
#endif

/*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/

#define HTS_GL_NAMESPACE gl

//- /////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace HTS_NAMESPACE {
namespace HTS_GL_NAMESPACE {

	//- /////////////////////////////////////////////////////////////////////////////////////////////////////////

	typedef GLuint Texture;
	typedef GLuint Texture1D;
	typedef GLuint Texture2D;
	typedef GLuint Texture3D;
	typedef GLuint FrameBuffer;
	typedef GLuint DepthBuffer ;

	#define INVALID_TEXTURE_ID   ((Texture) -1)
	#define INVALID_TEXTURE1D_ID ((Texture1D) -1)
	#define INVALID_TEXTURE2D_ID ((Texture2D) -1)
	#define INVALID_TEXTURE3D_ID ((Texture3D) -1)

	#define INVALID_TEXTURE_TARGET (0)

	#define IS_VALID_TEXTURE_ID(id) ((id) != INVALID_TEXTURE_ID)
}}

	/*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/

	#include "glcheckerror.h"
	#include "gltools.h"
	#include "gltexture.h"
	#include "glquad.h"
	#include "glframebuffer.h"
	#include "glframeBufferManager.h"
	#include "gltextureManager.h"
	#include "glInfos.h"

	#include "glShaders.h"
	#include "glcontextdatas.h"

	#include "zoompos.h"

	/*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/

namespace HTS_NAMESPACE {
namespace HTS_GL_NAMESPACE {

	inline bool CTexture::exportToFile( const std::string & path, GLenum frmt, GLenum type ) const {
		return HTS_NAMESPACE::HTS_GL_NAMESPACE::exportTextureToFile(
				target(),
				CTexture::id(),
				path,
				frmt,
				type
		);
	}

}}

#endif /* EZGL_H_ */
