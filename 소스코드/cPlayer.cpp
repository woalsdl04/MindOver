#include "DXUT.h"
#include "cPlayer.h"
#include "GSystem.h"
#include "cStage1_Boss.h"
#include "cIngame_Ui.h"
#include "cPlayer_Die_Eff.h"

extern GSystem* Active_GSystem;
//extern bool IsMaskUpdate = false;

extern float ClearPer;
extern int Score;
extern int TotalScore;
extern DWORD LineColor;

extern CSound* Sound;

float J_Speed = 0;
int Player_Life = 3;

bool IsEnemyDie_Check = false;
bool Hit_Check = false;
MOVEMODE PlayerState = MOVEMODE::NOMALMOVE;

extern SoundCLIP_Component* Electricity_Sound;
extern SoundCLIP_Component* Shoot_Sound;

cPlayer::cPlayer()
{

}

cPlayer::~cPlayer()
{

}

void cPlayer::NEW()
{

	Player_Sc = gameObject->Add_Component<SpriteRenderer_Component>(L"Player_Sc");
	Player_Sc->Load_Texture(L"Player.png", 1, 1, false);
	Player_Sc->Lock_Check();

	gameObject->Set_Center(true);
	gameObject->transform.Set_LocalPosition(PG_LEFT, PG_TOP, 0);
	gameObject->Render_Stack = 4;
	gameObject->transform.Set_LocalRotation(0, 0, 0);
	Player_Color = gameObject->Add_Component<Color_Component>(L"Player_Cr");
	Player_Color->Setup(GCOLOR(1, 1, 1, 0), GCOLOR(1, 0, 0, 1), -0.5f, COLOR_ACTIONTYPE::ROUNDTRIP, 0xFFFFFFFF);
	Player_Color->Active = false;
	//gameObject->Add_Component<TRS_Component>(L"Player_TRS")->Set_TRS(TRS_ENUM::SCALE, GVec3<float>(1, 1, 1), GVec3<float>(0.95f, 0.95f, 0.95f), -0.5f, TRS_LOOPTYPE::ROUNDTRIP, TRS_SPEEDTYPE::AVERAGE, 0, 0xFFFFFFFF);

	ingame_gameobject = Active_GSystem->Find(L"Ingame");
	Boss_gameobject = Active_GSystem->Find(L"Boss");
	ingame_gameobject_Ui = Active_GSystem->Find(L"Ingame_Ui");

	if(!ingame_gameobject_Ui)
	{
		GLog(L"Ingame_GameObject_Ui NULL");
		return;
	}

	if (!ingame_gameobject)
	{
		GLog(L"Ingame_GameObject NULL");
		return;
	}
	if(!Boss_gameobject)
	{
		GLog(L"Boss_gameobject NULL");
		return;
	}
	ingame_memmap = ingame_gameobject->Get_Component<MeMMap_Component>();
	ingame_Line = ingame_gameobject->Get_Component<Line_Component>();
	//ingame_Line->Active = false;
	Mask_Sc = Active_GSystem->Find(L"MaskBg")->Get_Component<SpriteRenderer_Component>();

	if(!ingame_Line)
	{
		GLog(L"Ingame_Line NULL");
		return;
	}
	if (!ingame_memmap)
	{
		GLog(L"Ingame_MemMap NULL");
		return;
	}

	Player_Life = 3;
	Hit_Check = false;
	IsEnemyDie_Check = false;
	MooJuck = false;
	J_Speed = 300;
	Boss_Pos = Boss_gameobject->transform.Get_LocalPosition();
}

void cPlayer::JInput()
{
	if (PlayerState == MOVEMODE::COMPLMOVE) return;

	if(PressKeys['A'] && PlayerState == MOVEMODE::NOMALMOVE)
	{
		KeyState = KEYSTATE::IDLE;
		PlayerState = MOVEMODE::ATTACKMOVE;
	}
	else if(!PressKeys['A'] && PlayerState == MOVEMODE::ATTACKMOVE)
	{
		KeyState = KEYSTATE::IDLE;

		if (ingame_Line->Active_LinePoint_Count > 0)
		{
			PlayerState = MOVEMODE::RETURNMOVE;
		}
		else
		{
			PlayerState = MOVEMODE::NOMALMOVE;
		}
	}

	if(DownKeys[VK_F1])
	{
		J_Speed += 300;
	}
	else if(DownKeys[VK_F2])
	{
		Active_GSystem->Change_Scene((DWORD)SCENE::STAGE2, SCENE_CHANGE_ACTION::FADE, GCOLOR(0, 0, 0, 1), 0);
	}
	else if (DownKeys[VK_F3])
	{
		Active_GSystem->Change_Scene((DWORD)SCENE::STAGE3, SCENE_CHANGE_ACTION::FADE, GCOLOR(0, 0, 0, 1), 0);
	}
	else if(DownKeys[VK_F4])
	{
		if (MooJuck)
			MooJuck = false;
		else
			MooJuck = true;
	}
}

GVec3<float> cPlayer::Calc_Step()
{
	GVec3<float> ms = {0, 0, 0};
	float ds = (J_Speed * DT);

	KeyState = KEYSTATE::IDLE;

	if (PressKeys[VK_UP])
	{
		ms = GVec3<float>(0, -ds * 0.01f,0);
		Direction = 0;
		KeyState = KEYSTATE::UP;
	}
	else if (PressKeys[VK_DOWN])
	{
		ms = GVec3<float>(0, ds * 0.01f, 0);
		Direction = 180;
		KeyState = KEYSTATE::DOWN;
	}
	else if (PressKeys[VK_LEFT])
	{
		ms = GVec3<float>(-ds * 0.01f, 0, 0);
		Direction = 90;
		KeyState = KEYSTATE::LEFT;
	}
	else if (PressKeys[VK_RIGHT])
	{
		ms = GVec3<float>(ds * 0.01f, 0, 0);
		Direction = 270;
		KeyState = KEYSTATE::RIGHT;
	}

	return ms;
}

void cPlayer::Get_FindNext_Pos(GVec3<float> ms)
{
	Find_Normal_Pos = Joo_Pos;
	Find_OutLine_Pos = Joo_Pos;
	Find_ActionLine_Pos = Joo_Pos;

	Find_Normal_OK = false;
	Find_OutLine_OK = false;
	Find_ActionLine_OK = false;
	Find_ClearArea_OK = false;
	

	for (int i = 0; i < 100; i++)
	{
		if ((int)Joo_Pos.x == (int)(Joo_Pos.x + ms.x * i) && (int)Joo_Pos.y == (int)(Joo_Pos.y + ms.y * i)) //같은 위치 방지
		{
			continue;
		}

		if (ingame_memmap->GetGap<char>(Joo_Pos.x + ms.x * i, Joo_Pos.y + ms.y * i) == (char)AREA::NORMAL)
		{
			Find_Normal_Pos = Joo_Pos + ms * i;
			Find_Normal_OK = true;
		}

		if (ingame_memmap->GetGap<char>(Joo_Pos.x + ms.x * i, Joo_Pos.y + ms.y * i) == (char)AREA::OUTLINE)
		{
			Find_OutLine_Pos = Joo_Pos + ms * i;
			Find_OutLine_OK = true;


			if(PlayerState == MOVEMODE::ATTACKMOVE)
			    return;
		}

		if (ingame_memmap->GetGap<char>(Joo_Pos.x + ms.x * i, Joo_Pos.y + ms.y * i) == (char)AREA::ACTION)
		{
			Find_ActionLine_Pos = Joo_Pos + ms * i;
			Find_ActionLine_OK = true;
		}

		if (ingame_memmap->GetGap<char>(Joo_Pos.x + ms.x * i, Joo_Pos.y + ms.y * i) == (char)AREA::CLEAR)
		{
			Find_ClearArea_OK = true;
		}
	}

	
}

void cPlayer::Delete_OutLine()
{

	for (int j = 0; j < PLAYG_HEIGHT; j++) {
		for (int i = 0; i < PLAYG_WIDTH; i++) {

			if (ingame_memmap->GetGap<char>(i, j) == (char)AREA::OUTLINE)
			{
				bool ck = false;

				for (int y = j - 1; y <= j + 1; y++) {
					for (int x = i - 1; x <= i + 1; x++) {

						if (ingame_memmap->GetGap<char>(x, y) == (char)AREA::NORMAL)
						{
							ck = true;
						}

					}
				}

				if (!ck)
				{
					ingame_memmap->SetGap<char>(i, j, (char)AREA::CLEAR);
				}

			}


		}
	}
}

void cPlayer::MeM2_MaskBg()
{
	for (int y = 0; y < PLAYG_HEIGHT; y++)
	{
		for (int x = 0; x < PLAYG_WIDTH; x++)
		{
			AREA Gap = (AREA)ingame_memmap->GetGap<char>(x, y);
			switch (Gap)
			{
			case AREA::OUTLINE:
				Mask_Sc->Set_Pixel_Color(x, y, 0, 255, 255, 255);
				break;
			case AREA::CLEAR:
				Mask_Sc->Set_Pixel_Alpha(x, y, 0);
				break;
			}
		}
	}

	Mask_Sc->UpdateTexture();
}

void cPlayer::Awake()
{

}

void cPlayer::Start()
{
	Player_Life = 3;

}

void cPlayer::Notice(Notice_Item* notice)
{


}

void cPlayer::Update()
{
	//Player_Life = 3;

	if (Player_Life <= 0)
	{
		gameObject->Active = false;
		ingame_Line->Active_LinePoint = 0;
		ingame_Line->Active_LinePoint_Count = 0;
	}

	JInput();

	Player_Die();

	switch (PlayerState)
	{
	case MOVEMODE::NOMALMOVE:
		NormalUpdate();
		break;
	case MOVEMODE::ATTACKMOVE:
		AttackUpdate();
		break;
	case MOVEMODE::RETURNMOVE:
		ReturnUpdate();
		break;
	case MOVEMODE::COMPLMOVE:
		ComplUpdate();
		break;
	}

	//GLog(L"Joo_x : %f , Joo_y : %f", Joo_Pos.x + PG_LEFT, Joo_Pos.y + PG_TOP);

	gameObject->transform.Set_LocalPosition(Joo_Pos.x + PG_LEFT, Joo_Pos.y + PG_TOP, 0);

	gameObject->transform.Set_LocalRotation(0, 0, Direction);

	//GLog(L"Get_Boss_pos: x: %d y: %d", Boss_Pos->x, Boss_Pos->y);
}

void cPlayer::Player_Die()
{
	if (Hit_Check && PlayerState != MOVEMODE::RETURNMOVE && !MooJuck) //플레이어 사망
	{
		Active_GScene->Set_Camera_Action(CAMERA_ACTION_TYPE::EARTHQUAKE3, -0.025, 1, 10);
		
		J_Speed = 300;
		PlayerState = MOVEMODE::RETURNMOVE;
		Player_Life -= 1; //체력감소
		LineColor = 0xFFFF0000; //빨간색
		Player_Color->Active = true;

		GameObject* Eff = new GameObject(L"Player_Die_Eff");
		Eff->Add_Component<cPlayer_Die_Eff>(L"Player_Die_Eff_Script");
		Eff->transform.Set_LocalPosition(Joo_Pos.x + PG_LEFT, Joo_Pos.y + PG_TOP, 0);
		//GameObject* Eff2 = Eff;
		Shoot_Sound->Play_Sound(false);
	}

}

void cPlayer::NormalUpdate()
{
	GVec3<float> ms = Calc_Step();

	if (ms.x != 0)
	{
		ms.x = ms.x;
	}

	Get_FindNext_Pos(ms);

	//if (ms.x != 0)
		//GLog(L"ms_x:%f ms_y%f", ms.x, ms.y);

	Joo_Pos.x = (float)(int)Find_OutLine_Pos.x;
	Joo_Pos.y = (float)(int)Find_OutLine_Pos.y;

	/*Joo_Pos.x = (float)(int)Find_Normal_Pos.x;
	Joo_Pos.y = (float)(int)Find_Normal_Pos.y;*/

	//GLog(L"Joo_x : %f , Joo_y : %f", Joo_Pos.x, Joo_Pos.y);

	//gameObject->transform.Set_LocalPosition(Joo_Pos.x + PG_LEFT, Joo_Pos.y + PG_TOP, 0);

	//gameObject->transform.Set_LocalPosition(pos);
	
}


void cPlayer::AttackUpdate()
{

	KEYSTATE OldKeyState = KeyState;

	GVec3<float> ms = Calc_Step();

	if (ms.x != 0)
	{
		ms.x = ms.x;
	}

	if (KeyState == KEYSTATE::IDLE) return;

	Get_FindNext_Pos(ms);

	if (Find_ActionLine_OK) return;

	bool ref = false;

	bool compl = false;

	AREA now_Area = (AREA)ingame_memmap->GetGap<char>(Joo_Pos.x, Joo_Pos.y);

	if(now_Area == AREA::OUTLINE && Find_Normal_OK)
	{

		Joo_Pos.x = (float)(int)Joo_Pos.x;
		Joo_Pos.y = (float)(int)Joo_Pos.y;

		ingame_Line->Set_Point(GVec2<float>(Joo_Pos.x + PG_LEFT, Joo_Pos.y + PG_TOP));
		ingame_Line->Add_Point(GVec2<float>(Joo_Pos.x + PG_LEFT, Joo_Pos.y + PG_TOP));
		GLog(L"처음");


		ref = true;
		Joo_Pos = Find_Normal_Pos;
	}
	if(now_Area == AREA::NORMAL && !Find_OutLine_OK && Joo_Pos != Find_Normal_Pos)
	{
		if(OldKeyState != KeyState)
		{
			ingame_Line->Add_Point(GVec2<float>(Joo_Pos.x + PG_LEFT, Joo_Pos.y + PG_TOP));
			OldKeyState = KeyState;
		}

		GLog(L"연장");

		ref = true;
		Joo_Pos = Find_Normal_Pos;
	}
	if(now_Area == AREA::NORMAL && Find_OutLine_OK)
	{
		if(OldKeyState != KeyState)
		{
			ingame_Line->Add_Point(GVec2<float>(Joo_Pos.x + PG_LEFT, Joo_Pos.y + PG_TOP));
			OldKeyState = KeyState;
		}

		GLog(L"완성");

		PlayerState = MOVEMODE::COMPLMOVE;
		ref = true;
		compl = true;

		Joo_Pos = Find_Normal_Pos;
	}

	Joo_Pos.x = (float)(int)Joo_Pos.x;
	Joo_Pos.y = (float)(int)Joo_Pos.y;

	ingame_Line->Set_Point(GVec2<float>(Joo_Pos.x + PG_LEFT, Joo_Pos.y + PG_TOP));

	if (ref)
	{
		//GLog(L"ingame_Line = %d\n", ingame_Line->Active_LinePoint_Count);
		Draw_Action_Line(true);
		if (!compl) ingame_memmap->SetGap<char>((int)Joo_Pos.x, (int)Joo_Pos.y, (char)AREA::NORMAL);
	}

	//ingame_Line->Active_LinePoint_Count = 0;
}


void cPlayer::ReturnUpdate()
{
	float ds = (J_Speed * DT);

	Draw_Action_Line(false);

	if(ingame_Line->Active_LinePoint < 1) //피격 후
	{
		PlayerState = MOVEMODE::NOMALMOVE;
		LineColor = 0xFF00FFFF; //하늘색
		Player_Color->Active = false;
		Player_Sc->Matrial_Color = 0xFFFFFFFF;
		return;
	}

	GVec2<float> Pos2, Pos1;
	GVec2<float> cha;
	float per, len;

	Pos1 = ingame_Line->ALine[ingame_Line->Active_LinePoint] - GVec2<float>(PG_LEFT, PG_TOP);
	Pos2 = ingame_Line->ALine[ingame_Line->Active_LinePoint - 1] - GVec2<float>(PG_LEFT, PG_TOP);

	cha = Pos1 - Pos2;
	len = Lenth(cha);
	per = ds / len;
	cha = cha * per;

	if (ds > len)
	{
		Pos1 = Pos2;
		ingame_Line->Del_Point();
	}
	else
	{
		GVec2<float> OldPos1 = Pos1;

		Pos1 -= cha;
		ingame_Line->ALine[ingame_Line->Active_LinePoint] = Pos1 + GVec2<float>(PG_LEFT, PG_TOP);

		if (OldPos1.y - Pos1.y > 0 && Pos1.y != OldPos1.y) Direction = 0; //돌아갈 때 방향
		else if (OldPos1.y - Pos1.y < 0 && Pos1.y != OldPos1.y) Direction = 180;
		else if (OldPos1.x - Pos1.x > 0 && Pos1.x != OldPos1.x) Direction = 90;
		else if (OldPos1.x - Pos1.x < 0 && Pos1.x != OldPos1.x) Direction = 270;

		//GLog(L"Pos1.x: %d Pos1.y: %d", (int)OldPos1.x - Pos1.x, (int)OldPos1.y - Pos1.y);
	}

	Joo_Pos = Pos1;

	Draw_Action_Line(true);

	Hit_Check = false; //hit_Off

	//GLog(L"%d", Direction);
}

void cPlayer::ComplUpdate()
{	
	bool Boss_Find = false;

	GRECT<int> LineRect = ingame_Line->Get_Rect();

	LineRect.top -= PG_TOP;
	LineRect.bottom -= PG_TOP;
	LineRect.left -= PG_LEFT;
	LineRect.right -= PG_LEFT;
	
	GVec2<int> fns;

	if(LineRect.top == LineRect.bottom || LineRect.right == LineRect.left) 
	{
		fns = ingame_memmap->Find_Gap((char)AREA::NORMAL);
	}
	else
	{
		fns = ingame_memmap->Find_Gap(LineRect, (char)AREA::NORMAL);
	}
	
	//GLog(L"%d %d %d %d= %d\n", ingame_Line->Active_LinePoint_Count);
	//GVec2<int> fns = ingame_memmap->Find_Gap<char>((char)AREA::NORMAL);

	ingame_memmap->Paint<char>((int)fns.x, (int)fns.y, (char)AREA::PAINT);

	if(ingame_memmap->GetGap<char>(Boss_Pos->x - PG_LEFT, Boss_Pos->y - PG_TOP) == (char)AREA::PAINT)
	{
		ingame_memmap->Change_Gap((char)AREA::NORMAL, (char)AREA::CLEAR);
		ingame_memmap->Change_Gap((char)AREA::PAINT, (char)AREA::NORMAL);
		ingame_memmap->Change_Gap((char)AREA::ACTION, (char)AREA::OUTLINE);
	}
	else
	{
		ingame_memmap->Change_Gap((char)AREA::PAINT, (char)AREA::CLEAR);
		ingame_memmap->Change_Gap((char)AREA::ACTION, (char)AREA::OUTLINE);
	}
	
	Delete_OutLine();
	
	ClearPer = (100 * (float)ingame_memmap->Count_Gap<char>((char)AREA::CLEAR)) / (PLAYG_HEIGHT * PLAYG_WIDTH);
	Score = (float)ingame_memmap->Count_Gap<char>((char)AREA::CLEAR) * 0.04;

	TotalScore += Score;

	MeM2_MaskBg();

	IsEnemyDie_Check = true;

	ingame_Line->Active_LinePoint_Count = 1;
	ingame_Line->Active_LinePoint = 0;
	PlayerState = MOVEMODE::NOMALMOVE;
	
	Electricity_Sound->Play_Sound(false);
}

void cPlayer::Draw_Action_Line(bool draw)
{

	if (ingame_Line->Active_LinePoint_Count < 2) return;

	GVec2<float> Pos1, Pos2;
	GVec2<float> cha;
	float len;

	for (int i = 0; i < ingame_Line->Active_LinePoint; i++)
	{
		Pos2 = ingame_Line->ALine[i + 1] - GVec2<float>(PG_LEFT, PG_TOP);
		Pos1 = ingame_Line->ALine[i] - GVec2<float>(PG_LEFT, PG_TOP);

		cha = Pos2 - Pos1;
		len = Lenth(cha);
		cha = cha / (len * 4);

		for(int j = 0; j < (len *4); j++)
		{
			Pos1 += cha;
			
			if (!draw)
			{
				ingame_memmap->SetGap<char>((int)Pos1.x, (int)Pos1.y, (char)AREA::NORMAL);
			}
			else
			{
				ingame_memmap->SetGap<char>((int)Pos1.x, (int)Pos1.y, (char)AREA::ACTION);
			}
		}
	}
}

void cPlayer::Play_Sound(CSound* SoundCLIP, bool Loop)
{
	if (!SoundCLIP) return;

	//SoundCLIP->Stop();

	if (Loop)
	{
		DWORD dwFlags = DSBPLAY_LOOPING;
		SoundCLIP->Play(0, dwFlags);
	}
	else
	{
		SoundCLIP->Play(0, NULL);

		//Log(L"사운드출력");
	}
}

void cPlayer::CreateDevice()
{
	MeM2_MaskBg();
}

void cPlayer::Late_Update()
{

}

void cPlayer::Final_Update()
{

}

void cPlayer::Render()
{

}

void cPlayer::Reload()
{

}

void cPlayer::Change()
{

}

void cPlayer::Release()
{
	delete this;
}
