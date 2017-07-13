#pragma once

#include "macros.h"

// ================ C PREPROCESSOR STRUCT (CPPVARS) ==========================
// so far it only supports ZL_cstring and ZL_uint
// (but not their typedef aliases!)
// EXAMPLE
//   #define cppVars(o) \
//      o(ZL_cstring, VLC_EXE) \
//      o(ZL_uint, BITRATE) \
//      o(ZL_uint, RESOLUTION_H) \
//      o(ZL_uint, FPS) \
//      o(ZL_uint, REMOTE_CONTROL_PORT)

// ==================== GENERATE CPPVARS INSTANCE ============================
// #DEFINE BEFORE USAGE:
//   - SETTINGS_MAX_VAR_LEN [int]
// EXAMPLE:
//   CPPVARS_TOSTRUCT(cppVars) instanceName;
#define CPPVARS_TOSTRUCT_INTERNAL_ZL_cstring(x) char x[SETTINGS_MAX_VAR_LEN];
#define CPPVARS_TOSTRUCT_INTERNAL_ZL_uint(x) ZL_uint x;
#define CPPVARS_TOSTRUCT_INTERNAL(a, b) CPPVARS_TOSTRUCT_INTERNAL_ ## a (b)
#define CPPVARS_TOSTRUCT(cppvars) struct { cppvars(CPPVARS_TOSTRUCT_INTERNAL) }

// ================= LOAD FILE TO CPPVARS INSTANCE ===========================
// TODO: consider rewriting to functions
// #DEFINE BEFORE USAGE:
//   - SETTINGS_MAX_VAR_LEN [int]
//   - CPPVARS_LOAD_FILE [FILE*]
//   - CPPVARS_LOAD_DESTINATION [cppvars instance]
//   - CPPVARS_LOAD_ERROR_HANDLER() [macro not-;-terminated (f.e. `do {} while (0)`)]
//   - CPPVARS_LOAD_TMP_PREFIX [macro]
//   - CPPVARS_LOAD_IGNORE_CHARACTERS [int]
// EXAMPLE:
//   CPPVARS_LOAD(cppVars);
#define CPPVARS_LOAD_INTERNAL_BUF_LEN SETTINGS_MAX_VAR_LEN + CPPVARS_LOAD_IGNORE_CHARACTERS + 2
#define CPPVARS_LOAD_INTERNAL_ZL_cstring(x) \
    while (1) { \
        if (fgets(CPPVARS_LOAD_TMP_PREFIX ## _b, CPPVARS_LOAD_INTERNAL_BUF_LEN, CPPVARS_LOAD_FILE) == NULL) { \
            CPPVARS_LOAD_ERROR_HANDLER(); \
        } else { \
            CPPVARS_LOAD_TMP_PREFIX ## _len = strlen(CPPVARS_LOAD_TMP_PREFIX ## _b); \
            if (CPPVARS_LOAD_TMP_PREFIX ## _len <= CPPVARS_LOAD_IGNORE_CHARACTERS) continue; \
            if (CPPVARS_LOAD_TMP_PREFIX ## _len > SETTINGS_MAX_VAR_LEN) CPPVARS_LOAD_ERROR_HANDLER(); \
            memcpy(CPPVARS_LOAD_DESTINATION.x, CPPVARS_LOAD_TMP_PREFIX ## _b + CPPVARS_LOAD_IGNORE_CHARACTERS, CPPVARS_LOAD_TMP_PREFIX ## _len - (CPPVARS_LOAD_IGNORE_CHARACTERS + 2)); \
            break; \
        } \
    }
#define CPPVARS_LOAD_INTERNAL_ZL_uint(x) \
    while (1) { \
        if (fgets(CPPVARS_LOAD_TMP_PREFIX ## _b, CPPVARS_LOAD_INTERNAL_BUF_LEN, CPPVARS_LOAD_FILE) == NULL) { \
            CPPVARS_LOAD_ERROR_HANDLER(); \
        } else { \
            CPPVARS_LOAD_TMP_PREFIX ## _len = strlen(CPPVARS_LOAD_TMP_PREFIX ## _b); \
            if (CPPVARS_LOAD_TMP_PREFIX ## _len <= CPPVARS_LOAD_IGNORE_CHARACTERS) continue; \
            CPPVARS_LOAD_DESTINATION.x = strtoul(CPPVARS_LOAD_TMP_PREFIX ## _b + CPPVARS_LOAD_IGNORE_CHARACTERS, NULL, 10); \
            break; \
        } \
    }
#define CPPVARS_LOAD_INTERNAL(a, b) CPPVARS_LOAD_INTERNAL_ ## a (b)
#define CPPVARS_LOAD(cppvars) do { \
    size_t CPPVARS_LOAD_TMP_PREFIX ## _len; \
    char CPPVARS_LOAD_TMP_PREFIX ## _b[CPPVARS_LOAD_INTERNAL_BUF_LEN]; \
    cppvars(CPPVARS_LOAD_INTERNAL) \
    } while (0)

// ===================== PRINTF CPPVARS INSTANCE =============================
// #DEFINE BEFORE USAGE:
//   - CPPVARS_LDEBUG_SOURCE [cppvars instance]
// EXAMPLE:
//   CPPVARS_LDEBUG(cppVars);
#define CPPVARS_LDEBUG_INTERNAL_ZL_cstring(x) LDEBUG(#x ": %s\n", CPPVARS_LDEBUG_SOURCE.x);
#define CPPVARS_LDEBUG_INTERNAL_ZL_uint(x) LDEBUG(#x ": %u\n", CPPVARS_LDEBUG_SOURCE.x);
#define CPPVARS_LDEBUG_INTERNAL(a, b) CPPVARS_LDEBUG_INTERNAL_ ## a (b)
#define CPPVARS_LDEBUG(cppvars) do { cppvars(CPPVARS_LDEBUG_INTERNAL) } while (0)