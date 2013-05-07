
/*////////////////////////////////////////////////////////////////////////////////////////////*/
// Check GL  Errors

#ifdef NDEBUG

#	define CHECK_GLERROR(d)

#else

namespace HTS_NAMESPACE {
namespace HTS_GL_NAMESPACE {
	void checkGlError(const char * File, const int & line, const char * function, const std::string & lib);
}}
#	define CHECK_GLERROR(lib) HTS_NAMESPACE::HTS_GL_NAMESPACE::checkGlError(__FILE__, __LINE__, __PRETTY_FUNCTION__, lib)


# endif

