#ifndef TestTerrainClient_h__
#define TestTerrainClient_h__

#include "Define.h"
#include "GameObject.h"

BEGIN(Engine)
class CTestTerrain;
class CRcCol;
class CTransform;
END

class CTestTerrainClient : public Engine::CGameObject
{
private:
	explicit CTestTerrainClient(LPDIRECT3DDEVICE9 pGarphicDev);
	virtual ~CTestTerrainClient(void);

public:
	virtual HRESULT Ready_Object(void) override;
	virtual _int Update_Object(const _float& fTimeDelta) override;
	virtual void Render_Object(void) override;


private:
	HRESULT		Add_Component(void);

private:
	Engine::CTestTerrain* m_pBufferCom = nullptr;
	Engine::CTransform* m_pTransform = nullptr;

public:
	static CTestTerrainClient* Create(LPDIRECT3DDEVICE9 pGraphicDev);
private:
	virtual void Free(void) override;
};
#endif // TestTerrainClient_h__
