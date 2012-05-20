	
// MTDouble.h : Declaration of the CMTDouble

#ifndef __MTDOUBLE_H_
#define __MTDOUBLE_H_

#include "resource.h"       // main symbols
#include "../MTParserLib/MTParserPublic.h"

/////////////////////////////////////////////////////////////////////////////
// CMTDouble
class ATL_NO_VTABLE CMTDouble : 
	public CComObjectRootEx<CComMultiThreadModel>,
	public CComCoClass<CMTDouble, &CLSID_MTDouble>,
	public ISupportErrorInfo,
	public IDispatchImpl<IMTDouble, &IID_IMTDouble, &LIBID_MTPARSERCOMLib>,
	public IDispatchImpl<IMTVariable, &IID_IMTVariable, &LIBID_MTPARSERCOMLib>
{
public:
	CMTDouble();


DECLARE_REGISTRY_RESOURCEID(IDR_MTDOUBLE)
DECLARE_GET_CONTROLLING_UNKNOWN()

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CMTDouble)
	COM_INTERFACE_ENTRY(IMTDouble)
//DEL 	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY_AGGREGATE(IID_IMarshal, m_pUnkMarshaler.p)
	COM_INTERFACE_ENTRY2(IDispatch, IMTDouble)
	COM_INTERFACE_ENTRY(IMTVariable)
END_COM_MAP()

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

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IMTDouble
public:
	STDMETHOD(get_name)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(get_value)(/*[out, retval]*/ double *pVal);
	STDMETHOD(put_value)(/*[in]*/ double newVal);
	STDMETHOD(create)(/*[in]*/ BSTR name, /*[in]*/ double value);
	STDMETHOD(setValue)(DOUBLE value);	
	STDMETHOD(getValue)(DOUBLE * pValue);

// IMTVariable
	STDMETHOD(getName)(BSTR * pName);		
	STDMETHOD(getNativeVar)(int* pVar);	

private:

	// COM variable adapter
	class MTDoubleAdapter : public MTVariableI						
	{
	public:

		void init(CComPtr<IMTDouble> &pVar);		

		// MTVariableI implementation

		// Return the variable name (unlimited length)
		virtual const MTCHAR* getSymbol();
		
		// Create a new instance of itself
		virtual MTVariableI* spawn();

		virtual MTDOUBLE evaluate(unsigned int nbArgs, const MTDOUBLE *pArg);

	private:

		CComPtr<IMTDouble> m_pVar;		
		MTSTRING m_name;
	};


private:

	CComBSTR m_name;
	double m_value;
	bool m_isCreated;
	MTDoubleAdapter m_var;	
};

#endif //__MTDOUBLE_H_
