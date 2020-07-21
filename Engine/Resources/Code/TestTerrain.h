#ifndef TestTerrain_h__
#define TestTerrain_h__

#include "VIBuffer.h"
BEGIN(Engine)

class ENGINE_DLL CTestTerrain : public CVIBuffer
{
private:
	explicit CTestTerrain(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CTestTerrain(const CTestTerrain& rhs);
	virtual ~CTestTerrain(void);

public:
	virtual HRESULT Ready_Buffer(void) override;
	virtual void Render_Buffer(void) override;

public:
	static CTestTerrain* Create(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual CComponent* Clone(void) override;
	virtual void Free(void) override;

private:
	int m_iCX = 129;
	int m_iCZ = 129;

};
END
#endif // TestTerrain_h__
