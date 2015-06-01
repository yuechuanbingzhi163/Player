#ifndef _LIB_CONTAINER_H
#define _LIB_CONTAINER_H



class CLibContainer : public CContainerUI, public IDialogBuilderCallback
{
public:
	CLibContainer(CPaintManagerUI &paint_manager);
	~CLibContainer();
	virtual CControlUI* CreateControl(LPCTSTR pstrClass);
private:
	CDialogBuilder  m_dlgItemBuilder;
	CPaintManagerUI &m_paint_manager;
};


#endif