	
// MTDate.h : Declaration of the CMTDate

#ifndef __MTDATE_H_
#define __MTDATE_H_

#include "resource.h"       // main symbols
#include "../MTParserLib/MTParserPublic.h"

/////////////////////////////////////////////////////////////////////////////
// CMTDate
class ATL_NO_VTABLE CMTDate : 
	public CComObjectRootEx<CComMultiThreadModel>,
	public CComCoClass<CMTDate, &CLSID_MTDate>,
	public ISupportErrorInfo,
	public IDispatchImpl<IMTDate, &IID_IMTDate, &LIBID_MTPARSERCOMLib>,
	public IDispatchImpl<IMTVariable, &IID_IMTVariable, &LIBID_MTPARSERCOMLib>
{
public:
	CMTDate();
	
DECLARE_REGISTRY_RESOURCEID(IDR_MTDATE)
DECLARE_GET_CONTROLLING_UNKNOWN()

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CMTDate)
	COM_INTERFACE_ENTRY(IMTDate)
//DEL 	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY_AGGREGATE(IID_IMarshal, m_pUnkMarshaler.p)
	COM_INTERFACE_ENTRY2(IDispatch, IMTDate)
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

// IMTDate
public:
	STDMETHOD(format)(/*[out, retval]*/ BSTR *pDateStr);
	STDMETHOD(get_value)(/*[out, retval]*/ double *pVal);
	STDMETHOD(put_value)(/*[in]*/ double newVal);
	STDMETHOD(get_name)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(setTime)(/*[in]*/ int hour, /*[in]*/ int minute, /*[in]*/ int second);
	STDMETHOD(setDate)(/*[in]*/ int year, /*[in]*/ int month, /*[in]*/ int day);
	STDMETHOD(parseDateTime)(/*[in]*/ BSTR datetime);
	STDMETHOD(create)(/*[in]*/ BSTR name);
	STDMETHOD(setValue)(DOUBLE value);	
	STDMETHOD(getValue)(DOUBLE * pValue);
// IMTVariable
	STDMETHOD(getName)(BSTR * pName);		
	STDMETHOD(getNativeVar)(int* pVar);
	
private:

	// COM variable adapter
	class MTDateAdapter : public MTVariableI						
	{
	public:

		void init(CComPtr<IMTDate> &pVar);		

		// MTVariableI implementation

		// Return the variable name (unlimited length)
		virtual const MTCHAR* getSymbol();
		
		// Create a new instance of itself
		virtual MTVariableI* spawn();

		virtual MTDOUBLE evaluate(unsigned int nbArgs, const MTDOUBLE *pArg);

	private:

		CComPtr<IMTDate> m_pVar;		
		MTSTRING m_name;
	};



private:

	CComBSTR m_name;
	COleDateTime m_dt;
	bool m_isCreated;	
	MTDateAdapter m_var;
public:
	
	
};

#endif //__MTDATE_H_
