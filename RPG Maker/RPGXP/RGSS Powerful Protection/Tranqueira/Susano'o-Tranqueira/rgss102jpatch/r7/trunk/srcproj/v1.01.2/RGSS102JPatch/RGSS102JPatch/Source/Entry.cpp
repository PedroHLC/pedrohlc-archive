/*
 *	Entry.cpp file
 *
 *	RGSS102J Patch v1.0
 *
 *	by Shana
 */
#include "RGSS102J.h"

HMODULE	g_hRgss102Patch = NULL;

HMODULE	g_hRgss102j = NULL;

bool LoadRGSS102J();
void UnloadRGSS102J();

#ifdef __cplusplus
extern "C"
{
#endif	//	__cplusplus

void FixedExportVarAddr();
void FixedMappingTable();

#ifdef __cplusplus
}
#endif	//	__cplusplus

/**************************************************************************************
 *	BOOL WINAPI DllMain(HINSTANCE,DWORD fdwReason,LPVOID)
 *
 *	The dll main function, it's the entry of the dll.
 *
 *	param:
 *		fdwReason - state of the dll
 *
 *	return:
 *		TRUE
 *************************************************************************************/
BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD fdwReason, LPVOID)
{
	g_hRgss102Patch = (HMODULE)hInstance;

	switch(fdwReason)
	{
	case DLL_PROCESS_ATTACH:
		if (!LoadRGSS102J())
		{
			//	加载原RGSS102J.DLL失败的情况
			//	MessageBoxA(NULL, "加载RGSS102J.DLL失败！", "错误", 0);
			return FALSE;
		}
		FixedExportVarAddr();
		FixedMappingTable();
		break;
	case DLL_PROCESS_DETACH:
		UnloadRGSS102J();
		break;
	default:
		break;
	}
	
	return TRUE;
}

#define GET_AND_CHECK_RGSS102J_FUNC(funcname) do\
{\
	*((u32*)&Shana##funcname) = PtrToUlong(GetProcAddress(g_hRgss102j, #funcname));\
	if (Shana##funcname == 0)\
		return false;\
}while(0)

bool LoadRGSS102J()
{
	char buf[_MAX_PATH];

	DWORD len;

	if (!(len = GetModuleFileNameA(g_hRgss102Patch, buf, _MAX_PATH)))
		return false;

	for (--len;len > 0; --len)
	{
		if (buf[len] == '\\' || buf[len] == '/')
		{
			buf[len + 1] = 0;
			break;
		}
	}

	if (strcat_s(buf, "RGSS102J.DLL"))
		return false;

	for(u32 i = 0; buf[i]; ++i) { if (buf[i] == '/') buf[i] = '\\'; }

	g_hRgss102j = LoadLibraryA(buf);

	if (!g_hRgss102j)
		return false;

	GET_AND_CHECK_RGSS102J_FUNC(RGSSSetupRTP);
	GET_AND_CHECK_RGSS102J_FUNC(RGSSInitialize);
	GET_AND_CHECK_RGSS102J_FUNC(RGSSEval);
	GET_AND_CHECK_RGSS102J_FUNC(RGSSGameMain);

	GET_AND_CHECK_RGSS102J_FUNC(EncDefaultCharEncoding);
	GET_AND_CHECK_RGSS102J_FUNC(RGSSAddRTPPath);
	GET_AND_CHECK_RGSS102J_FUNC(RGSSAudioFinalize);
	GET_AND_CHECK_RGSS102J_FUNC(RGSSAudioInitialize);
	GET_AND_CHECK_RGSS102J_FUNC(RGSSClearRTPPath);
	GET_AND_CHECK_RGSS102J_FUNC(RGSSErrorMessage);
	GET_AND_CHECK_RGSS102J_FUNC(RGSSErrorType);

	GET_AND_CHECK_RGSS102J_FUNC(RGSSFinalize);			//	@9
	GET_AND_CHECK_RGSS102J_FUNC(RGSSGC);				//	@10

	GET_AND_CHECK_RGSS102J_FUNC(RGSSGetBool);			//	@12
	GET_AND_CHECK_RGSS102J_FUNC(RGSSGetDouble);			//	@13
	GET_AND_CHECK_RGSS102J_FUNC(RGSSGetInt);			//	@14
	GET_AND_CHECK_RGSS102J_FUNC(RGSSGetPathWithRTP);	//	@15
	GET_AND_CHECK_RGSS102J_FUNC(RGSSGetRTPPath);		//	@16
	GET_AND_CHECK_RGSS102J_FUNC(RGSSGetStringACP);		//	@17
	GET_AND_CHECK_RGSS102J_FUNC(RGSSGetStringUTF8);		//	@18
	GET_AND_CHECK_RGSS102J_FUNC(RGSSGetTable);			//	@19

	GET_AND_CHECK_RGSS102J_FUNC(RGSSSetString);			//	@21
	GET_AND_CHECK_RGSS102J_FUNC(RGSSSetStringACP);		//	@22
	GET_AND_CHECK_RGSS102J_FUNC(RGSSSetStringUTF8);		//	@23

	GET_AND_CHECK_RGSS102J_FUNC(RegDefaultSyntax);		//	@25
	GET_AND_CHECK_RGSS102J_FUNC(RegEncodingASCII);		//	@26
	GET_AND_CHECK_RGSS102J_FUNC(RegEncodingEUC_JP);		//	@27
	GET_AND_CHECK_RGSS102J_FUNC(RegEncodingSJIS);		//	@28
	GET_AND_CHECK_RGSS102J_FUNC(RegEncodingUTF8);		//	@29
	GET_AND_CHECK_RGSS102J_FUNC(RegSyntaxRuby);			//	@30

	GET_AND_CHECK_RGSS102J_FUNC(enc_get_left_adjust_char_head);	//  @31  ; enc_get_left_adjust_char_head
	GET_AND_CHECK_RGSS102J_FUNC(enc_get_prev_char_head);		//	@32  ; enc_get_prev_char_head
	GET_AND_CHECK_RGSS102J_FUNC(enc_get_right_adjust_char_head);//	@33  ; enc_get_right_adjust_char_head
	GET_AND_CHECK_RGSS102J_FUNC(re_alloc_pattern);				//	@34  ; re_alloc_pattern
	GET_AND_CHECK_RGSS102J_FUNC(regex_end);						//	@35  ; regex_end
	GET_AND_CHECK_RGSS102J_FUNC(regex_error_code_to_str);		//	@36  ; regex_error_code_to_str
	GET_AND_CHECK_RGSS102J_FUNC(regex_foreach_name);			//	@37  ; regex_foreach_name
	GET_AND_CHECK_RGSS102J_FUNC(regex_free);					//	@38  ; regex_free
	GET_AND_CHECK_RGSS102J_FUNC(regex_get_encoding);			//	@39  ; regex_get_encoding
	GET_AND_CHECK_RGSS102J_FUNC(regex_get_options);				//	@40  ; regex_get_options
	GET_AND_CHECK_RGSS102J_FUNC(regex_get_syntax);				//	@41  ; regex_get_syntax
	GET_AND_CHECK_RGSS102J_FUNC(regex_init);					//	@42  ; regex_init
	GET_AND_CHECK_RGSS102J_FUNC(regex_match);					//	@43  ; regex_match
	GET_AND_CHECK_RGSS102J_FUNC(regex_name_to_backref_number);	//	@44  ; regex_name_to_backref_number
	GET_AND_CHECK_RGSS102J_FUNC(regex_name_to_group_numbers);	//	@45  ; regex_name_to_group_numbers
	GET_AND_CHECK_RGSS102J_FUNC(regex_new);						//	@46  ; regex_new
	GET_AND_CHECK_RGSS102J_FUNC(regex_number_of_names);			//	@47  ; regex_number_of_names
	GET_AND_CHECK_RGSS102J_FUNC(regex_recompile);				//	@48  ; regex_recompile
	GET_AND_CHECK_RGSS102J_FUNC(regex_region_clear);			//	@49  ; regex_region_clear
	GET_AND_CHECK_RGSS102J_FUNC(regex_region_copy);				//	@50  ; regex_region_copy
	GET_AND_CHECK_RGSS102J_FUNC(regex_region_free);				//	@51  ; regex_region_free
	GET_AND_CHECK_RGSS102J_FUNC(regex_region_new);				//	@52  ; regex_region_new
	GET_AND_CHECK_RGSS102J_FUNC(regex_region_resize);			//	@53  ; regex_region_resize
	GET_AND_CHECK_RGSS102J_FUNC(regex_search);					//	@54  ; regex_search
	GET_AND_CHECK_RGSS102J_FUNC(regex_set_verb_warn_func);		//	@55  ; regex_set_verb_warn_func
	GET_AND_CHECK_RGSS102J_FUNC(regex_set_warn_func);			//	@56  ; regex_set_warn_func
	GET_AND_CHECK_RGSS102J_FUNC(regex_version);					//	@57  ; regex_version
	GET_AND_CHECK_RGSS102J_FUNC(ruby_re_adjust_startpos);		//	@58  ; ruby_re_adjust_startpos
	GET_AND_CHECK_RGSS102J_FUNC(ruby_re_compile_pattern);		//	@59  ; ruby_re_compile_pattern
	GET_AND_CHECK_RGSS102J_FUNC(ruby_re_free_pattern);			//  @60  ; ruby_re_free_pattern
	GET_AND_CHECK_RGSS102J_FUNC(ruby_re_free_registers);		//	@61  ; ruby_re_free_registers
	GET_AND_CHECK_RGSS102J_FUNC(ruby_re_match);					//	@62  ; ruby_re_match
	GET_AND_CHECK_RGSS102J_FUNC(ruby_re_mbcinit);				//	@63  ; ruby_re_mbcinit
	GET_AND_CHECK_RGSS102J_FUNC(ruby_re_recompile_pattern);		//	@64  ; ruby_re_recompile_pattern
	GET_AND_CHECK_RGSS102J_FUNC(ruby_re_search);				//	@65  ; ruby_re_search
	GET_AND_CHECK_RGSS102J_FUNC(ruby_re_set_casetable);			//	@66  ; ruby_re_set_casetable

	return true;
}

void UnloadRGSS102J()
{
	if (g_hRgss102j)
	{
		::FreeLibrary(g_hRgss102j);
		g_hRgss102j = NULL;
	}
}