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
	//              下一个属性
	CUDXmlAttribute Next();
	//              前一个属性
	CUDXmlAttribute Pre();
	//              返回属性名称
	string          Name();
	//              设置属性名称
	void            SetName(const char* name);
	//              返回属性值string类型
	string          Value();
	//              返回属性值int类型
	int             IntValue();
	//              返回属性值double类型
	double          DoubleValue();
	//              设置属性值
	void            SetValue(const char* value);  

	BOOL			IsAttributeValued();
	//				是否为有效属性
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
	//              添加新的节点
	CUDXmlNodePtr   NewChild(const char* name);
	//              获取第一个孩子节点，默认返回第一个孩子节点
	CUDXmlNodePtr   GetFirstChild(const char* name=NULL);
	//              获取下一个兄弟节点，默认返回下边第一个兄弟节点
	CUDXmlNodePtr   NextSibling(const char* name=NULL);
	//              获取上一个兄弟节点，默认返回上边第一个兄弟节点
	CUDXmlNodePtr   PreSibling(const char* name=NULL);
	//              自我销毁
	BOOL            Destory();
	//              销毁所有孩子节点
	void            DestoryAllChildren();
	//              设置属性
	void            SetAttribute(const char* name, const char* value);
	//              读取属性值
	string          GetAttribute(const char* name);
	int				GetAttributeInt(const char* name);
	double			GetAttributeDouble(const char* name);
	CUDXmlAttribute GetFirstAttribute();
	CUDXmlAttribute LastAttribute();
	//              设置节点名称
	void            SetName(const char*name);
	//              获取节点名称
	string          GetName();
	//              设置节点值
	void            SetValue(const char* value);
	//              获取节点值
	string          GetValue();
	//              判断该节点是否为空
	BOOL            IsNull();
	//              返回根节点
	CUDXmlNodePtr   Root();
public:
	TiXmlElement *m_pElement;
};

class CUDXml
{
public:
	//    创建xml文件 默认声明为<?xml version="1.0" encoding="UTF-8" standalone="no"?>
	BOOL  CreateXml(
		const char* path, 
		const char* version="1.0", 
		const char*  encoding="UTF-8", 
		const char*  standalone="no");
	//    打开文件
	BOOL  Open(const char* path);
	//    保存文件
	BOOL  Save(const char* path=NULL);
	//    获取根节点
	CUDXmlNodePtr  GetRoot();
	//    判断该文件是否存在
	BOOL  IsExist(const char* path);
private:
	TiXmlDocument m_doc;
};
#endif