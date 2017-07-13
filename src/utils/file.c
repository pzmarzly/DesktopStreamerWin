#include "file.h"

bool FileExists(ZL_cstring fileName) {
    return GetFileAttributes(fileName) != 0xFFFFFFFF;
}