#pragma once
#include "config/config.h"

#include "hooks/hooks.h"
#include "renderer/renderer.h"
#include "utils/schema/schema.h"
#include "interfaces/interfaces.h"
#include "features/chams/chams.h"
class TempleWare {
public:
	void init(HWND& window, ID3D11Device* pDevice, ID3D11DeviceContext* pContext, ID3D11RenderTargetView* mainRenderTargetView);

	Schema schema;
	Renderer renderer;


	H::Hooks hooks;
	chams::Materials materials;
	I::Interfaces interfaces;

};
