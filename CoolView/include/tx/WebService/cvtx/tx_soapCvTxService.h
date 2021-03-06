/* tx_soapCvTxService.h
   Generated by gSOAP 2.8.21 from cvtx.h

Copyright(C) 2000-2014, Robert van Engelen, Genivia Inc. All Rights Reserved.
The generated code is released under one of the following licenses:
GPL or Genivia's license for commercial use.
This program is released under the GPL with the additional exemption that
compiling, linking, and/or using OpenSSL is allowed.
*/

#ifndef tx_soapCvTxService_H
#define tx_soapCvTxService_H
#include "tx_soapH.h"

namespace tx_soap {
class SOAP_CMAC CvTxService : public soap
{ public:
	/// Variables globally declared in cvtx.h (non-static)
	/// Constructor
	CvTxService();
	/// Construct from another engine state
	CvTxService(const struct soap&);
	/// Constructor with engine input+output mode control
	CvTxService(soap_mode iomode);
	/// Constructor with engine input and output mode control
	CvTxService(soap_mode imode, soap_mode omode);
	/// Destructor, also frees all deserialized data
	virtual ~CvTxService();
	/// Delete all deserialized data (with soap_destroy and soap_end)
	virtual	void destroy();
	/// Delete all deserialized data and reset to defaults
	virtual	void reset();
	/// Initializer used by constructor
	virtual	void CvTxService_init(soap_mode imode, soap_mode omode);
	/// Create a copy
	virtual	CvTxService *copy() SOAP_PURE_VIRTUAL;
	/// Close connection (normally automatic)
	virtual	int soap_close_socket();
	/// Force close connection (can kill a thread blocked on IO)
	virtual	int soap_force_close_socket();
	/// Return sender-related fault to sender
	virtual	int soap_senderfault(const char *string, const char *detailXML);
	/// Return sender-related fault with SOAP 1.2 subcode to sender
	virtual	int soap_senderfault(const char *subcodeQName, const char *string, const char *detailXML);
	/// Return receiver-related fault to sender
	virtual	int soap_receiverfault(const char *string, const char *detailXML);
	/// Return receiver-related fault with SOAP 1.2 subcode to sender
	virtual	int soap_receiverfault(const char *subcodeQName, const char *string, const char *detailXML);
	/// Print fault
	virtual	void soap_print_fault(FILE*);
#ifndef WITH_LEAN
	/// Print fault to stream
#ifndef WITH_COMPAT
	virtual	void soap_stream_fault(std::ostream&);
#endif
	/// Put fault into buffer
	virtual	char *soap_sprint_fault(char *buf, size_t len);
#endif
	/// Disables and removes SOAP Header from message
	virtual	void soap_noheader();
	/// Get SOAP Header structure (NULL when absent)
	virtual	const SOAP_ENV__Header *soap_header();
	/// Run simple single-thread (iterative, non-SSL) service on port until a connection error occurs (returns error code or SOAP_OK), use this->bind_flag = SO_REUSEADDR to rebind for a rerun
	virtual	int run(int port);
	/// Bind service to port (returns master socket or SOAP_INVALID_SOCKET)
	virtual	SOAP_SOCKET bind(const char *host, int port, int backlog);
	/// Accept next request (returns socket or SOAP_INVALID_SOCKET)
	virtual	SOAP_SOCKET accept();
#if defined(WITH_OPENSSL) || defined(WITH_GNUTLS)
	/// Then accept SSL handshake, when SSL is used
	virtual	int ssl_accept();
#endif
	/// Serve this request (returns error code or SOAP_OK)
	virtual	int serve();
	/// Used by serve() to dispatch a request (returns error code or SOAP_OK)
	virtual	int dispatch();

	///
	/// Service operations (you should define these):
	/// Note: compile with -DWITH_PURE_VIRTUAL for pure virtual methods
	///

	/// Web service operation 'QueryDBConference' (returns error code or SOAP_OK)
	virtual	int QueryDBConference(int offset, int count, ns__QueryDBConferenceResult *result) SOAP_PURE_VIRTUAL;

	/// Web service operation 'QueryDBTerminal' (returns error code or SOAP_OK)
	virtual	int QueryDBTerminal(int cid, ns__QueryDBTerminalResult *result) SOAP_PURE_VIRTUAL;

	/// Web service operation 'QueryDBEpisodeDates' (returns error code or SOAP_OK)
	virtual	int QueryDBEpisodeDates(int cid, std::string uri, ns__QueryDBEpisodeDatesResult *result) SOAP_PURE_VIRTUAL;

	/// Web service operation 'QueryDBEpisode' (returns error code or SOAP_OK)
	virtual	int QueryDBEpisode(int cid, std::string uri, int offset, int count, ns__QueryDBEpisodeResult *result) SOAP_PURE_VIRTUAL;

	/// Web service operation 'QueryDBEpisodeByTime' (returns error code or SOAP_OK)
	virtual	int QueryDBEpisodeByTime(int cid, std::string uri, LONG64 start, LONG64 end, ns__QueryDBEpisodeResult *result) SOAP_PURE_VIRTUAL;

	/// Web service operation 'QueryDBView' (returns error code or SOAP_OK)
	virtual	int QueryDBView(LONG64 eid, ns__QueryDBViewResult *result) SOAP_PURE_VIRTUAL;

	/// Web service operation 'StartRecord' (returns error code or SOAP_OK)
	virtual	int StartRecord(ns__StartRecordParam param, int *result) SOAP_PURE_VIRTUAL;

	/// Web service operation 'StopRecord' (returns error code or SOAP_OK)
	virtual	int StopRecord(ns__StopRecordParam param, int *result) SOAP_PURE_VIRTUAL;

	/// Web service operation 'GetRecordStatus' (returns error code or SOAP_OK)
	virtual	int GetRecordStatus(std::string focus, std::string uri, ns__GetRecordStatusResult *result) SOAP_PURE_VIRTUAL;
};

} // namespace tx_soap

#endif
