/******************************************************************************
 *
 * Copyright(c) 2007 - 2011 Realtek Corporation. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of version 2 of the GNU General Public License as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 *
 ******************************************************************************/
#ifndef __WLAN_BSSDEF_H__
#define __WLAN_BSSDEF_H__


#define MAX_IE_SZ	768

#define NDIS_802_11_LENGTH_SSID         32
#define NDIS_802_11_LENGTH_RATES        8
#define NDIS_802_11_LENGTH_RATES_EX     16

struct ndis_802_11_ssid {
	u32  SsidLength;
	u8  Ssid[32];
};

enum NDIS_802_11_NETWORK_TYPE {
	NDIS802_11FH,
	NDIS802_11DS,
	NDIS802_11OFDM5,
	NDIS802_11OFDM24,
	NDIS802_11NetworkTypeMax    /*  not a real type - upper bound */
};

struct ndis_802_11_config_fh {
    u32           Length;             /*  Length of structure */
    u32           HopPattern;         /*  As defined by 802.11, MSB set */
    u32           HopSet;             /*  to one if non-802.11 */
    u32           DwellTime;          /*  units are Kusec */
};


/*	FW will only save the channel number in DSConfig.
 *	ODI Handler will convert the channel number to freq. number.
 */
struct ndis_802_11_config {
	u32           Length;             /*  Length of structure */
	u32           BeaconPeriod;       /*  units are Kusec */
	u32           ATIMWindow;         /*  units are Kusec */
	u32           DSConfig;           /*  Frequency, units are kHz */
	struct ndis_802_11_config_fh    FHConfig;
};

enum NDIS_802_11_NETWORK_INFRASTRUCTURE {
	NDIS802_11IBSS,
	NDIS802_11INFRA,
	NDIS802_11AUTOUNK,
	NDIS802_11INFRA_MAX,     /*  Not a real value, defined as upper bound */
	NDIS802_11APMODE
};

struct ndis_802_11_fixed_ies {
	u8  Timestamp[8];
	u16  BeaconInterval;
	u16  Capabilities;
};

struct ndis_802_11_variable_ies {
	u8  ElementID;
	u8  Length;
	u8  data[1];
};

/*
Length is the 4 bytes multiples of the sume of
	6 * sizeof(unsigned char) + 2 + sizeof (struct ndis_802_11_ssid) + sizeof (u32)
+   sizeof (long) + sizeof (NDIS_802_11_NETWORK_TYPE) + sizeof (struct ndis_802_11_config)
+   NDIS_802_11_LENGTH_RATES_EX * sizeof(unsigned char) + IELength

Except the IELength, all other fields are fixed length. Therefore, we can define a marco to present the
partial sum.
*/

enum NDIS_802_11_AUTHENTICATION_MODE {
	NDIS802_11AUTHMODEOPEN,
	NDIS802_11AUTHMODESHARED,
	NDIS802_11AUTHMODESWITCH,
	NDIS802_11AUTHMODEWPA,
	NDIS802_11AUTHMODEWPAPSK,
	NDIS802_11AUTHMODEWPANONE,
	NDIS802_11AUTHMODEMAX               /*  Not a real mode, defined as upper bound */
};

enum NDIS_802_11_ENCRYPTION_STATUS {
	NDIS802_11WEP_ENABLED,
	NDIS802_11ENCRYPTION1ENABLED = NDIS802_11WEP_ENABLED,
	NDIS802_11WEPDISABLED,
	NDIS802_11ENCRYPTION_DISABLED = NDIS802_11WEPDISABLED,
	NDIS802_11WEPKEYABSENT,
	NDIS802_11ENCRYPTION1KEYABSENT = NDIS802_11WEPKEYABSENT,
	NDIS802_11WEPNOTSUPPORTED,
	NDIS802_11ENCRYPTIONNOTSUPPORTED = NDIS802_11WEPNOTSUPPORTED,
	NDIS802_11ENCRYPTION2ENABLED,
	NDIS802_11ENCRYPTION2KEYABSENT,
	NDIS802_11ENCRYPTION3ENABLED,
	NDIS802_11ENCRYPTION3KEYABSENT
};

#define NDIS_802_11_AI_REQFI_CAPABILITIES      1
#define NDIS_802_11_AI_REQFI_LISTENINTERVAL    2
#define NDIS_802_11_AI_REQFI_CURRENTAPADDRESS  4

#define NDIS_802_11_AI_RESFI_CAPABILITIES      1
#define NDIS_802_11_AI_RESFI_STATUSCODE        2
#define NDIS_802_11_AI_RESFI_ASSOCIATIONID     4

struct ndis_802_11_ai_reqfi {
    u16 Capabilities;
    u16 ListenInterval;
    unsigned char  CurrentAPAddress[6];
};

struct ndis_802_11_ai_resfi {
    u16 Capabilities;
    u16 StatusCode;
    u16 AssociationId;
};

struct ndis_802_11_assoc_info {
    u32                   Length;
    u16                  AvailableRequestFixedIEs;
    struct ndis_802_11_ai_reqfi    RequestFixedIEs;
    u32                   RequestIELength;
    u32                   OffsetRequestIEs;
    u16                  AvailableResponseFixedIEs;
    struct ndis_802_11_ai_resfi ResponseFixedIEs;
    u32                   ResponseIELength;
    u32                   OffsetResponseIEs;
};

/*  Key mapping keys require a BSSID */
struct ndis_802_11_key {
    u32           Length;             /*  Length of this structure */
    u32           KeyIndex;
    u32           KeyLength;          /*  length of key in bytes */
    unsigned char BSSID[6];
    unsigned long long KeyRSC;
    u8           KeyMaterial[32];     /*  variable length depending on above field */
};

struct ndis_802_11_remove_key {
    u32                   Length;        /*  Length of this structure */
    u32                   KeyIndex;
    unsigned char BSSID[6];
};

struct ndis_802_11_wep {
    u32     Length;        /*  Length of this structure */
    u32     KeyIndex;      /*  0 is the per-client key, 1-N are the global keys */
    u32     KeyLength;     /*  length of key in bytes */
    u8     KeyMaterial[16];/*  variable length depending on above field */
};

struct ndis_802_11_auth_req {
    u32 Length;            /*  Length of structure */
    unsigned char Bssid[6];
    u32 Flags;
};

enum NDIS_802_11_STATUS_TYPE {
	Ndis802_11StatusType_Authentication,
	Ndis802_11StatusType_MediaStreamMode,
	Ndis802_11StatusType_PMKID_CandidateList,
	Ndis802_11StatusTypeMax    /*  not a real type, defined as an upper bound */
};

struct ndis_802_11_status_ind {
	enum NDIS_802_11_STATUS_TYPE StatusType;
};

/*  mask for authentication/integrity fields */
#define NDIS_802_11_AUTH_REQUEST_AUTH_FIELDS        0x0f
#define NDIS_802_11_AUTH_REQUEST_REAUTH			0x01
#define NDIS_802_11_AUTH_REQUEST_KEYUPDATE		0x02
#define NDIS_802_11_AUTH_REQUEST_PAIRWISE_ERROR		0x06
#define NDIS_802_11_AUTH_REQUEST_GROUP_ERROR		0x0E

/*  MIC check time, 60 seconds. */
#define MIC_CHECK_TIME	60000000

struct ndis_802_11_auth_event {
    struct ndis_802_11_status_ind Status;
    struct ndis_802_11_auth_req Request[1];
};

struct ndis_802_11_test {
    u32 Length;
    u32 Type;
    union {
        struct ndis_802_11_auth_event AuthenticationEvent;
        long RssiTrigger;
    } tt;
};

#ifndef Ndis802_11APMode
#define Ndis802_11APMode (NDIS802_11INFRA_MAX + 1)
#endif

struct wlan_phy_info {
	u8	SignalStrength;/* in percentage) */
	u8	SignalQuality;/* in percentage) */
	u8	Optimum_antenna;  /* for Antenna diversity */
	u8	Reserved_0;
};

struct wlan_bssid_ex {
	u32  Length;
	unsigned char  MacAddress[6];
	u8  Reserved[2];/* 0]: IS beacon frame */
	struct ndis_802_11_ssid  Ssid;
	u32  Privacy;
	long  Rssi;/* in dBM,raw data ,get from PHY) */
	enum NDIS_802_11_NETWORK_TYPE  NetworkTypeInUse;
	struct ndis_802_11_config  Configuration;
	enum NDIS_802_11_NETWORK_INFRASTRUCTURE  InfrastructureMode;
	unsigned char SupportedRates[NDIS_802_11_LENGTH_RATES_EX];
	struct wlan_phy_info PhyInfo;
	u32  IELength;
	u8  IEs[MAX_IE_SZ];	/* timestamp, beacon interval, and capability information) */
} __packed;

static inline uint get_wlan_bssid_ex_sz(struct wlan_bssid_ex *bss)
{
	return (sizeof(struct wlan_bssid_ex) - MAX_IE_SZ + bss->IELength);
}

struct	wlan_network {
	struct list_head list;
	int	network_type;	/* refer to ieee80211.h for WIRELESS_11A/B/G */
	int	fixed;			/*  set to fixed when not to be removed as site-surveying */
	unsigned long	last_scanned; /* timestamp for the network */
	int	aid;			/* will only be valid when a BSS is joinned. */
	int	join_res;
	struct wlan_bssid_ex network; /* must be the last item */
};

enum VRTL_CARRIER_SENSE
{
    DISABLE_VCS,
    ENABLE_VCS,
    AUTO_VCS
};

enum VCS_TYPE
{
    NONE_VCS,
    RTS_CTS,
    CTS_TO_SELF
};




#define PWR_CAM 0
#define PWR_MINPS 1
#define PWR_MAXPS 2
#define PWR_UAPSD 3
#define PWR_VOIP 4


enum UAPSD_MAX_SP
{
	NO_LIMIT,
       TWO_MSDU,
       FOUR_MSDU,
       SIX_MSDU
};


/* john */
#define NUM_PRE_AUTH_KEY 16
#define NUM_PMKID_CACHE NUM_PRE_AUTH_KEY

/*
*	WPA2
*/

struct pmkid_candidate {
	unsigned char BSSID[6];
	u32 Flags;
};

struct ndis_802_11_pmkid_list {
	u32 Version;       /*  Version of the structure */
	u32 NumCandidates; /*  No. of pmkid candidates */
	struct pmkid_candidate CandidateList[1];
};

struct ndis_802_11_auth_encr {
	enum NDIS_802_11_AUTHENTICATION_MODE AuthModeSupported;
	enum NDIS_802_11_ENCRYPTION_STATUS EncryptStatusSupported;

};

struct ndis_802_11_capa {
	u32  Length;
	u32  Version;
	u32  NoOfPMKIDs;
	u32  NoOfAuthEncryptPairsSupported;
	struct ndis_802_11_auth_encr AuthenticationEncryptionSupported[1];

};


#endif /* ifndef WLAN_BSSDEF_H_ */
