// OCCIWrapper.h: interface for the COCCIWrapper class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_OCCIWRAPPER_H__9447E470_A278_4FD5_B908_82FD5D505235__INCLUDED_)
#define AFX_OCCIWRAPPER_H__9447E470_A278_4FD5_B908_82FD5D505235__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class COCCIWrapper  
{
public:
	COCCIWrapper();
	virtual ~COCCIWrapper();
public:
	// ����ORACLE���ݿ�
	BOOL Connect();
	// �Ͽ�����
	BOOL Disconnect();
	// ����sql��䴴��Statement����
	BOOL createStmt(int count,const char * sql,...);
	// ִ��Statement
	BOOL stmtExecute();
	// ִ��Statement����
	BOOL stmtExecuteUpdate();
	// �ر�Statement
	BOOL closeStmt();
	// ���ݲ�ѯ��ȡ��¼��
	ResultSet *stmtQuery();
	// ��ȡBLOB�ֶεĴ�С
	int getBlobSize(int colIndex);
	// ��ȡBLOB�ֶε�����
	int getBlob(int colIndex,char *blobData);
	// ����BLOB�ֶ�
	BOOL updateBlob(int blobCount,...);
	// �رռ�¼��
	BOOL closeRecordSet();

	// ���� Statement ʹ�����񣬼� setAutoCommit(false)
	BOOL setTransaction();

	// �ύ����
	BOOL Commit();
	// �����ع�
	BOOL Rollback();

// 	BOOL Connect(char *uid, char * pwd, char *sid);

	BOOL isConnected;

	BOOL isInitSucceed;

	const char *errMsg;

// 	string className;
// 	string classCode;
	
private:
	string m_uid;
	string m_pwd;
	string m_sid;
	Environment *env;
	Connection  *conn;

	Statement *stmt;
	ResultSet *rs;
};

#endif // !defined(AFX_OCCIWRAPPER_H__9447E470_A278_4FD5_B908_82FD5D505235__INCLUDED_)
