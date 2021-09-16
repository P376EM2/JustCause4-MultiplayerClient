#include "Offsets.h"

namespace offsets
{
static uintptr_t g_Address[Address::COUNT] = {};

void InitAddresses(bool isSteam)
{
    g_Address[SANITY_CHECK] = isSteam ? 0x141e7ee40 : 0x141e84ae8;
    g_Address[INST_CLOCK] = isSteam ? 0x142c846b0 : 0x142c8aaa8;
    g_Address[INST_CHARACTER_MANAGER] = isSteam ? 0x142cb1d40 : 0x142cb8110;
    g_Address[INST_GAME_WORLD] = isSteam ? 0x142cb0a48 : 0x142cb6e08;
    g_Address[INST_INPUT_MANAGER] = isSteam ? 0x142ce1af0 : 0x142ce7f30;
    g_Address[INST_PLAYER_MANAGER] = isSteam ? 0x142cb2388 : 0x142cb8758;
    g_Address[INST_RENDER_ENGINE] = isSteam ? 0x142c84be8 : 0x142c8afd8;
    g_Address[INST_SPAWN_SYSTEM] = isSteam ? 0x142cb1d20 : 0x142cb80f0;
    g_Address[INST_UI_MANAGER] = isSteam ? 0x142cb7dc8 : 0x142cbe190;
    g_Address[INST_HNPKWORLD] = isSteam ? 0x142ce3f30 : 0x142cea370;
    g_Address[INST_WORLDTIME] = isSteam ? 0x142cafdb0 : 0x142cb6170;
    g_Address[VAR_QUICK_START] = isSteam ? 0x142cb8f40 : 0x142cbf304;
    g_Address[IS_INTRO_SEQUENCE_COMPLETE] = isSteam ? 0x140e935b0 : 0x140e9b0d0;
    g_Address[IS_INTRO_MOVIE_COMPLETE] = isSteam ? 0x140e93530 : 0x140e9b050;
    g_Address[WND_PROC] = isSteam ? 0x140c7fb50 : 0x140c86fb0;
    g_Address[GRAPHICS_FLIP] = isSteam ? 0x140fa2c70 : 0x140faa750;
    g_Address[PLAYER_MANAGER_UPDATE] = isSteam ? 0x1498aa770 : 0x14e501500;
    g_Address[FIRING_MODULE_CONSUME_AMMO] = isSteam ? 0x140728840 : 0x14072c510;
    g_Address[VAR_GAME_STATE] = isSteam ? 0x142cb8f24 : 0x142cbf2d4;
    g_Address[VAR_SUSPEND_GAME] = isSteam ? 0x142cbdaf0 : 0x142cc3f90;
    g_Address[ALLOC] = isSteam ? 0x140a51dc0 : 0x140a57510;
    g_Address[FREE] = isSteam ? 0x141af8e1c : 0x141b012dc;
    g_Address[GET_DEFAULT_PLATFORM_ALLOCATOR] = isSteam ? 0x140f236f0 : 0x140f2b380;
    g_Address[PLATFORM_ALLOCATOR_FREE] = isSteam ? 0x140838070 : 0x14083c9b0;
    g_Address[CHARACTER_MODEL_COPY_PARTS] = isSteam ? 0x14026e9b0 : 0x14026f7f0;
    g_Address[CHARACTER_MODEL_SET_PROPERTIES] = isSteam ? 0x14028c790 : 0x14028d4e0;
    g_Address[CHARACTER_MODEL_REBUILD_MODEL] = isSteam ? 0x140287840 : 0x140288590;
    g_Address[CHARACTER_GET_VEHICLE_PTR] = isSteam ? 0x14054fd50 : 0x140551a10;
    g_Address[SEND_EVENT] = isSteam ? 0x140286930 : 0x140287680;
    g_Address[SPAWN_SYSTEM_SPAWN] = isSteam ? 0x140badc60 : 0x140bb4a10;
    g_Address[SPAWN_SYSTEM_PARSE_TAGS] = isSteam ? 0x1499d0740 : 0x14e607061;
    g_Address[SPAWN_SYSTEM_GET_MATCHING_RESOURCES] = isSteam ? 0x140b88770 : 0x140b8ef20;
    g_Address[WORLDTIME_SET_TIME] = isSteam ? 0x140322720 : 0x140324070;
    g_Address[INPUT_LOST_FOCUS] = isSteam ? 0x140fc8560 : 0x140fce5e0;
    g_Address[INPUT_GAIN_FOCUS] = isSteam ? 0x140fc84b0 : 0x140fce530;
    g_Address[ENTITY_PROVIDER_CTOR] = isSteam ? 0x14025f860 : 0x140260710;
    g_Address[ENTITY_PROVIDER_LOAD_RESOURCES] = isSteam ? 0x140284870 : 0x140285590;
    g_Address[ENTITY_PROVIDER_UPDATE_INTERNAL] = isSteam ? 0x140294f20 : 0x140295cd0;
    g_Address[DRAW_SKIN_BATCHES] = isSteam ? 0x140d1a150 : 0x140d21810;
    g_Address[RUNTIME_CONTAINER_GET_HASH] = isSteam ? 0x140091360 : 0x140090f60;
    g_Address[VTABLE_RENDERBLOCKCHARACTER] = isSteam ? 0x141eac3a0 : 0x141eb2050;
    g_Address[VTABLE_RENDERBLOCKCHARACTERSKIN] = isSteam ? 0x141eac550 : 0x141eb2200;
    g_Address[VTABLE_RENDERBLOCKGENERAL] = isSteam ? 0x141ebdf50 : 0x141ec3c10;
}

uintptr_t GetAddress(Address address)
{
    return g_Address[address];
}
}; // namespace jc