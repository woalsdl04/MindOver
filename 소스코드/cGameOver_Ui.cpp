#include "DXUT.h"
#include "cGameOver_Ui.h"
#include "GSystem.h"
#include "cGameClear_info.h"

extern GSystem* Active_GSystem;

cGameOver_Ui::cGameOver_Ui()
{

}

cGameOver_Ui::~cGameOver_Ui()
{

}

void cGameOver_Ui::NEW()
{

	GameOver_Ui_Ani = gameObject->Add_Component<FrameAni_Component>(L"GameOver_Ui_Ani");
	GameOver_Ui_Ani->Set_FrameTime(100, false);


	gameObject->Set_Center(true);
	//gameObject->Render_Stack = 5;
	gameObject->transform.Set_LocalPosition(WISIZE_X / 2, WISIZE_Y / 2, 0);

	GameOver_info = NULL;
}

void cGameOver_Ui::Awake()
{

}

void cGameOver_Ui::Start()
{

}

void cGameOver_Ui::Notice(Notice_Item* notice)
{
	if (notice->Notice_Command == GNOTICE::ANI_END)
	{
		GameOver_info = new GameObject(L"GameOver_info");
		GameOver_info->Render_Stack = 11;
		GameOver_info->Add_Component<cGameClear_info>(L"GameOver_info_Script")->GameInfo(false);

		//Active_GSystem->Change_Scene((DWORD)SCENE::MENU, SCENE_CHANGE_ACTION::FADE, GCOLOR(0, 0, 0, 1), -1);
		gameObject->Destroy = true;
	}
}

void cGameOver_Ui::Update()
{

}

void cGameOver_Ui::Late_Update()
{

}

void cGameOver_Ui::Final_Update()
{

}

void cGameOver_Ui::Render()
{

}

void cGameOver_Ui::Reload()
{

}

void cGameOver_Ui::Change()
{

}

void cGameOver_Ui::Release()
{
	delete this;
}
