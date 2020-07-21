#ifndef Export_Utility_h__
#define Export_Utility_h__

#include "Engine_Define.h"
#include "Management.h"
#include "Transform.h"

BEGIN(Engine)

// Management
// Get
inline CComponent*			Get_Component(const _tchar* pLayerTag, const _tchar* pObjTag, const _tchar* pComponentTag,	COMPONENTID eID);
// Set
// General
inline HRESULT	Create_Management(CManagement** ppManagement);

// Release
inline void		Release_Utility(void);

#include "Export_Utility.inl"

END
#endif // Export_Utility_h__
