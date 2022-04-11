#include "DXUT.h"
#include "cIngameManager.h"
#include "GSystem.h"
#include "cIngame.h"
#include "cIngameManager.h"
#include "cIngame_Ui.h"
#include "cPlayer.h"
#include "cBg.h"
#include "cStage1_Boss.h"
#include "cStage1_Enemy.h"
#include "cMaskBg.h"
#include "cGame_Start_Ui.h"
#include "cWarning_Back.h"
#include "cGameOver_Ui.h"
#include "cGameClear.h"

extern GSystem* Active_GSystem;
extern float ClearPer;
extern int Player_Life;
extern int Stage;

bool IsDie = false;

INGAME_STEP Ingame_Step = INGAME_STEP::INIT;

extern SoundCLIP_Component* Warning_Sound;

cIngameManager::cIngameManager()
{

}

cIngameManager::~cIngameManager()
{

}

void cIngameManager::NEW()
{
	GameOver = new GameObject(L"GameOver");
	GameOver->Render_Stack = 10;
	GameOver_Ui_Sc = GameOver->Add_Component<SpriteRenderer_Component>(L"GameOver_Ui_Sr");
	GameOver_Ui_Sc->Load_Texture(L"Ui/MindOver2.png", 8, 1, false);
	GameOver_Ui_Sc->Lock_Check();

	GameClear = new GameObject(L"GameClear");
	GameClear->Render_Stack = 10;
	GameClear_Sc = GameClear->Add_Component<SpriteRenderer_Component>(L"GameClear_Sr");
	GameClear_Sc->Load_Texture(L"Ui/GameClear.png", 3, 8, false);
	GameClear_Sc->Lock_Check();

	GameClear->Active = false;
	GameOver->Active = false;
	IsDie = false;


	switch (Stage)
	{
	case 1:
		break;
	case 2:
		break;
	case 3:
		break;
	}
}

void cIngameManager::Awake()
{

}

void cIngameManager::Start()
{
	StartTime = 1;
	IsGamestart = true;
}

void cIngameManager::Notice(Notice_Item* notice)
{


}

void cIngameManager::Update()
{



	WorldTime += DT;

	if(StartTime < WorldTime && IsGamestart)
	{
		/*Gamestart_Ui = new GameObject(L"Game_Start_Ui");

		Gamestart_Ui->Render_Stack = 5;
		Gamestart_Ui->Add_Component<cGame_Start_Ui>(L"Game_Start_Script");
		IsGamestart = false;*/
	}
	
	if (ClearPer >= 50 && ClearPer <= 80 && !IsWarning)
	{
		Warning_Sound->Play_Sound(false);

		GameObject* Warning = new GameObject(L"Warning_Back");
		Warning->Render_Stack = 7;
		Warning->Add_Component<cWarning_Back>(L"Warning_Back_Script");
		IsWarning = true;
		Warning_Sound->Play_Sound(false);
	}
	
	if (ClearPer >= 80 && GameClear->Active == false && IsDie) //게임 클리어
	{
		GameClear->Active = true;
		GameClear->Add_Component<cGameClear>(L"GameClear_Script");
	}

	if(Player_Life <= 0 && GameOver->Active == false)
	{
		GameOver->Active = true;
		GameOver->Add_Component<cGameOver_Ui>(L"GameOver_Script");
	}

	//switch (Ingame_Step)
	//{
	//case INGAME_STEP::INIT:
	//{
	//	StartTime = WorldTime;
	//	Ingame_Step = INGAME_STEP::READY;

	//	break;
	//}
	//case INGAME_STEP::READY:
	//{
	//	if (StartTime + 0 < WorldTime) //씬 체인지
	//	{
	//		Active_GSystem->Change_Scene((DWORD)SCENE::STAGE1, SCENE_CHANGE_ACTION::FADE, GCOLOR(0, 0, 0, 1), -1);
	//	}
	//	break;
	//}
	//case INGAME_STEP::SHOWSTART: 
	//{break; }
	//case INGAME_STEP::STAGE1:
	//{
	//	break;
	//}
	//case INGAME_STEP::STAGE2: {break; }
	//case INGAME_STEP::STAGE3: {break; }
	//case INGAME_STEP::DIE: {break; }
	//case INGAME_STEP::RE: {break; }
	//case INGAME_STEP::GAMEOVER: {break; }
	//case INGAME_STEP::STAGECLEAR: {break; }
	//case INGAME_STEP::CLEAR: {break; }
	//case INGAME_STEP::NONE:
	//{
	//	break;
	//}
	//	break;
	//}
}

void cIngameManager::Late_Update()
{

}

void cIngameManager::Final_Update()
{

}

void cIngameManager::Render()
{

}

void cIngameManager::Reload()
{

}

void cIngameManager::Change()
{

}

void cIngameManager::Release()
{
	delete this;
}
