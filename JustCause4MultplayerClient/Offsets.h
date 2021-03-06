#pragma once

#include <cstdint>

namespace offsets
{
enum Address {
    SANITY_CHECK,
    INST_CLOCK,
    INST_CHARACTER_MANAGER,
    INST_GAME_WORLD,
    INST_INPUT_MANAGER,
    INST_PLAYER_MANAGER,
    INST_RENDER_ENGINE,
    INST_SPAWN_SYSTEM,
    INST_UI_MANAGER,
    INST_HNPKWORLD,
    INST_WORLDTIME,
    VAR_QUICK_START,
    IS_INTRO_SEQUENCE_COMPLETE,
    IS_INTRO_MOVIE_COMPLETE,
    WND_PROC,
    GRAPHICS_FLIP,
    PLAYER_MANAGER_UPDATE,
    FIRING_MODULE_CONSUME_AMMO,
    VAR_GAME_STATE,
    VAR_SUSPEND_GAME,
    ALLOC,
    FREE,
    GET_DEFAULT_PLATFORM_ALLOCATOR,
    PLATFORM_ALLOCATOR_FREE,
    CHARACTER_MODEL_COPY_PARTS,
    CHARACTER_MODEL_SET_PROPERTIES,
    CHARACTER_MODEL_REBUILD_MODEL,
    CHARACTER_GET_VEHICLE_PTR,
    SEND_EVENT,
    SPAWN_SYSTEM_SPAWN,
    SPAWN_SYSTEM_PARSE_TAGS,
    SPAWN_SYSTEM_GET_MATCHING_RESOURCES,
    WORLDTIME_SET_TIME,
    INPUT_LOST_FOCUS,
    INPUT_GAIN_FOCUS,
    ENTITY_PROVIDER_CTOR,
    ENTITY_PROVIDER_LOAD_RESOURCES,
    ENTITY_PROVIDER_UPDATE_INTERNAL,
    DRAW_SKIN_BATCHES,
    RUNTIME_CONTAINER_GET_HASH,
    VTABLE_RENDERBLOCKCHARACTER,
    VTABLE_RENDERBLOCKCHARACTERSKIN,
    VTABLE_RENDERBLOCKGENERAL,
    COUNT,
};

void InitAddresses(bool is_steam);
uintptr_t GetAddress(Address address);
}; // namespace jc