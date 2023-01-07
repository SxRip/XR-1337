#include "render.hpp"

render::~render()
{
	ImGui_ImplDX9_Shutdown();
	ImGui_ImplWin32_Shutdown();

	ImGui::DestroyContext();
}

render::render(HWND hwnd)
{
	create(hwnd);
}

void render::create(HWND hwnd)
{
	_pD3D = Direct3DCreate9(D3D_SDK_VERSION);

	VERIFY(_pD3D);

	D3DPRESENT_PARAMETERS params{ sizeof(D3DPRESENT_PARAMETERS) };

	D3DDISPLAYMODE display;
	VERIFYD3D(_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &display));

	RECT rc{};
	GetWindowRect(hwnd, &rc);

	params.Windowed = true;
	params.hDeviceWindow = hwnd;
	params.BackBufferFormat = display.Format;
	params.BackBufferWidth = rc.right - rc.left;
	params.BackBufferHeight = rc.bottom - rc.top;
	params.BackBufferCount = 1;
	params.SwapEffect = D3DSWAPEFFECT_DISCARD;

	VERIFYD3D(_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE::D3DDEVTYPE_HAL, hwnd, D3DCREATE_MIXED_VERTEXPROCESSING, &params, &_pDevice));

	VERIFYD3D(_pDevice->SetRenderState(D3DRENDERSTATETYPE::D3DRS_ZENABLE, D3DZB_FALSE));
	VERIFYD3D(_pDevice->SetRenderState(D3DRENDERSTATETYPE::D3DRS_ZWRITEENABLE,	false));
	VERIFYD3D(_pDevice->SetRenderState(D3DRENDERSTATETYPE::D3DRS_CULLMODE, D3DCULL_CW));

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();

	VERIFY(ImGui_ImplDX9_Init(_pDevice.Get()));
	VERIFY(ImGui_ImplWin32_Init(hwnd));
	ImGui::StyleColorsDark();
}

void render::begin() const
{
	VERIFYD3D(_pDevice->BeginScene());

	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
}

void render::end() const
{
	ImGui::EndFrame();

	ImGui::Render();
	ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
	VERIFYD3D(_pDevice->EndScene());

	VERIFYD3D(_pDevice->Present(nullptr, nullptr, nullptr, nullptr));
}

void render::clear(D3DCOLOR color) const
{
	VERIFYD3D(_pDevice->Clear(0, 0, D3DCLEAR_TARGET, color, 1.f, 0));
}
