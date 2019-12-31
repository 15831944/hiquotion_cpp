// OCCIWrapper.cpp: implementation of the COCCIWrapper class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OCCIWrapper.h"
#include "AppConfig.h"
#include "MyException.h"

extern CRemark remark;

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
	
	CAppConfig config;
// 	remark.doLog("�������ļ���ȡ���ݿ����ӵ��û��������");
	m_uid=config.getDbUser();
	m_pwd=config.getDbPwd();
	m_sid=config.getDbSid();

	string msg="�û�����"+m_uid+"�����룺"+m_pwd+"��SID��"+m_sid;
	remark.doLog(LOGLEVEL_SHOWINFO,msg);

// 	remark.doLog("�û���Ϊ��"+m_uid);
// 	remark.doLog("����Ϊ��"+m_pwd);
// 	remark.doLog("Ora��Ϊ��"+m_sid);

	if(m_uid=="" || m_pwd=="" || m_sid=="")
	{
 		remark.doLog(LOGLEVEL_SHOWERROR,"��ȡ���ݿ�������Ϣʧ�ܣ��û����������SIDΪ�գ�");
//		throw CMyException("e","0",className,classCode,className,"00","01","��ȡ���ݿ�������Ϣʧ�ܣ�","�����ļ������ڣ��������ļ���ʽ����ȷ��",1);
//		throw CMyException(EXCEPTION_INTERNAL,"��ȡ���ݿ�������Ϣʧ�ܣ�","�����ļ������ڣ��������ļ���ʽ����ȷ��");
// 		exit(-100);
		isInitSucceed=FALSE;
		return;
	}
	isInitSucceed=TRUE;
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
		env->terminateConnection (conn);
		conn=NULL;		
	}
	if(env)
	{
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
//  			throw CMyException(EXCEPTION_INTERNAL,"����Statementʧ�ܣ�","createStmt");
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
// 					throw CMyException("e","0",className,classCode,"createStmt","02","02","��������","δ֪����",1);
// 					throw CMyException(EXCEPTION_INTERNAL,"���� Statement �Ĳ�������","δ֪����");
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

// ִ��Statement
BOOL COCCIWrapper::stmtExecute()
{
	if(!stmt)
		return FALSE;
//		throw CMyException(EXCEPTION_INTERNAL,"�޷��������ݿ�ִ�з�����","Statement ָ��Ϊ�գ�");
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

// ִ��Statement����
BOOL COCCIWrapper::stmtExecuteUpdate()
{
	if(!stmt)
		return FALSE;
//		throw CMyException(EXCEPTION_INTERNAL,"�޷��������ݿ�� ִ�и��� ������","Statement ָ��Ϊ�գ�");
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

// ��ȡBLOB������
int COCCIWrapper::getBlob(int colIndex,char *blobData)
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

		if(!blob.isNull())
			if(blob.isInitialized())
			{
				blobLength=blob.length();
				if(blobLength>0)
					blob.read(blobLength,(unsigned char *)blobData,blobLength);
			}
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

// ���� Statement ʹ�����񣬼� setAutoCommit(false)
BOOL COCCIWrapper::setTransaction()
{
	if(!conn)
		return FALSE;
	if(!stmt)
		return FALSE;
// 	try
// 	{
		stmt->setAutoCommit(false);
// 	}
// 	catch(SQLException *e)
// 	{
// 		remark.doLog(LOGLEVEL_SHOWERROR,e->getMessage());
// 		return FALSE;
// 	}
// 	catch(...)
// 	{
// 		remark.doLog(LOGLEVEL_SHOWERROR,"setAutoCommit(false)����δ֪����");
// 		return FALSE;
// 	}
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
