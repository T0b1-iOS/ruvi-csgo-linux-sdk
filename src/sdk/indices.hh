#pragma once

namespace idx
{
#ifdef _WIN32
	constexpr auto WIN = true;
#else
	constexpr auto WIN = false;
#endif


#pragma region VGUI
	constexpr size_t PAINT = WIN ? 14u : 15u;
#pragma endregion

#pragma region SURFACE
	constexpr size_t DRAW_SET_COLOR = WIN ? 15u : 14u;
	constexpr size_t DRAW_FILLED_RECT = 16u;
	constexpr size_t DRAW_OUTLINED_RECT = 18u;
	constexpr size_t DRAW_LINE = 19u;
	constexpr size_t DRAW_SET_TEX_FILE = 36u;
	constexpr size_t DRAW_SET_TEX_RGBA = 37u;
	constexpr size_t DRAW_SET_TEX = 38u;
	constexpr size_t DRAW_TEX_RECT = 41u;
	constexpr size_t IS_TEX_ID_VALID = 42u;
	constexpr size_t CREATE_TEX_ID = 43u;
	constexpr size_t GET_SCREEN_SIZE = 44u;
	constexpr size_t UNLOCK_CURSOR = 66u;
	constexpr size_t LOCK_CURSOR = 67u;
	constexpr size_t CREATE_FONT = 71u;
	constexpr size_t SET_FONT_GLYPH_SET = 72u;
	constexpr size_t GET_TEXT_SIZE = 79u;
	constexpr size_t PLAY_SOUND = 82u;
	constexpr size_t SURFACE_GET_CURSOR_POS = 100u;
	constexpr size_t DRAW_OUTLINED_CIRCLE = 103u;
	constexpr size_t DRAW_TEX_POLYGON = 106u;
	constexpr size_t DRAW_FILLED_RECT_FADE = 123u;
	constexpr size_t GET_CLIP_RECT = 146u;
	constexpr size_t SET_CLIP_RECT = 147u;
	constexpr size_t DISABLE_CLIPPING = 159u;
	constexpr size_t DRAW_COL_TEXT = 163u;
#pragma endregion

#pragma region BASE_CLIENT
	constexpr size_t GET_ALL_CLASSES = 8u;
	constexpr size_t IN_KEY_EVENT = 21u;
	constexpr size_t VIEW_FADE = 29u;
	constexpr size_t FRAME_STAGE_NOTIFY = 37u;
	constexpr size_t DISPATCH_USER_MSG = 38u;
#pragma endregion 

#pragma region ENGINE_CLIENT
	constexpr size_t ENGINE_GET_SCREEN_SIZE = 5u;
	constexpr size_t GET_PLAYER_INFO = 8u;
	constexpr size_t GET_PLAYER_USER_ID = 9u;
	constexpr size_t GET_LOCAL_PLAYER = 12u;
	constexpr size_t GET_VIEW_ANGLES = 18u;
	constexpr size_t SET_VIEW_ANGLES = 19u;
	constexpr size_t GET_MAX_CLIENTS = 20u;
	constexpr size_t IS_IN_GAME = 26u;
	constexpr size_t IS_CONNECTED = 27u;
	constexpr size_t GET_MAP_NAME = 52u;
	constexpr size_t IS_TAKING_SS = 92u;
	constexpr size_t EXEC_CLIENT_CMD = 108u;
	constexpr size_t EXEC_CMD_UNRESTRICTED = 113u;
#pragma endregion 

#pragma region CLIENT_MODE
	constexpr size_t CREATE_MOVE = WIN ? 24u : 25u;
#pragma endregion 

#pragma region DEBUG_OVERLAY
	constexpr size_t SCREEN_POSITION = WIN ? 13u : 11u;
#pragma endregion 

#pragma region PANEL
	constexpr size_t PANEL_GET_NAME = WIN ? 36u : 37u;
#pragma endregion 

#pragma region RENDER_CTX
	constexpr size_t TEX_GET_WIDTH = 3u;
	constexpr size_t TEX_GET_HEIGHT = 4u;
	constexpr size_t CTX_SET_RT = 6u;
	constexpr size_t CTX_DRAW_SS_RECT = WIN ? 114u : 113u;
	constexpr size_t CTX_PUSH_RT_VP = WIN ? 119u : 118u;
	constexpr size_t CTX_POP_RT_VP = WIN ? 120u : 119u;
	constexpr size_t CTX_SET_STENCIL_STATE = WIN ? 128u : 127u;
#pragma endregion

#pragma region MATERIAL_SYSTEM
	constexpr size_t MAT_BB_FMT = 36u;
	constexpr size_t MAT_CREATE_MAT = 83u;
	constexpr size_t MAT_FIND_MAT = 84u;
	constexpr size_t MAT_GET_MAT = 89u;
	constexpr size_t MAT_BEGIN_RT_ALLOC = 94u;
	constexpr size_t MAT_END_RT_ALLOC = 95u;
	constexpr size_t MAT_CREATE_NAMED_RT = 97u;
	constexpr size_t MAT_GET_CTX = 115u;
#pragma endregion 

#pragma region MATERIAL
	constexpr size_t MAT_GET_NAME = 0u;
	constexpr size_t MAT_TEX_GRP_NAME = 1u;
	constexpr size_t MAT_INC_REF = WIN ? 12u : 4u;
	constexpr size_t MAT_ALPHA_MOD = 27u;
	constexpr size_t MAT_COL_MOD = 28u;
	constexpr size_t MAT_SET_MAT_FLAG = 29u;
#pragma endregion

#pragma region INPUT_SYSTEM
	constexpr size_t INPUT_BTN_DOWN = 15u;
	constexpr size_t INPUT_ANALOG_VAL = WIN ? 17u : 18u;
	constexpr size_t INPUT_ANALOG_DELTA = WIN ? 18u : 19u;
	constexpr size_t INPUT_BTN_CODE_STR = 40u;
#pragma endregion 

#pragma region CONVAR
	constexpr size_t CV_GET_FLOAT = WIN ? 12u : 15u;
	constexpr size_t CV_GET_INT = WIN ? 13u : 16u;
	constexpr size_t CV_SET_STR_VAL = WIN ? 14u : 17u;
	constexpr size_t CV_SET_FL_VAL = WIN ? 15u : 18u;
	constexpr size_t CV_SET_INT_VAL = WIN ? 16u : 19u;

	constexpr size_t CV_REG_CMD = 10u;
	constexpr size_t CV_UNREG_CMD = 11u;
	constexpr size_t CV_FIND_VAR = 17u;
	constexpr size_t CV_CON_COL_PRINT = 25u;
#pragma endregion 

#pragma region ENTITIES
	constexpr size_t GET_ABS_ORIGIN = WIN ? 10u : 12u;
	constexpr size_t SET_MDL_IDX = WIN ? 75u : 111u;
	constexpr size_t GET_MDL = 8u;
	constexpr size_t DRAW_MDL = 9u;
	constexpr size_t SETUP_BONES = 13u;
	constexpr size_t GET_RENDER_BOUNDS = 17u;
	constexpr size_t NETWORKABLE_RELEASE = 1u;
	constexpr size_t GET_CLIENT_CLASS = 2u;
	constexpr size_t IS_DORMANT = 9u;
	constexpr size_t GET_INDEX = 10u;
	constexpr size_t SET_DESTROYED_ON_REC_ENT = 13u;
#pragma endregion 

}

namespace offsets
{
#ifdef _WIN32
	constexpr auto WIN = true;
#else
	constexpr auto WIN = false;
#endif

    // Regions needed here?

	constexpr size_t CLIPPING_ENABLED = WIN ? 0x280u : 0x3A8u;
	constexpr size_t MAT_GAME_STARTED = WIN ? 0x2C68u : 0x32A8u;
}
