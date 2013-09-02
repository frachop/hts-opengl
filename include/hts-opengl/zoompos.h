//*////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace HTS_NAMESPACE {
namespace HTS_GL_NAMESPACE {

	class CZoomPos {
	public:
		CZoomPos();
		CZoomPos(const CZoomPos & src);
		CZoomPos& operator=(const CZoomPos & src);
		bool operator==(const CZoomPos & src) const;

	public:
		CSizei  getImgSize() const { return m_imgSize; }
		CSizei  getCanevaSize() const { return m_canevaSize; }
		CPointf getCenter() const { return m_center; }

	public:
		void setImgSize(const CSizei & sz);
		void setCanevaSize(const CSizei & sz);
		void setCenter( const CPointf & p );
		void setCenter( const CPointi & p ) { setCenter( CPointf(float(p.x), float(p.y)) ); }

	public:
		float getZoom  () const { return m_zoom  ; }
		bool setZoom(float z); // retourne false si zoom inchange
		bool setZoomAuto(); // retourne false si zoom inchange
		bool incZoom(bool bInc); // retourne false si zoom inchange
		void setZoomRange( float zMin, float zMax);
		float setZoomStep( float zStep); // retourne le precedent
		float getZoomMin () const { return m_zoomMin; }
		float getZoomMax () const { return m_zoomMax; }
		float getZoomStep() const { return m_zoomStep; }

	public:
		CPointf canevaToImg(const CPointf &pt) const;
		CPointf imgToCaneva(const CPointf &pt) const;
		CPointi canevaToImg(const CPointi &pt) const { const CPointf p( canevaToImg(CPointf(pt)) ); return CPointi(int(round(p.x)),int(round(p.y))); }
		CPointi imgToCaneva(const CPointi &pt) const { const CPointf p( imgToCaneva(CPointf(pt)) ); return CPointi(int(round(p.x)),int(round(p.y))); }
		CSizef zoomed(const CSizef &sz) const { return m_zoom*sz; }
		CSizef unzoomed(const CSizef &sz) const { return (1.0f/m_zoom)*sz; }
		CSizei zoomed(const CSizei &sz) const { return CSizei( int(round( m_zoom*float(sz.cx) )), int(round(m_zoom*float(sz.cy) ) )); }
		CSizei unzoomed(const CSizei &sz) const { return CSizei( int(round( (1.f/m_zoom)*float(sz.cx) )), int(round((1.f/m_zoom)*float(sz.cy) ) )); }
		CRectf canevaToImg(const CRectf &r) const;
		CRectf imgToCaneva(const CRectf &r) const;
		CRecti canevaToImg(const CRecti &r) const { return CRecti( canevaToImg(r.pos()), unzoomed(r.size()) ); }
		CRecti imgToCaneva(const CRecti &r) const { return CRecti( imgToCaneva(r.pos()),   zoomed(r.size()) ); }

	public:
		CSizef getTranslation0() const { return CSizef( -0.5f * float(m_imgSize.cx) + m_center.x,  -0.5f * float(m_imgSize.cy) + m_center.y); }
		CSizef getScale1() const { return CSizef( m_zoom, m_zoom); }
		CSizef getTranslation2() const { return CSizef( 0.5f * float(m_canevaSize.cx),  0.5f * float(m_canevaSize.cy)); }
		void setupGL(GLenum matrixMode = GL_MODELVIEW, bool bPushMatrix = true ) const;

	protected:
		CSizei m_imgSize;
		CSizei m_canevaSize;
		CPointf m_center ;

	protected:
		float m_zoom   ;
		float m_zoomMin;
		float m_zoomMax;
		float m_zoomStep;

	protected:
		CMatrix3f m_matCanevaToImg;
		CMatrix3f m_matImgToCaneva;

	private:
		void buildMatrix();
	};

}}
