/* Copyright(C) 2014-2016 Doubango Telecom <https://github.com/sarandogou/webrtc-everywhere> */
// http://www.w3.org/TR/webrtc/#rtcstats-dictionary

#pragma once
#include "resource.h"       // main symbols

#include "../common/_Config.h"
#include "../common/_Common.h"
#include "../common/_AsyncEvent.h"

#include "webrtceverywhere_i.h"



#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Single-threaded COM objects are not properly supported on Windows CE platform, such as the Windows Mobile platforms that do not include full DCOM support. Define _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA to force ATL to support creating single-thread COM object's and allow use of it's single-threaded COM object implementations. The threading model in your rgs file was set to 'Free' as that is the only threading model supported in non DCOM Windows CE platforms."
#endif

using namespace ATL;


// CRTCStats

class ATL_NO_VTABLE CRTCStats :
	public _AsyncEventRaiser,
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CRTCStats, &CLSID_RTCStats>,
	public IDispatchImpl<IRTCStats, &IID_IRTCStats, &LIBID_webrtceverywhereLib, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
	CRTCStats();

DECLARE_REGISTRY_RESOURCEID(IDR_RTCSTATS)


BEGIN_COM_MAP(CRTCStats)
	COM_INTERFACE_ENTRY(IRTCStats)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()



	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct();

	void FinalRelease();

public:
	WE_INLINE void SetStats(std::shared_ptr<_RTCStats> & states) { m_Stats = states; }
	WE_INLINE std::shared_ptr<_RTCStats> GetStats() { return m_Stats; }

	STDMETHOD(get_timestamp)(__out DOUBLE* pVal);
	STDMETHOD(get_type)(__out BSTR* pVal);
	STDMETHOD(get_id)(__out BSTR* pVal);
	STDMETHOD(names)(__out VARIANT* Names);
	STDMETHOD(stat)(__in BSTR name, __out BSTR* pVal);

private:
	std::shared_ptr<_RTCStats> m_Stats;
	
};

OBJECT_ENTRY_AUTO(__uuidof(RTCStats), CRTCStats)
