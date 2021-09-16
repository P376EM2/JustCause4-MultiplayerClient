#pragma once

#include <Windows.h>
#include <filesystem>
#include <mutex>

#include "xinput9_1_0.h"

#include "input.h"

#include "Offsets.h"
#include "patches.h"

#include <meow_hook/memory.h>
#include <meow_hook/pattern_search.h>

static HMODULE g_original_module = nullptr;