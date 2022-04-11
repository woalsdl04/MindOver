#include "DXUT.h"
#include "cStage1_Boss.h"
#include "GSystem.h"
#include "cPlayer_Die_Eff.h"
#include "cEnemy_BaseBullet.h"
#include "cGameClear.h"

extern GSystem* Active_GSystem;
extern GameObject* Bullet_Prefab;
extern GameObject* Boss12_Die_Eff_Prefab;
extern SoundCLIP_Component* Shoot_Sound;

extern bool IsDie;

extern float ClearPer;
extern bool Hit_Check;

cStage1_Boss::cStage1_Boss()
{

}

cStage1_Boss::~cStage1_Boss()
{

}


bool cStage1_Boss::Col_Check(GVec2<float> min, GVec2<float> max, AREA area)
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

void cStage1_Boss::NEW()
{
	Boss_Sc = gameObject->Add_Component<SpriteRenderer_Component>(L"Boss_Sc");
	Boss_Sc->Load_Texture(L"Stage1/Stage1_Boss.png", 1, 1, false);

	Boss_Sc->Lock_Check();
	
	IsDie = false;

	gameObject->Set_Center(true);
	Enemy_Pos = GVec3<float>(WISIZE_X / 2, WISIZE_Y / 2, 0);
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

	J_Pos = gameObject->transform.Get_LocalPosition();
	J_Speed = 300;
	BulletCount = 15;
	ang = 0;
	rotate = 360 / BulletCount;
	Time = 0;

	
}

void cStage1_Boss::Awake()
{

}

void cStage1_Boss::Start()
{
	Count = 0;
}

void cStage1_Boss::Notice(Notice_Item* notice)
{
	
}

void cStage1_Boss::Update()
{
	Time += DT;

	if(Col_Check(GVec2<float>(Enemy_Pos.x - 128, Enemy_Pos.y - 128), GVec2<float>(Enemy_Pos.x + 128, Enemy_Pos.y + 128), AREA::ACTION))
	{
		Hit_Check = true;
	}

	WorldTime = timeGetTime();

	if(ClearPer >= 50) //보스 흥분 <클리어 게이지 50이상>
	{
		Boss_Color->Active = true;
		Boss_Trs->Active = true;
		J_Speed = 500; //보스 이동속도 업
	}
	if(ClearPer >= 80)
	{
		Sel = ENEMY_STATE::ENEMY_DEAD;
	}

	int r;
	switch (Sel)
	{
		case ENEMY_STATE::ENEMY_IDLE:
			r = rand() % 5;

			switch (r)
			{
			default:
				J_Time = WorldTime + (rand() % 2) * 1000;
				Sel = ENEMY_STATE::ENEMY_THINKING;
				break;

			case 1:

				TarGetPos = GVec3<float>(rand() % PLAYG_WIDTH, rand() % PLAYG_HEIGHT, 0);
				Sel = ENEMY_STATE::ENEMY_MOVE;

				break;
			case 2:
				Sel = ENEMY_STATE::ENEMY_ATTACK;
				break;
			}

			break;
		case ENEMY_STATE::ENEMY_THINKING:
			if (J_Time < WorldTime)
			{

				Sel = ENEMY_STATE::ENEMY_IDLE;
			}
			break;
		case ENEMY_STATE::ENEMY_MOVE:
		{
			GVec3<float> cha = (TarGetPos - Enemy_Pos);
			float len = Lenth(cha);
			float DS = J_Speed * DT;
			GVec3<float> Ex = cha * (DS / len);

			if (DS > len) // 도착
			{
				Enemy_Pos = TarGetPos;
				Sel = ENEMY_STATE::ENEMY_IDLE;
			}
			else //가는 중
			{
				if (ingame_memmap->GetGap<char>(Enemy_Pos.x + Ex.x, Enemy_Pos.y + Ex.y) != (char)AREA::NORMAL)
				{
					Sel = ENEMY_STATE::ENEMY_IDLE;
					return;
				}

				Enemy_Pos = Enemy_Pos + Ex;

			}

			//J_Pos = Vec2(0, 0);

			break;
		}
		case ENEMY_STATE::ENEMY_ATTACK:
		{
			//Shoot_Sound->Play_Sound(false);

			for (int B = 0; B < BulletCount; B++)
			{
				Bullet = Active_GSystem->Instantiate(Bullet_Prefab);
				Bullet->Render_Stack = 4;
				Bullet->Set_Center(true);
				Bullet->Get_Component<cEnemy_BaseBullet>(L"cEnemy_BaseBullet_Script")->BulletSet(Enemy_Pos, 300, ang, true, false);
				Bullet->Prefab = false;
				ang += rotate;
			}

			J_Time = WorldTime + (rand() % 2) * 1000;
			Sel = ENEMY_STATE::ENEMY_THINKING;

			break;
		}
		case ENEMY_STATE::ENEMY_DEAD:
		{
			Enemy_Pos.y += 0.5f;

			int Rand_X = GRand(-128, 128) + PG_LEFT;
			int Rand_Y = GRand(-128, 128) + PG_TOP;
				
			if(Count > 25)
			{
				IsDie = true;
				gameObject->Active = false;
			}

			if (Time > 0.25f)
			{
				Active_GScene->Set_Camera_Action(CAMERA_ACTION_TYPE::EARTHQUAKE3, -0.025, 1, 10);
				Eff = Active_GSystem->Instantiate(Boss12_Die_Eff_Prefab);
				Eff->transform.Set_LocalScale(0.5, 0.5, 0.5);
				Eff->transform.Set_LocalPosition(Enemy_Pos.x + Rand_X, Enemy_Pos.y + Rand_Y, 0);
				Eff->Prefab = false;
				Count++;
				Time = 0;
			}
				//Ingame->Set_Exp(J_Pos.x + Rand_X, J_Pos.y + Rand_Y, 0xFFFFFFFF);
			//if (J_Time + 2000 < WorldTime) //스테이지 전환
			//{
			//	IsDie = true;
			//}
			break;
		}
	}

	gameObject->transform.Set_LocalPosition(Enemy_Pos.x + PG_LEFT, Enemy_Pos.y + PG_TOP, 0);

}

void cStage1_Boss::Late_Update()
{

}

void cStage1_Boss::Final_Update()
{

}

void cStage1_Boss::Render()
{

}

void cStage1_Boss::Reload()
{

}

void cStage1_Boss::Change()
{

}

void cStage1_Boss::Release()
{
	delete this;
}
