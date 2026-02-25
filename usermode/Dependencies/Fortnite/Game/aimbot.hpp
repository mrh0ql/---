#include <cmath>
#include <chrono>
#include <thread>
#include <windows.h> // For PostMessage and GetAsyncKeyState|
#include "../../Fortnite/Game/UE_Functions\entity_utils.hpp"
#include "../../../Includes/Definitions/xorst.h"
#include <codecvt>
#include <locale>
#include <string>
#include <mutex>
#include "../../../Includes/Mouse.h"
#include "../../../interception.h"

std::mutex PlayerMutex_;

InterceptionContext mouse_context;
InterceptionDevice mouse_device;
InterceptionStroke mouse_stroke;

void run_mouse_loop() {
	while (interception_receive(mouse_context, mouse_device = interception_wait(mouse_context), &mouse_stroke, 1) > 0) {
		if (interception_is_mouse(mouse_device)) {
			InterceptionMouseStroke& mstroke = *(InterceptionMouseStroke*)&mouse_stroke;
			interception_send(mouse_context, mouse_device, &mouse_stroke, 1);
		}
	}
}

bool initialize_mouse() {
	mouse_context = interception_create_context();
	interception_set_filter(mouse_context, interception_is_mouse, INTERCEPTION_FILTER_MOUSE_MOVE);
	mouse_device = interception_wait(mouse_context);

	while (interception_receive(mouse_context, mouse_device = interception_wait(mouse_context), &mouse_stroke, 1) > 0) {
		if (interception_is_mouse(mouse_device)) {
			InterceptionMouseStroke& mstroke = *(InterceptionMouseStroke*)&mouse_stroke;
			interception_send(mouse_context, mouse_device, &mouse_stroke, 1);
			break;
		}
	}

	std::thread([&]() { run_mouse_loop(); }).detach();

	return true;
}

void move_mouse(int x, int y) {
	InterceptionMouseStroke& mstroke = *(InterceptionMouseStroke*)&mouse_stroke;

	mstroke.flags = 0;
	mstroke.information = 0;
	mstroke.x = x;
	mstroke.y = y;

	interception_send(mouse_context, mouse_device, &mouse_stroke, 1);
}

void mouse_click() {
	InterceptionMouseStroke& mstroke = *(InterceptionMouseStroke*)&mouse_stroke;

	mstroke.state = INTERCEPTION_MOUSE_LEFT_BUTTON_DOWN;
	interception_send(mouse_context, mouse_device, &mouse_stroke, 1);

	mstroke.state = INTERCEPTION_MOUSE_LEFT_BUTTON_UP;
	interception_send(mouse_context, mouse_device, &mouse_stroke, 1);

	//(Sleep)(itx::settings_c::iCustomDelay);
}

double get_cross_distance1(double x_, double y_)
{
	return sqrtf(powf((c_screen_width - x_), 2) + powf((c_screen_height - y_), 2));
}

float RandomFloat(float a, float b)
{
	float random = ((float)rand()) / (float)RAND_MAX;
	float diff = b - a;
	float r = random * diff;
	return a + r;
}

void perform(fvector2d Head2D)
{
	float x = Head2D.x; float y = Head2D.y;
	float AimSpeed = c_smooth;

	fvector2d Target;


	if (x != 0.f)
	{
		Target.x = (x > c_screen_width / 2) ? -(c_screen_width / 2 - x) : x - c_screen_width / 2;
		Target.x /= AimSpeed;
		Target.x = (x > c_screen_width / 2 && Target.x + c_screen_width / 2 > c_screen_width / 2 * 2) ? 0 : Target.x;
		Target.x = (x < c_screen_width / 2 && Target.x + c_screen_width / 2 < 0) ? 0 : Target.x;
	}

	if (y != 0.f)
	{
		Target.y = (y > c_screen_height / 2) ? -(c_screen_height / 2 - y) : y - c_screen_height / 2;
		Target.y /= AimSpeed;
		Target.y = (y > c_screen_height / 2 && Target.y + c_screen_height / 2 > c_screen_height / 2 * 2) ? 0 : Target.y;
		Target.y = (y < c_screen_height / 2 && Target.y + c_screen_height / 2 < 0) ? 0 : Target.y;
	}

	switch (C_Aimbot::c_aim1) {
	case 0:
		if (C_Aimbot::c_dead_zone) {
			if (abs(Target.x) > C_Aimbot::c_custom_dead_zone || abs(Target.x) > C_Aimbot::c_custom_dead_zone) {
				move_mouse(Target.x, Target.y);
			}

		}
		else {
			move_mouse(Target.x, Target.y);
		} break;
	case 1:
		float targetx_min = Target.x - 1;
		float targetx_max = Target.x + 1;

		float targety_min = Target.y - 1;
		float targety_max = Target.y + 1;

		float offset_x = RandomFloat(targetx_min, targetx_max);
		float offset_y = RandomFloat(targety_min, targety_max);

		move_mouse(static_cast<int> ((float)offset_x), static_cast<int>((float)offset_y / 1)); break;
	}
}


