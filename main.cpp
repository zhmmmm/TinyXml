#include <iostream>
using namespace std;
#include "UDXml.h"
typedef struct stLevelData 
{
	char data[20];
	char name[12];
	unsigned int id;
	unsigned int recod;
	bool passed;
	
}LEVELDATA,*LPLEVELDATA;


int main()
{
	CUDXml levelxml;
	if (levelxml.Open("./level.xml"))
	{
		//��ȡ���ڵ�
		CUDXmlNodePtr root = levelxml.GetRoot();
		//��ȡ��һ���ӽڵ�
		CUDXmlNodePtr level = root.GetFirstChild();
		while (!level.IsNull())
		{
			//<level data='34433443322132211001' id=1 pased='false' recod=0>��������</level>
			LEVELDATA ld;
			string data = level.GetAttribute("data");
			memcpy(ld.data,data.c_str(),20);
			ld.id = level.GetAttributeInt("id");
			ld.recod = level.GetAttributeInt("recod");
			ld.passed = level.GetAttributeInt("pased")?true:false;
			strcpy(ld.name,level.GetValue().c_str());
			printf("�󷨲��֣�%s id=%d ��¼��%d �Ƿ�ͨ����%s\n",
				ld.data,
				ld.id,
				ld.recod,
				(ld.passed?"��":"��")
				);
			level = level.NextSibling();
		}
	}else
	{
		cout<<"���ļ�ʧ��"<<endl;
	}
	system("pause");
	return 0;
}