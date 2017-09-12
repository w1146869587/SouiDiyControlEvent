/*******************************************************************   
 *  �ļ�����: TestControl.h
 *  ��Ҫ����: ���Կؼ��࣬��Ҫ���������Զ����¼�����
 *   
 *  ��������: 2017-9-12
 *  ��������: ��Ө
 *  ˵������: 
 *   
 *  �޸�����: 
 *  ��������: 
 *  ˵������: 
 ******************************************************************/  
#pragma once

namespace SOUI
{
// �Զ����¼���Ϣ
#define EVT_TEST_CONTROL (SOUI::EVT_EXTERNAL_BEGIN + 400)

class EventTestControl : public TplEventArgs<EventTestControl>
{
	SOUI_CLASS_NAME(EventTestControl, L"on_test_constrol")
public:
	EventTestControl(SOUI::SWindow* pSender) : TplEventArgs<EventTestControl>(pSender)
	{

	}
	enum { EventID = EVT_TEST_CONTROL };

	INT nIndex;
};
	
// �Զ�����Կؼ�
class STestControl : public SWindow
{
	SOUI_CLASS_NAME(STestControl, L"testcontrol")
public:
	STestControl();
	virtual ~STestControl();

protected:
	// �����ؼ�����ʼ�� xml�����¼��ȵ�
	int OnCreate(LPCREATESTRUCT lpCreateStruct);

	// ����ؼ� xml ����
	SOUI_ATTRS_BEGIN()
	SOUI_ATTRS_END()

	// ��Ӧ�ؼ�������Ϣ
	SOUI_MSG_MAP_BEGIN()
		MSG_WM_CREATE(OnCreate)
	SOUI_MSG_MAP_END()

private:
	// ��ť�����Ӧ
	bool OnBtnClick(SOUI::EventArgs* pEvt);
};

}