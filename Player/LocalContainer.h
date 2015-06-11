#ifndef _LOCAL_CONTAINER_H
#define _LOCAL_CONTAINER_H


class CLocalContainer : public CContainerUI , public IDialogBuilderCallback
{
public:
	CLocalContainer(CPaintManagerUI& paint_manager);
	~CLocalContainer();
	CControlUI* CreateControl(LPCTSTR pstrClass);

private:
	CPaintManagerUI& m_paint_manager;
	CDialogBuilder  m_dlgItemBuilder;
};

#endif