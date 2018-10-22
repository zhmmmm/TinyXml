#ifndef _UDXML_H_
#define _UDXML_H_
#include <string>
using std::string;
#include <Windows.h>
#include "./tinyxml/include/tinyxml.h"

class CUDXmlAttribute
{
public:
	CUDXmlAttribute(){ m_pAttribute=NULL;}
	CUDXmlAttribute( TiXmlAttribute *pAttribute){ m_pAttribute=pAttribute;}
	//              ��һ������
	CUDXmlAttribute Next();
	//              ǰһ������
	CUDXmlAttribute Pre();
	//              ������������
	string          Name();
	//              ������������
	void            SetName(const char* name);
	//              ��������ֵstring����
	string          Value();
	//              ��������ֵint����
	int             IntValue();
	//              ��������ֵdouble����
	double          DoubleValue();
	//              ��������ֵ
	void            SetValue(const char* value);  

	BOOL			IsAttributeValued();
	//				�Ƿ�Ϊ��Ч����
private:
	TiXmlAttribute *m_pAttribute;
};

class CUDXmlNodePtr
{
public:
	CUDXmlNodePtr()                         { m_pElement=NULL; }
	CUDXmlNodePtr(TiXmlElement *pElement)   { m_pElement=pElement; }
	CUDXmlNodePtr(TiXmlNode* pNode)         { m_pElement=pNode->ToElement(); }
	BOOL          operator==(CUDXmlNodePtr&node);
	//              ����µĽڵ�
	CUDXmlNodePtr   NewChild(const char* name);
	//              ��ȡ��һ�����ӽڵ㣬Ĭ�Ϸ��ص�һ�����ӽڵ�
	CUDXmlNodePtr   GetFirstChild(const char* name=NULL);
	//              ��ȡ��һ���ֵܽڵ㣬Ĭ�Ϸ����±ߵ�һ���ֵܽڵ�
	CUDXmlNodePtr   NextSibling(const char* name=NULL);
	//              ��ȡ��һ���ֵܽڵ㣬Ĭ�Ϸ����ϱߵ�һ���ֵܽڵ�
	CUDXmlNodePtr   PreSibling(const char* name=NULL);
	//              ��������
	BOOL            Destory();
	//              �������к��ӽڵ�
	void            DestoryAllChildren();
	//              ��������
	void            SetAttribute(const char* name, const char* value);
	//              ��ȡ����ֵ
	string          GetAttribute(const char* name);
	int				GetAttributeInt(const char* name);
	double			GetAttributeDouble(const char* name);
	CUDXmlAttribute GetFirstAttribute();
	CUDXmlAttribute LastAttribute();
	//              ���ýڵ�����
	void            SetName(const char*name);
	//              ��ȡ�ڵ�����
	string          GetName();
	//              ���ýڵ�ֵ
	void            SetValue(const char* value);
	//              ��ȡ�ڵ�ֵ
	string          GetValue();
	//              �жϸýڵ��Ƿ�Ϊ��
	BOOL            IsNull();
	//              ���ظ��ڵ�
	CUDXmlNodePtr   Root();
public:
	TiXmlElement *m_pElement;
};

class CUDXml
{
public:
	//    ����xml�ļ� Ĭ������Ϊ<?xml version="1.0" encoding="UTF-8" standalone="no"?>
	BOOL  CreateXml(
		const char* path, 
		const char* version="1.0", 
		const char*  encoding="UTF-8", 
		const char*  standalone="no");
	//    ���ļ�
	BOOL  Open(const char* path);
	//    �����ļ�
	BOOL  Save(const char* path=NULL);
	//    ��ȡ���ڵ�
	CUDXmlNodePtr  GetRoot();
	//    �жϸ��ļ��Ƿ����
	BOOL  IsExist(const char* path);
private:
	TiXmlDocument m_doc;
};
#endif