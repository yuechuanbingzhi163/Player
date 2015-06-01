#ifndef _TRY_CONTAINER_H
#define _TRY_CONTAINER_H



class CTryContainer : public CContainerUI, public IDialogBuilderCallback
{
public:
	CTryContainer(CPaintManagerUI &paint_manager);
	~CTryContainer();
	virtual CControlUI* CreateControl(LPCTSTR pstrClass);
private:
	CDialogBuilder  m_dlgItemBuilder;
	CPaintManagerUI &m_paint_manager;
};


#endif