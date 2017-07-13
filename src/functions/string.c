#include "string.h"

void ManualForStart(ARGCNV) {
    printf("Usage: %s [starting IP 1] [length 1] [starting IP 2] [length 2]...\n", argv[0]);
    printf("\n");
    printf("If no list of subnets is provided, the program will load static list of subnets from settings file.\n");
    printf("If static list is disabled, the program will broadcast to all detected local networks, using system IP adresses and subnet masks.\n");
    printf("\n");
    printf("Examples:\n");
    printf("\n");
    printf("    %s 192.168.1.0 100 192.168.2.0 255\n", argv[0]);
    printf("        program will broadcast to 192.168.1.0-192.168.1.100,192.168.2.0-192.168.2.255\n");
    printf("    %s\n", argv[0]);
    printf("        program will broadcast to detected local networks\n");
}

void ErrorInvalidArgAmount(ARGCNV) {
    printf("Invalid amount of arguments!\n");
    printf("Run \"%s -h\" to show a manual.\n", argv[0]);
}

void ErrorConfig(int errorId) {
    if (errorId == -1) {
        printf("settings.txt doesn't exist! Created one, please review and change it.\n");
    } else if (errorId == -2) {
        printf("Failed to process settings.txt. If it's corrupted, please rename it and run the program again.\n");
        printf("It will result in generating a new settings.txt.\n");
    } else if (errorId == -3) {
        printf("Failed to write to settings.txt!\n");
    } else if (errorId == -4) {
        printf("Failed to open settings.txt!\n");
    }
}