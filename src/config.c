#include "config.h"

const char * SETTINGS_FILE = "settings.txt";

void GenerateNewConfig() {
    FILE* f = fopen(SETTINGS_FILE, "wb");
    if (f == NULL) {
        ErrorConfig(-3);
        exit(1);
    }
    fprintf(f, "%s", DEFAULT_CONFIG);
    fclose(f);
}

void LoadConfig() {
    if (!FileExists(SETTINGS_FILE)) {
        GenerateNewConfig();
        ErrorConfig(-1);
        exit(1);
    }
    FILE* f = fopen(SETTINGS_FILE, "rb");
    if (f == NULL) {
        ErrorConfig(-4);
        exit(1);
    }

    #define CPPVARS_LOAD_FILE f
    #define CPPVARS_LOAD_DESTINATION PROGRAM_CONFIG
    #define CPPVARS_LOAD_ERROR_HANDLER() do { ErrorConfig(-2); exit(1); } while (0)
    #define CPPVARS_LOAD_IGNORE_CHARACTERS 64
    #define CPPVARS_LOAD_TMP_PREFIX __
    CPPVARS_LOAD(CFGVARS);

    #define CPPVARS_LDEBUG_SOURCE PROGRAM_CONFIG
    CPPVARS_LDEBUG(CFGVARS);

    fclose(f);
}

void VerifyConfig() {
    // TODO implement if needed
}

void Configure() {
    LoadConfig();
    VerifyConfig();
}