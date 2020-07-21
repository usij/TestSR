#ifndef TestPlayer_h__
#define TestPlayer_h__

#include "Define.h"
#include "GameObject.h"

BEGIN(Engine)

class CRcCol;
class CTransform;

END
class CTestPlayer : public Engine::CGameObject
{
private:
	explicit CTestPlayer(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CTestPlayer(void);

public:
	virtual HRESULT Ready_Object(void) override;
	virtual _int Update_Object(const _float& fTimeDelta) override;
	virtual void Render_Object(void) override;
	

private:
	HRESULT		Add_Component(void);
	void		Key_Input(const _float& fTimeDelta);


private:
	Engine::CRcCol*			m_pBufferCom = nullptr;
	Engine::CTransform*		m_pTransform = nullptr;
	_vec3					m_vLook;
	_vec3					m_vRight;

public:
	static CTestPlayer*	Create(LPDIRECT3DDEVICE9 pGraphicDev);
private:
	virtual void Free(void) override;

};

#endif // TestPlayer_h__
