#pragma once
#include "c_overlay.h"
#include "../Fonts/ubuntu_bold.h"
#include "../Fonts/ubuntu_medium.h"
#include "../Fonts/ubunutu_regular.h"
#include "../Fonts/Extras/icons.h"
#include <d3d11.h>

#define MYCLASSNAME    _("Microsoft (x86)")
#define MYWINDOWNAME   _("Microsoft (x86)")

using Overlay::DX11Overlay;

WNDCLASSEX DX11Overlay::wcex = { 0 };
MARGINS DX11Overlay::Margin = { -1 };
HINSTANCE DX11Overlay::InjectedModule;

HWND DX11Overlay::D11Overlay;
RECT DX11Overlay::Rect;
INT DX11Overlay::width;
INT DX11Overlay::height;
INT DX11Overlay::widthD2;
INT DX11Overlay::heightD2;
extern ImFont* ico_0;
extern ImFont* ico_1;
static LPDIRECT3D9              g_pD3D = NULL;
static LPDIRECT3DDEVICE9        g_pd3dDevice = NULL;

inline ImFont* ubu_0;
extern ImFont* ubu_2;

extern ImFont* ubu_child;


auto timeOld = std::chrono::high_resolution_clock::now();
auto timeNow = std::chrono::high_resolution_clock::now();
auto OverlayfpsClock = std::chrono::high_resolution_clock::now();

ID3D11Device* DX11Overlay::pDevice = nullptr;
ID3D11DeviceContext* DX11Overlay::PDeviceContext = nullptr;
IDXGISwapChain* DX11Overlay::pSwapChain = nullptr;
ID3D11RenderTargetView* DX11Overlay::pRenderTarget = nullptr;

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK WndProc(HWND hWnd, UINT pMsg, WPARAM wParam, LPARAM lParam) {

	if (ImGui_ImplWin32_WndProcHandler(hWnd, pMsg, wParam, lParam) && C_Overlay::c_show_menu)
		return TRUE;

	return DefWindowProc(hWnd, pMsg, wParam, lParam);
}

VOID DX11Overlay::RenderBlur(HWND hwnd)
{

		struct ACCENTPOLICY
		{
			int na;
			int nf;
			int nc;
			int nA;
		};
		struct WINCOMPATTRDATA
		{
			int na;
			PVOID pd;
			ULONG ul;
		};

		const HINSTANCE hm = LoadLibrary(_("user32.dll"));
		if (hm)
		{
			typedef BOOL(WINAPI* pSetWindowCompositionAttribute)(HWND, WINCOMPATTRDATA*);

			const pSetWindowCompositionAttribute SetWindowCompositionAttribute = (pSetWindowCompositionAttribute)GetProcAddress(hm, _("SetWindowCompositionAttribute"));
			if (SetWindowCompositionAttribute)
			{
				ACCENTPOLICY policy = { 3, 0, 0, 0 }; // and even works 4,0,155,0 (Acrylic blur)
				WINCOMPATTRDATA data = { 19, &policy,sizeof(ACCENTPOLICY) };
				SetWindowCompositionAttribute(hwnd, &data);
			}
			FreeLibrary(hm);
		}
}

// Initialize ImGui
BOOL DX11Overlay::InitImGui() {

	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	ImFontConfig fontConfig;
	fontConfig.RasterizerMultiply = 1.4f;

	io.Fonts->AddFontFromMemoryTTF(&khait, sizeof khait, 20, NULL, io.Fonts->GetGlyphRangesCyrillic());
	/*ico_0 = io.Fonts->AddFontFromMemoryTTF(&icon, sizeof icon, 21, NULL, io.Fonts->GetGlyphRangesCyrillic());
	ico_1 = io.Fonts->AddFontFromMemoryTTF(&icon, sizeof icon, 28, NULL, io.Fonts->GetGlyphRangesCyrillic());



	ubu_0 = io.Fonts->AddFontFromMemoryTTF(&ubuntu_0, sizeof ubuntu_0, 18, NULL, io.Fonts->GetGlyphRangesCyrillic());
	ubu_1 = io.Fonts->AddFontFromMemoryTTF(&ubuntu_0, sizeof ubuntu_0, 25, NULL, io.Fonts->GetGlyphRangesCyrillic());
	ubu_2 = io.Fonts->AddFontFromMemoryTTF(&ubuntu_2, sizeof ubuntu_2, 25, NULL, io.Fonts->GetGlyphRangesCyrillic());
	ubu_child = io.Fonts->AddFontFromMemoryTTF(&ubuntu_1, sizeof ubuntu_1, 15, NULL, io.Fonts->GetGlyphRangesCyrillic());*/

	ImVec4 clear_color = ImVec4(0.f, 0.f, 0.f, 1.00f);

	ImGui::StyleColorsDark();
	ImGuiStyle& s = ImGui::GetStyle();

    s.Colors[ImGuiCol_WindowBg] = ImColor(165, 175, 185, 100);
    s.Colors[ImGuiCol_ChildBg] = ImColor(22, 21, 26, 255);
    s.Colors[ImGuiCol_PopupBg] = ImColor(17, 16, 21, 255);
    s.Colors[ImGuiCol_TextDisabled] = ImColor(66, 65, 70, 255);
    s.Colors[ImGuiCol_Border] = ImColor(14, 13, 19, 0);
    s.Colors[ImGuiCol_TextSelectedBg] = ImColor(35, 32, 43, 160);

    s.WindowBorderSize = 0;
    s.WindowPadding = ImVec2(0, 0);
    s.ChildRounding = 7;
    s.PopupRounding = 5;
    s.PopupBorderSize = 0;
    s.WindowRounding = 14.f;
    s.FrameBorderSize = 0.0f;
    s.FrameRounding = 4.f;
    s.ScrollbarSize = 2.f;
    s.FramePadding = ImVec2(6, 3);
    s.ItemInnerSpacing = ImVec2(10, 0);
    s.ItemSpacing = ImVec2(0, 10);

	// Initialize ImGui for Win32 and DX11
	if (ImGui_ImplWin32_Init(D11Overlay)) {
		if (ImGui_ImplDX11_Init(pDevice, PDeviceContext))
			return TRUE;
	}
	return FALSE;
}

// Function to create the overlay window
BOOL DX11Overlay::Hijack() {
	wcex.cbSize = sizeof(wcex);
	wcex.lpfnWndProc = WndProc;
	wcex.hInstance = InjectedModule;
	wcex.lpszClassName = MYCLASSNAME;

	if (!RegisterClassExA(&wcex)) {
		return FALSE;
	}

	//NOT GOOD. This needs to be changes like the entire overlay process needs to be changes. Just create a window and "remove" all flags or use task manager
	D11Overlay = CreateWindowExA(NULL, MYCLASSNAME, MYWINDOWNAME, WS_POPUP | WS_VISIBLE, 0, 0, width, height, 0, 0, InjectedModule, 0);
	if (!D11Overlay) {
		return FALSE;
	}

	SetWindowLong(D11Overlay, GWL_EXSTYLE, WS_EX_LAYERED | WS_EX_TOOLWINDOW | WS_EX_TOPMOST | WS_EX_TRANSPARENT);
	DwmExtendFrameIntoClientArea(D11Overlay, &Margin);

	ShowWindow(D11Overlay, SW_SHOW);
	UpdateWindow(D11Overlay);

	SetWindowPos(D11Overlay, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_FRAMECHANGED);

	SetWindowLongA(D11Overlay, GWL_EXSTYLE, WS_EX_LAYERED | WS_EX_TRANSPARENT | WS_EX_TOPMOST | WS_EX_TOOLWINDOW | WS_EX_TRANSPARENT);
	return TRUE;
}

BOOL DX11Overlay::CreateRenderTarget() {
	ID3D11Texture2D* pBackBuffer = NULL;
	HRESULT hr = pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
	if (FAILED(hr)) {
		return FALSE;
	}

	hr = pDevice->CreateRenderTargetView(pBackBuffer, NULL, &pRenderTarget);
	pBackBuffer->Release();

	if (FAILED(hr)) {
		return FALSE;
	}

	return TRUE;
}

inline ImFont* icons;
inline ImFont* font_main;

// Function to create the Direct3D 11 swap chain
BOOL DX11Overlay::CreateSwapchain() {
	// Swap chain description
	DXGI_SWAP_CHAIN_DESC swapChainDesc = {};
	swapChainDesc.BufferCount = 1; // Single back buffer
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM; // 32-bit color
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT; // Render target usage
	swapChainDesc.OutputWindow = D11Overlay; // Overlay window handle
	swapChainDesc.SampleDesc.Count = 1; // No multi-sampling
	swapChainDesc.Windowed = TRUE; // Start in windowed mode
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD; // Discard old frames
	swapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH; // Allow fullscreen mode switching

	// Feature levels
	D3D_FEATURE_LEVEL featureLevels[] = {
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0
	};
	D3D_FEATURE_LEVEL featureLevel;

	// Create the device and swap chain
	HRESULT hr = D3D11CreateDeviceAndSwapChain(
		NULL,
		D3D_DRIVER_TYPE_HARDWARE,
		NULL,
		D3D11_CREATE_DEVICE_BGRA_SUPPORT,
		featureLevels,
		_countof(featureLevels),
		D3D11_SDK_VERSION,
		&swapChainDesc,
		&pSwapChain,
		&pDevice,
		&featureLevel,
		&PDeviceContext
	);

	if (FAILED(hr)) {
		return FALSE;
	}

	// Create the render target
	if (!CreateRenderTarget()) {
		return FALSE;
	}

	// Set the render target
	PDeviceContext->OMSetRenderTargets(1, &pRenderTarget, NULL);

	return TRUE;
}

void DX11Overlay::ToggleFullscreen() {
	SPOOF_FUNC;

	BOOL isFullscreen;
	pSwapChain->GetFullscreenState(&isFullscreen, nullptr);
	pSwapChain->SetFullscreenState(!isFullscreen, nullptr);

	if (!isFullscreen) {
		// Now in fullscreen mode
		// Update overlay window size to match the game window's resolution
		GetWindowRect(GetForegroundWindow(), &Rect);
		SetWindowPos(D11Overlay, HWND_TOPMOST, Rect.left, Rect.top,
			Rect.right - Rect.left, Rect.bottom - Rect.top,
			SWP_NOOWNERZORDER | SWP_FRAMECHANGED);
	}
	else {
		// Now in windowed mode
		// Restore the original window size
		SetWindowPos(D11Overlay, HWND_TOPMOST, 0, 0, width, height, SWP_NOMOVE | SWP_NOSIZE);
	}
}

// Function to check if the GameWindow handle is valid
VOID DX11Overlay::ChechWindow(HWND GameWindow) {

	if (!GameWindow) TerminateProcess(GetCurrentProcess(), 3);
}

// Function to get the position and size of the GameWindow
VOID DX11Overlay::GetWindow(HWND GameWindow) {
	
	if (GetWindowRect(GameWindow, &Rect)) {
		width = Rect.right - Rect.left;
		height = Rect.bottom - Rect.top;

		widthD2 = width / 2;
		heightD2 = height / 2;
	}
}

// Function to initialize the overlay and associated components
BOOL DX11Overlay::InitOverlay() {
	
	if (!Hijack()) {
		std::cout << "nr1";
		return FALSE;
	}
	if (!CreateSwapchain()) {
		std::cout << "nr2";
		return FALSE;
	}
	if (!InitImGui()) {
		std::cout << "nr3";
		return FALSE;
	}
	return TRUE;
}

// Function to clean up and present the overlay
BOOL DX11Overlay::Cleanup() {

	static ImVec4 vCleanColor{ 0, 0, 0, 0 };

	// Render ImGui
	ImGui::Render();
	ImGui::EndFrame();

	// Clear the render target view with the specified clean color
	PDeviceContext->ClearRenderTargetView(pRenderTarget, (float*)&vCleanColor);

	// Render ImGui draw data
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

	// Present the swap chain
	HRESULT pSent = pSwapChain->Present(1, 0);
	if (pSent)
		return TRUE;
	return FALSE;
}

// Function to change the clickability of the overlay window
bool clickable = false;
void change_click(bool canclick) {
	
	long style = ::GetWindowLong(DX11Overlay::D11Overlay, GWL_EXSTYLE);
	if (canclick)
	{
		style &= ~WS_EX_LAYERED;
		SetWindowLong(DX11Overlay::D11Overlay, GWL_EXSTYLE, style);
		SetFocus(DX11Overlay::D11Overlay);
		clickable = true;
	}
	else
	{
		style |= WS_EX_LAYERED;
		SetWindowLong(DX11Overlay::D11Overlay, GWL_EXSTYLE, style);
		SetFocus(DX11Overlay::D11Overlay);
		clickable = false;
	}
}

void UpdateOverlayPosition() {
	RECT gameRect;
	HWND gameWindow = FindWindow(NULL, "Fortnite  "); // Replace with actual game window title
	if (gameWindow && GetWindowRect(gameWindow, &gameRect)) {
		SetWindowPos(DX11Overlay::D11Overlay, HWND_TOPMOST, gameRect.left, gameRect.top,
			gameRect.right - gameRect.left, gameRect.bottom - gameRect.top,
			SWP_NOOWNERZORDER | SWP_FRAMECHANGED);
	}
}

// Function to run the main overlay loop
BOOL DX11Overlay::MainLoop(std::function<VOID()> DrawLoop) {
	UpdateOverlayPosition();
	MSG Msg;
	static ImVec4 vCleanColor{ 0, 0, 0, 0 };

	if (PeekMessageA(&Msg, NULL, 0, 0, PM_REMOVE)) {
		TranslateMessage(&Msg);
		DispatchMessageA(&Msg);
	}

	// Get the display size for centering elements
	ImGuiIO& io = ImGui::GetIO();
	io.IniFilename = NULL;
	C_Overlay::c_center_x = (GetSystemMetrics(SM_CXSCREEN) / 2);
	C_Overlay::c_center_y = (GetSystemMetrics(SM_CYSCREEN) / 2);

	C_Overlay::c_screen_width = GetSystemMetrics(SM_CXSCREEN);
	C_Overlay::c_screen_height = GetSystemMetrics(SM_CYSCREEN);

	// Start a new frame for ImGui
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
	{
		// Execute the DrawLoop function provided by the user
		DrawLoop();
		c_draw_fov();
		if (C_Overlay::c_fullscreen) {
			pSwapChain->SetFullscreenState(TRUE, NULL);
	
			UpdateOverlayPosition();
		}
		UpdateOverlayPosition();
		// Toggle the menu visibility when the F2 key is pressed
		if (GetAsyncKeyState(VK_F1) & 1)
		{
			C_Overlay::c_show_menu = !C_Overlay::c_show_menu;
			Sleep(100);
		}

		if (C_Overlay::c_fullscreen) {
			pSwapChain->SetFullscreenState(TRUE, NULL);

			UpdateOverlayPosition();
		}
		UpdateOverlayPosition();
		// If the menu is shown, make the overlay window clickable
		if (C_Overlay::c_show_menu) {
			if (clickable != true)
				change_click(true);

			// Draw the menu content
			draw_menu();
		}

		// If the menu is hidden, make the overlay window not clickable
		else {
			if (clickable != false)
				change_click(false);
		}

		if (C_Overlay::c_fullscreen) {
			pSwapChain->SetFullscreenState(TRUE, NULL);

			UpdateOverlayPosition();
		}
		UpdateOverlayPosition();
	}

	// Render ImGui draw data and present the swap chain
	ImGui::Render();
	ImGui::EndFrame();
	PDeviceContext->ClearRenderTargetView(pRenderTarget, (float*)&vCleanColor);
	float clearColor[4] = { 0, 0, 0, 0 }; // Fully transparent
	PDeviceContext->ClearRenderTargetView(pRenderTarget, clearColor);
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	pSwapChain->Present(C_Overlay::c_enable_vsync, 0);

	// Return whether the message is not WM_QUIT, indicating the loop should continue
	return Msg.message != WM_QUIT;
}