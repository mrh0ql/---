#pragma once
namespace C_Overlay
{
	inline bool c_show_menu = true;
	inline bool c_fullscreen = false;
	inline float c_center_y;
	inline float c_center_x;
	inline int c_screen_width = GetSystemMetrics(SM_CXSCREEN);
	inline int c_screen_height = GetSystemMetrics(SM_CYSCREEN);
	inline bool c_enable_vsync = true;
	inline ImVec4 general_child = ImColor(23, 23, 25);
}

static struct GunSettings {
	float c_smooth;
	int c_fov;
	int adsFovSize;
};

inline std::vector<GunSettings> gunSettings;  // Mark as inline to avoid multiple definitions


static const char* LineDirections[] = { "Top", "Center", "Bottom" };

namespace C_Players
{
	inline bool c_enable_esp = true;
	inline bool c_enable_box = true;
	inline int c_box = 0;
	inline bool c_static_box = true;
	inline bool c_cornered_box = false;
	inline bool c_seconds_alive = false;
	inline bool c_rank_esp = false;
	inline bool c_platform = false;
	inline bool c_skeleton = true;
	inline bool c_onscreenvis = true;
	inline bool c_lines = false;
	inline int c_line_start = 0;
	inline int c_line_end = 0;
	inline bool c_filled_box = false;
	inline float c_outlined = 2.0f;
	inline float c_outlined1 = 1.0f;
	inline int c_outlined23 = 3;
	inline float line_outline_thickness = 0.5f;
	inline float c_outlined_cor = 2.0f;
	inline float c_outlined2 = 1.0f;
	inline bool c_username = false;
	inline bool c_distance = true;
	inline bool c_weapon = false;
	inline bool c_threat = false;
	inline bool c_radar = true;
	inline bool c_radar_show = true;
	inline bool c_radar_type = true;
	inline bool c_arrows = false;
	inline bool c_loot = false;
	inline bool c_charms = true;
	inline bool c_wireframe = true;
	inline bool rGunConfigs;
	inline bool text_outline = false;
	inline bool Weapon_distance = false;
	inline float text_color[4] = { 165.0f / 255.0f, 0.0f / 255.0f, 192.0f / 255.0f, 1.0f };
	inline float InvisColor[4] = { 240.0f / 255.0f, 231.0f / 255.0f, 0.0f / 255.0f, 1.0f };
	inline int text_size = 16;

	inline ImVec4 AimlineColor = ImVec4(1.f, 1.f, 1.f, 1.f);
	inline ImVec4 FovColor = ImVec4(1.f, 1.f, 1.f, 1.f);
	inline ImVec4 AccentColor = ImVec4(1.f, 1.f, 1.f, 0.6f);

	inline ImVec4 FovFillColor = ImVec4(1.f, 1.f, 1.f, 0.f);

	inline ImVec4 BoxColorVis = ImVec4(1.f, 1.f, 1.f, 1.f);
	inline ImVec4 FillColorVis = ImVec4(1.f, 1.f, 1.f, 0.2f);
	inline ImVec4 DistanceColorVis = ImVec4(1.f, 1.f, 1.f, 1.f);
	inline ImVec4 UsernameColorVis = ImVec4(1.f, 1.f, 1.f, 1.f);
	inline ImVec4 PlatformColorVis = ImVec4(1.f, 1.f, 1.f, 1.f);
	inline ImVec4 KillsColorVis = ImVec4(1.f, 1.f, 1.f, 1.f);
	inline ImVec4 LevelsColorVis = ImVec4(1.f, 1.f, 1.f, 1.f);
	inline ImVec4 WeaponColorVis = ImVec4(1.f, 1.f, 1.f, 1.f);
	inline ImVec4 SkeletonColorVis = ImVec4(1.f, 1.f, 1.f, 1.f);
	inline ImVec4 SnaplineColorVis = ImVec4(1.f, 1.f, 1.f, 1.f);
	inline ImVec4 RadarColorVis = ImVec4(1.f, 0.f, 0.f, 1.f);
	inline ImVec4 FovArrowsColorVis = ImVec4(1.f, 0.f, 0.f, 1.f);

	inline ImVec4 BoxColorHidden = ImVec4(1.f, 1.f, 1.f, 1.f);
	inline ImVec4 FillColorHidden = ImVec4(1.f, 1.f, 1.f, 0.2f);
	inline ImVec4 DistanceColorHidden = ImVec4(1.f, 1.f, 1.f, 1.f);
	inline ImVec4 UsernameColorHidden = ImVec4(1.f, 1.f, 1.f, 1.f);
	inline ImVec4 PlatformColorHidden = ImVec4(1.f, 1.f, 1.f, 1.f);
	inline ImVec4 KillsColorHidden = ImVec4(1.f, 1.f, 1.f, 1.f);
	inline ImVec4 LevelsColorHidden = ImVec4(1.f, 1.f, 1.f, 1.f);
	inline ImVec4 WeaponColorHidden = ImVec4(1.f, 1.f, 1.f, 1.f);
	inline ImVec4 SkeletonColorHidden = ImVec4(1.f, 1.f, 1.f, 1.f);
	inline ImVec4 SnaplineColorHidden = ImVec4(1.f, 1.f, 1.f, 1.f);
	inline ImVec4 RadarColorHidden = ImVec4(0.f, 1.f, 0.f, 1.f);
	inline ImVec4 FovArrowsColorHidden = ImVec4(0.f, 1.f, 0.f, 1.f);
	inline ImVec4 c_color_invisible = ImVec4(240.0f / 255.0f, 231.0f / 255.0f, 0.0f / 255.0f, 1.0f);
	inline ImVec4 c_color_visible = ImVec4(165.0f / 255.0f, 0.0f / 255.0f, 192.0f / 255.0f, 1.0f);
	inline float g_color_Visible[3] = { 87 / 255.0f, 173 / 255.0f, 17 / 255.0f };  // RGB for visible color
	inline float g_color_invisible[3] = { 173 / 255.0f, 17 / 255.0f, 17 / 255.0f }; // RGB for invisible color
	inline float g_color[3] = { 255.00f, 0.00f, 255.00f };
	inline float radar_position_x{ 10.0f };
	inline float radar_position_y{ 10.0f };
	inline bool rect_radar = true;
	inline float radar_size{ 150.0f };
	inline float RadarDistance = { 50.f };
	inline ImColor MenuAccent = ImColor(140, 82, 255);

}

namespace weapon_cfg
{
	inline bool rAimbot;

	namespace rifle
	{
		inline bool rAimbot;
		inline bool rPrediction;
		inline int rSmooth = 5;
		inline bool rTriggerbot;
		inline int triggerDelay = 0;
		inline bool rFovCircle;
		inline int rFovSize = 200;
	}

	namespace shotgun
	{
		inline bool rAimbot;
		inline bool rPrediction;
		inline int rSmooth = 5;
		inline bool rTriggerbot;
		inline int triggerDelay = 0;
		inline bool rFovCircle;
		inline int rFovSize = 200;
	}

	namespace smg
	{
		inline bool rAimbot;
		inline bool rPrediction;
		inline int rSmooth = 5;
		inline bool rTriggerbot;
		inline int triggerDelay = 0;
		inline bool rFovCircle;
		inline int rFovSize = 200;
	}

	namespace sniper
	{
		inline bool rAimbot;
		inline bool rPrediction;
		inline int rSmooth = 5;
		inline bool rTriggerbot;
		inline int triggerDelay = 0;
		inline bool rFovCircle;
		inline int rFovSize = 200;
	}
}

inline int numVisiblePeople = 0;
inline bool debug = false;
inline bool c_trigger = true;

namespace worldnigga {
	inline bool enabled = false;
	inline bool chests = true;
	inline bool pickups = false;
	inline bool uncommon = false;
	inline bool common = false;
	inline bool epic = false;
	inline bool rare = false;
	inline bool legendary = false;
	inline bool mythic = false;
	inline int max_loots_distance = 50;
}
namespace C_Aimbot
{
	inline bool c_enable = true;
	inline bool c_prediction = false;
	inline bool c_dead_zone = false;
	inline int c_trig_key = 1;
	inline float c_custom_dead_zone = 0.1f;
	inline bool c_enable_deafult = true;
	inline bool c_triggggger = false;
	inline bool c_shotgun_only = false;
	inline int max_trig_distance = 30;
	inline int trig_delay = 1;
	inline bool c_enable_memory = true;
	inline bool c_circle = true;
	inline bool c_headcircle = true;
	inline bool c_humanized = false;
	inline float c_fov = 85;
	inline float c_max_render_distance = 425;
	inline bool c_visible_check = false;
	inline int c_aim_key = 1;
	inline int c_aim1 = 0;
	inline float c_smooth = 7;
	inline int c_hitbox = 3;
	inline bool c_knocked = 0;
	inline int c_mouse_type = 0;
	inline bool c_target = 0;
	inline int KillAllPlayersKey = 1;
	inline int c_fov_stuff = 1;
	inline bool fovreset = false;
	inline bool c_spinbot = true;
	inline bool c_ignore_downed = false;
	inline bool c_ignore_bots = false;
	inline int rFovSize = 200;
	inline bool g_weapon_cfg;

}

namespace C_Misc {

	inline bool c_performance_mode = false;
	inline bool c_show_fps = false;
	inline int tab_count, active_tab_count = 0;

	inline float anim_tab = 0;

	inline int tab_width = 85;

	inline float child_add, alpha_child = 0;
	inline ImVec2 size_menu = ImVec2(640, 520);
	inline ImVec2 size_watermark = ImVec2(479, 50);
	inline ImVec2 size_preview = ImVec2(300, 400);
}

namespace C_Exploits {
	inline bool freecam = false;
	inline bool wireframe = false;
}

namespace C_Radar
{
	inline bool enable = false;

}



namespace C_Color {

	inline ImVec4 accent_color = ImColor(255, 127, 73);

	namespace menu {

		inline ImVec4 window_bg = ImColor(20, 20, 22);
		inline ImVec4 border = ImColor(17, 17, 17, 255);
		inline ImVec4 watermark_bg = ImColor(21, 19, 20, 255);
		inline ImVec4 watermark_border = ImColor(21, 19, 20, 255);
		inline ImVec4 watermark_filled = ImColor(27, 25, 28);

	}

	namespace tabs {

		inline ImVec4 text_active = ImColor(255, 255, 255);
		inline ImVec4 text_hovered = ImColor(150, 150, 150);
		inline ImVec4 text_inactive = ImColor(76, 76, 77);

	}

	namespace child {

		inline ImVec4 child_background = ImColor(23, 23, 25);
		inline ImVec4 child_top = ImColor(25, 25, 27);
		inline float child_rounding = 7.f;

	}

	namespace checkbox {

		inline ImVec4 text_active = ImColor(255, 255, 255);
		inline ImVec4 text_hovered = ImColor(150, 150, 150);
		inline ImVec4 text_inactive = ImColor(76, 76, 77);

		inline ImVec4 checkbox_bg_active = ImColor(37, 37, 39);
		inline ImVec4 checkbox_bg_inactive = ImColor(35, 35, 37);

		inline ImVec4 circle_inactive = ImColor(44, 44, 46);

	}

	namespace slider {

		inline ImVec4 text_active = ImColor(255, 255, 255);
		inline ImVec4 text_hovered = ImColor(150, 150, 150);
		inline ImVec4 text_inactive = ImColor(76, 76, 77);
		inline ImVec4 slider_inactive = ImColor(35, 35, 37);

	}

	namespace combo {


		inline ImVec4 text_active = ImColor(255, 255, 255);
		inline ImVec4 text_hovered = ImColor(150, 150, 150);
		inline ImVec4 text_inactive = ImColor(76, 76, 77);
		inline ImVec4 combo_bg = ImColor(27, 27, 29);

	}

	namespace color_picker {

		inline ImVec4 picker_bg = ImColor(27, 27, 29);

	}

	namespace binder {

		inline ImVec4 binder_bg = ImColor(27, 27, 29);
		inline ImVec4 text_active = ImColor(255, 255, 255);
		inline ImVec4 text_hovered = ImColor(150, 150, 150);
		inline ImVec4 text_inactive = ImColor(76, 76, 77);
		inline ImVec4 line = ImColor(40, 40, 42);
		inline ImVec4 image_active = ImColor(255, 255, 255);
		inline ImVec4 image_hovered = ImColor(150, 150, 150);
		inline ImVec4 image_inactive = ImColor(76, 76, 77);

	}

	namespace button {

		inline ImVec4 button_bg = ImColor(27, 27, 29);
		inline ImVec4 text_active = ImColor(255, 255, 255);
		inline ImVec4 text_inactive = ImColor(76, 76, 77);
	}

	namespace input {

		inline ImVec4 input_bg = ImColor(27, 27, 29);
		inline ImVec4 input_image = ImColor(47, 47, 49);
		inline ImVec4 text_active = ImColor(255, 255, 255);
		inline ImVec4 text_hovered = ImColor(150, 150, 150);
		inline ImVec4 text_inactive = ImColor(76, 76, 77);
	}

	namespace preview {

		inline ImVec4 rect = ImColor(40, 40, 42);
		inline ImVec4 name = ImColor(255, 255, 255);
		inline ImVec4 distance = ImColor(255, 255, 255);
		inline ImVec4 head = ImColor(255, 255, 255);
		inline ImVec4 dice = ImColor(255, 255, 255);

	}


}

namespace settings {
	inline float checkbox_rounding = 100.f;
}