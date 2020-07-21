#include "stdafx.h"
#include "TestTerrainClient.h"
#include "Export_Function.h"

CTestTerrainClient::CTestTerrainClient(LPDIRECT3DDEVICE9 pGarphicDev)
	: Engine::CGameObject(pGarphicDev)
{
}

CTestTerrainClient::~CTestTerrainClient(void)
{
}

HRESULT CTestTerrainClient::Ready_Object(void)
{
	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	return S_OK;
}

_int CTestTerrainClient::Update_Object(const _float & fTimeDelta)
{
	Engine::CGameObject::Update_Object(fTimeDelta);

	return 0;
}

void CTestTerrainClient::Render_Object(void)
{
	m_pTransform->Set_Transform(m_pGraphicDev);

	m_pGraphicDev->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

	m_pBufferCom->Render_Buffer();
}

HRESULT CTestTerrainClient::Add_Component(void)
{
	Engine::CComponent* pComponent = nullptr;

	// buffer
	pComponent = m_pBufferCom = dynamic_cast<Engine::CTestTerrain*>
		(Engine::Clone(RESOURCE_STATIC, L"Buffer_TestTerrain"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[Engine::ID_STATIC].emplace(L"Com_Buffer", pComponent);

	//Transform
	pComponent = m_pTransform = Engine::CTransform::Create();
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[Engine::ID_DYNAMIC].emplace(L"Com_Transform", pComponent);

	return S_OK;
}

CTestTerrainClient * CTestTerrainClient::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CTestTerrainClient* pInstance = new CTestTerrainClient(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
		Engine::Safe_Release(pInstance);

	return pInstance;
}

void CTestTerrainClient::Free(void)
{
	Engine::CGameObject::Free();
}
