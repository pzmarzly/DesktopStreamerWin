#include "start.h"

void PingTheReceiverAllNetworks() {
    TryBroadcastAllNetworks(
        PROGRAM_CONFIG.REMOTE_CONTROL_PORT,
        PROGRAM_CONFIG.REMOTE_PASSWORD,
        PROGRAM_CONFIG.MAX_PING
    );
}

void PingTheReceiverSingleNetwork(ZL_cstring start, ZL_ulong length) {
    ZL_ulong startIP = inet_addr(start);
    if (   startIP != ULONG_MAX
        && startIP != 0) {
            TryBroadcastNetwork(
                startIP,
                length,
                PROGRAM_CONFIG.REMOTE_CONTROL_PORT,
                PROGRAM_CONFIG.REMOTE_PASSWORD,
                PROGRAM_CONFIG.MAX_PING
            );
        }
}

void PingTheReceiver(ARGCNV) {
    if (argc == 1) {
        PingTheReceiverAllNetworks();
    } else {
        int i;
        for (i = 1; i < argc; i += 2) {
            PingTheReceiverSingleNetwork(argv[i], atoi(argv[i + 1]));
        }
    }
}

void RunProcess() {
    ITOA_R(PROGRAM_CONFIG.LOCAL_CONTROL_PORT, program_config_local_control_port);
    ITOA_R(PROGRAM_CONFIG.BITRATE, program_config_bitrate);
    ITOA_R(PROGRAM_CONFIG.FPS, program_config_fps);
    ITOA_R(PROGRAM_CONFIG.RESOLUTION_H, program_config_resolution_h);
    ITOA_R(PROGRAM_CONFIG.VIDEO_PORT, program_config_video_port);

    char param_local_control[32];
    strcpy(param_local_control, "127.0.0.1:");
    strcat(param_local_control, program_config_local_control_port);

    char param_sout[1024];
    strcpy(param_sout, "\"#transcode{vcodec=MJPG,vb=");
    strcat(param_sout, program_config_bitrate);
    strcat(param_sout, ",fps=");
    strcat(param_sout, program_config_fps);
    strcat(param_sout, ",scale=Auto,height=");
    strcat(param_sout, program_config_resolution_h);
    strcat(param_sout, ",acodec=mpga,ab=64,channels=2,samplerate=8000}:http{dst=:");
    strcat(param_sout, program_config_video_port);
    strcat(param_sout, "/streamer.avi}\"");

    int result = (int) _spawnl(
        _P_NOWAIT,
        PROGRAM_CONFIG.VLC_EXE,
        PROGRAM_CONFIG.VLC_EXE,
        "-I", "dummy", // no GUI
        "--dummy-quiet", // detach
        "--extraintf", "rc", "--rc-host", param_local_control, "--rc-quiet", // RC
        "-vvv", "screen://",
        "--sout", param_sout,
        "--sout-keep",
        NULL   
    );
    if (result == -1) LFATAL("_execl", errno);
}