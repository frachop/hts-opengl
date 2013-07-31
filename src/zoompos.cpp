#include "common.h"
namespace HTS_NAMESPACE {
namespace HTS_GL_NAMESPACE {

	CZoomPos::CZoomPos()
	:	m_imgSize(1,1)
	,	m_canevaSize(1,1)
	,	m_center(0.f,0.f)
	,	m_zoom(1.f)
	,	m_zoomMin(1.f/16.f)
	,	m_zoomMax(16.f)
	,	m_zoomStep(1.1f)
	{
		buildMatrix();
	}

	CZoomPos::CZoomPos(const CZoomPos & src)
	:	m_imgSize       (src.m_imgSize       )
	,	m_canevaSize    (src.m_canevaSize    )
	,	m_center        (src.m_center        )
	,	m_zoom          (src.m_zoom          )
	,	m_zoomMin       (src.m_zoomMin       )
	,	m_zoomMax       (src.m_zoomMax       )
	,	m_zoomStep      (src.m_zoomStep      )
	,	m_matCanevaToImg(src.m_matCanevaToImg)
	,	m_matImgToCaneva(src.m_matImgToCaneva)
	{

	}

	CZoomPos& CZoomPos::operator=(const CZoomPos & src)
	{
		if (this != &src) {
			m_imgSize       = src.m_imgSize       ;
			m_canevaSize    = src.m_canevaSize    ;
			m_center        = src.m_center        ;
			m_zoom          = src.m_zoom          ;
			m_zoomMin       = src.m_zoomMin       ;
			m_zoomMax       = src.m_zoomMax       ;
			m_zoomStep      = src.m_zoomStep      ;
			m_matCanevaToImg= src.m_matCanevaToImg;
			m_matImgToCaneva= src.m_matImgToCaneva;
		}
		return (*this);

	}

	void CZoomPos::setImgSize(const CSizei & sz)
	{
		if (sz == m_imgSize) return;
		m_imgSize = sz;
		buildMatrix();
	}
	void CZoomPos::setCanevaSize(const CSizei & sz)
	{
		if (m_canevaSize == sz) return;
		m_canevaSize = sz;
		buildMatrix();
	}

	bool CZoomPos::setZoom(float z)
	{
		z = std::max( m_zoomMin, std::min(m_zoomMax, z));
		if (z == m_zoom) return false;
		m_zoom = z;
		buildMatrix();
		return true;
	}

	bool CZoomPos::setZoomAuto() {

		const float wSrc = float( m_imgSize.cx );
		const float hSrc = float( m_imgSize.cy );
		const float wDst = float( m_canevaSize.cx );
		const float hDst = float( m_canevaSize.cy );
		if ((wSrc <= 0.f) || (hSrc <= 0.f))
			return false;

		float z = wDst / wSrc;
		if ((z * hSrc) > hDst)
			z = hDst / hSrc;

		return setZoom( z );
	}

	void CZoomPos::setZoomRange( float zMin, float zMax)
	{
		if (zMin > zMax)
			std::swap(zMin, zMax);

		m_zoomMin = std::max( std::numeric_limits<float>::epsilon(), zMin );
		m_zoomMax = std::max( m_zoomMin, zMax );
		float z = m_zoom;
		if (z < m_zoomMin) z = m_zoomMin;
		if (z > m_zoomMax) z = m_zoomMax;
		if (z == m_zoom)
			return;

		m_zoom = z;
		buildMatrix();
	}

	float CZoomPos::setZoomStep( float zStep)
	{
		float result = m_zoomStep;
		m_zoomStep = std::max( std::numeric_limits<float>::epsilon(), zStep );
		return result;
	}

	bool CZoomPos::incZoom(bool bInc)
	{
		return setZoom( (bInc) ? (getZoom() * m_zoomStep) : getZoom() / m_zoomStep );
	}

	void CZoomPos::setCenter( const CPointf & p )
	{
		if (p == m_center)
			return;
		m_center = p;
		buildMatrix();
	}

	CPointf CZoomPos::canevaToImg(const CPointf &pt) const
	{
		const CVector3f v(m_matCanevaToImg * CVector3f( pt.x , pt.y, 1.f));
		return CPointf( v[0], v[1] );
	}
	CPointf CZoomPos::imgToCaneva(const CPointf &pt) const
	{
		const CVector3f v(m_matImgToCaneva * CVector3f( pt.x, pt.y, 1.f));
		return CPointf( v[0], v[1] );
	}

	CRectf CZoomPos::canevaToImg(const CRectf &r) const
	{
		return CRectf( canevaToImg(r.pos()), unzoomed(r.size()) );
	}
	CRectf CZoomPos::imgToCaneva(const CRectf &r) const
	{
		return CRectf( imgToCaneva(r.pos()), zoomed(r.size()) );
	}


	void CZoomPos::buildMatrix()
	{
		m_matImgToCaneva = m_matCanevaToImg = CMatrix3f::identity();

		const CSizef t2 ( getTranslation2() );
		const CSizef s1 ( getScale1() );
		const CSizef t0 ( getTranslation0() );

	//	TRACEFN("t2(%.2f,%.2f)\n", t2.cx, t2.cy);
	//	TRACEFN("s1(%.2f,%.2f)\n", s1.cx, s1.cy);
	//	TRACEFN("t0(%.2f,%.2f)\n", t0.cx, t0.cy);

		m_matImgToCaneva = CMatrix3f::identity()
			* CMatrix3f::translation( CVector2f(t2.cx, t2.cy) )
			* CMatrix3f::scaling    ( CVector2f(s1.cx, s1.cy) )
			* CMatrix3f::translation( CVector2f(t0.cx, t0.cy) );

		m_matImgToCaneva.inverse(m_matCanevaToImg);
	}

	void CZoomPos::setupGL(GLenum matrixMode, bool bPushMatrix )
	{
		const CSizef t2 ( getTranslation2() );
		const CSizef s1 ( getScale1      () );
		const CSizef t0 ( getTranslation0() );

		glMatrixMode( matrixMode );
		if (bPushMatrix)
			glPushMatrix();

		glLoadIdentity();
		glTranslatef ( t2.cx, t2.cy, 0.f );
		glScalef     ( s1.cx, s1.cy, 1.f );
		glTranslatef ( t0.cx, t0.cy, 0.f );
	}

}}
