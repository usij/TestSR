#include "stdafx.h"
#include "Logo.h"

#include "Export_Function.h"

CLogo::CLogo(LPDIRECT3DDEVICE9 pGraphicDev)
	: Engine::CScene(pGraphicDev)
{

}

CLogo::~CLogo(void)
{

}

HRESULT CLogo::Ready_Scene(void)
{

	FAILED_CHECK_RETURN(Engine::CScene::Ready_Scene(), E_FAIL);
	FAILED_CHECK_RETURN(Ready_Resource(m_pGraphicDev, RESOURCE_END), E_FAIL);
	FAILED_CHECK_RETURN(Ready_Layer_UI(L"UI"), E_FAIL);

	// 임시 적용
	_matrix		matView, matProj;

	D3DXMatrixLookAtLH(&matView, 
						&_vec3(0.f, 2.f, -50.f),
						&_vec3(0.f, 0.f, 0.f),
						&_vec3(0.f, 1.f, 0.f));

	D3DXMatrixPerspectiveFovLH(&matProj,
						D3DXToRadian(45.f),
						_float(WINCX) / WINCY, 
						1.f, 
						1000.f);

	m_pGraphicDev->SetTransform(D3DTS_VIEW, &matView);
	m_pGraphicDev->SetTransform(D3DTS_PROJECTION, &matProj);


	return S_OK;
}

_int CLogo::Update_Scene(const _float& fTimeDelta)
{
	Engine::CScene::Update_Scene(fTimeDelta);

	return 0;
}

void CLogo::Render_Scene(void)
{
	Engine::CScene::Render_Scene();
}

void CLogo::Free(void)
{
	Engine::CScene::Free();
}

CLogo* CLogo::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CLogo*	pInstance = new CLogo(pGraphicDev);

	if (FAILED(pInstance->Ready_Scene()))
		Engine::Safe_Release(pInstance);

	return pInstance;
}

HRESULT CLogo::Ready_Layer_UI(const _tchar* pLayerTag)
{
	Engine::CLayer*		pLayer = Engine::CLayer::Create();
	NULL_CHECK_RETURN(pLayer, E_FAIL);

	Engine::CGameObject*		pGameObject = nullptr;

	// BackGround
	//pGameObject = CBackGround::Create(m_pGraphicDev);
	//NULL_CHECK_RETURN(pGameObject, E_FAIL);
	//FAILED_CHECK_RETURN(pLayer->Add_Object(L"BackGround", pGameObject), E_FAIL);

	// TestPlayer
	pGameObject = CTestPlayer::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_Object(L"TestPlayer", pGameObject), E_FAIL);

	// TestMonster
	pGameObject = CTestMonster::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_Object(L"TestMonster", pGameObject), E_FAIL);

	pGameObject = CTestTerrainClient::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_Object(L"TestTerrain", pGameObject), E_FAIL);

	m_mapLayer.emplace(pLayerTag, pLayer);

	return S_OK;
}

HRESULT CLogo::Ready_Resource(LPDIRECT3DDEVICE9 pGraphicDev, RESOURCEID eMax)
{
	Engine::Reserve_ContainerSize(eMax);

	FAILED_CHECK_RETURN(Engine::Ready_Buffer(pGraphicDev,
												RESOURCE_STATIC,
												L"Buffer_TriCol",
												Engine::BUFFER_TRICOL),
												E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Buffer(pGraphicDev,
												RESOURCE_STATIC,
												L"Buffer_RcCol",
												Engine::BUFFER_RCCOL),
												E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Buffer(pGraphicDev,
		RESOURCE_STATIC,
		L"Buffer_TestTerrain",
		Engine::BUFFER_TERRINTEX),
		E_FAIL);


	return S_OK;
}

//	// BackGround
//	pGameObject = CBackGround::Create(m_pGraphicDev);
//	
//	if (nullptr == pGameObject)
//		goto Home;
//
//	if (FAILED(pLayer->Add_Object(L"BackGround", pGameObject)))
//		goto Home;
//
//	m_mapLayer.emplace(pLayerTag, pLayer);
//
//	return S_OK;
//
//Home:
//	Engine::Safe_Release(pLayer);
//	return E_FAIL;