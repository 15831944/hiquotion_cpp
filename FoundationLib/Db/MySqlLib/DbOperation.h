#pragma once

#include <mysql_connection.h>
#include <mysql_driver.h>

#include <cppconn/exception.h> 
#include <cppconn/resultset.h> 
#include <cppconn/statement.h> 
#include <cppconn/prepared_statement.h> 

using namespace sql;

#include <string>
using namespace std;

class DataBuf : public std::streambuf
{
public:
	DataBuf(char* d, size_t s)
	{
		setg(d, d, d+s);
	}
};

class CDbOperation
{
public:
	CDbOperation(void);
	~CDbOperation(void);

	void beginTransaction();
	void endTransaction();

	void commit();
	void rollback();

	// ִ�в�ѯ���������ӵ�sql�������������������������query
	// ����ֵ��
	// null����ȡ����ʧ�ܣ���ִ��ʧ��
	// ResultSet����
	ResultSet *executeQuery(char *sql, int count, ...);
	ResultSet *executeQuery(char *sql, int count, va_list argptr);

	// ִ��д�����²��������ӵ�sql�������������������������insert��update
	// ����ֵ��
	// -1����ȡ���ݿ�����ʧ�� 
	// -2��ʧ��
	// >=0���ɹ���������Ӱ�������
	uint64_t execute(char *sql, int count, ...);
	uint64_t execute(char *sql, int count, va_list argptr);

	void closeResultSet(ResultSet *rs);

	// ���ݿ�д��
	// ֻ��д�뵥����
	// Can use columns parameter like this:
	//     String columns = "col1,col2,col3"; // col count must equals to values parameter
	// Can use values parameter like this:
	//     String conditions = "value1,value2,value3"; // value count must equals to columns parameter
	// Can use ... parameter like this:
	//     'n',3,'s',"second para",'n',5
	// ����ֵ��
	// -1����ȡ���ݿ�����ʧ�� 
	// -2��ʧ��
	// >=0���ɹ���������Ӱ�������
	int insert(char *table, char *columns, char *values, int count, ...);

	// ���ݿ����
	// ֻ�ܸ��µ�����
	// Can use values parameter like this:
	//     String values = "col1=?,col2=?"; // etc
	// Can use ... parameter like this:
	//     'n',3,'s',"second para"  // etc
	// ����ֵ��
	// -1����ȡ���ݿ�����ʧ�� 
	// -2��ʧ��
	// >=0���ɹ���������Ӱ�������
	int update(char *table, char *values, char *whereConditions, int count, ...);

	// ���ݿ��ѯ
	// ֧�ֶ�����ϲ�ѯ
	// Can use selectedColumns parameter like this:
	//     String selectedColumns = "col1,col2,col3"; // etc
	// Can use ... parameter like this:
	//     'n',3,'s',"second para",'n',4
	// ����ֵ��
	// null����ȡ����ʧ�ܣ���ִ��ʧ��
	// ResultSet����
	ResultSet *select(char *selectedColumns, char *fromTables, char *whereCondition, int count, ...);

protected:
	BOOL getConnection();
	void closeConnection();
	void closeConnection(Connection *conn);

// 	PreparedStatement *prepareArgs(PreparedStatement *stmt, int count, ...);
	PreparedStatement *prepareArgs(PreparedStatement *stmt, int count, va_list argptr);

	void closeStatement(Statement *stmt);

	string m_url;
	string m_user;
	string m_pwd;

	Connection *m_conn;

	BOOL m_isTransaction;

	PreparedStatement *m_stmt;
};
