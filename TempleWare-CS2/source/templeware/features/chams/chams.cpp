#include <algorithm>
#include <iostream>
#include "chams.h"
#include "../../hooks/hooks.h"
#include "../../config/config.h"
#include "../../../../external/imgui/imgui.h"
#include "../../utils/math/utlstronghandle/utlstronghandle.h"
#include "../../../cs2/entity/C_Material/C_Material.h"
#include "../../interfaces/interfaces.h"
#include "../../interfaces/CGameEntitySystem/CGameEntitySystem.h"
#include "../../../cs2/datatypes/keyvalues/keyvalues.h"
#include "../../../cs2/datatypes/cutlbuffer/cutlbuffer.h"



CStrongHandle<CMaterial2> chams::create(const char* name, const char szVmatBuffer[])
{
    CKeyValues3* pKeyValues3 = nullptr;

    pKeyValues3 = pKeyValues3->create_material_from_resource();

    pKeyValues3->LoadFromBuffer(szVmatBuffer);

    CStrongHandle<CMaterial2> pCustomMaterial = {};

    I::CreateMaterial(nullptr, &pCustomMaterial, name, pKeyValues3, 0, 1);

    return pCustomMaterial;
}

struct resource_material_t
{
    CStrongHandle<CMaterial2> mat;
    CStrongHandle<CMaterial2> mat_invs;
};

static resource_material_t resourceMaterials[ChamsType::MAXCOUNT];
bool loaded_materials = false;
bool chams::Materials::init()
{
    // flat
    resourceMaterials[FLAT] = resource_material_t{
        .mat = create("materials/dev/flat.vmat", R"(<!-- kv3 encoding:text:version{e21c7f3c-8a33-41c5-9977-a76d3a32aa0d} format:generic:version{7412167c-06e9-4698-aff2-e63eb59037e7} -->
        {
            Shader = "csgo_unlitgeneric.vfx"
        
            F_IGNOREZ = 0
             F_DISABLE_Z_WRITE = 0
            F_DISABLE_Z_BUFFERING = 0
            F_BLEND_MODE = 1
            F_TRANSLUCENT = 1
            F_RENDER_BACKFACES = 0

            g_vColorTint = [1.000000, 1.000000, 1.000000, 1.000000]
            g_vGlossinessRange = [0.000000, 1.000000, 0.000000, 0.000000]
            g_vNormalTexCoordScale = [1.000000, 1.000000, 0.000000, 0.000000]
            g_vTexCoordOffset = [0.000000, 0.000000, 0.000000, 0.000000]
            g_vTexCoordScale = [1.000000, 1.000000, 0.000000, 0.000000]
            g_tColor = resource:"materials/dev/primary_white_color_tga_f7b257f6.vtex"
            g_tNormal = resource:"materials/default/default_normal_tga_7652cb.vtex"
        })"),
        .mat_invs = create("materials/dev/flat_i.vmat", R"(<!-- kv3 encoding:text:version{e21c7f3c-8a33-41c5-9977-a76d3a32aa0d} format:generic:version{7412167c-06e9-4698-aff2-e63eb59037e7} -->
        {
            Shader = "csgo_unlitgeneric.vfx"
            F_IGNOREZ = 1
            F_DISABLE_Z_WRITE = 1
            F_DISABLE_Z_BUFFERING = 1
            F_BLEND_MODE = 1
            F_TRANSLUCENT = 1
            g_vColorTint = [1.000000, 1.000000, 1.000000, 0.000000]
            g_vGlossinessRange = [0.000000, 1.000000, 0.000000, 0.000000]
            g_vNormalTexCoordScale = [1.000000, 1.000000, 0.000000, 0.000000]
            g_vTexCoordOffset = [0.000000, 0.000000, 0.000000, 0.000000]
            g_vTexCoordScale = [1.000000, 1.000000, 0.000000, 0.000000]
            g_tColor = resource:"materials/dev/primary_white_color_tga_f7b257f6.vtex"
            g_tNormal = resource:"materials/default/default_normal_tga_7652cb.vtex"
        })")
    };
    resourceMaterials[NORMAL] = resource_material_t{
    .mat = create("materials/dev/flat.vmat", R"(<!-- kv3 encoding:text:version{e21c7f3c-8a33-41c5-9977-a76d3a32aa0d} format:generic:version{7412167c-06e9-4698-aff2-e63eb59037e7} -->
        {
            Shader = "csgo_unlitgeneric.vfx"
        
            F_IGNOREZ = 0
             F_DISABLE_Z_WRITE = 0
            F_DISABLE_Z_BUFFERING = 0
            F_BLEND_MODE = 1
            F_TRANSLUCENT = 1
            F_RENDER_BACKFACES = 0

            g_vColorTint = [1.000000, 1.000000, 1.000000, 1.000000]
            g_vGlossinessRange = [0.000000, 1.000000, 0.000000, 0.000000]
            g_vNormalTexCoordScale = [1.000000, 1.000000, 0.000000, 0.000000]
            g_vTexCoordOffset = [0.000000, 0.000000, 0.000000, 0.000000]
            g_vTexCoordScale = [1.000000, 1.000000, 0.000000, 0.000000]
            g_tColor = resource:"materials/dev/primary_white_color_tga_f7b257f6.vtex"
            g_tNormal = resource:"materials/default/default_normal_tga_7652cb.vtex"
        })"),
        .mat_invs = create("materials/dev/flat_i.vmat", R"(<!-- kv3 encoding:text:version{e21c7f3c-8a33-41c5-9977-a76d3a32aa0d} format:generic:version{7412167c-06e9-4698-aff2-e63eb59037e7} -->
        {
            Shader = "csgo_unlitgeneric.vfx"
            F_IGNOREZ = 1
            F_DISABLE_Z_WRITE = 1
            F_DISABLE_Z_BUFFERING = 1
            F_BLEND_MODE = 1
            F_TRANSLUCENT = 1
            g_vColorTint = [1.000000, 1.000000, 1.000000, 0.000000]
            g_vGlossinessRange = [0.000000, 1.000000, 0.000000, 0.000000]
            g_vNormalTexCoordScale = [1.000000, 1.000000, 0.000000, 0.000000]
            g_vTexCoordOffset = [0.000000, 0.000000, 0.000000, 0.000000]
            g_vTexCoordScale = [1.000000, 1.000000, 0.000000, 0.000000]
            g_tColor = resource:"materials/dev/primary_white_color_tga_f7b257f6.vtex"
            g_tNormal = resource:"materials/default/default_normal_tga_7652cb.vtex"
        })")
    };
    return true;
}

ChamsEntity chams::GetTargetType(C_BaseEntity* render_ent) noexcept {
    auto local = H::oGetLocalPlayer(0);
    if (!local)
        return ChamsEntity::INVALID;

    if (!render_ent->IsBasePlayer() && !render_ent->IsPlayerController())
        return ChamsEntity::INVALID;

    auto player = (C_CSPlayerPawn*)render_ent;
    if (!player)
        return ChamsEntity::INVALID;

    auto alive = player->m_iHealth() > 0;
    if (!alive)
        return ChamsEntity::INVALID;

    if (player->m_iTeamNum() == local->m_iTeamNum())
        return ChamsEntity::INVALID;

    return ChamsEntity::ENEMY;
}

CMaterial2* GetMaterial(int type, bool invisible) { return invisible ? resourceMaterials[FLAT].mat_invs : resourceMaterials[FLAT].mat; }

void __fastcall chams::hook(void* a1, void* a2, CMeshData* pMeshScene, int MeshCount, void* pSceneView, void* pSceneLayer, void* pUnk, void* pUnk2)
{
    static auto original = H::DrawObject.GetOriginal();

    if (!I::EngineClient->valid())
        return original(a1, a2, pMeshScene, MeshCount, pSceneView, pSceneLayer, pUnk, pUnk2);
    auto local_player = H::oGetLocalPlayer(0);
    if (!local_player)
        return original(a1, a2, pMeshScene, MeshCount, pSceneView, pSceneLayer, pUnk, pUnk2);
    if (!pMeshScene)
        return original(a1, a2, pMeshScene, MeshCount, pSceneView, pSceneLayer, pUnk, pUnk2);

    if (!pMeshScene->pSceneAnimatableObject)
        return original(a1, a2, pMeshScene, MeshCount, pSceneView, pSceneLayer, pUnk, pUnk2);

    if (MeshCount < 1)
        return original(a1, a2, pMeshScene, MeshCount, pSceneView, pSceneLayer, pUnk, pUnk2);

    CMeshData* render_data = pMeshScene;
    if (!render_data)
        return original(a1, a2, pMeshScene, MeshCount, pSceneView, pSceneLayer, pUnk, pUnk2);

    if (!render_data->pSceneAnimatableObject)
        return original(a1, a2, pMeshScene, MeshCount, pSceneView, pSceneLayer, pUnk, pUnk2);

    auto render_ent = render_data->pSceneAnimatableObject->Owner();
    if (!render_ent.valid())
        return original(a1, a2, pMeshScene, MeshCount, pSceneView, pSceneLayer, pUnk, pUnk2);

    auto entity = I::GameEntity->Instance->Get(render_ent);
    if (!entity)
        return original(a1, a2, pMeshScene, MeshCount, pSceneView, pSceneLayer, pUnk, pUnk2);

    const auto target = GetTargetType(entity);

    if (target != ENEMY)
        return original(a1, a2, pMeshScene, MeshCount, pSceneView, pSceneLayer, pUnk, pUnk2);

    bool og = !Config::enemyChams && !Config::enemyChamsInvisible;
    if (og)
        return original(a1, a2, pMeshScene, MeshCount, pSceneView, pSceneLayer, pUnk, pUnk2);

    // Prioritize invisible chams if both are enabled
    if (Config::enemyChamsInvisible) {
        pMeshScene->pMaterial = GetMaterial(FLAT, true);
        pMeshScene->color.r = static_cast<uint8_t>(Config::colVisualChams.x * 255.0f);
        pMeshScene->color.g = static_cast<uint8_t>(Config::colVisualChams.y * 255.0f);
        pMeshScene->color.b = static_cast<uint8_t>(Config::colVisualChams.z * 255.0f);
        pMeshScene->color.a = static_cast<uint8_t>(Config::colVisualChams.w * 255.0f);
        return original(a1, a2, pMeshScene, MeshCount, pSceneView, pSceneLayer, pUnk, pUnk2);
    }

    // Only apply visible chams if invisible chams are not enabled
    if (Config::enemyChams) {
        pMeshScene->pMaterial = GetMaterial(FLAT, false);
        pMeshScene->color.r = static_cast<uint8_t>(Config::colVisualChamsIgnoreZ.x * 255.0f);
        pMeshScene->color.g = static_cast<uint8_t>(Config::colVisualChamsIgnoreZ.y * 255.0f);
        pMeshScene->color.b = static_cast<uint8_t>(Config::colVisualChamsIgnoreZ.z * 255.0f);
        pMeshScene->color.a = static_cast<uint8_t>(Config::colVisualChamsIgnoreZ.w * 255.0f);
        return original(a1, a2, pMeshScene, MeshCount, pSceneView, pSceneLayer, pUnk, pUnk2);
    }

    // If we get here, neither chams type is enabled, so just render normally
    return original(a1, a2, pMeshScene, MeshCount, pSceneView, pSceneLayer, pUnk, pUnk2);

}
