#include "RcCol.h"

USING(Engine)

Engine::CRcCol::CRcCol(LPDIRECT3DDEVICE9 pGraphicDev)
	: CVIBuffer(pGraphicDev)
{

}

Engine::CRcCol::CRcCol(const CRcCol& rhs)
	: CVIBuffer(rhs)
{

}

Engine::CRcCol::~CRcCol(void)
{

}

HRESULT Engine::CRcCol::Ready_Buffer(void)
{
	m_dwVtxCnt = 4;
	m_dwTriCnt = 2;
	m_dwVtxSize = sizeof(VTXCOL);
	m_dwFVF = FVF_COL;

	m_dwIdxSize = sizeof(INDEX16);
	m_IdxFmt = D3DFMT_INDEX16;

	FAILED_CHECK_RETURN(CVIBuffer::Ready_Buffer(), E_FAIL);

	VTXCOL*		pVertex = nullptr;

	m_pVB->Lock(0, 0, (void**)&pVertex, 0);
	// 1. 버텍스들의 대한 접근을 막는다.
	// 2. 3번째 인자값을 통해 버텍스 중 첫 번째 주소를 리턴한다.

	//// 오른쪽 위
	//pVertex[0].vPosition = _vec3(-1.f, 1.f, 0.f);
	//pVertex[0].dwColor = D3DXCOLOR(1.f, 0.f, 0.f, 1.f);

	//pVertex[1].vPosition = _vec3(1.f, 1.f, 0.f);
	//pVertex[1].dwColor = D3DXCOLOR(1.f, 0.f, 0.f, 1.f);

	//pVertex[2].vPosition = _vec3(1.f, -1.f, 0.f);
	//pVertex[2].dwColor = D3DXCOLOR(1.f, 0.f, 0.f, 1.f);

	//// 왼쪽 아래
	//pVertex[3].vPosition = _vec3(-1.f, 1.f, 0.f);
	//pVertex[3].dwColor = D3DXCOLOR(0.f, 1.f, 0.f, 1.f);

	//pVertex[4].vPosition = _vec3(1.f, -1.f, 0.f);
	//pVertex[4].dwColor = D3DXCOLOR(0.f, 1.f, 0.f, 1.f);

	//pVertex[5].vPosition = _vec3(-1.f, -1.f, 0.f);
	//pVertex[5].dwColor = D3DXCOLOR(0.f, 1.f, 0.f, 1.f);

	pVertex[0].vPosition = _vec3(-0.5f, 0.5f, 0.f);
	pVertex[0].dwColor = D3DXCOLOR(1.f, 0.f, 0.f, 1.f);

	pVertex[1].vPosition = _vec3(0.5f, 0.5f, 0.f);
	pVertex[1].dwColor = D3DXCOLOR(1.f, 0.f, 0.f, 1.f);

	pVertex[2].vPosition = _vec3(0.5f, -0.5f, 0.f);
	pVertex[2].dwColor = D3DXCOLOR(1.f, 0.f, 0.f, 1.f);

	pVertex[3].vPosition = _vec3(-0.5f, -0.5f, 0.f);
	pVertex[3].dwColor = D3DXCOLOR(0.f, 1.f, 0.f, 1.f);
	
	m_pVB->Unlock();

	INDEX16*		pIndex = nullptr;

	m_pIB->Lock(0, 0, (void**)&pIndex, 0);

	pIndex[0]._0 = 0;
	pIndex[0]._1 = 1;
	pIndex[0]._2 = 2;

	pIndex[1]._0 = 0;
	pIndex[1]._1 = 2;
	pIndex[1]._2 = 3;

	m_pIB->Unlock();

	return S_OK;
}

void Engine::CRcCol::Render_Buffer(void)
{
	CVIBuffer::Render_Buffer();
}

void Engine::CRcCol::Free(void)
{
	CVIBuffer::Free();
}

CRcCol* Engine::CRcCol::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CRcCol*	pInstance = new CRcCol(pGraphicDev);

	if (FAILED(pInstance->Ready_Buffer()))
		Safe_Release(pInstance);

	return pInstance;
}

CComponent* Engine::CRcCol::Clone(void)
{
	return new CRcCol(*this);
}

