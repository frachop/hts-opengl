#include "common.h"


void glClip( GLdouble x, GLdouble y, GLdouble w, GLdouble h ) {
	const GLdouble eqn0[4] = { 1.0,  0.0, 0.0, -x };
	const GLdouble eqn1[4] = { 0.0,  1.0, 0.0, -y };
	const GLdouble eqn2[4] = {-1.0,  0.0, 0.0, x + w };
	const GLdouble eqn3[4] = { 0.0, -1.0, 0.0, y + h };
	glClipPlane (GL_CLIP_PLANE0, eqn0);
	glClipPlane (GL_CLIP_PLANE1, eqn1);	
	glClipPlane (GL_CLIP_PLANE2, eqn2);	
	glClipPlane (GL_CLIP_PLANE3, eqn3);
	glEnable (GL_CLIP_PLANE0); 
	glEnable (GL_CLIP_PLANE1); 
	glEnable (GL_CLIP_PLANE2); 
	glEnable (GL_CLIP_PLANE3);
}

/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/
void glOval( GLdouble x, GLdouble y, GLdouble small_radius, GLdouble big_radius ) {

	float angle, angleBase;
	GLfloat abscisse, ordonnee;
	int nbSegments = (int)std::max(small_radius, big_radius);
	angleBase = 2.0*M_PI / (float)nbSegments;
	
	for(int i=0; i<=nbSegments; i++)
	{
		angle = angleBase * i;
		
		abscisse = x + (GLfloat)(cos(angle)*small_radius);
		ordonnee = y + (GLfloat)(sin(angle)*big_radius);
			
		glVertex3f(abscisse,ordonnee,0.0);
	}

} 
/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/
//
namespace HTS_NAMESPACE {
namespace HTS_GL_NAMESPACE {

	const GLenum CAutoEnable::INVALID_CAP = (GLenum)-1;

	CAutoEnable::CAutoEnable( GLenum a, GLenum b, GLenum c, GLenum d, GLenum e, GLenum f, GLenum g, GLenum h, GLenum i )
	{
		if ( a != INVALID_CAP ) m_caps.push_back( a );
		if ( b != INVALID_CAP ) m_caps.push_back( b );
		if ( c != INVALID_CAP ) m_caps.push_back( c );
		if ( d != INVALID_CAP ) m_caps.push_back( d );
		if ( e != INVALID_CAP ) m_caps.push_back( e );
		if ( f != INVALID_CAP ) m_caps.push_back( f );
		if ( g != INVALID_CAP ) m_caps.push_back( g );
		if ( h != INVALID_CAP ) m_caps.push_back( h );
		if ( i != INVALID_CAP ) m_caps.push_back( i );

		for (CCapList::iterator it= m_caps.begin(); it != m_caps.end(); ++it) {
			(*it).enable(); CHECK_GLERROR("");
		}
	}

	CAutoEnable::CAutoEnable( bool bEnable, GLenum a, GLenum b, GLenum c, GLenum d, GLenum e, GLenum f, GLenum g, GLenum h, GLenum i )
	{
		if ( a != INVALID_CAP ) m_caps.push_back( a );
		if ( b != INVALID_CAP ) m_caps.push_back( b );
		if ( c != INVALID_CAP ) m_caps.push_back( c );
		if ( d != INVALID_CAP ) m_caps.push_back( d );
		if ( e != INVALID_CAP ) m_caps.push_back( e );
		if ( f != INVALID_CAP ) m_caps.push_back( f );
		if ( g != INVALID_CAP ) m_caps.push_back( g );
		if ( h != INVALID_CAP ) m_caps.push_back( h );
		if ( i != INVALID_CAP ) m_caps.push_back( i );

		for (CCapList::iterator it= m_caps.begin(); it != m_caps.end(); ++it) {
			if (bEnable) (*it).enable(); else (*it).disable(); CHECK_GLERROR("");
		}
	}
	
	CAutoEnable::~CAutoEnable() {
		for (CCapList::iterator it= m_caps.begin(); it != m_caps.end(); ++it) {
			( *it ).restore(); CHECK_GLERROR("");
		}
	}
	
	/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/
	
	CAutoMatrixIdentity::CAutoMatrixIdentity( int wViewport, int hViewport, bool bOrigineEnBas )
	{
		glMatrixMode( GL_MODELVIEW); glPushMatrix(); glLoadIdentity();
		glMatrixMode(GL_PROJECTION); glPushMatrix(); glLoadIdentity();
		if (bOrigineEnBas)
			glOrtho(0.0, GLdouble(wViewport), GLdouble(hViewport), 0.0, -1.0, 1.0);
		else
			glOrtho(0.0, GLdouble(wViewport), 0.0, GLdouble(hViewport), -1.0, 1.0);
		glViewport( 0, 0, wViewport, hViewport);
	}
	CAutoMatrixIdentity::~CAutoMatrixIdentity()
	{
		glMatrixMode( GL_MODELVIEW); glPopMatrix();
		glMatrixMode(GL_PROJECTION); glPopMatrix();
	}



}}





