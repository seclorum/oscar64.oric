#pragma once

class Location
{
public:
	const char		*	mFileName;
	int					mLine, mColumn;
	const Location	*	mFrom;

	Location() : mFileName(nullptr), mLine(0), mColumn(0), mFrom(nullptr) {}
	Location(const Location& loc, const Location* from)
		: mFileName(loc.mFileName), mLine(loc.mLine), mColumn(loc.mColumn), mFrom(from)
	{}
};

class Ident;

enum ErrorID
{
	EINFO_GENERIC = 1000,
	EINFO_EXPANDED = 1001,
	EINFO_ORIGINAL_DEFINITION = 1002,
	EINFO_CALLED_FROM = 1003,
	EINFO_SIZE = 1004,

	EWARN_GENERIC = 2000,
	EWARN_CONSTANT_TRUNCATED,
	EWARN_UNKNOWN_PRAGMA,
	EWARN_INDEX_OUT_OF_BOUNDS,
	EWARN_SYNTAX,
	EWARN_NOT_INTERRUPT_SAFE,
	EWARN_BOOL_SHORTCUT,
	EWARN_OPTIMIZER_LOCKED,
	EWARN_LOOP_UNROLL_IGNORED,
	EWARN_USE_OF_UNINITIALIZED_VARIABLE,
	EWARN_MISSING_RETURN_STATEMENT,
	EWARN_UNREACHABLE_CODE,
	EWARN_NULL_POINTER_DEREFERENCED,
	EWARN_DESTRUCTOR_MISMATCH,
	EWARN_NUMERIC_0_USED_AS_NULLPTR,
	EWARN_FLOAT_TO_INT,

	EERR_GENERIC = 3000,
	EERR_FILE_NOT_FOUND,
	EERR_RUNTIME_CODE,
	EERR_UNIMPLEMENTED,
	EERR_COMMAND_LINE,
	EERR_OBJECT_NOT_FOUND,
	EERR_SYNTAX,
	EERR_EXECUTION_FAILED,
	EERR_CONSTANT_INITIALIZER,
	EERR_CONSTANT_TYPE,
	EERR_VARIABLE_TYPE,
	EERR_INVALID_VALUE,
	EERR_INCOMPATIBLE_TYPES,
	EERR_INCOMPATIBLE_OPERATOR,
	EERR_CONST_ASSIGN,
	EERR_NOT_AN_LVALUE,
	EERR_INVALID_INDEX,
	EERR_WRONG_PARAMETER,
	EERR_INVALID_RETURN,
	EERR_INVALID_BREAK,
	EERR_INVALID_CONTINUE,
	EERR_DUPLICATE_DEFAULT,
	EERR_UNDEFINED_OBJECT,
	EERR_DUPLICATE_DEFINITION,
	EERR_NOT_A_TYPE,
	EERR_DECLARATION_DIFFERS,
	EERR_INVALID_IDENTIFIER,
	EERR_ASM_INVALD_OPERAND,
	EERR_ASM_INVALID_INSTRUCTION,
	EERR_ASM_INVALID_MODE,
	EERR_PRAGMA_PARAMETER,
	ERRR_PREPROCESSOR,
	ERRR_INVALID_CASE,
	ERRR_INSUFFICIENT_MEMORY,
	ERRR_INTERRUPT_TO_COMPLEX,
	ERRR_INVALID_STORAGE_TYPE,
	ERRR_SEMICOLON_EXPECTED,
	ERRR_USE_OF_UNINITIALIZED_VARIABLE,
	ERRR_STRIPE_REQUIRES_FIXED_SIZE_ARRAY,
	ERRR_CANNOT_FIND_BANK_OF_EXPRESSION,
	ERRO_NOT_A_NAMESPACE,
	ERRO_NOT_A_BASE_CLASS,
	ERRO_THIS_OUTSIDE_OF_METHOD,
	ERRO_NO_MATCHING_FUNCTION_CALL,
	ERRO_AMBIGUOUS_FUNCTION_CALL,
	EERR_NO_DEFAULT_CONSTRUCTOR,
	EERR_INVALID_OPERATOR,
	EERR_MISSING_TEMP,
	EERR_NON_STATIC_MEMBER,
	EERR_TEMPLATE_PARAMS,
	EERR_FUNCTION_TEMPLATE,
	EERR_INVALID_BITFIELD,
	EERR_INVALID_CAPTURE,
	EERR_INVALID_PACK_USAGE,
	EERR_INVALID_FOLD_EXPRESSION,

	EERR_INVALID_CONSTEXPR,
	EERR_DOUBLE_FREE,
	EERR_UNBALANCED_HEAP_USE,

	ERRR_STACK_OVERFLOW,
	ERRR_INVALID_NUMBER,
	EERR_OVERLAPPING_DATA_SECTIONS,

	EERR_INVALID_PREPROCESSOR,

	EFATAL_GENERIC = 4000,
	EFATAL_OUT_OF_MEMORY,
	EFATAL_MACRO_EXPANSION_DEPTH,
};

class Errors
{
public:
	Errors(void);

	int		mErrorCount;

	void Error(const Location& loc, ErrorID eid, const char* msg, const Ident* info1, const Ident* info2 = nullptr);
	void Error(const Location& loc, ErrorID eid, const char* msg, const char* info1 = nullptr, const char* info2 = nullptr);
};
