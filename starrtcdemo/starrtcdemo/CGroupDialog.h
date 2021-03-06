#pragma once
#include "CSqliteDB.h"
#include "XHGroupManager.h"
// CGroupDialog 对话框

class CGroupDialog : public CDialogEx, public IGroupManagerListener, public IGroupGetListListener
{
	DECLARE_DYNAMIC(CGroupDialog)

public:
	CGroupDialog(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CGroupDialog();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_IM_GROUP };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	void getGroupList();
	void getGroupMemberList(string strGroupId);

	void resetGroupList();
	void clearMsgList();
	void getMsgList(string conversationId);
	void resetMsgList();
	void resetGroupMemberList();

	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonCreateGroup();
	afx_msg void OnBnClickedButtonGroupSendMsg();
	afx_msg void OnNMClickListGroupList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnMenuGroupAddMem();
	afx_msg void OnMenuGroupSetRecvmsgStatus();
	afx_msg void OnNMRClickListGroupList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButtonGroupAddMember();
	afx_msg void OnBnClickedButton();
public:
	/**
	 * 获取group list回调函数
	 */
	virtual int applyGetGroupListFin(list<CGroupInfo>& groupInfoList);
	/**
	 * 查询用户列表回调
	 */
	virtual int applyGetUserListFin(list<string>& userList);
	/**
	 * 群成员数发生变化
	 * @param groupID
	 * @param number
	 */
	virtual void onMembersUpdeted(string groupID, int number);

	/**
	 * 自己被移出群组
	 * @param groupID
	 */
	virtual void onSelfKicked(string groupID);

	/**
	 * 群组已经被删除
	 * @param groupID
	 */
	virtual void onGroupDeleted(string groupID);

	/**
	 *  收到消息
	 * @param message
	 */
	virtual void onReceivedMessage(string groupId, CIMMessage* pMessage);

	/**
	 *  创建群组回调
	 * @param message
	 */
	virtual void onApplyCreateGroupFin(string groupID);

	/**
	 *  删除群组回调
	 * @param message
	 */
	virtual void onApplyDelGroupFin(string groupID);

	/**
	 *  添加成员回调
	 * @param message
	 */
	virtual void onApplyAddUserToGroupFin(string groupID);

	/**
	 *  删除成员回调
	 * @param message
	 */
	virtual void onApplyRemoveUserFromGroupFin(string groupID);
public:
	CListCtrl m_groupList;
	CListBox m_recvDataListBox;
	CEdit m_sendMsgEdit;
	list<CMessageBean*> mDatas;
	list<CGroupInfo> mGroupList;
	list<string> mGroupMemberList;
	CGroupInfo* m_pCurrentGroup;
	CSqliteDB* m_pSqliteDB;
	XHGroupManager* m_pGroupManager;
	CStatic m_GroupName;
	CListCtrl m_GroupMemberList;
	afx_msg void OnBnClickedButtonDeleteGroup();
};
