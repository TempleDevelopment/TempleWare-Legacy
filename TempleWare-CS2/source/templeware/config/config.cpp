#include "config.h"

// CBA to make proper atm, it's 03:42 right now.
// For now just stores config values don't mind it too much
//
// (FYI THIS IS A HORRID SOLUTION BUT FUNCTIONS) 

namespace Config {
	bool esp = false;
	bool glow = false;
	bool showHealth = false;
	bool teamCheck = false;
	bool espFill = false;
	bool showNameTags = false;

	bool Night = false;

	bool enemyChamsInvisible = false;
	bool enemyChams = false;
	bool teamChams = false;
	bool teamChamsInvisible = false;
	int chamsMaterial = 0;


	bool armChams = false;
	bool viewmodelChams = false;
	ImVec4 colViewmodelChams = ImVec4(1, 0, 0, 1);
	ImVec4 colArmChams = ImVec4(1, 0, 0, 1);

	ImVec4 colVisualChams = ImVec4(1, 0, 0, 1);
	ImVec4 colVisualChamsIgnoreZ = ImVec4(1, 0, 0, 1);
	ImVec4 teamcolVisualChamsIgnoreZ = ImVec4(1, 0, 0, 1);
	ImVec4 teamcolVisualChams = ImVec4(1, 0, 0, 1);

	float espThickness = 1.0f;
	float espFillOpacity = 0.5f;
	ImVec4 espColor = ImVec4(1, 0, 0, 1);

	bool fovEnabled = false;
	float fov = 90.0f;

	bool antiflash = false;

	ImVec4 NightColor = ImVec4(0.1, 0.1, 0.1, 1);

	bool aimbot = 0;
	float aimbot_fov = 0;
	bool team_check = false;
	bool rcs = 0;
	bool fov_circle = 0;
	ImVec4 fovCircleColor = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
}
