#include "DXUT.h"
#include "cStage1_Enemy.h"
#include "GSystem.h"
#include "cPlayer_Die_Eff.h"
#include "cEnemy_Die_Eff.h"
#include "cEnemy_BaseBullet.h"
#include "GFunc.h"

extern GSystem* Active_GSystem;
extern bool Hit_Check;
extern MOVEMODE PlayerState;
extern bool IsEnemyDie_Check;
extern GameObject* Eff_Prefab;
extern GameObject* Bullet_Prefab;

extern SoundCLIP_Component* Shoot_Sound;

cStage1_Enemy::cStage1_Enemy()
{

}

cStage1_Enemy::~cStage1_Enemy()
{

}

void cStage1_Enemy::NEW()
{

}

void cStage1_Enemy::Awake()
{
	
}

void cStage1_Enemy::Start()
{
	gameObject->Set_Center(true);
	Enemy_Pos = GVec3<float>(rand() % PLAYG_WIDTH, rand() % PLAYG_HEIGHT, 0);
	//gameObject->transform.Set_LocalPosition(rand() % PLAYG_WIDTH, rand() % PLAYG_HEIGHT, 0);
	gameObject->transform.Set_LocalScale(GVec3<float>(0.5f, 0.5f, 0));
	gameObject->Render_Stack = 4; //Àû

	ingame_gameobject = Active_GSystem->Find(L"Ingame");
	Player_gameobject = Active_GSystem->Find(L"Player");

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
	J_Speed = 80;

}

void cStage1_Enemy::Notice(Notice_Item* notice)
{


}

bool cStage1_Enemy::Col_Check(GVec2<float> min, GVec2<float> max, AREA area)
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

void cStage1_Enemy::Update()
{
	WorldTime = timeGetTime();

	if (Col_Check(GVec2<float>(Enemy_Pos.x - 64, Enemy_Pos.y - 64), GVec2<float>(Enemy_Pos.x + 64, Enemy_Pos.y + 64), AREA::ACTION)) //ÇÃ·¹ÀÌ¾î »ç¸Á
	{
		Hit_Check = true;
	}

	if(ingame_memmap->GetGap<char>(Enemy_Pos.x, Enemy_Pos.y) == (char)AREA::CLEAR)/* && IsEnemyDie_Check == true*/ // Àû »ç¸Á
	{
		GameObject* Eff = Active_GSystem->Instantiate(Eff_Prefab);
		Eff->transform.Set_LocalPosition(Enemy_Pos.x + PG_LEFT, Enemy_Pos.y + PG_TOP, 0);
		Eff->Prefab = false;
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
			J_Time = WorldTime + (rand() % 1) * 1000;
			Sel = ENEMY_STATE::ENEMY_THINKING;
			break;

		case 1:
		{
			TarGetPos = GVec3<float>(rand() % PLAYG_WIDTH, rand() % PLAYG_HEIGHT, 0);
			gameObject->Get_Component<FrameAni_Component>()->Set_Ani_Item(&Enemy_Walking);
			GVec3<float> cha = TarGetPos - Enemy_Pos;
			ang = Get_Degree2D(GVec2<float>(0, -1), GVec2<float>(cha.x, cha.y));
			gameObject->transform.Set_LocalRotation(ang);
			Sel = ENEMY_STATE::ENEMY_MOVE;
			
			break;
		}
			
		case 2:
			gameObject->Get_Component<FrameAni_Component>()->Set_Ani_Item(&Enemy_Attack);
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

		if (DS > len) // µµÂø
		{
			Enemy_Pos = TarGetPos;
			Sel = ENEMY_STATE::ENEMY_IDLE;
		}
		else //°¡´Â Áß
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
		float Bullet_ang = atan2(Player_gameobject->transform.Get_LocalPosition()->y - (Enemy_Pos.y + PG_TOP), Player_gameobject->transform.Get_LocalPosition()->x - (Enemy_Pos.x + PG_LEFT));
		GVec3<float> cha = *Player_gameobject->transform.Get_LocalPosition() - *gameObject->transform.Get_LocalPosition();
		ang = Get_Degree2D(GVec2<float>(0, -1), GVec2<float>(cha.x, cha.y));
		//ang = Get_Degree2D_C(GVec2<float>(cha.x, cha.y));
		//float A = Get_Degree2D(GVec2<float>(0, -1), GVec2<float>(1, 0));
		//ang = 90;
		gameObject->transform.Set_LocalRotation(ang);
		GameObject* Bullet = Active_GSystem->Instantiate(Bullet_Prefab);
		Bullet->Render_Stack = 4;
		Bullet->Set_Center(true);
		Bullet->Get_Component<cEnemy_BaseBullet>(L"cEnemy_BaseBullet_Script")->BulletSet(Enemy_Pos, 300, Bullet_ang, false, false);
		Bullet->Prefab = false;

		J_Time = WorldTime + 1000;
		Sel = ENEMY_STATE::ENEMY_THINKING;
		break;
	}
	case ENEMY_STATE::ENEMY_DEAD:
	{
		gameObject->Active = false;
	}
	}

	gameObject->transform.Set_LocalPosition(Enemy_Pos.x + PG_LEFT, Enemy_Pos.y + PG_TOP, 0);
}

void cStage1_Enemy::Late_Update()
{

}

void cStage1_Enemy::Final_Update()
{

}

void cStage1_Enemy::Render()
{

}

void cStage1_Enemy::Reload()
{

}

void cStage1_Enemy::Change()
{

}

void cStage1_Enemy::Release()
{
	delete this;
}
