// OCCIWrapper.cpp: implementation of the COCCIWrapper class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OCCIWrapper.h"
#include "DbConfig.h"
#include <C++\FoudationLib\LogLib\Remark.h>
#include <c++\foudationlib\exception\myexception.h>

extern CRemark remark;
// extern CLogList logs;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

// env
// conn
// stmt
// rs

// һ���ʹ��˳��

// 1��ִ�л�ִ�и�������
// ����Statement
// ִ�л�ִ�и���
// �ر�Statement
// �ر�����

// 2����ѯ
// ����Statement
// ��ѯ��ȡ��¼��
// ��������˼�¼���еļ�¼����ִ�и���
// �رռ�¼��
// �ر�Statement
// �ر�����


// ���û���ӣ����ؼ�
// ���û��sql�����ؼ�
// ���û��stmt�����ؼ�
// ���û��rs�����ؼ�

COCCIWrapper::COCCIWrapper()
: env(0),conn(0),stmt(0),rs(0),isConnected(FALSE),errMsg(0)
{
// 	memset(m_uid,0x00,32);
// 	memset(m_pwd,0x00,32);
// 	memset(m_sid,0x00,32);
// 	env  = NULL;
// 	conn = NULL;

// 	className="COCCIWrapper";
// 	classCode="03";
	
	CDbConfig config;
// 	remark.doLog("�������ļ���ȡ���ݿ����ӵ��û��������");
	m_uid=config.getUserName();
	m_pwd=config.getPwd();
	m_sid=config.getOraName();

	string msg="�û�����"+m_uid+"�����룺"+m_pwd+"��SID��"+m_sid;
	remark.doLog(LOGLEVEL_SHOWINFO,msg);

// 	remark.doLog("�û���Ϊ��"+m_uid);
// 	remark.doLog("����Ϊ��"+m_pwd);
// 	remark.doLog("Ora��Ϊ��"+m_sid);

	if(m_uid=="" || m_pwd=="" || m_sid=="")
	{
		remark.doLog(LOGLEVEL_SHOWERROR,"��ȡ���ݿ�������Ϣʧ�ܣ��û����������SIDΪ�գ�");
//		throw CMyException("e","0",className,classCode,className,"00","01","��ȡ���ݿ�������Ϣʧ�ܣ�","�����ļ������ڣ��������ļ���ʽ����ȷ��",1);
// 		throw CException(EXCEPTION_INTERNAL,"��ȡ���ݿ�������Ϣʧ�ܣ�","�����ļ������ڣ��������ļ���ʽ����ȷ��");
// 		exit(-1);
	}
}

COCCIWrapper::~COCCIWrapper()
{
	m_uid="";
	m_pwd="";
	m_sid="";
	Disconnect();
}

// ����ORACLE���ݿ�
BOOL COCCIWrapper::Connect()
{
// 	try
// 	{
		remark.doLog(LOGLEVEL_SHOWINFO,"�������ݿ⻷��");
		env = Environment::createEnvironment (Environment::DEFAULT);
		if(!env)
		{
// 			remark.doLog("�������ݿ�ʧ�ܣ���ȡOracle��������Ϊ�գ�");
// 			throw CMyException("e","0",className,classCode,"Connect","01","01","�������ݿ�ʧ�ܣ�","��ȡOracle��������Ϊ�գ�",1);
			throw CMyException(EXCEPTION_INTERNAL,"�������ݿ�ʧ�ܣ�","��ȡOracle��������Ϊ�գ�");
// 			exit(-1);
		}
		//if(env==NULL) {	printf("%s","Can not create env!\n");return FALSE;}

		remark.doLog(LOGLEVEL_SHOWINFO,"�������ݿ�����");
		conn = env->createConnection (m_uid, m_pwd, m_sid);
		if(!conn)
		{
// 			remark.doLog("�������ݿ�ʧ�ܣ�ConnectionΪ�գ�");
// 			throw CMyException("e","0",className,classCode,"Connect","01","02","�������ݿ�ʧ�ܣ�","ConnectionΪ�գ�",1);
			throw CMyException(EXCEPTION_INTERNAL,"�������ݿ�ʧ�ܣ�","ConnectionΪ�գ�");
// 			exit(-1);
		}

		//if(conn==NULL){	printf("%s","Can not create connection !\n");return TRUE;}
// 	}
// 	catch(SQLException *e)
// 	{
// 		string msg;
// 		msg="����ʧ�ܣ�\n\nԭ��Ϊ��\n" + e->getMessage();
// // 		remark.doLog(msg.c_str());
// //		AfxMessageBox(msg.c_str());
// 		if(conn)
// 		{
// 			env->terminateConnection(conn);
// 			conn=NULL;
// 		}
// 		if(env)
// 		{
// 			env->terminateEnvironment(env);
// 			env=NULL;
// 		}
// 		return FALSE;
// 	}
// 	catch(...)
// 	{
// 		string msg;
// 		msg="����ʧ�ܣ�\n\nδ֪ԭ��\n";
// // 		remark.doLog("����ʧ�ܣ�δ֪ԭ��");
// //		AfxMessageBox(msg.c_str());
// 		if(conn)
// 		{
// 			env->terminateConnection(conn);
// 			conn=NULL;
// 		}
// 		if(env)
// 		{
// 			env->terminateEnvironment(env);
// 			env=NULL;
// 		}
// 		return FALSE;
// 	}

	isConnected=TRUE;
	return true;
}

// �Ͽ�����
BOOL COCCIWrapper::Disconnect()
{
//	if(env==NULL || conn == NULL){return FALSE;}
	if(conn)
	{
		remark.doLog(LOGLEVEL_SHOWDEBUG,"�ر����ݿ�����");
		env->terminateConnection (conn);
		conn=NULL;		
	}
	if(env)
	{
		remark.doLog(LOGLEVEL_SHOWDEBUG,"�ر����ݿ⻷��");
		Environment::terminateEnvironment (env);
		env=NULL;
	}
	isConnected=FALSE;
	return TRUE;
}

// ����sql��䴴��Statement����
BOOL COCCIWrapper::createStmt(int count,const char * sql,...)
{
// 	try
// 	{
		if(!conn) return FALSE;
		if(stmt)
		{
			remark.doLog(LOGLEVEL_SHOWDEBUG,"�ر������򿪵� Statement");
			conn->terminateStatement(stmt);
			stmt=NULL;
		}

		remark.doLog(LOGLEVEL_SHOWDEBUG,"���� Statement");
		stmt = conn->createStatement (sql);
		if(!stmt)
		{
 			remark.doLog(LOGLEVEL_SHOWERROR,"����Statementʧ�ܣ�");
// 			throw CMyException("e","0",className,classCode,"createStmt","02","01","����Statementʧ�ܣ�","",1);
 			throw CMyException(EXCEPTION_INTERNAL,"����Statementʧ�ܣ�","createStmt");
// 			exit(-1);
			return FALSE;
		}

// 		const char *tmp = sql;
// 		int icount = 0 ;
// 		while(*tmp)
// 		{
// 			if(*tmp++ == ':' ) icount +=2; 
// 		}

		remark.doLog(LOGLEVEL_SHOWDEBUG,"�򴴽��� Statement ��д��ֵ");
		va_list argptr;     //�����������
		va_start(argptr,sql);//��ʼ�����marker����

		for(int i = 1 ; i <= count ; i ++ )
		{
			char *s = va_arg( argptr, char* );
			if(!s)
			{
				remark.doLog(LOGLEVEL_SHOWERROR,"CreateStmt �������󣡿�����©д�˱��������ͣ�Ҳ�����ǿɱ�����ĸ�����ָ���ĸ�����ƥ�䣡");
				closeStmt();
				return FALSE;
			}
			switch (*s)
			{
			case 'S':
			case 's':
				stmt->setString (i,va_arg( argptr, char* ));
				//printf("%s\n",va_arg( argptr, char* ));
				break;
			case 'N':
			case 'n':
				stmt->setInt(i,va_arg( argptr, int ));
				//printf("%d\n",va_arg( argptr,int ));
				break;
			default:
				{
					//printf("unknown para type %s \n" ,s);
					va_end(argptr);//��������va_start����
					closeStmt();
					remark.doLog(LOGLEVEL_SHOWERROR,"Statement��������δ֪����");
// 					throw CMyException("e","0",className,classCode,"createStmt","02","02","��������","δ֪����",1);
 					throw CMyException(EXCEPTION_INTERNAL,"���� Statement �Ĳ�������","δ֪����");
//					exit(-1);
					return FALSE;
				}
			}
		}
		va_end(argptr);//��������va_start����
// 	}
// 	catch(SQLException e)
// 	{
// 		//errMsg=e.getMessage().c_str();
// 		printf("CreateStmt error!\n errnum %d errmsg %s\n",e.getErrorCode(),e.getMessage().c_str());
// 		closeStmt();
// 		return FALSE;
// 	}
// // 	catch(CMyException *e)
// // 	{
// // // 		e->showDebugMessage();
// // 		closeStmt();
// // 		return FALSE;
// // 	}
// 	catch(...)
// 	{
// 		errMsg="CreateStmt error : Unknown error.\n";
// 		printf(errMsg);
// 		closeStmt();
// 		return FALSE;
// 	}
	return TRUE;
}

Statement *COCCIWrapper::createStatement(int count,const char * sql,...)
{
	remark.doLog(LOGLEVEL_SHOWDEBUG,"���� Statement");
	Statement *stmt = conn->createStatement (sql);
	if(!stmt)
	{
		remark.doLog(LOGLEVEL_SHOWERROR,"����Statementʧ�ܣ�");
		return FALSE;
	}

	remark.doLog(LOGLEVEL_SHOWDEBUG,"�򴴽��� Statement ��д��ֵ");
	va_list argptr;     //�����������
	va_start(argptr,sql);//��ʼ�����marker����

	for(int i = 1 ; i <= count ; i ++ )
	{
		char *s = va_arg( argptr, char* );
		if(!s)
		{
			remark.doLog(LOGLEVEL_SHOWERROR,"CreateStmt �������󣡿�����©д�˱��������ͣ�Ҳ�����ǿɱ�����ĸ�����ָ���ĸ�����ƥ�䣡");
			break;
		}
		switch (*s)
		{
		case 'S':
		case 's':
			stmt->setString (i,va_arg( argptr, char* ));
			//printf("%s\n",va_arg( argptr, char* ));
			break;
		case 'N':
		case 'n':
			stmt->setInt(i,va_arg( argptr, int ));
			//printf("%d\n",va_arg( argptr,int ));
			break;
		default:
			{
				//printf("unknown para type %s \n" ,s);
				va_end(argptr);//��������va_start����
				closeStmt();
				remark.doLog(LOGLEVEL_SHOWERROR,"Statement��������δ֪����");
				return FALSE;
			}
		}
	}
	va_end(argptr);//��������va_start����
	return stmt;
}

// ִ��Statement
BOOL COCCIWrapper::stmtExecute()
{
	if(!stmt)
		throw CMyException(EXCEPTION_INTERNAL,"�޷��������ݿ�ִ�з�����","Statement ָ��Ϊ�գ�");
// 	try
// 	{
		if(stmt)
		{
			remark.doLog(LOGLEVEL_SHOWDEBUG,"�������ݿ�ִ�з���");
			stmt->execute();
		}
// 	}
// 	catch(SQLException e)
// 	{
// 		//errMsg=e.getMessage().c_str();
// 		CString errMsg;
// 		errMsg.Format("StmtExecute error!\n errnum %d errmsg %s\n",e.getErrorCode(),e.getMessage().c_str());
// //		AfxMessageBox(errMsg);
// // 		printf("StmtExecute error!\n errnum %d errmsg %s\n",e.getErrorCode(),e.getMessage().c_str());
// 		closeStmt();
// 		return FALSE;
// 	}
// 	catch(...)
// 	{
// 		errMsg="StmtExecute error : Unknown error.\n";
// 		printf(errMsg);
// 		closeStmt();
// 		return FALSE;
// 	}
	return TRUE;
}

BOOL COCCIWrapper::stmtExecute(Statement *stmt)
{
	if(!stmt)
		return FALSE;

	remark.doLog(LOGLEVEL_SHOWDEBUG,"�������ݿ�ִ�з���");
	stmt->execute();
	return TRUE;
}

// ִ��Statement����
BOOL COCCIWrapper::stmtExecuteUpdate()
{
	if(!stmt)
		throw CMyException(EXCEPTION_INTERNAL,"�޷��������ݿ�� ִ�и��� ������","Statement ָ��Ϊ�գ�");
// 	try
// 	{
		if(stmt)
		{
			remark.doLog(LOGLEVEL_SHOWDEBUG,"�������ݿ�� ִ�и��� ����");
			stmt->executeUpdate();
		}
// 	}
// 	catch(SQLException e)
// 	{
// 		//errMsg=e.getMessage().c_str();
// 		printf("StmtExecuteUpdate error!\n errnum %d errmsg %s\n",e.getErrorCode(),e.getMessage().c_str());
// 		closeStmt();
// 		return FALSE;
// 	}
// 	catch(...)
// 	{
// 		errMsg="StmtExecuteUpdate error : Unknown error.\n";
// 		printf(errMsg);
// 		closeStmt();
// 		return FALSE;
// 	}
	return TRUE;
}

BOOL COCCIWrapper::stmtExecuteUpdate(Statement *stmt)
{
	if(!stmt)
		return FALSE;

	remark.doLog(LOGLEVEL_SHOWDEBUG,"�������ݿ�� ִ�и��� ����");
	stmt->executeUpdate();
	return TRUE;
}

// �ر�Statement
BOOL COCCIWrapper::closeStmt()
{
// 	try
// 	{
		if(conn)
			if(stmt)
			{
				if(rs)
				{
					remark.doLog(LOGLEVEL_SHOWDEBUG,"�ر� Statement ǰ�ȹرռ�¼��");
					stmt->closeResultSet(rs);
					rs=NULL;
				}
				remark.doLog(LOGLEVEL_SHOWDEBUG,"�ر� Statement");
				conn->terminateStatement(stmt);
				stmt=NULL;
			}
// 	}
// 	catch(SQLException e)
// 	{
// 		//errMsg=e.getMessage().c_str();
// 		printf("CloseStmt error!\n errnum %d errmsg %s\n",e.getErrorCode(),e.getMessage().c_str());
// 		if(stmt)
// 		{
// 			conn->terminateStatement(stmt);
// 			stmt=NULL;
// 		}
// 		return FALSE;
// 	}
// 	catch(...)
// 	{
// 		errMsg="CloseStmt error : Unknown error.\n";
// 		printf(errMsg);
// 		if(stmt)
// 		{
// 			conn->terminateStatement(stmt);
// 			stmt=NULL;
// 		}
// 		return FALSE;
// 	}
	return TRUE;
}

BOOL COCCIWrapper::closeStmt(Statement *stmt)
{
	if(conn)
		if(stmt)
		{
			remark.doLog(LOGLEVEL_SHOWDEBUG,"�ر� Statement");
			conn->terminateStatement(stmt);
			stmt=NULL;
		}

		return TRUE;
}

// ���ݲ�ѯ��ȡ��¼��
ResultSet *COCCIWrapper::stmtQuery()
{
	if(!stmt) return NULL;

// 	try
// 	{
		if(rs)
		{
			remark.doLog(LOGLEVEL_SHOWDEBUG,"�ر� Statement ǰ�ȹرռ�¼��");
			stmt->closeResultSet(rs);
			rs=NULL;
		}
		remark.doLog(LOGLEVEL_SHOWDEBUG,"ִ�����ݿ��ѯ");
		rs=stmt->executeQuery();
// 	}
// 	catch(SQLException e)
// 	{
// 		//errMsg=e.getMessage().c_str();
// 		printf("StmtQuery error!\n errnum %d errmsg %s\n",e.getErrorCode(),e.getMessage().c_str());
// 		closeRecordSet();
// 		closeStmt();
// 		return NULL;
// 	}
// 	catch(...)
// 	{
// 		errMsg="StmtQuery error : Unknown error.\n";
// 		printf(errMsg);
// 		closeRecordSet();
// 		closeStmt();
// 		return NULL;
// 	}
	return rs;
}

ResultSet *COCCIWrapper::stmtQuery(Statement *stmt)
{
	if(!stmt)
		return NULL;

	remark.doLog(LOGLEVEL_SHOWDEBUG,"ִ�����ݿ��ѯ");
	ResultSet *rs=stmt->executeQuery();
	return rs;
}

BOOL COCCIWrapper::createStmtByMultiConditions(string whereConditions,CStringArray *whereValues,CStringArray *types)
{
	// 	try
	// 	{
	if(!conn) return FALSE;
	if(stmt)
	{
		remark.doLog(LOGLEVEL_SHOWDEBUG,"�ر������򿪵� Statement");
		conn->terminateStatement(stmt);
		stmt=NULL;
	}
	
	remark.doLog(LOGLEVEL_SHOWDEBUG,"���� Statement");
	stmt = conn->createStatement(whereConditions.c_str());
	if(!stmt)
	{
		remark.doLog(LOGLEVEL_SHOWERROR,"����Statementʧ�ܣ�");
		// 			throw CMyException("e","0",className,classCode,"createStmt","02","01","����Statementʧ�ܣ�","",1);
		throw CMyException(EXCEPTION_INTERNAL,"����Statementʧ�ܣ�","createStmt");
		// 			exit(-1);
		return FALSE;
	}
	
	remark.doLog(LOGLEVEL_SHOWDEBUG,"�򴴽��� Statement ��д��ֵ");

	int count=whereValues->GetSize();
	
	for(int i = 1 ; i <= count ; i ++ )
	{
		char *s = (LPTSTR)(LPCTSTR)types->GetAt(i-1);
		if(!s)
		{
			remark.doLog(LOGLEVEL_SHOWERROR,"createStmtByMultiConditions ��������types �а������ַ��");
			closeStmt();
			return FALSE;
		}
		switch (*s)
		{
		case 'S':
		case 's':
			{
				CString tmp=whereValues->GetAt(i-1);
				stmt->setString(i,tmp.GetBuffer(tmp.GetLength()));
				//printf("%s\n",va_arg( argptr, char* ));
				break;
			}
		case 'N':
		case 'n':
		{
			CString tmp=whereValues->GetAt(i-1);
			int ntmp=atol((LPTSTR)(LPCTSTR)tmp);
			stmt->setInt(i,ntmp);
			//printf("%d\n",va_arg( argptr,int ));
			break;
		}
		default:
			{
				//printf("unknown para type %s \n" ,s);
				closeStmt();
				remark.doLog(LOGLEVEL_SHOWERROR,"types ����δ֪����");
				// 					throw CMyException("e","0",className,classCode,"createStmt","02","02","��������","δ֪����",1);
				throw CMyException(EXCEPTION_INTERNAL,"��ѯ��������","δ֪����");
				//					exit(-1);
				return FALSE;
			}
		}
	}

	// 	}
	// 	catch(SQLException e)
	// 	{
	// 		//errMsg=e.getMessage().c_str();
	// 		printf("CreateStmt error!\n errnum %d errmsg %s\n",e.getErrorCode(),e.getMessage().c_str());
	// 		closeStmt();
	// 		return FALSE;
	// 	}
	// // 	catch(CMyException *e)
	// // 	{
	// // // 		e->showDebugMessage();
	// // 		closeStmt();
	// // 		return FALSE;
	// // 	}
	// 	catch(...)
	// 	{
	// 		errMsg="CreateStmt error : Unknown error.\n";
	// 		printf(errMsg);
	// 		closeStmt();
	// 		return FALSE;
	// 	}
	return TRUE;
}

// ��ȡBLOB�ֶεĴ�С
int COCCIWrapper::getBlobSize(int colIndex)
{
	if(colIndex<=0) return -1;
	if(!rs) return -1;

	int blobLength=0;

	// 	try
	// 	{
	// ͨ�����ú�����������������
	// 		if(!rs->next()) return -1;

	Blob blob;
	remark.doLog(LOGLEVEL_SHOWDEBUG,"��ȡ BLOB ��С");
	blob=rs->getBlob(colIndex);

	if(blob.isNull())
	{
		remark.doLog(LOGLEVEL_SHOWERROR,"BLOB �ֶ�Ϊ�գ�");
		return -1;
	}

	if(!blob.isInitialized())
	{
		remark.doLog(LOGLEVEL_SHOWERROR,"BLOG �ֶ�δ��ʼ����");
		return -1;
	}

	blobLength=blob.length();
	if(blobLength<0)
	{
		remark.doLog(LOGLEVEL_SHOWERROR,"BLOB �ֶδ�СΪ����");
		return -1;
	}
// 		blob.read(blobLength,blobData,blobLength);

	// 	}
	// 	catch(SQLException e)
	// 	{
	// 		CString s=e.getMessage().c_str();
	// 		AfxMessageBox(s);
	// 		printf("GetBlob error!\n errnum %d errmsg %s\n",e.getErrorCode(),e.getMessage().c_str());
	// 		closeRecordSet();
	// 		closeStmt();
	// 		return -1;
	// 	}
	// 	catch(...)
	// 	{
	// 		errMsg="GetBlob error : Unknown error.\n";
	// 		printf(errMsg);
	// 		closeRecordSet();
	// 		closeStmt();
	// 		return -1;
	// 	}

	return blobLength;
}

// ��ȡBLOB�ֶε�����
int COCCIWrapper::getBlob(int colIndex,unsigned char *blobData)
{
	if(colIndex<=0) return -1;
	if(!blobData) return -1;
	if(!rs) return -1;

	int blobLength=0;

// 	try
// 	{
		// ͨ�����ú�����������������
// 		if(!rs->next()) return -1;

		Blob blob;
		remark.doLog(LOGLEVEL_SHOWDEBUG,"��ȡ BLOB ");
		blob=rs->getBlob(colIndex);

		if(blob.isNull())
		{
			remark.doLog(LOGLEVEL_SHOWERROR,"BLOB �ֶ�Ϊ�գ�");
			return -1;
		}

		if(!blob.isInitialized())
		{
			remark.doLog(LOGLEVEL_SHOWERROR,"BLOG �ֶ�δ��ʼ����");
			return -1;
		}

		blobLength=blob.length();
		
		if(blobLength<0)
		{
			remark.doLog(LOGLEVEL_SHOWERROR,"BLOB �ֶδ�СΪ����");
			return -1;
		}
// 		if(!blob.isNull())
// 			if(blob.isInitialized())
// 			{
// 				blobLength=blob.length();
// 				if(blobLength>0)

		if(blobLength==0)
		{
// 			remark.doLog((LOGLEVEL_SHOWWARNING,"BLOB �ֶγ���Ϊ 0��"))
			return -1;
		}
		
		blob.read(blobLength,blobData,blobLength);

		// 			}
// 	}
// 	catch(SQLException e)
// 	{
// 		CString s=e.getMessage().c_str();
// 		AfxMessageBox(s);
// 		printf("GetBlob error!\n errnum %d errmsg %s\n",e.getErrorCode(),e.getMessage().c_str());
// 		closeRecordSet();
// 		closeStmt();
// 		return -1;
// 	}
// 	catch(...)
// 	{
// 		errMsg="GetBlob error : Unknown error.\n";
// 		printf(errMsg);
// 		closeRecordSet();
// 		closeStmt();
// 		return -1;
// 	}

	return blobLength;
}

// ����BLOB��ʹ�����ڲ���rs��¼������ֱ�������ƶ�һ��
// �ϲ���벻��Ҫ�ƶ�һ����
BOOL COCCIWrapper::updateBlob(int blobCount,...)
{
	if(blobCount<=0) return FALSE;
	if(!rs) return FALSE;

	int skipBlob=0;

// 	try
// 	{
		if(!rs->next()) return FALSE;

		remark.doLog(LOGLEVEL_SHOWDEBUG,"����BLOB");
		va_list argptr;     //�����������
		va_start(argptr,blobCount);//��ʼ�����marker����

		Blob blob;
		int blobLen=0;

		for(int i=1;i<=blobCount;i++)
		{
			blobLen = va_arg( argptr, int );
			if(blobLen<=0)
			{
				remark.doLog(LOGLEVEL_SHOWDEBUG,"��Blob���ȷ�����������");
				skipBlob++;
				va_arg( argptr, unsigned char* );
				continue;
// 				remark.doLog(LOGLEVEL_SHOWERROR,"Blob���ȷ�����");
//				throw CMyException("e","0",className,classCode,"UpdateBlob","03","01","����Blobʧ�ܣ�","Blob���ȷ�����",1);
// 				closeRecordSet();
// 				closeStmt();
// 				exit(-1);
// 				va_end(argptr);//��������va_start����
// 				return FALSE;
			}
			blob=rs->getBlob(i);
			blob.write(blobLen,va_arg( argptr, unsigned char* ),blobLen);
		}

		remark.doLog(LOGLEVEL_SHOWDEBUG,"Blob �������");
		va_end(argptr);//��������va_start����

// 	}
// 	catch(SQLException e)
// 	{
// 		//errMsg=e.getMessage().c_str();
// 		printf("UpdateBlob error!\n errnum %d errmsg %s\n",e.getErrorCode(),e.getMessage().c_str());
// 		closeRecordSet();
// 		closeStmt();
// 		return FALSE;
// 	}
// 	catch(...)
// 	{
// 		errMsg="UpdateBlob error : Unknown error.\n";
// 		printf(errMsg);
// 		closeRecordSet();
// 		closeStmt();
// 		return FALSE;
// 	}
	
	return TRUE;
}

// �رռ�¼��
BOOL COCCIWrapper::closeRecordSet()
{
	if(stmt)
		if(rs)
		{
// 			try
// 			{
			remark.doLog(LOGLEVEL_SHOWDEBUG,"�رռ�¼��");
				stmt->closeResultSet(rs);
				rs=NULL;
// 			}
// 			catch(SQLException e)
// 			{
// 				//errMsg=e.getMessage().c_str();
// 				printf("CloseResultSet error!\n errnum %d errmsg %s\n",e.getErrorCode(),e.getMessage().c_str());
// 				rs=NULL;
// 				closeStmt();
// 				return FALSE;
// 			}
// 			catch(...)
// 			{
// 				errMsg="CloseResultSet error : Unknown error.\n";
// 				printf(errMsg);
// 				rs=NULL;
// 				closeStmt();
// 				return FALSE;
// 			}
		}
		
	return TRUE;
}

BOOL COCCIWrapper::closeRecordSet(Statement *stmt, ResultSet *rs)
{
	if(stmt)
		if(rs)
		{
			remark.doLog(LOGLEVEL_SHOWDEBUG,"�رռ�¼��");
			stmt->closeResultSet(rs);
			rs=NULL;
		}

		return TRUE;
}

BOOL COCCIWrapper::Commit()
{	
	if (!conn) return FALSE;
	
// 	try
// 	{
	remark.doLog(LOGLEVEL_SHOWDEBUG,"���ݿ������ύ");
		conn->commit();
// 	}
// 	catch(SQLException e)
// 	{
// 		printf("Insert2table errnum %d errmsg %s\n",e.getErrorCode(),e.getMessage());
// 		return FALSE;
// 	}
	return TRUE;
}

BOOL COCCIWrapper::Rollback()
{
	if(!conn) return FALSE;
	
// 	try
// 	{
	remark.doLog(LOGLEVEL_SHOWDEBUG,"���ݿ�����ع�");
		conn->rollback();
// 	}
// 	catch(SQLException e)
// 	{
// 		printf("Insert2table errnum %d errmsg %s\n",e.getErrorCode(),e.getMessage());
// 		return FALSE;
// 	}
	return TRUE;
}

// BOOL COCCIWrapper::Insert(const char *sql, ...)
// {
// // 'S' string 'N' number
// 	if(!sql) return FALSE;
// 	const char *tmp = sql;
// 	int icount = 0 ;
// 	while(*tmp)
// 	{
// 		if(*tmp++ == ':' ) icount +=2; 
// 	}
// 	Statement *stmt;
// 	try
// 	{
// 		if(!conn) return FALSE;
// 		stmt = conn->createStatement (sql);
// 		if(!stmt)
// 		{
// 			throw CMyException("e","0",className,classCode,"Insert","02","01","����ʧ�ܣ�","����Statementʧ�ܣ�",1);
// 			exit(-1);
// 			return FALSE;
// 		}
// 		va_list argptr;     //�����������
// 		va_start(argptr,sql);//��ʼ�����marker����
// 		for(int i = 1 ; i <= icount/2 ; i ++ )
// 		{
// 			char *s = va_arg( argptr, char* );
// 			switch (*s)
// 			{
// 			case 'S':
// 			case 's':
// 				stmt->setString (i,va_arg( argptr, char* ));
// 				//printf("%s\n",va_arg( argptr, char* ));
// 				break;
// 			case 'N':
// 			case 'n':
// 				stmt->setInt(i,va_arg( argptr, int ));
// 				//printf("%d\n",va_arg( argptr,int ));
// 				break;
// 			default:
// 				{
// 					throw CMyException("e","0",className,classCode,"Insert","02","02","��������","δ֪����",1);
// 					//printf("unknown para type %s \n" ,s);
// 					va_end(argptr);//��������va_start����
// 					conn->terminateStatement (stmt);
// 					exit(-1);
// 					return FALSE;
// 				}
// 			}
// 		}
// 		stmt->execute();
// 		va_end(argptr);//��������va_start����
// 	}
// 	catch(SQLException e)
// 	{
// 		errMsg=e.getMessage().c_str();
// 		printf("Insert2table errnum %d errmsg %s\n",e.getErrorCode(),e.getMessage().c_str());
// 		conn->terminateStatement (stmt);
// 		return FALSE;
// 	}
// 	catch(...)
// 	{
// 		errMsg="Insert2table error : Unknown error.\n";
// 		printf(errMsg);
// 		conn->terminateStatement (stmt);
// 		return FALSE;
// 	}
// 	conn->terminateStatement (stmt);
// 	return TRUE;
// }
// 
// BOOL COCCIWrapper::Update(const char *sql, ...)
// {
// 	if(!sql) return FALSE;
// 
// 	const char * tmp = sql;
// 	int icount = 0 ;
// 	while(*tmp)
// 	{
// 		if(*tmp++ == ':' ) icount +=2;
// 	}
// 
// 	Statement *stmt;
// 	try
// 	{
// 		if(!conn) return FALSE;
// 		stmt = conn->createStatement (sql);
// 		if(!stmt)
// 		{
// 			throw CMyException("e","0",className,classCode,"Update","03","01","����ʧ�ܣ�","����Statementʧ�ܣ�",1);
// 			exit(-1);
// 			return FALSE;
// 		}
// 		va_list argptr;     //�����������
// 		va_start(argptr,sql);//��ʼ�����marker����
// // 		Blob *pblob;
// 	//	int k;
// 		for(int i = 1 ; i <= icount/2 ; i ++ )
// 		{
// 			char *s = va_arg( argptr, char* );
// 			int tmp = 0 ;
// 			switch (*s)
// 			{
// 			case 'S':
// 			case 's':
// 				stmt->setString (i,va_arg( argptr, char* ));
// 				//printf("%s\n",va_arg( argptr, char* ));
// 				break;
// 			case 'N':
// 			case 'n':
// 				stmt->setInt(i,va_arg( argptr, int ));
// 				//printf("%d\n",va_arg( argptr,int ));
// 				break;
// // 			case 'B':
// // 			case 'b':
// // 				//stmt->setAutoCommit(true);
// // 				tmp = va_arg( argptr, int );
// // 				pblob = new Blob(conn);
// // 				if(!pblob) return FALSE;
// // 				*pblob=stmt->getBlob(i);
// // 				pblob->setEmpty();
// // 	// 			k = pblob->isInitialized();
// // 	// 			k = pblob->isOpen();
// // 	// 			k= pblob->length();
// // 				pblob->write(tmp,va_arg( argptr, unsigned char* ),tmp);
// // 				stmt->setBlob(i,*pblob);
// // 				i--;
// // 				pblob->close();
// // 				delete pblob;
// // 				//printf("%s\n",va_arg( argptr, char* ));
// // 				break;
// 			default:
// 				{
// 					throw CMyException("e","0",className,classCode,"Update","03","01","��������","δ֪����",1);
// 					//printf("unknown para type %s \n" ,s);
// 					va_end(argptr);//��������va_start����
// 					conn->terminateStatement (stmt);
// 					exit(-1);
// 					return FALSE;
// 				}
// 			}
// 		}
// 		va_end(argptr);//��������va_start����
// 		stmt->executeUpdate();
// 	}
// 	catch(SQLException e)
// 	{
// 		errMsg=e.getMessage().c_str();
// 		printf("Insert2table errnum %d errmsg %s\n",e.getErrorCode(),e.getMessage());
// 		return FALSE;
// 	}
// 	catch(...)
// 	{
// 		errMsg="Update2table error : Unknown error.\n";
// 		printf(errMsg);
// 		return FALSE;
// 	}
// 	conn->terminateStatement (stmt);
// 	return TRUE;
// }
// 
// BOOL COCCIWrapper::UpdateBlob(int blobCount,const char *sql, ...)
// {
// 	if(blobCount<=0) return FALSE;
// 	if(!sql) return FALSE;
// 
// 	Statement *stmt;
// 
// 	try
// 	{
// 		if(!conn) return FALSE;
// 		stmt = conn->createStatement (sql);
// //		if(!stmt) {printf("UpdateBlob fail : can not create statement!");return FALSE;}
// 		if(!stmt)
// 		{
// 			throw CMyException("e","0",className,classCode,"UpdateBlob","04","01","����Blobʧ�ܣ�","����Statementʧ�ܣ�",1);
// 			exit(-1);
// 			return FALSE;
// 		}
// 
// 		va_list argptr;     //�����������
// 		va_start(argptr,sql);//��ʼ�����marker����
// 
// 		ResultSet* rs=stmt->executeQuery();
// 		if(!rs)
// 		{
// 			throw CMyException("e","0",className,classCode,"UpdateBlob","04","02","����Blobʧ�ܣ�","ִ�в�ѯʧ�ܣ���¼��Ϊ�գ�",1);
// 			if(!stmt)
// 				conn->terminateStatement (stmt);
// 			exit(-1);
// 			return FALSE;
// 		}
// // 		{
// // 			printf("UpdateBlob fail : can not create resultset!");
// // 			if(!stmt)
// // 				conn->terminateStatement (stmt);
// // 			return FALSE;
// // 		}
// 
// 		Blob blob;
// 		int blobLen=0;
// 		if(rs->next())
// 		{
// 			for(int i=1;i<=blobCount;i++)
// 			{
// 				blobLen = va_arg( argptr, int );
// 				if(blobLen<=0)
// 				{
// 					throw CMyException("e","0",className,classCode,"UpdateBlob","04","03","����Blobʧ�ܣ�","Blob���ȷ�����",1);
// 					if(!stmt)
// 						conn->terminateStatement (stmt);
// 					exit(-1);
// 					return FALSE;
// 				}
// // 				{
// // 					printf("UpdateBlob fail : bloLen <= 0 !");
// // 					if(!stmt)
// // 						conn->terminateStatement (stmt);
// // 					return FALSE;
// // 				}
// 				blob=rs->getBlob(i);
// // 				if(!blob)
// // 				{
// // 					throw CMyException("e","0",className,classCode,"UpdateBlob","04","04","����Blobʧ�ܣ�","��ȡBlobʧ�ܣ�",1);
// // 					if(!stmt)
// // 						conn->terminateStatement (stmt);
// // 					exit(-1);
// // 					return FALSE;
// // 				}
// // 				{
// // 					printf("UpdateBlob fail : getBlob() returns NULL!");
// // 					if(!stmt)
// // 						conn->terminateStatement (stmt);
// // 					return FALSE;
// // 				}
// // 				blob->write(blobLen,va_arg( argptr, unsigned char* ),blobLen);
// 				blob.write(blobLen,va_arg( argptr, unsigned char* ),blobLen);
// 			}
// 		}
// 		stmt->executeUpdate();
// 		stmt->closeResultSet(rs);
// 		va_end(argptr);//��������va_start����
// 	}
// 	catch(SQLException e)
// 	{
// 		errMsg=e.getMessage().c_str();
// 		printf("UpdateBlob errnum %d errmsg %s\n",e.getErrorCode(),e.getMessage());
// 		va_end(argptr);//��������va_start����
// 		return FALSE;
// 	}
// 	catch(...)
// 	{
// 		errMsg="UpdateBlob error : Unknown error.\n";
// 		printf(errMsg);
// 		return FALSE;
// 	}
// 	conn->terminateStatement (stmt);
// 	return TRUE;
// }
// 
// BOOL COCCIWrapper::tdelete(const char * sql,...)
// {
// 	// 'S' string 'N' number
// 	if(!sql) return FALSE;
// 	const char *tmp = sql;
// 	int icount = 0 ;
// 	while(*tmp)
// 	{
// 		if(*tmp++ == ':' ) icount +=2; 
// 	}
// 	Statement *stmt;
// 	try
// 	{
// 		if(!conn) return FALSE;
// 		stmt = conn->createStatement (sql);
// 		if(!stmt)
// 		{
// 			throw CMyException("e","0",className,classCode,"tdelete","05","01","ɾ��ʧ�ܣ�","����Statementʧ�ܣ�",1);
// 			exit(-1);
// 			return FALSE;
// 		}
// 		va_list argptr;     //�����������
// 		va_start(argptr,sql);//��ʼ�����marker����
// 		for(int i = 1 ; i <= icount/2 ; i ++ )
// 		{
// 			char *s = va_arg( argptr, char* );
// 			switch (*s)
// 			{
// 			case 'S':
// 			case 's':
// 				stmt->setString (i,va_arg( argptr, char* ));
// 				//printf("%s\n",va_arg( argptr, char* ));
// 				break;
// 			case 'N':
// 			case 'n':
// 				stmt->setInt(i,va_arg( argptr, int ));
// 				//printf("%d\n",va_arg( argptr,int ));
// 				break;
// 			default:
// 				{
// 					throw CMyException("e","0",className,classCode,"tdelete","05","02","��������","δ֪����",1);
// 					//printf("unknown para type %s \n" ,s);
// 					va_end(argptr);//��������va_start����
// 					conn->terminateStatement (stmt);
// 					exit(-1);
// 					return FALSE;
// 				}
// 			}
// 		}
// 		stmt->execute();
// 		va_end(argptr);//��������va_start����
// 	}
// 	catch(SQLException e)
// 	{
// 		errMsg=e.getMessage().c_str();
// 		printf("Delete from table errnum %d errmsg %s\n",e.getErrorCode(),e.getMessage().c_str());
// 		conn->terminateStatement (stmt);
// 		return FALSE;
// 	}
// 	catch(...)
// 	{
// 		errMsg="Delete from table error : Unknown error.\n";
// 		printf(errMsg);
// 		conn->terminateStatement (stmt);
// 		return FALSE;
// 	}
// 	conn->terminateStatement (stmt);
// 	return TRUE;
// }
// 
// ResultSet *COCCIWrapper::query(const char * sql,...)
// {
// 	if(!sql) return FALSE;
// 	const char *tmp = sql;
// 	int icount = 0 ;
// 	while(*tmp)
// 	{
// 		if(*tmp++ == ':' ) icount +=2; 
// 	}
// 	Statement *stmt;
// 	try
// 	{
// 		if(!conn) return NULL;
// 		stmt = conn->createStatement (sql);
// 		if(!stmt)
// 		{
// 			throw CMyException("e","0",className,classCode,"tdelete","05","01","��ѯʧ�ܣ�","����Statementʧ�ܣ�",1);
// 			exit(-1);
// 			return NULL;
// 		}
// 		va_list argptr;     //�����������
// 		va_start(argptr,sql);//��ʼ�����marker����
// 		for(int i = 1 ; i <= icount/2 ; i ++ )
// 		{
// 			char *s = va_arg( argptr, char* );
// 			switch (*s)
// 			{
// 			case 'S':
// 			case 's':
// 				stmt->setString (i,va_arg( argptr, char* ));
// 				//printf("%s\n",va_arg( argptr, char* ));
// 				break;
// 			case 'N':
// 			case 'n':
// 				stmt->setInt(i,va_arg( argptr, int ));
// 				//printf("%d\n",va_arg( argptr,int ));
// 				break;
// 			default:
// 				{
// 					throw CMyException("e","0",className,classCode,"tdelete","05","02","��������","δ֪����",1);
// 					//printf("unknown para type %s \n" ,s);
// 					va_end(argptr);//��������va_start����
// 					conn->terminateStatement (stmt);
// 					exit(-1);
// 					return NULL;
// 				}
// 			}
// 		}
// 		ResultSet* rs=stmt->executeQuery();
// 		if(!rs)
// 		{
// 			throw CMyException("e","0",className,classCode,"UpdateBlob","05","03","��ѯʧ�ܣ�","ִ�в�ѯʧ�ܣ���¼��Ϊ�գ�",1);
// 			if(!stmt)
// 				conn->terminateStatement (stmt);
// 			exit(-1);
// 			return NULL;
// 		}
// 		// 		stmt->execute();
// 		va_end(argptr);//��������va_start����
// 	}
// 	catch(SQLException e)
// 	{
// 		errMsg=e.getMessage().c_str();
// 		printf("Delete from table errnum %d errmsg %s\n",e.getErrorCode(),e.getMessage().c_str());
// 		conn->terminateStatement (stmt);
// 		return NULL;
// 	}
// 	catch(...)
// 	{
// 		errMsg="Delete from table error : Unknown error.\n";
// 		printf(errMsg);
// 		conn->terminateStatement (stmt);
// 		return NULL;
// 	}
// 	conn->terminateStatement (stmt);
// 	return rs;
// }
