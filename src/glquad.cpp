#include "common.h"
namespace HTS_NAMESPACE {
namespace HTS_GL_NAMESPACE {

	//-----------------------------------------------------------------------------

	void CQuad::draw(const CRectf & vPos, const CRectf & tPos)
	{
		CQuad(vPos, tPos).draw();
	}

	//-----------------------------------------------------------------------------

	CQuad::CQuad()
	:	x0(0.0f), y0(0.0f), x1(0.0f), y1(0.0f)
	,	u0(0.0f), v0(0.0f), u1(0.0f), v1(0.0f)
	{
	}

	CQuad::CQuad(const CQuad & src) {
		(*this) = src;
	}

	//CQuad::CQuad(const CRectf & vPos, const CRectf & tPos)
	//:	x0(vPos.x), y0(vPos.y), x1(vPos.x + vPos.w), y1(vPos.y + vPos.h)
	//,	u0(tPos.x), v0(tPos.y), u1(tPos.x + tPos.w), v1(tPos.y + tPos.h)
	//{
	//}

	CQuad & CQuad::operator=(const CQuad & src) {
		if (this != &src) {
			x0 = src.x0; y0 = src.y0;
			x1 = src.x1; y1 = src.y1;
			u0 = src.u0; v0 = src.v0;
			u1 = src.u1; v1 = src.v1;
		}
		return (*this);
	}


	CQuad::CQuad(const CTexture & texture) {
		const float w = texture.getWidth();
		const float h = texture.getHeight();

		x0= y0= 0.0f;
		x1= w;
		y1= h;

		u0= v0 = 0.0f;
		if (texture.target() == GL_TEXTURE_2D)
			u1= v1 = 1.0f;
		else {
			u1 = w;
			v1 = h;
		}
	}
	
	
	void CQuad::draw() {

		CHECK_GLERROR("");
		glBegin(GL_QUADS);
			glMultiTexCoord2fARB(GL_TEXTURE0_ARB,u0, v0); glVertex2f(x0, y0);
			glMultiTexCoord2fARB(GL_TEXTURE0_ARB,u0, v1); glVertex2f(x0, y1);
			glMultiTexCoord2fARB(GL_TEXTURE0_ARB,u1, v1); glVertex2f(x1, y1);
			glMultiTexCoord2fARB(GL_TEXTURE0_ARB,u1, v0); glVertex2f(x1, y0);

		glEnd();
		CHECK_GLERROR("");
	}

}}

