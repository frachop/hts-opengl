#include "common.h"

//* ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static std::string compile( GLuint shader, const std::string & src)
{
	const char * pSrc= src.c_str();
	glShaderSource(shader, 1, &pSrc, NULL);
	glCompileShader(shader);
	GLint compile_status = GL_TRUE;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compile_status);
	if(compile_status == GL_TRUE)
		return std::string("");

	/* on recupere la taille du message d'erreur */
	GLsizei logsize = 0;
	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logsize);

	/* on alloue un espace memoire dans lequel OpenGL ecrira le message */
	char* log = static_cast<char*>( malloc(1 + logsize) );
	if(log == NULL)
		return std::string("impossible d'allouer de la memoire !\n");

	/* initialisation du contenu */
	bzero(log, logsize + 1);
	glGetShaderInfoLog(shader, logsize, &logsize, log);
	std::string res(log);

	free(log);
	return res;
}

static std::string link( GLuint prg, GLuint vShader, GLuint fShader)
{
	glAttachShader(prg, vShader);
	glAttachShader(prg, fShader);
	glLinkProgram(prg);

	GLint status = GL_TRUE;
	glGetProgramiv(prg, GL_LINK_STATUS, &status);
	if(status == GL_TRUE)
		return std::string("");

	/* on recupere la taille du message d'erreur */
	GLsizei logsize = 0;
	glGetProgramiv(prg, GL_INFO_LOG_LENGTH, &logsize);

	/* on alloue un espace memoire dans lequel OpenGL ecrira le message */
	char* log = static_cast<char*>( malloc(1 + logsize) );
	if(log == NULL)
		return std::string("impossible d'allouer de la memoire !\n");

	/* initialisation du contenu */
	bzero(log, logsize + 1);
	glGetProgramInfoLog(prg, logsize, &logsize, log);
	std::string res(log);

	free(log);
	return res;
}

//* ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace HTS_NAMESPACE {
namespace HTS_GL_NAMESPACE {




	std::string CShader::getDefaultVSource()
	{
		return ""
				"void main(void) {"
				"   gl_FrontColor = gl_Color;"
				"   gl_Position   = gl_ModelViewProjectionMatrix * gl_Vertex;"
				"   gl_TexCoord[0] = gl_MultiTexCoord0;"
				"   gl_TexCoord[1] = gl_MultiTexCoord1;"
				"}";
	}


	//* ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	CShader::CShader()
	:	m_fShader(0), m_vShader(0), m_program(0)
	{

	}

	void CShader::destroy()
	{
		if (m_fShader) glDeleteShader (m_fShader);
		if (m_vShader) glDeleteShader (m_vShader);
		if (m_program) glDeleteProgram(m_program);
		m_fShader= m_vShader= m_program =0;
	}

	CShader::~CShader()
	{
		destroy();
	}

	bool CShader::create( const std::string & fSource, const std::string & vSource )
	{
		if (m_program)
			return true;

		destroy();

		std::string res;
		m_vShader = glCreateShader(GL_VERTEX_SHADER  );
		m_fShader = glCreateShader(GL_FRAGMENT_SHADER);
		if ((m_vShader == 0) || (m_fShader == 0)) {
			std::cerr << __PRETTY_FUNCTION__ << " : can't create shader" << std::endl;
			return false;
		}

		res = compile( m_vShader, (vSource.empty() ? getDefaultVSource() : vSource));
		if (!res.empty()) {
			destroy();
			std::cerr << __PRETTY_FUNCTION__ << " : vertex compilation error : " << res << std::endl;
			return false;
		}

		res = compile( m_fShader, (fSource.empty() ? getDefaultFSource() : fSource));
		if (!res.empty()) {
			destroy();
			std::cerr << __PRETTY_FUNCTION__<< " : fragment compilation error : " << res << std::endl;
			return false;
		}

		m_program = glCreateProgram();
		if (m_program == 0) {
			destroy();
			std::cerr << __PRETTY_FUNCTION__ << " : can't create program" << std::endl;
			return false;
		}

		res = link( m_program, m_vShader, m_fShader);
		if (!res.empty()) {
			destroy();
			std::cerr << "link error : " << res << std::endl;
			return false;
		}

		return true;
	}


	bool CShader::use()
	{
		if (!isValid())
			if (!create())
				return false;

		glUseProgram( m_program );
		CHECK_GLERROR("");
		return true;
	}

	void CShader::unuse()
	{
		glUseProgram(0);

		for (std::map<GLint, GLenum>::const_iterator it= m_usedTextures.begin(); it != m_usedTextures.end(); ++it) {
			glActiveTexture(it->first);
			glBindTexture(it->second, 0);
		}

		m_usedTextures.clear();
		glActiveTexture(GL_TEXTURE0 + 0);
	}

	bool CShader::setTexture(const std::string & pName, Texture texture, GLenum target, int idx)
	{
		if (!isValid()) return false;
		GLint iImg= glGetUniformLocation(m_program,	static_cast<const GLchar *>(pName.c_str())); CHECK_GLERROR("");
		if (iImg < 0) return false;

		glActiveTexture(static_cast<GLenum>(GL_TEXTURE0 + idx));
		CHECK_GLERROR("");
		glBindTexture( target, texture);
		CHECK_GLERROR("");
		glUniform1i(iImg, idx);
		CHECK_GLERROR("");

		m_usedTextures.insert(std::map<GLint, GLenum>::value_type( GL_TEXTURE0 + idx, target ));

		return true;
	}

}}
