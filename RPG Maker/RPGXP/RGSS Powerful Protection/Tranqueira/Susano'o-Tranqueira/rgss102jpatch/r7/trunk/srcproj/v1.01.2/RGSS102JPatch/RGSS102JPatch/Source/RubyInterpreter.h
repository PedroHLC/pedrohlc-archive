/**
 *	@file		RubyInterpreter.h
 *
 *	@desc		RGSS102J补丁之解释器导出相关的定义文件
 *
 *	@author		Syalon
 *
 *	@history	2009/07/04	初版
 */

#ifndef __RUBY_INTERPRETER_H__
#define __RUBY_INTERPRETER_H__

#include "RubyInterpreterDefines.h"

#ifdef __cplusplus
extern "C" {
#endif	//	__cplusplus

/*
 *	变量导出声明
 */
#define rb_cArray				(*ptr_rb_cArray)
#define rb_cBignum				(*ptr_rb_cBignum)
#define rb_cClass				(*ptr_rb_cClass)
#define rb_cData				(*ptr_rb_cData)
#define rb_cDir					(*ptr_rb_cDir)
#define rb_cFalseClass			(*ptr_rb_cFalseClass)
#define rb_cFile				(*ptr_rb_cFile)
#define rb_cFixnum				(*ptr_rb_cFixnum)
#define rb_cFloat				(*ptr_rb_cFloat)
#define rb_cHash				(*ptr_rb_cHash)
#define rb_cIO					(*ptr_rb_cIO)
#define rb_cInteger				(*ptr_rb_cInteger)
#define rb_cModule				(*ptr_rb_cModule)
#define rb_cNilClass			(*ptr_rb_cNilClass)
#define rb_cNumeric				(*ptr_rb_cNumeric)
#define rb_cObject				(*ptr_rb_cObject)
#define rb_cProc				(*ptr_rb_cProc)
#define rb_cRange				(*ptr_rb_cRange)
#define rb_cRegexp				(*ptr_rb_cRegexp)
#define rb_cString				(*ptr_rb_cString)
#define rb_cStruct				(*ptr_rb_cStruct)
#define rb_cSymbol				(*ptr_rb_cSymbol)
#define rb_cThread				(*ptr_rb_cThread)
#define rb_cTime				(*ptr_rb_cTime)
#define rb_cTrueClass			(*ptr_rb_cTrueClass)

#define rb_eArgError			(*ptr_rb_eArgError)
#define rb_eEOFError			(*ptr_rb_eEOFError)
#define rb_eException			(*ptr_rb_eException)
#define rb_eFatal				(*ptr_rb_eFatal)
#define rb_eFloatDomainError	(*ptr_rb_eFloatDomainError)
#define rb_eIOError				(*ptr_rb_eIOError)
#define rb_eIndexError			(*ptr_rb_eIndexError)
#define rb_eInterrupt			(*ptr_rb_eInterrupt)
#define rb_eLoadError			(*ptr_rb_eLoadError)
#define rb_eNameError			(*ptr_rb_eNameError)
#define rb_eNoMemError			(*ptr_rb_eNoMemError)
#define rb_eNoMethodError		(*ptr_rb_eNoMethodError)
#define rb_eNotImpError			(*ptr_rb_eNotImpError)
#define rb_eRangeError			(*ptr_rb_eRangeError)
#define rb_eRuntimeError		(*ptr_rb_eRuntimeError)
#define rb_eScriptError			(*ptr_rb_eScriptError)
#define rb_eSecurityError		(*ptr_rb_eSecurityError)
#define rb_eSignal				(*ptr_rb_eSignal)
#define rb_eStandardError		(*ptr_rb_eStandardError)
#define rb_eSyntaxError			(*ptr_rb_eSyntaxError)
#define rb_eSystemCallError		(*ptr_rb_eSystemCallError)
#define rb_eSystemExit			(*ptr_rb_eSystemExit)
#define rb_eTypeError			(*ptr_rb_eTypeError)
#define rb_eZeroDivError		(*ptr_rb_eZeroDivError)

#define rb_mComparable			(*ptr_rb_mComparable)
#define rb_mEnumerable			(*ptr_rb_mEnumerable)
#define rb_mErrno				(*ptr_rb_mErrno)
#define rb_mFileTest			(*ptr_rb_mFileTest)
#define rb_mGC					(*ptr_rb_mGC)
#define rb_mKernel				(*ptr_rb_mKernel)
#define rb_mMath				(*ptr_rb_mMath)
#define rb_mPrecision			(*ptr_rb_mPrecision)
#define rb_mProcGID				(*ptr_rb_mProcGID)
#define rb_mProcID_Syscall		(*ptr_rb_mProcID_Syscall)
#define rb_mProcUID				(*ptr_rb_mProcUID)
#define rb_mProcess				(*ptr_rb_mProcess)

#define ruby_safe_level			(*ptr_ruby_safe_level)


extern VALUE*	ptr_rb_cArray;
extern VALUE*	ptr_rb_cBignum;
extern VALUE*	ptr_rb_cClass;
extern VALUE*	ptr_rb_cData;
extern VALUE*	ptr_rb_cDir;
extern VALUE*	ptr_rb_cFalseClass;
extern VALUE*	ptr_rb_cFile;
extern VALUE*	ptr_rb_cFixnum;
extern VALUE*	ptr_rb_cFloat;
extern VALUE*	ptr_rb_cHash;
extern VALUE*	ptr_rb_cIO;
extern VALUE*	ptr_rb_cInteger;
extern VALUE*	ptr_rb_cModule;
extern VALUE*	ptr_rb_cNilClass;
extern VALUE*	ptr_rb_cNumeric;
extern VALUE*	ptr_rb_cObject;
extern VALUE*	ptr_rb_cProc;
extern VALUE*	ptr_rb_cRange;
extern VALUE*	ptr_rb_cRegexp;
extern VALUE*	ptr_rb_cString;
extern VALUE*	ptr_rb_cStruct;
extern VALUE*	ptr_rb_cSymbol;
extern VALUE*	ptr_rb_cThread;
extern VALUE*	ptr_rb_cTime;
extern VALUE*	ptr_rb_cTrueClass;

extern VALUE*	ptr_rb_eArgError;
extern VALUE*	ptr_rb_eEOFError;
extern VALUE*	ptr_rb_eException;
extern VALUE*	ptr_rb_eFatal;
extern VALUE*	ptr_rb_eFloatDomainError;
extern VALUE*	ptr_rb_eIOError;
extern VALUE*	ptr_rb_eIndexError;
extern VALUE*	ptr_rb_eInterrupt;
extern VALUE*	ptr_rb_eLoadError;
extern VALUE*	ptr_rb_eNameError;
extern VALUE*	ptr_rb_eNoMemError;
extern VALUE*	ptr_rb_eNoMethodError;
extern VALUE*	ptr_rb_eNotImpError;
extern VALUE*	ptr_rb_eRangeError;
extern VALUE*	ptr_rb_eRuntimeError;
extern VALUE*	ptr_rb_eScriptError;
extern VALUE*	ptr_rb_eSecurityError;
extern VALUE*	ptr_rb_eSignal;
extern VALUE*	ptr_rb_eStandardError;
extern VALUE*	ptr_rb_eSyntaxError;
extern VALUE*	ptr_rb_eSystemCallError;
extern VALUE*	ptr_rb_eSystemExit;
extern VALUE*	ptr_rb_eTypeError;
extern VALUE*	ptr_rb_eZeroDivError;

extern VALUE*	ptr_rb_mComparable;
extern VALUE*	ptr_rb_mEnumerable;
extern VALUE*	ptr_rb_mErrno;
extern VALUE*	ptr_rb_mFileTest;
extern VALUE*	ptr_rb_mGC;
extern VALUE*	ptr_rb_mKernel;
extern VALUE*	ptr_rb_mMath;
extern VALUE*	ptr_rb_mPrecision;
extern VALUE*	ptr_rb_mProcGID;
extern VALUE*	ptr_rb_mProcID_Syscall;
extern VALUE*	ptr_rb_mProcUID;
extern VALUE*	ptr_rb_mProcess;

extern int*		ptr_ruby_safe_level;

#include "ruby1.8.1/ruby.h"
/*
 *	函数导出声明
 */
//void	rb_add_method(VALUE klass, ID mid, struct RNode* node, int noex);
//void	rb_alias(VALUE klass, ID name, ID def);
//void	rb_alias_variable(ID name1, ID name2);
//VALUE	rb_any_to_s(VALUE obj);
//VALUE	rb_apply(VALUE, ID, VALUE);
//VALUE	rb_ary_aref(int, VALUE*, VALUE);
//VALUE	rb_ary_assoc(VALUE, VALUE);
//VALUE	rb_ary_clear(VALUE);
//VALUE	rb_ary_cmp(VALUE, VALUE);
//VALUE	rb_ary_concat(VALUE, VALUE);
//VALUE	rb_ary_delete(VALUE, VALUE);
//VALUE	rb_ary_delete_at(VALUE, long);
//VALUE	rb_ary_dup(VALUE);
//VALUE	rb_ary_each(VALUE);
//VALUE	rb_ary_entry(VALUE, long);
//VALUE	rb_ary_freeze(VALUE);
//VALUE	rb_ary_includes(VALUE, VALUE);
//VALUE	rb_ary_join(VALUE, VALUE);
//VALUE	rb_ary_new(void);
//VALUE	rb_ary_new2(long);
//VALUE	rb_ary_new3(long, ANYARGS);
//VALUE	rb_ary_new4(long, const VALUE *);
//VALUE	rb_ary_plus(VALUE, VALUE);
//VALUE	rb_ary_pop(VALUE);
//VALUE	rb_ary_push(VALUE, VALUE);
//VALUE	rb_ary_rassoc(VALUE, VALUE);
//VALUE	rb_ary_reverse(VALUE);
//VALUE	rb_ary_shift(VALUE);
//VALUE	rb_ary_sort(VALUE);
//VALUE	rb_ary_sort_bang(VALUE);
//void	rb_ary_store(VALUE, long, VALUE);
//VALUE	rb_ary_to_ary(VALUE);
//VALUE	rb_ary_to_s(VALUE);
//VALUE	rb_ary_unshift(VALUE, VALUE);
//VALUE	rb_assoc_new(VALUE, VALUE);
//void	rb_attr(VALUE klass, ID id, int read, int write, int ex);
//VALUE	rb_attr_get(VALUE obj, ID id);
//void	rb_autoload(VALUE, ID, const char*);
//void	rb_autoload_load(VALUE, ID);
//VALUE	rb_autoload_p(VALUE, ID);
//
//VALUE	rb_backref_get();
//void	rb_backref_set(VALUE);
//void	rb_backtrace();
//double	rb_big2dbl(VALUE);
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
//int		rb_block_given_p();
//VALUE	rb_block_proc(void);
//void	rb_bug(const char*, ANYARGS);
//
//void	rb_call_inits(void);
//VALUE	rb_call_super(int argc, const VALUE* argv);
//VALUE	rb_catch(const char*, VALUE(*)(ANYARGS), VALUE);
//VALUE	rb_check_array_type(VALUE);
//VALUE	rb_check_convert_type(VALUE, int, const char*, const char*);
//void	rb_check_frozen(VALUE);
//void	rb_check_inheritable(VALUE);
//void	rb_check_safe_obj(VALUE x);
//void	rb_check_safe_str(VALUE x);
//VALUE	rb_check_string_type(VALUE);
//void	rb_check_type(VALUE x, int t);
//char*	rb_class2name(VALUE klass);
//VALUE	rb_class_boot(VALUE);
//VALUE	rb_class_inherited(VALUE, VALUE);
//VALUE	rb_class_init_copy(VALUE, VALUE);
//VALUE	rb_class_instance_methods(int, VALUE*, VALUE);
//VALUE	rb_class_new(VALUE);
//VALUE	rb_class_new_instance(int, VALUE*, VALUE);
//VALUE	rb_class_path(VALUE);
//VALUE	rb_class_private_instance_methods(int, VALUE*, VALUE);
//VALUE	rb_class_protected_instance_methods(int, VALUE*, VALUE);
//VALUE	rb_class_public_instance_methods(int, VALUE*, VALUE);
//VALUE	rb_class_real(VALUE);
//void	rb_clear_cache(void);
//void	rb_clear_cache_by_class(VALUE);
//void	rb_cmperr(VALUE, VALUE);
//int		rb_cmpint(VALUE, VALUE, VALUE);
//struct RNode*	rb_compile_cstr(const char* f, const char* s, int len, int line);
//void	rb_compile_error(const char*, ANYARGS);
//void	rb_compile_error_append(const char*, ANYARGS);
//struct RNode*	rb_compile_file(const char* f, VALUE file, int start);
//struct RNode*	rb_compile_string(const char* f, VALUE s, int line);
//int		rb_const_defined(VALUE, ID);
//int		rb_const_defined_at(VALUE, ID);
//int		rb_const_defined_from(VALUE, ID);
//VALUE	rb_const_get(VALUE, ID);
//VALUE	rb_const_get_at(VALUE, ID);
//VALUE	rb_const_get_from(VALUE, ID);
//VALUE	rb_const_list(void*);
//void	rb_const_set(VALUE, ID, VALUE);
//VALUE	rb_convert_type(VALUE,int,const char*,const char*);
//void	rb_copy_generic_ivar(VALUE, VALUE);
//VALUE	rb_cstr2inum(const char*, int);
//double	rb_cstr_to_dbl(const char*, int);
//VALUE	rb_cstr_to_inum(const char*, int, int);
//VALUE	rb_cv_get(VALUE, const char*);
//void	rb_cv_set(VALUE, const char*, VALUE);
//VALUE	rb_cvar_defined(VALUE, ID);
//VALUE	rb_cvar_get(VALUE, ID);
//void	rb_cvar_set(VALUE, ID, VALUE, int);
//
//VALUE	rb_data_object_alloc(VALUE klass, void* datap, RubyDataFunc dmark, RubyDataFunc dfree);
//VALUE	rb_dbl2big(double);
//VALUE	rb_dbl_cmp(double, double);
//void	rb_define_alias(VALUE, const char*, const char*);
//void	rb_define_alloc_func(VALUE, VALUE (*)(VALUE));
//void	rb_define_attr(VALUE, const char*, int, int);
//VALUE	rb_define_class(const char* name, VALUE super);
//VALUE	rb_define_class_id(ID, VALUE);
//VALUE	rb_define_class_under(VALUE, const char*, VALUE);
//void	rb_define_class_variable(VALUE, const char*, VALUE);
//void	rb_define_const(VALUE,const char*, VALUE);
//void	rb_define_global_const(const char*, VALUE);
//void	rb_define_global_function(const char*, VALUE(*)(ANYARGS), int);
//void	rb_define_hooked_variable(const char*, VALUE*, VALUE(*)(ANYARGS), void(*)(ANYARGS));
//void	rb_define_method(VALUE, const char*, VALUE(*)(ANYARGS), int);
//void	rb_define_method_id(VALUE, ID, VALUE (*)(ANYARGS), int);
//VALUE	rb_define_module(const char*);
//void	rb_define_module_function(VALUE,const char*,VALUE(*)(ANYARGS),int);
//VALUE	rb_define_module_id(ID);
//VALUE	rb_define_module_under(VALUE, const char*);
//void	rb_define_private_method(VALUE, const char*, VALUE (*)(ANYARGS), int);
//void	rb_define_protected_method(VALUE, const char*, VALUE (*)(ANYARGS), int);
//void	rb_define_readonly_variable(const char*,VALUE*);
//void	rb_define_singleton_method(VALUE, const char*, VALUE(*)(ANYARGS), int);
//void	rb_define_variable(const char*,VALUE*);
//void	rb_define_virtual_variable(const char*, VALUE(*)(ANYARGS), void(*)(ANYARGS));
//VALUE	rb_detach_process(int);
//void	rb_disable_super(VALUE klass, const char* name);
//VALUE	rb_dvar_curr(ID);
//VALUE	rb_dvar_defined(ID);
//void	rb_dvar_push(ID, VALUE);
//VALUE	rb_dvar_ref(ID);
//
//VALUE	rb_each(VALUE);
//void	rb_enable_super(VALUE klass, const char* name);
//VALUE	rb_ensure(VALUE(*)(ANYARGS), VALUE,VALUE(*)(ANYARGS), VALUE);
//int		rb_env_path_tainted(void);
//void	rb_eof_error();
//int		rb_eql(VALUE, VALUE);
//VALUE	rb_equal(VALUE,VALUE);
//void	rb_error_frozen(char* what);
//VALUE	rb_eval_cmd(VALUE, VALUE, int);
//VALUE	rb_eval_string(const char*);
//VALUE	rb_eval_string_protect(const char*, int*);
//VALUE	rb_eval_string_wrap(const char*, int*);
//void	rb_exc_fatal(VALUE);
//VALUE	rb_exc_new(VALUE, const char*, long);
//VALUE	rb_exc_new2(VALUE, const char*);
//VALUE	rb_exc_new3(VALUE, VALUE);
//void	rb_exc_raise(VALUE mesg);
//void	rb_exec_end_proc(void);
//void	rb_exit(int);
//void	rb_extend_object(VALUE,VALUE);
//
//VALUE	rb_f_abort(int, VALUE*);
//VALUE	rb_f_exec(int, VALUE*);
//VALUE	rb_f_exit(int, VALUE*);
//VALUE	rb_f_global_variables(void);
//VALUE	rb_f_kill(int, VALUE*);
//VALUE	rb_f_lambda(void);
//VALUE	rb_f_require(VALUE, VALUE);
//VALUE	rb_f_sprintf(int, VALUE*);
//VALUE	rb_f_trace_var(int, VALUE*);
//VALUE	rb_f_untrace_var(int, VALUE*);
//void	rb_fatal(const char*, ANYARGS);
//FILE*	rb_fdopen(int fd, const char* mode);
//void	rb_file_const(const char*, VALUE);
//VALUE	rb_file_expand_path(VALUE fname, VALUE dname);
//VALUE	rb_file_open(const char*, const char*);
//VALUE	rb_file_s_expand_path(int, VALUE *);
//VALUE	rb_file_sysopen(const char* fname, int flags, int mode);
//VALUE	rb_find_file(VALUE);
//int		rb_find_file_ext(VALUE*, const char* const*);
//long	rb_fix2int(VALUE);
//VALUE	rb_fix2str(VALUE, int);
//VALUE	rb_float_new(double);
//FILE*	rb_fopen(const char* fname, const char* mode);
//ID		rb_frame_last_func();
//void	rb_free_generic_ivar(VALUE);
//void	rb_frozen_class_p(VALUE);
//VALUE	rb_funcall(VALUE, ID, int, ANYARGS);
//VALUE	rb_funcall2(VALUE, ID, int, const VALUE*);
//VALUE	rb_funcall3(VALUE, ID, int, const VALUE*);
//
//void	rb_gc(void);
//void	rb_gc_call_finalizer_at_exit(void);
//void	rb_gc_copy_finalizer(VALUE,VALUE);
//VALUE	rb_gc_disable(void);
//VALUE	rb_gc_enable(void);
//void	rb_gc_force_recycle(VALUE);
//void	rb_gc_mark(VALUE);
//void	rb_gc_mark_frame(struct FRAME * frame);
//void	rb_gc_mark_global_tbl(void);
//void	rb_gc_mark_locations(VALUE*, VALUE*);
//void	rb_gc_mark_maybe(VALUE);
//void	rb_gc_mark_parser(void);
//void	rb_gc_mark_threads(void);
//void	rb_gc_mark_trap_list(void);
//void	rb_gc_register_address(VALUE*);
//VALUE	rb_gc_start(void);
//void	rb_gc_unregister_address(VALUE*);
//struct st_table*	rb_generic_ivar_table(VALUE);
//const char*			rb_get_kcode(void);
//int		rb_getc(FILE *f);
//VALUE	rb_gets();
//void	rb_glob(char*, void(*)(const char*, VALUE), VALUE);
//struct global_entry*	rb_global_entry(ID id);
//void	rb_global_variable(VALUE*);
//void	rb_globi(char*, void(*)(const char*, VALUE), VALUE);
//VALUE	rb_gv_get(const char*);
//VALUE	rb_gv_set(const char*, VALUE);
//VALUE	rb_gvar_defined(struct global_entry *entry);
//VALUE	rb_gvar_get(struct global_entry *entry);
//VALUE	rb_gvar_set(struct global_entry *entry, VALUE val);
//
//VALUE	rb_hash(VALUE);
//VALUE	rb_hash_aref(VALUE, VALUE);
//VALUE	rb_hash_aset(VALUE, VALUE, VALUE);
//VALUE	rb_hash_delete(VALUE, VALUE);
//VALUE	rb_hash_delete_if(VALUE);
//VALUE	rb_hash_freeze(VALUE);
//VALUE	rb_hash_new(void);
//VALUE	rb_hash_reject_bang(VALUE hash);
//VALUE	rb_hash_select(int argc, VALUE* argv, VALUE hash);
//VALUE	rb_hash_values_at(int argc, VALUE* argv, VALUE hash);
//
//char*	rb_id2name(ID);
//ID		rb_id_attrset(ID);
//void	rb_include_module(VALUE, VALUE);
//VALUE	rb_inspect(VALUE);
//VALUE	rb_inspecting_p(VALUE);
//VALUE	rb_int2big(long);
//VALUE	rb_int2inum(long);
//ID		rb_intern(const char*);
//void	rb_interrupt(void);
//void	rb_invalid_str(const char*, const char*);
//VALUE	rb_io_addstr(VALUE, VALUE);
//VALUE	rb_io_binmode(VALUE);
//void	rb_io_check_closed(struct OpenFile *fptr);
//void	rb_io_check_readable(struct OpenFile *fptr);
//void	rb_io_check_writable(struct OpenFile *fptr);
//VALUE	rb_io_close(VALUE);
//VALUE	rb_io_eof(VALUE);
//char*	rb_io_flags_mode(int flags, char* mode);
//void	rb_io_fptr_finalize(struct OpenFile *fptr);
//long	rb_io_fread(char* ptr, long len, FILE* f);
//long	rb_io_fwrite(const char* ptr, long len, FILE* f);
//VALUE	rb_io_getc(VALUE);
//VALUE	rb_io_gets(VALUE);
//int		rb_io_mode_flags(const char* mode);
//VALUE	rb_io_print(int, VALUE*, VALUE);
//VALUE	rb_io_printf(int, VALUE*, VALUE);
//VALUE	rb_io_puts(int, VALUE*, VALUE);
//void	rb_io_synchronized(struct OpenFile *fptr);
//VALUE	rb_io_taint_check(VALUE io);
//void	rb_io_unbuffered(struct OpenFile *fptr);
//VALUE	rb_io_ungetc(VALUE io, VALUE c);
//int		rb_io_wait_readable(int f);
//int		rb_io_wait_writable(int f);
//VALUE	rb_io_write(VALUE, VALUE);
//int		rb_is_class_id(ID);
//int		rb_is_const_id(ID);
//int		rb_is_instance_id(ID);
//int		rb_is_junk_id(ID);
//int		rb_is_local_id(ID);
//void	rb_iter_break(void);
//VALUE	rb_iterate(VALUE(*)(VALUE), VALUE,VALUE(*)(ANYARGS), VALUE);
//int		rb_iterator_p();
//VALUE	rb_iv_get(VALUE, const char*);
//VALUE	rb_iv_set(VALUE, const char*, VALUE);
//VALUE	rb_ivar_defined(VALUE, ID);
//VALUE	rb_ivar_get(VALUE, ID);
//VALUE	rb_ivar_set(VALUE, ID, VALUE);
//
//void	rb_jump_tag(int);
//
//int		rb_kcode();
//
//VALUE	rb_lastline_get(void);
//void	rb_lastline_set(VALUE);
//VALUE	rb_ll2big(s64);
//VALUE	rb_ll2inum(s64);
//void	rb_load(VALUE, int);
//void	rb_load_fail(char*);
//void	rb_load_file(char*);
//void	rb_load_protect(VALUE, int, int*);
//void	rb_loaderror(const char*, ANYARGS);
//
//VALUE	rb_make_metaclass(VALUE, VALUE);
//void	rb_mark_end_proc(void);
//void	rb_mark_generic_ivar(VALUE);
//void	rb_mark_generic_ivar_tbl(void);
//void	rb_mark_hash(struct st_table*);
//void	rb_mark_tbl(struct st_table*);
//VALUE	rb_marshal_dump(VALUE, VALUE);
//VALUE	rb_marshal_load(VALUE);
//void	rb_match_busy(VALUE match);
//void	rb_mem_clear(register VALUE*, register long);
//int		rb_memcicmp(char*,char*,long);
//int		rb_memcmp(char*,char*,long);
//void	rb_memerror(void);
//long	rb_memsearch(char*, long, char*, long);
//int		rb_method_boundp(VALUE, ID, int);
//struct RNode*	rb_method_node(VALUE klass, ID id);
//VALUE	rb_mod_ancestors(VALUE);
//VALUE	rb_mod_class_variables(VALUE);
//void*	rb_mod_const_at(VALUE, void*);
//VALUE	rb_mod_const_missing(VALUE, VALUE);
//void*	rb_mod_const_of(VALUE, void*);
//VALUE	rb_mod_constants(VALUE);
//VALUE	rb_mod_include_p(VALUE, VALUE);
//VALUE	rb_mod_included_modules(VALUE);
//VALUE	rb_mod_init_copy(VALUE, VALUE);
//VALUE	rb_mod_module_eval(int, VALUE*, VALUE);
//VALUE	rb_mod_name(VALUE);
//VALUE	rb_mod_remove_const(VALUE, VALUE);
//VALUE	rb_mod_remove_cvar(VALUE, VALUE);
//VALUE	rb_module_new(void);
//
//void	rb_name_class(VALUE, ID);
//void	rb_name_error(ID, const char*, ANYARGS);
//VALUE	rb_newobj(void);
//struct RNode*	rb_node_newnode(enum node_type, VALUE, VALUE, VALUE);
//void	rb_notimplement(void);
//double	rb_num2dbl(VALUE);
//VALUE	rb_num2fix(VALUE val);
//long	rb_num2int(VALUE val);
//s64		rb_num2ll(VALUE val);
//long	rb_num2long(VALUE val);
//u64		rb_num2ull(VALUE val);
//u32		rb_num2ulong(VALUE val);
//VALUE	rb_num_coerce_bin(VALUE x, VALUE y);
//VALUE	rb_num_coerce_cmp(VALUE, VALUE);
//VALUE	rb_num_coerce_relop(VALUE, VALUE);
//void	rb_num_zerodiv(void);
//
//VALUE	rb_obj_alloc(VALUE);
//VALUE	rb_obj_as_string(VALUE);
//void	rb_obj_call_init(VALUE, int, VALUE*);
//VALUE	rb_obj_class(VALUE);
//char*	rb_obj_classname(VALUE);
//VALUE	rb_obj_clone(VALUE);
//VALUE	rb_obj_dup(VALUE);
//VALUE	rb_obj_freeze(VALUE);
//VALUE	rb_obj_id(VALUE);
//VALUE	rb_obj_id_obsolete(VALUE obj);
//void	rb_obj_infect(VALUE,VALUE);
//VALUE	rb_obj_init_copy(VALUE, VALUE);
//VALUE	rb_obj_instance_eval(int, VALUE*, VALUE);
//VALUE	rb_obj_instance_variables(VALUE);
//VALUE	rb_obj_is_instance_of(VALUE, VALUE);
//VALUE	rb_obj_is_kind_of(VALUE, VALUE);
//VALUE	rb_obj_remove_instance_variable(VALUE, VALUE);
//VALUE	rb_obj_singleton_methods(int, VALUE*, VALUE);
//VALUE	rb_obj_taint(VALUE);
//VALUE	rb_obj_tainted(VALUE);
//VALUE	rb_obj_type(VALUE obj);
//VALUE	rb_obj_untaint(VALUE);
//
//void	rb_p(VALUE);
//void	rb_parser_append_print(void);
//void	rb_parser_while_loop(int, int);
//VALUE	rb_path2class(const char*);
//int		rb_path_check(char*);
//char*	rb_path_end(const char *);
//char*	rb_path_last_separator(const char *);
//char*	rb_path_next(const char *);
//char*	rb_path_skip_prefix(const char *);
//int		rb_proc_exec(const char*);
//VALUE	rb_proc_new(VALUE (*)(ANYARGS/* VALUE yieldarg[, VALUE procarg] */), VALUE);
//VALUE	rb_proc_times(VALUE);
//VALUE	rb_protect(VALUE (*)(VALUE), VALUE, int*);
//VALUE	rb_protect_inspect(VALUE(*)(ANYARGS), VALUE, VALUE);
//void	rb_provide(const char*);
//int		rb_provided(const char*);
//
//void	rb_quad_pack(char*,VALUE);
//VALUE	rb_quad_unpack(const char*,int);
//
//void	rb_raise(VALUE, const char*, ...);
//VALUE	rb_range_beg_len(VALUE, long*, long*, long, int);
//VALUE	rb_range_new(VALUE, VALUE, int);
//void	rb_read_check(FILE* fp);
//int		rb_read_pending(FILE *fp);
//long	rb_reg_adjust_startpos(VALUE re, VALUE str, long pos, long reverse);
//VALUE	rb_reg_eqq(VALUE re, VALUE str);
//VALUE	rb_reg_last_match(VALUE);
//VALUE	rb_reg_match(VALUE, VALUE);
//VALUE	rb_reg_match2(VALUE);
//VALUE	rb_reg_match_last(VALUE);
//VALUE	rb_reg_match_post(VALUE);
//VALUE	rb_reg_match_pre(VALUE);
//int		rb_reg_mbclen2(unsigned int c, VALUE re);
//VALUE	rb_reg_new(const char*, long, int);
//VALUE	rb_reg_nth_defined(int, VALUE);
//VALUE	rb_reg_nth_match(int, VALUE);
//int		rb_reg_options(VALUE);
//VALUE	rb_reg_quote(VALUE str);
//VALUE	rb_reg_regcomp(VALUE str);
//VALUE	rb_reg_regsub(VALUE str, VALUE src, struct re_registers *regs);
//long	rb_reg_search(VALUE re, VALUE str, long pos, long reverse);
//void	rb_remove_method(VALUE, const char*);
//VALUE	rb_require(const char*);
//VALUE	rb_require_safe(VALUE, int);
//VALUE	rb_rescue(VALUE(*)(ANYARGS), VALUE, VALUE(*)(ANYARGS), VALUE);
//VALUE	rb_rescue2(VALUE(*)(ANYARGS), VALUE, VALUE(*)(ANYARGS), VALUE, ANYARGS);
//struct kwtable*	rb_reserved_word(register const char* str, register unsigned int len);
//int		rb_respond_to(VALUE, ID);
//
//int		rb_scan_args(int, const VALUE*, const char*, ANYARGS);
//void	rb_secure(int);
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
//VALUE	rb_str_buf_cat(VALUE, const char*, long);
//VALUE	rb_str_buf_cat2(VALUE, const char*);
//VALUE	rb_str_buf_new(long);
//VALUE	rb_str_buf_new2(const char*);
//VALUE	rb_str_cat(VALUE, const char*, long);
//VALUE	rb_str_cat2(VALUE, const char*);
//int		rb_str_cmp(VALUE, VALUE);
//VALUE	rb_str_concat(VALUE, VALUE);
//VALUE	rb_str_dump(VALUE);
//VALUE	rb_str_dup(VALUE);
//VALUE	rb_str_dup_frozen(VALUE);
//VALUE	rb_str_freeze(VALUE);
//int		rb_str_hash(VALUE);
//VALUE	rb_str_inspect(VALUE);
//VALUE	rb_str_intern(VALUE);
//void	rb_str_modify(VALUE);
//VALUE	rb_str_new(const char*, long);
//VALUE	rb_str_new2(const char*);
//VALUE	rb_str_new3(VALUE);
//VALUE	rb_str_new4(VALUE);
//VALUE	rb_str_new5(VALUE, const char*, long);
//VALUE	rb_str_plus(VALUE, VALUE);
//VALUE	rb_str_resize(VALUE, long);
//void	rb_str_setter(VALUE, ID, VALUE*);
//VALUE	rb_str_split(VALUE, const char*);
//VALUE	rb_str_substr(VALUE, long, long);
//VALUE	rb_str_times(VALUE, VALUE);
//double	rb_str_to_dbl(VALUE, int);
//VALUE	rb_str_to_inum(VALUE, int, int);
//VALUE	rb_str_to_str(VALUE);
//void	rb_str_update(VALUE, long, long, VALUE);
//VALUE	rb_str_upto(VALUE, VALUE, int);
//VALUE	rb_string_value(volatile VALUE*);
//char*	rb_string_value_cstr(volatile VALUE*);
//char*	rb_string_value_ptr(volatile VALUE*);
//VALUE	rb_struct_alloc(VALUE, VALUE);
//VALUE	rb_struct_aref(VALUE, VALUE);
//VALUE	rb_struct_aset(VALUE, VALUE, VALUE);
//VALUE	rb_struct_define(const char*, ANYARGS);
//VALUE	rb_struct_getmember(VALUE, ID);
//VALUE	rb_struct_iv_get(VALUE, char*);
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
//ID		rb_to_id(VALUE);
//VALUE	rb_to_int(VALUE);
//void	rb_trap_exec(void);
//void	rb_trap_exit(void);
//void	rb_trap_restore_mask();
//
//VALUE	rb_uint2big(u32);
//VALUE	rb_uint2inum(u32);
//VALUE	rb_ull2big(u64);
//VALUE	rb_ull2inum(u64);
//void	rb_undef(VALUE, ID);
//void	rb_undef_alloc_func(VALUE);
//void	rb_undef_method(VALUE,const char*);
//
//VALUE	rb_values_at(VALUE, long, int, VALUE*, VALUE(*)(VALUE, long));
//
//int		rb_w32_accept(int, struct sockaddr *, int *);
//u32		rb_w32_asynchronize(u32 (*)(u32, int, u32*), u32, int, u32*, u32);
//int		rb_w32_bind(int, struct sockaddr *, int);
//int		rb_w32_close(int);
//void	rb_w32_closedir(struct DIR *);
//int		rb_w32_connect(int, struct sockaddr *, int);
//void	rb_w32_enter_critical(void);
//int		rb_w32_fclose(FILE*);
//void	rb_w32_fdclr(int, struct fd_set*);
//int		rb_w32_fdisset(int, struct fd_set*);
//void	rb_w32_fdset(int, struct fd_set*);
//void	rb_w32_free_environ(char **);
//char**	rb_w32_get_environ(void);
//SOCKET	rb_w32_get_osfhandle(int);
//int		rb_w32_getc(FILE*);
//char*	rb_w32_getcwd(char *buffer, int size);
//char*	rb_w32_getenv(const char *);
//struct hostent*	rb_w32_gethostbyaddr(char *, int, int);
//struct hostent*	rb_w32_gethostbyname(char *);
//int		rb_w32_gethostname(char *, int);
//int		rb_w32_getpeername(int, struct sockaddr *, int *);
//pid_t	rb_w32_getpid(void);
//struct protoent*	rb_w32_getprotobyname(char *);
//struct protoent*	rb_w32_getprotobynumber(int);
//struct servent*		rb_w32_getservbyname(char *, char *);
//struct servent*		rb_w32_getservbyport(int, char *);
//int		rb_w32_getsockname(int, struct sockaddr *, int *);
//int		rb_w32_getsockopt(int, int, int, char *, int *);
//int		rb_w32_ioctlsocket(int, long, u_long *);
//void	rb_w32_leave_critical(void);
//int		rb_w32_listen(int, int);
//int		rb_w32_main_context(int arg, void (*handler)(int));
//DIR*    rb_w32_opendir(const char*);
//int		rb_w32_putc(int, FILE*);
//struct direct*	rb_w32_readdir(DIR *);
//int		rb_w32_recv(int, char *, int, int);
//int		rb_w32_recvfrom(int, char *, int, int, struct sockaddr *, int *);
//int		rb_w32_rename(const char *, const char *);
//void    rb_w32_rewinddir(DIR *);
//void    rb_w32_seekdir(DIR *, long);
//long	rb_w32_select(int, fd_set *, fd_set *, fd_set *, struct timeval *);
//int		rb_w32_send(int, char *, int, int);
//int		rb_w32_sendto(int, char *, int, int, struct sockaddr *, int);
//int		rb_w32_setsockopt(int, int, int, char *, int);
//int		rb_w32_shutdown(int, int);
//int		rb_w32_sleep(u32 msec);
//int		rb_w32_snprintf(char *, size_t, const char *, ANYARGS);
//int		rb_w32_socket(int, int, int);
//int		rb_w32_stat(const char *path, struct stat *st);
//char*	rb_w32_strerror(int);
//long    rb_w32_telldir(DIR *);
//int		rb_w32_times(struct tms *);
//int		rb_w32_utime(const char *, struct utimbuf *);
//int		rb_w32_vsnprintf(char *, size_t, const char *, va_list);
//
//int		rb_waitpid(int, int*, int);
//void	rb_warn(const char*, ANYARGS);
//void	rb_warning(const char*, ANYARGS);
//VALUE	rb_with_disable_interrupt(VALUE (*proc)(), VALUE data);
//void	rb_write_error(const char*);
//void	rb_write_error2(const char*, long);
//VALUE	rb_yield(VALUE);
//VALUE	rb_yield_splat(VALUE);
//VALUE	rb_yield_values(int n, ANYARGS);
//
//long	re_set_syntax(long syntax);
//
//void*	ruby_xmalloc(long size);
//
//void		st_add_direct(st_table *, st_data_t, st_data_t);
//void		st_cleanup_safe(st_table *, st_data_t);
//st_table*	st_copy(st_table *);
//int			st_delete(st_table *, st_data_t *, st_data_t *);
//int			st_delete_safe(st_table *, st_data_t *, st_data_t *, st_data_t);
//void		st_foreach(st_table *, int (*)(), st_data_t);
//void		st_free_table(st_table *);
//st_table*	st_init_numtable(void);
//st_table*	st_init_numtable_with_size(int);
//st_table*	st_init_strtable(void);
//st_table*	st_init_strtable_with_size(int);
//st_table*	st_init_table(struct st_hash_type *);
//st_table*	st_init_table_with_size(struct st_hash_type *, int);
//int			st_insert(st_table *, st_data_t, st_data_t);
//int			st_lookup(st_table *, st_data_t, st_data_t *);

#ifdef __cplusplus
}
#endif	//	__cplusplus

#endif	//	__RUBY_INTERPRETER_H__