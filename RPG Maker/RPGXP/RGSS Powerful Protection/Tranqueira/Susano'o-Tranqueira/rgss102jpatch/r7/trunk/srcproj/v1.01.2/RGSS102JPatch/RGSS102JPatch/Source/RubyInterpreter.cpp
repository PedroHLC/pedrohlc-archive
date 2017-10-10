/**
 *	@file		RubyInterpreter.cpp
 *
 *	@desc		RGSS102J补丁之解释器导出相关的实现文件
 *
 *	@author		Syalon
 *
 *	@history	2009/07/04	初版
 */

#include "RubyInterpreter.h"
#include "RGSS102J.h"

/***
 *	RGSS102JPatch需要导出的变量定义
 */
VALUE*	ptr_rb_cArray		= (VALUE*)UlongToPtr(0x10166668);
VALUE*	ptr_rb_cBignum		= (VALUE*)UlongToPtr(0x10166664);
VALUE*	ptr_rb_cClass		= (VALUE*)UlongToPtr(0x1016655C);
VALUE*	ptr_rb_cData		= (VALUE*)UlongToPtr(0x10166554);
VALUE*	ptr_rb_cDir			= (VALUE*)UlongToPtr(0x1016665C);
VALUE*	ptr_rb_cFalseClass	= (VALUE*)UlongToPtr(0x10166560);
VALUE*	ptr_rb_cFile		= (VALUE*)UlongToPtr(0x101665C8);
VALUE*	ptr_rb_cFixnum		= (VALUE*)UlongToPtr(0x1016657C);
VALUE*	ptr_rb_cFloat		= (VALUE*)UlongToPtr(0x10166584);
VALUE*	ptr_rb_cHash		= (VALUE*)UlongToPtr(0x101665C0);
VALUE*	ptr_rb_cIO			= (VALUE*)UlongToPtr(0x101665AC);
VALUE*	ptr_rb_cInteger		= (VALUE*)UlongToPtr(0x1016658C);
VALUE*	ptr_rb_cModule		= (VALUE*)UlongToPtr(0x10166564);
VALUE*	ptr_rb_cNilClass	= (VALUE*)UlongToPtr(0x10166568);
VALUE*	ptr_rb_cNumeric		= (VALUE*)UlongToPtr(0x10166578);
VALUE*	ptr_rb_cObject		= (VALUE*)UlongToPtr(0x10166574);
VALUE*	ptr_rb_cProc		= (VALUE*)UlongToPtr(0x101665D8);
VALUE*	ptr_rb_cRange		= (VALUE*)UlongToPtr(0x1016651C);
VALUE*	ptr_rb_cRegexp		= (VALUE*)UlongToPtr(0x10166518);
VALUE*	ptr_rb_cString		= (VALUE*)UlongToPtr(0x101664F8);
VALUE*	ptr_rb_cStruct		= (VALUE*)UlongToPtr(0x101664F4);
VALUE*	ptr_rb_cSymbol		= (VALUE*)UlongToPtr(0x1016656C);
VALUE*	ptr_rb_cThread		= (VALUE*)UlongToPtr(0x101665EC);
VALUE*	ptr_rb_cTime		= (VALUE*)UlongToPtr(0x101664F0);
VALUE*	ptr_rb_cTrueClass	= (VALUE*)UlongToPtr(0x10166570);

VALUE*	ptr_rb_eArgError			= (VALUE*)UlongToPtr(0x10166644);
VALUE*	ptr_rb_eEOFError			= (VALUE*)UlongToPtr(0x101665A0);
VALUE*	ptr_rb_eException			= (VALUE*)UlongToPtr(0x10166600);
VALUE*	ptr_rb_eFatal				= (VALUE*)UlongToPtr(0x10166648);
VALUE*	ptr_rb_eFloatDomainError	= (VALUE*)UlongToPtr(0x10166588);
VALUE*	ptr_rb_eIOError				= (VALUE*)UlongToPtr(0x10166598);
VALUE*	ptr_rb_eIndexError			= (VALUE*)UlongToPtr(0x10166608);
VALUE*	ptr_rb_eInterrupt			= (VALUE*)UlongToPtr(0x10166610);
VALUE*	ptr_rb_eLoadError			= (VALUE*)UlongToPtr(0x10166604);
VALUE*	ptr_rb_eNameError			= (VALUE*)UlongToPtr(0x10166620);
VALUE*	ptr_rb_eNoMemError			= (VALUE*)UlongToPtr(0x10166638);
VALUE*	ptr_rb_eNoMethodError		= (VALUE*)UlongToPtr(0x10166650);
VALUE*	ptr_rb_eNotImpError			= (VALUE*)UlongToPtr(0x1016662C);
VALUE*	ptr_rb_eRangeError			= (VALUE*)UlongToPtr(0x10166614);
VALUE*	ptr_rb_eRuntimeError		= (VALUE*)UlongToPtr(0x10166640);
VALUE*	ptr_rb_eScriptError			= (VALUE*)UlongToPtr(0x1016663C);
VALUE*	ptr_rb_eSecurityError		= (VALUE*)UlongToPtr(0x10166630);
VALUE*	ptr_rb_eSignal				= (VALUE*)UlongToPtr(0x1016664C);
VALUE*	ptr_rb_eStandardError		= (VALUE*)UlongToPtr(0x10166618);
VALUE*	ptr_rb_eSyntaxError			= (VALUE*)UlongToPtr(0x10166628);
VALUE*	ptr_rb_eSystemCallError		= (VALUE*)UlongToPtr(0x10166624);
VALUE*	ptr_rb_eSystemExit			= (VALUE*)UlongToPtr(0x1016660C);
VALUE*	ptr_rb_eTypeError			= (VALUE*)UlongToPtr(0x10166654);
VALUE*	ptr_rb_eZeroDivError		= (VALUE*)UlongToPtr(0x10166580);

VALUE*	ptr_rb_mComparable			= (VALUE*)UlongToPtr(0x10166660);
VALUE*	ptr_rb_mEnumerable			= (VALUE*)UlongToPtr(0x10166658);
VALUE*	ptr_rb_mErrno				= (VALUE*)UlongToPtr(0x10166634);
VALUE*	ptr_rb_mFileTest			= (VALUE*)UlongToPtr(0x101665CC);
VALUE*	ptr_rb_mGC					= (VALUE*)UlongToPtr(0x101665C4);
VALUE*	ptr_rb_mKernel				= (VALUE*)UlongToPtr(0x10166558);
VALUE*	ptr_rb_mMath				= (VALUE*)UlongToPtr(0x10166590);
VALUE*	ptr_rb_mPrecision			= (VALUE*)UlongToPtr(0x10166530);
VALUE*	ptr_rb_mProcGID				= (VALUE*)UlongToPtr(0x10166524);
VALUE*	ptr_rb_mProcID_Syscall		= (VALUE*)UlongToPtr(0x10166528);
VALUE*	ptr_rb_mProcUID				= (VALUE*)UlongToPtr(0x1016652C);
VALUE*	ptr_rb_mProcess				= (VALUE*)UlongToPtr(0x10166520);

int*	ptr_ruby_safe_level			= (int*)UlongToPtr(0x1013159C);

/***
 *	未导出的函数原型声明
 */
static VALUE rb_call(VALUE, VALUE, ID, int, const VALUE*, int);

enum __SymbolIdList
{
	//	导出函数
	SI_rb_Float = 0,
	SI_rb_add_method,
	SI_rb_alias,
	SI_rb_alias_variable,
	SI_rb_any_to_s,
	SI_rb_apply,
	SI_rb_ary_aref,
	SI_rb_ary_assoc,
	SI_rb_ary_clear,
	SI_rb_ary_cmp,
	SI_rb_ary_concat,
	SI_rb_ary_delete,
	SI_rb_ary_delete_at,
	SI_rb_ary_dup,
	SI_rb_ary_each,
	SI_rb_ary_entry,
	SI_rb_ary_freeze,
	SI_rb_ary_includes,
	SI_rb_ary_join,
	SI_rb_ary_new,
	SI_rb_ary_new2,
	SI_rb_ary_new3,
	SI_rb_ary_new4,
	SI_rb_ary_plus,
	SI_rb_ary_pop,
	SI_rb_ary_push,
	SI_rb_ary_rassoc,
	SI_rb_ary_reverse,
	SI_rb_ary_shift,
	SI_rb_ary_sort,
	SI_rb_ary_sort_bang,
	SI_rb_ary_store,
	SI_rb_ary_to_ary,
	SI_rb_ary_to_s,
	SI_rb_ary_unshift,
	SI_rb_assoc_new,
	SI_rb_attr,
	SI_rb_attr_get,
	SI_rb_autoload,
	SI_rb_autoload_load,
	SI_rb_autoload_p,

	SI_rb_backref_get,
	SI_rb_backref_set,
	SI_rb_backtrace,
	SI_rb_big2dbl,
	SI_rb_big2ll,
	SI_rb_big2long,
	SI_rb_big2str,
	SI_rb_big2ull,
	SI_rb_big2ulong,
	SI_rb_big_2comp,
	SI_rb_big_and,
	SI_rb_big_clone,
	SI_rb_big_divmod,
	SI_rb_big_lshift,
	SI_rb_big_minus,
	SI_rb_big_mul,
	SI_rb_big_norm,
	SI_rb_big_or,
	SI_rb_big_plus,
	SI_rb_big_pow,
	SI_rb_big_rand,
	SI_rb_big_xor,
	SI_rb_block_given_p,
	SI_rb_block_proc,
	SI_rb_bug,

	SI_rb_call_inits,
	SI_rb_call_super,
	SI_rb_catch,
	SI_rb_check_array_type,
	SI_rb_check_convert_type,
	SI_rb_check_frozen,
	SI_rb_check_inheritable,
	SI_rb_check_safe_obj,
	SI_rb_check_safe_str,
	SI_rb_check_string_type,
	SI_rb_check_type,
	SI_rb_class2name,
	SI_rb_class_boot,
	SI_rb_class_inherited,
	SI_rb_class_init_copy,
	SI_rb_class_instance_methods,
	SI_rb_class_new,
	SI_rb_class_new_instance,
	SI_rb_class_path,
	SI_rb_class_private_instance_methods,
	SI_rb_class_protected_instance_methods,
	SI_rb_class_public_instance_methods,
	SI_rb_class_real,
	SI_rb_clear_cache,
	SI_rb_clear_cache_by_class,
	SI_rb_cmperr,
	SI_rb_cmpint,
	SI_rb_compile_cstr,
	SI_rb_compile_error,
	SI_rb_compile_error_append,
	SI_rb_compile_file,
	SI_rb_compile_string,
	SI_rb_const_defined,
	SI_rb_const_defined_at,
	SI_rb_const_defined_from,
	SI_rb_const_get,
	SI_rb_const_get_at,
	SI_rb_const_get_from,
	SI_rb_const_list,
	SI_rb_const_set,
	SI_rb_convert_type,
	SI_rb_copy_generic_ivar,
	SI_rb_cstr2inum,
	SI_rb_cstr_to_dbl,
	SI_rb_cstr_to_inum,
	SI_rb_cv_get,
	SI_rb_cv_set,
	SI_rb_cvar_defined,
	SI_rb_cvar_get,
	SI_rb_cvar_set,

	SI_rb_data_object_alloc,
	SI_rb_dbl2big,
	SI_rb_dbl_cmp,
	SI_rb_define_alias,
	SI_rb_define_alloc_func,
	SI_rb_define_attr,
	SI_rb_define_class,
	SI_rb_define_class_id,
	SI_rb_define_class_under,
	SI_rb_define_class_variable,
	SI_rb_define_const,
	SI_rb_define_global_const,
	SI_rb_define_global_function,
	SI_rb_define_hooked_variable,
	SI_rb_define_method,
	SI_rb_define_method_id,
	SI_rb_define_module,
	SI_rb_define_module_function,
	SI_rb_define_module_id,
	SI_rb_define_module_under,
	SI_rb_define_private_method,
	SI_rb_define_protected_method,
	SI_rb_define_readonly_variable,
	SI_rb_define_singleton_method,
	SI_rb_define_variable,
	SI_rb_define_virtual_variable,
	SI_rb_detach_process,
	SI_rb_disable_super,
	SI_rb_dvar_curr,
	SI_rb_dvar_defined,
	SI_rb_dvar_push,
	SI_rb_dvar_ref,

	SI_rb_each,
	SI_rb_enable_super,
	SI_rb_ensure,
	SI_rb_env_path_tainted,
	SI_rb_eof_error,
	SI_rb_eql,
	SI_rb_equal,
	SI_rb_error_frozen,
	SI_rb_eval_cmd,
	SI_rb_eval_string,
	SI_rb_eval_string_protect,
	SI_rb_eval_string_wrap,
	SI_rb_exc_fatal,
	SI_rb_exc_new,
	SI_rb_exc_new2,
	SI_rb_exc_new3,
	SI_rb_exc_raise,
	SI_rb_exec_end_proc,
	SI_rb_exit,
	SI_rb_extend_object,

	SI_rb_f_abort,
	SI_rb_f_exec,
	SI_rb_f_exit,
	SI_rb_f_global_variables,
	SI_rb_f_kill,
	SI_rb_f_lambda,
	SI_rb_f_require,
	SI_rb_f_sprintf,
	SI_rb_f_trace_var,
	SI_rb_f_untrace_var,
	SI_rb_fatal,
	SI_rb_fdopen,
	SI_rb_file_const,
	SI_rb_file_expand_path,
	SI_rb_file_open,
	SI_rb_file_s_expand_path,
	SI_rb_file_sysopen,
	SI_rb_find_file,
	SI_rb_find_file_ext,
	SI_rb_fix2int,
	SI_rb_fix2str,
	SI_rb_float_new,
	SI_rb_fopen,
	SI_rb_frame_last_func,
	SI_rb_free_generic_ivar,
	SI_rb_frozen_class_p,
	SI_rb_funcall,
	SI_rb_funcall2,
	SI_rb_funcall3,

	SI_rb_gc,
	SI_rb_gc_call_finalizer_at_exit,
	SI_rb_gc_copy_finalizer,
	SI_rb_gc_disable,
	SI_rb_gc_enable,
	SI_rb_gc_force_recycle,
	SI_rb_gc_mark,
	SI_rb_gc_mark_frame,
	SI_rb_gc_mark_global_tbl,
	SI_rb_gc_mark_locations,
	SI_rb_gc_mark_maybe,
	SI_rb_gc_mark_parser,
	SI_rb_gc_mark_threads,
	SI_rb_gc_mark_trap_list,
	SI_rb_gc_register_address,
	SI_rb_gc_start,
	SI_rb_gc_unregister_address,
	SI_rb_generic_ivar_table,
	SI_rb_get_kcode,
	SI_rb_getc,
	SI_rb_gets,
	SI_rb_glob,
	SI_rb_global_entry,
	SI_rb_global_variable,
	SI_rb_globi,
	SI_rb_gv_get,
	SI_rb_gv_set,
	SI_rb_gvar_defined,
	SI_rb_gvar_get,
	SI_rb_gvar_set,

	SI_rb_hash,
	SI_rb_hash_aref,
	SI_rb_hash_aset,
	SI_rb_hash_delete,
	SI_rb_hash_delete_if,
	SI_rb_hash_freeze,
	SI_rb_hash_new,
	SI_rb_hash_reject_bang,
	SI_rb_hash_select,
	SI_rb_hash_values_at,

	SI_rb_id2name,
	SI_rb_id_attrset,
	SI_rb_include_module,
	SI_rb_inspect,
	SI_rb_inspecting_p,
	SI_rb_int2big,
	SI_rb_int2inum,
	SI_rb_intern,
	SI_rb_interrupt,
	SI_rb_invalid_str,
	SI_rb_io_addstr,
	SI_rb_io_binmode,
	SI_rb_io_check_closed,
	SI_rb_io_check_readable,
	SI_rb_io_check_writable,
	SI_rb_io_close,
	SI_rb_io_eof,
	SI_rb_io_flags_mode,
	SI_rb_io_fptr_finalize,
	SI_rb_io_fread,
	SI_rb_io_fwrite,
	SI_rb_io_getc,
	SI_rb_io_gets,
	SI_rb_io_mode_flags,
	SI_rb_io_print,
	SI_rb_io_printf,
	SI_rb_io_puts,
	SI_rb_io_synchronized,
	SI_rb_io_taint_check,
	SI_rb_io_unbuffered,
	SI_rb_io_ungetc,
	SI_rb_io_wait_readable,
	SI_rb_io_wait_writable,
	SI_rb_io_write,
	SI_rb_is_class_id,
	SI_rb_is_const_id,
	SI_rb_is_instance_id,
	SI_rb_is_junk_id,
	SI_rb_is_local_id,
	SI_rb_iter_break,
	SI_rb_iterate,
	SI_rb_iterator_p,
	SI_rb_iv_get,
	SI_rb_iv_set,
	SI_rb_ivar_defined,
	SI_rb_ivar_get,
	SI_rb_ivar_set,

	SI_rb_jump_tag,

	SI_rb_kcode,

	SI_rb_lastline_get,
	SI_rb_lastline_set,
	SI_rb_ll2big,
	SI_rb_ll2inum,
	SI_rb_load,
	SI_rb_load_fail,
	SI_rb_load_file,
	SI_rb_load_protect,
	SI_rb_loaderror,

	SI_rb_make_metaclass,
	SI_rb_mark_end_proc,
	SI_rb_mark_generic_ivar,
	SI_rb_mark_generic_ivar_tbl,
	SI_rb_mark_hash,
	SI_rb_mark_tbl,
	SI_rb_marshal_dump,
	SI_rb_marshal_load,
	SI_rb_match_busy,
	SI_rb_mem_clear,
	SI_rb_memcicmp,
	SI_rb_memcmp,
	SI_rb_memerror,
	SI_rb_memsearch,
	SI_rb_method_boundp,
	SI_rb_method_node,
	SI_rb_mod_ancestors,
	SI_rb_mod_class_variables,
	SI_rb_mod_const_at,
	SI_rb_mod_const_missing,
	SI_rb_mod_const_of,
	SI_rb_mod_constants,
	SI_rb_mod_include_p,
	SI_rb_mod_included_modules,
	SI_rb_mod_init_copy,
	SI_rb_mod_module_eval,
	SI_rb_mod_name,
	SI_rb_mod_remove_const,
	SI_rb_mod_remove_cvar,
	SI_rb_module_new,

	SI_rb_name_class,
	SI_rb_name_error,
	SI_rb_newobj,
	SI_rb_node_newnode,
	SI_rb_notimplement,
	SI_rb_num2dbl,
	SI_rb_num2fix,
	SI_rb_num2int,
	SI_rb_num2ll,
	SI_rb_num2long,
	SI_rb_num2ull,
	SI_rb_num2ulong,
	SI_rb_num_coerce_bin,
	SI_rb_num_coerce_cmp,
	SI_rb_num_coerce_relop,
	SI_rb_num_zerodiv,

	SI_rb_obj_alloc,
	SI_rb_obj_as_string,
	SI_rb_obj_call_init,
	SI_rb_obj_class,
	SI_rb_obj_classname,
	SI_rb_obj_clone,
	SI_rb_obj_dup,
	SI_rb_obj_freeze,
	SI_rb_obj_id,
	SI_rb_obj_id_obsolete,
	SI_rb_obj_infect,
	SI_rb_obj_init_copy,
	SI_rb_obj_instance_eval,
	SI_rb_obj_instance_variables,
	SI_rb_obj_is_instance_of,
	SI_rb_obj_is_kind_of,
	SI_rb_obj_remove_instance_variable,
	SI_rb_obj_singleton_methods,
	SI_rb_obj_taint,
	SI_rb_obj_tainted,
	SI_rb_obj_type,
	SI_rb_obj_untaint,

	SI_rb_p,
	SI_rb_parser_append_print,
	SI_rb_parser_while_loop,
	SI_rb_path2class,
	SI_rb_path_check,
	SI_rb_path_end,
	SI_rb_path_last_separator,
	SI_rb_path_next,
	SI_rb_path_skip_prefix,
	SI_rb_proc_exec,
	SI_rb_proc_new,
	SI_rb_proc_times,
	SI_rb_protect,
	SI_rb_protect_inspect,
	SI_rb_provide,
	SI_rb_provided,

	SI_rb_quad_pack,
	SI_rb_quad_unpack,

	SI_rb_raise,
	SI_rb_range_beg_len,
	SI_rb_range_new,
	SI_rb_read_check,
	SI_rb_read_pending,
	SI_rb_reg_adjust_startpos,
	SI_rb_reg_eqq,
	SI_rb_reg_last_match,
	SI_rb_reg_match,
	SI_rb_reg_match2,
	SI_rb_reg_match_last,
	SI_rb_reg_match_post,
	SI_rb_reg_match_pre,
	SI_rb_reg_mbclen2,
	SI_rb_reg_new,
	SI_rb_reg_nth_defined,
	SI_rb_reg_nth_match,
	SI_rb_reg_options,
	SI_rb_reg_quote,
	SI_rb_reg_regcomp,
	SI_rb_reg_regsub,
	SI_rb_reg_search,
	SI_rb_remove_method,
	SI_rb_require,
	SI_rb_require_safe,
	SI_rb_rescue,
	SI_rb_rescue2,
	SI_rb_reserved_word,
	SI_rb_respond_to,

	SI_rb_scan_args,
	SI_rb_secure,
	SI_rb_secure_update,
	SI_rb_set_class_path,
	SI_rb_set_end_proc,
	SI_rb_set_kcode,
	SI_rb_set_safe_level,
	SI_rb_singleton_class,
	SI_rb_singleton_class_attached,
	SI_rb_singleton_class_clone,
	SI_rb_source_filename,
	SI_rb_str2cstr,
	SI_rb_str2inum,
	SI_rb_str_append,
	SI_rb_str_associate,
	SI_rb_str_associated,
	SI_rb_str_buf_append,
	SI_rb_str_buf_cat,
	SI_rb_str_buf_cat2,
	SI_rb_str_buf_new,
	SI_rb_str_buf_new2,
	SI_rb_str_cat,
	SI_rb_str_cat2,
	SI_rb_str_cmp,
	SI_rb_str_concat,
	SI_rb_str_dump,
	SI_rb_str_dup,
	SI_rb_str_dup_frozen,
	SI_rb_str_freeze,
	SI_rb_str_hash,
	SI_rb_str_inspect,
	SI_rb_str_intern,
	SI_rb_str_modify,
	SI_rb_str_new,
	SI_rb_str_new2,
	SI_rb_str_new3,
	SI_rb_str_new4,
	SI_rb_str_new5,
	SI_rb_str_plus,
	SI_rb_str_resize,
	SI_rb_str_setter,
	SI_rb_str_split,
	SI_rb_str_substr,
	SI_rb_str_times,
	SI_rb_str_to_dbl,
	SI_rb_str_to_inum,
	SI_rb_str_to_str,
	SI_rb_str_update,
	SI_rb_str_upto,
	SI_rb_string_value,
	SI_rb_string_value_cstr,
	SI_rb_string_value_ptr,
	SI_rb_struct_alloc,
	SI_rb_struct_aref,
	SI_rb_struct_aset,
	SI_rb_struct_define,
	SI_rb_struct_getmember,
	SI_rb_struct_iv_get,
	SI_rb_struct_new,
	SI_rb_svar,
	SI_rb_sym_all_symbols,
	SI_rb_sys_fail,
	SI_rb_sys_warning,
	SI_rb_syswait,

	SI_rb_tainted_str_new,
	SI_rb_tainted_str_new2,

	SI_rb_thread_alone,
	SI_rb_thread_atfork,
	SI_rb_thread_create,
	SI_rb_thread_current,
	SI_rb_thread_fd_close,
	SI_rb_thread_fd_writable,
	SI_rb_thread_group,
	SI_rb_thread_interrupt,
	SI_rb_thread_kill,
	SI_rb_thread_list,
	SI_rb_thread_local_aref,
	SI_rb_thread_local_aset,
	SI_rb_thread_main,
	SI_rb_thread_polling,
	SI_rb_thread_run,
	SI_rb_thread_schedule,
	SI_rb_thread_select,
	SI_rb_thread_signal_raise,
	SI_rb_thread_sleep,
	SI_rb_thread_sleep_forever,
	SI_rb_thread_stop,
	SI_rb_thread_trap_eval,
	SI_rb_thread_wait_fd,
	SI_rb_thread_wait_for,
	SI_rb_thread_wakeup,
	SI_rb_throw,
	SI_rb_time_interval,
	SI_rb_time_new,
	SI_rb_time_timeval,
	SI_rb_to_id,
	SI_rb_to_int,
	SI_rb_trap_exec,
	SI_rb_trap_exit,
	SI_rb_trap_restore_mask,

	SI_rb_uint2big,
	SI_rb_uint2inum,
	SI_rb_ull2big,
	SI_rb_ull2inum,
	SI_rb_undef,
	SI_rb_undef_alloc_func,
	SI_rb_undef_method,

	SI_rb_values_at,

	SI_rb_w32_accept,
	SI_rb_w32_asynchronize,
	SI_rb_w32_bind,
	SI_rb_w32_close,
	SI_rb_w32_closedir,
	SI_rb_w32_connect,
	SI_rb_w32_enter_critical,
	SI_rb_w32_fclose,
	SI_rb_w32_fdclr,
	SI_rb_w32_fdisset,
	SI_rb_w32_fdset,
	SI_rb_w32_free_environ,
	SI_rb_w32_get_environ,
	SI_rb_w32_get_osfhandle,
	SI_rb_w32_getc,
	SI_rb_w32_getcwd,
	SI_rb_w32_getenv,
	SI_rb_w32_gethostbyaddr,
	SI_rb_w32_gethostbyname,
	SI_rb_w32_gethostname,
	SI_rb_w32_getpeername,
	SI_rb_w32_getpid,
	SI_rb_w32_getprotobyname,
	SI_rb_w32_getprotobynumber,
	SI_rb_w32_getservbyname,
	SI_rb_w32_getservbyport,
	SI_rb_w32_getsockname,
	SI_rb_w32_getsockopt,
	SI_rb_w32_ioctlsocket,
	SI_rb_w32_leave_critical,
	SI_rb_w32_listen,
	SI_rb_w32_main_context,
	SI_rb_w32_opendir,
	SI_rb_w32_putc,
	SI_rb_w32_readdir,
	SI_rb_w32_recv,
	SI_rb_w32_recvfrom,
	SI_rb_w32_rename,
	SI_rb_w32_rewinddir,
	SI_rb_w32_seekdir,
	SI_rb_w32_select,
	SI_rb_w32_send,
	SI_rb_w32_sendto,
	SI_rb_w32_setsockopt,
	SI_rb_w32_shutdown,
	SI_rb_w32_sleep,
	SI_rb_w32_snprintf,
	SI_rb_w32_socket,
	SI_rb_w32_stat,
	SI_rb_w32_strerror,
	SI_rb_w32_telldir,
	SI_rb_w32_times,
	SI_rb_w32_utime,
	SI_rb_w32_vsnprintf,

	SI_rb_waitpid,
	SI_rb_warn,
	SI_rb_warning,
	SI_rb_with_disable_interrupt,
	SI_rb_write_error,
	SI_rb_write_error2,
	SI_rb_yield,
	SI_rb_yield_splat,
	SI_rb_yield_values,

	SI_re_set_syntax,

	SI_ruby_xmalloc,

	SI_st_add_direct,
	SI_st_cleanup_safe,
	SI_st_copy,
	SI_st_delete,
	SI_st_delete_safe,
	SI_st_foreach,
	SI_st_free_table,
	SI_st_init_numtable,
	SI_st_init_numtable_with_size,
	SI_st_init_strtable,
	SI_st_init_strtable_with_size,
	SI_st_init_table,
	SI_st_init_table_with_size,
	SI_st_insert,
	SI_st_lookup,

	//	未导出函数
	SI_rb_call,

	SymbolIdList_MAX_NUMS
};

static unsigned long sMappingTable[SymbolIdList_MAX_NUMS] = 
{
	//	导出的函数
	0x10051B00, //	rb_Float

	0x0, //	rb_add_method
	0x0, //	rb_alias
	0x0, //	rb_alias_variable
	0x0, //	rb_any_to_s
	0x0, //	rb_apply
	0x1001A4E0, //	rb_ary_aref
	0x0, //	rb_ary_assoc
	0x0, //	rb_ary_clear
	0x0, //	rb_ary_cmp
	0x1001C090, //	rb_ary_concat
	0x0, //	rb_ary_delete
	0x0, //	rb_ary_delete_at
	0x0, //	rb_ary_dup
	0x1001ADA0, //	rb_ary_each
	0x1001A3D0, //	rb_ary_entry
	0x0, //	rb_ary_freeze
	0x0, //	rb_ary_includes
	0x0, //	rb_ary_join
	0x10019E30, //	rb_ary_new
	0x10019E10, //	rb_ary_new2
	0x0, //	rb_ary_new3
	0x10019ED0, //	rb_ary_new4
	0x0, //	rb_ary_plus
	0x1001A180, //	rb_ary_pop
	0x1001A120, //	rb_ary_push
	0x0, //	rb_ary_rassoc
	0x0, //	rb_ary_reverse
	0x1001A260, //	rb_ary_shift
	0x0, //	rb_ary_sort
	0x1001B260, //	rb_ary_sort_bang
	0x1001A030, //	rb_ary_store
	0x0, //	rb_ary_to_ary
	0x0, //	rb_ary_to_s
	0x0, //	rb_ary_unshift
	0x0, //	rb_assoc_new
	0x0, //	rb_attr
	0x0, //	rb_attr_get
	0x10082B60, //	rb_autoload
	0x0, //	rb_autoload_load
	0x0, //	rb_autoload_p

	0x0, //	rb_backref_get
	0x0, //	rb_backref_set
	0x0, //	rb_backtrace
	0x1001E8D0, //	rb_big2dbl
	0x0, //	rb_big2ll
	0x0, //	rb_big2long
	0x0, //	rb_big2str
	0x0, //	rb_big2ull
	0x0, //	rb_big2ulong
	0x0, //	rb_big_2comp
	0x0, //	rb_big_and
	0x0, //	rb_big_clone
	0x0, //	rb_big_divmod
	0x0, //	rb_big_lshift
	0x0, //	rb_big_minus
	0x0, //	rb_big_mul
	0x0, //	rb_big_norm
	0x0, //	rb_big_or
	0x0, //	rb_big_plus
	0x0, //	rb_big_pow
	0x0, //	rb_big_rand
	0x0, //	rb_big_xor
	0x10029180, //	rb_block_given_p
	0x1002EC50, //	rb_block_proc
	0x100258B0, //	rb_bug

	0x0, //	rb_call_inits
	0x1002A250, //	rb_call_super
	0x0, //	rb_catch
	0x0, //	rb_check_array_type
	0x0, //	rb_check_convert_type
	0x0, //	rb_check_frozen
	0x0, //	rb_check_inheritable
	0x0, //	rb_check_safe_obj
	0x10027120, //	rb_check_safe_str
	0x0, //	rb_check_string_type
	0x10026940, //	rb_check_type
	0x0, //	rb_class2name
	0x100207C0, //	rb_class_boot
	0x0, //	rb_class_inherited
	0x0, //	rb_class_init_copy
	0x0, //	rb_class_instance_methods
	0x0, //	rb_class_new
	0x10050B90, //	rb_class_new_instance
	0x0, //	rb_class_path
	0x0, //	rb_class_private_instance_methods
	0x0, //	rb_class_protected_instance_methods
	0x0, //	rb_class_public_instance_methods
	0x1004FDC0, //	rb_class_real
	0x0, //	rb_clear_cache
	0x0, //	rb_clear_cache_by_class
	0x0, //	rb_cmperr
	0x0, //	rb_cmpint
	0x0, //	rb_compile_cstr
	0x0, //	rb_compile_error
	0x0, //	rb_compile_error_append
	0x0, //	rb_compile_file
	0x0, //	rb_compile_string
	0x100825B0, //	rb_const_defined
	0x0, //	rb_const_defined_at
	0x0, //	rb_const_defined_from
	0x10082DD0, //	rb_const_get
	0x0, //	rb_const_get_at
	0x0, //	rb_const_get_from
	0x0, //	rb_const_list
	0x100826E0, //	rb_const_set
	0x0, //	rb_convert_type
	0x0, //	rb_copy_generic_ivar
	0x0, //	rb_cstr2inum
	0x0, //	rb_cstr_to_dbl
	0x0, //	rb_cstr_to_inum
	0x100831D0, //	rb_cv_get
	0x10083190, //	rb_cv_set
	0x0, //	rb_cvar_defined
	0x10083110, //	rb_cvar_get
	0x10083010, //	rb_cvar_set

	0x1003F4E0, //	rb_data_object_alloc
	0x0, //	rb_dbl2big
	0x0, //	rb_dbl_cmp
	0x100215F0, //	rb_define_alias
	0x10027430, //	rb_define_alloc_func
	0x0, //	rb_define_attr
	0x10020AB0, //	rb_define_class
	0x0, //	rb_define_class_id
	0x10020BB0, //	rb_define_class_under
	0x0, //	rb_define_class_variable
	0x10082700, //	rb_define_const
	0x10082760, //	rb_define_global_const
	0x100215D0, //	rb_define_global_function
	0x100834E0, //	rb_define_hooked_variable
	0x10021330, //	rb_define_method
	0x0, //	rb_define_method_id
	0x10020D70, //	rb_define_module
	0x10021560, //	rb_define_module_function
	0x0, //	rb_define_module_id
	0x10020E00, //	rb_define_module_under
	0x10021370, //	rb_define_private_method
	0x0, //	rb_define_protected_method
	0x10083570, //	rb_define_readonly_variable
	0x10021510, //	rb_define_singleton_method
	0x10083530, //	rb_define_variable
	0x100835C0, //	rb_define_virtual_variable
	0x0, //	rb_detach_process
	0x0, //	rb_disable_super
	0x0, //	rb_dvar_curr
	0x0, //	rb_dvar_defined
	0x0, //	rb_dvar_push
	0x0, //	rb_dvar_ref

	0x100246B0, //	rb_each
	0x0, //	rb_enable_super
	0x10029AA0, //	rb_ensure
	0x0, //	rb_env_path_tainted
	0x0, //	rb_eof_error
	0x0, //	rb_eql
	0x0, //	rb_equal
	0x0, //	rb_error_frozen
	0x0, //	rb_eval_cmd
	0x10032DE0, //	rb_eval_string
	0x0, //	rb_eval_string_protect
	0x0, //	rb_eval_string_wrap
	0x0, //	rb_exc_fatal
	0x0, //	rb_exc_new
	0x100259D0, //	rb_exc_new2
	0x0, //	rb_exc_new3
	0x0, //	rb_exc_raise
	0x0, //	rb_exec_end_proc
	0x0, //	rb_exit
	0x1002B100, //	rb_extend_object

	0x0, //	rb_f_abort
	0x0, //	rb_f_exec
	0x0, //	rb_f_exit
	0x0, //	rb_f_global_variables
	0x0, //	rb_f_kill
	0x0, //	rb_f_lambda
	0x0, //	rb_f_require
	0x0, //	rb_f_sprintf
	0x10083630, //	rb_f_trace_var
	0x10081610, //	rb_f_untrace_var
	0x0, //	rb_fatal
	0x0, //	rb_fdopen
	0x1003BD80, //	rb_file_const
	0x0, //	rb_file_expand_path
	0x0, //	rb_file_open
	0x0, //	rb_file_s_expand_path
	0x0, //	rb_file_sysopen
	0x0, //	rb_find_file
	0x0, //	rb_find_file_ext
	0x0, //	rb_fix2int
	0x1004E450, //	rb_fix2str
	0x1004CBF0, //	rb_float_new
	0x10043C10, //	rb_fopen
	0x0, //	rb_frame_last_func
	0x0, //	rb_free_generic_ivar
	0x0, //	rb_frozen_class_p
	0x10037B20, //	rb_funcall
	0x0, //	rb_funcall2
	0x10037BC0, //	rb_funcall3

	0x0, //	rb_gc
	0x0, //	rb_gc_call_finalizer_at_exit
	0x0, //	rb_gc_copy_finalizer
	0x0, //	rb_gc_disable
	0x0, //	rb_gc_enable
	0x0, //	rb_gc_force_recycle
	0x1003EB90, //	rb_gc_mark
	0x0, //	rb_gc_mark_frame
	0x10081520, //	rb_gc_mark_global_tbl
	0x0, //	rb_gc_mark_locations
	0x1003EFA0, //	rb_gc_mark_maybe
	0x10056DA6, //	rb_gc_mark_parser
	0x1002C6B0, //	rb_gc_mark_threads
	0x10074E20, //	rb_gc_mark_trap_list
	0x1003F410, //	rb_gc_register_address
	0x0, //	rb_gc_start
	0x1003D690, //	rb_gc_unregister_address
	0x0, //	rb_generic_ivar_table
	0x0, //	rb_get_kcode
	0x0, //	rb_getc
	0x0, //	rb_gets
	0x0, //	rb_glob
	0x0, //	rb_global_entry
	0x1003F490, //	rb_global_variable
	0x0, //	rb_globi
	0x0, //	rb_gv_get
	0x0, //	rb_gv_set
	0x0, //	rb_gvar_defined
	0x0, //	rb_gvar_get
	0x0, //	rb_gvar_set

	0x0, //	rb_hash
	0x1003FBA0, //	rb_hash_aref
	0x10040210, //	rb_hash_aset
	0x1003FE50, //	rb_hash_delete
	0x1003FFD0, //	rb_hash_delete_if
	0x0, //	rb_hash_freeze
	0x1003FA60, //	rb_hash_new
	0x0, //	rb_hash_reject_bang
	0x0, //	rb_hash_select
	0x0, //	rb_hash_values_at

	0x10057040, //	rb_id2name
	0x0, //	rb_id_attrset
	0x10020F90, //	rb_include_module
	0x0, //	rb_inspect
	0x0, //	rb_inspecting_p
	0x0, //	rb_int2big
	0x1001DCA0, //	rb_int2inum
	0x10056E0A, //	rb_intern
	0x0, //	rb_interrupt
	0x0, //	rb_invalid_str
	0x0, //	rb_io_addstr
	0x0, //	rb_io_binmode
	0x0, //	rb_io_check_closed
	0x0, //	rb_io_check_readable
	0x0, //	rb_io_check_writable
	0x0, //	rb_io_close
	0x0, //	rb_io_eof
	0x0, //	rb_io_flags_mode
	0x0, //	rb_io_fptr_finalize
	0x0, //	rb_io_fread
	0x0, //	rb_io_fwrite
	0x0, //	rb_io_getc
	0x0, //	rb_io_gets
	0x0, //	rb_io_mode_flags
	0x0, //	rb_io_print
	0x0, //	rb_io_printf
	0x0, //	rb_io_puts
	0x0, //	rb_io_synchronized
	0x0, //	rb_io_taint_check
	0x0, //	rb_io_unbuffered
	0x0, //	rb_io_ungetc
	0x0, //	rb_io_wait_readable
	0x0, //	rb_io_wait_writable
	0x0, //	rb_io_write
	0x10057169, //	rb_is_class_id
	0x1005714D, //	rb_is_const_id
	0x0, //	rb_is_instance_id
	0x0, //	rb_is_junk_id
	0x0, //	rb_is_local_id
	0x0, //	rb_iter_break
	0x10029500, //	rb_iterate
	0x0, //	rb_iterator_p
	0x10082850, //	rb_iv_get
	0x10082870, //	rb_iv_set
	0x10081DA0, //	rb_ivar_defined
	0x10081CB0, //	rb_ivar_get
	0x10081CF0, //	rb_ivar_set

	0x0, //	rb_jump_tag

	0x0, //	rb_kcode

	0x0, //	rb_lastline_get
	0x0, //	rb_lastline_set
	0x0, //	rb_ll2big
	0x0, //	rb_ll2inum
	0x0, //	rb_load
	0x0, //	rb_load_fail
	0x0, //	rb_load_file
	0x0, //	rb_load_protect
	0x0, //	rb_loaderror

	0x10020920, //	rb_make_metaclass
	0x1002B290, //	rb_mark_end_proc
	0x0, //	rb_mark_generic_ivar
	0x10081B10, //	rb_mark_generic_ivar_tbl
	0x0, //	rb_mark_hash
	0x0, //	rb_mark_tbl
	0x0, //	rb_marshal_dump
	0x0, //	rb_marshal_load
	0x0, //	rb_match_busy
	0x0, //	rb_mem_clear
	0x0, //	rb_memcicmp
	0x0, //	rb_memcmp
	0x0, //	rb_memerror
	0x0, //	rb_memsearch
	0x0, //	rb_method_boundp
	0x0, //	rb_method_node
	0x0, //	rb_mod_ancestors
	0x0, //	rb_mod_class_variables
	0x0, //	rb_mod_const_at
	0x0, //	rb_mod_const_missing
	0x0, //	rb_mod_const_of
	0x0, //	rb_mod_constants
	0x0, //	rb_mod_include_p
	0x0, //	rb_mod_included_modules
	0x0, //	rb_mod_init_copy
	0x0, //	rb_mod_module_eval
	0x0, //	rb_mod_name
	0x0, //	rb_mod_remove_const
	0x10083210, //	rb_mod_remove_cvar
	0x0, //	rb_module_new

	0x100829D0, //	rb_name_class
	0x10025D60, //	rb_name_error
	0x1003F4A0, //	rb_newobj
	0x100563ED, //	rb_node_newnode
	0x0, //	rb_notimplement
	0x0, //	rb_num2dbl
	0x0, //	rb_num2fix
	0x0, //	rb_num2int
	0x0, //	rb_num2ll
	0x1004E170, //	rb_num2long
	0x0, //	rb_num2ull
	0x1004E260, //	rb_num2ulong
	0x0, //	rb_num_coerce_bin
	0x0, //	rb_num_coerce_cmp
	0x0, //	rb_num_coerce_relop
	0x0, //	rb_num_zerodiv

	0x10050AE0, //	rb_obj_alloc
	0x0, //	rb_obj_as_string
	0x1002B050, //	rb_obj_call_init
	0x1004FE90, //	rb_obj_class
	0x10082A20, //	rb_obj_classname
	0x10051CF0, //	rb_obj_clone
	0x10051D80, //	rb_obj_dup
	0x10050590, //	rb_obj_freeze
	0x1004FD70, //	rb_obj_id
	0x1004FD90, //	rb_obj_id_obsolete
	0x0, //	rb_obj_infect
	0x1004FFE0, //	rb_obj_init_copy
	0x100353F0, //	rb_obj_instance_eval
	0x10081E60, //	rb_obj_instance_variables
	0x100503A0, //	rb_obj_is_instance_of
	0x10050400, //	rb_obj_is_kind_of
	0x10081F10, //	rb_obj_remove_instance_variable
	0x10021990, //	rb_obj_singleton_methods
	0x100504F0, //	rb_obj_taint
	0x100504C0, //	rb_obj_tainted
	0x1004FE10, //	rb_obj_type
	0x10050550, //	rb_obj_untaint

	0x0, //	rb_p
	0x0, //	rb_parser_append_print
	0x0, //	rb_parser_while_loop
	0x0, //	rb_path2class
	0x0, //	rb_path_check
	0x0, //	rb_path_end
	0x0, //	rb_path_last_separator
	0x0, //	rb_path_next
	0x0, //	rb_path_skip_prefix
	0x0, //	rb_proc_exec
	0x0, //	rb_proc_new
	0x0, //	rb_proc_times
	0x0, //	rb_protect
	0x0, //	rb_protect_inspect
	0x0, //	rb_provide
	0x0, //	rb_provided

	0x0, //	rb_quad_pack
	0x0, //	rb_quad_unpack

	0x10026090, //	rb_raise
	0x1005F1A0, //	rb_range_beg_len
	0x0, //	rb_range_new
	0x0, //	rb_read_check
	0x0, //	rb_read_pending
	0x0, //	rb_reg_adjust_startpos
	0x0, //	rb_reg_eqq
	0x0, //	rb_reg_last_match
	0x0, //	rb_reg_match
	0x0, //	rb_reg_match2
	0x0, //	rb_reg_match_last
	0x0, //	rb_reg_match_post
	0x0, //	rb_reg_match_pre
	0x0, //	rb_reg_mbclen2
	0x0, //	rb_reg_new
	0x0, //	rb_reg_nth_defined
	0x0, //	rb_reg_nth_match
	0x0, //	rb_reg_options
	0x0, //	rb_reg_quote
	0x0, //	rb_reg_regcomp
	0x0, //	rb_reg_regsub
	0x0, //	rb_reg_search
	0x0, //	rb_remove_method
	0x0, //	rb_require
	0x0, //	rb_require_safe
	0x0, //	rb_rescue
	0x0, //	rb_rescue2
	0x0, //	rb_reserved_word
	0x10028CA0, //	rb_respond_to

	0x10021620, //	rb_scan_args
	0x10027030, //	rb_secure
	0x0, //	rb_secure_update
	0x0, //	rb_set_class_path
	0x0, //	rb_set_end_proc
	0x0, //	rb_set_kcode
	0x0, //	rb_set_safe_level
	0x0, //	rb_singleton_class
	0x0, //	rb_singleton_class_attached
	0x0, //	rb_singleton_class_clone
	0x0, //	rb_source_filename
	0x0, //	rb_str2cstr
	0x0, //	rb_str2inum
	0x0, //	rb_str_append
	0x0, //	rb_str_associate
	0x0, //	rb_str_associated
	0x0, //	rb_str_buf_append
	0x10077BE0, //	rb_str_buf_cat
	0x0, //	rb_str_buf_cat2
	0x10077470, //	rb_str_buf_new
	0x1007AC70, //	rb_str_buf_new2
	0x10077CD0, //	rb_str_cat
	0x10077D70, //	rb_str_cat2
	0x10078000, //	rb_str_cmp
	0x10077F60, //	rb_str_concat
	0x10079450, //	rb_str_dump
	0x1007ADD0, //	rb_str_dup
	0x0, //	rb_str_dup_frozen
	0x0, //	rb_str_freeze
	0x0, //	rb_str_hash
	0x1007B790, //	rb_str_inspect
	0x1007AAD0, //	rb_str_intern
	0x0, //	rb_str_modify
	0x10077180, //	rb_str_new
	0x100771A0, //	rb_str_new2
	0x100772F0, //	rb_str_new3
	0x0, //	rb_str_new4
	0x0, //	rb_str_new5
	0x0, //	rb_str_plus
	0x0, //	rb_str_resize
	0x0, //	rb_str_setter
	0x0, //	rb_str_split
	0x0, //	rb_str_substr
	0x0, //	rb_str_times
	0x10051A60, //	rb_str_to_dbl
	0x0, //	rb_str_to_inum
	0x0, //	rb_str_to_str
	0x0, //	rb_str_update
	0x0, //	rb_str_upto
	0x0, //	rb_string_value
	0x0, //	rb_string_value_cstr
	0x10077980, //	rb_string_value_ptr
	0x0, //	rb_struct_alloc
	0x0, //	rb_struct_aref
	0x0, //	rb_struct_aset
	0x1007D720, //	rb_struct_define
	0x0, //	rb_struct_getmember
	0x1007C9F0, //	rb_struct_iv_get
	0x0, //	rb_struct_new
	0x0, //	rb_svar
	0x0, //	rb_sym_all_symbols
	0x0, //	rb_sys_fail
	0x0, //	rb_sys_warning
	0x0, //	rb_syswait

	0x0, //	rb_tainted_str_new
	0x0, //	rb_tainted_str_new2

	0x0, //	rb_thread_alone
	0x0, //	rb_thread_atfork
	0x0, //	rb_thread_create
	0x0, //	rb_thread_current
	0x0, //	rb_thread_fd_close
	0x0, //	rb_thread_fd_writable
	0x0, //	rb_thread_group
	0x0, //	rb_thread_interrupt
	0x0, //	rb_thread_kill
	0x0, //	rb_thread_list
	0x0, //	rb_thread_local_aref
	0x0, //	rb_thread_local_aset
	0x0, //	rb_thread_main
	0x0, //	rb_thread_polling
	0x0, //	rb_thread_run
	0x0, //	rb_thread_schedule
	0x0, //	rb_thread_select
	0x0, //	rb_thread_signal_raise
	0x0, //	rb_thread_sleep
	0x0, //	rb_thread_sleep_forever
	0x0, //	rb_thread_stop
	0x0, //	rb_thread_trap_eval
	0x0, //	rb_thread_wait_fd
	0x0, //	rb_thread_wait_for
	0x0, //	rb_thread_wakeup
	0x0, //	rb_throw
	0x0, //	rb_time_interval
	0x0, //	rb_time_new
	0x0, //	rb_time_timeval
	0x10050C50, //	rb_to_id
	0x0, //	rb_to_int
	0x0, //	rb_trap_exec
	0x0, //	rb_trap_exit
	0x0, //	rb_trap_restore_mask

	0x1001DBD0, //	rb_uint2big
	0x0, //	rb_uint2inum
	0x0, //	rb_ull2big
	0x0, //	rb_ull2inum
	0x0, //	rb_undef
	0x100274B0, //	rb_undef_alloc_func
	0x100213B0, //	rb_undef_method

	0x0, //	rb_values_at

	0x0, //	rb_w32_accept
	0x0, //	rb_w32_asynchronize
	0x0, //	rb_w32_bind
	0x0, //	rb_w32_close
	0x0, //	rb_w32_closedir
	0x0, //	rb_w32_connect
	0x0, //	rb_w32_enter_critical
	0x0, //	rb_w32_fclose
	0x0, //	rb_w32_fdclr
	0x0, //	rb_w32_fdisset
	0x0, //	rb_w32_fdset
	0x0, //	rb_w32_free_environ
	0x0, //	rb_w32_get_environ
	0x0, //	rb_w32_get_osfhandle
	0x0, //	rb_w32_getc
	0x0, //	rb_w32_getcwd
	0x0, //	rb_w32_getenv
	0x0, //	rb_w32_gethostbyaddr
	0x0, //	rb_w32_gethostbyname
	0x0, //	rb_w32_gethostname
	0x0, //	rb_w32_getpeername
	0x0, //	rb_w32_getpid
	0x0, //	rb_w32_getprotobyname
	0x0, //	rb_w32_getprotobynumber
	0x0, //	rb_w32_getservbyname
	0x0, //	rb_w32_getservbyport
	0x0, //	rb_w32_getsockname
	0x0, //	rb_w32_getsockopt
	0x0, //	rb_w32_ioctlsocket
	0x0, //	rb_w32_leave_critical
	0x0, //	rb_w32_listen
	0x0, //	rb_w32_main_context
	0x0, //	rb_w32_opendir
	0x0, //	rb_w32_putc
	0x0, //	rb_w32_readdir
	0x0, //	rb_w32_recv
	0x0, //	rb_w32_recvfrom
	0x0, //	rb_w32_rename
	0x0, //	rb_w32_rewinddir
	0x0, //	rb_w32_seekdir
	0x0, //	rb_w32_select
	0x0, //	rb_w32_send
	0x0, //	rb_w32_sendto
	0x0, //	rb_w32_setsockopt
	0x0, //	rb_w32_shutdown
	0x0, //	rb_w32_sleep
	0x0, //	rb_w32_snprintf
	0x0, //	rb_w32_socket
	0x0, //	rb_w32_stat
	0x0, //	rb_w32_strerror
	0x0, //	rb_w32_telldir
	0x0, //	rb_w32_times
	0x0, //	rb_w32_utime
	0x0, //	rb_w32_vsnprintf

	0x0, //	rb_waitpid
	0x100257A0, //	rb_warn
	0x0, //	rb_warning
	0x0, //	rb_with_disable_interrupt
	0x0, //	rb_write_error
	0x0, //	rb_write_error2
	0x100351D0, //	rb_yield
	0x0, //	rb_yield_splat
	0x0, //	rb_yield_values

	0x0, //	re_set_syntax

	0x1003F2D0, //	ruby_xmalloc

	0x10077010, //	st_add_direct
	0x0, //	st_cleanup_safe
	0x0, //	st_copy
	0x0, //	st_delete
	0x0, //	st_delete_safe
	0x10076E50, //	st_foreach
	0x0, //	st_free_table
	0x100769E0, //	st_init_numtable
	0x100769F0, //	st_init_numtable_with_size
	0x10076A10, //	st_init_strtable
	0x10076A20, //	st_init_strtable_with_size
	0x0, //	st_init_table
	0x0, //	st_init_table_with_size
	0x10076F20, //	st_insert
	0x10076A90, //	st_lookup

	//	未导出的函数
	0x10037860, //	rb_call
};

void FixedExportVarAddr()
{
	u32 uOriAddr = 0x10003b80;
	u32 uNowAddr = PtrToUlong(ShanaRGSSEval);

	if (uOriAddr > uNowAddr)
	{
		u32	uOffset = (uOriAddr - uNowAddr);

		#define FIXED_VAR(addr)	addr = (VALUE*)UlongToPtr(PtrToUlong(addr) - uOffset)

		FIXED_VAR(ptr_rb_cArray);
		FIXED_VAR(ptr_rb_cBignum);
		FIXED_VAR(ptr_rb_cClass);
		FIXED_VAR(ptr_rb_cData);
		FIXED_VAR(ptr_rb_cDir);
		FIXED_VAR(ptr_rb_cFalseClass);
		FIXED_VAR(ptr_rb_cFile);
		FIXED_VAR(ptr_rb_cFixnum);
		FIXED_VAR(ptr_rb_cFloat);
		FIXED_VAR(ptr_rb_cHash);
		FIXED_VAR(ptr_rb_cIO);
		FIXED_VAR(ptr_rb_cInteger);
		FIXED_VAR(ptr_rb_cModule);
		FIXED_VAR(ptr_rb_cNilClass);
		FIXED_VAR(ptr_rb_cNumeric);
		FIXED_VAR(ptr_rb_cObject);
		FIXED_VAR(ptr_rb_cProc);
		FIXED_VAR(ptr_rb_cRange);
		FIXED_VAR(ptr_rb_cRegexp);
		FIXED_VAR(ptr_rb_cString);
		FIXED_VAR(ptr_rb_cStruct);
		FIXED_VAR(ptr_rb_cSymbol);
		FIXED_VAR(ptr_rb_cThread);
		FIXED_VAR(ptr_rb_cTime);
		FIXED_VAR(ptr_rb_cTrueClass);

		FIXED_VAR(ptr_rb_eArgError);
		FIXED_VAR(ptr_rb_eEOFError);
		FIXED_VAR(ptr_rb_eException);
		FIXED_VAR(ptr_rb_eFatal);
		FIXED_VAR(ptr_rb_eFloatDomainError);
		FIXED_VAR(ptr_rb_eIOError);
		FIXED_VAR(ptr_rb_eIndexError);
		FIXED_VAR(ptr_rb_eInterrupt);
		FIXED_VAR(ptr_rb_eLoadError);
		FIXED_VAR(ptr_rb_eNameError);
		FIXED_VAR(ptr_rb_eNoMemError);
		FIXED_VAR(ptr_rb_eNoMethodError);
		FIXED_VAR(ptr_rb_eNotImpError);
		FIXED_VAR(ptr_rb_eRangeError);
		FIXED_VAR(ptr_rb_eRuntimeError);
		FIXED_VAR(ptr_rb_eScriptError);
		FIXED_VAR(ptr_rb_eSecurityError);
		FIXED_VAR(ptr_rb_eSignal);
		FIXED_VAR(ptr_rb_eStandardError);
		FIXED_VAR(ptr_rb_eSyntaxError);
		FIXED_VAR(ptr_rb_eSystemCallError);
		FIXED_VAR(ptr_rb_eSystemExit);
		FIXED_VAR(ptr_rb_eTypeError);
		FIXED_VAR(ptr_rb_eZeroDivError);

		FIXED_VAR(ptr_rb_mComparable);
		FIXED_VAR(ptr_rb_mEnumerable);
		FIXED_VAR(ptr_rb_mErrno);
		FIXED_VAR(ptr_rb_mFileTest);
		FIXED_VAR(ptr_rb_mGC);
		FIXED_VAR(ptr_rb_mKernel);
		FIXED_VAR(ptr_rb_mMath);
		FIXED_VAR(ptr_rb_mPrecision);
		FIXED_VAR(ptr_rb_mProcGID);
		FIXED_VAR(ptr_rb_mProcID_Syscall);
		FIXED_VAR(ptr_rb_mProcUID);
		FIXED_VAR(ptr_rb_mProcess);

		ptr_ruby_safe_level = (int*)UlongToPtr(PtrToUlong(ptr_ruby_safe_level) - uOffset);

		#undef FIXED_VAR
	}
	else
	{
		u32 uOffset = (uNowAddr - uOriAddr);

		#define FIXED_VAR(addr)	addr = (VALUE*)UlongToPtr(PtrToUlong(addr) + uOffset)

		FIXED_VAR(ptr_rb_cArray);
		FIXED_VAR(ptr_rb_cBignum);
		FIXED_VAR(ptr_rb_cClass);
		FIXED_VAR(ptr_rb_cData);
		FIXED_VAR(ptr_rb_cDir);
		FIXED_VAR(ptr_rb_cFalseClass);
		FIXED_VAR(ptr_rb_cFile);
		FIXED_VAR(ptr_rb_cFixnum);
		FIXED_VAR(ptr_rb_cFloat);
		FIXED_VAR(ptr_rb_cHash);
		FIXED_VAR(ptr_rb_cIO);
		FIXED_VAR(ptr_rb_cInteger);
		FIXED_VAR(ptr_rb_cModule);
		FIXED_VAR(ptr_rb_cNilClass);
		FIXED_VAR(ptr_rb_cNumeric);
		FIXED_VAR(ptr_rb_cObject);
		FIXED_VAR(ptr_rb_cProc);
		FIXED_VAR(ptr_rb_cRange);
		FIXED_VAR(ptr_rb_cRegexp);
		FIXED_VAR(ptr_rb_cString);
		FIXED_VAR(ptr_rb_cStruct);
		FIXED_VAR(ptr_rb_cSymbol);
		FIXED_VAR(ptr_rb_cThread);
		FIXED_VAR(ptr_rb_cTime);
		FIXED_VAR(ptr_rb_cTrueClass);

		FIXED_VAR(ptr_rb_eArgError);
		FIXED_VAR(ptr_rb_eEOFError);
		FIXED_VAR(ptr_rb_eException);
		FIXED_VAR(ptr_rb_eFatal);
		FIXED_VAR(ptr_rb_eFloatDomainError);
		FIXED_VAR(ptr_rb_eIOError);
		FIXED_VAR(ptr_rb_eIndexError);
		FIXED_VAR(ptr_rb_eInterrupt);
		FIXED_VAR(ptr_rb_eLoadError);
		FIXED_VAR(ptr_rb_eNameError);
		FIXED_VAR(ptr_rb_eNoMemError);
		FIXED_VAR(ptr_rb_eNoMethodError);
		FIXED_VAR(ptr_rb_eNotImpError);
		FIXED_VAR(ptr_rb_eRangeError);
		FIXED_VAR(ptr_rb_eRuntimeError);
		FIXED_VAR(ptr_rb_eScriptError);
		FIXED_VAR(ptr_rb_eSecurityError);
		FIXED_VAR(ptr_rb_eSignal);
		FIXED_VAR(ptr_rb_eStandardError);
		FIXED_VAR(ptr_rb_eSyntaxError);
		FIXED_VAR(ptr_rb_eSystemCallError);
		FIXED_VAR(ptr_rb_eSystemExit);
		FIXED_VAR(ptr_rb_eTypeError);
		FIXED_VAR(ptr_rb_eZeroDivError);

		FIXED_VAR(ptr_rb_mComparable);
		FIXED_VAR(ptr_rb_mEnumerable);
		FIXED_VAR(ptr_rb_mErrno);
		FIXED_VAR(ptr_rb_mFileTest);
		FIXED_VAR(ptr_rb_mGC);
		FIXED_VAR(ptr_rb_mKernel);
		FIXED_VAR(ptr_rb_mMath);
		FIXED_VAR(ptr_rb_mPrecision);
		FIXED_VAR(ptr_rb_mProcGID);
		FIXED_VAR(ptr_rb_mProcID_Syscall);
		FIXED_VAR(ptr_rb_mProcUID);
		FIXED_VAR(ptr_rb_mProcess);

		ptr_ruby_safe_level = (int*)UlongToPtr(PtrToUlong(ptr_ruby_safe_level) + uOffset);

		#undef FIXED_VAR
	}
}

void FixedMappingTable()
{
	u32 uOriAddr = 0x10003b80;
	u32 uNowAddr = PtrToUlong(ShanaRGSSEval);

	u32 idx;
	if (uOriAddr > uNowAddr)
	{
		//for (u32 idx = 0; idx < SymbolIdList_MAX_NUMS; ++idx)
		for (idx = 0; idx < SymbolIdList_MAX_NUMS; ++idx)
		{
			sMappingTable[idx] -= (uOriAddr - uNowAddr);
		}		
	}
	else
	{
		for (idx = 0; idx < SymbolIdList_MAX_NUMS; ++idx)
		{
			sMappingTable[idx] += (uNowAddr - uOriAddr);
		}
	}
}

#define noreturn_implement(method_name, ...)	\
	(void)((RubyFunc)UlongToPtr(sMappingTable[SI_##method_name]))(__VA_ARGS__);

#define return_implement(return_type, method_name, ...)	\
	VALUE ret = ((RubyFunc)UlongToPtr(sMappingTable[SI_##method_name]))(__VA_ARGS__);	\
	return *(return_type*)&ret;


VALUE	rb_Array(VALUE);
VALUE	rb_Float(VALUE val)
{
	return_implement(VALUE, rb_Float, val);
}
VALUE	rb_Integer(VALUE);
VALUE	rb_String(VALUE);

void	rb_add_method(VALUE klass, ID mid, struct RNode* node, int noex);
void	rb_alias(VALUE klass, ID name, ID def);
void	rb_alias_variable(ID name1, ID name2);
VALUE	rb_any_to_s(VALUE obj);
VALUE	rb_apply(VALUE recv, ID mid, VALUE args)
{
    int argc;
    VALUE *argv;

    argc = RARRAY(args)->len; /* Assigns LONG, but argc is INT */
    argv = ALLOCA_N(VALUE, argc);
    MEMCPY(argv, RARRAY(args)->ptr, VALUE, argc);
    return rb_call(CLASS_OF(recv), recv, mid, argc, argv, 1);
}
VALUE	rb_ary_aref(int argc, VALUE* argv, VALUE ary)
{
	return_implement(VALUE, rb_ary_aref, argc, argv, ary);
}
VALUE	rb_ary_assoc(VALUE, VALUE);
VALUE	rb_ary_clear(VALUE);
VALUE	rb_ary_cmp(VALUE, VALUE);
VALUE	rb_ary_concat(VALUE x, VALUE y)
{
	return_implement(VALUE, rb_ary_concat, x, y);
}
VALUE	rb_ary_delete(VALUE, VALUE);
VALUE	rb_ary_delete_at(VALUE, long);
VALUE	rb_ary_dup(VALUE);
VALUE	rb_ary_each(VALUE ary)
{
	return_implement(VALUE, rb_ary_each, ary);
}
VALUE	rb_ary_entry(VALUE ary, long offset)
{
	return_implement(VALUE, rb_ary_entry, ary, offset);
}
VALUE	rb_ary_freeze(VALUE);
VALUE	rb_ary_includes(VALUE, VALUE);
VALUE	rb_ary_join(VALUE, VALUE);
VALUE	rb_ary_new(void)
{
	return_implement(VALUE, rb_ary_new);
}
VALUE	rb_ary_new2(long len)
{
	return_implement(VALUE, rb_ary_new2, len);
}
//VALUE	rb_ary_new3(long, ANYARGS);
VALUE	rb_ary_new3(long n, ...)
{
    va_list	ar;
    VALUE	ary;
    long	i;

    ary = rb_ary_new2(n);

    va_start(ar, n);
    for (i = 0; i < n; ++i)
	{
		RARRAY(ary)->ptr[i] = va_arg(ar, VALUE);
    }
    va_end(ar);

    RARRAY(ary)->len = n;

    return ary;
}
VALUE	rb_ary_new4(long n, const VALUE * elts)
{
	return_implement(VALUE, rb_ary_new4, n, elts);
}
//VALUE	rb_ary_plus(VALUE, VALUE);
VALUE	rb_ary_pop(VALUE ary)
{
	return_implement(VALUE, rb_ary_pop, ary);
}
VALUE	rb_ary_push(VALUE ary, VALUE item)
{
	return_implement(VALUE, rb_ary_push, ary, item);
}
//VALUE	rb_ary_rassoc(VALUE, VALUE);
//VALUE	rb_ary_reverse(VALUE);
VALUE	rb_ary_shift(VALUE ary)
{
	return_implement(VALUE, rb_ary_shift, ary);
}
//VALUE	rb_ary_sort(VALUE);
VALUE	rb_ary_sort_bang(VALUE ary)
{
	return_implement(VALUE, rb_ary_sort_bang, ary);
}
void	rb_ary_store(VALUE ary, long idx, VALUE val)
{
	noreturn_implement(rb_ary_store, ary, idx, val);
}
//VALUE	rb_ary_to_ary(VALUE);
//VALUE	rb_ary_to_s(VALUE);
//VALUE	rb_ary_unshift(VALUE, VALUE);
//VALUE	rb_assoc_new(VALUE, VALUE);
//void	rb_attr(VALUE klass, ID id, int read, int write, int ex);
//VALUE	rb_attr_get(VALUE obj, ID id);
void	rb_autoload(VALUE mod, ID id, const char* file)
{
	noreturn_implement(rb_autoload, mod, id, file);
}
//void	rb_autoload_load(VALUE, ID);
//VALUE	rb_autoload_p(VALUE, ID);
//
//VALUE	rb_backref_get();
//void	rb_backref_set(VALUE);
//void	rb_backtrace();
double	rb_big2dbl(VALUE x)
{
	return_implement(double, rb_big2dbl, x);
}
//s64		rb_big2ll(VALUE);
//long	rb_big2long(VALUE);
//VALUE	rb_big2str(VALUE, int);
//u64		rb_big2ull(VALUE);
//u32		rb_big2ulong(VALUE);
//void	rb_big_2comp(VALUE);
//VALUE	rb_big_and(VALUE, VALUE);
//VALUE	rb_big_clone(VALUE);
//VALUE	rb_big_divmod(VALUE, VALUE);
//VALUE	rb_big_lshift(VALUE, VALUE);
//VALUE	rb_big_minus(VALUE, VALUE);
//VALUE	rb_big_mul(VALUE, VALUE);
//VALUE	rb_big_norm(VALUE);
//VALUE	rb_big_or(VALUE, VALUE);
//VALUE	rb_big_plus(VALUE, VALUE);
//VALUE	rb_big_pow(VALUE, VALUE);
//VALUE	rb_big_rand(VALUE, double*);
//VALUE	rb_big_xor(VALUE, VALUE);
int		rb_block_given_p()
{
	return_implement(int, rb_block_given_p);
}
VALUE	rb_block_proc(void)
{
	return_implement(VALUE, rb_block_proc);
}
//void	rb_bug(const char*, ...)
//{
//	//....<not implement>
//}
//
//void	rb_call_inits(void);
VALUE	rb_call_super(int argc, const VALUE* argv)
{
	return_implement(VALUE, rb_call_super, argc, argv);
}
//VALUE	rb_catch(const char*, VALUE(*)(ANYARGS), VALUE);
//VALUE	rb_check_array_type(VALUE);
//VALUE	rb_check_convert_type(VALUE, int, const char*, const char*);
//void	rb_check_frozen(VALUE);
//void	rb_check_inheritable(VALUE);
//void	rb_check_safe_obj(VALUE x);
void	rb_check_safe_str(VALUE x)
{
	noreturn_implement(rb_check_safe_str, x);
}
//VALUE	rb_check_string_type(VALUE);
void	rb_check_type(VALUE x, int t)
{
	noreturn_implement(rb_check_type, x, t);
}
//char*	rb_class2name(VALUE klass);
VALUE	rb_class_boot(VALUE obj)
{
	return_implement(VALUE, rb_class_boot, obj);
}
VALUE	rb_class_inherited(VALUE, VALUE);
VALUE	rb_class_init_copy(VALUE, VALUE);
VALUE	rb_class_instance_methods(int, VALUE*, VALUE);
VALUE	rb_class_new(VALUE);
VALUE	rb_class_new_instance(int argc, VALUE* argv, VALUE obj)
{
	return_implement(VALUE, rb_class_new_instance, argc, argv, obj);
}
VALUE	rb_class_path(VALUE);
VALUE	rb_class_private_instance_methods(int, VALUE*, VALUE);
VALUE	rb_class_protected_instance_methods(int, VALUE*, VALUE);
VALUE	rb_class_public_instance_methods(int, VALUE*, VALUE);
VALUE	rb_class_real(VALUE v)
{
	return_implement(VALUE, rb_class_real, v);
}
//void	rb_clear_cache(void);
//void	rb_clear_cache_by_class(VALUE);
//void	rb_cmperr(VALUE, VALUE);
//int		rb_cmpint(VALUE, VALUE, VALUE);
//struct RNode*	rb_compile_cstr(const char* f, const char* s, int len, int line);
//void	rb_compile_error(const char*, ANYARGS);
//void	rb_compile_error_append(const char*, ANYARGS);
//struct RNode*	rb_compile_file(const char* f, VALUE file, int start);
//struct RNode*	rb_compile_string(const char* f, VALUE s, int line);
int		rb_const_defined(VALUE obj, ID id)
{
	return_implement(int, rb_const_defined, obj, id);
}
int		rb_const_defined_at(VALUE, ID);
int		rb_const_defined_from(VALUE arg1, ID arg2);
VALUE	rb_const_get(VALUE arg1, ID arg2)
{
	return_implement(VALUE, rb_const_get, arg1, arg2);
}
VALUE	rb_const_get_at(VALUE, ID);
VALUE	rb_const_get_from(VALUE, ID);
VALUE	rb_const_list(void*);
void	rb_const_set(VALUE obj, ID id, VALUE v)
{
	noreturn_implement(rb_const_set, obj, id, v);
}
VALUE	rb_convert_type(VALUE,int,const char*,const char*);
void	rb_copy_generic_ivar(VALUE, VALUE);
VALUE	rb_cstr2inum(const char*, int);
double	rb_cstr_to_dbl(const char* arg1, int arg2);
VALUE	rb_cstr_to_inum(const char*, int, int);
VALUE	rb_cv_get(VALUE klass, const char* name)
{
	return_implement(VALUE, rb_cv_get, klass, name);
}
void	rb_cv_set(VALUE klass, const char* name, VALUE val)
{
	noreturn_implement(rb_cv_set, klass, name, val);
}
VALUE	rb_cvar_defined(VALUE, ID);
VALUE	rb_cvar_get(VALUE klass, ID id)
{
	return_implement(VALUE, rb_cvar_get, klass, id);
}
void	rb_cvar_set(VALUE klass, ID id, VALUE val, int warn)
{
	noreturn_implement(rb_cvar_set, klass, id, val, warn);
}

VALUE	rb_data_object_alloc(VALUE klass, void* datap, RubyDataFunc dmark, RubyDataFunc dfree)
{
	return_implement(VALUE, rb_data_object_alloc, klass, datap, dmark, dfree);
}
VALUE	rb_dbl2big(double);
VALUE	rb_dbl_cmp(double, double);
void	rb_define_alias(VALUE obj, const char* newname, const char* oldname)
{
	noreturn_implement(rb_define_alias, obj, newname, oldname);
}
void	rb_define_alloc_func(VALUE obj, VALUE (*func)(VALUE))
{
	noreturn_implement(rb_define_alloc_func, obj, func);
}
void	rb_define_attr(VALUE, const char*, int, int);
VALUE	rb_define_class(const char* name, VALUE super)
{
	return_implement(VALUE, rb_define_class, name, super);
}
VALUE	rb_define_class_id(ID, VALUE);
VALUE	rb_define_class_under(VALUE outer, const char* name, VALUE super)
{
	return_implement(VALUE, rb_define_class_under, outer, name, super);
}
void	rb_define_class_variable(VALUE, const char*, VALUE);
void	rb_define_const(VALUE obj, const char* name, VALUE v)
{
	noreturn_implement(rb_define_const, obj, name, v);
}
void	rb_define_global_const(const char* name, VALUE v)
{
	noreturn_implement(rb_define_global_const, name, v);
}
void	rb_define_global_function(const char* name, VALUE(*func)(ANYARGS), int argc)
{
	noreturn_implement(rb_define_global_function, name, func, argc);
}
void	rb_define_hooked_variable(const char* name, VALUE* vp, VALUE(*func1)(ANYARGS), void(*func2)(ANYARGS))
{
	noreturn_implement(rb_define_hooked_variable, name, vp, func1, func2);
}
void	rb_define_method(VALUE klass, const char* name, VALUE(*func)(ANYARGS), int argc)
{
	noreturn_implement(rb_define_method, klass, name, func, argc);
}
void	rb_define_method_id(VALUE, ID, VALUE (*)(ANYARGS), int);
VALUE	rb_define_module(const char* name)
{
	return_implement(VALUE, rb_define_module, name);
}
void	rb_define_module_function(VALUE obj, const char* name, VALUE(*func)(ANYARGS), int argc)
{
	noreturn_implement(rb_define_module_function, obj, name, func, argc);
}
VALUE	rb_define_module_id(ID);
VALUE	rb_define_module_under(VALUE outer, const char* name)
{
	return_implement(VALUE, rb_define_module_under, outer, name);
}
void	rb_define_private_method(VALUE obj, const char* name, VALUE (*func)(ANYARGS), int argc)
{
	noreturn_implement(rb_define_private_method, obj, name, func, argc);
}
void	rb_define_protected_method(VALUE, const char*, VALUE (*)(ANYARGS), int);
void	rb_define_readonly_variable(const char* name, VALUE* vp)
{
	noreturn_implement(rb_define_readonly_variable, name, vp);
}
void	rb_define_singleton_method(VALUE obj, const char* name, VALUE(*func)(ANYARGS), int argc)
{
	noreturn_implement(rb_define_singleton_method, obj, name, func, argc);
}
void	rb_define_variable(const char* name,VALUE* vp)
{
	noreturn_implement(rb_define_variable, name, vp);
}
void	rb_define_virtual_variable(const char* name, VALUE(*get)(ANYARGS), void(*set)(ANYARGS))
{
	noreturn_implement(rb_define_virtual_variable, name, get, set);
}
VALUE	rb_detach_process(int);
//void	rb_disable_super(VALUE klass, const char* name);
//VALUE	rb_dvar_curr(ID);
//VALUE	rb_dvar_defined(ID);
//void	rb_dvar_push(ID, VALUE);
//VALUE	rb_dvar_ref(ID);
//
VALUE	rb_each(VALUE obj)
{
	return_implement(VALUE, rb_each, obj);
}
//void	rb_enable_super(VALUE klass, const char* name);
VALUE	rb_ensure(VALUE(* b_proc)(ANYARGS), VALUE data1, VALUE(*e_proc)(ANYARGS), VALUE data2)
{
	return_implement(VALUE, rb_ensure, b_proc, data1, e_proc, data2);
}
//int		rb_env_path_tainted(void);
//void	rb_eof_error();
//int		rb_eql(VALUE, VALUE);
//VALUE	rb_equal(VALUE,VALUE);
//void	rb_error_frozen(char* what);
//VALUE	rb_eval_cmd(VALUE, VALUE, int);
VALUE	rb_eval_string(const char* str)
{
	return_implement(VALUE, rb_eval_string, str);
}
VALUE	rb_eval_string_protect(const char*, int*);
VALUE	rb_eval_string_wrap(const char*, int*);
void	rb_exc_fatal(VALUE);
VALUE	rb_exc_new(VALUE, const char*, long);
VALUE	rb_exc_new2(VALUE obj, const char* str)
{
	return_implement(VALUE, rb_exc_new2, obj, str);
}
VALUE	rb_exc_new3(VALUE, VALUE);
void	rb_exc_raise(VALUE mesg);
void	rb_exec_end_proc(void);
void	rb_exit(int);
void	rb_extend_object(VALUE obj, VALUE mod)
{
	noreturn_implement(rb_extend_object, obj, mod);
}

//VALUE	rb_f_abort(int, VALUE*);
//VALUE	rb_f_exec(int, VALUE*);
//VALUE	rb_f_exit(int, VALUE*);
//VALUE	rb_f_global_variables(void);
//VALUE	rb_f_kill(int, VALUE*);
//VALUE	rb_f_lambda(void);
//VALUE	rb_f_require(VALUE, VALUE);
//VALUE	rb_f_sprintf(int, VALUE*);
VALUE	rb_f_trace_var(int argc, VALUE* argv)
{
	return_implement(VALUE, rb_f_trace_var, argc, argv);
}
VALUE	rb_f_untrace_var(int argc, VALUE* argv)
{
	return_implement(VALUE, rb_f_untrace_var, argc, argv);
}
//void	rb_fatal(const char*, ANYARGS);
//FILE*	rb_fdopen(int fd, const char* mode);
void	rb_file_const(const char* name, VALUE v)
{
	noreturn_implement(rb_file_const, name, v);
}
VALUE	rb_file_expand_path(VALUE fname, VALUE dname);
VALUE	rb_file_open(const char*, const char*);
VALUE	rb_file_s_expand_path(int, VALUE *);
VALUE	rb_file_sysopen(const char* fname, int flags, int mode);
VALUE	rb_find_file(VALUE);
int		rb_find_file_ext(VALUE*, const char* const*);
long	rb_fix2int(VALUE);
VALUE	rb_fix2str(VALUE x, int base)
{
	return_implement(VALUE, rb_fix2str, x, base);
}
VALUE	rb_float_new(double d)
{
	return_implement(VALUE, rb_float_new, d);
}
FILE*	rb_fopen(const char* fname, const char* mode)
{
	return_implement(FILE*, rb_fopen, fname, mode);
}
ID		rb_frame_last_func();
void	rb_free_generic_ivar(VALUE);
void	rb_frozen_class_p(VALUE);

VALUE	rb_funcall(VALUE recv, ID mid, int n, ...)
{
    va_list	ar;
    VALUE*	argv;

	if (n > 0)
	{
		long i;

		argv = ALLOCA_N(VALUE, n);

		va_start(ar, n);

		for (i=0; i < n; ++i)
		{
			argv[i] = va_arg(ar, VALUE);
		}
		va_end(ar);
	}
	else
	{
		argv = 0;
	}
	return rb_call(CLASS_OF(recv), recv, mid, n, argv, 1);
}
VALUE	rb_funcall2(VALUE recv, ID mid, int argc, const VALUE* argv)
{
	//return_implement(VALUE, rb_funcall2, recv, mid, argc, argv);
    return rb_call(CLASS_OF(recv), recv, mid, argc, argv, 1);
}
VALUE	rb_funcall3(VALUE recv, ID mid, int argc, const VALUE* argv)
{
	return_implement(VALUE, rb_funcall3, recv, mid, argc, argv);
}

void	rb_gc(void);
void	rb_gc_call_finalizer_at_exit(void);
void	rb_gc_copy_finalizer(VALUE,VALUE);
VALUE	rb_gc_disable(void);
VALUE	rb_gc_enable(void);
void	rb_gc_force_recycle(VALUE);
void	rb_gc_mark(VALUE obj)
{
	noreturn_implement(rb_gc_mark, obj);
}
void	rb_gc_mark_frame(struct FRAME * frame);
void	rb_gc_mark_global_tbl(void)
{
	noreturn_implement(rb_gc_mark_global_tbl);
}
void	rb_gc_mark_locations(VALUE*, VALUE*);
void	rb_gc_mark_maybe(VALUE obj)
{
	noreturn_implement(rb_gc_mark_maybe, obj);
}
void	rb_gc_mark_parser(void)
{
	noreturn_implement(rb_gc_mark_parser);
}
void	rb_gc_mark_threads(void)
{
	noreturn_implement(rb_gc_mark_threads);
}
void	rb_gc_mark_trap_list(void)
{
	noreturn_implement(rb_gc_mark_trap_list);
}
void	rb_gc_register_address(VALUE* vp)
{
	noreturn_implement(rb_gc_register_address, vp);
}
VALUE	rb_gc_start(void);
void	rb_gc_unregister_address(VALUE* vp)
{
	noreturn_implement(rb_gc_unregister_address, vp);
}
struct st_table*	rb_generic_ivar_table(VALUE);
const char*			rb_get_kcode(void);
int		rb_getc(FILE *f);
VALUE	rb_gets();
void	rb_glob(char*, void(*)(const char*, VALUE), VALUE);
struct global_entry*	rb_global_entry(ID id);
void	rb_global_variable(VALUE* vp)
{
	noreturn_implement(rb_global_variable, vp);
}
void	rb_globi(char*, void(*)(const char*, VALUE), VALUE);
VALUE	rb_gv_get(const char*);
VALUE	rb_gv_set(const char*, VALUE);
VALUE	rb_gvar_defined(struct global_entry *entry);
VALUE	rb_gvar_get(struct global_entry *entry);
VALUE	rb_gvar_set(struct global_entry *entry, VALUE val);

VALUE	rb_hash(VALUE);
VALUE	rb_hash_aref(VALUE hash, VALUE key)
{
	return_implement(VALUE, rb_hash_aref, hash, key);
}
VALUE	rb_hash_aset(VALUE hash, VALUE key, VALUE val)
{
	return_implement(VALUE, rb_hash_aset, hash, key, val);
}
VALUE	rb_hash_delete(VALUE hash, VALUE key)
{
	return_implement(VALUE, rb_hash_delete, hash, key);
}
VALUE	rb_hash_delete_if(VALUE hash)
{
	return_implement(VALUE, rb_hash_delete_if, hash);
}
VALUE	rb_hash_freeze(VALUE);
VALUE	rb_hash_new(void)
{
	return_implement(VALUE, rb_hash_new);
}
VALUE	rb_hash_reject_bang(VALUE hash);
VALUE	rb_hash_select(int argc, VALUE* argv, VALUE hash);
VALUE	rb_hash_values_at(int argc, VALUE* argv, VALUE hash);

char*	rb_id2name(ID id)
{
	return_implement(char*, rb_id2name, id);
}
ID		rb_id_attrset(ID);
void	rb_include_module(VALUE obj, VALUE mod)
{
	noreturn_implement(rb_include_module, obj, mod);
}
VALUE	rb_inspect(VALUE);
VALUE	rb_inspecting_p(VALUE);
VALUE	rb_int2big(long);
VALUE	rb_int2inum(long n)
{
	return_implement(VALUE, rb_int2inum, n);
}
ID		rb_intern(const char* name)
{
	return_implement(ID, rb_intern, name);
}
void	rb_interrupt(void);
void	rb_invalid_str(const char*, const char*);
VALUE	rb_io_addstr(VALUE, VALUE);
VALUE	rb_io_binmode(VALUE);
void	rb_io_check_closed(struct OpenFile *fptr);
void	rb_io_check_readable(struct OpenFile *fptr);
void	rb_io_check_writable(struct OpenFile *fptr);
VALUE	rb_io_close(VALUE);
VALUE	rb_io_eof(VALUE);
char*	rb_io_flags_mode(int flags, char* mode);
void	rb_io_fptr_finalize(struct OpenFile *fptr);
long	rb_io_fread(char* ptr, long len, FILE* f);
long	rb_io_fwrite(const char* ptr, long len, FILE* f);
VALUE	rb_io_getc(VALUE);
VALUE	rb_io_gets(VALUE);
int		rb_io_mode_flags(const char* mode);
VALUE	rb_io_print(int, VALUE*, VALUE);
VALUE	rb_io_printf(int, VALUE*, VALUE);
VALUE	rb_io_puts(int, VALUE*, VALUE);
void	rb_io_synchronized(struct OpenFile *fptr);
VALUE	rb_io_taint_check(VALUE io);
void	rb_io_unbuffered(struct OpenFile *fptr);
VALUE	rb_io_ungetc(VALUE io, VALUE c);
int		rb_io_wait_readable(int f);
int		rb_io_wait_writable(int f);
VALUE	rb_io_write(VALUE, VALUE);
int		rb_is_class_id(ID id)
{
	return_implement(int, rb_is_class_id, id);
}
int		rb_is_const_id(ID id)
{
	return_implement(int, rb_is_const_id, id);
}
int		rb_is_instance_id(ID);
int		rb_is_junk_id(ID);
int		rb_is_local_id(ID);
void	rb_iter_break(void);
VALUE	rb_iterate(VALUE(* it_proc)(VALUE), VALUE data1, VALUE(*bl_proc)(ANYARGS), VALUE data2)
{
	return_implement(VALUE, rb_iterate, it_proc, data1, bl_proc, data2);
}
int		rb_iterator_p();
VALUE	rb_iv_get(VALUE obj, const char* name)
{
	return_implement(VALUE, rb_iv_get, obj, name);
}
VALUE	rb_iv_set(VALUE obj, const char* name, VALUE v)
{
	return_implement(VALUE, rb_iv_set, obj, name, v);
}
VALUE	rb_ivar_defined(VALUE obj, ID id)
{
	return_implement(VALUE, rb_ivar_defined, obj, id);
}
VALUE	rb_ivar_get(VALUE obj, ID id)
{
	return_implement(VALUE, rb_ivar_get, obj, id);
}
VALUE	rb_ivar_set(VALUE obj, ID id, VALUE val)
{
	return_implement(VALUE, rb_ivar_set, obj, id, val);
}

void	rb_jump_tag(int);

int		rb_kcode();

//VALUE	rb_lastline_get(void);
//void	rb_lastline_set(VALUE);
//VALUE	rb_ll2big(s64);
//VALUE	rb_ll2inum(s64);
//void	rb_load(VALUE, int);
//void	rb_load_fail(char*);
//void	rb_load_file(char*);
//void	rb_load_protect(VALUE, int, int*);
//void	rb_loaderror(const char*, ANYARGS);

VALUE	rb_make_metaclass(VALUE v1, VALUE v2)
{
	return_implement(VALUE, rb_make_metaclass, v1, v2);
}
void	rb_mark_end_proc(void)
{
	noreturn_implement(rb_mark_end_proc);
}
void	rb_mark_generic_ivar(VALUE);
void	rb_mark_generic_ivar_tbl(void)
{
	noreturn_implement(rb_mark_generic_ivar_tbl);
}
void	rb_mark_hash(struct st_table*);
void	rb_mark_tbl(struct st_table*);
VALUE	rb_marshal_dump(VALUE, VALUE);
VALUE	rb_marshal_load(VALUE);
void	rb_match_busy(VALUE match);
void	rb_mem_clear(register VALUE*, register long);
int		rb_memcicmp(char*,char*,long);
int		rb_memcmp(char*,char*,long);
void	rb_memerror(void);
long	rb_memsearch(char*, long, char*, long);
int		rb_method_boundp(VALUE, ID, int);
struct RNode*	rb_method_node(VALUE klass, ID id);
VALUE	rb_mod_ancestors(VALUE);
VALUE	rb_mod_class_variables(VALUE);
void*	rb_mod_const_at(VALUE, void*);
VALUE	rb_mod_const_missing(VALUE, VALUE);
void*	rb_mod_const_of(VALUE, void*);
VALUE	rb_mod_constants(VALUE);
VALUE	rb_mod_include_p(VALUE, VALUE);
VALUE	rb_mod_included_modules(VALUE);
VALUE	rb_mod_init_copy(VALUE, VALUE);
VALUE	rb_mod_module_eval(int, VALUE*, VALUE);
VALUE	rb_mod_name(VALUE);
VALUE	rb_mod_remove_const(VALUE, VALUE);
VALUE	rb_mod_remove_cvar(VALUE mod, VALUE name)
{
	return_implement(VALUE, rb_mod_remove_cvar, mod, name);
}
VALUE	rb_module_new(void);

void	rb_name_class(VALUE obj, ID id)
{
	noreturn_implement(rb_name_class, obj, id);
}
//void	rb_name_error(ID, const char*, ANYARGS)
//{
//}
VALUE	rb_newobj(void)
{
	return_implement(VALUE, rb_newobj);
}
struct RNode*	rb_node_newnode(enum node_type type, VALUE a0, VALUE a1, VALUE a2)
{
	return_implement(struct RNode*, rb_node_newnode, type, a0, a1, a2);
}
//void	rb_notimplement(void);
double	rb_num2dbl(VALUE val)
{
	switch (TYPE(val))
	{
	case T_FLOAT:
		return RFLOAT(val)->value;

	case T_STRING:
		rb_raise(rb_eTypeError, "no implicit conversion to float from string");
		break;

	case T_NIL:
		rb_raise(rb_eTypeError, "no implicit conversion to float from nil");
		break;

	default:
		break;
	}

	return RFLOAT(rb_Float(val))->value;
}
//VALUE	rb_num2fix(VALUE val);
//long	rb_num2int(VALUE val);
//s64		rb_num2ll(VALUE val);
long	rb_num2long(VALUE val)
{
	return_implement(VALUE, rb_num2long, val);
}
//u64		rb_num2ull(VALUE val);
u32		rb_num2ulong(VALUE val)
{
	return_implement(u32, rb_num2ulong, val);
}
VALUE	rb_num_coerce_bin(VALUE x, VALUE y);
VALUE	rb_num_coerce_cmp(VALUE, VALUE);
VALUE	rb_num_coerce_relop(VALUE, VALUE);
void	rb_num_zerodiv(void);

VALUE	rb_obj_alloc(VALUE obj)
{
	return_implement(VALUE, rb_obj_alloc, obj);
}
VALUE	rb_obj_as_string(VALUE);
void	rb_obj_call_init(VALUE obj, int argc, VALUE* argv)
{
	noreturn_implement(rb_obj_call_init, obj, argc, argv);
}
VALUE	rb_obj_class(VALUE obj)
{
	return_implement(VALUE, rb_obj_class, obj);
}
char*	rb_obj_classname(VALUE obj)
{
	return_implement(char*, rb_obj_classname, obj);
}
VALUE	rb_obj_clone(VALUE obj)
{
	return_implement(VALUE, rb_obj_clone, obj);
}
VALUE	rb_obj_dup(VALUE obj)
{
	return_implement(VALUE, rb_obj_dup, obj);
}
VALUE	rb_obj_freeze(VALUE obj)
{
	return_implement(VALUE, rb_obj_freeze, obj);
}
VALUE	rb_obj_id(VALUE obj)
{
	return_implement(VALUE, rb_obj_id, obj);
}
VALUE	rb_obj_id_obsolete(VALUE obj)
{
	return_implement(VALUE, rb_obj_id_obsolete, obj);
}
void	rb_obj_infect(VALUE,VALUE);
VALUE	rb_obj_init_copy(VALUE obj1, VALUE obj2)
{
	return_implement(VALUE, rb_obj_init_copy, obj1, obj2);
}
VALUE	rb_obj_instance_eval(int argc, VALUE* argv, VALUE obj)
{
	return_implement(VALUE, rb_obj_instance_eval, argc, argv, obj);
}
VALUE	rb_obj_instance_variables(VALUE obj)
{
	return_implement(VALUE, rb_obj_instance_variables, obj);
}
VALUE	rb_obj_is_instance_of(VALUE obj, VALUE klass)
{
	return_implement(VALUE, rb_obj_is_instance_of, obj, klass);
}
VALUE	rb_obj_is_kind_of(VALUE obj, VALUE klass)
{
	return_implement(VALUE, rb_obj_is_kind_of, obj, klass);
}
VALUE	rb_obj_remove_instance_variable(VALUE obj, VALUE v)
{
	return_implement(VALUE, rb_obj_remove_instance_variable, obj, v);
}
VALUE	rb_obj_singleton_methods(int argc, VALUE* argv, VALUE obj)
{
	return_implement(VALUE, rb_obj_singleton_methods, argc, argv, obj);
}
VALUE	rb_obj_taint(VALUE obj)
{
	return_implement(VALUE, rb_obj_taint, obj);
}
VALUE	rb_obj_tainted(VALUE obj)
{
	return_implement(VALUE, rb_obj_tainted, obj);
}
VALUE	rb_obj_type(VALUE obj)
{
	return_implement(VALUE, rb_obj_type, obj);
}
VALUE	rb_obj_untaint(VALUE obj)
{
	return_implement(VALUE, rb_obj_untaint, obj);
}

void	rb_p(VALUE);
void	rb_parser_append_print(void);
void	rb_parser_while_loop(int, int);
VALUE	rb_path2class(const char*);
int		rb_path_check(char*);
char*	rb_path_end(const char *);
char*	rb_path_last_separator(const char *);
char*	rb_path_next(const char *);
char*	rb_path_skip_prefix(const char *);
int		rb_proc_exec(const char*);
VALUE	rb_proc_new(VALUE (*)(ANYARGS/* VALUE yieldarg[, VALUE procarg] */), VALUE);
VALUE	rb_proc_times(VALUE);
VALUE	rb_protect(VALUE (*)(VALUE), VALUE, int*);
VALUE	rb_protect_inspect(VALUE(*)(ANYARGS), VALUE, VALUE);
void	rb_provide(const char*);
int		rb_provided(const char*);

void	rb_quad_pack(char*,VALUE);
VALUE	rb_quad_unpack(const char*,int);

void	rb_raise(VALUE ex, const char* fmt, ...)
{
	char errinfo[BUFSIZ];
    va_list args;
    
	va_start(args, fmt);
    //vsprintf_s(errinfo, fmt, args);
	vsprintf(errinfo, fmt, args);
    va_end(args);

	noreturn_implement(rb_raise, ex, errinfo);
}
VALUE	rb_range_beg_len(VALUE range, long* begp, long* lenp, long len, int err)
{
	return_implement(VALUE, rb_range_beg_len, range, begp, lenp, len, err);
}
VALUE	rb_range_new(VALUE, VALUE, int);
void	rb_read_check(FILE* fp);
int		rb_read_pending(FILE *fp);
long	rb_reg_adjust_startpos(VALUE re, VALUE str, long pos, long reverse);
VALUE	rb_reg_eqq(VALUE re, VALUE str);
VALUE	rb_reg_last_match(VALUE);
VALUE	rb_reg_match(VALUE, VALUE);
VALUE	rb_reg_match2(VALUE);
VALUE	rb_reg_match_last(VALUE);
VALUE	rb_reg_match_post(VALUE);
VALUE	rb_reg_match_pre(VALUE);
int		rb_reg_mbclen2(unsigned int c, VALUE re);
VALUE	rb_reg_new(const char*, long, int);
VALUE	rb_reg_nth_defined(int, VALUE);
VALUE	rb_reg_nth_match(int, VALUE);
int		rb_reg_options(VALUE);
VALUE	rb_reg_quote(VALUE str);
VALUE	rb_reg_regcomp(VALUE str);
VALUE	rb_reg_regsub(VALUE str, VALUE src, struct re_registers *regs);
long	rb_reg_search(VALUE re, VALUE str, long pos, long reverse);
void	rb_remove_method(VALUE, const char*);
VALUE	rb_require(const char*);
VALUE	rb_require_safe(VALUE, int);
VALUE	rb_rescue(VALUE(*)(ANYARGS), VALUE, VALUE(*)(ANYARGS), VALUE);
//VALUE	rb_rescue2(VALUE(*)(ANYARGS), VALUE, VALUE(*)(ANYARGS), VALUE, ANYARGS);
struct kwtable*	rb_reserved_word(register const char* str, register unsigned int len);
int		rb_respond_to(VALUE obj, ID id)
{
	return_implement(int, rb_respond_to, obj, id);
}

//int		rb_scan_args(int, const VALUE*, const char*, ANYARGS)
//{
//	return 0;
//}
int
#ifdef HAVE_STDARG_PROTOTYPES
rb_scan_args(int argc, const VALUE *argv, const char *fmt, ...)
#else
rb_scan_args(argc, argv, fmt, va_alist)
int argc;
const VALUE *argv;
const char *fmt;
va_dcl
#endif
{
	int n, i = 0;
	const char *p = fmt;
	VALUE *var;
	va_list vargs;

	va_start(vargs, fmt);

	if (*p == '*') goto rest_arg;

	if (ISDIGIT(*p)) {
		n = *p - '0';
		if (n > argc)
			rb_raise(rb_eArgError, "wrong number of arguments (%d for %d)", argc, n);
		for (i=0; i<n; i++) {
			var = va_arg(vargs, VALUE*);
			if (var) *var = argv[i];
		}
		p++;
	}
	else {
		goto error;
	}

	if (ISDIGIT(*p)) {
		n = i + *p - '0';
		for (; i<n; i++) {
			var = va_arg(vargs, VALUE*);
			if (argc > i) {
				if (var) *var = argv[i];
			}
			else {
				if (var) *var = Qnil;
			}
		}
		p++;
	}

	if(*p == '*') {
rest_arg:
		var = va_arg(vargs, VALUE*);
		if (argc > i) {
			if (var) *var = rb_ary_new4(argc-i, argv+i);
			i = argc;
		}
		else {
			if (var) *var = rb_ary_new();
		}
		p++;
	}

	if (*p == '&') {
		var = va_arg(vargs, VALUE*);
		if (rb_block_given_p()) {
			*var = rb_block_proc();
		}
		else {
			*var = Qnil;
		}
		p++;
	}
	va_end(vargs);

	if (*p != '\0') {
		goto error;
	}

	if (argc > i) {
		rb_raise(rb_eArgError, "wrong number of arguments(%d for %d)", argc, i);
	}

	return argc;

error:
	//rb_fatal("bad scan arg format: %s", fmt);	//	origin
	rb_raise(rb_eArgError, "bad scan arg format: %s", fmt);
	return 0;
}
void	rb_secure(int level)
{
	noreturn_implement(rb_secure, level);
}
//void	rb_secure_update(VALUE);
//void	rb_set_class_path(VALUE, VALUE, const char*);
//void	rb_set_end_proc(void (*)(VALUE), VALUE);
//void	rb_set_kcode(const char*);
//void	rb_set_safe_level(int);
//VALUE	rb_singleton_class(VALUE);
//void	rb_singleton_class_attached(VALUE, VALUE);
//VALUE	rb_singleton_class_clone(VALUE);
//char*	rb_source_filename(const char*);
//char*	rb_str2cstr(VALUE,long*);
//VALUE	rb_str2inum(VALUE, int);
//VALUE	rb_str_append(VALUE, VALUE);
//void	rb_str_associate(VALUE, VALUE);
//VALUE	rb_str_associated(VALUE);
//VALUE	rb_str_buf_append(VALUE, VALUE);
VALUE	rb_str_buf_cat(VALUE str, const char* ptr, long len)
{
	return_implement(VALUE, rb_str_buf_cat, str, ptr, len);
}
//VALUE	rb_str_buf_cat2(VALUE, const char*);
VALUE	rb_str_buf_new(long capa)
{
	return_implement(VALUE, rb_str_buf_new, capa);
}
VALUE	rb_str_buf_new2(const char* ptr)
{
	return_implement(VALUE, rb_str_buf_new2, ptr);
}
VALUE	rb_str_cat(VALUE obj, const char* str, long len)
{
	return_implement(VALUE, rb_str_cat, obj, str, len);
}
VALUE	rb_str_cat2(VALUE str, const char* ptr)
{
	return_implement(VALUE, rb_str_cat2, str, ptr);
}
int		rb_str_cmp(VALUE str1, VALUE str2)
{
	return_implement(int, rb_str_cmp, str1, str2);
}
VALUE	rb_str_concat(VALUE obj, VALUE str)
{
	return_implement(VALUE, rb_str_concat, obj, str);
}
VALUE	rb_str_dump(VALUE obj)
{
	return_implement(VALUE, rb_str_dump, obj);
}
VALUE	rb_str_dup(VALUE obj)
{
	return_implement(VALUE, rb_str_dup, obj);
}
VALUE	rb_str_dup_frozen(VALUE);
VALUE	rb_str_freeze(VALUE);
int		rb_str_hash(VALUE);
VALUE	rb_str_inspect(VALUE obj)
{
	return_implement(VALUE, rb_str_inspect, obj);
}
VALUE	rb_str_intern(VALUE obj)
{
	return_implement(VALUE, rb_str_intern, obj);
}
void	rb_str_modify(VALUE);
VALUE	rb_str_new(const char* str, long len)
{
	return_implement(VALUE, rb_str_new, str, len);
}
VALUE	rb_str_new2(const char* str)
{
	return_implement(VALUE, rb_str_new2, str);
}
VALUE	rb_str_new3(VALUE str)
{
	return_implement(VALUE, rb_str_new3, str);
}
VALUE	rb_str_new4(VALUE);
VALUE	rb_str_new5(VALUE, const char*, long);
VALUE	rb_str_plus(VALUE, VALUE);
VALUE	rb_str_resize(VALUE, long);
void	rb_str_setter(VALUE, ID, VALUE*);
VALUE	rb_str_split(VALUE, const char*);
VALUE	rb_str_substr(VALUE, long, long);
VALUE	rb_str_times(VALUE, VALUE);
double	rb_str_to_dbl(VALUE str, int badcheck)
{
	return_implement(double, rb_str_to_dbl, str, badcheck);
}
VALUE	rb_str_to_inum(VALUE, int, int);
VALUE	rb_str_to_str(VALUE);
void	rb_str_update(VALUE, long, long, VALUE);
VALUE	rb_str_upto(VALUE, VALUE, int);
VALUE	rb_string_value(volatile VALUE*);
char*	rb_string_value_cstr(volatile VALUE*);
char*	rb_string_value_ptr(volatile VALUE* vp)
{
	return_implement(char*, rb_string_value_ptr, vp);
}
VALUE	rb_struct_alloc(VALUE, VALUE);
VALUE	rb_struct_aref(VALUE, VALUE);
VALUE	rb_struct_aset(VALUE, VALUE, VALUE);
//VALUE	rb_struct_define(const char*, ANYARGS)
//{
//	return 0;
//}
//VALUE	rb_struct_getmember(VALUE, ID);
VALUE	rb_struct_iv_get(VALUE c, char* name)
{
	return_implement(VALUE, rb_struct_iv_get, c, name);
}
//VALUE	rb_struct_new(VALUE, ANYARGS);
//VALUE*	rb_svar(int);
//VALUE	rb_sym_all_symbols(void);
//void	rb_sys_fail(const char*);
//void	rb_sys_warning(const char*, ANYARGS);
//void	rb_syswait(int);
//
//VALUE	rb_tainted_str_new(const char*, long);
//VALUE	rb_tainted_str_new2(const char*);
//
//int		rb_thread_alone(void);
//void	rb_thread_atfork(void);
//VALUE	rb_thread_create(VALUE (*)(ANYARGS), void*);
//VALUE	rb_thread_current();
//void	rb_thread_fd_close(int);
//int		rb_thread_fd_writable(int);
//VALUE	rb_thread_group(VALUE thread);
//void	rb_thread_interrupt(void);
//VALUE	rb_thread_kill(VALUE);
//VALUE	rb_thread_list();
//VALUE	rb_thread_local_aref(VALUE, ID);
//VALUE	rb_thread_local_aset(VALUE, ID, VALUE);
//VALUE	rb_thread_main(void);
//void	rb_thread_polling();
//VALUE	rb_thread_run(VALUE);
//void	rb_thread_schedule(void);
//int		rb_thread_select(ANYARGS);
//void	rb_thread_signal_raise(char*);
//void	rb_thread_sleep(int);
//void	rb_thread_sleep_forever(void);
//VALUE	rb_thread_stop(void);
//void	rb_thread_trap_eval(VALUE, int);
//void	rb_thread_wait_fd(int);
//void	rb_thread_wait_for(ANYARGS);
//VALUE	rb_thread_wakeup(VALUE);
//void	rb_throw(const char*, VALUE);
//struct timeval	rb_time_interval(VALUE time);
//VALUE	rb_time_new(ANYARGS);
//struct timeval	rb_time_timeval(VALUE time);
ID		rb_to_id(VALUE name)
{
	return_implement(ID, rb_to_id, name);
}
//VALUE	rb_to_int(VALUE);
//void	rb_trap_exec(void);
//void	rb_trap_exit(void);
//void	rb_trap_restore_mask();
//
VALUE	rb_uint2big(u32 n)
{
	return_implement(VALUE, rb_uint2big, n);
}
//VALUE	rb_uint2inum(u32);
//VALUE	rb_ull2big(u64);
//VALUE	rb_ull2inum(u64);
//void	rb_undef(VALUE, ID);
void	rb_undef_alloc_func(VALUE obj)
{
	noreturn_implement(rb_undef_alloc_func, obj);
}
void	rb_undef_method(VALUE obj, const char* name)
{
	noreturn_implement(rb_undef_method, obj, name);
}

VALUE	rb_values_at(VALUE, long, int, VALUE*, VALUE(*)(VALUE, long));

int		rb_w32_accept(int, struct sockaddr *, int *);
u32		rb_w32_asynchronize(u32 (*)(u32, int, u32*), u32, int, u32*, u32);
int		rb_w32_bind(int, struct sockaddr *, int);
int		rb_w32_close(int);
void	rb_w32_closedir(struct DIR *);
int		rb_w32_connect(int, struct sockaddr *, int);
void	rb_w32_enter_critical(void);
int		rb_w32_fclose(FILE*);
void	rb_w32_fdclr(int, struct fd_set*);
int		rb_w32_fdisset(int, struct fd_set*);
void	rb_w32_fdset(int, struct fd_set*);
void	rb_w32_free_environ(char **);
char**	rb_w32_get_environ(void);
SOCKET	rb_w32_get_osfhandle(int);
int		rb_w32_getc(FILE*);
char*	rb_w32_getcwd(char *buffer, int size);
char*	rb_w32_getenv(const char *);
struct hostent*	rb_w32_gethostbyaddr(char *, int, int);
struct hostent*	rb_w32_gethostbyname(char *);
int		rb_w32_gethostname(char *, int);
int		rb_w32_getpeername(int, struct sockaddr *, int *);
pid_t	rb_w32_getpid(void);
struct protoent*	rb_w32_getprotobyname(char *);
struct protoent*	rb_w32_getprotobynumber(int);
struct servent*		rb_w32_getservbyname(char *, char *);
struct servent*		rb_w32_getservbyport(int, char *);
int		rb_w32_getsockname(int, struct sockaddr *, int *);
int		rb_w32_getsockopt(int, int, int, char *, int *);
int		rb_w32_ioctlsocket(int, long, u_long *);
void	rb_w32_leave_critical(void);
int		rb_w32_listen(int, int);
int		rb_w32_main_context(int arg, void (*handler)(int));
//DIR*    rb_w32_opendir(const char*);
//int		rb_w32_putc(int, FILE*);
//struct direct*	rb_w32_readdir(DIR *);
int		rb_w32_recv(int, char *, int, int);
int		rb_w32_recvfrom(int, char *, int, int, struct sockaddr *, int *);
int		rb_w32_rename(const char *, const char *);
//void    rb_w32_rewinddir(DIR *);
//void    rb_w32_seekdir(DIR *, long);
long	rb_w32_select(int, fd_set *, fd_set *, fd_set *, struct timeval *);
int		rb_w32_send(int, char *, int, int);
int		rb_w32_sendto(int, char *, int, int, struct sockaddr *, int);
int		rb_w32_setsockopt(int, int, int, char *, int);
int		rb_w32_shutdown(int, int);
int		rb_w32_sleep(u32 msec);
//int		rb_w32_snprintf(char *, size_t, const char *, ANYARGS);
//int		rb_w32_socket(int, int, int);
//int		rb_w32_stat(const char *path, struct stat *st);
//char*	rb_w32_strerror(int);
//long    rb_w32_telldir(DIR *);
//int		rb_w32_times(struct tms *);
//int		rb_w32_utime(const char *, struct utimbuf *);
int		rb_w32_vsnprintf(char *buf, size_t size, const char *format, va_list va)
{
    int ret = _vsnprintf(buf, size, format, va);
    if (size > 0) buf[size - 1] = 0;
    return ret;
}

int		rb_waitpid(int, int*, int);
//void	rb_warn(const char*, ANYARGS);
//void	rb_warning(const char*, ANYARGS);
//VALUE	rb_with_disable_interrupt(VALUE (*proc)(), VALUE data);
//void	rb_write_error(const char*);
//void	rb_write_error2(const char*, long);
VALUE	rb_yield(VALUE val)
{
	return_implement(VALUE, rb_yield, val);
}
//VALUE	rb_yield_splat(VALUE);
//VALUE	rb_yield_values(int n, ANYARGS);

long	re_set_syntax(long syntax);

void*	ruby_xmalloc(long size)
{
	return_implement(void*, ruby_xmalloc, size);
}

void		st_add_direct(struct st_table * tbl, st_data_t t1, st_data_t t2)
{
	noreturn_implement(st_add_direct, tbl, t1, t2);
}
void		st_cleanup_safe(struct st_table *, st_data_t);
struct st_table*	st_copy(struct st_table *);
int			st_delete(struct st_table *, st_data_t *, st_data_t *);
int			st_delete_safe(struct st_table *, st_data_t *, st_data_t *, st_data_t);
void		st_foreach(struct st_table * tbl, int (*func)(), st_data_t t)
{
	noreturn_implement(st_foreach, tbl, func, t);
}
void		st_free_table(struct st_table *);
struct st_table*	st_init_numtable(void)
{
	return_implement(struct st_table*, st_init_numtable);
}
struct st_table*	st_init_numtable_with_size(int size)
{
	return_implement(struct st_table*, st_init_numtable_with_size, size);
}
struct st_table*	st_init_strtable(void)
{
	return_implement(struct st_table*, st_init_strtable);
}
struct st_table*	st_init_strtable_with_size(int size)
{
	return_implement(struct st_table*, st_init_strtable_with_size, size);
}
struct st_table*	st_init_table(struct st_hash_type *);
struct st_table*	st_init_table_with_size(struct st_hash_type *, int);
int			st_insert(struct st_table * tbl, st_data_t key, st_data_t value)
{
	return_implement(int, st_insert, tbl, key, value);
}
int			st_lookup(struct st_table * tbl, st_data_t key, st_data_t * value)
{
	return_implement(int, st_lookup, tbl, key, value);
}


//	未导出函数的实现
static VALUE rb_call(VALUE klass, VALUE recv, ID mid, int argc, const VALUE* argv, int scope)
{
	return_implement(VALUE, rb_call, klass, recv, mid, argc, argv, scope);
}