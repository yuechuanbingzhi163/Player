#ifndef _TAB_LIBRARY_H
#define _TAB_LIBRARY_H

class CTabLibraryUI : public CContainerUI
{
public:
	CTabLibraryUI();
	BOOL	InitUI();
private:
	CDialogBuilder    m_dlgItemBuilder;
};
#endif // !_TAB_LIBRARY_H
