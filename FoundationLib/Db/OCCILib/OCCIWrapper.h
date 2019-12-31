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
	BOOL createStmtByMultiConditions(string whereConditions,CStringArray *whereValues,CStringArray *types);
	Statement *createStatement(int count,const char * sql,...);
	// ִ��Statement
	BOOL stmtExecute();
	BOOL stmtExecute(Statement *stmt);
	// ִ��Statement����
	BOOL stmtExecuteUpdate();
	BOOL stmtExecuteUpdate(Statement *stmt);
	// �ر�Statement
	BOOL closeStmt();
	BOOL closeStmt(Statement *stmt);
	// ���ݲ�ѯ��ȡ��¼��
	ResultSet *stmtQuery();
	ResultSet *stmtQuery(Statement *stmt);
	// ��ȡBLOB�ֶεĴ�С
	int getBlobSize(int colIndex);
	// ��ȡBLOB�ֶε�����
	int getBlob(int colIndex,unsigned char *blobData);
	// ����BLOB�ֶΣ��ڲ���¼�������next()����
	BOOL updateBlob(int blobCount,...);
	// �رռ�¼��
	BOOL closeRecordSet();
	BOOL closeRecordSet(Statement *stmt, ResultSet *rs);

	// �ύ����
	BOOL Commit();
	// �����ع�
	BOOL Rollback();

// 	BOOL Connect(char *uid, char * pwd, char *sid);

	BOOL isConnected;

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
