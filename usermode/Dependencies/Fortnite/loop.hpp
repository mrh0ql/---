#include "drawing.hpp"
#include <iostream>
#include <vector>
#include <memory>
#include <optional>
#include <thread>
#include <chrono>
#include "../../m_world.hpp"
#include <mutex>
#include <stdexcept>
using namespace std;
__int64 va_text;
vector<fvector> chestloc;
vector<fvector> ammo;
class item {
public:
    uintptr_t
        Actor;

    std::string
        Name;
    bool
        isVehicle,
        isChest,
        isPickup,
        isAmmoBox;
    float
        distance;
};
std::vector<item> item_pawns;
std::vector<entities> temporary_entity_list;

enum class EFortRarity : uint8_t
{
    EFortRarity__Common = 0,
    EFortRarity__Uncommon = 1,
    EFortRarity__Rare = 2,
    EFortRarity__Epic = 3,
    EFortRarity__Legendary = 4,
    EFortRarity__Mythic = 5,
    EFortRarity__Transcendent = 6,
    EFortRarity__Unattainable = 7,
    EFortRarity__NumRarityValues = 8,
};

ImVec4 get_loot_color(EFortRarity tier) {
    if (tier == EFortRarity::EFortRarity__Common)
        return ImVec4(123 / 255.0f, 123 / 255.0f, 123 / 255.0f, 1.f);
    else if (tier == EFortRarity::EFortRarity__Uncommon)
        return ImVec4(58 / 255.0f, 121 / 255.0f, 19 / 255.0f, 1.f);
    else if (tier == EFortRarity::EFortRarity__Rare)
        return ImVec4(18 / 255.0f, 88 / 255.0f, 162 / 255.0f, 1.f);
    else if (tier == EFortRarity::EFortRarity__Epic)
        return ImVec4(189 / 255.0f, 63 / 255.0f, 250 / 255.0f, 1.f);
    else if (tier == EFortRarity::EFortRarity__Legendary)
        return ImVec4(255 / 255.0f, 118 / 255.0f, 5 / 255.0f, 1.f);
    else if (tier == EFortRarity::EFortRarity__Mythic)
        return ImVec4(220 / 255.0f, 160 / 255.0f, 30 / 255.0f, 1.f);
    else if (tier == EFortRarity::EFortRarity__Transcendent)
        return ImVec4(0 / 255.0f, 225 / 255.0f, 252 / 255.0f, 1.f);

    return ImVec4(123 / 255.0f, 123 / 255.0f, 123 / 255.0f, 1.f);
}

std::string get_loot_tier_name(EFortRarity tier) {
    if (tier == EFortRarity::EFortRarity__Common)
        return "Common";
    else if (tier == EFortRarity::EFortRarity__Uncommon)
        return "Uncommon";
    else if (tier == EFortRarity::EFortRarity__Rare)
        return "Rare";
    else if (tier == EFortRarity::EFortRarity__Epic)
        return "Epic";
    else if (tier == EFortRarity::EFortRarity__Legendary)
        return "Legendary";
    else if (tier == EFortRarity::EFortRarity__Mythic)
        return "Mythic";
    else if (tier == EFortRarity::EFortRarity__Transcendent)
        return "Transcendent";

    return "Invalid";
}

void DrawString3(float fontSize, int x, int y, ImVec4 color, bool bCenter, bool stroke, const char* pText, ...)
{
    ImU32 converted_color = ImGui::ColorConvertFloat4ToU32(color);
    va_list va_alist;
    char buf[1024] = { 0 };
    va_start(va_alist, pText);
    _vsnprintf_s(buf, sizeof(buf), pText, va_alist);
    va_end(va_alist);
    std::string text = wstring_to_utf8(string_to_wstring(buf).c_str());
    if (bCenter)
    {
        ImVec2 textSize = ImGui::CalcTextSize(text.c_str());
        x = x - textSize.x / 4;
        y = y - textSize.y;
    }
    if (stroke)
    {
        ImGui::GetBackgroundDrawList()->AddText(ImGui::GetFont(), fontSize, ImVec2(x, y - 1), ImGui::ColorConvertFloat4ToU32(ImVec4(1 / 255.0, 1 / 255.0, 1 / 255.0, 255 / 255.0)), text.c_str());
        ImGui::GetBackgroundDrawList()->AddText(ImGui::GetFont(), fontSize, ImVec2(x, y + 1), ImGui::ColorConvertFloat4ToU32(ImVec4(1 / 255.0, 1 / 255.0, 1 / 255.0, 255 / 255.0)), text.c_str());
        ImGui::GetBackgroundDrawList()->AddText(ImGui::GetFont(), fontSize, ImVec2(x - 1, y), ImGui::ColorConvertFloat4ToU32(ImVec4(1 / 255.0, 1 / 255.0, 1 / 255.0, 255 / 255.0)), text.c_str());
        ImGui::GetBackgroundDrawList()->AddText(ImGui::GetFont(), fontSize, ImVec2(x + 1, y), ImGui::ColorConvertFloat4ToU32(ImVec4(1 / 255.0, 1 / 255.0, 1 / 255.0, 255 / 255.0)), text.c_str());
    }
    ImGui::GetBackgroundDrawList()->AddText(ImGui::GetFont(), fontSize, ImVec2(x, y), converted_color, text.c_str());
}

void DrawString2(float fontSize, int x, int y, ImColor color, bool bCenter, bool stroke, const char* pText, ...)
{
    va_list va_alist;
    char buf[1024] = { 0 };
    va_start(va_alist, pText);
    _vsnprintf_s(buf, sizeof(buf), pText, va_alist);
    va_end(va_alist);
    std::string text = wstring_to_utf8(string_to_wstring(buf).c_str());
    if (bCenter)
    {
        ImVec2 textSize = ImGui::CalcTextSize(text.c_str());
        x = x - textSize.x / 4;
        y = y - textSize.y;
    }
    if (stroke)
    {
        ImGui::GetBackgroundDrawList()->AddText(ImGui::GetFont(), fontSize, ImVec2(x, y - 1), ImGui::ColorConvertFloat4ToU32(ImVec4(1 / 255.0, 1 / 255.0, 1 / 255.0, 255 / 255.0)), text.c_str());
        ImGui::GetBackgroundDrawList()->AddText(ImGui::GetFont(), fontSize, ImVec2(x, y + 1), ImGui::ColorConvertFloat4ToU32(ImVec4(1 / 255.0, 1 / 255.0, 1 / 255.0, 255 / 255.0)), text.c_str());
        ImGui::GetBackgroundDrawList()->AddText(ImGui::GetFont(), fontSize, ImVec2(x - 1, y), ImGui::ColorConvertFloat4ToU32(ImVec4(1 / 255.0, 1 / 255.0, 1 / 255.0, 255 / 255.0)), text.c_str());
        ImGui::GetBackgroundDrawList()->AddText(ImGui::GetFont(), fontSize, ImVec2(x + 1, y), ImGui::ColorConvertFloat4ToU32(ImVec4(1 / 255.0, 1 / 255.0, 1 / 255.0, 255 / 255.0)), text.c_str());
    }
    ImGui::GetBackgroundDrawList()->AddText(ImGui::GetFont(), fontSize, ImVec2(x, y), color, text.c_str());
}

#define FNAMEPOOL_OFFSET 0x1778FC80

static std::string GetNameFromIndex(int key)
{
    SPOOF_FUNC;
    uint32_t ChunkOffset = (uint32_t)((int)(key) >> 16);
    uint16_t NameOffset = (uint16_t)key;
    uint64_t NamePoolChunk = device_().read<uint64_t>(va_text + FNAMEPOOL_OFFSET + (8 * ChunkOffset) + 16) + (unsigned int)(2 * NameOffset);
    uint16_t nameEntry = device_().read<uint16_t>(NamePoolChunk);
    int nameLength = nameEntry >> 6;
    char buff[1024] = {};

    char* v3 = buff;
    int v5;
    __int64 result = nameLength;
    __int64 v7 = 0;
    unsigned int v8;
    v5 = 26;
    if ((int)result)
    {
        device_().read1(reinterpret_cast<void*>(NamePoolChunk + 2), static_cast<uint8_t*>(static_cast<void*>(buff)), 2 * nameLength);
        do
        {
            v8 = v5 + 45297;
            *v3 = v8 + ~*v3;
            result = v8 << 8;
            v5 = result | (v8 >> 8);
            ++v3;
            --v7;
        } while (v7);
        buff[nameLength] = '\0';
        return std::string(buff);
    }
    return std::string("");
}

static std::string get_fname(int key)
{
    SPOOF_FUNC;
    uint32_t ChunkOffset = (uint32_t)((int)(key) >> 16);
    uint16_t NameOffset = (uint16_t)key;

    uint64_t NamePoolChunk = device_().read<uint64_t>(va_text + FNAMEPOOL_OFFSET + (8 * ChunkOffset) + 16) + (unsigned int)(2 * NameOffset);
    if (device_().read<uint16_t>(NamePoolChunk) < 64)
    {
        auto a1 = device_().read<DWORD>(NamePoolChunk + 2);
        return GetNameFromIndex(a1);
    }
    else
    {
        return GetNameFromIndex(key);
    }
}

namespace GameCache {

    Cache& cache = Cache::getInstance();

    uintptr_t local_player_() {
        auto gameInstance = cache.gameInstance_;
        if (!gameInstance.has_value()) return 0;
        return device_().read<uintptr_t>(device_().read<uintptr_t>(gameInstance.value() + 0x38));
    }

    int array_size_() {
        auto gameState = cache.gameState_;
        if (!gameState.has_value()) return 0;
        return device_().read<int>(gameState.value() + apply_offset_().player_array_() + sizeof(uintptr_t));
    }

    char team_id_() {
        if (!cache.playerState_.has_value()) return 0;
        return device_().read<char>(cache.playerState_.value_or(0) + apply_offset_().team_id_());
    }

    uintptr_t apply_offset(uintptr_t base, uintptr_t offset) {
        return base + offset;
    }

    template<typename T>
    optional<T> readd(uintptr_t address) {
        try {
            return device_().read<T>(address);
        }
        catch (const exception& e) {
            cerr << "read issue" << hex << address << ": " << e.what() << endl;
            return nullopt;
        }
    }

    template<typename T>
    void Cache::update_cache_val(optional<T>& cachevar, uintptr_t base, uintptr_t offset) {
        if (auto value = readd<T>(apply_offset(base, offset))) {
            cachevar = move(value);
        }
    }

    auto GetPlayerArray() -> TArray<uintptr_t*>
    {
        return device_().read<TArray<uintptr_t*>>(cache.gameState_.value() + apply_offset_().player_array_());
    }

    static auto RootC(uintptr_t actor) {
        return device_().read<uintptr_t>(actor + offset::root_component);
    }

    static auto GetLocation(uintptr_t actor) {
        return device_().read<fvector>(RootC(actor) + offset::relative_location);
    }

    uintptr_t reada(uintptr_t baseAddress, uintptr_t offset) {
        return read_addy(uintptr_t, baseAddress, offset);
    }

    // Sequential cache chain - no async for dependent reads
    void Cache::cache() {
        lock_guard<mutex> lock(cacheMutex_);

        auto encrypted = device_().read<uintptr_t>(apply_offset(offset_()->get_apply_offsets().uworld_(), va_text));
        uworld_ = encrypted ^ 0xFFFFFFFFDF234856ULL;

        if (debug) {
            std::cout << "[cache] uworld encrypted: 0x" << std::hex << encrypted
                      << " decrypted: 0x" << uworld_.value_or(0) << std::dec << std::endl;
        }

        if (!uworld_ || !uworld_.value()) {
            if (debug) std::cout << "[cache] FAIL: uworld is null after XOR decrypt" << std::endl;
            return;
        }

        // Independent reads from UWorld (can be done together)
        update_cache_val<uintptr_t>(locationPtr_, uworld_.value(), offset_()->get_apply_offsets().location_ptr_());
        update_cache_val<uintptr_t>(rotationPtr_, uworld_.value(), offset_()->get_apply_offsets().rotation_ptr_());
        update_cache_val<uintptr_t>(gameInstance_, uworld_.value(), offset_()->get_apply_offsets().game_instance_());
        update_cache_val<uintptr_t>(gameState_, uworld_.value(), offset_()->get_apply_offsets().game_state_());

        if (debug) {
            std::cout << "[cache] gameInstance: 0x" << std::hex << gameInstance_.value_or(0)
                      << " gameState: 0x" << gameState_.value_or(0)
                      << " locPtr: 0x" << locationPtr_.value_or(0)
                      << " rotPtr: 0x" << rotationPtr_.value_or(0) << std::dec << std::endl;
        }

        // GameState -> PlayerArray (sequential, depends on gameState_)
        if (gameState_.has_value() && gameState_.value()) {
            update_cache_val<uintptr_t>(playerArray_, gameState_.value(), offset_()->get_apply_offsets().player_array_());
            playerArraySize_ = array_size_();
            if (debug) {
                std::cout << "[cache] playerArray: 0x" << std::hex << playerArray_.value_or(0)
                          << std::dec << " size: " << playerArraySize_.value_or(0) << std::endl;
            }
        }

        // GameInstance -> LocalPlayer (sequential)
        localPlayer_ = local_player_();

        if (localPlayer_.has_value() && localPlayer_.value()) {
            // LocalPlayer -> PlayerController (sequential, depends on localPlayer_)
            update_cache_val<uintptr_t>(playerController_, localPlayer_.value(), offset_()->get_apply_offsets().player_controller_());

            // PlayerController -> AcknowledgedPawn (sequential, depends on playerController_)
            if (playerController_.has_value() && playerController_.value()) {
                update_cache_val<uintptr_t>(acknowledgedPawn_, playerController_.value(), offset_()->get_apply_offsets().local_pawn_());

                // AcknowledgedPawn -> Mesh, PlayerState, RootComponent (sequential, depends on acknowledgedPawn_)
                auto localpawn_val = acknowledgedPawn_.value_or(0);
                if (localpawn_val) {
                    update_cache_val<uintptr_t>(skeletalMesh_, localpawn_val, offset_()->get_apply_offsets().mesh_());
                    update_cache_val<uintptr_t>(playerState_, localpawn_val, offset_()->get_apply_offsets().pstate_());
                    update_cache_val<uintptr_t>(rootComponent_, localpawn_val, offset_()->get_apply_offsets().root_());
                }
            }
        }

        teamIndex_ = team_id_();

        if (debug) {
            std::cout << "[cache] localPlayer: 0x" << std::hex << localPlayer_.value_or(0)
                      << " pController: 0x" << playerController_.value_or(0)
                      << " localPawn: 0x" << acknowledgedPawn_.value_or(0)
                      << " mesh: 0x" << skeletalMesh_.value_or(0)
                      << std::dec << " teamID: " << (int)teamIndex_.value_or(0) << std::endl;
        }
    }

    void cachep() {
        Cache& cache = Cache::getInstance();
        cache.cache();

        vector<entities> temp_entity_list;

        auto player_array_ = cache.get_playerarray();
        auto array_size_ = cache.get_playersize().value_or(0);

        for (int i = 0; i < array_size_; ++i) {
            uintptr_t pstate_ = reada(player_array_.value_or(0), i * sizeof(uintptr_t));

            uintptr_t aactor = reada(pstate_, static_cast<uintptr_t>(offset_()->get_apply_offsets().pawn_private_()));

            if (aactor == cache.get_local_pawn().value_or(0))
                continue;

            uintptr_t mesh = reada(aactor, static_cast<uintptr_t>(offset_()->get_apply_offsets().mesh_()));
            if (!mesh)
                continue;

            uintptr_t array_p = reada(player_array_.value_or(0), i * 0x8);
            uintptr_t local_actor = reada(array_p, static_cast<uintptr_t>(offset_()->get_apply_offsets().pawn_private_()));

            int teamid = static_cast<int>(reada(pstate_, static_cast<uintptr_t>(offset_()->get_apply_offsets().team_id_())));
            uint64_t local_player_state = reada(local_actor, static_cast<uintptr_t>(offset_()->get_apply_offsets().pstate_()));

            if (cache.get_local_pawn().value_or(0))
                if (teamid == cache.get_teamid().value_or(0)) continue;

            entities storedEntity;
            storedEntity.entity_ = aactor;
            storedEntity.mesh_ = mesh;
            storedEntity.pstate_ = pstate_;
            storedEntity.local_player_state_ = local_player_state;
            temp_entity_list.push_back(storedEntity);
        }

        {
            lock_guard<mutex> lock(cache.cacheMutex_);
            entity_list.swap(temp_entity_list);
        }

        sleep_for(milliseconds(200));
    }
}
