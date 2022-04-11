#include "DXUT.h"
#include "cGameClear_info.h"
#include "GSystem.h"
#include "cPlayer.h"
#include "cIngame_Ui.h"
#include "Score_Number.h"

extern GSystem* Active_GSystem;

extern int Stage;
extern int TotalScore;

extern SoundCLIP_Component* End_Sound;

cGameClear_info::cGameClear_info()
{

}

cGameClear_info::~cGameClear_info()
{

}

void cGameClear_info::NEW()
{
	
}

void cGameClear_info::Awake()
{

}

void cGameClear_info::Start()
{
	if (IsGameClear)
		gameObject->Add_Component<SpriteRenderer_Component>(L"GameClear_info_Sc")->Load_Texture(L"Ui/Clear_Info.png", 1, 1, false);
	else
		gameObject->Add_Component<SpriteRenderer_Component>(L"GameOver_info_Sc")->Load_Texture(L"Ui/Gameover_Info.png", 1, 1, false);

	gameObject->Get_Component<SpriteRenderer_Component>()->Lock_Check();

	gameObject->Add_Component<Color_Component>(L"GameClear_info_Color")->Setup(GCOLOR(1, 1, 1, 0), GCOLOR(1, 1, 1, 1), -0.5, COLOR_ACTIONTYPE::ONEWAY, 0xFFFFFFFF);
	gameObject->Add_Component<TRS_Component>(L"GameClear_info_TRS")->Set_TRS(TRS_ENUM::SCALE, GVec3<float>(0.7, 0.7, 0.7), GVec3<float>(1, 1, 1), -2, TRS_LOOPTYPE::ONEWAY, TRS_SPEEDTYPE::SPEEDUP, 0, 0xFFFFFFFF);

	gameObject->Set_Center(true);
	gameObject->transform.Set_LocalPosition(WISIZE_X / 2, WISIZE_Y / 2, 0);
	//gameObject->Active = false;

	Active_GSystem->Find(L"Player")->Get_Component<cPlayer>(L"Player_Script")->Active = false;
	//Active_GSystem->Find(L"Ingame_Ui")->Get_Component<cIngame_Ui>(L"Ingame_Ui_Script")->Active = false;

	Arrow_obj = NULL;
	Number = NULL;

	Sel = 0;
	End_Sound->Play_Sound(false);
}

void cGameClear_info::Notice(Notice_Item* notice)
{
	if(notice->Notice_Command == GNOTICE::TRS_END && Arrow_obj == NULL && Number == NULL)
	{
		Arrow_obj = new GameObject(L"Arrow_obj");
		Arrow_obj->Render_Stack = 12;
		Arrow_obj->Add_Component<SpriteRenderer_Component>(L"Arrow_obj_Sc")->Load_Texture(L"Ui/Arrow.png", 1, 1, false);
		Arrow_obj->Get_Component<SpriteRenderer_Component>()->Lock_Check();
		Arrow_obj->Set_Center(true);
		Arrow_obj->transform.Set_LocalPosition(WISIZE_X / 2 + 240, WISIZE_Y / 2 + 23, 0);


		Number = new GameObject(L"Number");
		Number->Render_Stack = 12;
		Number->Set_Center(true);

		Number_Sc = Number->Add_Component<SpriteRenderer_Component>(L"Number_Sc");
		Number_Sc->Load_Texture(L"Score_Number.png", 10, 1, false);
		Number_Sc->Lock_Check();
		Number_Sc->Active = false;

		Number->Add_Component<Score_Number>(L"Number_Script");
	}

}

void cGameClear_info::Update()
{


	if (DownKeys[VK_DOWN])
	{
		if(Sel < 1)
		Sel++;
	}
	else if (DownKeys[VK_UP])
	{
		if(Sel > 0)
		Sel--;
		//Arrow_obj->transform.Set_LocalPosition();
	}
	
	if(DownKeys['A'])
	{
		switch (Sel)
		{
		case 0:
			if (IsGameClear)
			{
				switch (Stage)
				{
				case 1:
					Active_GSystem->Change_Scene((DWORD)SCENE::STAGE2, SCENE_CHANGE_ACTION::FADE, GCOLOR(0, 0, 0, 1), -1);
					break;
				case 2:
					Active_GSystem->Change_Scene((DWORD)SCENE::STAGE3, SCENE_CHANGE_ACTION::FADE, GCOLOR(0, 0, 0, 1), -1);
					break;
				case 3:
					Active_GSystem->Change_Scene((DWORD)SCENE::MENU, SCENE_CHANGE_ACTION::FADE, GCOLOR(0, 0, 0, 1), -1);
					break;
				}
				Stage++;
			}
			else
			{
				switch (Stage)
				{
				case 1:
					Active_GSystem->Change_Scene((DWORD)SCENE::STAGE1, SCENE_CHANGE_ACTION::FADE, GCOLOR(0, 0, 0, 1), -1);
					break;
				case 2:
					Active_GSystem->Change_Scene((DWORD)SCENE::STAGE2, SCENE_CHANGE_ACTION::FADE, GCOLOR(0, 0, 0, 1), -1);
					break;
				case 3:
					Active_GSystem->Change_Scene((DWORD)SCENE::STAGE3, SCENE_CHANGE_ACTION::FADE, GCOLOR(0, 0, 0, 1), -1);
					break;
				}
				TotalScore = 0;
			}
			break;
		case 1:
			TotalScore = 0;
			Active_GSystem->Change_Scene((DWORD)SCENE::MENU, SCENE_CHANGE_ACTION::FADE, GCOLOR(0, 0, 0, 1), -1);
			break;
		}
	}

	if(Arrow_obj != NULL)
	{
		switch (Sel)
		{
		case 0:
			Arrow_obj->transform.Set_LocalPosition(WISIZE_X / 2 + 240, WISIZE_Y / 2 + 23, 0);
			break;
		case 1:
			Arrow_obj->transform.Set_LocalPosition(WISIZE_X / 2 + 240, WISIZE_Y / 2 + 163, 0);
			break;
		default:
			break;
		}
	}
	/*Score_Ui_Font->Set_Text(L"%.0f", 186503.436);

	Score_Ui->transform.Set_LocalPosition(GVec3<float>(J_Pos.x / 2, J_Pos.y / 2, 0));*/
}

void cGameClear_info::GameInfo(bool Isgameclear)
{
	IsGameClear = Isgameclear;
}

void cGameClear_info::Late_Update()
{

}

void cGameClear_info::Final_Update()
{

}

void cGameClear_info::Render()
{

}

void cGameClear_info::Reload()
{

}

void cGameClear_info::Change()
{

}

void cGameClear_info::Release()
{
	delete this;
}
