#pragma once

#include <iostream>
#include <string>

#define _snprintf snprintf

#include "../Dependencies/Fortnite/Game/UE_Defnitions/entity_engine.hpp"

namespace offsets {
    // Current Patch: v39.50 - CL-51043566
    uintptr_t UWorld = 0x178D5418;
    uintptr_t GObjects = 0x177FFDB0;
    uintptr_t GNames = 0x17722E80;
    uintptr_t Levels = 0x1F0;
    uintptr_t AActors = 0x48;
    uintptr_t Mesh = 0x330;
    uintptr_t RootComponent = 0x1B0;
    uintptr_t ComponentToWorld = 0x1E0;
    uintptr_t PlayerController = 0x30;
    uintptr_t LocalPlayers = 0x38;
    uintptr_t OwningGameInstance = 0x250;
    uintptr_t GameState = 0x1D8;
    uintptr_t PersistentLevel = 0x40;
    uintptr_t PawnPrivate = 0x328;
    uintptr_t bIsABot = 0x2BA;
    uintptr_t TeamIndex = 0x11B1;
    uintptr_t CurrentWeapon = 0x990;
    uintptr_t WeaponData = 0x5B8;
    uintptr_t PlayerArray = 0x2C8;
    uintptr_t BoneArray = 0x5F0;
    uintptr_t PlayerState = 0x2D0;
    uintptr_t AcknowledgedPawn = 0x358;
    uintptr_t Platform = 0x440;
    uintptr_t RelativeLocation = 0x140;
    uintptr_t fLastSubmitTime = 0x2E0;
    uintptr_t fLastRenderTimeOnScreen = 0x328;
    uintptr_t WorldTimeSeconds = 0x198;
    uintptr_t OwningWorld = 0xC0;
    uintptr_t Velocity = 0x188;
    uintptr_t CurrentWeapons = 0x990;
}
