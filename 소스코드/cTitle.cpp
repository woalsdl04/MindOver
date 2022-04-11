#include "DXUT.h"
#include "cTitle.h"
#include "GSystem.h"

extern GSystem* Active_GSystem;
extern GScene* Active_GScene;

extern INGAME_STEP ingame_Step;

extern int TotalScore;
extern int Stage;

cTitle::cTitle()
{

}

cTitle::~cTitle()
{

}

void cTitle::NEW()
{
	Title_Sc = gameObject->Add_Component<SpriteRenderer_Component>(L"Title_Sc");
	Title_Sc->Load_Texture(L"Title/Title_Bg.png", 1, 1, false);
	Title_Sc->Lock_Check();

	gameObject->Set_Center(true);
	gameObject->Render_Stack = 1;
	gameObject->transform.Set_LocalPosition(WISIZE_X / 2, WISIZE_Y / 2, 0);

	Button[0] = new GameObject(L"Start_Button");
	Button[1] = new GameObject(L"Developer_Button");
	Button[2] = new GameObject(L"Exit_Button");

	for (int i = 0; i < 3; i++) Button[i]->Render_Stack = 2;

	Button_Sc[0] = Button[0]->Add_Component<SpriteRenderer_Component>(L"Start_Sc");
	Button_Sc[1] = Button[1]->Add_Component<SpriteRenderer_Component>(L"Developer_Sc");
	Button_Sc[2] = Button[2]->Add_Component<SpriteRenderer_Component>(L"Exit_Sc");
	/*Button_TRS[0] = Button[0]->Add_Component<TRS_Component>(L"Start_TRS");
	Button_TRS[1] = Button[1]->Add_Component<TRS_Component>(L"Developer_TRS");
	Button_TRS[2] = Button[2]->Add_Component<TRS_Component>(L"Exit_TRS");*/


	Button_Sc[0]->Load_Texture(L"Title/START.png", 1, 1, false);
	Button_Sc[1]->Load_Texture(L"Title/EXIT.png", 1, 1, false);
	Button_Sc[2]->Load_Texture(L"Title/°³¹ßÀÚ.png", 1, 1, false);

	for (int i = 0; i < 3; i++)
	{
		Button_Sc[i]->Lock_Check();
	}

	Button[0]->Set_Center(true);
	Button[1]->Set_Center(true);
	Button[2]->Set_Center(true);

	Button[0]->transform.Set_LocalPosition((WISIZE_X/2) + 645, (WISIZE_Y/2), 0);
	Button[1]->transform.Set_LocalPosition((WISIZE_X / 2) + 600, (WISIZE_Y / 2) + 120, 0);
	Button[2]->transform.Set_LocalPosition((WISIZE_X / 2) + 565, (WISIZE_Y / 2) + 240, 0);

	Button_Pos[0] = Button[0]->transform.Get_LocalPosition();
	Button_Pos[1] = Button[1]->transform.Get_LocalPosition();
	Button_Pos[2] = Button[2]->transform.Get_LocalPosition();

	Title_Logo = new GameObject(L"Title_Logo");
	Title_Logo->Render_Stack = 2;
	Title_Logo->Add_Component<SpriteRenderer_Component>(L"Title_Logo_Sc")->Load_Texture(L"Title/Logo.png", 1, 1, false);
	Title_Logo->Get_Component<SpriteRenderer_Component>()->Lock_Check();
	Title_Logo->Set_Center(true);
	Title_Logo->transform.Set_LocalPosition(350, 250, 0);
	Title_Logo->transform.Set_LocalScale(0.5, 0.5, 0);

	Creadit = new GameObject(L"Creadit");
	Creadit->Render_Stack = 2;
	Creadit->Add_Component<SpriteRenderer_Component>(L"Creadit_Sc")->Load_Texture(L"Title/Creadit.png", 1, 1, false);
	Creadit->Get_Component<SpriteRenderer_Component>()->Lock_Check();
	Creadit->Set_Center(true);
	Creadit->transform.Set_LocalPosition(WISIZE_X / 2, WISIZE_Y / 2, 0);
	Creadit->Active = false;
	
	/*for (int i = 0; i < 3; i++)
	{
		Button_TRS[i]->Set_TRS(TRS_ENUM::MOVE, GVec3<float>(Button_Pos[i]->x, Button_Pos[i]->y, 0),
			GVec3<float>(Button_Pos[i]->x - 200, Button_Pos[i]->y, 0), -0.5, TRS_LOOPTYPE::ONEWAY, TRS_SPEEDTYPE::AVERAGE, 0, 1);
	}*/
	
	//Button_TRS[0]->Active = false;
	//Button_TRS[1]->Active = false;
	//Button_TRS[2]->Active = false;

	//T_Font = new GameObject(L"T_Font_Obj");
	//T_Font_FC = T_Font->Add_Component<GFont>(L"T_Font_FT");

	//T_Font->transform.Set_LocalScale(1, 1, 0);
	//T_Font_FC->Local_Rect = GRECT<int>{ 0, 0, WISIZE_X, WISIZE_Y };
	//T_Font_FC->Align = DT_CENTER | DT_BOTTOM;
	////T_Font->transform.Set_LocalPosition(0, 0, 0);

	//T_Font_FC->Setup(50, L"Fixedsys");
	
	/*gameObject->Add_Component<Music_Component>(L"Title_Sound")->Load_Music(L"./Res/ddddd.MP3");
	gameObject->Get_Component<Music_Component>()->Play_Music(true, 100, BGM_VOLUME_FADE::NOW);*/

	
	
	Title_Sound = gameObject->Add_Component<SoundCLIP_Component>(L"Title_Sound");
	Title_Sound->Load_Sound(L"./Res/Sound/ArcadeButton.WAV", 1);
	Title_Sound->Lock_Check();
	//Title_Sound->Stop_Sound();

	Sel = 0;
	Stage = 1;
	TotalScore = 0;
}

void cTitle::Awake()
{

	//Active_GScene->Set_Camera_Action(CAMERA_ACTION_TYPE::EARTHQUAKE, -0.03f, 20);
}

void cTitle::Start()
{
	
}

void cTitle::Notice(Notice_Item* notice)
{
	
}

void cTitle::Update()
{
	/*memcpy(m_Old, m_Cur, 128);
	memset(m_Cur, false, 128);


	for (int i = 0; i < 128; i++)
	{
		if (GetAsyncKeyState(i) & 0x8000)
		{
			m_Cur[i] = true;
		}
	}*/
	Active_GSystem->System_LoopCount = Active_GSystem->System_LoopCount;

	if (DownKeys[VK_DOWN])
	{
		Sel++;
		Title_Sound->Play_Sound(false);
		//GLog(L"Sel: %d", Sel);
	}
	else if (DownKeys[VK_UP])
	{
		Sel--;
		Title_Sound->Play_Sound(false);
	}
	else if(DownKeys['A'])
	{
		Title_Sound->Play_Sound(false);

		switch (Sel)
		{
		case 0:
			Active_GSystem->Change_Scene((DWORD)SCENE::STAGE1, SCENE_CHANGE_ACTION::FADE, GCOLOR(0, 0, 0, 1), -1);
			break;
		case 1:
			PostQuitMessage(0);
			break;
		case 2:
			if(Creadit->Active == false)
			Creadit->Active = true;
			else
				Creadit->Active = false;
			break;
		}
	}
	
	Sel = (Sel + 99999) % 3;
	

	for(int i = 0; i < 3; i++)
	{
		if (Sel != i)
		{
			switch (i)
			{
				case 0:
					if (Button_Pos[i]->x < (WISIZE_X / 2) + 645)
					{
						Button_Pos[i]->x += 300 * DT;
					}
					break;
				case 1:
					if (Button_Pos[i]->x < (WISIZE_X / 2) + 600)
					{
						Button_Pos[i]->x += 300 * DT;
					}
					break;
				case 2:
					if (Button_Pos[i]->x < (WISIZE_X / 2) + 565)
					{
						Button_Pos[i]->x += 300 * DT;
					}
					break;
			}
		}
	}

	if (Button_Pos[Sel]->x > 1400)
		Button_Pos[Sel]->x -= 300 * DT;

	/*GVec3<float>* pos = gameObject->transform.Get_LocalPosition();

	if (PressKeys[VK_SPACE])
		Active_GSystem->Change_Scene((DWORD)SCENE::STAGE1, SCENE_CHANGE_ACTION::FADE, GCOLOR(0, 0, 0, 1), -1);

	T_Font_FC->Set_Text(L"Press Spacebar Key!");*/
}

void cTitle::Late_Update()
{


}

void cTitle::Final_Update()
{

}

void cTitle::Render()
{

}

void cTitle::Reload()
{

}

void cTitle::Change()
{

}

void cTitle::Release()
{

	delete this;
}
