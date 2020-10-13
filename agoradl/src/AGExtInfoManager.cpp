#include "AGExtInfoManager.h"


CAGExtInfoManager *CAGExtInfoManager::m_lpExtInfoManager = NULL;

CAGExtInfoManager::CAGExtInfoManager()
{
}


CAGExtInfoManager::~CAGExtInfoManager()
{
}

CAGExtInfoManager *CAGExtInfoManager::GetAGExtInfoManager()
{
	if (m_lpExtInfoManager == NULL)
		m_lpExtInfoManager = new CAGExtInfoManager();

	return m_lpExtInfoManager;
}

void CAGExtInfoManager::CloseAGExtInfoManager()
{
	if (m_lpExtInfoManager){
		delete m_lpExtInfoManager;
		m_lpExtInfoManager = NULL;
	}
}

void CAGExtInfoManager::AddView(AHANDLE hWnd)
{
	m_wnds.push_back(hWnd);
	auto pos = find(m_wndFreeView.begin(), m_wndFreeView.end(), hWnd);
	if (pos != m_wndFreeView.end())
		return;

	m_wndFreeView.push_back(hWnd);
}

void CAGExtInfoManager::RemoveView(AHANDLE hView)
{
	m_wndFreeView.remove(hView);
}

AHANDLE CAGExtInfoManager::AllocView()
{
	if (m_wndFreeView.empty())
		return NULL;

	AHANDLE hView = m_wndFreeView.front();
	m_wndFreeView.pop_front();

	m_wndBusyView.push_back(hView);

	return hView;
}

void CAGExtInfoManager::FreeView(AHANDLE hView)
{
	auto pos = find(m_wndBusyView.begin(), m_wndBusyView.end(), hView);
	if (pos == m_wndBusyView.end())
		return;

	m_wndBusyView.remove(hView);
	m_wndFreeView.push_back(hView);
}

void CAGExtInfoManager::FreeAllView()
{
	m_wndFreeView.clear();
	//m_wndFreeView.AddTail(&m_wndBusyView);
	m_wndBusyView.clear();
	for (int i = 0; i < m_wnds.size(); i++){
		m_wndFreeView.push_back(m_wnds[i]); 
	}
}

AHANDLE CAGExtInfoManager::GetOneFreeView()
{
	if (m_wndFreeView.empty())
	{
		return nullptr;
	}
	AHANDLE res = m_wndFreeView.front();
	m_wndFreeView.pop_front();
	m_wndBusyView.push_back(res);

	return  res;
}

AHANDLE CAGExtInfoManager::GetFirstView()
{
	auto pos = find(m_wndFreeView.begin(), m_wndFreeView.end(), m_wnds[0]);
	if (pos == m_wndFreeView.end())
		return m_wnds[0];

	m_wndFreeView.remove(m_wnds[0]);
	m_wndBusyView.push_back(m_wnds[0]);

	return  m_wnds[0];
}

AHANDLE CAGExtInfoManager::GetViewAt(int i)
{
	if (i >= m_wnds.size())
		return NULL;

	return m_wnds[i];
}
