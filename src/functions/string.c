#include "string.h"

void ManualForStart() {
    PRINT(
        "Usage: start [starting IP 1] [length 1] [starting IP 2] [length 2]...\n"
        "\n"
        "If no list of subnets is provided, the program will load static list of subnets from settings file.\n"
        "If static list is disabled, the program will broadcast to all detected local networks, using system IP adresses and subnet masks.\n"
        "\n"
        "Examples:\n"
        "\n"
        "    start 192.168.1.0 100 192.168.2.0 255\n"
        "        program will broadcast to 192.168.1.0-192.168.1.100,192.168.2.0-192.168.2.255\n"
        "    start\n"
        "        program will broadcast to detected local networks\n"
    );
}

void ManualForStop() {
    PRINT(
        "Usage: stop\n"
        "\n"
        "This program will stop hidden local VLC streamer.\n"
    );
}

void ErrorInvalidArgAmount(ARGCNV) {
    PRINT(
        "Invalid amount of arguments!\n"
        "Use -h parameter to show a manual.\n"
    );
}

void ErrorConfig(int errorId) {
    if (errorId == -1) {
        PRINT("settings.txt doesn't exist! Created one, please review and change it.\n");
    } else if (errorId == -2) {
        PRINT(
            "Failed to process settings.txt. If it's corrupted, please rename it and run the program again.\n"
            "It will result in generating a new settings.txt.\n"
        );
    } else if (errorId == -3) {
        PRINT("Failed to write to settings.txt!\n");
    } else if (errorId == -4) {
        PRINT("Failed to open settings.txt!\n");
    }
}