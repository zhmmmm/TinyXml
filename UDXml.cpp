#include "UDXml.h"
#include "io.h"

#pragma comment(lib,"./tinyxml/lib/tinyxml.lib")

BOOL CUDXml::CreateXml(
					   const char* path, 
					   const char* _version, 
					   const char*  _encoding, 
					   const char*  _standalone)
{
	m_doc.LoadFile(path, TIXML_ENCODING_UTF8);

	TiXmlNode *pDelar = new TiXmlDeclaration(_version, _encoding, _standalone);
	m_doc.InsertEndChild(*pDelar);delete pDelar;

	TiXmlNode *pRoot  = new TiXmlElement("root");
	m_doc.InsertEndChild(*pRoot);	

	return TRUE;
}

BOOL CUDXml::Open( const char* path )
{
	BOOL _ret=m_doc.LoadFile(path);
	return _ret;
}

BOOL CUDXml::Save(const char* path)
{
	BOOL ret;

	if(NULL == path) ret = m_doc.SaveFile();
	else ret = m_doc.SaveFile(path);

	return ret;
}

CUDXmlNodePtr  CUDXml::GetRoot()
{
	return m_doc.RootElement();
}

BOOL CUDXml::IsExist( const char* path )
{
	if(-1 != _access(path,0))
		return TRUE;
	else
		return FALSE;
}

CUDXmlNodePtr CUDXmlNodePtr::NewChild( const char* name )
{
	CUDXmlNodePtr NewNode;
	TiXmlNode *pNode = new TiXmlElement(name);

	NewNode = m_pElement->InsertEndChild(*pNode);

	delete pNode;
	return NewNode;
}

BOOL CUDXmlNodePtr::IsNull()
{
	return NULL==m_pElement;
}

void CUDXmlNodePtr::SetAttribute( const char* name, const char* value )
{
	m_pElement->SetAttribute(name, value);
}

std::string CUDXmlNodePtr::GetAttribute( const char* name )
{	
	return 	m_pElement->Attribute(name);
}
int CUDXmlNodePtr::GetAttributeInt(const char* name)
{
	std::string _temp=GetAttribute(name);
	int ret=atoi(_temp.c_str());
	return ret;
}
double CUDXmlNodePtr::GetAttributeDouble(const char* name)
{
	std::string _temp=GetAttribute(name);
	double ret=atof(_temp.c_str());
	return ret;
}

void CUDXmlNodePtr::SetName( const char*name )
{
	m_pElement->SetValue(name);
}

std::string CUDXmlNodePtr::GetName()
{
	const char *pName = m_pElement->Value();
	if(NULL == pName)
		return "";

	return pName;
}	

void CUDXmlNodePtr::SetValue( const char* value )
{
	TiXmlNode *pText = new TiXmlText(value);
	m_pElement->InsertEndChild(*pText);
	delete pText;
}

std::string CUDXmlNodePtr::GetValue()
{
	const char* pText = m_pElement->GetText();
	if(NULL == pText)
		return "";

	return pText;
}

CUDXmlNodePtr CUDXmlNodePtr::GetFirstChild( const char* name/*=NULL*/ )
{
	if(NULL == name)
		return m_pElement->FirstChildElement();
	else
		return m_pElement->FirstChildElement(name);
}

CUDXmlNodePtr CUDXmlNodePtr::NextSibling( const char* name/*=NULL*/ )
{
	if(NULL == name)
		return m_pElement->NextSiblingElement();
	else
		return m_pElement->NextSiblingElement(name); 
}

CUDXmlNodePtr CUDXmlNodePtr::PreSibling( const char* name/*=NULL*/ )
{
	if(NULL == name)
		return m_pElement->PreviousSibling();
	else
		return m_pElement->PreviousSibling(name);
}

BOOL CUDXmlNodePtr::Destory()
{
	if(*this == Root())return FALSE;

	return	m_pElement->Parent()->RemoveChild((TiXmlNode*)m_pElement);
}

CUDXmlNodePtr CUDXmlNodePtr::Root()
{
	TiXmlElement *pElement = m_pElement;
	TiXmlElement *pRoot = NULL;

	int nType = pElement->Type();
	while (0 != nType)
	{
		pRoot    = pElement;
		pElement = (TiXmlElement*)pElement->Parent();
		nType    = pElement->Type();
	}

	return pRoot;
}

BOOL CUDXmlNodePtr::operator==( CUDXmlNodePtr&node )
{
	return this->m_pElement == node.m_pElement;
}

void CUDXmlNodePtr::DestoryAllChildren()
{
	m_pElement->Clear();
}

CUDXmlAttribute CUDXmlNodePtr::GetFirstAttribute()
{
	return m_pElement->FirstAttribute();
}

CUDXmlAttribute CUDXmlNodePtr::LastAttribute()
{
	return m_pElement->LastAttribute();
}

CUDXmlAttribute CUDXmlAttribute::Next()
{
	return	m_pAttribute->Next();
}

CUDXmlAttribute CUDXmlAttribute::Pre()
{
	return m_pAttribute->Previous();
}

std::string CUDXmlAttribute::Name()
{
	return m_pAttribute->Name();
}

std::string CUDXmlAttribute::Value()
{
	return m_pAttribute->Value();
}

void CUDXmlAttribute::SetName( const char* name )
{
	m_pAttribute->SetName(name);
}

void CUDXmlAttribute::SetValue( const char* value )
{
	m_pAttribute->SetValue(value);
}

double CUDXmlAttribute::DoubleValue()
{
	return m_pAttribute->DoubleValue();
}

int CUDXmlAttribute::IntValue()
{
	return m_pAttribute->IntValue();
}
BOOL CUDXmlAttribute::IsAttributeValued()
{
	if (m_pAttribute)
	{
		return TRUE;
	}
	return FALSE;
}