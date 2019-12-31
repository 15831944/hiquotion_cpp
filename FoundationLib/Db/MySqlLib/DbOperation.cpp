#include "StdAfx.h"
#include "DbOperation.h"
#include "AppConfig.h"
#include "mysqldbhelper.h"

CDbOperation::CDbOperation(void)
:m_conn(NULL),m_stmt(NULL),m_url(""),m_user(""),m_pwd("")
{
}

CDbOperation::~CDbOperation(void)
{
	closeConnection();
}

BOOL CDbOperation::getConnection()
{
	if(!m_conn)
	{
		if(m_url=="" || m_user=="" || m_pwd=="")
		{
			CAppConfig config;
			m_url=config.getDbUrl();
			m_user=config.getDbUser();
			m_pwd=config.getDbPwd();
		}

		m_conn=CMysqlDbHelper::getConnection((char *)m_url.c_str(), (char *)m_user.c_str(), (char *)m_pwd.c_str());
		if(!m_conn)
			return FALSE;
	}

	return TRUE;
}

void CDbOperation::closeConnection()
{
	if(m_conn)
		closeConnection(m_conn);
}

void CDbOperation::closeConnection(Connection *conn)
{
	if(conn)
	{
		CMysqlDbHelper::closeConnection(conn);
		delete m_conn;
		m_conn=NULL;
	}
}

void CDbOperation::beginTransaction()
{
	if(!getConnection())
		return;

	try{
		m_conn->setAutoCommit(false);
		m_isTransaction=TRUE;
	}
	catch(SQLException e){
		endTransaction();
	}

}

void CDbOperation::endTransaction()
{
	// ��������˵���Ѿ���ȡ�����ˣ�ֻҪ���Ӳ��գ����ɼ���ִ����ȥ
	if(!m_conn)
		return;

	try{
		m_conn->setAutoCommit(true);
		m_isTransaction=FALSE;
	}
	catch(SQLException &e){
		
	}

}

void CDbOperation::commit()
{
	// û�����ݿ����Ӿ��ύ���϶�����������ֱ�ӷ���
	if(!m_conn)
		return;

	try{
		m_conn->commit();
	}
	catch(SQLException &e){
		rollback();
		endTransaction();
	}

}

void CDbOperation::rollback()
{
	if(!m_conn)
		return;

	try{
		m_conn->rollback();
	}
	catch(SQLException e){
		endTransaction();
	}

}

PreparedStatement *CDbOperation::prepareArgs(PreparedStatement *stmt, int count, va_list argptr)
{
// 	va_list argptr;     //�����������
// 	va_start(argptr,count);//��ʼ�����marker����

	for(int i = 1 ; i <= count ; i ++ )
	{
		char *s = va_arg( argptr, char* );
		char *ss=NULL;
		if(!s)
		{
// 			remark.doLog(LOGLEVEL_SHOWERROR,"CreateStmt �������󣡿�����©д�˱��������ͣ�Ҳ�����ǿɱ�����ĸ�����ָ���ĸ�����ƥ�䣡");
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
		case 'd':
		case 'D':  // ����
			stmt->setDateTime(i, va_arg( argptr, char*));
			//printf("%d\n",va_arg( argptr,int ));
			break;
		case 'b':
		case 'B':  // Binary(MySQL��Blob����Ҫ��Binary����)
			stmt->setBlob(i, va_arg( argptr, std::istream*));
			break;
		default:
			{
// 				remark.doLog(LOGLEVEL_SHOWERROR,"Statement��������δ֪����");
			}
		}
	}
// 	va_end(argptr);//��������va_start����

	return stmt;
}

ResultSet *CDbOperation::executeQuery(char *sql, int count, ...)
{
	ResultSet *rs=NULL;
	va_list argptr;     //�����������
	va_start(argptr,count);//��ʼ�����marker����
	rs=executeQuery(sql, count, argptr);
	va_end(argptr);

	return rs;
}

ResultSet *CDbOperation::executeQuery(char *sql, int count, va_list argptr)
{
	if(!getConnection())
		return NULL;

	ResultSet *rs=NULL;

	try{
		if(m_stmt)
			closeStatement(m_stmt);

		m_stmt=m_conn->prepareStatement(sql);
		if(count>0)
		{
// 			va_list argptr;     //�����������
// 			va_start(argptr,count);//��ʼ�����marker����
			m_stmt=prepareArgs(m_stmt, count, argptr);
// 			va_end(argptr);
		}
		rs=m_stmt->executeQuery();
		return rs;
	}
	catch(SQLException e){
		closeResultSet(rs);
		closeStatement(m_stmt);
		return NULL;
	}

}

uint64_t CDbOperation::execute(char *sql, int count, ...)
{
	uint64_t ret=0;
	va_list argptr;     //�����������
	va_start(argptr,count);//��ʼ�����marker����
	ret=execute(sql, count, argptr);
	va_end(argptr);

	return ret;
}

uint64_t CDbOperation::execute(char *sql, int count, va_list argptr)
{
	if(!getConnection())
		return -1;

	uint64_t n=0;
	try{
		if(m_stmt)
			closeStatement(m_stmt);

		m_stmt=m_conn->prepareStatement(sql);
		if(count>0)
		{
// 			va_list argptr;     //�����������
// 			va_start(argptr,count);//��ʼ�����marker����
			m_stmt=prepareArgs(m_stmt, count, argptr);
// 			va_end(argptr);
		}
		m_stmt->execute();
		
		closeStatement(m_stmt);
// 		if(!m_isTransaction)
// 			closeConnection(m_conn);
	}
	catch(SQLException &e){
		try{
			m_stmt->close();
		}
		catch(SQLException &ee){

		}
		return -2;
	}
	return n;

}

void CDbOperation::closeResultSet(ResultSet *rs)
{
	if(!rs)
		return;

	try
	{
		rs->close();
		delete rs;
		if(m_stmt)
		{
			closeStatement(m_stmt);
		}
	}
	catch(SQLException &e)
	{

	}
}

void CDbOperation::closeStatement(Statement *stmt)
{
	if(!stmt)
		return;

	try
	{
		stmt->close();
		delete m_stmt;
		m_stmt=NULL;
	}
	catch(SQLException &e)
	{

	}
}

int CDbOperation::insert(char *table, char *columns, char *values, int count, ...)
{
	string sql="insert into ";
	sql += table;
	if(columns)
		sql = sql +  " (" + columns + ")";
	sql = sql + " values (" + values + ")";

	va_list argptr;     //�����������
	va_start(argptr,count);//��ʼ�����marker����
	int ret=execute((char *)sql.c_str(), count, argptr);
	va_end(argptr);
	return ret;
}

int CDbOperation::update(char *table, char *values, char *whereConditions, int count, ...)
{
	string sql="update table ";
	sql = sql + table + " set " + values;
	if(whereConditions)
		sql = sql + " where " + whereConditions;

	va_list argptr;     //�����������
	va_start(argptr,count);//��ʼ�����marker����
	int ret=execute((char *)sql.c_str(), count, argptr);
	va_end(argptr);
	return ret;
}

ResultSet *CDbOperation::select(char *selectedColumns, char *fromTables, char *whereCondition, int count, ...)
{
	string sql="select ";
	sql = sql + selectedColumns + " from " + fromTables;
	if(whereCondition)
		sql = sql + " where " + whereCondition;

	va_list argptr;     //�����������
	va_start(argptr,count);//��ʼ�����marker����
	ResultSet *rs=executeQuery((char *)sql.c_str(), count, argptr);
	va_end(argptr);
	return rs;
}
