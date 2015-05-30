#ifndef _TAB_TRY_H
#define _TAB_TRY_H

class CTryListUI;
class CTabTryContainerUI : public CContainerUI , public IDialogBuilderCallback
{
public:
	CTabTryContainerUI();
	virtual CControlUI* CreateControl(LPCTSTR pstrClass);
	
private:
	CDialogBuilder  m_dlgItemBuilder;
};

#endif