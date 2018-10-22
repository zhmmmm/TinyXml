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
		//获取根节点
		CUDXmlNodePtr root = levelxml.GetRoot();
		//获取第一个子节点
		CUDXmlNodePtr level = root.GetFirstChild();
		while (!level.IsNull())
		{
			//<level data='34433443322132211001' id=1 pased='false' recod=0>云遮雾障</level>
			LEVELDATA ld;
			string data = level.GetAttribute("data");
			memcpy(ld.data,data.c_str(),20);
			ld.id = level.GetAttributeInt("id");
			ld.recod = level.GetAttributeInt("recod");
			ld.passed = level.GetAttributeInt("pased")?true:false;
			strcpy(ld.name,level.GetValue().c_str());
			printf("阵法布局：%s id=%d 纪录：%d 是否通过：%s\n",
				ld.data,
				ld.id,
				ld.recod,
				(ld.passed?"是":"否")
				);
			level = level.NextSibling();
		}
	}else
	{
		cout<<"打开文件失败"<<endl;
	}
	system("pause");
	return 0;
}