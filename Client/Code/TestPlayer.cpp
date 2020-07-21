#include "stdafx.h"
#include "TestPlayer.h"

#include "Export_Function.h"

CTestPlayer::CTestPlayer(LPDIRECT3DDEVICE9 pGraphicDev)
	: Engine::CGameObject(pGraphicDev)
	, m_vLook(0.f, 0.f, 0.f)
	, m_vRight(1.f,0.f,0.f)
{

}

CTestPlayer::~CTestPlayer(void)
{

}

HRESULT CTestPlayer::Ready_Object(void)
{
	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	/*m_pTransform->m_vScale.x = 2.f;
	m_pTransform->m_vScale.y = 2.f;*/

	//m_pTransform->m_vAngle.z = D3DXToRadian(45.f);

	return S_OK;
}

_int CTestPlayer::Update_Object(const _float& fTimeDelta)
{
	Engine::CGameObject::Update_Object(fTimeDelta);

	Key_Input(fTimeDelta);
	

	return 0;
}

void CTestPlayer::Render_Object(void)
{
	m_pTransform->Set_Transform(m_pGraphicDev);
	m_pGraphicDev->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	m_pBufferCom->Render_Buffer();

	m_pGraphicDev->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}

void CTestPlayer::Free(void)
{
	Engine::CGameObject::Free();
}


HRESULT CTestPlayer::Add_Component(void)
{
	Engine::CComponent*		pComponent = nullptr;

	// buffer
	pComponent = m_pBufferCom = dynamic_cast<Engine::CRcCol*>
		(Engine::Clone(RESOURCE_STATIC, L"Buffer_RcCol"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[Engine::ID_STATIC].emplace(L"Com_Buffer", pComponent);

	//Transform
	pComponent = m_pTransform = Engine::CTransform::Create();
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[Engine::ID_DYNAMIC].emplace(L"Com_Transform", pComponent);


	return S_OK;
}

CTestPlayer* CTestPlayer::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CTestPlayer*		pInstance = new CTestPlayer(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
		Engine::Safe_Release(pInstance);

	return pInstance;
}

void CTestPlayer::Key_Input(const _float& fTimeDelta)
{
	m_pTransform->Get_Info(Engine::INFO_UP, &m_vLook);

	if (GetAsyncKeyState(VK_UP) & 0x8000)
	{
		D3DXVec3Normalize(&m_vLook, &m_vLook);
		m_pTransform->Move_Pos(&(m_vLook * fTimeDelta * 5.f));
	}
	if (GetAsyncKeyState(VK_DOWN) & 0x8000)
	{
		D3DXVec3Normalize(&m_vLook, &m_vLook);
		m_pTransform->Move_Pos(&(m_vLook * fTimeDelta * -5.f));
	}

	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		D3DXVec3Normalize(&m_vLook, &m_vLook);
		m_pTransform->Move_Pos(&(m_vRight * fTimeDelta * 5.f));
	}
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		D3DXVec3Normalize(&m_vLook, &m_vLook);
		m_pTransform->Move_Pos(&(m_vRight * fTimeDelta * -5.f));
	}

	if (GetAsyncKeyState('Q') & 0x8000)
		m_pTransform->Rotation(Engine::ROT_X, D3DXToRadian(90.f * fTimeDelta));

	if (GetAsyncKeyState('A') & 0x8000)
		m_pTransform->Rotation(Engine::ROT_X, D3DXToRadian(90.f * -fTimeDelta));
	
	if (GetAsyncKeyState('W') & 0x8000)
		m_pTransform->Rotation(Engine::ROT_Y, D3DXToRadian(90.f * fTimeDelta));

	if (GetAsyncKeyState('S') & 0x8000)
		m_pTransform->Rotation(Engine::ROT_Y, D3DXToRadian(90.f * -fTimeDelta));

	if (GetAsyncKeyState('E') & 0x8000)
		m_pTransform->Rotation(Engine::ROT_Z, D3DXToRadian(90.f * fTimeDelta));

	if (GetAsyncKeyState('D') & 0x8000)
		m_pTransform->Rotation(Engine::ROT_Z, D3DXToRadian(90.f * -fTimeDelta));
}

