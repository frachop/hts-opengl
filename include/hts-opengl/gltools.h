
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <typename T> void glVertex(const T & x, const T & y, const T & z);
template <typename T> void glVertex(const T & x, const T & y);
template <typename T> void glVertex(const T * p);

template <> inline void glVertex(const GLdouble & x, const GLdouble & y, const GLdouble & z) { glVertex3d(x,y,z); }
template <> inline void glVertex(const GLdouble & x, const GLdouble & y) { glVertex2d(x,y); }
template <> inline void glVertex(const GLdouble * p) { glVertex2dv(p); }

template <> inline void glVertex(const GLfloat & x, const GLfloat & y, const GLfloat & z) { glVertex3f(x,y,z); }
template <> inline void glVertex(const GLfloat & x, const GLfloat & y) { glVertex2f(x,y); }
template <> inline void glVertex(const GLfloat * p) { glVertex2fv(p); }

template <> inline void glVertex(const GLint & x, const GLint & y, const GLint & z) { glVertex3i(x,y,z); }
template <> inline void glVertex(const GLint & x, const GLint & y) { glVertex2i(x,y); }
template <> inline void glVertex(const GLint * p) { glVertex2iv(p); }

template <> inline void glVertex(const GLshort & x, const GLshort & y, const GLshort & z) { glVertex3s(x,y,z); }
template <> inline void glVertex(const GLshort & x, const GLshort & y) { glVertex2s(x,y); }
template <> inline void glVertex(const GLshort * p) { glVertex2sv(p); }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <typename T> void glColor(const T & r, const T & g, const T & b, const T & a);
template <typename T> void glColor(const T & r, const T & g, const T & b);
template <typename T> void glColor(const T * p);

template <> inline void glColor(const GLdouble & r, const GLdouble & g, const GLdouble & b, const GLdouble & a) { glColor4d(r,g,b,a); }
template <> inline void glColor(const GLdouble & r, const GLdouble & g, const GLdouble & b) { glColor3d(r,g,b); }
template <> inline void glColor(const GLdouble * p) { glColor4dv(p); }

template <> inline void glColor(const GLfloat & r, const GLfloat & g, const GLfloat & b, const GLfloat & a) { glColor4f(r,g,b,a); }
template <> inline void glColor(const GLfloat & r, const GLfloat & g, const GLfloat & b) { glColor3f(r,g,b); }
template <> inline void glColor(const GLfloat * p) { glColor4fv(p); }

template <> inline void glColor(const GLint & r, const GLint & g, const GLint & b, const GLint & a) { glColor4i(r,g,b,a); }
template <> inline void glColor(const GLint & r, const GLint & g, const GLint & b) { glColor3i(r,g,b); }
template <> inline void glColor(const GLint * p) { glColor4iv(p); }

template <> inline void glColor(const GLuint & r, const GLuint & g, const GLuint & b, const GLuint & a) { glColor4ui(r,g,b,a); }
template <> inline void glColor(const GLuint & r, const GLuint & g, const GLuint & b) { glColor3ui(r,g,b); }
template <> inline void glColor(const GLuint * p) { glColor4uiv(p); }

template <> inline void glColor(const GLshort & r, const GLshort & g, const GLshort & b, const GLshort & a) { glColor4s(r,g,b,a); }
template <> inline void glColor(const GLshort & r, const GLshort & g, const GLshort & b) { glColor3s(r,g,b); }
template <> inline void glColor(const GLshort * p) { glColor4sv(p); }

template <> inline void glColor(const GLushort & r, const GLushort & g, const GLushort & b, const GLushort & a) { glColor4us(r,g,b,a); }
template <> inline void glColor(const GLushort & r, const GLushort & g, const GLushort & b) { glColor3us(r,g,b); }
template <> inline void glColor(const GLushort * p) { glColor4usv(p); }

template <> inline void glColor(const GLbyte & r, const GLbyte & g, const GLbyte & b, const GLbyte & a) { glColor4b(r,g,b,a); }
template <> inline void glColor(const GLbyte & r, const GLbyte & g, const GLbyte & b) { glColor3b(r,g,b); }
template <> inline void glColor(const GLbyte * p) { glColor4bv(p); }

template <> inline void glColor(const GLubyte & r, const GLubyte & g, const GLubyte & b, const GLubyte & a) { glColor4ub(r,g,b,a); }
template <> inline void glColor(const GLubyte & r, const GLubyte & g, const GLubyte & b) { glColor3ub(r,g,b); }
template <> inline void glColor(const GLubyte * p) { glColor4ubv(p); }

template <typename T> inline void glColor(const hts::CTColor<T> & c) { glColor(c.r, c.g, c.b, c.a); }

// GLRECT //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline void glRect(const HTS_NAMESPACE::CRecti & r) { ::glRecti(r.x, r.y, r.x+r.w, r.y+r.h ); }
inline void glRect(const HTS_NAMESPACE::CRectf & r) { ::glRectf(r.x, r.y, r.x+r.w, r.y+r.h ); }
inline void glRect(const HTS_NAMESPACE::CRectd & r) { ::glRectd(r.x, r.y, r.x+r.w, r.y+r.h ); }

inline void glRect(const HTS_NAMESPACE::CPointi & p, const HTS_NAMESPACE::CSizei & s) { ::glRecti(p.x, p.y, p.x+s.cx, p.y+s.cy ); }
inline void glRect(const HTS_NAMESPACE::CPointf & p, const HTS_NAMESPACE::CSizef & s) { ::glRectf(p.x, p.y, p.x+s.cx, p.y+s.cy ); }
inline void glRect(const HTS_NAMESPACE::CPointf & p, const HTS_NAMESPACE::CSized & s) { ::glRectd(p.x, p.y, p.x+s.cx, p.y+s.cy ); }

//- /////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace HTS_NAMESPACE {
namespace HTS_GL_NAMESPACE {

	bool exportTextureToFile( GLenum target, GLint idTexture, const std::string & path, GLenum format= GL_RGBA, GLenum type= GL_UNSIGNED_BYTE );

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	class CAutoBeginEnd {
	public:
		CAutoBeginEnd(GLenum mode) { glBegin(mode); }
		~CAutoBeginEnd() { glEnd(); }
	};

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	class CAutoColor {
	public:
		CAutoColor(const CColorb & color) { save(); glColor(color); }
		CAutoColor(const CColori & color) { save(); glColor(color); }
		CAutoColor(const CColorf & color) { save(); glColor(color); }
		CAutoColor(const CColord & color) { save(); glColor(color); }
		virtual ~CAutoColor() { restore(); }

	private:
		GLdouble m_saved[4];
		void save() { glGetDoublev(GL_CURRENT_COLOR, m_saved); }
		void restore() { glColor4dv( m_saved ); }
	};

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	class CAutoEnable {
	public:
		static const GLenum INVALID_CAP;

	public:
		CAutoEnable( GLenum a
				,	GLenum b = INVALID_CAP
				,	GLenum c = INVALID_CAP
				,	GLenum d = INVALID_CAP
				,	GLenum e = INVALID_CAP
				,	GLenum f = INVALID_CAP
				,	GLenum g = INVALID_CAP
				,	GLenum h = INVALID_CAP
				,	GLenum i = INVALID_CAP );


		CAutoEnable( bool bEnable, GLenum a
				,	GLenum b = INVALID_CAP
				,	GLenum c = INVALID_CAP
				,	GLenum d = INVALID_CAP
				,	GLenum e = INVALID_CAP
				,	GLenum f = INVALID_CAP
				,	GLenum g = INVALID_CAP
				,	GLenum h = INVALID_CAP
				,	GLenum i = INVALID_CAP );

		virtual ~CAutoEnable();

	protected:
		class CItem {
		public:
			GLboolean m_wasEnabled;
			GLenum    m_enum;
			CItem(GLenum _enum) : m_wasEnabled( glIsEnabled(_enum) ), m_enum(_enum) {}
			void enable( ) { glEnable( m_enum); }
			void disable( ) { glDisable( m_enum); }
			void restore( ) { if (m_wasEnabled) glEnable( m_enum); else glDisable( m_enum); }
		};

		typedef std::list<CItem> CCapList;
		CCapList m_caps;
	};

}}

//- /////////////////////////////////////////////////////////////////////////////////////////////////////////


template<class COLOR> inline void glRect(const HTS_NAMESPACE::CRecti & r, const COLOR & color) { HTS_NAMESPACE::HTS_GL_NAMESPACE::CAutoColor c(color); glRect(r); }
template<class COLOR> inline void glRect(const HTS_NAMESPACE::CRectf & r, const COLOR & color) { HTS_NAMESPACE::HTS_GL_NAMESPACE::CAutoColor c(color); glRect(r); }
template<class COLOR> inline void glRect(const HTS_NAMESPACE::CRectd & r, const COLOR & color) { HTS_NAMESPACE::HTS_GL_NAMESPACE::CAutoColor c(color); glRect(r); }

template<class COLOR> inline void glRect(const HTS_NAMESPACE::CPointi & p, const HTS_NAMESPACE::CSizei & s, const COLOR & color) { HTS_NAMESPACE::HTS_GL_NAMESPACE::CAutoColor c(color); glRect(p, s); }
template<class COLOR> inline void glRect(const HTS_NAMESPACE::CPointf & p, const HTS_NAMESPACE::CSizef & s, const COLOR & color) { HTS_NAMESPACE::HTS_GL_NAMESPACE::CAutoColor c(color); glRect(p, s); }
template<class COLOR> inline void glRect(const HTS_NAMESPACE::CPointf & p, const HTS_NAMESPACE::CSized & s, const COLOR & color) { HTS_NAMESPACE::HTS_GL_NAMESPACE::CAutoColor c(color); glRect(p, s); }

// GLFRAMERECT /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline void glFrameRect(const HTS_NAMESPACE::CRecti & r) { glBegin( (GLenum)GL_LINE_LOOP ); glVertex2i(r.x,r.y); glVertex2i( r.x+r.w, r.y); glVertex2i( r.x+r.w, r.y+r.h); glVertex2i(r.x, r.y+r.h); glEnd(); }
inline void glFrameRect(const HTS_NAMESPACE::CRectf & r) { glBegin( (GLenum)GL_LINE_LOOP ); glVertex2f(r.x,r.y); glVertex2f( r.x+r.w, r.y); glVertex2f( r.x+r.w, r.y+r.h); glVertex2f(r.x, r.y+r.h); glEnd(); }
inline void glFrameRect(const HTS_NAMESPACE::CRectd & r) { glBegin( (GLenum)GL_LINE_LOOP ); glVertex2d(r.x,r.y); glVertex2d( r.x+r.w, r.y); glVertex2d( r.x+r.w, r.y+r.h); glVertex2d(r.x, r.y+r.h); glEnd(); }

inline void glFrameRect(const HTS_NAMESPACE::CPointi & p, const HTS_NAMESPACE::CSizei & s) { glFrameRect(HTS_NAMESPACE::CRecti(p, s)); }
inline void glFrameRect(const HTS_NAMESPACE::CPointf & p, const HTS_NAMESPACE::CSizef & s) { glFrameRect(HTS_NAMESPACE::CRectf(p, s)); }
inline void glFrameRect(const HTS_NAMESPACE::CPointf & p, const HTS_NAMESPACE::CSized & s) { glFrameRect(HTS_NAMESPACE::CRectd(p, s)); }

void glFrameRect(const HTS_NAMESPACE::CRecti & r, double lineWidth);
void glFrameRect(const HTS_NAMESPACE::CRectf & r, double lineWidth);
void glFrameRect(const HTS_NAMESPACE::CRectd & r, double lineWidth);

template<class COLOR> inline void glFrameRect(const HTS_NAMESPACE::CRecti & r, const COLOR & color, bool bSmooth=true) { using namespace HTS_NAMESPACE::HTS_GL_NAMESPACE; CAutoColor c(color); CAutoEnable s(bSmooth, GL_LINE_SMOOTH); glFrameRect(r); }
template<class COLOR> inline void glFrameRect(const HTS_NAMESPACE::CRectf & r, const COLOR & color, bool bSmooth=true) { using namespace HTS_NAMESPACE::HTS_GL_NAMESPACE; CAutoColor c(color); CAutoEnable s(bSmooth, GL_LINE_SMOOTH); glFrameRect(r); }
template<class COLOR> inline void glFrameRect(const HTS_NAMESPACE::CRectd & r, const COLOR & color, bool bSmooth=true) { using namespace HTS_NAMESPACE::HTS_GL_NAMESPACE; CAutoColor c(color); CAutoEnable s(bSmooth, GL_LINE_SMOOTH); glFrameRect(r); }

template<class COLOR> inline void glFrameRect(const HTS_NAMESPACE::CRecti & r, double lineWidth, const COLOR & color, bool bSmooth=true) { using namespace HTS_NAMESPACE::HTS_GL_NAMESPACE; CAutoColor c(color); CAutoEnable s(bSmooth, GL_LINE_SMOOTH); glFrameRect(r,lineWidth); }
template<class COLOR> inline void glFrameRect(const HTS_NAMESPACE::CRectf & r, double lineWidth, const COLOR & color, bool bSmooth=true) { using namespace HTS_NAMESPACE::HTS_GL_NAMESPACE; CAutoColor c(color); CAutoEnable s(bSmooth, GL_LINE_SMOOTH); glFrameRect(r,lineWidth); }
template<class COLOR> inline void glFrameRect(const HTS_NAMESPACE::CRectd & r, double lineWidth, const COLOR & color, bool bSmooth=true) { using namespace HTS_NAMESPACE::HTS_GL_NAMESPACE; CAutoColor c(color); CAutoEnable s(bSmooth, GL_LINE_SMOOTH); glFrameRect(r,lineWidth); }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void glClip( GLdouble x, GLdouble y, GLdouble w, GLdouble h);
inline void glClip( const HTS_NAMESPACE::CRecti & r ) { glClip( r.x, r.y, r.w, r.h ); }
inline void glClip( const HTS_NAMESPACE::CRectf & r ) { glClip( r.x, r.y, r.w, r.h ); }
inline void glClip( const HTS_NAMESPACE::CRectd & r ) { glClip( r.x, r.y, r.w, r.h ); }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void glOval( GLdouble x, GLdouble y, GLdouble small_radius, GLdouble big_radius );
inline void glOval( const HTS_NAMESPACE::CRecti & r ) { glOval( ( r.x + r.w/2.0 ), ( r.y + r.h/2.0 ), r.w/2.0, r.h/2.0 ); }
inline void glOval( const HTS_NAMESPACE::CRectf & r ) { glOval( ( r.x + r.w/2.0 ), ( r.y + r.h/2.0 ), r.w/2.0, r.h/2.0 ); }
inline void glOval( const HTS_NAMESPACE::CRectd & r ) { glOval( ( r.x + r.w/2.0 ), ( r.y + r.h/2.0 ), r.w/2.0, r.h/2.0 ); }

//- /////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace HTS_NAMESPACE {
namespace HTS_GL_NAMESPACE {


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	class CAutoMatrixIdentity {
	public:
		CAutoMatrixIdentity( int wViewport, int hViewport, bool bOrigineEnBas = true );
		~CAutoMatrixIdentity();
	};

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	class CAutoBlendFunc
	{
	public:
		CAutoBlendFunc(GLenum sfactor = GL_SRC_ALPHA, GLenum dfactor= GL_ONE_MINUS_SRC_ALPHA)
		:	m_autoEnable( GL_BLEND )
		{
			glGetIntegerv(GL_BLEND_SRC, &m_savedSFactor);
			glGetIntegerv(GL_BLEND_DST, &m_savedDFactor);
			glBlendFunc(sfactor, dfactor);
		}

		~CAutoBlendFunc() {
			glBlendFunc(m_savedSFactor, m_savedDFactor);
		}

	private:
		CAutoEnable m_autoEnable  ;
		GLint       m_savedSFactor;
		GLint       m_savedDFactor;
	};

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	class CAutoClipRect {
	public:
		CAutoClipRect(const CRecti & r) { glPushAttrib(GL_TRANSFORM_BIT); glClip( r ); }
		CAutoClipRect(const CRectf & r) { glPushAttrib(GL_TRANSFORM_BIT); glClip( r ); }
		CAutoClipRect(const CRectd & r) { glPushAttrib(GL_TRANSFORM_BIT); glClip( r ); }
		CAutoClipRect(GLdouble x, GLdouble y, GLdouble w, GLdouble h) { glPushAttrib(GL_TRANSFORM_BIT); glClip( x,y,w,h ); }
		~CAutoClipRect() { glPopAttrib(); }
	};

	
	// INLINES /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	template<typename RECT_TYPE, typename COLOR_TYPE>
	class CTFrameRect {
	public:
		CTFrameRect(const CTRect<RECT_TYPE>& r, const CTSize<RECT_TYPE> & epais, const CTColor<COLOR_TYPE> & cExterieur, const CTColor<COLOR_TYPE> & cInterieur);
		CTFrameRect(const CTRect<RECT_TYPE>& r, const CTSize<RECT_TYPE> & epais, const CTColor<COLOR_TYPE> & color);
		void frame();

	private:
		void setEpaisseur( const CSized & sz, const CSized & e);

	private:
		CVector2d m_pExt0;
		CVector2d m_pExt1;
		CVector2d m_pInt0;
		CVector2d m_pInt1;
		CColord   m_colorExt;
		CColord   m_colorInt;
	};
	
	// CGLLineWidthAuto /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	#define CGLAutoLineWidth CGLLineWidthAuto
	class CGLLineWidthAuto {
	public:
		CGLLineWidthAuto( double e ) { glGetDoublev((GLenum)GL_LINE_WIDTH, &m_saved); glLineWidth(e); }
		virtual ~CGLLineWidthAuto() { glLineWidth(m_saved); }

	private:
		double m_saved;
	};
	
	// INLINES /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	inline void glFrameRect(const HTS_NAMESPACE::CRecti & r, double lineWidth) {
		double o; glGetDoublev(	(GLenum)GL_LINE_WIDTH, &o);
		glLineWidth(lineWidth);
		::glFrameRect(r);
		glLineWidth(o);
	}

	inline void glFrameRect(const HTS_NAMESPACE::CRectf & r, double lineWidth) {
		double o; glGetDoublev(	(GLenum)GL_LINE_WIDTH, &o);
		glLineWidth(lineWidth);
		::glFrameRect(r);
		glLineWidth(o);
	}

	inline void glFrameRect(const HTS_NAMESPACE::CRectd & r, double lineWidth) {
		double o; glGetDoublev(	(GLenum)GL_LINE_WIDTH, &o);
		glLineWidth(lineWidth);
		::glFrameRect(r);
		glLineWidth(o);
	}


	/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/
	
	
	template<typename RECT_TYPE, typename COLOR_TYPE>
	CTFrameRect<RECT_TYPE,COLOR_TYPE>::CTFrameRect(const CTRect<RECT_TYPE>& r, const CTSize<RECT_TYPE> & epais, const CTColor<COLOR_TYPE> & cExterieur, const CTColor<COLOR_TYPE> & cInterieur)
	:	m_pExt0( (double)r.x , (double)r.y )
	,	m_pExt1( (double)r.x + (double)r.w, (double)r.y + (double)r.h )
	,	m_colorExt( (double)cExterieur.r, (double)cExterieur.g, (double)cExterieur.b, (double)cExterieur.a )
	,	m_colorInt( (double)cInterieur.r, (double)cInterieur.g, (double)cInterieur.b, (double)cInterieur.a )
	{
		setEpaisseur( CSized((double)r.w,(double)r.h), CSized((double)epais.cx, (double)epais.cy) );
	}
	
	template<typename RECT_TYPE, typename COLOR_TYPE>
	CTFrameRect<RECT_TYPE,COLOR_TYPE>::CTFrameRect(const CTRect<RECT_TYPE>& r, const CTSize<RECT_TYPE> & epais, const CTColor<COLOR_TYPE> & color)
	:	m_pExt0( (double)r.x , (double)r.y )
	,	m_pExt1( (double)r.x + (double)r.w, (double)r.y + (double)r.h )
	,	m_colorExt( (double)color.r, (double)color.g, (double)color.b, (double)color.a )
	,	m_colorInt( m_colorExt )
	{
		setEpaisseur( CSized((double)r.w,(double)r.h), CSized((double)epais.cx, (double)epais.cy) );
	}
	
	template<typename RECT_TYPE, typename COLOR_TYPE>
	void CTFrameRect<RECT_TYPE,COLOR_TYPE>::setEpaisseur( const CSized & sz, const CSized & epais) {
		const CSized e(
			std::min(epais.cx, 0.5 * sz.cx),
			std::min(epais.cy, 0.5 * sz.cy)
		);

		m_pInt0 = CVector2d( m_pExt0[0] + e.cx, m_pExt0[1] + e.cy);
		m_pInt1 = CVector2d( m_pExt1[0] - e.cx, m_pExt1[1] - e.cy);
	}
	
	template<typename RECT_TYPE, typename COLOR_TYPE>
	void CTFrameRect<RECT_TYPE,COLOR_TYPE>::frame() {
	
		// pour sauver la couleur courante
		CAutoColor c(m_colorInt);

	/*
		pExt0
		1/9                     3
		 +---------------------+
		 |\  pInt0           / |
		 |  +---------------+  |
		 |  |0/8           2|  |
		 |  |6       pInt1 4|  |
		 |  +---------------+  |
		 | /                 \ |
		 +---------------------+ pExt1
		7                       5

	*/

		glBegin( (GLenum)GL_QUAD_STRIP );
			/* 0 */ glColor(m_colorInt); glVertex2d( m_pInt0[0], m_pInt0[1] );
			/* 1 */ glColor(m_colorExt); glVertex2d( m_pExt0[0], m_pExt0[1] );
			/* 2 */ glColor(m_colorInt); glVertex2d( m_pInt1[0], m_pInt0[1] );
			/* 3 */ glColor(m_colorExt); glVertex2d( m_pExt1[0], m_pExt0[1] );
			/* 4 */ glColor(m_colorInt); glVertex2d( m_pInt1[0], m_pInt1[1] );
			/* 5 */ glColor(m_colorExt); glVertex2d( m_pExt1[0], m_pExt1[1] );
			/* 6 */ glColor(m_colorInt); glVertex2d( m_pInt0[0], m_pInt1[1] );
			/* 7 */ glColor(m_colorExt); glVertex2d( m_pExt0[0], m_pExt1[1] );
			/* 8 */ glColor(m_colorInt); glVertex2d( m_pInt0[0], m_pInt0[1] );
			/* 9 */ glColor(m_colorExt); glVertex2d( m_pExt0[0], m_pExt0[1] );
		glEnd();

	}


}}
