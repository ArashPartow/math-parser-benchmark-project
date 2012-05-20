	
// MTParser.h : Declaration of the CMTParser

#ifndef __MTPARSER_H_
#define __MTPARSER_H_

#include "resource.h"       // main symbols
#include "../MTParserLib/MTParser.h"
#include "MTExcepHelper.h"


/////////////////////////////////////////////////////////////////////////////
// CMTParser
class ATL_NO_VTABLE CMTParser : 
	public CComObjectRootEx<CComMultiThreadModel>,
	public CComCoClass<CMTParser, &CLSID_MTParser>,
	public ISupportErrorInfo,
	public IDispatchImpl<IMTParser, &IID_IMTParser, &LIBID_MTPARSERCOMLib>
{
public:
	CMTParser();
	~CMTParser();
	
DECLARE_REGISTRY_RESOURCEID(IDR_MTPARSER)
DECLARE_GET_CONTROLLING_UNKNOWN()

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CMTParser)
	COM_INTERFACE_ENTRY(IMTParser)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY_AGGREGATE(IID_IMarshal, m_pUnkMarshaler.p)
END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

	HRESULT FinalConstruct()
	{
		return CoCreateFreeThreadedMarshaler(
			GetControllingUnknown(), &m_pUnkMarshaler.p);
	}

	void FinalRelease()
	{
		m_pUnkMarshaler.Release();
	}

	CComPtr<IUnknown> m_pUnkMarshaler;

	



// IMTParser
public:	
	STDMETHOD(getSyntax)(/*[out, retval]*/ SMTSyntax *pSyntax);
	STDMETHOD(setSyntax)(/*[in]*/ SMTSyntax *pSyntax);
	STDMETHOD(useLocaleSettings)();
	STDMETHOD(loadPlugin)(/*[in]*/ BSTR clsid);	
	STDMETHOD(undefineAllVars)();
	STDMETHOD(undefineVar)(/*[in]*/ BSTR symbol);	
	STDMETHOD(resetExpression)();
	STDMETHOD(evaluateCompiled)(/*[out, retval]*/ double *pResult);
	STDMETHOD(compile)(/*[in]*/ BSTR expr);
	STDMETHOD(evaluate)(/*[in]*/ BSTR expr, /*[out, retval]*/ double *pResult);	
	STDMETHOD(defineConst)(/*[in]*/ BSTR name, /*[in]*/ double value);
	STDMETHOD(copy)(/*[in]*/ IMTParser *pParser);
	STDMETHOD(getParserPtr)(/*[out]*/ int *pParserPtr);
	STDMETHOD(getUsedVar)(/*[in]*/ int index, /*[out, retval]*/ BSTR *symbol);
	STDMETHOD(getNbUsedVars)(/*[out]*/ int *pNbUsedVars);
	STDMETHOD(getConst)(/*[in]*/ int index, /*[out, retVal]*/ SMTConstant *pConst);
	STDMETHOD(getNbDefinedConsts)(/*[out]*/ int *pNbDefinedConsts);	
	STDMETHOD(getFunc)(/*[in]*/ int index, /*[out, retval]*/ SMTFunction *pFunc);
	STDMETHOD(getNbDefinedFuncs)(/*[out, retval]*/ int *pNbDefinedFuncs);
	STDMETHOD(getOp)(/*[in]*/ int index, /*[out, retval]*/ SMTOperator *pOp);
	STDMETHOD(getNbDefinedOps)(/*[out, retval]*/ int *pNbDefinedOps);	
	STDMETHOD(getLastExcep)(/*[out, retval]*/ IMTExcepData *pExcep);
	STDMETHOD(defineVar)(/*[in]*/ IMTVariable *pVar);	
	STDMETHOD(isNaN)(/*[out, retval]*/ int *pRet);
	STDMETHOD(getNaN)(/*[out, retval]*/ double *pNaN);
	STDMETHOD(defineMacro)(/*[in]*/ BSTR prototype, /*[in]*/ BSTR macro, /*[in]*/ BSTR description);
	STDMETHOD(isFinite)(/*[out, retval]*/ int *pRet);
	STDMETHOD(loadAllPlugins)(BSTR directory, BSTR searchPattern);
	STDMETHOD(evaluateCompiledBatch)(int nbLoops, SAFEARRAY * pResults);
	STDMETHOD(evaluateCompiledBatchVB6)(int nbLoops, SAFEARRAY ** pResults);
	STDMETHOD(redefineVar)(IMTVariable* pVar);
	STDMETHOD(undefineConst)(/*[in]*/ BSTR name);	
	STDMETHOD(undefineFuncById)(/*[in]*/ BSTR id);	
	STDMETHOD(undefineOpById)(/*[in]*/ BSTR id);	
	STDMETHOD(undefineFuncsBySymbol)(/*[in]*/ BSTR symbol);	
	STDMETHOD(undefineOpsBySymbol)(/*[in]*/ BSTR symbol);
	STDMETHOD(getNbDefinedVars)(/*[out]*/ int *pNbDefinedVars);
	STDMETHOD(getVar)(/*[in]*/ int index, /*[out, retval]*/ BSTR *symbol);	
	STDMETHOD(defineFunc)(/*[in]*/ IMTFunction *pFunc);	
	

private:
	
	// converts a BSTR to a MTSTRING and free the BSTR's memory
	MTSTRING toMTSTRING(BSTR &bstr);



private:

	class LocalVariable : public MTVariableI
	{
	public:
		// set the variable name represented by this object
		void setName( const MTCHAR *name ){ m_name = name; }		

		virtual void setValue(MTDOUBLE value){ m_value = value;	}
		virtual MTDOUBLE getValue(){ return m_value; }		

		virtual const MTCHAR* getSymbol(){ return m_name.c_str(); }			
		
		virtual MTDOUBLE evaluate(unsigned int nbArgs, const MTDOUBLE *pArg){ return m_value; }

		
		virtual MTVariableI* spawn()
		{ 
			LocalVariable *pObj = new LocalVariable(); 
			pObj->setName(getSymbol());			
			return pObj;			
		}
		
		LocalVariable()
		{
			m_value = 0;
	
		}

	private:

		MTDOUBLE m_value;
		MTSTRING m_name;

	};

	class LocalVariableFactory : public MTVariableFactoryI				
	{
	public:

		// create a default variable object
		virtual MTVariableI* create(const MTCHAR *newVarName)
		{
			LocalVariable *pEval = new LocalVariable();			
			pEval->setName(newVarName);
			return pEval;
		}

		virtual MTVariableFactoryI* spawn(){ return new LocalVariableFactory(); }

	};

	
	class FunctionWrapper : public MTFunctionI
	{	
	public:

		void init(CComPtr<IMTFunction> &func);
		
		virtual const MTCHAR* getSymbol();

		virtual const MTCHAR* getHelpString();
		virtual const MTCHAR* getDescription();
		virtual int getNbArgs();
		virtual MTDOUBLE evaluate(unsigned int nbArgs, const MTDOUBLE *pArg);

		virtual MTFunctionI* spawn();

	private:

		CComPtr<IMTFunction> m_pFunc;
		MTSTRING m_symbol;
		MTSTRING m_helpString;
		MTSTRING m_description;

	};

	
private:
	
	MTParser *m_pParser;							// parser object
	MTExcepHelper m_excep;
public:
	STDMETHOD(get_expression)(BSTR* pVal);
	STDMETHOD(put_expression)(BSTR newVal);
	STDMETHOD(get_autoVarDefinitionEnabled)(SHORT* pVal);
	STDMETHOD(put_autoVarDefinitionEnabled)(SHORT newVal);
	STDMETHOD(get_syntax)(SMTSyntax* pVal);
	STDMETHOD(putref_syntax)(SMTSyntax newVal);
};

OBJECT_ENTRY_AUTO(__uuidof(MTParser), CMTParser)

#endif //__MTPARSER_H_
