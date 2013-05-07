namespace HTS_NAMESPACE {
namespace HTS_GL_NAMESPACE {

	class CInfos
	{
	public:
		static bool _isATICard();
		static bool _isNVidiaCard();

	public:
		CInfos();

	public:
		bool get();                             // extract info
		void print(bool bWithExts);                           // print itself
		bool isExtensionSupported(const std::string& ext); // check if a extension is supported

	public:
		bool isATICard() const;
		bool isNVidiaCard() const;

	public:
		std::string m_vendor;
		std::string m_renderer;
		std::string m_version;
		std::vector <std::string> m_extensions;
		int m_redBits;
		int m_greenBits;
		int m_blueBits;
		int m_alphaBits;
		int m_depthBits;
		int m_stencilBits;
		int m_maxTexture2DSize;
		int m_maxTexture3DSize;
		int m_maxLights;
		int m_maxAttribStacks;
		int m_maxModelViewStacks;
		int m_maxProjectionStacks;
		int m_maxClipPlanes;
		int m_maxTextureStacks;
	};

}}
