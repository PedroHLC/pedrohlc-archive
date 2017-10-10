//FOR: miniupnpc 1.8
//TODO: INFILE
//HELP: http://fossies.org/dox/freeswitch-1.2.17/miniupnpc_8h.html
//Maintainer: PedroHLC


[CCode (cprefix = "UPNP", cheader_filename = "miniupnpc/igd_desc_parse.h")]
namespace IGD {
	[CCode (cname="MINIUPNPC_URL_MAXSIZE")]
	public static const uint URL_MAXSIZE;
	
	[CCode (cname="IGDdatas_service")]
	[SimpleType]
	public struct DatasService {
		char controlurl[IGD.URL_MAXSIZE];
		char eventsuburl[IGD.URL_MAXSIZE];
		char scpdurl[IGD.URL_MAXSIZE];
		char servicetype[IGD.URL_MAXSIZE];
	}
	
	[CCode (cname="IGDdatas")]
	[Compact]
	public class Datas {
		char curelt_name[IGD.URL_MAXSIZE];
		char url_base[IGD.URL_MAXSIZE];
		char presentation_url[IGD.URL_MAXSIZE];
		int level;
		
		IGD.DatasService cif;
		IGD.DatasService first;
		IGD.DatasService second;
		IGD.DatasService ipv6_fc;
		IGD.DatasService tmp;
	}
	
	/* TODO
void IGDstartelt(void *, const char *, int);
void IGDendelt(void *, const char *, int);
void IGDdata(void *, const char *, int);
void printIGD(struct IGDdatas *);
	*/
}

[CCode (cprefix = "UPNP", cheader_filename = "miniupnpc/miniupnpc.h")]
namespace UPNP {
	[CCode (cprefix = "UPNPDISCOVER_", cname="int")]
	public enum DiscoverResult {
		SUCCESS, UNKNOWN_ERROR, SOCKET_ERROR, MEMORY_ERROR
	}
	
	[CCode (cname="UPNParg")]
	[SimpleType]
	public struct Arg {
		string elt;
		string val;
	}
	
	[CCode (cname="simpleUPnPcommand")]
	public string simple_upnp_command (int s, string url, string service, string action, UPNP.Arg *args, char *buffer, int *bufsize);
	
	[CCode (cname="UPNPDev", free_function = "freeUPNPDevlist")]
	[Compact]
	public class Dev {
		unowned UPNP.Dev next;
		string desc_url;
		string st;
		uint scope_id;
		char buffer[2];
		
		[CCode (cname="upnpDiscover")]
		public Dev (int delay, string multicastif, string minissdpdsock, int sameport, int ipv6, UPNP.DiscoverResult error);
	}
	
	[CCode (cname="parserootdesc")]
	public static void parse_root_desc (string, int, IGD.Datas);
	
	[CCode (cname="UPNPUrls", free_function = "FreeUPNPUrls")]
	[SimpleType]
	public struct Urls {
		string control;
		string ipcon_desc;
		string control_cif;
		string control_6fc;
		string root_desc_url;
	}
	
	/* TODO
int UPNP_GetValidIGD(struct UPNPDev * devlist,
                 struct UPNPUrls * urls,
				 struct IGDdatas * data,
				 char * lanaddr, int lanaddrlen);
int UPNP_GetIGDFromUrl(const char * rootdescurl,
                   struct UPNPUrls * urls,
                   struct IGDdatas * data,
                   char * lanaddr, int lanaddrlen);
void GetUPNPUrls(struct UPNPUrls *, struct IGDdatas *,
            const char *, unsigned int);
void FreeUPNPUrls(struct UPNPUrls *);
int UPNPIGD_IsConnected(struct UPNPUrls *, struct IGDdatas *);

	[CCode (cheader_filename = "miniupnpc/portlistingparse.h")]
	
typedef enum { PortMappingEltNone,
       PortMappingEntry, NewRemoteHost,
       NewExternalPort, NewProtocol,
       NewInternalPort, NewInternalClient,
       NewEnabled, NewDescription,
       NewLeaseTime } portMappingElt;
struct PortMapping {
	LIST_ENTRY(PortMapping) entries;
	UNSIGNED_INTEGER leaseTime;
	unsigned short externalPort;
	unsigned short internalPort;
	char remoteHost[64];
	char internalClient[64];
	char description[64];
	char protocol[4];
	unsigned char enabled;
};
struct PortMappingParserData {
	LIST_HEAD(portmappinglisthead, PortMapping) head;
	portMappingElt curelt;
};
void ParsePortListing(const char * buffer, int bufsize,
                 struct PortMappingParserData * pdata);

void FreePortListing(struct PortMappingParserData * pdata);
	*/
	
}