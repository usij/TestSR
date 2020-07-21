// Management
// Get
CComponent*			Get_Component(const _tchar* pLayerTag, const _tchar* pObjTag, const _tchar* pComponentTag, COMPONENTID eID)
{
	return CManagement::GetInstance()->Get_Component(pLayerTag, pObjTag, pComponentTag, eID);
}
// Set
// General
HRESULT	Create_Management(CManagement** ppManagement)
{
	CManagement*	pManagement = CManagement::GetInstance();

	if (nullptr == pManagement)
		return E_FAIL;

	*ppManagement = pManagement;

	return S_OK;
}

// Release
void		Release_Utility(void)
{
	CManagement::GetInstance()->DestroyInstance();
}