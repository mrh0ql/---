#include "../Drawing/imgui.h"

void draw_static(int X, int Y, int W, int H, const ImColor color, int thickness)
{
	SPOOF_FUNC;

	float lineW = (W / 1);
	float lineH = (H / 1);

	// Black outlines with fixed thickness of 1 (or any desired thin thickness)
	ImColor blackColor = ImColor(0, 0, 0, 255); // Black color with full opacity
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(X, Y), ImVec2(X, Y + lineH), blackColor, 1);
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(X, Y), ImVec2(X + lineW, Y), blackColor, 1);
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(X + W - lineW, Y), ImVec2(X + W, Y), blackColor, 1);
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(X + W, Y), ImVec2(X + W, Y + lineH), blackColor, 1);
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(X, Y + H - lineH), ImVec2(X, Y + H), blackColor, 1);
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(X, Y + H), ImVec2(X + lineW, Y + H), blackColor, 1);
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(X + W - lineW, Y + H), ImVec2(X + W, Y + H), blackColor, 1);
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(X + W, Y + H - lineH), ImVec2(X + W, Y + H), blackColor, 1);

	// Calculate offset for thinner lines
	float offset = thickness / 2.0f;

	// Corners with customizable thickness
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(X + offset, Y + offset), ImVec2(X + offset, Y + lineH - offset), color, thickness);
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(X + offset, Y + offset), ImVec2(X + lineW - offset, Y + offset), color, thickness);
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(X + W - lineW + offset, Y + offset), ImVec2(X + W - offset, Y + offset), color, thickness);
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(X + W - offset, Y + offset), ImVec2(X + W - offset, Y + lineH - offset), color, thickness);
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(X + offset, Y + H - lineH + offset), ImVec2(X + offset, Y + H - offset), color, thickness);
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(X + offset, Y + H - offset), ImVec2(X + lineW - offset, Y + H - offset), color, thickness);
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(X + W - lineW + offset, Y + H - offset), ImVec2(X + W - offset, Y + H - offset), color, thickness);
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(X + W - offset, Y + H - lineH + offset), ImVec2(X + W - offset, Y + H - offset), color, thickness);
}



void cornered(int X, int Y, int W, int H, int thickness, ImColor color) {
	SPOOF_FUNC;
	float lineW = (W / 5);
	float lineH = (H / 6);
	float lineT = 1;

	//outline
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(X - lineT, Y - lineT), ImVec2(X + lineW, Y - lineT), ImGui::ColorConvertFloat4ToU32(ImVec4(1 / 255.0, 1 / 255.0, 1 / 255.0, 255 / 255.0)), thickness); //top left
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(X - lineT, Y - lineT), ImVec2(X - lineT, Y + lineH), ImGui::ColorConvertFloat4ToU32(ImVec4(1 / 255.0, 1 / 255.0, 1 / 255.0, 255 / 255.0)), thickness);
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(X - lineT, Y + H - lineH), ImVec2(X - lineT, Y + H + lineT), ImGui::ColorConvertFloat4ToU32(ImVec4(1 / 255.0, 1 / 255.0, 1 / 255.0, 255 / 255.0)), thickness); //bot left
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(X - lineT, Y + H + lineT), ImVec2(X + lineW, Y + H + lineT), ImGui::ColorConvertFloat4ToU32(ImVec4(1 / 255.0, 1 / 255.0, 1 / 255.0, 255 / 255.0)), thickness);
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(X + W - lineW, Y - lineT), ImVec2(X + W + lineT, Y - lineT), ImGui::ColorConvertFloat4ToU32(ImVec4(1 / 255.0, 1 / 255.0, 1 / 255.0, 255 / 255.0)), thickness); // top right
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(X + W + lineT, Y - lineT), ImVec2(X + W + lineT, Y + lineH), ImGui::ColorConvertFloat4ToU32(ImVec4(1 / 255.0, 1 / 255.0, 1 / 255.0, 255 / 255.0)), thickness);
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(X + W + lineT, Y + H - lineH), ImVec2(X + W + lineT, Y + H + lineT), ImGui::ColorConvertFloat4ToU32(ImVec4(1 / 255.0, 1 / 255.0, 1 / 255.0, 255 / 255.0)), thickness);// bot right
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(X + W - lineW, Y + H + lineT), ImVec2(X + W + lineT, Y + H + lineT), ImGui::ColorConvertFloat4ToU32(ImVec4(1 / 255.0, 1 / 255.0, 1 / 255.0, 255 / 255.0)), thickness);

	//inline
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(X, Y), ImVec2(X, Y + lineH), color, thickness);//top left
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(X, Y), ImVec2(X + lineW, Y), color, thickness);
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(X + W - lineW, Y), ImVec2(X + W, Y), color, thickness); //top right
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(X + W, Y), ImVec2(X + W, Y + lineH), color, thickness);
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(X, Y + H - lineH), ImVec2(X, Y + H), color, thickness); //bot left
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(X, Y + H), ImVec2(X + lineW, Y + H), color, thickness);
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(X + W - lineW, Y + H), ImVec2(X + W, Y + H), color, thickness);//bot right
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(X + W, Y + H - lineH), ImVec2(X + W, Y + H), color, thickness);

}



void outlined_text(ImDrawList* drawlist, int x, int y, ImColor Color, const char* text)
{
	SPOOF_FUNC;

	ImVec2 offsets[] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };

	for (const auto& offset : offsets)
	{
		drawlist->AddText(ImVec2(x + offset.x, y + offset.y), ImColor(0, 0, 0, 255), text);
	}

	drawlist->AddText(ImVec2(x, y), Color, text);
}

inline std::wstring MBytesToWString(const char* lpcszString)
{
	SPOOF_FUNC;

	int len = strlen(lpcszString);
	int unicodeLen = ::MultiByteToWideChar(CP_ACP, 0, lpcszString, -1, NULL, 0);
	wchar_t* pUnicode = new wchar_t[unicodeLen + 1];
	memset(pUnicode, 0, (unicodeLen + 1) * sizeof(wchar_t));
	::MultiByteToWideChar(CP_ACP, 0, lpcszString, -1, (LPWSTR)pUnicode, unicodeLen);
	std::wstring wString = (wchar_t*)pUnicode;
	delete[] pUnicode;
	return wString;
}
inline std::string WStringToUTF8(const wchar_t* lpwcszWString)
{
	SPOOF_FUNC;

	char* pElementText;
	int iTextLen = ::WideCharToMultiByte(CP_UTF8, 0, (LPWSTR)lpwcszWString, -1, NULL, 0, NULL, NULL);
	pElementText = new char[iTextLen + 1];
	memset((void*)pElementText, 0, (iTextLen + 1) * sizeof(char));
	::WideCharToMultiByte(CP_UTF8, 0, (LPWSTR)lpwcszWString, -1, pElementText, iTextLen, NULL, NULL);
	std::string strReturn(pElementText);
	delete[] pElementText;
	return strReturn;
}

inline void DrawString(float fontSize, int x, int y, float color[4], bool bCenter, bool stroke, const char* pText, ...)
{

	float r = color[0];
	float g = color[1];
	float b = color[2];
	float a = color[3];

	ImU32 converted_color = ImGui::ColorConvertFloat4ToU32(ImVec4(r, g, b, a));
	va_list va_alist;
	char buf[1024] = { 0 };
	va_start(va_alist, pText);
	_vsnprintf_s(buf, sizeof(buf), pText, va_alist);
	va_end(va_alist);
	std::string text = WStringToUTF8(MBytesToWString(buf).c_str());
	if (bCenter)
	{
		ImVec2 textSize = ImGui::CalcTextSize(text.c_str());
		x = x - textSize.x / 4;
		y = y - textSize.y;
	}
	if (stroke)
	{
		/*ImGui::GetBackgroundDrawList()->AddText(ImGui::GetFont(), fontSize, ImVec2(x + 1, y + 1), ImGui::ColorConvertFloat4ToU32(ImVec4(0, 0, 0, 1)), text.c_str());
		ImGui::GetBackgroundDrawList()->AddText(ImGui::GetFont(), fontSize, ImVec2(x - 1, y - 1), ImGui::ColorConvertFloat4ToU32(ImVec4(0, 0, 0, 1)), text.c_str());
		ImGui::GetBackgroundDrawList()->AddText(ImGui::GetFont(), fontSize, ImVec2(x + 1, y - 1), ImGui::ColorConvertFloat4ToU32(ImVec4(0, 0, 0, 1)), text.c_str());
		ImGui::GetBackgroundDrawList()->AddText(ImGui::GetFont(), fontSize, ImVec2(x - 1, y + 1), ImGui::ColorConvertFloat4ToU32(ImVec4(0, 0, 0, 1)), text.c_str());*/
		ImGui::GetBackgroundDrawList()->AddText(ImGui::GetFont(), fontSize, ImVec2(x, y - 1), ImGui::ColorConvertFloat4ToU32(ImVec4(1 / 255.0, 1 / 255.0, 1 / 255.0, 255 / 255.0)), text.c_str());
		ImGui::GetBackgroundDrawList()->AddText(ImGui::GetFont(), fontSize, ImVec2(x, y + 1), ImGui::ColorConvertFloat4ToU32(ImVec4(1 / 255.0, 1 / 255.0, 1 / 255.0, 255 / 255.0)), text.c_str());
		ImGui::GetBackgroundDrawList()->AddText(ImGui::GetFont(), fontSize, ImVec2(x - 1, y), ImGui::ColorConvertFloat4ToU32(ImVec4(1 / 255.0, 1 / 255.0, 1 / 255.0, 255 / 255.0)), text.c_str());
		ImGui::GetBackgroundDrawList()->AddText(ImGui::GetFont(), fontSize, ImVec2(x + 1, y), ImGui::ColorConvertFloat4ToU32(ImVec4(1 / 255.0, 1 / 255.0, 1 / 255.0, 255 / 255.0)), text.c_str());
	}
	ImGui::GetBackgroundDrawList()->AddText(ImGui::GetFont(), fontSize, ImVec2(x, y), converted_color, text.c_str());
}

 void draw_string(float fontSize, int x, int y, ImColor color, bool bCenter, bool stroke, std::string text)
{
	 SPOOF_FUNC;

	if (text.empty()) {
		return;
	}

	if (bCenter) {
		ImVec2 textSize = ImGui::CalcTextSize(text.c_str());
		x -= textSize.x / 2;
		y -= textSize.y / 2;
	}

	// Outline/stroke the text if required
	if (stroke) {
		ImVec4 black = ImVec4(0, 0, 0, 1);
		ImColor black_color = ImColor(black);
		ImGui::GetBackgroundDrawList()->AddText(ImGui::GetFont(), fontSize, ImVec2(x + 1, y + 1), black_color, text.c_str());
		ImGui::GetBackgroundDrawList()->AddText(ImGui::GetFont(), fontSize, ImVec2(x - 1, y - 1), black_color, text.c_str());
		ImGui::GetBackgroundDrawList()->AddText(ImGui::GetFont(), fontSize, ImVec2(x + 1, y - 1), black_color, text.c_str());
		ImGui::GetBackgroundDrawList()->AddText(ImGui::GetFont(), fontSize, ImVec2(x - 1, y + 1), black_color, text.c_str());
	}

	ImGui::GetBackgroundDrawList()->AddText(ImGui::GetFont(), fontSize, ImVec2(x, y), color, text.c_str());
}

 void line(fvector ScreenPositionA, fvector ScreenPositionB, int Thickness, ImColor RenderColor, bool outline) {
	 SPOOF_FUNC;

	if (outline)
	{
		ImGui::GetBackgroundDrawList()->AddLine(ImVec2(ScreenPositionA.x, ScreenPositionA.y), ImVec2(ScreenPositionB.x + 1, ScreenPositionB.y + 1), ImColor(0, 0, 0, 255), Thickness + 1.5);
	}
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(ScreenPositionA.x, ScreenPositionA.y), ImVec2(ScreenPositionB.x + 1, ScreenPositionB.y + 1), RenderColor, Thickness);
}

void filled(int x, int y, int w, int h, ImColor color1, ImColor color2)
{
	SPOOF_FUNC;

	ImDrawList* draw_list = ImGui::GetBackgroundDrawList();
	draw_list->AddRectFilledMultiColor(
		ImVec2(x, y), ImVec2(x + w, y + h),
		color1, color1, color2, color2
	);
}

void drawstatic_(const fvector2d head_box, float box_width, float box_height, const ImColor& viscolor,int c_outlined1) {
	SPOOF_FUNC;

	draw_static((head_box.x - (box_width / 2)), head_box.y, box_width, box_height, viscolor, c_outlined1);
}

void drawfilled_(const fvector2d head_box, float box_width, float box_height, const ImColor& filldecolor, const ImColor& filldecolor1) {
	SPOOF_FUNC;

	filled((head_box.x - (box_width / 2)), head_box.y, box_width, box_height, filldecolor, filldecolor1);
}

void drawcorner_(const fvector2d head_box, float box_width, float box_height, const ImColor& viscolor, int c_outlined1) {
	SPOOF_FUNC;

	cornered((head_box.x - (box_width / 2)), head_box.y, box_width, box_height, c_outlined1, viscolor);
}

void drawoutlined_(const std::string& text, const ImVec2& position, ImColor color, int offset_y) {
	SPOOF_FUNC;

	ImVec2 text_size = ImGui::CalcTextSize(text.c_str());
	outlined_text(ImGui::GetBackgroundDrawList(), position.x - (text_size.x / 2), position.y + offset_y, color, text.c_str());
}
