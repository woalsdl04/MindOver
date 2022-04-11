#include "DXUT.h"
#include "cStage3_Boss.h"
#include "GSystem.h"
#include "cPlayer_Die_Eff.h"
#include "cEnemy_BaseBullet.h"
#include "cGameClear.h"
#include "cStage3_Boss.h"

extern GSystem* Active_GSystem;
extern GameObject* Bullet_Prefab;
extern GameObject* Boss3_Die_Eff_Prefab;

extern bool IsDie;

extern float ClearPer;
extern bool Hit_Check;

cStage3_Boss::cStage3_Boss()
{

}

cStage3_Boss::~cStage3_Boss()
{

}


bool cStage3_Boss::Col_Check(GVec2<float> min, GVec2<float> max, AREA area)
{
	for (int i = min.y; i < max.y; i++)
	{
		for (int j = min.x; j < max.x; j++)
		{
			if (ingame_memmap->GetGap<char>(j, i) == (char)area)
			{
				return true;
			}

		}
	}

	return false;
}

void cStage3_Boss::NEW()
{
	Boss_Sc = gameObject->Add_Component<SpriteRenderer_Component>(L"Boss_Sc");
	Boss_Sc->Load_Texture(L"Stage3/Stage3_Boss.png", 5, 1, false);

	Boss_Sc->Lock_Check();

	IsDie = false;

	gameObject->Set_Center(true);
	Enemy_Pos = GVec3<float>(WISIZE_X / 2 - PG_LEFT, WISIZE_Y / 2 - PG_TOP, 0);
	//gameObject->transform.Set_LocalPosition(WISIZE_X/2 , WISIZE_Y/2, 0);
	gameObject->Render_Stack = 5;

	ingame_gameobject = Active_GSystem->Find(L"Ingame");

	if (!ingame_gameobject)
	{
		GLog(L"Ingame_GameObject NULL");
		return;
	}

	ingame_memmap = ingame_gameobject->Get_Component<MeMMap_Component>(L"Ingame_MeMMap");

	if (!ingame_memmap)
	{
		GLog(L"Ingame_MemMap NULL");
		return;
	}

	Boss_Color = gameObject->Add_Component<Color_Component>(L"Boss_Cr");
	Boss_Color->Setup(GCOLOR(1, 1, 1, 1), GCOLOR(1, 0, 0, 1), -0.5f, COLOR_ACTIONTYPE::ROUNDTRIP, 0xFFFFFFFF);
	Boss_Color->Active = false;

	Boss_Trs = gameObject->Add_Component<TRS_Component>(L"Boss_Trs");
	Boss_Trs->Set_TRS(TRS_ENUM::SCALE, GVec3<float>(1, 1, 1), GVec3<float>(0.95f, 0.95f, 0.95f), -0.5f, TRS_LOOPTYPE::ROUNDTRIP, TRS_SPEEDTYPE::AVERAGE, 0, 0xFFFFFFFF);
	Boss_Trs->Active = false;
	
	gameObject->Add_Component<FrameAni_Component>(L"cStage3_Boss_Ani")->Set_FrameTime(75, true);

	J_Pos = gameObject->transform.Get_LocalPosition();
	J_Speed = 450;
	BulletCount = 20;
	ang = 0;
	rotate = 360 / BulletCount;
	Time = 0;
}

void cStage3_Boss::Awake()
{

}

void cStage3_Boss::Start()
{
	Count = 0;
	Attack_Count = 0;
}

void cStage3_Boss::Notice(Notice_Item* notice)
{

}

void cStage3_Boss::Update()
{
	Time += DT;
	
	int line = 2;

	if (Col_Check(GVec2<float>(Enemy_Pos.x - 128, Enemy_Pos.y - 128), GVec2<float>(Enemy_Pos.x + 128, Enemy_Pos.y + 128), AREA::ACTION))
	{
		Hit_Check = true;
	}

	WorldTime = timeGetTime();

	if(ClearPer >= 25)
		line = 3;

	if (ClearPer >= 50) //보스 흥분 <클리어 게이지 50이상>
	{
		line = 4;
		Boss_Color->Active = true;
		Boss_Trs->Active = true;
		J_Speed = 700; //보스 이동속도 업
	}
	if (ClearPer >= 80)
	{
		Sel = ENEMY_STATE::ENEMY_DEAD;
	}
	else
	{
		if (Time <= 0.05)
			return;

		for (int i = 0; i < line; i++)
		{
			Bullet = Active_GSystem->Instantiate(Bullet_Prefab);
			Bullet->Render_Stack = 4;
			Bullet->Set_Center(true);
			Bullet->Get_Component<cEnemy_BaseBullet>(L"cEnemy_BaseBullet_Script")->BulletSet(Enemy_Pos, 600, ang, true, true);
			Bullet->Prefab = false;
			ang += 360 / line;
		}
		ang += 2;


		Time = 0;
	}

	
	int r;

	switch (Sel)
	{
	case ENEMY_STATE::ENEMY_DEAD:
	{
		Enemy_Pos.y += 0.5f;

		int Rand_X = GRand(-128, 128) + PG_LEFT;
		int Rand_Y = GRand(-128, 128) + PG_TOP;

		if (Count > 25)
		{
			IsDie = true;
			gameObject->Active = false;
		}

		if (Time > 0.15f)
		{
			Active_GScene->Set_Camera_Action(CAMERA_ACTION_TYPE::EARTHQUAKE3, -0.04, 1, 10);
			Eff = Active_GSystem->Instantiate(Boss3_Die_Eff_Prefab);
			//Eff->transform.Set_LocalScale(0.5, 0.5, 0.5);
			Eff->transform.Set_LocalPosition(Enemy_Pos.x + Rand_X, Enemy_Pos.y + Rand_Y, 0);
			Eff->Prefab = false;
			Count++;
			Time = 0;
		}
		break;
	}
	}

	gameObject->transform.Set_LocalPosition(Enemy_Pos.x + PG_LEFT, Enemy_Pos.y + PG_TOP, 0);

}

void cStage3_Boss::Late_Update()
{

}

void cStage3_Boss::Final_Update()
{

}

void cStage3_Boss::Render()
{

}

void cStage3_Boss::Reload()
{

}

void cStage3_Boss::Change()
{

}

void cStage3_Boss::Release()
{
	delete this;
}
