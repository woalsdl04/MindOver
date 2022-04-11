#include "DXUT.h"
#include "cGameClear.h"
#include "DXUT.h"
#include "cGameClear.h"
#include "cGameClear_info.h"
#include "GSystem.h"

extern GSystem* Active_GSystem;

cGameClear::cGameClear()
{

}

cGameClear::~cGameClear()
{

}

void cGameClear::NEW()
{
	GameClear_Ani = gameObject->Add_Component<FrameAni_Component>(L"Gamestart_Ui_Ani");
	GameClear_Ani->Set_FrameTime(50, false);

	gameObject->Set_Center(true);
	//gameObject->Render_Stack = 5;
	gameObject->transform.Set_LocalPosition(WISIZE_X / 2, WISIZE_Y / 2, 0);
	GameClear_info = NULL;
}

void cGameClear::Awake()
{

}

void cGameClear::Start()
{

}

void cGameClear::Notice(Notice_Item* notice)
{
	if (notice->Notice_Command == GNOTICE::ANI_END)
	{
		GameClear_info = new GameObject(L"GameClear_info");
		GameClear_info->Render_Stack = 11;
		GameClear_info->Add_Component<cGameClear_info>(L"GameClear_info_Script")->GameInfo(true);
		
		gameObject->Destroy = true;
		//Active_GSystem->Change_Scene((DWORD)SCENE::MENU, SCENE_CHANGE_ACTION::FADE, GCOLOR(0, 0, 0, 1), -1);
	}
}

void cGameClear::Update()
{

}

void cGameClear::Late_Update()
{

}

void cGameClear::Final_Update()
{

}

void cGameClear::Render()
{

}

void cGameClear::Reload()
{

}

void cGameClear::Change()
{

}

void cGameClear::Release()
{
	delete this;
}
