// pHLC_VU_DLL.cpp : Defines the exported functions for the DLL application.
// Developed by PedroHLC 11-19-2011

#include "stdafx.h"
#include <Mmdeviceapi.h>
#include <Endpointvolume.h>
//#include <Audioclient.h>
#define DLLEXTERN extern "C" __declspec (dllexport)

DLLEXTERN long GetDefaultRenderDeviceMeter(){
	//Prepare COM System
	CoInitialize(NULL); 
	//Some Variables
	HRESULT result = NULL;
	IMMDeviceEnumerator *pEnumerator = NULL;
	IMMDevice *pDevice = NULL;
	IAudioMeterInformation* pMeterInfo = NULL;
	//IMMDeviceEnumerator
	result = CoCreateInstance(
		__uuidof(MMDeviceEnumerator), NULL,
		CLSCTX_ALL, __uuidof(IMMDeviceEnumerator),
		(LPVOID*)&pEnumerator);
	if(FAILED(result))
		return NULL;
	//IMMDevice
	result = pEnumerator->GetDefaultAudioEndpoint(eRender, eMultimedia, &pDevice);
	if(FAILED(result))
		return NULL;
	//IAudioMeterInformation
	result = pDevice->Activate(__uuidof(IAudioMeterInformation),
                           CLSCTX_ALL, NULL, (void**)&pMeterInfo);
	if(FAILED(result))
		return NULL;
	//The Sucessfull end
	return (long)pMeterInfo;
}

DLLEXTERN int GetPeaks(long pDefaultDeviceMeter, int channels_num, float* peaks){
	//Some Variables
	IAudioMeterInformation* pMeterInfo = (IAudioMeterInformation*)pDefaultDeviceMeter;
	HRESULT result = NULL;
	//Magic
	result = pMeterInfo->GetChannelsPeakValues(channels_num, peaks);
	if(FAILED(result))
		return NULL;
	//The Sucessfull end
	return 1;
}

DLLEXTERN float GetDefRendDevLeftPeak(){
	//Some Variables
	IAudioMeterInformation* pMeterInfo = (IAudioMeterInformation*)GetDefaultRenderDeviceMeter();
	HRESULT result = NULL;
	//Magic
	float peak[2];
	result = pMeterInfo->GetChannelsPeakValues(2, peak);
	if(FAILED(result))
		return NULL;
	//The Sucessfull end
	return peak[0];
}

DLLEXTERN float GetDefRendDevRightPeak(){
	//Some Variables
	IAudioMeterInformation* pMeterInfo = (IAudioMeterInformation*)GetDefaultRenderDeviceMeter();
	HRESULT result = NULL;
	//Magic
	float peak[2];
	result = pMeterInfo->GetChannelsPeakValues(2, peak);
	if(FAILED(result))
		return NULL;
	//The Sucessfull end
	return peak[1];
}