#include "Layer.h"

USING(Engine)

Engine::CLayer::CLayer(void)
{

}

Engine::CLayer::~CLayer(void)
{

}

HRESULT Engine::CLayer::Ready_Layer(void)
{
	return S_OK;
}

_int Engine::CLayer::Update_Layer(const _float& fTimeDelta)
{
	_int iEnd = 0;

	for (auto& iter : m_mapObject)
	{
		iEnd = iter.second->Update_Object(fTimeDelta);
		if (iEnd & 0x80000000)
			return iEnd;
	}
	
	return iEnd;
}

void Engine::CLayer::Render_Layer(void)
{
	for (auto& iter : m_mapObject)
		iter.second->Render_Object();
}

CLayer* Engine::CLayer::Create(void)
{
	CLayer*	pInstance = new CLayer;

	if (FAILED(pInstance->Ready_Layer()))
		Safe_Release(pInstance);

	return pInstance;
}

void Engine::CLayer::Free(void)
{
	for_each(m_mapObject.begin(), m_mapObject.end(), CDeleteMap());
	m_mapObject.clear();
}

HRESULT Engine::CLayer::Add_Object(const _tchar* pObjTag, CGameObject* pGameObject)
{
	if (nullptr == pGameObject)
		return E_FAIL;

	m_mapObject.emplace(pObjTag, pGameObject);

	return S_OK;
}

CComponent* Engine::CLayer::Get_Component(const _tchar* pObjTag, const _tchar* pComponentTag, COMPONENTID eID)
{
	auto	iter = find_if(m_mapObject.begin(), m_mapObject.end(), CTag_Finder(pObjTag));

	if (iter == m_mapObject.end())
		return nullptr;

	return iter->second->Get_Component(pComponentTag, eID);
}

