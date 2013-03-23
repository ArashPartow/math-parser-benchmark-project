/*
 * Copyright 2008  Veselin Georgiev,
 * anrieffNOSPAM @ mgail_DOT.com (convert to gmail)
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#ifndef __LIBCPUID_H__
#define __LIBCPUID_H__
/**
 * @File     libcpuid.h
 * @Author   Veselin Georgiev
 * @Date     Oct 2008
 * @Version  0.1.0
 *
 * Version history:
 *
 *  0.1.0 (2008-10-15): initial adaptation from wxfractgui sources
 */

/** @mainpage A simple libcpuid introduction
 *
 * LibCPUID provides CPU identification and access to the CPUID and RDTSC
 * instructions on the x86.
 * <p>
 * To execute CPUID, use \ref cpu_exec_cpuid <br>
 * To execute RDTSC, use \ref cpu_rdtsc <br>
 * To fetch the CPUID info needed for CPU identification, use
 *   \ref cpuid_get_raw_data <br>
 * To make sense of that data (decode, extract features), use \ref cpu_identify <br>
 * </p>
 */

/** @defgroup libcpuid LibCPUID
 @{ */

/* Include some integer type specifications: */
#include "libcpuid_types.h"

/* Some limits and other constants */
#include "libcpuid_constants.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief CPU vendor, as guessed from the Vendor String.
 */
typedef enum {
   VENDOR_INTEL = 0,  /*!< Intel CPU */
   VENDOR_AMD,        /*!< AMD CPU */
   VENDOR_CYRIX,      /*!< Cyrix CPU */
   VENDOR_NEXGEN,     /*!< NexGen CPU */
   VENDOR_TRANSMETA,  /*!< Transmeta CPU */
   VENDOR_UMC,        /*!< x86 CPU by UMC */
   VENDOR_CENTAUR,    /*!< x86 CPU by IDT */
   VENDOR_RISE,       /*!< x86 CPU by Rise Technology */
   VENDOR_SIS,        /*!< x86 CPU by SiS */
   VENDOR_NSC,        /*!< x86 CPU by National Semiconductor */

   NUM_CPU_VENDORS,   /*!< Valid CPU vendor ids: 0..NUM_CPU_VENDORS - 1 */
   VENDOR_UNKNOWN = -1,
} cpu_vendor_t;
#define NUM_CPU_VENDORS NUM_CPU_VENDORS

/**
 * @brief Contains just the raw CPUID data.
 *
 * This contains only the most basic CPU data, required to do identification
 * and feature recognition. Every processor should be identifiable using this
 * data only.
 */
struct cpu_raw_data_t {
   /** contains results of CPUID for eax = 0, 1, ...*/
   uint32_t basic_cpuid[MAX_CPUID_LEVEL][4];

   /** contains results of CPUID for eax = 0x80000000, 0x80000001, ...*/
   uint32_t ext_cpuid[MAX_EXT_CPUID_LEVEL][4];

   /** when the CPU is intel and it supports deterministic cache
       information: this contains the results of CPUID for eax = 4
       and ecx = 0, 1, ... */
   uint32_t intel_fn4[MAX_INTELFN4_LEVEL][4];
};

/**
 * @brief This contains the recognized CPU features/info
 */
struct cpu_id_t {
   /** contains the CPU vendor string, e.g. "GenuineIntel" */
   char vendor_str[VENDOR_STR_MAX];

   /** contains the brand string, e.g. "Intel(R) Xeon(TM) CPU 2.40GHz" */
   char brand_str[BRAND_STR_MAX];

   /** contains the recognized CPU vendor */
   cpu_vendor_t vendor;

   /**
    * contain CPU flags. Used to test for features. See
    * the CPU_FEATURE_* macros below. @see Features
    */
   uint8_t flags[CPU_FLAGS_MAX];

   /** CPU family */
   int32_t family;

   /** CPU model */
   int32_t model;

   /** CPU stepping */
   int32_t stepping;

   /** CPU extended family */
   int32_t ext_family;

   /** CPU extended model */
   int32_t ext_model;

   /** Number of CPU cores on the current processor */
   int32_t num_cores;

   /**
    * Number of logical processors on the current processor.
    * Could be more than the number of physical cores,
    * e.g. when the processor has HyperThreading.
    */
   int32_t num_logical_cpus;

   /**
    * The total number of logical processors.
    *
    * This is num_logical_cpus * {total physical processors in the system}
    *
    * If you're writing a multithreaded program and you want to run it on
    * all CPUs, this is the number of threads you need.
    */
   int32_t total_logical_cpus;

   /**
    * L1 data cache size in KB. Could be zero, if the CPU lacks cache.
    * If the size cannot be determined, it will be -1.
    */
   int32_t l1_data_cache;

   /**
    * L1 instruction cache size in KB. Could be zero, if the CPU lacks
    * cache. If the size cannot be determined, it will be -1.
    * @note On some Intel CPUs, whose instruction cache is in fact
    * a trace cache, the size will be expressed in K uOps.
    */
   int32_t l1_instruction_cache;

   /**
    * L2 cache size in KB. Could be zero, if the CPU lacks L2 cache.
    * If the size of the cache could not be determined, it will be -1
    */
   int32_t l2_cache;

   /** L3 cache size in KB. Zero on most systems */
   int32_t l3_cache;

   /** Cache associativity for the L1 data cache. -1 if undetermined */
   int32_t l1_assoc;

   /** Cache associativity for the L2 cache. -1 if undetermined */
   int32_t l2_assoc;

   /** Cache associativity for the L3 cache. -1 if undetermined */
   int32_t l3_assoc;

   /** Cache-line size for L1 data cache. -1 if undetermined */
   int32_t l1_cacheline;

   /** Cache-line size for L2 cache. -1 if undetermined */
   int32_t l2_cacheline;

   /** Cache-line size for L3 cache. -1 if undetermined */
   int32_t l3_cacheline;

   /**
    * The brief and human-friendly CPU codename, which was recognized.<br>
    * Examples:
    * @code
    * +--------+--------+-------+-------+-------+---------------------------------------+-----------------------+
    * | Vendor | Family | Model | Step. | Cache |       Brand String                    | cpu_id_t.cpu_codename |
    * +--------+--------+-------+-------+-------+---------------------------------------+-----------------------+
    * | AMD    |      6 |     8 |     0 |   256 | (not available - will be ignored)     | "K6-2"                |
    * | Intel  |     15 |     2 |     5 |   512 | "Intel(R) Xeon(TM) CPU 2.40GHz"       | "Xeon (Prestonia)"    |
    * | Intel  |      6 |    15 |    11 |  4096 | "Intel(R) Core(TM)2 Duo CPU E6550..." | "Conroe (Core 2 Duo)" |
    * | AMD    |     15 |    35 |     2 |  1024 | "Dual Core AMD Opteron(tm) Proces..." | "Opteron (Dual Core)" |
    * +--------+--------+-------+-------+-------+---------------------------------------+-----------------------+
    * @endcode
    */
   char cpu_codename[64];
};

/**
 * @brief CPU feature identifiers
 *
 * Usage:
 * @code
 * ...
 * struct cpu_raw_data_t raw;
 * struct cpu_id_t id;
 * if (cpuid_get_raw_data(&raw) == 0 && cpu_identify(&raw, &id) == 0) {
 *     if (id.flags[CPU_FEATURE_SSE2]) {
 *         // The CPU has SSE2...
 *         ...
 *     } else {
 *         // no SSE2
 *     }
 * } else {
 *   // processor cannot be determined.
 * }
 * @endcode
 */
typedef enum {
   CPU_FEATURE_FPU = 0, /*!< Floating point unit */
   CPU_FEATURE_VME,  /*!< Virtual mode extension */
   CPU_FEATURE_DE,      /*!< Debugging extension */
   CPU_FEATURE_PSE,  /*!< Page size extension */
   CPU_FEATURE_TSC,  /*!< Time-stamp counter */
   CPU_FEATURE_MSR,  /*!< Model-specific regsisters, RDMSR/WRMSR supported */
   CPU_FEATURE_PAE,  /*!< Physical address extension */
   CPU_FEATURE_MCE,  /*!< Machine check exception */
   CPU_FEATURE_CX8,  /*!< CMPXCHG8B instruction supported */
   CPU_FEATURE_APIC, /*!< APIC support */
   CPU_FEATURE_MTRR, /*!< Memory type range registers */
   CPU_FEATURE_SEP,  /*!< SYSENTER / SYSEXIT instructions supported */
   CPU_FEATURE_PGE,  /*!< Page global enable */
   CPU_FEATURE_MCA,  /*!< Machine check architecture */
   CPU_FEATURE_CMOV, /*!< CMOVxx instructions supported */
   CPU_FEATURE_PAT,  /*!< Page attribute table */
   CPU_FEATURE_PSE36,   /*!< 36-bit page address extension */
   CPU_FEATURE_PN,      /*!< Processor serial # implemented (Intel P3 only) */
   CPU_FEATURE_CLFLUSH, /*!< CLFLUSH instruction supported */
   CPU_FEATURE_DTS,  /*!< Debug store supported */
   CPU_FEATURE_ACPI, /*!< ACPI support (power states) */
   CPU_FEATURE_MMX,  /*!< MMX instruction set supported */
   CPU_FEATURE_FXSR, /*!< FXSAVE / FXRSTOR supported */
   CPU_FEATURE_SSE,  /*!< Streaming-SIMD Extensions (SSE) supported */
   CPU_FEATURE_SSE2, /*!< SSE2 instructions supported */
   CPU_FEATURE_SS,      /*!< Self-snoop */
   CPU_FEATURE_HT,      /*!< Hyper-threading supported (but might be disabled) */
   CPU_FEATURE_TM,      /*!< Thermal monitor */
   CPU_FEATURE_IA64, /*!< IA64 supported (Itanium only) */
   CPU_FEATURE_PBE,  /*!< Pending-break enable */
   CPU_FEATURE_PNI,  /*!< PNI (SSE3) instructions supported */
   CPU_FEATURE_PCLMUL,  /*!< PCLMULQDQ instruction supported */
   CPU_FEATURE_DTS64,   /*!< 64-bit Debug store supported */
   CPU_FEATURE_MONITOR, /*!< MONITOR / MWAIT supported */
   CPU_FEATURE_DS_CPL,  /*!< CPL Qualified Debug Store */
   CPU_FEATURE_VMX,  /*!< Virtualization technology supported */
   CPU_FEATURE_SMX,  /*!< Safer mode exceptions */
   CPU_FEATURE_EST,  /*!< Enhanced SpeedStep */
   CPU_FEATURE_TM2,  /*!< Thermal monitor 2 */
   CPU_FEATURE_SSSE3,   /*!< SSSE3 instructionss supported (this is different from SSE3!) */
   CPU_FEATURE_CID,  /*!< Context ID supported */
   CPU_FEATURE_CX16, /*!< CMPXCHG16B instruction supported */
   CPU_FEATURE_XTPR, /*!< Send Task Priority Messages disable */
   CPU_FEATURE_PDCM, /*!< Performance capabilities MSR supported */
   CPU_FEATURE_DCA,  /*!< Direct cache access supported */
   CPU_FEATURE_SSE4_1,  /*!< SSE 4.1 instructions supported */
   CPU_FEATURE_SSE4_2,  /*!< SSE 4.2 instructions supported */
   CPU_FEATURE_SYSCALL, /*!< SYSCALL / SYSRET instructions supported */
   CPU_FEATURE_XD,      /*!< Execute disable bit supported */
   CPU_FEATURE_MOVBE,   /*!< MOVBE instruction supported */
   CPU_FEATURE_POPCNT,  /*!< POPCNT instruction supported */
   CPU_FEATURE_AES,  /*!< AES* instructions supported */
   CPU_FEATURE_XSAVE,   /*!< XSAVE/XRSTOR/etc instructions supported */
   CPU_FEATURE_OSXSAVE, /*!< non-privileged copy of OSXSAVE supported */
   CPU_FEATURE_AVX,  /*!< Advanced vector extensions supported */
   CPU_FEATURE_MMXEXT,  /*!< AMD MMX-extended instructions supported */
   CPU_FEATURE_3DNOW,   /*!< AMD 3DNow! instructions supported */
   CPU_FEATURE_3DNOWEXT,   /*!< AMD 3DNow! extended instructions supported */
   CPU_FEATURE_NX,      /*!< No-execute bit supported */
   CPU_FEATURE_FXSR_OPT,   /*!< FFXSR: FXSAVE and FXRSTOR optimizations */
   CPU_FEATURE_RDTSCP,  /*!< RDTSCP instruction supported (AMD-only) */
   CPU_FEATURE_LM,      /*!< Long mode (x86_64/EM64T) supported */
   CPU_FEATURE_LAHF_LM, /*!< LAHF/SAHF supported in 64-bit mode */
   CPU_FEATURE_CMP_LEGACY, /*!< core multi-processing legacy mode */
   CPU_FEATURE_SVM,  /*!< AMD Secure virtual machine */
   CPU_FEATURE_ABM,  /*!< LZCNT instruction support */
   CPU_FEATURE_MISALIGNSSE,/*!< Misaligned SSE supported */
   CPU_FEATURE_SSE4A,   /*!< SSE 4a from AMD */
   CPU_FEATURE_3DNOWPREFETCH, /*!< PREFETCH/PREFETCHW support */
   CPU_FEATURE_OSVW, /*!< OS Visible Workaround (AMD) */
   CPU_FEATURE_IBS,  /*!< Instruction-based sampling */
   CPU_FEATURE_SSE5, /*!< SSE 5 instructions supported */
   CPU_FEATURE_SKINIT,  /*!< SKINIT / STGI supported */
   CPU_FEATURE_WDT,  /*!< Watchdog timer support */
   CPU_FEATURE_TS,      /*!< Temperature sensor */
   CPU_FEATURE_FID,  /*!< Frequency ID control */
   CPU_FEATURE_VID,  /*!< Voltage ID control */
   CPU_FEATURE_TTP,  /*!< THERMTRIP */
   CPU_FEATURE_TM_AMD,  /*!< AMD-specified hardware thermal control */
   CPU_FEATURE_STC,  /*!< Software thermal control */
   CPU_FEATURE_100MHZSTEPS,/*!< 100 MHz multiplier control */
   CPU_FEATURE_HWPSTATE,   /*!< Hardware P-state control */
   CPU_FEATURE_CONSTANT_TSC,  /*!< TSC ticks at constant rate */
   /* termination: */
   NUM_CPU_FEATURES,
} cpu_feature_t;

/**
 * @brief Describes common library error codes
 */
typedef enum {
   ERR_OK       =  0,   /*!< "No error" */
   ERR_NO_CPUID = -1,   /*!< "CPUID instruction is not supported" */
   ERR_NO_RDTSC = -2,   /*!< "RDTSC instruction is not supported" */
   ERR_NO_MEM   = -3,   /*!< "Memory allocation failed" */
   ERR_OPEN     = -4,   /*!< "File open operation failed" */
   ERR_BADFMT   = -5,   /*!< "Bad file format" */
   ERR_NOT_IMP  = -6,   /*!< "Not implemented" */
   ERR_CPU_UNKN = -7,   /*!< "Unsupported processor" */
} cpu_error_t;

/**
 * @brief Internal structure, used in cpu_tsc_mark, cpu_tsc_unmark and
 *        cpu_clock_by_mark
 */
struct cpu_mark_t {
   uint64_t tsc;     /*!< Time-stamp from RDTSC */
   uint64_t sys_clock;  /*!< In microsecond resolution */
};

/**
 * @brief Checks if the CPUID instruction is supported
 * @retval 1 if CPUID is present
 * @retval 0 the CPU doesn't have CPUID.
 */
int cpuid_present(void);

/**
 * @brief Executes the CPUID instruction
 * @param eax - the value of the EAX register when executing CPUID
 * @param regs - the results will be stored here. regs[0] = EAX, regs[1] = EBX, ...
 * @note CPUID will be executed with EAX set to the given value and EBX, ECX,
 *       EDX set to zero.
 */
void cpu_exec_cpuid(uint32_t eax, uint32_t* regs);

/**
 * @brief Executes the CPUID instruction with the given input registers
 * @note This is just a bit more generic version of cpu_exec_cpuid - it allows
 *       you to control all the registers.
 * @param regs - Input/output. Prior to executing CPUID, EAX, EBX, ECX and
 *               EDX will be set to regs[0], regs[1], regs[2] and regs[3].
 *               After CPUID, this array will contain the results.
 */
void cpu_exec_cpuid_ext(uint32_t* regs);

/**
 * @brief Obtains the raw CPUID data from the current CPU
 * @param data - a pointer to cpu_raw_data_t structure
 * @returns zero if successful, and some negative number on error.
 *          The error message can be obtained by calling \ref cpuid_error.
 *          @see cpu_error_t
 */
int cpuid_get_raw_data(struct cpu_raw_data_t* data);

/**
 * @brief Writes the raw CPUID data to a text file
 * @param data - a pointer to cpu_raw_data_t structure
 * @param filename - the path of the file, where the serialized data should be
 *                   written. If empty, stdout will be used.
 * @note This is intended primarily for debugging. On some processor, which is
 *       not currently supported or not completely recognized by cpu_identify,
 *       one can still successfully get the raw data and write it to a file.
 *       libcpuid developers can later import this file and debug the detection
 *       code as if running on the actual hardware.
 *       The file is simple text format of "something=value" pairs. Version info
 *       is also written, but the format is not intended to be neither backward-
 *       nor forward compatible.
 * @returns zero if successful, and some negative number on error.
 *          The error message can be obtained by calling \ref cpuid_error.
 *          @see cpu_error_t
 */
int cpuid_serialize_raw_data(struct cpu_raw_data_t* data, const char* filename);

/**
 * @brief Reads raw CPUID data from file
 * @param data - a pointer to cpu_raw_data_t structure. The deserialized data will
 *               be written here.
 * @param filename - the path of the file, containing the serialized raw data.
 *                   If empty, stdin will be used.
 * @note This function may fail, if the file is created by different version of
 *       the library. Also, see the notes on cpuid_serialize_raw_data.
 * @returns zero if successful, and some negative number on error.
 *          The error message can be obtained by calling \ref cpuid_error.
 *          @see cpu_error_t
*/
int cpuid_deserialize_raw_data(struct cpu_raw_data_t* data, const char* filename);

/**
 * @brief Identifies the CPU
 * @param raw - Input - a pointer to the raw CPUID data, which is obtained
 *              either by cpuid_get_raw_data or cpuid_deserialize_raw_data.
 *              Can also be NULL, in which case the functions calls
 *              cpuid_get_raw_data itself.
 * @param data - Output - the decoded CPU features/info is written here.
 * @note The function will not fail, even if some of the information
 *       cannot be obtained. Even when the CPU is new and thus unknown to
 *       libcpuid, some generic info, such as "AMD K9 family CPU" will be
 *       written to data.cpu_codename, and most other things, such as the
 *       CPU flags, cache sizes, etc. should be detected correctly anyway.
 *       However, the function CAN fail, if the CPU is completely alien to
 *       libcpuid.
 * @note While cpu_identify() and cpuid_get_raw_data() are fast for most
 *       purposes, running them several thousand times per second can hamper
 *       performance significantly. Specifically, avoid writing "cpu feature
 *       checker" wrapping function, which calls cpu_identify and returns the
 *       value of some flag, if that function is going to be called frequently.
 * @returns zero if successful, and some negative number on error.
 *          The error message can be obtained by calling \ref cpuid_error.
 *          @see cpu_error_t
 */
int cpu_identify(struct cpu_raw_data_t* raw, struct cpu_id_t* data);

/**
 * @brief Returns the short textual representation of a CPU flag
 * @param feature - the feature, whose textual representation is wanted.
 * @returns a constant string like "fpu", "tsc", "sse2", etc.
 * @note the names of the returned flags are compatible with those from
 *       /proc/cpuinfo in Linux, with the exception of `tm_amd'
 */
const char* cpu_feature_str(cpu_feature_t feature);

/**
 * @brief Returns textual description of the last error
 *
 * libcpuid stores an `errno'-style error status, whose description
 * can be obtained with this function.
 * @note This function is not thread-safe
 * @see cpu_error_t
 */
const char* cpuid_error(void);

/**
 * @brief Executes RDTSC
 *
 * The RDTSC (ReaD Time Stamp Counter) instruction gives access to an
 * internal 64-bit counter, which usually increments at each clock cycle.
 * This can be used for various timing routines, and as a very precise
 * clock source. It is set to zero on system startup. Beware that may not
 * increment at the same frequency as the CPU. Consecutive calls of RDTSC
 * are, however, guaranteed to return monotonically-increasing values.
 *
 * @param result - a pointer to a 64-bit unsigned integer, where the TSC value
 *                 will be stored
 *
 * @note  If 100% compatibility is a concern, you must first check if the
 * RDTSC instruction is present (if it is not, your program will crash
 * with "invalid opcode" exception). Only some very old processors (i486,
 * early AMD K5 and some Cyrix CPUs) lack that instruction - they should
 * have become exceedingly rare these days. To verify RDTSC presence,
 * run cpu_identify() and check flags[CPU_FEATURE_TSC].
 *
 * @note The monotonically increasing nature of the TSC may be violated
 * on SMP systems, if their TSC clocks run at different rate. If the OS
 * doesn't account for that, the TSC drift may become arbitrary large.
 */
void cpu_rdtsc(uint64_t* result);

/**
 * @brief Store TSC and timing info
 *
 * This function stores the current TSC value and current
 * time info from a precise OS-specific clock source in the cpu_mark_t
 * structure. The sys_clock field contains time with microsecond resolution.
 * The values can later be used to measure time intervals, number of clocks,
 * FPU frequency, etc.
 * @see cpu_rdtsc
 *
 * @param mark [out] - a pointer to a cpu_mark_t structure
 */
void cpu_tsc_mark(struct cpu_mark_t* mark);

/**
 * @brief Calculate TSC and timing difference
 *
 * @param mark - input/output: a pointer to a cpu_mark_t sturcture, which has
 *               already been initialized by cpu_tsc_mark. The difference in
 *               TSC and time will be written here.
 *
 * This function calculates the TSC and time difference, by obtaining the
 * current TSC and timing values and subtracting the contents of the `mark'
 * structure from them. Results are written in the same structure.
 *
 * Example:
 * @code
 * ...
 * struct cpu_mark_t mark;
 * cpu_tsc_mark(&mark);
 * foo();
 * cpu_tsc_unmark(&mark);
 * printf("Foo finished. Executed in %llu cycles and %llu usecs\n",
 *        mark.tsc, mark.sys_clock);
 * ...
 * @endcode
 */
void cpu_tsc_unmark(struct cpu_mark_t* mark);

/**
 * @brief Calculates the CPU clock
 *
 * @param mark - pointer to a cpu_mark_t structure, which has been initialized
 *   with cpu_tsc_mark and later `stopped' with cpu_tsc_unmark.
 *
 * @note For reliable results, the marked time interval should be at least about
 * 10 ms.
 *
 * @returns the CPU clock frequency, in MHz. Due to measurement error, it will
 * differ from the true value in a few least-significant bits. Accuracy depends
 * on the timing interval - the more, the better. If the timing interval is
 * insufficient, the result is -1. Also, see the comment on cpu_clock_measure
 * for additional issues and pitfalls in using RDTSC for CPU frequency
 * measurements.
 */
int cpu_clock_by_mark(struct cpu_mark_t* mark);

/**
 * @brief Returns the CPU clock, as reported by the OS
 *
 * This function uses OS-specific functions to obtain the CPU clock. It may
 * differ from the true clock for several reasons:<br><br>
 *
 * i) The CPU might be in some power saving state, while the OS reports its
 *    full-power frequency, or vice-versa.<br>
 * ii) In some cases you can raise or lower the CPU frequency with overclocking
 *     utilities and the OS will not notice.
 *
 * @returns the CPU clock frequency in MHz. If the OS is not (yet) supported
 * or lacks the necessary reporting machinery, the return value is -1
 */
int cpu_clock_by_os(void);

/**
 * @brief Measure the CPU clock frequency
 *
 * @param millis - How much time to waste in the busy-wait cycle. In millisecs.
 *                 Useful values 10 - 1000
 * @param quad_check - Do a more thorough measurement if nonzero
 *                     (see the explanation).
 *
 * The function performs a busy-wait cycle for the given time and calculates
 * the CPU frequency by the difference of the TSC values. The accuracy of the
 * calculation depends on the length of the busy-wait cycle: more is better,
 * but 100ms should be enough for most purposes.
 *
 * While this will calculate the CPU frequency correctly in most cases, there are
 * several reasons why it might be incorrect:<br>
 *
 * i) RDTSC doesn't guarantee it will run at the same clock as the CPU.
 *    Apparently there aren't CPUs at the moment, but still, there's no
 *    guarantee.<br>
 * ii) The CPU might be in a low-frequency power saving mode, and the CPU
 *     might be switched to higher frequency at any time. If this happens
 *     during the measurement, the result can be anywhere between the
 *     low and high frequencies. Also, if you're interested in the
 *     high frequency value only, this function might return the low one
 *     instead.<br>
 * iii) On SMP systems exhibiting TSC drift (see \ref cpu_rdtsc)
 *
 * the quad_check option will run four consecutive measurements and
 * then return the average of the two most-consistent results. The total
 * runtime of the function will still be `millis' - consider using
 * a bit more time for the timing interval.
 *
 * Finally, for benchmarking / CPU intensive applications, the best strategy is
 * to use the cpu_tsc_mark() / cpu_tsc_unmark() / cpu_clock_by_mark() method.
 * Begin by mark()-ing about one second after application startup (allowing the
 * power-saving manager to kick in and rise the frequency during that time),
 * then unmark() just before application finishing. The result will most
 * acurately represent at what frequency your app was running.
 *
 * @returns the CPU clock frequency in MHz (within some measurement error
 * margin). If RDTSC is not supported, the result is -1.
 */
int cpu_clock_measure(int millis, int quad_check);

/**
 * @brief Get the CPU clock frequency (all-in-one method)
 *
 * This is an all-in-one method for getting the CPU clock frequency.
 * It tries to use the OS for that. If the OS doesn't have this info, it
 * uses cpu_clock_measure with 200ms time interval and quadruple checking.
 *
 * @returns the CPU clock frequency in MHz. If every possible method fails,
 * the result is -1.
 */
int cpu_clock(void);

/**
 * @brief Returns the libcpuid version
 *
 * @returns the string representation of the libcpuid version, like "0.1.0"
 */
const char* cpuid_lib_version(void);

typedef void (*libcpuid_warn_fn_t) (const char *msg);
/**
 * @brief Sets the warning print function
 *
 * In some cases, the internal libcpuid machinery would like to emit useful
 * debug warnings. By default, these warnings are written to stderr. However,
 * you can set a custom function that will receive those warnings.
 *
 * @param warn_fun - the warning function you want to set. If NULL, warnings
 *                   are disabled. The function takes const char* argument.
 *
 * @returns the current warning function. You can use the return value to
 * keep the previous warning function and restore it at your discretion.
 */
libcpuid_warn_fn_t cpuid_set_warn_function(libcpuid_warn_fn_t warn_fun);

/**
 * @brief Sets the verbosiness level
 *
 * When the verbosiness level is above zero, some functions might print
 * diagnostic information about what are they doing. The higher the level is,
 * the more detail is printed. Level zero is guaranteed to omit all such
 * output. The output is written using the same machinery as the warnings,
 * @see cpuid_set_warn_function()
 *
 * @param level the desired verbosiness level. Useful values 0..2 inclusive
 */
void cpuid_set_verbosiness_level(int level);


/**
 * @brief a structure that holds a list of processor names
 */
struct cpu_list_t {
   /** Number of entries in the list */
   int num_entries;
   /** Pointers to names. There will be num_entries of them */
   char **names;
};

/**
 * @brief Gets a list of all known CPU names from a specific vendor.
 *
 * This function compiles a list of all known CPU (code)names
 * (i.e. the possible values of cpu_id_t::cpu_codename) for the given vendor.
 *
 * There are about 100 entries for Intel and AMD, and a few for the other
 * vendors. The list is written out in approximate chronological introduction
 * order of the parts.
 *
 * @param vendor the vendor to be queried
 * @param list [out] the resulting list will be written here.
 * NOTE: As the memory is dynamically allocated, be sure to call
 *       cpuid_free_cpu_list() after you're done with the data
 * @see cpu_list_t
 */
void cpuid_get_cpu_list(cpu_vendor_t vendor, struct cpu_list_t* list);

/**
 * @brief Frees a CPU list
 *
 * This function deletes all the memory associated with a CPU list, as obtained
 * by cpuid_get_cpu_list()
 *
 * @param list - the list to be free()'d.
 */
void cpuid_free_cpu_list(struct cpu_list_t* list);

#ifdef __cplusplus
}; /* extern "C" */
#endif


/** @} */

#endif /* __LIBCPUID_H__ */
