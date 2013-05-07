namespace HTS_NAMESPACE {
namespace HTS_GL_NAMESPACE {

	//* ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	class CShader;
	class CShaders;

	//*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	class CShader
	{
		friend class CShaders;

	public:
		static std::string getDefaultVSource();
		static std::string getDefaultFSource() { return "void main(void) { gl_FragColor = gl_Color; }"; }

	public:
		CShader();
		virtual ~CShader();

	public:
		virtual bool create( const std::string & fSource= "", const std::string & vSource= "" );
		void destroy();
		bool isValid() const { return m_program; }
		GLuint program() const { return m_program; }

	public:
		bool use();
		virtual void unuse();
		GLint getParamLocation( const std::string & pName) const;

	public:
		bool setTexture(const std::string & pName, Texture texture, GLenum target, int idx = 0);
		bool setTexture(const std::string & pName, const CTexture & texture, int idx = 0) { return setTexture( pName, texture, texture.target(), idx); }
		template<typename T> bool set( const std::string & pName, const T & v) const;
		template<typename T> bool set( const std::string & pName, const T & v0, const T & v1) const;
		template<typename T> bool set( const std::string & pName, const T & v0, const T & v1, const T & v2) const;
		template<typename T> bool set( const std::string & pName, const T & v0, const T & v1, const T & v2, const T & v3) const;
		template<typename T> bool setArray( const std::string & pName, int count, const T * v0) const;

	private:
		GLuint m_fShader, m_vShader, m_program;
		std::map<GLint, GLenum> m_usedTextures;
	};

	//* ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	#define DECLARE_GLSHADER(className) public: static const char * getClassName() { return #className; }

	//* ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	class CShaders
	{
	public:
		CShaders();
		virtual ~CShaders();

	public:
		bool add( CShader* pShader, const std::string & name );
		bool exists( const std::string & name ) const;
		CShader * get(const std::string & name) const;
		CShader * operator[](const std::string & name) const { return get(name); }

	public:
		template<typename T>
		bool add( T * pShader ) { return add( pShader, T::getClassName() ); }

		template<typename T>
		bool exists() const { return exists( T::getClassName() ); }

		template<typename T>
		T* get() const { return dynamic_cast<T*>( get(T::getClassName()) ); }

		template<typename T>
		T* registerShader() { if (!exists<T>()) add( new T() ); return get<T>(); }

	private:
		std::map<std::string, CShader*> m_shaders;
	};

	//* ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}}

#include "glShaders.hpp"
