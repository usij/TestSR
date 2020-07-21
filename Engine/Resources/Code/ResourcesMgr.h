#ifndef ResourcesMgr_h__
#define ResourcesMgr_h__

#include "TriCol.h"
#include "RcCol.h"
#include "TestTerrain.h"
BEGIN(Engine)

class ENGINE_DLL CResourcesMgr : public CBase
{
	DECLARE_SINGLETON(CResourcesMgr)

private:
	explicit CResourcesMgr(void);
	virtual ~CResourcesMgr(void);

public:
	HRESULT	Reserve_ContainerSize(const _ushort& wSize);
	
	HRESULT	Ready_Buffer(LPDIRECT3DDEVICE9 pGraphicDev,
						const _ushort& wContainerIdx,
						const _tchar* pBufferTag,
						BUFFERID eID);
	
	void	Render_Buffer(const _ushort& wContainerIdx,
							const _tchar* pBufferTag);

	CResources*		Clone(const _ushort& wContainerIdx, 
							const _tchar* pResourceTag);

private:
	CResources*		Find_Resources(const _ushort& wContainerIdx, const _tchar* pResourceTag);

private:
	map<const _tchar*, CResources*>*		m_pmapResource = nullptr;

public:
	virtual void Free(void);
};

END
#endif // ResourcesMgr_h__
