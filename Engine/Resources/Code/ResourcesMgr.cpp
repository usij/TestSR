#include "ResourcesMgr.h"

USING(Engine)
IMPLEMENT_SINGLETON(CResourcesMgr)

Engine::CResourcesMgr::CResourcesMgr(void)
	: m_pmapResource(nullptr)
{

}

Engine::CResourcesMgr::~CResourcesMgr(void)
{
	Free();
}

HRESULT Engine::CResourcesMgr::Reserve_ContainerSize(const _ushort& wSize)
{
	if (nullptr != m_pmapResource)
		return E_FAIL;

	m_pmapResource = new map<const _tchar*, CResources*>[wSize];

	return S_OK;
}

HRESULT Engine::CResourcesMgr::Ready_Buffer(LPDIRECT3DDEVICE9 pGraphicDev,
											const _ushort& wContainerIdx,
											const _tchar* pBufferTag,
											BUFFERID eID)
{
	NULL_CHECK_RETURN(m_pmapResource, E_FAIL);

	CResources*	pResources = Find_Resources(wContainerIdx, pBufferTag);

	if (nullptr != pResources)
		return E_FAIL;

	switch (eID)
	{
	case BUFFER_TRICOL:
		pResources = CTriCol::Create(pGraphicDev);
		break;

	case BUFFER_RCCOL:
		pResources = CRcCol::Create(pGraphicDev);
		break;

	case BUFFER_RCTEX:
		//pResources = CTriCol::Create(pGraphicDev);
		break;
	case BUFFER_TERRINTEX:
		pResources = CTestTerrain::Create(pGraphicDev);
		break;

	}
	
	m_pmapResource[wContainerIdx].emplace(pBufferTag, pResources);

	return S_OK;
}

CResources* Engine::CResourcesMgr::Find_Resources(const _ushort& wContainerIdx, const _tchar* pResourceTag)
{
	auto	iter = find_if(m_pmapResource[wContainerIdx].begin(), m_pmapResource[wContainerIdx].end(), CTag_Finder(pResourceTag));

	if (iter == m_pmapResource[wContainerIdx].end())
		return nullptr;

	return iter->second;
}

void Engine::CResourcesMgr::Free(void)
{
	for_each(m_pmapResource->begin(), m_pmapResource->end(), CDeleteMap());
	m_pmapResource->clear();

	Safe_Delete_Array(m_pmapResource);
}

void Engine::CResourcesMgr::Render_Buffer(const _ushort& wContainerIdx, const _tchar* pBufferTag)
{
	CResources*	pResources = Find_Resources(wContainerIdx, pBufferTag);
	NULL_CHECK(pResources);

	dynamic_cast<CVIBuffer*>(pResources)->Render_Buffer();
}

CResources* Engine::CResourcesMgr::Clone(const _ushort& wContainerIdx, const _tchar* pResourceTag)
{
	if (nullptr == m_pmapResource)
		return nullptr;

	CResources*	pPrototype = Find_Resources(wContainerIdx, pResourceTag);

	return dynamic_cast<CResources*>(pPrototype->Clone());
}

