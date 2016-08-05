#include "symbol.h"
namespace seg{
	Symbol::Symbol(){}
	Symbol::~Symbol(){}

	void Symbol::Init(const char* path){
		std::string namepath = std::string(path) + "name";
		std::string connectpath = std::string(path) + "connet";
		LoadName(namepath.c_str());
		LoadConnet(connectpath.c_str());
		LoadNameFre (path);
	}
	bool Symbol::LoadNameFre (const char *  namedir)	{
		if (NULL == namedir){
			commom::LOG_INFO("load namefre error");
			return false;
		}
		std::string pathfirst = std::string(namedir) + "Chinese.name";
		std::string pathsecond = std::string(namedir) + "Chinese.secondname";
		FILE *pf = fopen(pathfirst.c_str(),"r");	
		if (pf == NULL){
			commom::LOG_INFO("load namefre error");
			return false;
		}
		char buffer[SHORT_LENTH]; 
		memset( buffer,0,SHORT_LENTH );			
		std::vector<std::string> temp; 
		while ( commom::ReadLine(buffer,SHORT_LENTH,pf)!=NULL)	{	
			std::string str = commom::GetLine(buffer);	 
			commom::Split(" ",  str, temp);	 
			if (temp.size() <= 2) {
				namefre.insert(std::pair<std::string,unsigned int>(temp[0],atoi(temp[1].c_str()))); 
			}			
		}
		fclose(pf);
		memset( buffer,0,SHORT_LENTH );		
		pf = fopen(pathsecond.c_str(),"r");
		if (pf == NULL){
			commom::LOG_INFO("load namefre error");
			return false;
		}
		while ( commom::ReadLine(buffer,SHORT_LENTH,pf)!=NULL)	{	
			std::string str = commom::GetLine(buffer);	 
			commom::Split(" ",  str, temp);	 
			if (temp.size() <= 2) {
				secondnamefir.insert(std::pair<std::string,unsigned int>(temp[0],atoi(temp[1].c_str()))); 
			}			
		}
		return true;
	}

	bool Symbol::LoadConnet(const char *  connetpath){
		FILE *pf = fopen(connetpath,"r");
		char buffer[MAX_LENTH];
		memset( buffer,0,MAX_LENTH );
		std::string chinaname="";
		while ( commom::ReadLine(buffer,MAX_LENTH,pf)!=NULL)	{
			chinaname = commom::GetLine(buffer); break;			
		}		
		return commom::StrToVec(chinaname.c_str(), m_connet);
	}

	/*����Ƿ�Ϊ���ӷ�*/
	bool Symbol::CheckConnet(uint16_t  x){ 
		std::vector<uint16_t>::iterator it = find(m_connet.begin(),m_connet.end(),x);
		return ( it != m_connet.end());
	}

	/*��������*/
	bool Symbol::LoadName(const char *  namepath){
		FILE *pf = fopen(namepath,"r");
		char buffer[MAX_LENTH];
		memset( buffer,0,MAX_LENTH );
		std::string chinaname="";
		while ( commom::ReadLine(buffer,MAX_LENTH,pf)!=NULL)	{
			chinaname = commom::GetLine(buffer);	break;
		}		
		return commom::StrToVec(chinaname.c_str(), m_name);
	}

	/*����Ƿ�Ϊ����*/
	bool Symbol::CheckName(uint16_t  x){ 
		intvector::iterator nameresult = find( m_name.begin(),m_name.end(),x);  
		return (nameresult !=m_name.end()); 
	}

}