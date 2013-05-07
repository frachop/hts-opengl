#include "common.h"

#ifndef NDEBUG

namespace HTS_NAMESPACE {
namespace HTS_GL_NAMESPACE {

	/*! \brief méthode de detection des erreurs de OpenGL

		Cette fonction n'est définie que si NDEBUG n'est pas definie
	*/
	void checkGlError(const char * File, const int & line, const char * function, const std::string &  lib) {
		const GLenum error = glGetError();
		if (error ==  GL_NO_ERROR) return;
		std::cerr << File << ":" << line << ":" << function << " glERROR (" << lib << ") : " << gluErrorString(error) << std::endl;
// 		exit( -1 );
	}
}}

#endif


