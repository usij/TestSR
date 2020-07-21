#include "stdafx.h"
#include "TestMonster.h"

#include "Export_Function.h"

CTestMonster::CTestMonster(LPDIRECT3DDEVICE9 pGraphicDev)
	: Engine::CGameObject(pGraphicDev)
	, m_vLook(0.f, 0.f, 0.f)
{

}

CTestMonster::~CTestMonster(void)
{

}

HRESULT CTestMonster::Ready_Object(void)
{
	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);


	return S_OK;
}

_int CTestMonster::Update_Object(const _float& fTimeDelta)
{
	Engine::CGameObject::Update_Object(fTimeDelta);

	Engine::CTransform*		pPlayerTransformCom = dynamic_cast<Engine::CTransform*>
		(Engine::Get_Component(L"UI",
								L"TestPlayer", 
								L"Com_Transform",
								Engine::ID_DYNAMIC));

	if (nullptr == pPlayerTransformCom)
		return -1;

	_vec3	vPlayerPos;
	pPlayerTransformCom->Get_Info(Engine::INFO_POS, &vPlayerPos);
	
	m_pTransform->Chase_Target(&vPlayerPos, (fTimeDelta * 2.f));

	return 0;
}

void CTestMonster::Render_Object(void)
{
	m_pTransform->Set_Transform(m_pGraphicDev);
	m_pGraphicDev->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	m_pBufferCom->Render_Buffer();

	m_pGraphicDev->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}

void CTestMonster::Free(void)
{
	Engine::CGameObject::Free();
}


HRESULT CTestMonster::Add_Component(void)
{
	Engine::CComponent*		pComponent = nullptr;

	// buffer
	pComponent = m_pBufferCom = dynamic_cast<Engine::CTriCol*>
		(Engine::Clone(RESOURCE_STATIC, L"Buffer_TriCol"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[Engine::ID_STATIC].emplace(L"Com_Buffer", pComponent);

	//Transform
	pComponent = m_pTransform = Engine::CTransform::Create();
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[Engine::ID_STATIC].emplace(L"Com_Transform", pComponent);


	return S_OK;
}

CTestMonster* CTestMonster::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CTestMonster*		pInstance = new CTestMonster(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
		Engine::Safe_Release(pInstance);

	return pInstance;
}



