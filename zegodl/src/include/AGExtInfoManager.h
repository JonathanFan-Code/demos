#pragma once

#include <list>
#include <vector>

#include "types.h"

using namespace std;
class CAGExtInfoManager
{
protected:
	CAGExtInfoManager();
	~CAGExtInfoManager();

public:
	void AddView(ZHANDLE hWnd);
	void RemoveView(ZHANDLE hView);
	ZHANDLE AllocView();
	void FreeView(ZHANDLE hView);
	void FreeAllView();
	ZHANDLE GetOneFreeView();
	ZHANDLE GetFirstView();
	ZHANDLE GetViewAt(int i);

public:
	static CAGExtInfoManager *GetAGExtInfoManager();
	void CloseAGExtInfoManager();

private:
	static  CAGExtInfoManager	*m_lpExtInfoManager;

private:
	list<ZHANDLE>		m_wndFreeView;
	list<ZHANDLE>		m_wndBusyView;
	vector<ZHANDLE>      m_wnds;
};

