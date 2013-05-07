#include "common.h"

//#define DUMP_IT

#ifdef DUMP_IT
#	define _DUMP TRACEFN
#else
#	define _DUMP _dump
	inline void _dump(const void * , ...) {}
#endif

namespace HTS_NAMESPACE {
namespace HTS_GL_NAMESPACE {

	bool CTextureManagerKey::operator<( const CTextureManagerKey & b) const {
		if (m_target < b.m_target) return true ;
		if (m_target > b.m_target) return false;

		if (m_w < b.m_w) return true ;
		if (m_w > b.m_w) return false;
		if (m_h < b.m_h) return true ;
		if (m_h > b.m_h) return false;
		if (m_d < b.m_d) return true ;
		if (m_d > b.m_d) return false;

		if (m_internalFormat < b.m_internalFormat) return true;
		if (m_internalFormat > b.m_internalFormat) return false;

		if (m_format < b.m_format) return true ;
		if (m_format > b.m_format) return false;

		if (m_type < b.m_type) return true ;
		if (m_type > b.m_type) return false;
		return false;
	}

	class CTextureRefCount
	{
	public:
		Texture          m_id;
		int                m_refCount;
		CTextureManagerKey m_key;
	public:
		CTextureRefCount(Texture id, const CTextureManagerKey & key) : m_id(id), m_refCount(1), m_key(key) {}
		~CTextureRefCount() {
			if (m_id) {
				TRACEFN("deleting texture %i\n", m_id);
				CHECK_GLERROR("Before\n");
				glDeleteTextures(1, &m_id );
				CHECK_GLERROR("After\n");
			}
		}

	};

	//* /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	class CTextureManagerImpl
	{
	public:
		CTextureManagerImpl(CTextureManager & mng);
		~CTextureManagerImpl();
		void purgeAll();

	public:
		bool isManaged(Texture id) const;
		CTextureManagerKey getInfos(Texture id) const;
		CTexture get( GLenum target, unsigned int w, GLint internalFormat, GLenum format, GLenum type, bool & bCreated);
		CTexture get( GLenum target, unsigned int w, unsigned int h, GLint internalFormat, GLenum format, GLenum type, bool & bCreated);
		CTexture get( GLenum target, unsigned int w, unsigned int h, unsigned int d, GLint internalFormat, GLenum format, GLenum type, bool & bCreated);
		bool get( Texture id );
		bool release( Texture id );
		int refCount( Texture id ) const; // renvoie < 0 si non managée
		size_t getAllManaged(std::set<Texture> & all) const;

	private:
		void dumpAll();
		bool deleteTexture( Texture id );

	private:
		CTextureManager & m_mng;
		typedef std::map<Texture, CTextureRefCount*> CAllTextures;
		typedef std::multimap<CTextureManagerKey, CTextureRefCount*> CAvailables;
		typedef std::map<Texture, CTextureRefCount*> CInUse;
		CAllTextures m_all;
		CAvailables  m_availables;
		CInUse       m_inUse;
	};

	//* /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	CTextureManagerImpl::CTextureManagerImpl(CTextureManager & mng)
	:	m_mng(mng)
	{
		TRACEFN("\n");
	}
	CTextureManagerImpl::~CTextureManagerImpl()
	{
		TRACEFN("\n");
		while (!m_all.empty())
		{
			CAllTextures::iterator it= m_all.begin();
			deleteTexture( it->second->m_id );
		}
	}

	bool CTextureManagerImpl::deleteTexture( Texture id )
	{
		for (CAvailables::iterator it= m_availables.begin(); it != m_availables.end(); ++it) {
			Texture idCrt= it->second->m_id;
			if ( idCrt == id ) {

				m_mng.notify( CTextureManager::NOTIFY_DELETING, int(id));

				if (it->second->m_refCount) {
					TRACEFN("*** Warning destroying used texture (id=%i, refCount=%i)\n", (int)it->second->m_id, it->second->m_refCount);
				}

				CTextureRefCount* pRc = it->second;
				m_availables.erase(it);
				CAllTextures::iterator itAll = m_all.find( id ); ASSERT( itAll != m_all.end() );
				m_all.erase(itAll);

				delete pRc;

				m_mng.notify( CTextureManager::NOTIFY_DELETED, int(id));
				return true;
			}
		}
		return false;
	}

	void CTextureManagerImpl::purgeAll()
	{
		TRACEFN("\n");

		std::set<Texture> unused;
		while (!m_availables.empty())
		{
			CAvailables::iterator it= m_availables.begin();
			Texture id= it->second->m_id;
			m_mng.notify( CTextureManager::NOTIFY_DELETING, int(id));

			CTextureRefCount* pOldRef = it->second;
			m_availables.erase(it);

			CAllTextures::iterator itAll = m_all.find( id ); ASSERT( itAll != m_all.end() );
			m_all.erase(itAll);
			delete pOldRef;

			m_mng.notify( CTextureManager::NOTIFY_DELETED, int(id));
		}
	}

	bool CTextureManagerImpl::isManaged(Texture id) const
	{
		CAllTextures::const_iterator itFound = m_all.find(id);
		return (itFound != m_all.end());
	}

	CTextureManagerKey CTextureManagerImpl::getInfos(Texture id) const
	{
		CAllTextures::const_iterator itFound = m_all.find(id);
		if (itFound != m_all.end())
			return itFound->second->m_key;

		return CTextureManagerKey();
	}

	int CTextureManagerImpl::refCount(Texture id) const
	{
		CAllTextures::const_iterator itFound = m_all.find(id);
		if (itFound == m_all.end()) return -1;
		return itFound->second->m_refCount;
	}

	size_t CTextureManagerImpl::getAllManaged(std::set<Texture> & all) const {

		all.clear();
		for (CAllTextures::const_iterator it= m_all.begin(); it != m_all.end(); ++it)
			all.insert( it->first );

		return all.size();
	}



	#ifdef DUMP_IT

	static std::string strKey( const CTextureManagerKey & k) {
		return strFormat( " %ix%ix%i, %i, %i, %i, %i", k.m_w, k.m_h, k.m_d, k.m_target, k.m_internalFormat, k.m_format, k.m_type );
	}
	void CTextureManagerImpl::dumpAll()
	{
		TRACEFN("m_availables (%i) : \n", m_availables.size());
		for (CAvailables::iterator it= m_availables.begin(); it != m_availables.end(); ++it) {
			 const CTextureRefCount* p = it->second;
			 TRACEFN("     %i(%i) : %s\n", p->m_id, p->m_refCount, strKey(p->m_key).c_str());
		}
		TRACEFN("m_inUse (%i) : \n", m_inUse.size());
		for (CInUse::iterator it= m_inUse.begin(); it != m_inUse.end(); ++it) {
			 const CTextureRefCount* p = it->second;
			 TRACEFN("     %i(%i) : %s\n", p->m_id, p->m_refCount, strKey(p->m_key).c_str());
		}

	}
	#else
	inline void CTextureManagerImpl::dumpAll() {}
	#endif


	CTexture CTextureManagerImpl::get( GLenum target, unsigned int w, GLint internalFormat, GLenum format, GLenum type, bool & bCreated )
	{
		return get( target,w,0,0,internalFormat, format, type, bCreated);
	}

	CTexture CTextureManagerImpl::get( GLenum target, unsigned int w, unsigned int h, GLint internalFormat, GLenum format, GLenum type, bool & bCreated )
	{
		return get( target,w,h,0,internalFormat, format, type, bCreated);
	}

	CTexture CTextureManagerImpl::get( GLenum target, unsigned int w, unsigned int h, unsigned int d, GLint internalFormat, GLenum format, GLenum type, bool & bCreated )
	{
		_DUMP("%ix%i, %i, %i, %i\n", target, w, h, d, internalFormat, format, type);
		dumpAll();

		bCreated = false;
		CTextureRefCount * p = NULL;
		const CTextureManagerKey key(target,w,h,d,internalFormat,format,type);

		CAvailables::iterator itFound = m_availables.find(key);

		if (itFound != m_availables.end()) {
			// On en a trouve une !
			p = itFound->second;
			m_availables.erase(itFound);
			p->m_refCount++;
			_DUMP("  => Found %i \n", p->m_id );

		} else if (m_availables.empty()) {
			// Aucune texture disponible
			CTexture t;
			t.create(w,h,d,target,internalFormat, format, type);
	//t.setMinMaxFilters(GL_LINEAR);
			p = new CTextureRefCount(t, key);
			m_all.insert(std::pair<Texture, CTextureRefCount*>(p->m_id, p));
			t.detach();
			bCreated = true;
			_DUMP("  => Create new %i \n", p->m_id );
			TRACEFN("Generated new texture id : %i\n", p->m_id);

		} else {
			// au moins 1 texture disponible => on la re-assigne

			itFound = m_availables.begin();
			p = itFound->second;
			m_availables.erase(itFound);
			p->m_refCount++;

			CTexture t;
			t.attach( p->m_key.m_target, p->m_id, p->m_key.m_w, p->m_key.m_h );
			t.create(w,h,d,target,internalFormat, format, type);
	//t.setMinMaxFilters(GL_LINEAR);

			p->m_key = key;
			t.detach();
			_DUMP("  => reassign %i \n", p->m_id );
		}

		ASSERT( p->m_refCount > 0 );
		m_inUse.insert(std::pair<Texture, CTextureRefCount*>( p->m_id, p) );

		dumpAll();
	//TRACE("GET (%i[%i]) %ix%i, %i, %i, %i\n", p->m_id, p->m_refCount, target, w, h, internalFormat, format, type);
		return CTexture(p->m_key.m_target, p->m_id, p->m_key.m_w, p->m_key.m_h, p->m_key.m_d);
	}

	bool CTextureManagerImpl::get( Texture id )
	{
		_DUMP("%i\n", id );
		dumpAll();
		if (!IS_VALID_TEXTURE_ID(id)) {
			TRACEFN("***** WARNING ***** trying to get an invalid texture\n");
			_DUMP("  => INVALID\n" );
			return false;
		}

		CInUse::iterator itFound = m_inUse.find(id);
		if (itFound == m_inUse.end()) {
			TRACEFN("***** WARNING ***** trying to get an unused texture\n");
			_DUMP("  => NOT UN INUSE LIST\n" );
			return false;
		}

		itFound->second->m_refCount++;
		dumpAll();
		_DUMP("  => Found (refCount = %i)\n", itFound->second->m_refCount);
		return true;
	}

	bool CTextureManagerImpl::release( Texture id )
	{
		_DUMP("%i\n", id );
		dumpAll();
		if (!IS_VALID_TEXTURE_ID(id)) {
			_DUMP("  => INVALID\n" );
			return false;
		}

		CInUse::iterator itFound = m_inUse.find(id);
		if (itFound == m_inUse.end()) {
			_DUMP("  => NOT UN INUSE LIST\n" );
			return false;
		}

		CTextureRefCount * p = itFound->second;

		ASSERT( p->m_refCount > 0 );
		p->m_refCount--;
		if (p->m_refCount == 0) {
			m_inUse.erase(itFound);
			m_availables.insert(std::pair<CTextureManagerKey, CTextureRefCount*>( p->m_key , p ));
		}
		dumpAll();
		_DUMP("  => Found (refCount = %i)\n", p->m_refCount);
	//TRACE("RELEASE (%i[%i])\n", id, p->m_refCount);
		return true;
	}

	//* /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	CTextureManager::CTextureManager()
	:	m_pImpl( new CTextureManagerImpl(*this) )
	{
	}

	CTextureManager::~CTextureManager()
	{
	}

	void CTextureManager::purgeAll()
	{
		m_pImpl->purgeAll();
	}

	bool CTextureManager::isManaged( Texture2D id ) const
	{
		return m_pImpl->isManaged(id);
	}

	CTextureManagerKey CTextureManager::getInfos(Texture id) const
	{
		return m_pImpl->getInfos(id);
	}

	CTexture CTextureManager::get( GLenum target, unsigned int w, GLint internalFormat, GLenum format, GLenum type )
	{
		bool bCreated = false;
		const CTexture result= m_pImpl->get(target,w, internalFormat, format, type, bCreated);
		if (bCreated)
			notify(NOTIFY_CREATENEW, int(result.id()) );

		notify( NOTIFY_GETNEW, (int)result.id());
		return result;
	}
	CTexture CTextureManager::get( GLenum target, unsigned int w, unsigned int h, GLint internalFormat, GLenum format, GLenum type )
	{
		bool bCreated = false;
		const CTexture result= m_pImpl->get(target,w,h, internalFormat, format, type, bCreated);
		if (bCreated)
			notify(NOTIFY_CREATENEW, int(result.id()) );

		notify( NOTIFY_GETNEW, (int)result.id());
		return result;
	}
	CTexture CTextureManager::get( GLenum target, unsigned int w, unsigned int h, unsigned int d, GLint internalFormat, GLenum format, GLenum type )
	{
		bool bCreated = false;
		const CTexture result= m_pImpl->get(target,w,h,d, internalFormat, format, type, bCreated);
		if (bCreated)
			notify(NOTIFY_CREATENEW, int(result.id()) );

		notify( NOTIFY_GETNEW, (int)result.id());
		return result;
	}

	bool CTextureManager::get( Texture id )
	{
		const bool result = m_pImpl->get(id);
		notify( NOTIFY_GET, (int)id);
		return result;
	}
	bool CTextureManager::release( Texture id )
	{
		const bool result = m_pImpl->release(id);
		notify( NOTIFY_RELEASED, (int)id);
		return result;
	}

	int CTextureManager::refCount( Texture id ) const // renvoie < 0 si non managée
	{
		return m_pImpl->refCount( id );
	}

	size_t CTextureManager::getAllManaged(std::set<Texture> & all) const
	{
		return m_pImpl->getAllManaged(all);
	}


}}
