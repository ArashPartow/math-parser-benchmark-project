// ATLMTParserInfoFile.cpp : Implementation of CATLMTParserInfoFile
/*
	Doesn't compile correctly under Visual Studio 2003 but 2005 seams ok.
*/




#include "stdafx.h"
#include "ATLMTParserInfoFile.h"
#include ".\atlmtparserinfofile.h"

#define XML_SCHEMA 2		// compatible xml file schema version
// CATLMTParserInfoFile


STDMETHODIMP CATLMTParserInfoFile::load(BSTR fileName)
{
	m_xmlFile = fileName;
	System::Xml::XmlDocument *pDoc = new System::Xml::XmlDocument();
	try
	{
		pDoc->Load(fileName);
		System::String *pXpath = "//LibraryInfo";
		System::Xml::XmlNode *pNode = pDoc->DocumentElement->SelectSingleNode( pXpath );
		
		// xml schema validation...
		System::Xml::XmlAttribute *pXmlAttr = pNode->Attributes->get_ItemOf("schema");
		std::wstring schemaStr = convMngString(pXmlAttr->InnerText);

		int schema = System::Convert::ToInt32(schemaStr.c_str());

		if( schema != XML_SCHEMA  )
		{
			return E_FAIL;	// bad schema version
		}		

		pXmlAttr = pNode->Attributes->get_ItemOf("data1");
		m_libInfo.data1 = convMngString(pXmlAttr->InnerText);

		pXmlAttr = pNode->Attributes->get_ItemOf("data2");
		m_libInfo.data2 = convMngString(pXmlAttr->InnerText);

		pXmlAttr = pNode->Attributes->get_ItemOf("version");
		m_libInfo.version = convMngString(pXmlAttr->InnerText);

		pXmlAttr = pNode->Attributes->get_ItemOf("type");
		m_libInfo.type = convMngString(pXmlAttr->InnerText);

		// enumerate all locales...
		pXpath = "//Resource";
		System::Xml::XmlNodeList *pNodeList = pDoc->DocumentElement->SelectNodes( pXpath );
		
		for( int t=0; t<pNodeList->Count; t++ )
		{
			pNode = pNodeList->Item(t);
			pXmlAttr = pNode->Attributes->get_ItemOf("LCID");
			m_localeList.push_back( convMngString(pXmlAttr->InnerText) );
		}				
	}
	catch( System::Exception * )
	{		
		return E_FAIL;
	}	
	
	return S_OK;
}

std::wstring CATLMTParserInfoFile::convMngString(System::String *pStr)
{
	std::wstring str;
	int length = pStr->Length;
	for( int t=0; t<length; t++ )
	{
		str += pStr->Chars[t];
	}

	return str;
}



STDMETHODIMP CATLMTParserInfoFile::getNbLocales(ULONG* pNbLocales)
{
	*pNbLocales = (ULONG)m_localeList.size();

	return S_OK;
}

STDMETHODIMP CATLMTParserInfoFile::getLocale(ULONG id, BSTR* pLocale)
{
	*pLocale = SysAllocString(m_localeList[id].c_str());
	return S_OK;
}

STDMETHODIMP CATLMTParserInfoFile::setLocale(BSTR locale)
{
	m_funcList.clear();
	m_opList.clear();
	m_constList.clear();
	m_varList.clear();
	m_excepList.clear();
	
	// load all resources
	System::Xml::XmlDocument *pDoc = new System::Xml::XmlDocument();
	try
	{
		pDoc->Load(m_xmlFile.c_str());
		System::String *pXpath = System::String::Format("//Resource[@LCID='{0}']", (System::String*)locale);		
				
		System::Xml::XmlNode *pNode = pDoc->DocumentElement->SelectSingleNode( pXpath );
		System::Xml::XmlAttribute *pXmlAttr;		

		// enumerate all functions
		pXpath = "function";	// without the '//' at the beginning = look in your childs
		System::Xml::XmlNodeList *pNodeList = pNode->SelectNodes( pXpath );
		
		for( int t=0; t<pNodeList->Count; t++ )
		{
			sFuncInfo info;
			System::Xml::XmlNode *pFuncNode = pNodeList->Item(t);		

			pXmlAttr = pFuncNode ->Attributes->get_ItemOf("id");
			info.id = convMngString(pXmlAttr->InnerText);
			
			pXmlAttr = pFuncNode ->Attributes->get_ItemOf("symbol");
			info.symbol = convMngString(pXmlAttr->InnerText);

			pXmlAttr = pFuncNode ->Attributes->get_ItemOf("args");
			info.args = convMngString(pXmlAttr->InnerText);

			pXmlAttr = pFuncNode ->Attributes->get_ItemOf("argDescs");
			info.argDescs = convMngString(pXmlAttr->InnerText);

			pXmlAttr = pFuncNode ->Attributes->get_ItemOf("description");
			info.desc = convMngString(pXmlAttr->InnerText);

			m_funcList.push_back(info);
		}			

		// enumerate all operators
		pXpath = "operator";	// without the '//' at the beginning = look in your childs
		pNodeList = pNode->SelectNodes( pXpath );
		
		for( int t=0; t<pNodeList->Count; t++ )
		{
			sOpInfo info;
			System::Xml::XmlNode *pOpNode = pNodeList->Item(t);			

			pXmlAttr = pOpNode->Attributes->get_ItemOf("id");
			info.id = convMngString(pXmlAttr->InnerText);

			pXmlAttr = pOpNode->Attributes->get_ItemOf("symbol");
			info.symbol = convMngString(pXmlAttr->InnerText);

			pXmlAttr = pOpNode->Attributes->get_ItemOf("args");
			info.args = convMngString(pXmlAttr->InnerText);

			pXmlAttr = pOpNode->Attributes->get_ItemOf("description");
			info.desc = convMngString(pXmlAttr->InnerText);

			m_opList.push_back(info);
		}	

		// enumerate all constants
		pXpath = "constant";	// without the '//' at the beginning = look in your childs
		pNodeList = pNode->SelectNodes( pXpath );
		
		for( int t=0; t<pNodeList->Count; t++ )
		{
			sConstInfo info;
			System::Xml::XmlNode *pOpNode = pNodeList->Item(t);			

			pXmlAttr = pOpNode->Attributes->get_ItemOf("symbol");
			info.symbol = convMngString(pXmlAttr->InnerText);
			
			pXmlAttr = pOpNode->Attributes->get_ItemOf("description");
			info.desc = convMngString(pXmlAttr->InnerText);

			m_constList.push_back(info);
		}	

		// enumerate all variables
		pXpath = "variable";	// without the '//' at the beginning = look in your childs
		pNodeList = pNode->SelectNodes( pXpath );
		
		for( int t=0; t<pNodeList->Count; t++ )
		{
			sVarInfo info;
			System::Xml::XmlNode *pOpNode = pNodeList->Item(t);			

			pXmlAttr = pOpNode->Attributes->get_ItemOf("symbol");
			info.symbol = convMngString(pXmlAttr->InnerText);
			
			pXmlAttr = pOpNode->Attributes->get_ItemOf("description");
			info.desc = convMngString(pXmlAttr->InnerText);

			m_varList.push_back(info);
		}	

		// enumerate all exceptions
		pXpath = "exception";	// without the '//' at the beginning = look in your childs
		pNodeList = pNode->SelectNodes( pXpath );
		
		for( int t=0; t<pNodeList->Count; t++ )
		{
			sExcepInfo info;
			System::Xml::XmlNode *pOpNode = pNodeList->Item(t);			

			pXmlAttr = pOpNode->Attributes->get_ItemOf("id");
			info.id = convMngString(pXmlAttr->InnerText);
			
			pXmlAttr = pOpNode->Attributes->get_ItemOf("description");
			info.desc = convMngString(pXmlAttr->InnerText);

			m_excepList.push_back(info);
		}	
		
		pXpath = "library";
		System::Xml::XmlNode *pPluginNode = pNode->SelectSingleNode( pXpath );
		pXmlAttr = pPluginNode->Attributes->get_ItemOf("title");
		m_libInfo.title = convMngString(pXmlAttr->InnerText);

		pXmlAttr = pPluginNode->Attributes->get_ItemOf("description");
		m_libInfo.desc = convMngString(pXmlAttr->InnerText);
	}
	catch( System::Exception * )
	{		
		return E_FAIL;
	}	

	return S_OK;
}

STDMETHODIMP CATLMTParserInfoFile::getNbFuncs(ULONG* pNbFuncs)
{
	*pNbFuncs = (ULONG)m_funcList.size();

	return S_OK;
}

STDMETHODIMP CATLMTParserInfoFile::getNbOps(ULONG* pNbOps)
{
	*pNbOps = (ULONG)m_opList.size();

	return S_OK;
}

STDMETHODIMP CATLMTParserInfoFile::getNbConsts(ULONG* pNbConsts)
{
	*pNbConsts = (ULONG)m_constList.size();

	return S_OK;
}

STDMETHODIMP CATLMTParserInfoFile::getNbVars(ULONG* pNbVars)
{
	*pNbVars = (ULONG)m_varList.size();

	return S_OK;
}

STDMETHODIMP CATLMTParserInfoFile::getNbExceps(ULONG* pNbExceps)
{
	*pNbExceps = (ULONG)m_excepList.size();

	return S_OK;
}

STDMETHODIMP CATLMTParserInfoFile::getFunc(ULONG id, SATLFuncInfo* pFunc)
{
	pFunc->id = SysAllocString(m_funcList[id].id.c_str());
	pFunc->symbol = SysAllocString(m_funcList[id].symbol.c_str());
	pFunc->args = SysAllocString(m_funcList[id].args.c_str());
	pFunc->argDescs = SysAllocString(m_funcList[id].argDescs.c_str());
	pFunc->desc = SysAllocString(m_funcList[id].desc.c_str());

	return S_OK;
}

STDMETHODIMP CATLMTParserInfoFile::getOp(ULONG id, SATLOpInfo* pOp)
{
	pOp->id = SysAllocString(m_opList[id].id.c_str());
	pOp->symbol = SysAllocString(m_opList[id].symbol.c_str());
	pOp->args = SysAllocString(m_opList[id].args.c_str());	
	pOp->desc = SysAllocString(m_opList[id].desc.c_str());

	return S_OK;
}

STDMETHODIMP CATLMTParserInfoFile::getConst(ULONG id, SATLConstInfo* pConst)
{
	pConst->symbol = SysAllocString(m_constList[id].symbol.c_str());	
	pConst->desc = SysAllocString(m_constList[id].desc.c_str());

	return S_OK;
}

STDMETHODIMP CATLMTParserInfoFile::getVar(ULONG id, SATLVarInfo* pVar)
{
	pVar->symbol = SysAllocString(m_varList[id].symbol.c_str());	
	pVar->desc = SysAllocString(m_varList[id].desc.c_str());

	return S_OK;
}

STDMETHODIMP CATLMTParserInfoFile::getExcep(ULONG id, SATLExcepInfo* pExcep)
{
	pExcep->id = SysAllocString(m_excepList[id].id.c_str());	
	pExcep->desc = SysAllocString(m_excepList[id].desc.c_str());

	return S_OK;
}

STDMETHODIMP CATLMTParserInfoFile::getLib(SATLLibInfo* pLib)
{
	pLib->title = SysAllocString(m_libInfo.title.c_str());	
	pLib->desc = SysAllocString(m_libInfo.desc.c_str());	
	pLib->type = SysAllocString(m_libInfo.type.c_str());	
	pLib->data1 = SysAllocString(m_libInfo.data1.c_str());	
	pLib->data2 = SysAllocString(m_libInfo.data2.c_str());	
	pLib->version = SysAllocString(m_libInfo.version.c_str());	

	return S_OK;
}


