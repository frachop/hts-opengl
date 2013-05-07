#include "common.h"
namespace HTS_NAMESPACE {
namespace HTS_GL_NAMESPACE {

	bool exportTextureToFile( GLenum target, GLint idTexture, const std::string & path, GLenum format, GLenum type )
	{
		GLint w(0),h(0);
		glBindTexture(target, idTexture);

		glGetTexLevelParameteriv(target,0, GL_TEXTURE_WIDTH, &w);
		CHECK_GLERROR("\n");

		glGetTexLevelParameteriv(target,0, GL_TEXTURE_HEIGHT, &h);
		CHECK_GLERROR("\n");

		size_t chanCount = 0;
		switch (format) {
			case GL_RED:
			case GL_GREEN:
			case GL_BLUE:
			case GL_ALPHA:
			case GL_LUMINANCE : chanCount = 1; break;

			case GL_RGB:
			case GL_BGR: chanCount = 3; break;

			case GL_RGBA:
			case GL_BGRA: chanCount = 4; break;

			case GL_LUMINANCE_ALPHA: chanCount = 2; break;
		};

		size_t bpp(0);
		switch (type) {
		case GL_UNSIGNED_BYTE:
		case GL_BYTE:
		case GL_UNSIGNED_BYTE_3_3_2:
		case GL_UNSIGNED_BYTE_2_3_3_REV:
			 bpp = 1; break;

		case GL_UNSIGNED_SHORT:
		case GL_SHORT:
		case GL_UNSIGNED_SHORT_5_6_5:
		case GL_UNSIGNED_SHORT_5_6_5_REV:
		case GL_UNSIGNED_SHORT_4_4_4_4:
		case GL_UNSIGNED_SHORT_4_4_4_4_REV:
		case GL_UNSIGNED_SHORT_5_5_5_1:
		case GL_UNSIGNED_SHORT_1_5_5_5_REV:
			bpp = 2; break;

		case GL_UNSIGNED_INT:
		case GL_INT:
			bpp = 4; break;

		case GL_FLOAT:
			bpp= sizeof(float); break;

		case GL_UNSIGNED_INT_8_8_8_8:
		case GL_UNSIGNED_INT_8_8_8_8_REV:
		case GL_UNSIGNED_INT_10_10_10_2:
		case GL_UNSIGNED_INT_2_10_10_10_REV:
			break;
		};

		size_t byteCount= bpp * chanCount * w * h;
		if (byteCount) {
			unsigned char * pPixels = new unsigned char[byteCount];
			glGetTexImage( target, 0, format, type, pPixels );

			FILE * pFile = fopen(path.c_str(), "wb" );
			if (pFile == 0)
				byteCount = 0;
			else {
				fwrite( pPixels, 1, byteCount, pFile );
				fclose( pFile);
			}

			delete[] pPixels;
		}

		glBindTexture(target, 0);

		return byteCount > 0;
	}

}}
