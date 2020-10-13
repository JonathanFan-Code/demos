#pragma once

#include<list>
#include<vector>
#include "types.h"

using namespace std;
class CAGExtInfoManager
{
protected:
	CAGExtInfoManager();
	~CAGExtInfoManager();

public:
	void AddView(AHANDLE hWnd);
	void RemoveView(AHANDLE hView);
	AHANDLE AllocView();
	void FreeView(AHANDLE hView);
	void FreeAllView();
	AHANDLE GetOneFreeView();
	AHANDLE GetFirstView();
	AHANDLE GetViewAt(int i);

public:
	static CAGExtInfoManager *GetAGExtInfoManager();
	void CloseAGExtInfoManager();

private:
	static  CAGExtInfoManager	*m_lpExtInfoManager;

private:
	list<AHANDLE>		m_wndFreeView;
	list<AHANDLE>		m_wndBusyView;
	vector<AHANDLE>      m_wnds;
};

