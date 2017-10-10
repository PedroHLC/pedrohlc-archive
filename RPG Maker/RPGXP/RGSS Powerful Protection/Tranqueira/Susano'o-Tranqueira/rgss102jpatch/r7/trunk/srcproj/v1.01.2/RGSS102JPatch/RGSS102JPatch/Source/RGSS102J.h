/*
 *	RGSS102J.h file
 *
 *	RGSS102J Patch v1.0
 *
 *	by Shana
 */
#ifndef __RGSS102J_H__
#define __RGSS102J_H__

#include <windows.h>
#include "Types.h"

struct ParamUlong
{
	u32 v[16];
};

struct ParamUChar
{
	u8* v[16];
};

#define attr_accessor(method)	extern RGSS102JFunc Shana##method

typedef int (* RGSS102JFunc)(struct ParamUChar);

#ifdef __cplusplus
	extern "C"
	{
#endif

	attr_accessor(RGSSSetupRTP);
	attr_accessor(RGSSInitialize);
	attr_accessor(RGSSEval);
	attr_accessor(RGSSGameMain);

	attr_accessor(EncDefaultCharEncoding);
	attr_accessor(RGSSAddRTPPath);
	attr_accessor(RGSSAudioFinalize);
	attr_accessor(RGSSAudioInitialize);
	attr_accessor(RGSSClearRTPPath);
	attr_accessor(RGSSErrorMessage);
	attr_accessor(RGSSErrorType);

	attr_accessor(RGSSFinalize);		//	@9
	attr_accessor(RGSSGC);				//	@10

	attr_accessor(RGSSGetBool);			//	@12
	attr_accessor(RGSSGetDouble);		//	@13
	attr_accessor(RGSSGetInt);			//	@14
	attr_accessor(RGSSGetPathWithRTP);	//	@15
	attr_accessor(RGSSGetRTPPath);		//	@16
	attr_accessor(RGSSGetStringACP);	//	@17
	attr_accessor(RGSSGetStringUTF8);	//	@18
	attr_accessor(RGSSGetTable);		//	@19

	attr_accessor(RGSSSetString);		//	@21
	attr_accessor(RGSSSetStringACP);	//	@22
	attr_accessor(RGSSSetStringUTF8);	//	@23

	attr_accessor(RegDefaultSyntax);	//	@25
	attr_accessor(RegEncodingASCII);	//	@26
	attr_accessor(RegEncodingEUC_JP);	//	@27
	attr_accessor(RegEncodingSJIS);		//	@28
	attr_accessor(RegEncodingUTF8);		//	@29
	attr_accessor(RegSyntaxRuby);		//	@30

	attr_accessor(enc_get_left_adjust_char_head);	//  @31  ; enc_get_left_adjust_char_head
	attr_accessor(enc_get_prev_char_head);			//	@32  ; enc_get_prev_char_head
	attr_accessor(enc_get_right_adjust_char_head);	//	@33  ; enc_get_right_adjust_char_head
	attr_accessor(re_alloc_pattern);				//	@34  ; re_alloc_pattern
	attr_accessor(regex_end);						//	@35  ; regex_end
	attr_accessor(regex_error_code_to_str);			//	@36  ; regex_error_code_to_str
	attr_accessor(regex_foreach_name);				//	@37  ; regex_foreach_name
	attr_accessor(regex_free);						//	@38  ; regex_free
	attr_accessor(regex_get_encoding);				//	@39  ; regex_get_encoding
	attr_accessor(regex_get_options);				//	@40  ; regex_get_options
	attr_accessor(regex_get_syntax);				//	@41  ; regex_get_syntax
	attr_accessor(regex_init);						//	@42  ; regex_init
	attr_accessor(regex_match);						//	@43  ; regex_match
	attr_accessor(regex_name_to_backref_number);	//	@44  ; regex_name_to_backref_number
	attr_accessor(regex_name_to_group_numbers);		//	@45  ; regex_name_to_group_numbers
	attr_accessor(regex_new);						//	@46  ; regex_new
	attr_accessor(regex_number_of_names);			//	@47  ; regex_number_of_names
	attr_accessor(regex_recompile);					//	@48  ; regex_recompile
	attr_accessor(regex_region_clear);				//	@49  ; regex_region_clear
	attr_accessor(regex_region_copy);				//	@50  ; regex_region_copy
	attr_accessor(regex_region_free);				//	@51  ; regex_region_free
	attr_accessor(regex_region_new);				//	@52  ; regex_region_new
	attr_accessor(regex_region_resize);				//	@53  ; regex_region_resize
	attr_accessor(regex_search);					//	@54  ; regex_search
	attr_accessor(regex_set_verb_warn_func);		//	@55  ; regex_set_verb_warn_func
	attr_accessor(regex_set_warn_func);				//	@56  ; regex_set_warn_func
	attr_accessor(regex_version);					//	@57  ; regex_version
	attr_accessor(ruby_re_adjust_startpos);			//	@58  ; ruby_re_adjust_startpos
	attr_accessor(ruby_re_compile_pattern);			//	@59  ; ruby_re_compile_pattern
	attr_accessor(ruby_re_free_pattern);			//  @60  ; ruby_re_free_pattern
	attr_accessor(ruby_re_free_registers);			//	@61  ; ruby_re_free_registers
	attr_accessor(ruby_re_match);					//	@62  ; ruby_re_match
	attr_accessor(ruby_re_mbcinit);					//	@63  ; ruby_re_mbcinit
	attr_accessor(ruby_re_recompile_pattern);		//	@64  ; ruby_re_recompile_pattern
	attr_accessor(ruby_re_search);					//	@65  ; ruby_re_search
	attr_accessor(ruby_re_set_casetable);			//	@66  ; ruby_re_set_casetable

#ifdef __cplusplus
	}
#endif


#endif

