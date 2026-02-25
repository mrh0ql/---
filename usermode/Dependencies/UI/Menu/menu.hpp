#pragma once
#include "../../../Includes/includes.hpp"
#include "../Fonts/Extras/colors.h"
#include "../../../Includes/Definitions/c_definitions.hpp"
#include <d3d11.h>
#include <wrl/client.h>
#include <wincodec.h>
#include "../../D3D/d3dx9.h"
#include <d3d11.h>
#include <wrl/client.h>
#include <vector>
#include <fstream>
#include <filesystem>
#include <string>
//#include "../Renderer/c_overlay.h"
using namespace ImGui;
using namespace C_Players;
using namespace C_Aimbot;

inline BOOL WritePrivateProfileInt(LPCSTR lpAppName, LPCSTR lpKeyName, int nInteger, LPCSTR lpFileName) {
    char lpString[1024];
    sprintf_s(lpString, sizeof(lpString), TEXT("%d"), nInteger);
    return WritePrivateProfileStringA(lpAppName, lpKeyName, lpString, lpFileName);
}

inline BOOL WritePrivateProfileFloat(LPCSTR lpAppName, LPCSTR lpKeyName, float nInteger, LPCSTR lpFileName) {
    char lpString[1024];
    sprintf_s(lpString, sizeof(lpString), TEXT("%f"), nInteger);
    return WritePrivateProfileStringA(lpAppName, lpKeyName, lpString, lpFileName);
}

inline float GetPrivateProfileFloat(LPCSTR lpAppName, LPCSTR lpKeyName, FLOAT flDefault, LPCSTR lpFileName)
{
    char szData[32];
    GetPrivateProfileStringA(lpAppName, lpKeyName, std::to_string(flDefault).c_str(), szData, 32, lpFileName);
    return (float)atof(szData);
}

inline static int MyGetPrivateProfileInt(LPCSTR lpAppName, LPCSTR lpKeyName, FLOAT flDefault, LPCSTR lpFileName)
{
    char szData[32];
    GetPrivateProfileStringA(lpAppName, lpKeyName, std::to_string(flDefault).c_str(), szData, 32, lpFileName);
    return (int)atof(szData);
}

inline static void savecfg(LPCSTR path)
{
    WritePrivateProfileInt(("a"), TEXT("Aimbot"), c_enable, path);
    WritePrivateProfileInt(("a"), TEXT("Gun Configs"), rGunConfigs, path);
    WritePrivateProfileInt(("a"), TEXT("Triggerbot"), c_triggggger, path);
    WritePrivateProfileInt(("a"), TEXT("Prediction"), c_prediction, path);
    WritePrivateProfileInt(("a"), TEXT("DeadZone"), c_dead_zone, path);
    WritePrivateProfileInt(("a"), TEXT("Visible Check"), c_visible_check, path);
    WritePrivateProfileInt(("a"), TEXT("FOV Circle"), c_fov, path);
    WritePrivateProfileInt(("a"), TEXT("Aimline"), c_target, path);
    WritePrivateProfileInt(("a"), TEXT("Ignore Downed"), c_ignore_downed, path);
    WritePrivateProfileInt(("a"), TEXT("Ignore Bots"), c_ignore_bots, path);
    WritePrivateProfileInt(("a"), TEXT("Aimkey"), c_aim_key, path);
    WritePrivateProfileInt(("a"), TEXT("Trigkey"), c_trig_key, path);
    WritePrivateProfileFloat(("a"), TEXT("Triggerbot Delay"), trig_delay, path);
    WritePrivateProfileInt(("a"), TEXT("Humanization"), c_humanized, path);
    WritePrivateProfileFloat(("a"), TEXT("Smoothing0"), c_smooth, path);
    WritePrivateProfileFloat(("a"), TEXT("Smoothing1"), c_smooth, path);
    WritePrivateProfileFloat(("a"), TEXT("Smoothing2"), c_smooth, path);
    WritePrivateProfileFloat(("a"), TEXT("Smoothing3"), c_smooth, path);
    WritePrivateProfileFloat(("a"), TEXT("Smoothing4"), c_smooth, path);
    WritePrivateProfileFloat(("a"), TEXT("Smoothing5"), c_smooth, path);
    WritePrivateProfileFloat(("a"), TEXT("Fov0"), c_fov, path);
    WritePrivateProfileFloat(("a"), TEXT("Fov1"), c_fov, path);
    WritePrivateProfileFloat(("a"), TEXT("Fov2"), c_fov, path);
    WritePrivateProfileFloat(("a"), TEXT("Fov3"), c_fov, path);
    WritePrivateProfileFloat(("a"), TEXT("Fov4"), c_fov, path);
    WritePrivateProfileFloat(("a"), TEXT("Fov5"), c_fov, path);
    WritePrivateProfileFloat(("a"), TEXT("FOV Color1"), FovColor.x, path);
    WritePrivateProfileFloat(("a"), TEXT("FOV Color2"), FovColor.y, path);
    WritePrivateProfileFloat(("a"), TEXT("FOV Color3"), FovColor.z, path);
    WritePrivateProfileFloat(("a"), TEXT("FOV Color4"), FovColor.w, path);
    WritePrivateProfileFloat(("a"), TEXT("Fov Fill Color1"), FovFillColor.x, path);
    WritePrivateProfileFloat(("a"), TEXT("Fov Fill Color2"), FovFillColor.y, path);
    WritePrivateProfileFloat(("a"), TEXT("Fov Fill Color3"), FovFillColor.z, path);
    WritePrivateProfileFloat(("a"), TEXT("Fov Fill Color4"), FovFillColor.w, path);
    WritePrivateProfileFloat(("a"), TEXT("Fill Color1"), FillColorVis.x, path);
    WritePrivateProfileFloat(("a"), TEXT("Fill Color2"), FillColorVis.y, path);
    WritePrivateProfileFloat(("a"), TEXT("Fill Color3"), FillColorVis.z, path);
    WritePrivateProfileFloat(("a"), TEXT("Fill Color4"), FillColorVis.w, path);
    WritePrivateProfileFloat(("a"), TEXT("Fill ColorHid1"), FillColorHidden.x, path);
    WritePrivateProfileFloat(("a"), TEXT("Fill ColorHid2"), FillColorHidden.y, path);
    WritePrivateProfileFloat(("a"), TEXT("Fill ColorHid3"), FillColorHidden.z, path);
    WritePrivateProfileFloat(("a"), TEXT("Fill ColorHid4"), FillColorHidden.w, path);
    WritePrivateProfileFloat(("a"), TEXT("Aimline Color1"), AimlineColor.x, path);
    WritePrivateProfileFloat(("a"), TEXT("Aimline Color2"), AimlineColor.y, path);
    WritePrivateProfileFloat(("a"), TEXT("Aimline Color3"), AimlineColor.z, path);
    WritePrivateProfileFloat(("a"), TEXT("Aimline Color4"), AimlineColor.w, path);
    WritePrivateProfileInt(("b"), TEXT("Box Type"), c_box, path);
    WritePrivateProfileInt(("b"), TEXT("Skeleton"), c_skeleton, path);
    WritePrivateProfileInt(("b"), TEXT("Chams"), c_charms, path);
    WritePrivateProfileInt(("b"), TEXT("Wireframe"), c_wireframe, path);
    WritePrivateProfileInt(("b"), TEXT("Distance"), c_distance, path);
    WritePrivateProfileInt(("b"), TEXT("FPS"), C_Overlay::c_enable_vsync, path);
    WritePrivateProfileFloat(("a"), TEXT("Accent Color1"), AccentColor.x, path);
    WritePrivateProfileFloat(("a"), TEXT("Accent Color2"), AccentColor.y, path);
    WritePrivateProfileFloat(("a"), TEXT("Accent Color3"), AccentColor.z, path);
    WritePrivateProfileFloat(("a"), TEXT("Accent Color4"), AccentColor.w, path);
    WritePrivateProfileFloat(("b"), TEXT("Box Color1"), BoxColorVis.x, path);
    WritePrivateProfileFloat(("b"), TEXT("Box Color2"), BoxColorVis.y, path);
    WritePrivateProfileFloat(("b"), TEXT("Box Color3"), BoxColorVis.z, path);
    WritePrivateProfileFloat(("b"), TEXT("Box Color4"), BoxColorVis.w, path);
    WritePrivateProfileFloat(("b"), TEXT("Skeleton Color1"), SkeletonColorVis.x, path);
    WritePrivateProfileFloat(("b"), TEXT("Skeleton Color2"), SkeletonColorVis.y, path);
    WritePrivateProfileFloat(("b"), TEXT("Skeleton Color3"), SkeletonColorVis.z, path);
    WritePrivateProfileFloat(("b"), TEXT("Skeleton Color4"), SkeletonColorVis.w, path);
    WritePrivateProfileFloat(("b"), TEXT("Distance Color1"), DistanceColorVis.x, path);
    WritePrivateProfileFloat(("b"), TEXT("Distance Color2"), DistanceColorVis.y, path);
    WritePrivateProfileFloat(("b"), TEXT("Distance Color3"), DistanceColorVis.z, path);
    WritePrivateProfileFloat(("b"), TEXT("Distance Color4"), DistanceColorVis.w, path);
    WritePrivateProfileFloat(("b"), TEXT("Username Color1"), UsernameColorVis.x, path);
    WritePrivateProfileFloat(("b"), TEXT("Username Color2"), UsernameColorVis.y, path);
    WritePrivateProfileFloat(("b"), TEXT("Username Color3"), UsernameColorVis.z, path);
    WritePrivateProfileFloat(("b"), TEXT("Username Color4"), UsernameColorVis.w, path);
    WritePrivateProfileFloat(("b"), TEXT("Kills Color1"), KillsColorVis.x, path);
    WritePrivateProfileFloat(("b"), TEXT("Kills Color2"), KillsColorVis.y, path);
    WritePrivateProfileFloat(("b"), TEXT("Kills Color3"), KillsColorVis.z, path);
    WritePrivateProfileFloat(("b"), TEXT("Kills Color4"), KillsColorVis.w, path);
    WritePrivateProfileFloat(("b"), TEXT("Weapon Color1"), WeaponColorVis.x, path);
    WritePrivateProfileFloat(("b"), TEXT("Weapon Color2"), WeaponColorVis.y, path);
    WritePrivateProfileFloat(("b"), TEXT("Weapon Color3"), WeaponColorVis.z, path);
    WritePrivateProfileFloat(("b"), TEXT("Weapon Color4"), WeaponColorVis.w, path);
    WritePrivateProfileFloat(("b"), TEXT("Snapline Color1"), SnaplineColorVis.x, path);
    WritePrivateProfileFloat(("b"), TEXT("Snapline Color2"), SnaplineColorVis.y, path);
    WritePrivateProfileFloat(("b"), TEXT("Snapline Color3"), SnaplineColorVis.z, path);
    WritePrivateProfileFloat(("b"), TEXT("Snapline Color4"), SnaplineColorVis.w, path);
    WritePrivateProfileFloat(("b"), TEXT("FOVArrow Color1"), FovArrowsColorVis.x, path);
    WritePrivateProfileFloat(("b"), TEXT("FOVArrow Color2"), FovArrowsColorVis.y, path);
    WritePrivateProfileFloat(("b"), TEXT("FOVArrow Color3"), FovArrowsColorVis.z, path);
    WritePrivateProfileFloat(("b"), TEXT("FOVArrow Color4"), FovArrowsColorVis.w, path);
    WritePrivateProfileFloat(("b"), TEXT("HidBox Color1"), BoxColorHidden.x, path);
    WritePrivateProfileFloat(("b"), TEXT("HidBox Color2"), BoxColorHidden.y, path);
    WritePrivateProfileFloat(("b"), TEXT("HidBox Color3"), BoxColorHidden.z, path);
    WritePrivateProfileFloat(("b"), TEXT("HidBox Color4"), BoxColorHidden.w, path);
    WritePrivateProfileFloat(("b"), TEXT("HidSkeleton Color1"), SkeletonColorHidden.x, path);
    WritePrivateProfileFloat(("b"), TEXT("HidSkeleton Color2"), SkeletonColorHidden.y, path);
    WritePrivateProfileFloat(("b"), TEXT("HidSkeleton Color3"), SkeletonColorHidden.z, path);
    WritePrivateProfileFloat(("b"), TEXT("HidSkeleton Color4"), SkeletonColorHidden.w, path);
    WritePrivateProfileFloat(("b"), TEXT("HidDistance Color1"), DistanceColorHidden.x, path);
    WritePrivateProfileFloat(("b"), TEXT("HidDistance Color2"), DistanceColorHidden.y, path);
    WritePrivateProfileFloat(("b"), TEXT("HidDistance Color3"), DistanceColorHidden.z, path);
    WritePrivateProfileFloat(("b"), TEXT("HidDistance Color4"), DistanceColorHidden.w, path);
    WritePrivateProfileFloat(("b"), TEXT("HidUsername Color1"), UsernameColorHidden.x, path);
    WritePrivateProfileFloat(("b"), TEXT("HidUsername Color2"), UsernameColorHidden.y, path);
    WritePrivateProfileFloat(("b"), TEXT("HidUsername Color3"), UsernameColorHidden.z, path);
    WritePrivateProfileFloat(("b"), TEXT("HidUsername Color4"), UsernameColorHidden.w, path);
    WritePrivateProfileFloat(("b"), TEXT("HidSkeleton Color21"), c_color_visible.x, path);
    WritePrivateProfileFloat(("b"), TEXT("HidSkeleton Color22"), c_color_visible.y, path);
    WritePrivateProfileFloat(("b"), TEXT("HidSkeleton Color32"), c_color_visible.z, path);
    WritePrivateProfileFloat(("b"), TEXT("HidSkeleton Color42"), c_color_visible.w, path);
    WritePrivateProfileFloat(("b"), TEXT("HidSkeleton Color211"), c_color_invisible.x, path);
    WritePrivateProfileFloat(("b"), TEXT("HidSkeleton Color221"), c_color_invisible.y, path);
    WritePrivateProfileFloat(("b"), TEXT("HidSkeleton Color321"), c_color_invisible.z, path);
    WritePrivateProfileFloat(("b"), TEXT("HidSkeleton Color241"), c_color_invisible.w, path);
    WritePrivateProfileFloat(("b"), TEXT("HidKills Color1"), KillsColorHidden.x, path);
    WritePrivateProfileFloat(("b"), TEXT("HidKills Color2"), KillsColorHidden.y, path);
    WritePrivateProfileFloat(("b"), TEXT("HidKills Color3"), KillsColorHidden.z, path);
    WritePrivateProfileFloat(("b"), TEXT("HidKills Color4"), KillsColorHidden.w, path);
    WritePrivateProfileFloat(("b"), TEXT("HidWeapon Color1"), WeaponColorHidden.x, path);
    WritePrivateProfileFloat(("b"), TEXT("HidWeapon Color2"), WeaponColorHidden.y, path);
    WritePrivateProfileFloat(("b"), TEXT("HidWeapon Color3"), WeaponColorHidden.z, path);
    WritePrivateProfileFloat(("b"), TEXT("HidWeapon Color4"), WeaponColorHidden.w, path);
    WritePrivateProfileFloat(("b"), TEXT("HidSnapline Color1"), SnaplineColorHidden.x, path);
    WritePrivateProfileFloat(("b"), TEXT("HidSnapline Color2"), SnaplineColorHidden.y, path);
    WritePrivateProfileFloat(("b"), TEXT("HidSnapline Color3"), SnaplineColorHidden.z, path);
    WritePrivateProfileFloat(("b"), TEXT("HidSnapline Color4"), SnaplineColorHidden.w, path);
    WritePrivateProfileFloat(("b"), TEXT("HidFOVArrow Color1"), FovArrowsColorHidden.x, path);
    WritePrivateProfileFloat(("b"), TEXT("HidFOVArrow Color2"), FovArrowsColorHidden.y, path);
    WritePrivateProfileFloat(("b"), TEXT("HidFOVArrow Color3"), FovArrowsColorHidden.z, path);
    WritePrivateProfileFloat(("b"), TEXT("HidFOVArrow Color4"), FovArrowsColorHidden.w, path);

    WritePrivateProfileInt(("b"), TEXT("Render"), c_max_render_distance, path);
    WritePrivateProfileInt(("b"), TEXT("Head Circle"), c_headcircle, path);
    WritePrivateProfileInt(("b"), TEXT("Weapon Name"), c_weapon, path);
    WritePrivateProfileInt(("b"), TEXT("Platform Name"), c_platform, path);
    WritePrivateProfileInt(("b"), TEXT("Username"), c_username, path);
    WritePrivateProfileInt(("b"), TEXT("Rank"), c_rank_esp, path);
    WritePrivateProfileInt(("b"), TEXT("FOV Arrows"), c_arrows, path);
    WritePrivateProfileInt(("b"), TEXT("Snapline Position"), c_lines, path);
    WritePrivateProfileFloat(("b"), TEXT("ESP Distance"), c_distance, path);
    WritePrivateProfileInt(("b"), TEXT("Hitbox"), c_hitbox, path);
    WritePrivateProfileInt(("a"), TEXT("Risk"), c_threat, path);
}

inline static void loadcfg(LPCSTR path)
{
    c_color_invisible.x = GetPrivateProfileFloat(("a"), TEXT("HidSkeleton Color211"), c_color_invisible.x, path);
    c_color_invisible.y = GetPrivateProfileFloat(("a"), TEXT("HidSkeleton Color221"), c_color_invisible.y, path);
    c_color_invisible.z = GetPrivateProfileFloat(("a"), TEXT("HidSkeleton Color321"), c_color_invisible.z, path);
    c_color_invisible.w = GetPrivateProfileFloat(("a"), TEXT("HidSkeleton Color241"), c_color_invisible.w, path);
    c_threat = MyGetPrivateProfileInt(("a"), TEXT("Risk"), c_threat, path);
    c_enable = MyGetPrivateProfileInt(("a"), TEXT("Aimbot"), c_enable, path);
    c_hitbox = MyGetPrivateProfileInt(("a"), TEXT("Hitbox"), c_hitbox, path);
    rGunConfigs = MyGetPrivateProfileInt(("a"), TEXT("Gun Configs"), rGunConfigs, path);
    c_triggggger = MyGetPrivateProfileInt(("a"), TEXT("Triggerbot"), c_triggggger, path);
    c_prediction = MyGetPrivateProfileInt(("a"), TEXT("Prediction"), c_prediction, path);
    c_visible_check = MyGetPrivateProfileInt(("a"), TEXT("Visible Check"), c_visible_check, path);
    c_fov = MyGetPrivateProfileInt(("a"), TEXT("FOV Circle"), c_fov, path);
    c_target = MyGetPrivateProfileInt(("a"), TEXT("Aimline"), c_target, path);
    c_color_visible.x = GetPrivateProfileFloat(("a"), TEXT("HidSkeleton Color21"), c_color_visible.x, path);
    c_color_visible.y = GetPrivateProfileFloat(("a"), TEXT("HidSkeleton Color22"), c_color_visible.y, path);
    c_color_visible.z = GetPrivateProfileFloat(("a"), TEXT("HidSkeleton Color32"), c_color_visible.z, path);
    c_color_visible.w = GetPrivateProfileFloat(("a"), TEXT("HidSkeleton Color42"), c_color_visible.w, path);
    c_ignore_downed = MyGetPrivateProfileInt(("a"), TEXT("Ignore Downed"), c_ignore_downed, path);
    c_ignore_bots = MyGetPrivateProfileInt(("a"), TEXT("Ignore Bots"), c_ignore_bots, path);
    FovColor.x = GetPrivateProfileFloat(("a"), TEXT("FOV Color1"), FovColor.x, path);
    FovColor.y = GetPrivateProfileFloat(("a"), TEXT("FOV Color2"), FovColor.y, path);
    FovColor.z = GetPrivateProfileFloat(("a"), TEXT("FOV Color3"), FovColor.z, path);
    FovColor.w = GetPrivateProfileFloat(("a"), TEXT("FOV Color4"), FovColor.w, path);
    FovFillColor.x = GetPrivateProfileFloat(("a"), TEXT("Fov Fill Color1"), FovFillColor.x, path);
    FovFillColor.y = GetPrivateProfileFloat(("a"), TEXT("Fov Fill Color2"), FovFillColor.y, path);
    FovFillColor.z = GetPrivateProfileFloat(("a"), TEXT("Fov Fill Color3"), FovFillColor.z, path);
    FovFillColor.w = GetPrivateProfileFloat(("a"), TEXT("Fov Fill Color4"), FovFillColor.w, path);
    FillColorVis.x = GetPrivateProfileFloat(("a"), TEXT("Fill Color1"), FillColorVis.x, path);
    FillColorVis.y = GetPrivateProfileFloat(("a"), TEXT("Fill Color2"), FillColorVis.y, path);
    FillColorVis.z = GetPrivateProfileFloat(("a"), TEXT("Fill Color3"), FillColorVis.z, path);
    FillColorVis.w = GetPrivateProfileFloat(("a"), TEXT("Fill Color4"), FillColorVis.w, path);
    FillColorHidden.x = GetPrivateProfileFloat(("a"), TEXT("Fill ColorHid1"), FillColorHidden.x, path);
    FillColorHidden.y = GetPrivateProfileFloat(("a"), TEXT("Fill ColorHid2"), FillColorHidden.y, path);
    FillColorHidden.z = GetPrivateProfileFloat(("a"), TEXT("Fill ColorHid3"), FillColorHidden.z, path);
    FillColorHidden.w = GetPrivateProfileFloat(("a"), TEXT("Fill ColorHid4"), FillColorHidden.w, path);
    AimlineColor.x = GetPrivateProfileFloat(("a"), TEXT("Aimline Color1"), AimlineColor.x, path);
    AimlineColor.y = GetPrivateProfileFloat(("a"), TEXT("Aimline Color2"), AimlineColor.y, path);
    AimlineColor.z = GetPrivateProfileFloat(("a"), TEXT("Aimline Color3"), AimlineColor.z, path);
    AimlineColor.w = GetPrivateProfileFloat(("a"), TEXT("Aimline Color4"), AimlineColor.w, path);
    c_aim_key = MyGetPrivateProfileInt(("a"), TEXT("Aimkey"), c_aim_key, path);
    c_trig_key = MyGetPrivateProfileInt(("a"), TEXT("Trigkey"), c_trig_key, path);
    trig_delay = GetPrivateProfileFloat(("a"), TEXT("Triggerbot Delay"), trig_delay, path);
    c_humanized = GetPrivateProfileFloat(("a"), TEXT("Humanization"), c_humanized, path);
    c_smooth = GetPrivateProfileFloat(("a"), TEXT("Smoothing0"), c_smooth, path);
    c_smooth = GetPrivateProfileFloat(("a"), TEXT("Smoothing1"), c_smooth, path);
    c_smooth = GetPrivateProfileFloat(("a"), TEXT("Smoothing2"), c_smooth, path);
    c_smooth = GetPrivateProfileFloat(("a"), TEXT("Smoothing3"), c_smooth, path);
    c_smooth = GetPrivateProfileFloat(("a"), TEXT("Smoothing4"), c_smooth, path);
    c_smooth = GetPrivateProfileFloat(("a"), TEXT("Smoothing5"), c_smooth, path);
    c_fov = GetPrivateProfileFloat(("a"), TEXT("Fov0"), c_fov, path);
    c_fov = GetPrivateProfileFloat(("a"), TEXT("Fov1"), c_fov, path);
    c_fov = GetPrivateProfileFloat(("a"), TEXT("Fov2"), c_fov, path);
    c_fov = GetPrivateProfileFloat(("a"), TEXT("Fov3"), c_fov, path);
    c_fov = GetPrivateProfileFloat(("a"), TEXT("Fov4"), c_fov, path);
    c_fov = GetPrivateProfileFloat(("a"), TEXT("Fov5"), c_fov, path);
    c_dead_zone = MyGetPrivateProfileInt(("b"), TEXT("DeadZone"), c_dead_zone, path);
    c_max_render_distance = MyGetPrivateProfileInt(("b"), TEXT("Render"), c_max_render_distance, path);
    c_box = MyGetPrivateProfileInt(("b"), TEXT("Box Type"), c_box, path);
    c_skeleton = MyGetPrivateProfileInt(("b"), TEXT("Skeleton"), c_skeleton, path);
    c_charms = MyGetPrivateProfileInt(("b"), TEXT("Chams"), c_charms, path);
    c_wireframe = MyGetPrivateProfileInt(("b"), TEXT("Wireframe"), c_wireframe, path);
    c_distance = MyGetPrivateProfileInt(("b"), TEXT("Distance"), c_distance, path);
    C_Overlay::c_enable_vsync = MyGetPrivateProfileInt(("b"), TEXT("FPS"), C_Overlay::c_enable_vsync, path);
    AccentColor.x = GetPrivateProfileFloat(("a"), TEXT("Accent Color1"), AccentColor.x, path);
    AccentColor.y = GetPrivateProfileFloat(("a"), TEXT("Accent Color2"), AccentColor.y, path);
    AccentColor.z = GetPrivateProfileFloat(("a"), TEXT("Accent Color3"), AccentColor.z, path);
    AccentColor.w = GetPrivateProfileFloat(("a"), TEXT("Accent Color4"), AccentColor.w, path);
    BoxColorVis.x = GetPrivateProfileFloat(("b"), TEXT("Box Color1"), BoxColorVis.x, path);
    BoxColorVis.y = GetPrivateProfileFloat(("b"), TEXT("Box Color2"), BoxColorVis.y, path);
    BoxColorVis.z = GetPrivateProfileFloat(("b"), TEXT("Box Color3"), BoxColorVis.z, path);
    BoxColorVis.w = GetPrivateProfileFloat(("b"), TEXT("Box Color4"), BoxColorVis.w, path);
    SkeletonColorVis.x = GetPrivateProfileFloat(("b"), TEXT("Skeleton Color1"), SkeletonColorVis.x, path);
    SkeletonColorVis.y = GetPrivateProfileFloat(("b"), TEXT("Skeleton Color2"), SkeletonColorVis.y, path);
    SkeletonColorVis.z = GetPrivateProfileFloat(("b"), TEXT("Skeleton Color3"), SkeletonColorVis.z, path);
    SkeletonColorVis.w = GetPrivateProfileFloat(("b"), TEXT("Skeleton Color4"), SkeletonColorVis.w, path);
    DistanceColorVis.x = GetPrivateProfileFloat(("b"), TEXT("Distance Color1"), DistanceColorVis.x, path);
    DistanceColorVis.y = GetPrivateProfileFloat(("b"), TEXT("Distance Color2"), DistanceColorVis.y, path);
    DistanceColorVis.z = GetPrivateProfileFloat(("b"), TEXT("Distance Color3"), DistanceColorVis.z, path);
    DistanceColorVis.w = GetPrivateProfileFloat(("b"), TEXT("Distance Color4"), DistanceColorVis.w, path);
    UsernameColorVis.x = GetPrivateProfileFloat(("b"), TEXT("Username Color1"), UsernameColorVis.x, path);
    UsernameColorVis.y = GetPrivateProfileFloat(("b"), TEXT("Username Color2"), UsernameColorVis.y, path);
    UsernameColorVis.z = GetPrivateProfileFloat(("b"), TEXT("Username Color3"), UsernameColorVis.z, path);
    UsernameColorVis.w = GetPrivateProfileFloat(("b"), TEXT("Username Color4"), UsernameColorVis.w, path);
    KillsColorVis.x = GetPrivateProfileFloat(("b"), TEXT("Kills Color1"), KillsColorVis.x, path);
    KillsColorVis.y = GetPrivateProfileFloat(("b"), TEXT("Kills Color2"), KillsColorVis.y, path);
    KillsColorVis.z = GetPrivateProfileFloat(("b"), TEXT("Kills Color3"), KillsColorVis.z, path);
    KillsColorVis.w = GetPrivateProfileFloat(("b"), TEXT("Kills Color4"), KillsColorVis.w, path);
    WeaponColorVis.x = GetPrivateProfileFloat(("b"), TEXT("Weapon Color1"), WeaponColorVis.x, path);
    WeaponColorVis.y = GetPrivateProfileFloat(("b"), TEXT("Weapon Color2"), WeaponColorVis.y, path);
    WeaponColorVis.z = GetPrivateProfileFloat(("b"), TEXT("Weapon Color3"), WeaponColorVis.z, path);
    WeaponColorVis.w = GetPrivateProfileFloat(("b"), TEXT("Weapon Color4"), WeaponColorVis.w, path);
    SnaplineColorVis.x = GetPrivateProfileFloat(("b"), TEXT("Snapline Color1"), SnaplineColorVis.x, path);
    SnaplineColorVis.y = GetPrivateProfileFloat(("b"), TEXT("Snapline Color2"), SnaplineColorVis.y, path);
    SnaplineColorVis.z = GetPrivateProfileFloat(("b"), TEXT("Snapline Color3"), SnaplineColorVis.z, path);
    SnaplineColorVis.w = GetPrivateProfileFloat(("b"), TEXT("Snapline Color4"), SnaplineColorVis.w, path);
    FovArrowsColorVis.x = GetPrivateProfileFloat(("b"), TEXT("FOVArrow Color1"), FovArrowsColorVis.x, path);
    FovArrowsColorVis.y = GetPrivateProfileFloat(("b"), TEXT("FOVArrow Color2"), FovArrowsColorVis.y, path);
    FovArrowsColorVis.z = GetPrivateProfileFloat(("b"), TEXT("FOVArrow Color3"), FovArrowsColorVis.z, path);
    FovArrowsColorVis.w = GetPrivateProfileFloat(("b"), TEXT("FOVArrow Color4"), FovArrowsColorVis.w, path);
    DistanceColorHidden.x = GetPrivateProfileFloat(("b"), TEXT("HidDistance Color1"), DistanceColorHidden.x, path);
    DistanceColorHidden.y = GetPrivateProfileFloat(("b"), TEXT("HidDistance Color2"), DistanceColorHidden.y, path);
    DistanceColorHidden.z = GetPrivateProfileFloat(("b"), TEXT("HidDistance Color3"), DistanceColorHidden.z, path);
    DistanceColorHidden.w = GetPrivateProfileFloat(("b"), TEXT("HidDistance Color4"), DistanceColorHidden.w, path);
    UsernameColorHidden.x = GetPrivateProfileFloat(("b"), TEXT("HidUsername Color1"), UsernameColorHidden.x, path);
    UsernameColorHidden.y = GetPrivateProfileFloat(("b"), TEXT("HidUsername Color2"), UsernameColorHidden.y, path);
    UsernameColorHidden.z = GetPrivateProfileFloat(("b"), TEXT("HidUsername Color3"), UsernameColorHidden.z, path);
    UsernameColorHidden.w = GetPrivateProfileFloat(("b"), TEXT("HidUsername Color4"), UsernameColorHidden.w, path);
    KillsColorHidden.x = GetPrivateProfileFloat(("b"), TEXT("HidKills Color1"), KillsColorHidden.x, path);
    KillsColorHidden.y = GetPrivateProfileFloat(("b"), TEXT("HidKills Color2"), KillsColorHidden.y, path);
    KillsColorHidden.z = GetPrivateProfileFloat(("b"), TEXT("HidKills Color3"), KillsColorHidden.z, path);
    KillsColorHidden.w = GetPrivateProfileFloat(("b"), TEXT("HidKills Color4"), KillsColorHidden.w, path);
    WeaponColorHidden.x = GetPrivateProfileFloat(("b"), TEXT("HidWeapon Color1"), WeaponColorHidden.x, path);
    WeaponColorHidden.y = GetPrivateProfileFloat(("b"), TEXT("HidWeapon Color2"), WeaponColorHidden.y, path);
    WeaponColorHidden.z = GetPrivateProfileFloat(("b"), TEXT("HidWeapon Color3"), WeaponColorHidden.z, path);
    WeaponColorHidden.w = GetPrivateProfileFloat(("b"), TEXT("HidWeapon Color4"), WeaponColorHidden.w, path);
    SnaplineColorHidden.x = GetPrivateProfileFloat(("b"), TEXT("HidSnapline Color1"), SnaplineColorHidden.x, path);
    SnaplineColorHidden.y = GetPrivateProfileFloat(("b"), TEXT("HidSnapline Color2"), SnaplineColorHidden.y, path);
    SnaplineColorHidden.z = GetPrivateProfileFloat(("b"), TEXT("HidSnapline Color3"), SnaplineColorHidden.z, path);
    SnaplineColorHidden.w = GetPrivateProfileFloat(("b"), TEXT("HidSnapline Color4"), SnaplineColorHidden.w, path);
    FovArrowsColorHidden.x = GetPrivateProfileFloat(("b"), TEXT("HidFOVArrow Color1"), FovArrowsColorHidden.x, path);
    FovArrowsColorHidden.y = GetPrivateProfileFloat(("b"), TEXT("HidFOVArrow Color2"), FovArrowsColorHidden.y, path);
    FovArrowsColorHidden.z = GetPrivateProfileFloat(("b"), TEXT("HidFOVArrow Color3"), FovArrowsColorHidden.z, path);
    FovArrowsColorHidden.w = GetPrivateProfileFloat(("b"), TEXT("HidFOVArrow Color4"), FovArrowsColorHidden.w, path);
    BoxColorHidden.x = GetPrivateProfileFloat(("b"), TEXT("HidBox Color1"), BoxColorHidden.x, path);
    BoxColorHidden.y = GetPrivateProfileFloat(("b"), TEXT("HidBox Color2"), BoxColorHidden.y, path);
    BoxColorHidden.z = GetPrivateProfileFloat(("b"), TEXT("HidBox Color3"), BoxColorHidden.z, path);
    BoxColorHidden.w = GetPrivateProfileFloat(("b"), TEXT("HidBox Color4"), BoxColorHidden.w, path);
    c_hitbox = MyGetPrivateProfileInt(("b"), TEXT("Hitbox"), c_hitbox, path);
    c_headcircle = MyGetPrivateProfileInt(("b"), TEXT("Head Circle"), c_headcircle, path);
    c_weapon = MyGetPrivateProfileInt(("b"), TEXT("Weapon Name"), c_weapon, path);
    c_platform = MyGetPrivateProfileInt(("b"), TEXT("Platform Name"), c_platform, path);
    c_username = MyGetPrivateProfileInt(("b"), TEXT("Username"), c_username, path);
    c_rank_esp = MyGetPrivateProfileInt(("b"), TEXT("Rank"), c_rank_esp, path);
    c_arrows = MyGetPrivateProfileInt(("b"), TEXT("FOV Arrows"), c_arrows, path);
    c_lines = MyGetPrivateProfileInt(("b"), TEXT("Snapline Position"), c_lines, path);
    c_distance = GetPrivateProfileFloat(("b"), TEXT("ESP Distance"), c_distance, path);
    c_enable_box = GetPrivateProfileFloat(("b"), TEXT("c_enable_box"), c_enable_box, path);
}

inline void c_draw_fov()
{
    SPOOF_FUNC;
    if (c_circle) {
        GetBackgroundDrawList()->AddCircle(ImVec2(C_Overlay::c_screen_width / 2, C_Overlay::c_screen_height / 2), c_fov, ImColor(255, 255, 255), 64, 1);
    }
}

// ============================================================
//  PURPLE THEME + MODERN MENU
// ============================================================

// Accent colors - purple palette
#define PURPLE_MAIN     IM_COL32(140, 82, 255, 255)    // #8C52FF
#define PURPLE_LIGHT    IM_COL32(170, 120, 255, 255)    // #AA78FF
#define PURPLE_DARK     IM_COL32(90, 50, 180, 255)      // #5A32B4
#define PURPLE_GLOW     IM_COL32(140, 82, 255, 40)      // glow/hover fill
#define PURPLE_DIM      IM_COL32(140, 82, 255, 15)      // very subtle

// Background palette
#define BG_DARKEST      IM_COL32(10, 10, 14, 255)       // window bg
#define BG_SIDEBAR      IM_COL32(14, 14, 20, 255)       // sidebar
#define BG_CHILD        IM_COL32(18, 18, 26, 255)       // child panels
#define BG_FRAME        IM_COL32(24, 24, 34, 255)       // input frames
#define BG_FRAME_HOV    IM_COL32(30, 30, 42, 255)       // hovered frames
#define BG_FRAME_ACT    IM_COL32(36, 34, 50, 255)       // active frames
#define BORDER_COL      IM_COL32(32, 30, 44, 255)       // borders
#define TEXT_BRIGHT     IM_COL32(230, 225, 240, 255)     // main text
#define TEXT_DIM        IM_COL32(100, 95, 120, 255)      // dim text
#define TEXT_MID        IM_COL32(160, 155, 175, 255)     // mid text

namespace idfk {
    inline bool bShowMenu = true;
    inline int m_MenuTab = 0;
}

inline static void apply_theme() {
    SPOOF_FUNC;
    auto& s = ImGui::GetStyle();

    s.WindowPadding     = ImVec2(0, 0);
    s.FramePadding      = ImVec2(10, 6);
    s.ItemSpacing       = ImVec2(10, 8);
    s.ItemInnerSpacing  = ImVec2(8, 4);
    s.IndentSpacing     = 20.0f;

    s.WindowBorderSize  = 0.0f;
    s.ChildBorderSize   = 1.0f;
    s.FrameBorderSize   = 0.0f;
    s.PopupBorderSize   = 1.0f;

    s.WindowRounding    = 12.0f;
    s.ChildRounding     = 8.0f;
    s.FrameRounding     = 6.0f;
    s.PopupRounding     = 8.0f;
    s.ScrollbarRounding = 8.0f;
    s.GrabRounding      = 6.0f;
    s.TabRounding       = 6.0f;

    s.ScrollbarSize     = 10.0f;
    s.GrabMinSize       = 10.0f;

    auto* c = s.Colors;
    c[ImGuiCol_WindowBg]            = ImColor(BG_DARKEST);
    c[ImGuiCol_ChildBg]             = ImColor(BG_CHILD);
    c[ImGuiCol_PopupBg]             = ImColor(20, 18, 28);
    c[ImGuiCol_Text]                = ImColor(TEXT_BRIGHT);
    c[ImGuiCol_TextDisabled]        = ImColor(TEXT_DIM);
    c[ImGuiCol_Border]              = ImColor(BORDER_COL);
    c[ImGuiCol_BorderShadow]        = ImColor(0, 0, 0, 0);
    c[ImGuiCol_FrameBg]             = ImColor(BG_FRAME);
    c[ImGuiCol_FrameBgHovered]      = ImColor(BG_FRAME_HOV);
    c[ImGuiCol_FrameBgActive]       = ImColor(BG_FRAME_ACT);
    c[ImGuiCol_TitleBg]             = ImColor(BG_DARKEST);
    c[ImGuiCol_TitleBgActive]       = ImColor(BG_DARKEST);
    c[ImGuiCol_TitleBgCollapsed]    = ImColor(BG_DARKEST);
    c[ImGuiCol_ScrollbarBg]         = ImColor(BG_DARKEST);
    c[ImGuiCol_ScrollbarGrab]       = ImColor(50, 45, 70);
    c[ImGuiCol_ScrollbarGrabHovered]= ImColor(70, 60, 100);
    c[ImGuiCol_ScrollbarGrabActive] = ImColor(PURPLE_MAIN);
    c[ImGuiCol_Button]              = ImColor(BG_FRAME);
    c[ImGuiCol_ButtonHovered]       = ImColor(BG_FRAME_HOV);
    c[ImGuiCol_ButtonActive]        = ImColor(PURPLE_DARK);
    c[ImGuiCol_CheckMark]           = ImColor(PURPLE_MAIN);
    c[ImGuiCol_SliderGrab]          = ImColor(PURPLE_MAIN);
    c[ImGuiCol_SliderGrabActive]    = ImColor(PURPLE_LIGHT);
    c[ImGuiCol_Header]              = ImColor(28, 26, 38);
    c[ImGuiCol_HeaderHovered]       = ImColor(38, 34, 52);
    c[ImGuiCol_HeaderActive]        = ImColor(48, 42, 66);
    c[ImGuiCol_Separator]           = ImColor(BORDER_COL);
    c[ImGuiCol_SeparatorHovered]    = ImColor(PURPLE_MAIN);
    c[ImGuiCol_SeparatorActive]     = ImColor(PURPLE_MAIN);
    c[ImGuiCol_ResizeGrip]          = ImColor(0, 0, 0, 0);
    c[ImGuiCol_ResizeGripHovered]   = ImColor(0, 0, 0, 0);
    c[ImGuiCol_ResizeGripActive]    = ImColor(0, 0, 0, 0);
    c[ImGuiCol_Tab]                 = ImColor(BG_CHILD);
    c[ImGuiCol_TabHovered]          = ImColor(38, 34, 52);
    c[ImGuiCol_TabActive]           = ImColor(48, 42, 66);
}

// ---- Helpers for consistent layout ----
inline void SectionLabel(const char* text) {
    ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(140/255.f, 82/255.f, 1.0f, 1.0f));
    ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 2);
    ImGui::Text("%s", text);
    ImGui::PopStyleColor();
    ImGui::Spacing();
}

inline void SectionSep() {
    ImGui::Spacing();
    ImGui::PushStyleColor(ImGuiCol_Separator, ImVec4(140/255.f, 82/255.f, 1.0f, 0.2f));
    ImGui::Separator();
    ImGui::PopStyleColor();
    ImGui::Spacing();
}

inline bool Chk(const char* label, bool* v) {
    ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 6);
    return ImGui::Checkbox(label, v);
}

inline bool Sld(const char* label, float* v, float mn, float mx) {
    ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 6);
    ImGui::PushItemWidth(-18);
    bool r = ImGui::SliderFloat(label, v, mn, mx);
    ImGui::PopItemWidth();
    return r;
}

inline bool SldI(const char* label, int* v, int mn, int mx) {
    ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 6);
    ImGui::PushItemWidth(-18);
    bool r = ImGui::SliderInt(label, v, mn, mx);
    ImGui::PopItemWidth();
    return r;
}

inline bool Cmb(const char* label, int* v, const char* items) {
    ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 6);
    ImGui::PushItemWidth(-18);
    bool r = ImGui::Combo(label, v, items);
    ImGui::PopItemWidth();
    return r;
}

// ============================================================
//  MAIN MENU
// ============================================================
inline void draw_menu() {
    SPOOF_FUNC;
    apply_theme();

    constexpr float W = 760.0f;
    constexpr float H = 500.0f;
    constexpr float SIDE = 150.0f;
    constexpr float PAD = 16.0f;

    enum Tab { Combat, Visuals, Trigger, Misc, Settings };
    const char* tabs[] = { "Combat", "Visuals", "Trigger", "Misc", "Settings" };
    constexpr int tab_n = 5;

    ImGui::SetNextWindowSize(ImVec2(W, H));
    ImGui::Begin(_("##MainWnd"), 0,
        ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar |
        ImGuiWindowFlags_NoResize   | ImGuiWindowFlags_NoCollapse);
    {
        auto* dl = ImGui::GetWindowDrawList();
        ImVec2 p = ImGui::GetWindowPos();

        // ---- Top gradient bar ----
        for (int i = 0; i < 3; i++) {
            float alpha = 1.0f - i * 0.3f;
            dl->AddRectFilledMultiColor(
                ImVec2(p.x, p.y + i),
                ImVec2(p.x + W, p.y + i + 1),
                IM_COL32(140, 82, 255, (int)(255*alpha)),
                IM_COL32(200, 100, 255, (int)(255*alpha)),
                IM_COL32(200, 100, 255, (int)(255*alpha)),
                IM_COL32(140, 82, 255, (int)(255*alpha))
            );
        }

        // ---- Sidebar ----
        dl->AddRectFilled(
            ImVec2(p.x, p.y + 3),
            ImVec2(p.x + SIDE, p.y + H),
            BG_SIDEBAR, 0.0f
        );
        // sidebar right edge
        dl->AddLine(
            ImVec2(p.x + SIDE, p.y + 3),
            ImVec2(p.x + SIDE, p.y + H),
            BORDER_COL
        );

        // ---- Title ----
        dl->AddText(ImVec2(p.x + 22, p.y + 18), PURPLE_MAIN, "Immortal");
        dl->AddText(ImVec2(p.x + 22, p.y + 36), TEXT_DIM, "fortnite");

        // ---- Sidebar separator under title ----
        dl->AddLine(
            ImVec2(p.x + 16, p.y + 58),
            ImVec2(p.x + SIDE - 16, p.y + 58),
            IM_COL32(50, 45, 70, 120)
        );

        // ---- Tab buttons ----
        float ty_start = 68.0f;
        float th = 36.0f;
        float tgap = 3.0f;

        for (int i = 0; i < tab_n; i++) {
            float ty = ty_start + i * (th + tgap);
            bool active = (idfk::m_MenuTab == i);

            ImVec2 tmin(p.x + 10, p.y + ty);
            ImVec2 tmax(p.x + SIDE - 10, p.y + ty + th);

            ImGui::SetCursorPos(ImVec2(10, ty));
            char id[16]; sprintf_s(id, "##t%d", i);
            if (ImGui::InvisibleButton(id, ImVec2(SIDE - 20, th)))
                idfk::m_MenuTab = i;
            bool hov = ImGui::IsItemHovered();

            if (active) {
                // Active: purple pill + subtle fill
                dl->AddRectFilled(
                    ImVec2(p.x + 5, p.y + ty + 8),
                    ImVec2(p.x + 8, p.y + ty + th - 8),
                    PURPLE_MAIN, 4.0f
                );
                dl->AddRectFilled(tmin, tmax, PURPLE_GLOW, 6.0f);
            } else if (hov) {
                dl->AddRectFilled(tmin, tmax, IM_COL32(255, 255, 255, 8), 6.0f);
            }

            ImU32 tcol = active  ? IM_COL32(220, 200, 255, 255) :
                         hov     ? IM_COL32(180, 170, 200, 255) :
                                   TEXT_DIM;
            ImVec2 ts = ImGui::CalcTextSize(tabs[i]);
            dl->AddText(
                ImVec2(p.x + 28, p.y + ty + (th - ts.y) * 0.5f),
                tcol, tabs[i]
            );
        }

        // ---- Bottom info in sidebar ----
        dl->AddLine(
            ImVec2(p.x + 16, p.y + H - 50),
            ImVec2(p.x + SIDE - 16, p.y + H - 50),
            IM_COL32(50, 45, 70, 80)
        );
        dl->AddText(ImVec2(p.x + 20, p.y + H - 40), TEXT_DIM, "v39.30");
        char fps_buf[32];
        sprintf_s(fps_buf, "%.0f fps", ImGui::GetIO().Framerate);
        dl->AddText(ImVec2(p.x + 20, p.y + H - 24), TEXT_DIM, fps_buf);

        // ---- Content area ----
        float cx = SIDE + PAD;
        float cy = 3 + PAD;
        float cw = W - SIDE - PAD * 2;
        float ch = H - 3 - PAD * 2;
        float half_w = (cw - 14) * 0.5f;

        ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 8.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(16, 14));

        switch (idfk::m_MenuTab) {

        // ============================
        //  COMBAT
        // ============================
        case Tab::Combat:
        {
            ImGui::SetCursorPos(ImVec2(cx, cy));
            ImGui::BeginChild("##cb_l", ImVec2(half_w, ch), true);
            {
                SectionLabel("Aimbot");
                Chk("Enable##aim", &c_enable);

                if (c_enable) {
                    ImGui::Spacing();
                    Chk("Dead Zone", &c_dead_zone);
                    Chk("Humanization", &c_humanized);
                    Chk("Prediction", &c_prediction);
                    Chk("Ignore Knocked", &c_knocked);
                    Chk("Visible Check", &c_visible_check);
                    Chk("Show FOV Circle", &c_circle);
                }

                SectionSep();
                SectionLabel("Keybinds");
                Cmb("Aim Key", &c_aim_key, "LMB\0RMB\0MB2\0MB1\0LShift\0LCtrl\0LAlt\0\0");
                ImGui::Spacing();
                Cmb("Input", &c_aim1, "Input\0Mouse\0Humanized\0\0");
                ImGui::Spacing();
                Cmb("Hitbox", &c_hitbox, "Head\0Neck\0Pelvis\0Random\0\0");
            }
            ImGui::EndChild();

            ImGui::SetCursorPos(ImVec2(cx + half_w + 14, cy));
            ImGui::BeginChild("##cb_r", ImVec2(half_w, ch), true);
            {
                SectionLabel("Tuning");
                Sld("Smoothness", &c_smooth, 1.0f, 20.0f);
                ImGui::Spacing();
                Sld("FOV Size", &c_fov, 1.0f, 300.0f);
                ImGui::Spacing();
                Sld("Dead Zone Val", &c_custom_dead_zone, 0.0f, 1.0f);
                ImGui::Spacing();
                SldI("Max Distance", &max_trig_distance, 0, 50);

                SectionSep();
                SectionLabel("Weapon Configs");

                ImGui::Text("Shotgun");
                Chk("Prediction##sg", &weapon_cfg::shotgun::rPrediction);
                SldI("Smooth##sg", &weapon_cfg::shotgun::rSmooth, 1, 20);
                SldI("FOV##sg", &weapon_cfg::shotgun::rFovSize, 1, 1000);

                ImGui::Spacing();
                ImGui::Text("SMG");
                Chk("Prediction##smg", &weapon_cfg::smg::rPrediction);
                SldI("Smooth##smg", &weapon_cfg::smg::rSmooth, 1, 20);
                SldI("FOV##smg", &weapon_cfg::smg::rFovSize, 1, 1000);

                ImGui::Spacing();
                ImGui::Text("Rifle");
                Chk("Prediction##ar", &weapon_cfg::rifle::rPrediction);
                SldI("Smooth##ar", &weapon_cfg::rifle::rSmooth, 1, 20);
                SldI("FOV##ar", &weapon_cfg::rifle::rFovSize, 1, 1000);

                ImGui::Spacing();
                ImGui::Text("Sniper");
                Chk("Prediction##snp", &weapon_cfg::sniper::rPrediction);
                SldI("Smooth##snp", &weapon_cfg::sniper::rSmooth, 1, 20);
                SldI("FOV##snp", &weapon_cfg::sniper::rFovSize, 1, 1000);
            }
            ImGui::EndChild();
            break;
        }

        // ============================
        //  VISUALS
        // ============================
        case Tab::Visuals:
        {
            ImGui::SetCursorPos(ImVec2(cx, cy));
            ImGui::BeginChild("##vs_l", ImVec2(half_w, ch), true);
            {
                SectionLabel("Player ESP");
                Chk("Enable ESP", &c_enable_esp);

                if (c_enable_esp) {
                    ImGui::Spacing();
                    Chk("Box", &c_enable_box);
                    if (c_enable_box) {
                        ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 24);
                        Cmb("##boxtype", &c_box, "Static\0Filled\0Cornered\0\0");
                        ImGui::Spacing();
                        Chk("Filled Box", &c_filled_box);
                    }
                    Chk("Skeleton", &c_skeleton);
                    Chk("Snaplines", &c_lines);
                    Chk("Head Circle", &c_headcircle);
                    Chk("Distance", &c_distance);
                    Chk("Weapon", &c_weapon);
                    Chk("Username", &c_username);
                    Chk("Rank", &c_rank_esp);
                    Chk("Platform", &c_platform);
                    Chk("FOV Arrows", &c_arrows);
                    Chk("Target Line", &c_target);
                    Chk("Chams", &c_charms);
                    Chk("Wireframe", &c_wireframe);
                    Chk("Radar", &c_radar);
                    Chk("Risk Detection", &c_threat);
                }
            }
            ImGui::EndChild();

            ImGui::SetCursorPos(ImVec2(cx + half_w + 14, cy));
            ImGui::BeginChild("##vs_r", ImVec2(half_w, ch), true);
            {
                SectionLabel("Colors");

                ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 6);
                ImGui::Text("Visible");
                ImGui::SameLine(0, 8);
                ImGui::ColorEdit3("##vis_c", (float*)&c_color_visible,
                    ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel);

                ImGui::SameLine(0, 20);
                ImGui::Text("Invisible");
                ImGui::SameLine(0, 8);
                ImGui::ColorEdit3("##inv_c", (float*)&c_color_invisible,
                    ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel);

                SectionSep();
                SectionLabel("Adjustments");

                Cmb("Line Start", &c_line_start, "Top\0Center\0Bottom\0\0");
                ImGui::Spacing();
                Cmb("Line End", &c_line_end, "Top\0Center\0Bottom\0\0");
                ImGui::Spacing();
                Sld("Max Distance", &c_max_render_distance, 1.0f, 360.0f);
                ImGui::Spacing();
                Sld("Skeleton Width", &c_outlined, 1.0f, 5.0f);
                ImGui::Spacing();
                Sld("Box Width", &c_outlined1, 1.0f, 5.0f);
            }
            ImGui::EndChild();
            break;
        }

        // ============================
        //  TRIGGER
        // ============================
        case Tab::Trigger:
        {
            ImGui::SetCursorPos(ImVec2(cx, cy));
            ImGui::BeginChild("##tr_l", ImVec2(half_w, ch * 0.6f), true);
            {
                SectionLabel("Triggerbot");
                Chk("Enable (Shotgun)", &c_triggggger);
                ImGui::Spacing();
                SldI("Max Distance", &max_trig_distance, 0, 50);
                ImGui::Spacing();
                SldI("Delay (ms)", &trig_delay, 0, 5);
                ImGui::Spacing();
                Cmb("Keybind", &c_trig_key, "LMB\0RMB\0MB2\0MB1\0LShift\0LCtrl\0LAlt\0\0");
            }
            ImGui::EndChild();
            break;
        }

        // ============================
        //  MISC
        // ============================
        case Tab::Misc:
        {
            ImGui::SetCursorPos(ImVec2(cx, cy));
            ImGui::BeginChild("##ms_l", ImVec2(half_w, ch), true);
            {
                SectionLabel("Config");

                ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 6);
                ImVec2 bsz((half_w - 48) * 0.5f, 32);

                ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(24/255.f, 22/255.f, 34/255.f, 1.0f));
                ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(40/255.f, 36/255.f, 56/255.f, 1.0f));
                ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(140/255.f, 82/255.f, 1.0f, 0.7f));
                ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 8.0f);

                if (ImGui::Button("Save", bsz))
                    savecfg("C:\\info");
                ImGui::SameLine(0, 8);
                if (ImGui::Button("Load", bsz))
                    loadcfg("C:\\info");

                ImGui::PopStyleVar();
                ImGui::PopStyleColor(3);

                SectionSep();
                SectionLabel("Display");
                Chk("Show FPS", &C_Misc::c_show_fps);
                Chk("VSync", &C_Overlay::c_enable_vsync);
                Chk("Debug Mode", &debug);
            }
            ImGui::EndChild();

            ImGui::SetCursorPos(ImVec2(cx + half_w + 14, cy));
            ImGui::BeginChild("##ms_r", ImVec2(half_w, ch * 0.35f), true);
            {
                SectionLabel("Info");
                ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.5f, 0.45f, 0.6f, 1.0f));
                ImGui::Text("Build: v39.50");
                ImGui::Text("Visible: %d", numVisiblePeople);
                ImGui::PopStyleColor();
            }
            ImGui::EndChild();
            break;
        }

        // ============================
        //  SETTINGS
        // ============================
        case Tab::Settings:
        {
            ImGui::SetCursorPos(ImVec2(cx, cy));
            ImGui::BeginChild("##st_l", ImVec2(half_w, ch * 0.4f), true);
            {
                SectionLabel("Appearance");

                ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 6);
                ImGui::Text("Menu Accent");
                ImGui::SameLine(0, 10);
                ImGui::ColorEdit4("##accent", (float*)&MenuAccent,
                    ImGuiColorEditFlags_NoSidePreview |
                    ImGuiColorEditFlags_AlphaBar |
                    ImGuiColorEditFlags_NoInputs);
            }
            ImGui::EndChild();
            break;
        }
        } // switch

        ImGui::PopStyleVar(2);
    }
    ImGui::End();
}
