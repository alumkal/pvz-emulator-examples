#pragma once

#include "seml/types.h"

struct Test {
    std::vector<Op> ops;
    std::vector<std::vector<unique_plant>> plants_to_be_shoveled;
    std::vector<pvz_emulator::object::plant*> protect_plants;
};
