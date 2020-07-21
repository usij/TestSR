#ifndef Export_Resources_h__
#define Export_Resources_h__

#include "Engine_Define.h"
#include "ResourcesMgr.h"

BEGIN(Engine)

// ResourcesMgr
// Get
// Set
// General
inline HRESULT	Reserve_ContainerSize(const _ushort& wSize);
inline HRESULT	Ready_Buffer(LPDIRECT3DDEVICE9 pGraphicDev,
							const _ushort& wContainerIdx,
							const _tchar* pBufferTag,
							BUFFERID eID);
inline void	Render_Buffer(const _ushort& wContainerIdx, const _tchar* pBufferTag);
inline CResources*		Clone(const _ushort& wContainerIdx, const _tchar* pResourceTag);


// Release
inline void		Release_Resources(void);

#include "Export_Resources.inl"

END
#endif // Export_Resources_h__
