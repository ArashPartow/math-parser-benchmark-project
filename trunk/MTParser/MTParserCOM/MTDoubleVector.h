// MTDoubleVector.h : Declaration of the CMTDoubleVector

#pragma once
#include "resource.h"       // main symbols

#include "MTParserCOM.h"
#include "../MTParserLib/MTParserPublic.h"

// CMTDoubleVector

class ATL_NO_VTABLE CMTDoubleVector : 
	public CComObjectRootEx<CComMultiThreadModel>,
	public CComCoClass<CMTDoubleVector, &CLSID_MTDoubleVector>,
	public ISupportErrorInfo,
	public IDispatchImpl<IMTDoubleVector, &IID_IMTDoubleVector, &LIBID_MTPARSERCOMLib, /*wMajor =*/ 1, /*wMinor =*/ 0>,
	public IDispatchImpl<IMTVariable, &__uuidof(IMTVariable), &LIBID_MTPARSERCOMLib, /* wMajor = */ 1, /* wMinor = */ 0>
{
public:
	CMTDoubleVector();
	~CMTDoubleVector();
	
	DECLARE_REGISTRY_RESOURCEID(IDR_MTDOUBLEVECTOR)


	BEGIN_COM_MAP(CMTDoubleVector)
		COM_INTERFACE_ENTRY(IMTDoubleVector)
		COM_INTERFACE_ENTRY2(IDispatch, IMTVariable)
		COM_INTERFACE_ENTRY(ISupportErrorInfo)
		COM_INTERFACE_ENTRY(IMTVariable)
	END_COM_MAP()

	// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}

	void FinalRelease() 
	{
	}

public:


	// IMTVariable Methods
public:
	STDMETHOD(getName)( BSTR *  pName);
	STDMETHOD(create)(BSTR name);
	STDMETHOD(setValueVector)(SAFEARRAY * pValues);	
	STDMETHOD(setValueVectorVB6)(SAFEARRAY ** pValues);	
	STDMETHOD(getNativeVar)(int* pVar);	
	STDMETHOD(registerListener)(int pListener);
	STDMETHOD(unregisterListener)(int pListener);

private:

	void clear();

private:

	// COM variable vector adapter
	class MTDoubleVectorAdapter : public MTVariableI						
	{
	public:

		MTDoubleVectorAdapter();
		~MTDoubleVectorAdapter();

		void init(CComPtr<IMTDoubleVector> &pVar);
		void setPos(unsigned int pos);
		void setValues(MTDOUBLE *pValues, unsigned int nbValues);

		// MTVariableI implementation

		// Return the variable name (unlimited length)
		virtual const MTCHAR* getSymbol();
		
		// Create a new instance of itself
		virtual MTVariableI* spawn();

		virtual MTDOUBLE evaluate(unsigned int nbArgs, const MTDOUBLE *pArg);

	private:

		CComPtr<IMTDoubleVector> m_pVar;
		MTSTRING m_name;
		unsigned int m_pos;
		double *m_pValues;
		unsigned int m_nbValues;	
		static MTDOUBLE m_nanValue;

	};
private:

	// tell all listeners about the value change
	void updateListeners();


private:
	unsigned int m_pos;
	unsigned int m_nbValues;
	bool m_isCreated;
	CComBSTR m_name;
	double *m_pValues;
	MTDoubleVectorAdapter m_var;

	std::vector<MTDoubleVectorAdapter*> m_varListeners;	
};

OBJECT_ENTRY_AUTO(__uuidof(MTDoubleVector), CMTDoubleVector)
