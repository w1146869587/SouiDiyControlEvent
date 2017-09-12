#include "stdafx.h"
#include "TestControl.h"

namespace SOUI
{

STestControl::STestControl()
{
	m_evtSet.addEvent(EVENTID(EventTestControl));
}

STestControl::~STestControl()
{

}

// �����ؼ�����ʼ�� xml�����¼��ȵ�
int STestControl::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	pugi::xml_document xmlDoc;
	SOUI::SStringW strXml = L"test_control";

	if (!LOADXML(xmlDoc, strXml, L"LAYOUT")) {
		return E_FAIL;
	}
	pugi::xml_node itemXmlNode = xmlDoc.child(L"testcontrol");
	if (!itemXmlNode) {
		return E_FAIL;
	}
	this->CreateChildren(itemXmlNode);

	// ��������ť������¼�
	for (UINT i = 0; i < 2; ++i) {
		SOUI::SStringW strXmlName;
		strXmlName.Format(L"btn_%d", i + 1);
		SOUI::SButton* pButton =
			FindChildByName2<SOUI::SButton>(strXmlName);
		assert(pButton != NULL);
		pButton->GetEventSet()->subscribeEvent(SOUI::EVT_CMD,
			Subscriber(&STestControl::OnBtnClick, this));
	}
	return 0;
}

// ��ť�����Ӧ
bool STestControl::OnBtnClick(SOUI::EventArgs* pEvt)
{
	// ��ȡ��ť���ƣ���ȡ��׺����
	SOUI::SWindow* pButton =
		SOUI::sobj_cast<SOUI::SWindow>(pEvt->sender);
	assert(pButton != NULL);
	SOUI::SStringW strName = pButton->GetName();
	SOUI::SStringW strIndex = strName.Right(1);
	INT nIndex = _wtoi(strIndex);

	// ����ȫ�ֵ��Զ�����Ϣ
	EventTestControl evt(this);
	evt.nIndex = nIndex;
	FireEvent(evt);	// �����¼� Fire!!!
	return true;
}

}