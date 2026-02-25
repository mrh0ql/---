#include "Game/aimbot.hpp"
#include <iomanip>
#include <sstream>
#include <algorithm>
#include <unordered_set>
std::atomic<bool> aimbot_running(false);
std::thread aimbot_thread;


void DrawGradientBackground(ImVec2 p1, ImVec2 p2, ImU32 col1, ImU32 col2) {
    ImGui::GetWindowDrawList()->AddRectFilledMultiColor(p1, p2, col1, col2, col2, col1);
}



void RenderTargetGUI(int kills, char teamid, std::string& targetName, const std::string& weaponName, float distance, ImVec2 screenPos) {
    SPOOF_FUNC;

    ImGui::SetNextWindowPos(screenPos, ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2(200, 140), ImGuiCond_Always);

    ImGui::Begin("Target GUI", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoBackground);

    ImVec2 windowPos = ImGui::GetWindowPos();
    ImVec2 windowSize = ImGui::GetWindowSize();

    ImU32 col1 = ImGui::GetColorU32(ImVec4(0.0353f, 0.1882f, 0.1569f, 0.8f));
    ImU32 col2 = ImGui::GetColorU32(ImVec4(0.1373f, 0.4784f, 0.3412f, 0.8f));

    DrawGradientBackground(windowPos, ImVec2(windowPos.x + windowSize.x, windowPos.y + windowSize.y), col1, col2);

    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 10.0f);
    ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(255, 255, 255, 255));
    ImGui::PushStyleColor(ImGuiCol_Border, IM_COL32(0, 0, 0, 0));
    ImGui::SetCursorPos(ImVec2(10, 10));
    ImGui::Text("Target: %s", targetName.c_str());
    ImGui::SetCursorPos(ImVec2(10, 30));
    ImGui::Text("Weapon: %s", weaponName.c_str());
    ImGui::SetCursorPos(ImVec2(10, 50));
    ImGui::Text("Kills: %d", kills);
    ImGui::SetCursorPos(ImVec2(10, 70));
    ImGui::Text("TeamID: %d", teamid);
    ImGui::SetCursorPos(ImVec2(10, 110));
    ImGui::Text("Distance: %.2fm", distance);

    ImGui::PopStyleColor(2);
    ImGui::PopStyleVar(2);

    ImGui::End();
}

void draw_box1(int x, int y, int w, int h, const ImColor color, ImColor fill_color, int thickness)
{
    if (c_filled_box)
    {
        ImGui::GetBackgroundDrawList()->AddRectFilled(ImVec2(x, y), ImVec2(x + w, y + h), fill_color, 0, 0);
    }
    ImGui::GetBackgroundDrawList()->AddRect(ImVec2(x + 1, y + 1), ImVec2(x + w - 1, y + h - 1), ImColor(0, 0, 0), 0, 0, thickness);
    ImGui::GetBackgroundDrawList()->AddRect(ImVec2(x - 1, y - 1), ImVec2(x + w + 1, y + h + 1), ImColor(0, 0, 0), 0, 0, thickness);
    ImGui::GetBackgroundDrawList()->AddRect(ImVec2(x + 1, y - 1), ImVec2(x + w - 1, y + h + 1), ImColor(0, 0, 0), 0, 0, thickness);
    ImGui::GetBackgroundDrawList()->AddRect(ImVec2(x - 1, y + 1), ImVec2(x + w + 1, y + h - 1), ImColor(0, 0, 0), 0, 0, thickness);
    ImGui::GetBackgroundDrawList()->AddRect(ImVec2(x, y), ImVec2(x + w, y + h), color, 0, 0, thickness);
}

void draw_skeleton(uintptr_t mesh, ImColor color)
{
    fvector head = bone_manager.get_bone(110);
    fvector2d wts_head = camera_manager.w2s(head);
    fvector neck = bone_manager.get_bone(67);
    fvector2d wts_neck = camera_manager.w2s(neck);
    fvector chest = bone_manager.get_bone(7);
    fvector2d wts_chest = camera_manager.w2s(chest);
    fvector pelvis = bone_manager.get_bone(2);
    fvector2d wts_pelvis = camera_manager.w2s(pelvis);

    fvector right_shoulder = bone_manager.get_bone(9);
    fvector2d wts_right_shoulder = camera_manager.w2s(right_shoulder);
    fvector right_elbow = bone_manager.get_bone(10);
    fvector2d wts_right_elbow = camera_manager.w2s(right_elbow);
    fvector right_wrist = bone_manager.get_bone(11);
    fvector2d wts_right_wrist = camera_manager.w2s(right_wrist);

    fvector left_shoulder = bone_manager.get_bone(38);
    fvector2d wts_left_shoulder = camera_manager.w2s(left_shoulder);
    fvector left_elbow = bone_manager.get_bone(39);
    fvector2d wts_left_elbow = camera_manager.w2s(left_elbow);
    fvector left_wrist = bone_manager.get_bone(40);
    fvector2d wts_left_wrist = camera_manager.w2s(left_wrist);

    fvector right_hip = bone_manager.get_bone(71);
    fvector2d wts_right_hip = camera_manager.w2s(right_hip);
    fvector right_knee = bone_manager.get_bone(72);
    fvector2d wts_right_knee = camera_manager.w2s(right_knee);
    fvector right_ankle = bone_manager.get_bone(73);
    fvector2d wts_right_ankle = camera_manager.w2s(right_ankle);
    fvector right_foot_upper = bone_manager.get_bone(86);
    fvector2d wts_right_foot_upper = camera_manager.w2s(right_foot_upper);
    fvector right_foot = bone_manager.get_bone(76);
    fvector2d wts_right_foot = camera_manager.w2s(right_foot);

    fvector left_hip = bone_manager.get_bone(78);
    fvector2d wts_left_hip = camera_manager.w2s(left_hip);
    fvector left_knee = bone_manager.get_bone(79);
    fvector2d wts_left_knee = camera_manager.w2s(left_knee);
    fvector left_ankle = bone_manager.get_bone(80);
    fvector2d wts_left_ankle = camera_manager.w2s(left_ankle);
    fvector left_foot_upper = bone_manager.get_bone(87);
    fvector2d wts_left_foot_upper = camera_manager.w2s(left_foot_upper);
    fvector left_foot = bone_manager.get_bone(83);
    fvector2d wts_left_foot = camera_manager.w2s(left_foot);

    ImGui::GetBackgroundDrawList()->AddLine(ImVec2(wts_head.x, wts_head.y), ImVec2(wts_neck.x, wts_neck.y), ImColor(0, 0, 0, 255), c_outlined + 1.0f);
    ImGui::GetBackgroundDrawList()->AddLine(ImVec2(wts_neck.x, wts_neck.y), ImVec2(wts_chest.x, wts_chest.y), ImColor(0, 0, 0, 255), c_outlined + 1.0f);
    ImGui::GetBackgroundDrawList()->AddLine(ImVec2(wts_chest.x, wts_chest.y), ImVec2(wts_pelvis.x, wts_pelvis.y), ImColor(0, 0, 0, 255), c_outlined + 1.0f);
    ImGui::GetBackgroundDrawList()->AddLine(ImVec2(wts_chest.x, wts_chest.y), ImVec2(wts_right_shoulder.x, wts_right_shoulder.y), ImColor(0, 0, 0, 255), c_outlined + 1.0f);
    ImGui::GetBackgroundDrawList()->AddLine(ImVec2(wts_right_shoulder.x, wts_right_shoulder.y), ImVec2(wts_right_elbow.x, wts_right_elbow.y), ImColor(0, 0, 0, 255), c_outlined + 1.0f);
    ImGui::GetBackgroundDrawList()->AddLine(ImVec2(wts_right_elbow.x, wts_right_elbow.y), ImVec2(wts_right_wrist.x, wts_right_wrist.y), ImColor(0, 0, 0, 255), c_outlined + 1.0f);
    ImGui::GetBackgroundDrawList()->AddLine(ImVec2(wts_chest.x, wts_chest.y), ImVec2(wts_left_shoulder.x, wts_left_shoulder.y), ImColor(0, 0, 0, 255), c_outlined + 1.0f);
    ImGui::GetBackgroundDrawList()->AddLine(ImVec2(wts_left_shoulder.x, wts_left_shoulder.y), ImVec2(wts_left_elbow.x, wts_left_elbow.y), ImColor(0, 0, 0, 255), c_outlined + 1.0f);
    ImGui::GetBackgroundDrawList()->AddLine(ImVec2(wts_left_elbow.x, wts_left_elbow.y), ImVec2(wts_left_wrist.x, wts_left_wrist.y), ImColor(0, 0, 0, 255), c_outlined + 1.0f);
    ImGui::GetBackgroundDrawList()->AddLine(ImVec2(wts_pelvis.x, wts_pelvis.y), ImVec2(wts_right_hip.x, wts_right_hip.y), ImColor(0, 0, 0, 255), c_outlined + 1.0f);
    ImGui::GetBackgroundDrawList()->AddLine(ImVec2(wts_right_hip.x, wts_right_hip.y), ImVec2(wts_right_knee.x, wts_right_knee.y), ImColor(0, 0, 0, 255), c_outlined + 1.0f);
    ImGui::GetBackgroundDrawList()->AddLine(ImVec2(wts_right_knee.x, wts_right_knee.y), ImVec2(wts_right_ankle.x, wts_right_ankle.y), ImColor(0, 0, 0, 255), c_outlined + 1.0f);
    ImGui::GetBackgroundDrawList()->AddLine(ImVec2(wts_right_ankle.x, wts_right_ankle.y), ImVec2(wts_right_foot_upper.x, wts_right_foot_upper.y), ImColor(0, 0, 0, 255), c_outlined + 1.0f);
    ImGui::GetBackgroundDrawList()->AddLine(ImVec2(wts_right_foot_upper.x, wts_right_foot_upper.y), ImVec2(wts_right_foot.x, wts_right_foot.y), ImColor(0, 0, 0, 255), c_outlined + 1.0f);
    ImGui::GetBackgroundDrawList()->AddLine(ImVec2(wts_pelvis.x, wts_pelvis.y), ImVec2(wts_left_hip.x, wts_left_hip.y), ImColor(0, 0, 0, 255), c_outlined + 1.0f);
    ImGui::GetBackgroundDrawList()->AddLine(ImVec2(wts_left_hip.x, wts_left_hip.y), ImVec2(wts_left_knee.x, wts_left_knee.y), ImColor(0, 0, 0, 255), c_outlined + 1.0f);
    ImGui::GetBackgroundDrawList()->AddLine(ImVec2(wts_left_knee.x, wts_left_knee.y), ImVec2(wts_left_ankle.x, wts_left_ankle.y), ImColor(0, 0, 0, 255), c_outlined + 1.0f);
    ImGui::GetBackgroundDrawList()->AddLine(ImVec2(wts_left_ankle.x, wts_left_ankle.y), ImVec2(wts_left_foot_upper.x, wts_left_foot_upper.y), ImColor(0, 0, 0, 255), c_outlined + 1.0f);
    ImGui::GetBackgroundDrawList()->AddLine(ImVec2(wts_left_foot_upper.x, wts_left_foot_upper.y), ImVec2(wts_left_foot.x, wts_left_foot.y), ImColor(0, 0, 0, 255), c_outlined + 1.0f);

    ImGui::GetBackgroundDrawList()->AddLine(ImVec2(wts_head.x, wts_head.y), ImVec2(wts_neck.x, wts_neck.y), color, c_outlined);
    ImGui::GetBackgroundDrawList()->AddLine(ImVec2(wts_neck.x, wts_neck.y), ImVec2(wts_chest.x, wts_chest.y), color, c_outlined);
    ImGui::GetBackgroundDrawList()->AddLine(ImVec2(wts_chest.x, wts_chest.y), ImVec2(wts_pelvis.x, wts_pelvis.y), color, c_outlined);
    ImGui::GetBackgroundDrawList()->AddLine(ImVec2(wts_chest.x, wts_chest.y), ImVec2(wts_right_shoulder.x, wts_right_shoulder.y), color, c_outlined);
    ImGui::GetBackgroundDrawList()->AddLine(ImVec2(wts_right_shoulder.x, wts_right_shoulder.y), ImVec2(wts_right_elbow.x, wts_right_elbow.y), color, c_outlined);
    ImGui::GetBackgroundDrawList()->AddLine(ImVec2(wts_right_elbow.x, wts_right_elbow.y), ImVec2(wts_right_wrist.x, wts_right_wrist.y), color, c_outlined);
    ImGui::GetBackgroundDrawList()->AddLine(ImVec2(wts_chest.x, wts_chest.y), ImVec2(wts_left_shoulder.x, wts_left_shoulder.y), color, c_outlined);
    ImGui::GetBackgroundDrawList()->AddLine(ImVec2(wts_left_shoulder.x, wts_left_shoulder.y), ImVec2(wts_left_elbow.x, wts_left_elbow.y), color, c_outlined);
    ImGui::GetBackgroundDrawList()->AddLine(ImVec2(wts_left_elbow.x, wts_left_elbow.y), ImVec2(wts_left_wrist.x, wts_left_wrist.y), color, c_outlined);
    ImGui::GetBackgroundDrawList()->AddLine(ImVec2(wts_pelvis.x, wts_pelvis.y), ImVec2(wts_right_hip.x, wts_right_hip.y), color, c_outlined);
    ImGui::GetBackgroundDrawList()->AddLine(ImVec2(wts_right_hip.x, wts_right_hip.y), ImVec2(wts_right_knee.x, wts_right_knee.y), color, c_outlined);
    ImGui::GetBackgroundDrawList()->AddLine(ImVec2(wts_right_knee.x, wts_right_knee.y), ImVec2(wts_right_ankle.x, wts_right_ankle.y), color, c_outlined);
    ImGui::GetBackgroundDrawList()->AddLine(ImVec2(wts_right_ankle.x, wts_right_ankle.y), ImVec2(wts_right_foot_upper.x, wts_right_foot_upper.y), color, c_outlined);
    ImGui::GetBackgroundDrawList()->AddLine(ImVec2(wts_right_foot_upper.x, wts_right_foot_upper.y), ImVec2(wts_right_foot.x, wts_right_foot.y), color, c_outlined);
    ImGui::GetBackgroundDrawList()->AddLine(ImVec2(wts_pelvis.x, wts_pelvis.y), ImVec2(wts_left_hip.x, wts_left_hip.y), color, c_outlined);
    ImGui::GetBackgroundDrawList()->AddLine(ImVec2(wts_left_hip.x, wts_left_hip.y), ImVec2(wts_left_knee.x, wts_left_knee.y), color, c_outlined);
    ImGui::GetBackgroundDrawList()->AddLine(ImVec2(wts_left_knee.x, wts_left_knee.y), ImVec2(wts_left_ankle.x, wts_left_ankle.y), color, c_outlined);
    ImGui::GetBackgroundDrawList()->AddLine(ImVec2(wts_left_ankle.x, wts_left_ankle.y), ImVec2(wts_left_foot_upper.x, wts_left_foot_upper.y), color, c_outlined);
    ImGui::GetBackgroundDrawList()->AddLine(ImVec2(wts_left_foot_upper.x, wts_left_foot_upper.y), ImVec2(wts_left_foot.x, wts_left_foot.y), color, c_outlined);
}

void draw_cornered_box(int x, int y, int w, int h, ImColor color, float thickness, float th)
{
    ImGui::GetBackgroundDrawList()->AddLine(ImVec2(x, y), ImVec2(x, y + (h / 3)), color, thickness);
    ImGui::GetBackgroundDrawList()->AddLine(ImVec2(x, y), ImVec2(x + (w / 3), y), color, thickness);
    ImGui::GetBackgroundDrawList()->AddLine(ImVec2(x + w - (w / 3), y), ImVec2(x + w, y), color, thickness);
    ImGui::GetBackgroundDrawList()->AddLine(ImVec2(x + w, y), ImVec2(x + w, y + (h / 3)), color, thickness);
    ImGui::GetBackgroundDrawList()->AddLine(ImVec2(x, y + h - (h / 3)), ImVec2(x, y + h), color, thickness);
    ImGui::GetBackgroundDrawList()->AddLine(ImVec2(x, y + h), ImVec2(x + (w / 3), y + h), color, thickness);
    ImGui::GetBackgroundDrawList()->AddLine(ImVec2(x + w - (w / 3), y + h), ImVec2(x + w, y + h), color, thickness);
    ImGui::GetBackgroundDrawList()->AddLine(ImVec2(x + w, y + h - (h / 3)), ImVec2(x + w, y + h), color, thickness);
}

bool is_shotgun(const std::string& weapon)
{
    return weapon.find("Shotgun") != std::string::npos;
}

int getCurrentWeaponFovSize() {
    auto& cache = GameCache::Cache::getInstance();
    weapon_info_ local_held_weapon = weapon_manager.get_weapon_name(cache.get_local_pawn().value_or(0));
    local_player_weapon = local_held_weapon.weapon_name;
    std::string weaponName = local_player_weapon;

    if (weaponName.find("Shotgun") != std::string::npos) {
        return weapon_cfg::shotgun::rFovSize;
    }
    else if (weaponName.find("SMG") != std::string::npos) {
        return weapon_cfg::smg::rFovSize;
    }
    else if (weaponName.find("Rifle") != std::string::npos) {
        return weapon_cfg::rifle::rFovSize;
    }
    else if (weaponName.find("Sniper") != std::string::npos) {
        return weapon_cfg::sniper::rFovSize;
    }

    return rFovSize;
}

static auto is_visible(uintptr_t skeletal_mesh) -> bool {
    auto& cache = GameCache::Cache::getInstance();
    auto world_time = device_().read<double>(cache.get_uworld().value_or(0) + offset::WorldTimeSeconds);
    auto last_render = device_().read<float>(skeletal_mesh + offset::last_render);
    return (bool)(last_render + 0.06f >= world_time);
}

void radar_range(float* x, float* y, float range)
{
    if (fabs((*x)) > range || fabs((*y)) > range)
    {
        if ((*y) > (*x))
        {
            if ((*y) > -(*x))
            {
                (*x) = range * (*x) / (*y);
                (*y) = range;
            }
            else
            {
                (*y) = -range * (*y) / (*x);
                (*x) = -range;
            }
        }
        else
        {
            if ((*y) > -(*x))
            {
                (*y) = range * (*y) / (*x);
                (*x) = range;
            }
            else
            {
                (*x) = -range * (*x) / (*y);
                (*y) = -range;
            }
        }
    }
}

void project_world_to_radar(fvector vOrigin, int& screenx, int& screeny)
{
    frotator camera_location = rotation;
    frotator vAngle = rotation;
    auto fYaw = vAngle.Yaw * M_PI / 180.0f;
    float dx = vOrigin.x - location.x;
    float dy = vOrigin.y - location.y;
    float fsin_yaw = sinf(fYaw);
    float fminus_cos_yaw = -cosf(fYaw);
    float x = dy * fminus_cos_yaw + dx * fsin_yaw;
    x = -x;
    float y = dx * fminus_cos_yaw - dy * fsin_yaw;
    float range = (float)(200.0f / 5) * 1000.f;

    radar_range(&x, &y, range);

    ImVec2 DrawPos = ImVec2(10.0f, 60.0f);
    ImVec2 DrawSize = ImVec2(200.0f, 200.0f);
    float radarRadius = 200.0f / 2;
    float distance = sqrt(pow(screenx - DrawPos.x, 2) + pow(screeny - DrawPos.y, 2));

    if (distance > radarRadius)
    {
        float angle = atan2(screeny - DrawPos.y, screenx - DrawPos.x);
        screenx = static_cast<int>(DrawPos.x + radarRadius * cos(angle));
        screeny = static_cast<int>(DrawPos.y + radarRadius * sin(angle));
    }

    int rad_x = (int)DrawPos.x;
    int rad_y = (int)DrawPos.y;
    float r_siz_x = DrawSize.x;
    float r_siz_y = DrawSize.y;
    int x_max = (int)r_siz_x + rad_x - 5;
    int y_max = (int)r_siz_y + rad_y - 5;

    screenx = rad_x + ((int)r_siz_x / 2 + int(x / range * r_siz_x));
    screeny = rad_y + ((int)r_siz_y / 2 + int(y / range * r_siz_y));

    if (screenx > x_max)
        screenx = x_max;

    if (screenx < rad_x)
        screenx = rad_x;

    if (screeny > y_max)
        screeny = y_max;

    if (screeny < rad_y)
        screeny = rad_y;
}

void line1(const ImVec2& from, const ImVec2& to, ImColor color, float thickness) {
    ImGui::GetBackgroundDrawList()->AddLine(from, to, color, thickness);
}


void draw_head(ImColor color, fvector head_location)
{
    auto& cache = GameCache::Cache::getInstance();

    if (!cache.get_local_pawn().value_or(0))
    {
        auto camera_location = location;
        auto fov1 = fov;
        fvector2d head_2d = camera_manager.w2s(fvector(head_location.x, head_location.y, head_location.z + 20));
        fvector delta = head_location - location;

        float distance = delta.length();
        const float constant_circle_size = 10;
        float circle_radius = constant_circle_size * (c_screen_height / (2.0f * distance * tanf(fov1 * (float)M_PI / 360.f)));
        float y_offset = +70.0f;
        head_2d.y += y_offset;
        int segments = 50;

        ImGui::GetBackgroundDrawList()->AddCircle(ImVec2(head_2d.x, head_2d.y), circle_radius, ImColor(0, 0, 0, 255), segments, c_outlined + 1.0f);
        ImGui::GetBackgroundDrawList()->AddCircle(ImVec2(head_2d.x, head_2d.y), circle_radius, color, segments, c_outlined);
    }
    else
    {
        auto camera_location = location;
        auto fov1 = fov;
        fvector2d head_2d = camera_manager.w2s(fvector(head_location.x, head_location.y, head_location.z));
        fvector delta = head_location - location;

        float distance = delta.length();
        const float constant_circle_size = 10;
        float circle_radius = constant_circle_size * (c_screen_height / (2.0f * distance * tanf(fov1 * (float)M_PI / 360.f)));
        float y_offset = +12.0f;
        int segments = 50;

        ImGui::GetBackgroundDrawList()->AddCircle(ImVec2(head_2d.x, head_2d.y), circle_radius, ImColor(0, 0, 0, 255), segments, c_outlined + 1.0f);
        ImGui::GetBackgroundDrawList()->AddCircle(ImVec2(head_2d.x, head_2d.y), circle_radius, color, segments, c_outlined);
    }
}

fvector PredictPlayerPosition(fvector CurrentLocation, float DistanceToTarget, fvector Velocity, float ProjectileSpeed, float ProjectileGravity) {
    fvector CalculatedPosition = CurrentLocation;

    if (ProjectileSpeed <= 0) return CalculatedPosition;
    float fHorizontalTime = DistanceToTarget / fabsf(ProjectileSpeed);
    float fVerticalTime = DistanceToTarget / fabsf(ProjectileSpeed);
    CalculatedPosition.x += Velocity.x * fHorizontalTime;
    CalculatedPosition.y += Velocity.y * fHorizontalTime;
    CalculatedPosition.z += Velocity.z * fVerticalTime;
    CalculatedPosition.z += abs(-980.f * ProjectileGravity) * 0.5f * (fVerticalTime * fVerticalTime);

    return CalculatedPosition;
}

float  target_dist = FLT_MAX;
uintptr_t target_entity = NULL;
void draw_esp_elements(const entities& Player, const fvector& camera_location) {
    SPOOF_FUNC;
    
    auto& cache = GameCache::Cache::getInstance();
    ImDrawList* drawlist = ImGui::GetBackgroundDrawList();

    bone_manager.get_bone_array(Player.mesh_);

    auto root_bone = bone_manager.get_bone(root);
    auto head_bone = bone_manager.get_bone(Head);

    auto root = camera_manager.w2s(fvector(root_bone.x, root_bone.y, root_bone.z - 15));
    auto head = camera_manager.w2s(head_bone);
    auto head_box = camera_manager.w2s(fvector(head_bone.x, head_bone.y, head_bone.z + 15));
    auto root_box = camera_manager.w2s(root_bone);
    auto pelvis_2D = camera_manager.w2s(bone_manager.get_bone(Pelvis));

    float distance = location.distance(root_bone) * 0.01f;
    float box_height = abs(head.y - root.y);
    float box_width = box_height * 0.38f;

    if (distance > c_max_render_distance && cache.get_local_pawn().value_or(0)) return;

    const ImColor viscolor = player_manager.is_visible(Player.mesh_) ? c_color_visible : c_color_invisible;
    const ImColor filldecolor = player_manager.is_visible(Player.mesh_) ? c_color_visible : c_color_invisible;

    ImColor color1 = ImColor(21, 153, 87, 175);
    ImColor color2 = ImColor(21, 87, 153, 175);

    if (c_enable) {
        auto dx = head.x - (C_Overlay::c_screen_width / 2);
        auto dy = head.y - (C_Overlay::c_screen_height / 2);
        auto dist = sqrtf(dx * dx + dy * dy);

        if (dist < C_Aimbot::c_fov && dist < target_dist) {
            target_dist = dist;
            target_entity = Player.entity_;
        }
    }

    if (c_enable_esp) {
        if (c_lines) {
            line1(
                { (float)c_screen_width / 2, c_line_start == 1 ? (float)c_screen_height / 2 : c_line_start == 2 ? (float)c_screen_height : 0 },
                { (float)head_box.x, c_line_end == 1 ? (float)pelvis_2D.y : c_line_end == 2 ? (float)root_box.y : (float)head_box.y }, viscolor, line_outline_thickness + c_outlined23);
        }

        if (c_enable_box) {
            switch (c_box) {
            case 0: draw_box1(head_box.x - (box_width / 2), head_box.y, box_width, box_height, viscolor, ImColor(0, 0, 0, 100), c_outlined1); break;
            case 2: drawcorner_(head_box, box_width, box_height, viscolor, c_outlined1); break;
            }
        }
        if (c_headcircle)
        {
            draw_head(viscolor, head_bone);
        }

        if (c_radar)
        {
            ImGui::SetNextWindowPos({ 11.0f, 60.0f }); // Lowered from 60.0f to 100.0f
            ImGui::SetNextWindowSize({ 200.0f, 200.0f });
            ImGui::PushStyleColor(ImGuiCol_WindowBg, IM_COL32(11, 11, 11, 150)); // Reduced alpha for transparency (150 out of 255)
            ImGui::Begin("radar", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoResize);
            {
                ImGui::PopStyleColor();

                int ScreenX, ScreenY = 0;
                project_world_to_radar(root_bone, ScreenX, ScreenY);
                ImGui::GetWindowDrawList()->AddCircleFilled(ImVec2(ScreenX, ScreenY), 2.0f, ImColor(255, 50, 50, 255), 64);

                ImVec2 winpos = ImGui::GetWindowPos();
                ImVec2 winsize = ImGui::GetWindowSize();
                ImGui::GetWindowDrawList()->AddCircleFilled(ImVec2(winpos.x + winsize.x * 0.5f, winpos.y + winsize.y * 0.5f), 2.0f, ImColor(255, 255, 255, 255), 64);
            }
            ImGui::End();
        }



        if (c_skeleton)
        {
            draw_skeleton(Player.entity_, viscolor);
        }

       

        if (c_username) {
            std::string username_str = player_manager.get_player_name(Player.pstate_);

            if (!username_str.empty()) {
                drawoutlined_(
                    username_str,
                    ImVec2
                    (head_box.x, head_box.y - 20),
                    ImColor(255, 255, 255),
                    -20);
            }
        }

        if (c_platform) {
            std::string platform = player_manager.get_platform(Player.local_player_state_);

            drawoutlined_(
                platform,
                ImVec2(head_box.x, head_box.y - 30),
                ImColor(255, 255, 255),
                -0);
        }
        if (c_rank_esp) {
            uintptr_t habanero = device_().read<uintptr_t>(Player.local_player_state_ + 0x948);

            int32_t rankProgress = device_().read<int32_t>(habanero + 0xD8);

            std::string rankType = player_manager.get_rank(rankProgress);

            std::string finalRank = wstring_to_utf8(string_to_wstring(rankType));

            ImVec2 textSize = CalcTextSize(finalRank.c_str());

            outlined_text(
                GetBackgroundDrawList(),
                root_box.x - (textSize.x / 2), root_box.y + 41,
                player_manager.get_rank_color(rankProgress),
                finalRank.c_str());
        }

        if (c_weapon) {
           weapon_info_ weapon_info = weapon_manager.get_weapon_name(Player.entity_);

            std::string weapon_name = weapon_info.weapon_name;
          if (weapon_name == "") weapon_name = "null";

           drawoutlined_(
               weapon_name,
               ImVec2
               (root_box.x, root_box.y + 10),
              viscolor,
              15);
        }

        if (c_distance) {
            std::ostringstream oss;
            oss << std::fixed << std::setprecision(2) << distance << "m";
            std::string distance_str = oss.str();
            drawoutlined_(
                distance_str,
                ImVec2
                (
                    root_box.x, root_box.y + 5
                ),
                ImColor(255, 255, 255),
                5);
        }


        if (c_arrows) {

            float fov_radius = static_cast<float>(c_fov);
            float arrow_size = 20.0f;
            float arrow_offset = 30.0f;

            ImVec2 screen_center(C_Overlay::c_screen_width / 2, C_Overlay::c_screen_height / 2);

            auto player_screen_pos = camera_manager.w2s(head_bone);

            ImVec2 direction(player_screen_pos.x - screen_center.x, player_screen_pos.y - screen_center.y);

            float length = sqrt(direction.x * direction.x + direction.y * direction.y);
            direction.x /= length;
            direction.y /= length;

            float arrow_distance = fov_radius + arrow_offset;
            ImVec2 arrow_position(
                screen_center.x + direction.x * arrow_distance,
                screen_center.y + direction.y * arrow_distance
            );

            ImVec2 perp_direction(-direction.y, direction.x);

            ImVec2 p1(arrow_position.x, arrow_position.y);
            ImVec2 p2(
                arrow_position.x - direction.x * arrow_size + perp_direction.x * arrow_size / 2,
                arrow_position.y - direction.y * arrow_size + perp_direction.y * arrow_size / 2
            );
            ImVec2 p3(
                arrow_position.x - direction.x * arrow_size - perp_direction.x * arrow_size / 2,
                arrow_position.y - direction.y * arrow_size - perp_direction.y * arrow_size / 2
            );

            GetBackgroundDrawList()->AddTriangleFilled(p1, p2, p3, viscolor);
        }

        if (c_threat) {

            int player_kills = device_().read<int>(Player.pstate_ + 0x11C8);
            int player_level = device_().read<int>(Player.pstate_ + 0x11CC);

            float distance_component = 1.0f / distance;
            float kills_component = player_kills * 0.1f;
            float level_component = player_level * 0.05f;

            float threat_level = (distance_component + kills_component + level_component) / 3.0f;

            threat_level = clamp(threat_level, 0.0f, 1.0f);

            int threat_percentage = static_cast<int>(threat_level * 100);

            std::string threat_text = std::to_string(threat_percentage) + "%";
            outlined_text(
                GetBackgroundDrawList(),
                static_cast <int> (head_box.x - 13), static_cast<int>(head_box.y - 50),
                ImColor(255, 255, 255),
                threat_text.c_str()
            );
        }
        }
        if (!TargetedFortpawn) { TargetedFortpawn = TargetedFortPawn(); }
        if (c_triggggger) {
            if (TargetedFortpawn) {
                int keyid1 = VK_LSHIFT;
                switch (c_trig_key) {
                case 0:    keyid1 = VK_LBUTTON; break;
                case 1:    keyid1 = VK_RBUTTON; break;
                case 2:    keyid1 = VK_XBUTTON2; break;
                case 3:    keyid1 = VK_XBUTTON1; break;
                case 4:    keyid1 = VK_LSHIFT; break;
                case 5:    keyid1 = VK_LCONTROL; break;
                case 6: keyid1 = VK_MENU; break;
                }

                weapon_info_ local_held_weapon = weapon_manager.get_weapon_name(cache.get_local_pawn().value_or(0));
                local_player_weapon = local_held_weapon.weapon_name;

                if (is_shotgun(local_player_weapon)) {

                    if (GetAsyncKeyState(keyid1)) {
                        float distance = location.distance(root_bone) * 0.01f;
                        if (distance <= max_trig_distance) {

                            if (has_clicked) {
                                tb_begin = std::chrono::steady_clock::now();
                                has_clicked = false;
                            }

                            tb_end = std::chrono::steady_clock::now();
                            tb_time_since = std::chrono::duration_cast<std::chrono::milliseconds>(tb_end - tb_begin).count();

                            if (tb_time_since >= trig_delay) {
                                TargetedFortpawn = NULL;
                                mouse_click();
                                has_clicked = true;
                            }
                        }
                    }
                }
            }
        }
}

auto actor_loop() -> void {
    SPOOF_FUNC;

    auto& cache = GameCache::Cache::getInstance();

    target_dist = FLT_MAX;
    target_entity = NULL;

    utilites_manager.render_elements();

    // Debug overlay - shows all cached pointers and key values on screen
    if (debug) {
        ImDrawList* dl = ImGui::GetBackgroundDrawList();
        float y = 50.0f;
        float x = 10.0f;
        float line_h = 16.0f;
        ImU32 label_col = IM_COL32(180, 130, 255, 255);
        ImU32 val_col = IM_COL32(255, 255, 255, 255);
        ImU32 good_col = IM_COL32(80, 255, 80, 255);
        ImU32 bad_col = IM_COL32(255, 80, 80, 255);
        ImU32 header_col = IM_COL32(140, 82, 255, 255);

        auto draw_debug = [&](const char* label, const char* fmt, ...) {
            char buf[256];
            va_list args;
            va_start(args, fmt);
            vsnprintf(buf, sizeof(buf), fmt, args);
            va_end(args);
            dl->AddText(ImVec2(x, y), label_col, label);
            dl->AddText(ImVec2(x + 200, y), val_col, buf);
            y += line_h;
        };

        auto draw_ptr = [&](const char* label, uintptr_t ptr) {
            char buf[64];
            snprintf(buf, sizeof(buf), "0x%llX", (unsigned long long)ptr);
            dl->AddText(ImVec2(x, y), label_col, label);
            dl->AddText(ImVec2(x + 200, y), ptr ? good_col : bad_col, buf);
            y += line_h;
        };

        auto draw_header = [&](const char* text) {
            y += 4.0f;
            dl->AddText(ImVec2(x, y), header_col, text);
            y += line_h + 2.0f;
        };

        // Background panel
        float panel_w = 480.0f;
        float panel_h = 520.0f;
        dl->AddRectFilled(ImVec2(x - 5, 45), ImVec2(x + panel_w, 45 + panel_h), IM_COL32(10, 10, 12, 220), 6.0f);
        dl->AddRect(ImVec2(x - 5, 45), ImVec2(x + panel_w, 45 + panel_h), IM_COL32(140, 82, 255, 120), 6.0f);

        draw_header("--- Cache Chain (v39.50) ---");
        draw_ptr("UWorld:", cache.get_uworld().value_or(0));
        draw_ptr("GameInstance:", cache.get_game_instance().value_or(0));
        draw_ptr("GameState:", cache.get_gamestate().value_or(0));
        draw_ptr("LocalPlayer:", cache.get_local_player().value_or(0));
        draw_ptr("PlayerController:", cache.get_pcontroller().value_or(0));
        draw_ptr("LocalPawn:", cache.get_local_pawn().value_or(0));
        draw_ptr("Mesh:", cache.get_mesh().value_or(0));
        draw_ptr("PlayerState:", cache.get_pstate().value_or(0));
        draw_ptr("RootComponent:", cache.get_rcomponent().value_or(0));
        draw_ptr("PlayerArray:", cache.get_playerarray().value_or(0));
        draw_ptr("LocationPtr:", cache.get_location_ptr().value_or(0));
        draw_ptr("RotationPtr:", cache.get_rotation_ptr().value_or(0));

        draw_header("--- Player Data ---");
        draw_debug("PlayerArray Size:", "%d", cache.get_playersize().value_or(0));
        draw_debug("Entity List:", "%d", (int)entity_list.size());
        draw_debug("TeamID:", "%d", (int)cache.get_teamid().value_or(0));

        draw_header("--- Camera ---");
        draw_debug("FOV:", "%.2f", fov);
        draw_debug("Location:", "%.0f, %.0f, %.0f", location.x, location.y, location.z);
        draw_debug("Rotation:", "P=%.2f Y=%.2f", rotation.Pitch, rotation.Yaw);

        draw_header("--- World Time (is_visible) ---");
        if (cache.get_uworld().value_or(0)) {
            auto wt = device_().read<double>(cache.get_uworld().value_or(0) + 0x198);
            draw_debug("WorldTime (0x198):", "%.4f", wt);
        }
        if (cache.get_mesh().value_or(0)) {
            auto lr = device_().read<float>(cache.get_mesh().value_or(0) + 0x328);
            draw_debug("LocalMesh LRT (0x328):", "%.4f", lr);
        }

        draw_header("--- Weapon ---");
        if (cache.get_local_pawn().value_or(0)) {
            uintptr_t wpn = device_().read<uintptr_t>(cache.get_local_pawn().value_or(0) + offset_()->get_apply_offsets().CurrentWeapon());
            draw_ptr("CurrentWeapon:", wpn);
            if (wpn) {
                uintptr_t wdata = device_().read<uintptr_t>(wpn + offset_()->get_apply_offsets().WeaponData());
                draw_ptr("WeaponData:", wdata);
                float proj_speed = device_().read<float>(wpn + 0x25D4);
                float proj_grav = device_().read<float>(wpn + 0x25D8);
                draw_debug("ProjSpeed (0x25D4):", "%.2f", proj_speed);
                draw_debug("ProjGravity (0x25D8):", "%.2f", proj_grav);
            }
        }

        draw_header("--- Aimbot ---");
        draw_ptr("TargetEntity:", target_entity);
        draw_debug("TargetDist:", "%.2f", target_dist);
        draw_ptr("TargetedFortPawn:", TargetedFortpawn);
    }

    if (!cache.get_uworld().value() || entity_list.empty()) return;

    auto camera_location = location;
    for (auto& Player : entity_list) {
        draw_esp_elements(Player, camera_location);
    }

    if (c_enable && target_entity) {

        auto root_bone = bone_manager.get_bone(root);
        auto head_bone = bone_manager.get_bone(Head);
        auto root = camera_manager.w2s(fvector(root_bone.x, root_bone.y, root_bone.z - 15));
        auto head = camera_manager.w2s(head_bone);

        auto dx = head.x - (C_Overlay::c_screen_width / 2);
        auto dy = head.y - (C_Overlay::c_screen_height / 2);
        auto dist = sqrtf(dx * dx + dy * dy);

        auto closest_mesh = device_().read<std::uint64_t>(target_entity + offset_()->get_apply_offsets().mesh_());

        bone_manager.get_bone_array(closest_mesh);

        fvector hitbox;
        switch (c_hitbox) {
        case 0:
            hitbox = bone_manager.get_bone(HumanHead);
            break;
        case 1:
            hitbox = bone_manager.get_bone(Chest);
            break;
        case 2:
            hitbox = bone_manager.get_bone(Pelvis);
            break;
        case 3:
            srand((unsigned)time(NULL));
            int Random = (rand() % 4);
            switch (Random) {
            case 0:
                hitbox = bone_manager.get_bone(HumanHead);
                break;
            case 1:
                hitbox = bone_manager.get_bone(HumanNeck);
                break;
            case 2:
                hitbox = bone_manager.get_bone(HumanChest);
                break;
            case 3:
                hitbox = bone_manager.get_bone(HumanPelvis);
                break;
            }
            break;
        }

        int keyid = VK_LSHIFT;

        switch (c_aim_key) {
        case 0:	keyid = VK_LBUTTON;	break;
        case 1:	keyid = VK_RBUTTON;	break;
        case 2:	keyid = VK_XBUTTON2; break;
        case 3:	keyid = VK_XBUTTON1; break;
        case 4:	keyid = VK_LSHIFT; break;
        case 5:	keyid = VK_LCONTROL; break;
        case 6: keyid = VK_MENU; break;
        }


        fvector2d hitbox_screen = camera_manager.w2s(hitbox);


        if (c_target)
        {
            ImGui::GetBackgroundDrawList()->AddLine(ImVec2(c_screen_width, c_screen_height), ImVec2(hitbox_screen.x, hitbox_screen.y), ImColor(255, 255, 255, 255), 2);
        }

        weapon_info_ local_held_weapon = weapon_manager.get_weapon_name(cache.get_local_pawn().value_or(0));
        local_player_weapon = local_held_weapon.weapon_name;

        int AimSpeed = c_smooth;


        if (c_spinbot)
        {

            auto Mesh = device_().read<uint64_t>(cache.get_local_pawn().value_or(0) + offset_()->get_apply_offsets().mesh_());
            static auto Cached = device_().read<fvector>(Mesh + 0x140);

            if (GetAsyncKeyState(VK_LBUTTON)) {
                device_().write<fvector>(Mesh + 0x140, fvector(1, rand() % 361, 1));
            }
            else {
                device_().write<fvector>(Mesh + 0x140, Cached);
            }
        }

        if (c_prediction) {
            uintptr_t current_weapon = device_().read<uintptr_t>(cache.get_local_pawn().value_or(0) + offset_()->get_apply_offsets().CurrentWeapon());
            auto GetProjectileSpeed = device_().read<float>(current_weapon + 0x25D4);
            auto GetProjectileGravity = device_().read<float>(current_weapon + 0x25D8);
            if (GetProjectileGravity && GetProjectileSpeed && current_weapon) {
                auto tRoot = device_().read<uintptr_t>((uintptr_t)target_entity + offset_()->get_apply_offsets().root_());
                auto tVelocity = device_().read<fvector>(tRoot + offset_()->get_apply_offsets().velocity_());
                hitbox_screen = camera_manager.w2s(PredictPlayerPosition(hitbox, location.distance(hitbox), tVelocity, GetProjectileSpeed, GetProjectileGravity));
            }
        }


        if (hitbox.x != 0 || hitbox.y != 0 && (get_cross_distance(hitbox.x, hitbox.y, c_screen_width / 2, c_screen_height / 2) <= c_fov))
        {
            if (c_visible_check) {
                if (player_manager.is_visible(closest_mesh))
                {
                    if (GetAsyncKeyState(keyid)) {
                        perform(hitbox_screen);
                    }
                }
            }
            else
            {

                if (GetAsyncKeyState(keyid)) {
                    perform(hitbox_screen);
                }

            }
        }
    }
    else {
        target_dist = FLT_MAX;
        target_entity = NULL;
    }
}
