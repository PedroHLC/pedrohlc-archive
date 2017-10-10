/*
 *	RGSS102J.cpp file
 *
 *	RGSS102J Patch v1.0
 *
 *	by Shana
 */
#include "RGSS102J.h"
#include "RGSS102JEx.h"

RGSS102JFunc ShanaRGSSSetupRTP = NULL;
RGSS102JFunc ShanaRGSSInitialize = NULL;
RGSS102JFunc ShanaRGSSEval = NULL;
RGSS102JFunc ShanaRGSSGameMain = NULL;

RGSS102JFunc ShanaEncDefaultCharEncoding = NULL;
RGSS102JFunc ShanaRGSSAddRTPPath = NULL;
RGSS102JFunc ShanaRGSSAudioFinalize = NULL;
RGSS102JFunc ShanaRGSSAudioInitialize = NULL;
RGSS102JFunc ShanaRGSSClearRTPPath = NULL;
RGSS102JFunc ShanaRGSSErrorMessage = NULL;
RGSS102JFunc ShanaRGSSErrorType = NULL;

#define imp_attr_accessor(method)\
\
RGSS102JFunc Shana##method = NULL;\
\
u32	method(struct ParamUChar param)\
{\
	u32	ret = Shana##method(param);\
\
	return ret;\
}\

u32 EncDefaultCharEncoding(struct ParamUChar param)	//	@1
{
	u32 ret = ShanaEncDefaultCharEncoding(param);

	return ret;
}

u32 RGSSAddRTPPath(struct ParamUChar param)			//	@2
{
	u32 ret = ShanaRGSSAddRTPPath(param);

	return ret;
}

u32 RGSSAudioFinalize(struct ParamUChar param)		//	@3
{
	u32 ret = ShanaRGSSAudioFinalize(param);

	return ret;
}

u32 RGSSAudioInitialize(struct ParamUChar param)	//	@4
{
	u32 ret = ShanaRGSSAudioInitialize(param);

	return ret;
}

u32 RGSSClearRTPPath(struct ParamUChar param)		//	@5
{
	u32 ret = ShanaRGSSClearRTPPath(param);

	return ret;
}

u32 RGSSErrorMessage(struct ParamUChar param)		//	@6
{
	u32 ret = ShanaRGSSErrorMessage(param);

	return ret;
}

u32 RGSSErrorType(struct ParamUChar param)			//	@7
{
	u32 ret = ShanaRGSSErrorType(param);

	return ret;
}

u32 RGSSEval(struct ParamUChar param)				//	@8
{
	u32 ret = ShanaRGSSEval(param);

	return ret;
}

imp_attr_accessor(RGSSFinalize)			//	@9
imp_attr_accessor(RGSSGC)				//	@10

/*
 *	param02 - script
 */
u32 RGSSGameMain(struct ParamUChar param)			//	@11
{
	Init_RGSS102JEx();								//	Init RGSS102J Ext Library

	u32 ret = ShanaRGSSGameMain(param);

	return ret;
}

imp_attr_accessor(RGSSGetBool)			//	@12
imp_attr_accessor(RGSSGetDouble)		//	@13
imp_attr_accessor(RGSSGetInt)			//	@14
imp_attr_accessor(RGSSGetPathWithRTP)	//	@15
imp_attr_accessor(RGSSGetRTPPath)		//	@16
imp_attr_accessor(RGSSGetStringACP)		//	@17
imp_attr_accessor(RGSSGetStringUTF8)	//	@18
imp_attr_accessor(RGSSGetTable)			//	@19

u32 RGSSInitialize(struct ParamUChar param)			//	@20
{
	u32 ret = ShanaRGSSInitialize(param);

#ifdef _DEBUG
	const char* str = (const char*)UlongToPtr(0x100E8ED0 - (0x10003a60 - PtrToUlong(ShanaRGSSInitialize)));

	CLSID id = *(CLSID*)UlongToPtr(0x10109218 - (0x10003a60 - PtrToUlong(ShanaRGSSInitialize)));
#endif	//	_DEBUG

	return ret;
}

imp_attr_accessor(RGSSSetString)		//	@21
imp_attr_accessor(RGSSSetStringACP)		//	@22
imp_attr_accessor(RGSSSetStringUTF8)	//	@23

//	char * inipath
u32 RGSSSetupRTP(struct ParamUChar param)			//	@24
{
	u32 ret = ShanaRGSSSetupRTP(param);

	return ret;
}

imp_attr_accessor(RegDefaultSyntax)		//	@25
imp_attr_accessor(RegEncodingASCII)		//	@26
imp_attr_accessor(RegEncodingEUC_JP)	//	@27
imp_attr_accessor(RegEncodingSJIS)		//	@28
imp_attr_accessor(RegEncodingUTF8)		//	@29
imp_attr_accessor(RegSyntaxRuby)		//	@30

imp_attr_accessor(enc_get_left_adjust_char_head)	//  @31  ; enc_get_left_adjust_char_head
imp_attr_accessor(enc_get_prev_char_head)			//	@32  ; enc_get_prev_char_head
imp_attr_accessor(enc_get_right_adjust_char_head)	//	@33  ; enc_get_right_adjust_char_head
imp_attr_accessor(re_alloc_pattern)					//	@34  ; re_alloc_pattern
imp_attr_accessor(regex_end)						//	@35  ; regex_end
imp_attr_accessor(regex_error_code_to_str)			//	@36  ; regex_error_code_to_str
imp_attr_accessor(regex_foreach_name)				//	@37  ; regex_foreach_name
imp_attr_accessor(regex_free)						//	@38  ; regex_free
imp_attr_accessor(regex_get_encoding)				//	@39  ; regex_get_encoding
imp_attr_accessor(regex_get_options)				//	@40  ; regex_get_options
imp_attr_accessor(regex_get_syntax)					//	@41  ; regex_get_syntax
imp_attr_accessor(regex_init)						//	@42  ; regex_init
imp_attr_accessor(regex_match)						//	@43  ; regex_match
imp_attr_accessor(regex_name_to_backref_number)		//	@44  ; regex_name_to_backref_number
imp_attr_accessor(regex_name_to_group_numbers)		//	@45  ; regex_name_to_group_numbers
imp_attr_accessor(regex_new)						//	@46  ; regex_new
imp_attr_accessor(regex_number_of_names)			//	@47  ; regex_number_of_names
imp_attr_accessor(regex_recompile)					//	@48  ; regex_recompile
imp_attr_accessor(regex_region_clear)				//	@49  ; regex_region_clear
imp_attr_accessor(regex_region_copy)				//	@50  ; regex_region_copy
imp_attr_accessor(regex_region_free)				//	@51  ; regex_region_free
imp_attr_accessor(regex_region_new)					//	@52  ; regex_region_new
imp_attr_accessor(regex_region_resize)				//	@53  ; regex_region_resize
imp_attr_accessor(regex_search)						//	@54  ; regex_search
imp_attr_accessor(regex_set_verb_warn_func)			//	@55  ; regex_set_verb_warn_func
imp_attr_accessor(regex_set_warn_func)				//	@56  ; regex_set_warn_func
imp_attr_accessor(regex_version)					//	@57  ; regex_version
imp_attr_accessor(ruby_re_adjust_startpos)			//	@58  ; ruby_re_adjust_startpos
imp_attr_accessor(ruby_re_compile_pattern)			//	@59  ; ruby_re_compile_pattern
imp_attr_accessor(ruby_re_free_pattern)				//  @60  ; ruby_re_free_pattern
imp_attr_accessor(ruby_re_free_registers)			//	@61  ; ruby_re_free_registers
imp_attr_accessor(ruby_re_match)					//	@62  ; ruby_re_match
imp_attr_accessor(ruby_re_mbcinit)					//	@63  ; ruby_re_mbcinit
imp_attr_accessor(ruby_re_recompile_pattern)		//	@64  ; ruby_re_recompile_pattern
imp_attr_accessor(ruby_re_search)					//	@65  ; ruby_re_search
imp_attr_accessor(ruby_re_set_casetable)			//	@66  ; ruby_re_set_casetable