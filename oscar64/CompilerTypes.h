#pragma once

#include "MachineTypes.h"

static const uint64 COPT_OPTIMIZE_BASIC = 1ULL << 0;
static const uint64 COPT_OPTIMIZE_INLINE = 1ULL << 1;
static const uint64 COPT_OPTIMIZE_ASSEMBLER = 1ULL << 2;

static const uint64 COPT_OPTIMIZE_AUTO_INLINE = 1ULL << 4;
static const uint64 COPT_OPTIMIZE_AUTO_INLINE_ALL = 1ULL << 5;
static const uint64 COPT_OPTIMIZE_AUTO_UNROLL = 1ULL << 6;
static const uint64 COPT_OPTIMIZE_CONST_EXPRESSIONS = 1ULL << 7;
static const uint64 COPT_OPTIMIZE_AUTO_ZEROPAGE = 1ULL << 8;
static const uint64 COPT_OPTIMIZE_CONST_PARAMS = 1ULL << 9;
static const uint64 COPT_OPTIMIZE_MERGE_CALLS = 1ULL << 10;
static const uint64 COPT_OPTIMIZE_GLOBAL = 1ULL << 11;

static const uint64 COPT_OPTIMIZE_CODE_SIZE = 1ULL << 16;
static const uint64 COPT_NATIVE = 1ULL << 17;
static const uint64 COPT_EXTENDED_ZERO_PAGE = 1ULL << 20;

static const uint64 COPT_TARGET_PRG = 1ULL << 32;
static const uint64 COPT_TARGET_CRT8 = 1ULL << 33;
static const uint64 COPT_TARGET_CRT16 = 1ULL << 34;
static const uint64 COPT_TARGET_CRT_EASYFLASH = 1ULL << 35;

static const uint64 COPT_TARGET_CRT = COPT_TARGET_CRT8 | COPT_TARGET_CRT16 | COPT_TARGET_CRT_EASYFLASH;

static const uint64 COPT_TARGET_COPY = 1ULL << 36;
static const uint64 COPT_TARGET_BIN = 1ULL << 37;
static const uint64 COPT_TARGET_LZO = 1ULL << 38;
static const uint64 COPT_TARGET_NES = 1ULL << 39;

static const uint64 COPT_VERBOSE = 1ULL << 48;
static const uint64 COPT_VERBOSE2 = 1ULL << 49;
static const uint64 COPT_VERBOSE3 = 1ULL << 50;

static const uint64 COPT_DEBUGINFO = 1ULL << 51;

static const uint64 COPT_CPLUSPLUS = 1ULL << 52;
static const uint64 COPT_PETSCII = 1ULL << 53;
static const uint64 COPT_ERROR_FILES = 1ULL << 54;

static const uint64 COPT_PROFILEINFO = 1ULL << 55;
static const uint64 COPT_STRICT = 1ULL << 56;



static const uint64 COPT_DEFAULT = COPT_OPTIMIZE_BASIC | COPT_OPTIMIZE_INLINE | COPT_OPTIMIZE_CONST_EXPRESSIONS;

static const uint64 COPT_OPTIMIZE_DEFAULT = COPT_OPTIMIZE_BASIC | COPT_OPTIMIZE_INLINE | COPT_OPTIMIZE_CONST_EXPRESSIONS;

static const uint64 COPT_OPTIMIZE_SIZE = COPT_OPTIMIZE_BASIC | COPT_OPTIMIZE_INLINE | COPT_OPTIMIZE_AUTO_INLINE | COPT_OPTIMIZE_CONST_EXPRESSIONS | COPT_OPTIMIZE_CODE_SIZE | COPT_OPTIMIZE_CONST_PARAMS | COPT_OPTIMIZE_MERGE_CALLS | COPT_OPTIMIZE_GLOBAL;

static const uint64 COPT_OPTIMIZE_SPEED = COPT_OPTIMIZE_BASIC | COPT_OPTIMIZE_INLINE | COPT_OPTIMIZE_AUTO_INLINE | COPT_OPTIMIZE_AUTO_UNROLL | COPT_OPTIMIZE_CONST_EXPRESSIONS | COPT_OPTIMIZE_ASSEMBLER | COPT_OPTIMIZE_CONST_PARAMS | COPT_OPTIMIZE_MERGE_CALLS | COPT_OPTIMIZE_GLOBAL;

static const uint64 COPT_OPTIMIZE_ALL = COPT_OPTIMIZE_BASIC | COPT_OPTIMIZE_INLINE | COPT_OPTIMIZE_AUTO_INLINE | COPT_OPTIMIZE_AUTO_INLINE_ALL | COPT_OPTIMIZE_AUTO_UNROLL | COPT_OPTIMIZE_CONST_EXPRESSIONS | COPT_OPTIMIZE_ASSEMBLER | COPT_OPTIMIZE_AUTO_ZEROPAGE | COPT_OPTIMIZE_CONST_PARAMS | COPT_OPTIMIZE_MERGE_CALLS | COPT_OPTIMIZE_GLOBAL;

enum TargetMachine
{
	TMACH_C64,
	TMACH_VIC20,
	TMACH_VIC20_3K,
	TMACH_VIC20_8K,
	TMACH_VIC20_16K,
	TMACH_VIC20_24K,
	TMACH_C128,
	TMACH_C128B,
	TMACH_C128E,
	TMACH_PET_8K,
	TMACH_PET_16K,
	TMACH_PET_32K,
	TMACH_PLUS4,
	TMACH_NES,
	TMACH_NES_NROM_H,
	TMACH_NES_NROM_V,
	TMACH_NES_MMC1,
	TMACH_NES_MMC3,
	TMACH_ATARI,
	TMACH_X16
};


