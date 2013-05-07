namespace HTS_NAMESPACE {
namespace HTS_GL_NAMESPACE {

	class CQuad {
	public:
		static void draw(const CRectf & vPos, const CRectf & tPos= CRectf(0.0f,0.0f,1.0f,1.0f));

	public:
		float x0,y0, x1,y1;
		float u0,v0, u1,v1;

	public:
		CQuad();
		CQuad(const CTexture & texture);
		CQuad(const CQuad & src);
		//CGLQuad(const CRectf & vPos, const CRectf & tPos);
		CQuad & operator=(const CQuad & src);

		template <typename T, typename U> CQuad(const CTRect<T> & vPos, const CTRect<U> & tPos)
		:	x0(vPos.x), y0(vPos.y), x1(vPos.x + vPos.w), y1(vPos.y + vPos.h)
		,	u0(tPos.x), v0(tPos.y), u1(tPos.x + tPos.w), v1(tPos.y + tPos.h)
		{
		}

		template <typename T, typename U> CQuad(const CTSize<T> & vPos, const CTSize<U> & tPos)
		:	x0(0.f), y0(0.f), x1(vPos.cx), y1(vPos.cy)
		,	u0(0.f), v0(0.f), u1(tPos.cx), v1(tPos.cy)
		{
		}

	public:
		void draw();
	};



}}
