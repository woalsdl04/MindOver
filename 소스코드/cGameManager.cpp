#include "DXUT.h"
#include "cGameManager.h"
#include "cTitle.h"
#include "cIngame.h"
#include "cIngameManager.h"
#include "cIngame_Ui.h"
#include "cGame_Start_Ui.h"
#include "cPlayer.h"
#include "cPlayer_Life.h"
#include "cHp_Item.h"
#include "cSpeedUp_Item.h"
#include "cBg.h"
#include "cStage1_Boss.h"
#include "cStage1_Enemy.h"
#include "cStage1_Enemy_Dog.h"
#include "cStage2_Boss.h"
#include "cStage2_Enemy_Poison.h"
#include "cStage3_Boss.h"
#include "cEnemy_BaseBullet.h"
#include "cEnemy_Rocket.h"
#include "cEnemy_Gas.h"
#include "cBoss12_Die_Eff.h"
#include "cBoss3_Die_Eff.h"
#include "cMaskBg.h"
#include "GSystem.h"


extern GScene* Active_GScene;
extern GSystem* Active_GSystem;

GameObject* Bullet_Prefab = NULL;
GameObject* Rocket_Prefab = NULL;
GameObject* Gas_Prefab = NULL;
GameObject* Boss12_Die_Eff_Prefab = NULL;
GameObject* Boss3_Die_Eff_Prefab = NULL;

SoundCLIP_Component* Shoot_Sound = NULL;
SoundCLIP_Component* Warning_Sound = NULL;
SoundCLIP_Component* Explosion_Sound = NULL;
SoundCLIP_Component* PowerUp_Sound = NULL;
SoundCLIP_Component* Electricity_Sound = NULL;
SoundCLIP_Component* End_Sound = NULL;

int Stage = 1;
int Score = 0;
int TotalScore = 0;

void cGameManager::Change_Scene(DWORD ID)
{

	switch ((SCENE)ID)
	{
	case SCENE::MENU:
		{
			Title_Bg = new GameObject(L"Title");
			Title_Bg->Add_Component<cTitle>(L"Title_Script");
			
			//Title->transform.Set_LocalScale(1, 1, 0);
			
			//Active_GScene->Frame_View_All = false;		// 해당 신에 관련된 것을 로딩한다

			Active_GSystem->Change_Music(L"./Res/Sound/REVENANT.wav", true, 100, BGM_VOLUME_FADE::NOW);

			break;
		}
	case SCENE::READY:
	{
		break;
	}
	case SCENE::STAGE1:
		{
			Ingame_Base_Bg = new GameObject(L"BBg");
			Ingame_Bg = new GameObject(L"Ingame_Bg");
			MaskBg = new GameObject(L"MaskBg");
			Ingame = new GameObject(L"Ingame");
			Boss = new GameObject(L"Boss");
			Player = new GameObject(L"Player");
			Ingame_Ui = new GameObject(L"Ingame_Ui");
			Player_Life_MN = new GameObject(L"Player_Life_MN");
			Ingame_Manager = new GameObject(L"Ingame_Manager");
			Hp_Item = new GameObject(L"Hp_Item");
			SpeedUp_Item = new GameObject(L"SpeedUp_Item");
			Active_GScene->Camera_Sprite->Load_Texture(L"Warning/Warning_Bg.png", 1, 1, false);
			Active_GScene->Camera_Sprite->Active = false;
			
			SpriteRenderer_Component* BBg_Sc = Ingame_Base_Bg->Add_Component<SpriteRenderer_Component>(L"BBg_Sc");
			BBg_Sc->Load_Texture(L"Stage1/BBg.png", 1, 1, false);
			Ingame_Base_Bg->Render_Stack = 0;

			Stage1_Enemy_Man_Prefab = new GameObject(L"Stage1_Enemy_Man");
			Stage1_Enemy_Man_Prefab->Prefab = true;
			Enemy_Sc = Stage1_Enemy_Man_Prefab->Add_Component<SpriteRenderer_Component>(L"Stage1_Enemy_Man_Sc");
			Enemy_Sc->Load_Texture(L"Stage1/Stage1_Enemy_Man.png", 10, 1, false);
			Enemy_Sc->Lock_Check();
			Stage1_Enemy_Man_Prefab->Add_Component<FrameAni_Component>(L"Stage1_Enemy_Man_Prefab_Ani");
			//Stage1_Enemy_Man_Prefab->Get_Component<FrameAni_Component>()->Set_FrameTime(75, true);
			Stage1_Enemy_Man_Prefab->Add_Component<cStage1_Enemy>(L"Stage1_Enemy_Man_Script");


			Stage1_Enemy_Dog_Prefab = new GameObject(L"Stage1_Enemy_Dog");
			Stage1_Enemy_Dog_Prefab->Prefab = true;
			Stage1_Enemy_Dog_Prefab->transform.Set_LocalScale(GVec3<float>(0.5f, 0.5f, 0));
			Enemy_Sc = Stage1_Enemy_Dog_Prefab->Add_Component<SpriteRenderer_Component>(L"Stage1_Enemy_Dog");
			Enemy_Sc->Load_Texture(L"Stage1/1스테이지 잡몹2.png", 1, 1, false);
			Enemy_Sc->Lock_Check();
			Stage1_Enemy_Dog_Prefab->Add_Component<cStage1_Enemy_Dog>(L"Stage1_Enemy_Dog");

			
			Ingame_Bg->Add_Component<cBg>(L"Bg_Script");
			MaskBg->Add_Component<cMaskBg>(L"Mask_Script");
			Ingame->Add_Component<cIngame>(L"Ingame_Script");
			Boss->Add_Component<cStage1_Boss>(L"Boss_Script");
			/*	for (int i = 0; i < 3; i++)
					Enemy[i]->Add_Component<cEnemy>(L"Enemy_Script");*/
			Ingame_Ui->Add_Component<cIngame_Ui>(L"Ingame_Ui_Script");
			Player->Add_Component<cPlayer>(L"Player_Script");
			Player_Life_MN->Add_Component<cPlayer_Life>(L"Player_Life_Script");
			Ingame_Manager->Add_Component<cIngameManager>(L"cIngame_Manager_Script");
			Hp_Item->Add_Component<cHp_Item>(L"cHp_Item_Script");
			SpeedUp_Item->Add_Component<cSpeedUp_Item>(L"cSpeedUp_Item_Script");
			for(int i = 0; i < 2; i++)
			{
				Stage1_Enemy_Man[i] = Active_GSystem->Instantiate(Stage1_Enemy_Man_Prefab);
				Stage1_Enemy_Man[i]->Render_Stack = 3; //적
				Stage1_Enemy_Man[i]->Prefab = false;
				Stage1_Enemy_Dog[i] = Active_GSystem->Instantiate(Stage1_Enemy_Dog_Prefab);
				Stage1_Enemy_Dog[i]->Render_Stack = 3; //적
				Stage1_Enemy_Dog[i]->Prefab = false;
			}

			Bullet_Prefab = new GameObject(L"Bullet");
			Bullet_Prefab->Prefab = true;
			Bullet_Prefab->Add_Component<SpriteRenderer_Component>(L"Bullet_Sc")->Load_Texture(L"Enemy_Bullet.png", 1, 1, false);
			Bullet_Prefab->Get_Component<SpriteRenderer_Component>()->Lock_Check();
			Bullet_Prefab->Add_Component<cEnemy_BaseBullet>(L"cEnemy_BaseBullet_Script");
			Bullet_Prefab->Add_Component<TRS_Component>(L"Bullet_Prefabs_Trs")->Set_TRS(TRS_ENUM::SCALE, GVec3<float>(1, 1, 1), GVec3<float>(0.8f, 0.8f, 0.8f), -0.5f, TRS_LOOPTYPE::ROUNDTRIP, TRS_SPEEDTYPE::AVERAGE, 0, 0xFFFFFFFF);

			Boss12_Die_Eff_Prefab = new GameObject(L"Boss12_Die_Eff_Prefab");
			Boss12_Die_Eff_Prefab->Prefab = true;
			Boss12_Die_Eff_Prefab->Set_Center(true);
			Boss12_Die_Eff_Prefab->Render_Stack = 6;
			Boss12_Die_Eff_Prefab->Add_Component<cBoss12_Die_Eff>(L"Boss12_Die_Eff_Prefab_Script");
			Boss12_Die_Eff_Prefab->Add_Component<SpriteRenderer_Component>(L"Boss12_Die_Eff_Prefab_Sc");
			Boss12_Die_Eff_Prefab->Get_Component<SpriteRenderer_Component>()->Load_Texture(L"Eff/Boss_Die_Eff.png", 4, 6, false);
			Boss12_Die_Eff_Prefab->Get_Component<SpriteRenderer_Component>()->Lock_Check();
			Boss12_Die_Eff_Prefab->Add_Component<FrameAni_Component>(L"Enemy_Die_Eff_Ani")->Set_FrameTime(50, false);
			
			Active_GSystem->Change_Music(L"./Res/Sound/SuperPower.mp3", true, 100, BGM_VOLUME_FADE::NOW);
			
			Shoot_Sound = Ingame_Manager->Add_Component<SoundCLIP_Component>(L"Shoot_Sound");
			Shoot_Sound->Load_Sound(L"./Res/Sound/Shoot22.WAV", 2);
			Shoot_Sound->Lock_Check();

			Warning_Sound = Ingame_Manager->Add_Component<SoundCLIP_Component>(L"Warning_Sound");
			Warning_Sound->Load_Sound(L"./Res/Sound/Warning.WAV", 1);
			Warning_Sound->Lock_Check();

			Explosion_Sound = Ingame_Manager->Add_Component<SoundCLIP_Component>(L"Explosion_Sound");
			Explosion_Sound->Load_Sound(L"./Res/Sound/Explosion.WAV", 10);
			Explosion_Sound->Lock_Check();

			PowerUp_Sound = Ingame_Manager->Add_Component<SoundCLIP_Component>(L"PowerUp_Sound");
			PowerUp_Sound->Load_Sound(L"./Res/Sound/PowerUp.WAV", 2);
			PowerUp_Sound->Lock_Check();

			Electricity_Sound = Ingame_Manager->Add_Component<SoundCLIP_Component>(L"Electricity_Sound");
			Electricity_Sound->Load_Sound(L"./Res/Sound/Electricity.WAV", 2);
			Electricity_Sound->Lock_Check();
			
			End_Sound = Ingame_Manager->Add_Component<SoundCLIP_Component>(L"End_Sound");
			End_Sound->Load_Sound(L"./Res/Sound/End.WAV", 2);
			End_Sound->Lock_Check();

			// 해당 신에 관련된 것을 로딩한다
			//Bg->Add_Component<MeMMap_Component>(L"Bg_AlpaMap")->Init_Setup<BYTE>(1920, 1080);
			//Bg->Add_Component<MeMMap_Component>(L"Bg_AttribMap")->Init_Setup<BYTE>(1920, 1080);
			break;
		}
	case SCENE::STAGE2:
	{

		Ingame_Base_Bg = new GameObject(L"BBg");
		Ingame_Bg = new GameObject(L"Ingame_Bg");
		MaskBg = new GameObject(L"MaskBg");
		Ingame = new GameObject(L"Ingame");
		Boss = new GameObject(L"Boss");
		Player = new GameObject(L"Player");
		Ingame_Ui = new GameObject(L"Ingame_Ui");
		Player_Life_MN = new GameObject(L"Player_Life_MN");
		Ingame_Manager = new GameObject(L"Ingame_Manager");
		Hp_Item = new GameObject(L"Hp_Item");
		SpeedUp_Item = new GameObject(L"SpeedUp_Item");
		Active_GScene->Camera_Sprite->Load_Texture(L"Warning/Warning_Bg.png", 1, 1, false);
		Active_GScene->Camera_Sprite->Active = false;

		SpriteRenderer_Component* BBg_Sc = Ingame_Base_Bg->Add_Component<SpriteRenderer_Component>(L"BBg_Sc");
		BBg_Sc->Load_Texture(L"Stage2/BBg.png", 1, 1, false);
		Ingame_Base_Bg->Render_Stack = 0;
			
		Ingame_Bg->Add_Component<cBg>(L"Bg_Script");
		MaskBg->Add_Component<cMaskBg>(L"Mask_Script");
		Ingame->Add_Component<cIngame>(L"Ingame_Script");
		Boss->Add_Component<cStage2_Boss>(L"Boss_Script");
		/*	for (int i = 0; i < 3; i++)
				Enemy[i]->Add_Component<cEnemy>(L"Enemy_Script");*/
		Ingame_Ui->Add_Component<cIngame_Ui>(L"Ingame_Ui_Script");
		Player->Add_Component<cPlayer>(L"Player_Script");
		Player_Life_MN->Add_Component<cPlayer_Life>(L"Player_Life_Script");
		Ingame_Manager->Add_Component<cIngameManager>(L"cIngame_Manager_Script");
		Hp_Item->Add_Component<cHp_Item>(L"cHp_Item_Script");
		SpeedUp_Item->Add_Component<cSpeedUp_Item>(L"cSpeedUp_Item_Script");

		Stage2_Enemy_Gas_Prefab = new GameObject(L"Stage2_Enemy_Poison");
		Stage2_Enemy_Gas_Prefab->Prefab = true;
		Enemy_Sc = Stage2_Enemy_Gas_Prefab->Add_Component<SpriteRenderer_Component>(L"Stage2_Enemy_Poison_Sc");
		Enemy_Sc->Load_Texture(L"Stage2/Stage2_Enemy_Gas.png", 1, 1, false);
		Enemy_Sc->Lock_Check();
		Stage2_Enemy_Gas_Prefab->Add_Component<cStage2_Enemy_Poison>(L"Stage2_Enemy_Poison_Script");

		Stage1_Enemy_Dog_Prefab = new GameObject(L"Stage1_Enemy_Dog");
		Stage1_Enemy_Dog_Prefab->Prefab = true;
		Stage1_Enemy_Dog_Prefab->transform.Set_LocalScale(GVec3<float>(0.5f, 0.5f, 0));
		Enemy_Sc = Stage1_Enemy_Dog_Prefab->Add_Component<SpriteRenderer_Component>(L"Stage1_Enemy_Dog");
		Enemy_Sc->Load_Texture(L"Stage2/2스테이지 잡몹2.png", 1, 1, false);
		Enemy_Sc->Lock_Check();
		Stage1_Enemy_Dog_Prefab->Add_Component<cStage1_Enemy_Dog>(L"Stage1_Enemy_Dog");

		for (int i = 0; i < 2; i++)
		{
			Stage2_Enemy_Gas[i] = Active_GSystem->Instantiate(Stage2_Enemy_Gas_Prefab);
			Stage2_Enemy_Gas[i]->Render_Stack = 3; //적
			Stage2_Enemy_Gas[i]->Prefab = false;
			Stage1_Enemy_Dog[i] = Active_GSystem->Instantiate(Stage1_Enemy_Dog_Prefab);
			Stage1_Enemy_Dog[i]->Render_Stack = 3; //적
			Stage1_Enemy_Dog[i]->Prefab = false;
		}

		Bullet_Prefab = new GameObject(L"Bullet");
		Bullet_Prefab->Prefab = true;
		Bullet_Prefab->Add_Component<SpriteRenderer_Component>(L"Bullet_Sc")->Load_Texture(L"Enemy_Bullet.png", 1, 1, false);
		Bullet_Prefab->Get_Component<SpriteRenderer_Component>()->Lock_Check();
		Bullet_Prefab->Add_Component<cEnemy_BaseBullet>(L"cEnemy_BaseBullet_Script");
		Bullet_Prefab->Add_Component<TRS_Component>(L"Bullet_Prefabs_Trs")->Set_TRS(TRS_ENUM::SCALE, GVec3<float>(1, 1, 1), GVec3<float>(0.8f, 0.8f, 0.8f), -0.5f, TRS_LOOPTYPE::ROUNDTRIP, TRS_SPEEDTYPE::AVERAGE, 0, 0xFFFFFFFF);
	
		Rocket_Prefab = new GameObject(L"Rocket_Prefab");
		Rocket_Prefab->Prefab = true;
		Rocket_Prefab->Add_Component<SpriteRenderer_Component>(L"Rocket_Sc")->Load_Texture(L"Rocket.png", 4, 1, false);
		Rocket_Prefab->Get_Component<SpriteRenderer_Component>()->Lock_Check();
		Rocket_Prefab->Add_Component<cEnemy_Rocket>(L"cEnemy_Rocket_Prefab_Script");
		Rocket_Prefab->Add_Component<FrameAni_Component>(L"Rocket_Prefab_Fc");
		Rocket_Prefab->Get_Component<FrameAni_Component>()->Set_FrameTime(75, true);
		Rocket_Prefab->Add_Component<TRS_Component>(L"Rocket_Prefab_Trs")->Set_TRS(TRS_ENUM::SCALE, GVec3<float>(0.3, 0.3, 0.3), GVec3<float>(0.4f, 0.4f, 0.4f), -0.5f, TRS_LOOPTYPE::ROUNDTRIP, TRS_SPEEDTYPE::AVERAGE, 0, 0xFFFFFFFF);

		Boss12_Die_Eff_Prefab = new GameObject(L"Boss12_Die_Eff_Prefab");
		Boss12_Die_Eff_Prefab->Prefab = true;
		Boss12_Die_Eff_Prefab->Set_Center(true);
		Boss12_Die_Eff_Prefab->Render_Stack = 6;
		Boss12_Die_Eff_Prefab->Add_Component<cBoss12_Die_Eff>(L"Boss12_Die_Eff_Prefab_Script");
		Boss12_Die_Eff_Prefab->Add_Component<SpriteRenderer_Component>(L"Boss12_Die_Eff_Prefab_Sc");
		Boss12_Die_Eff_Prefab->Get_Component<SpriteRenderer_Component>()->Load_Texture(L"Eff/Boss_Die_Eff.png", 4, 6, false);
		Boss12_Die_Eff_Prefab->Get_Component<SpriteRenderer_Component>()->Lock_Check();
		Boss12_Die_Eff_Prefab->Add_Component<FrameAni_Component>(L"Enemy_Die_Eff_Ani")->Set_FrameTime(50, false);

		Gas_Prefab = new GameObject(L"Gas_Prefab");
		Gas_Prefab->Prefab = true;
		Gas_Prefab->Add_Component<SpriteRenderer_Component>(L"cEnemy_Gas_Sc")->Load_Texture(L"Eff/Gas_Eff.png", 6, 1, false);
		Gas_Prefab->Get_Component<SpriteRenderer_Component>()->Lock_Check();
		Gas_Prefab->Add_Component<cEnemy_Gas>(L"cEnemy_Gas_Prefab_Script");
		Gas_Prefab->Add_Component<FrameAni_Component>(L"Gas_Prefab_Fc");
		Gas_Prefab->Get_Component<FrameAni_Component>()->Set_FrameTime(75, false);
		Gas_Prefab->Add_Component<TRS_Component>(L"Gas_TRS")->Set_TRS(TRS_ENUM::SCALE, GVec3<float>(1, 1, 1), GVec3<float>(2, 2, 2), -0.5f, TRS_LOOPTYPE::ONEWAY, TRS_SPEEDTYPE::AVERAGE, 0, 0xFFFFFFFF);
		// 해당 신에 관련된 것을 로딩한다
		//Bg->Add_Component<MeMMap_Component>(L"Bg_AlpaMap")->Init_Setup<BYTE>(1920, 1080);
		//Bg->Add_Component<MeMMap_Component>(L"Bg_AttribMap")->Init_Setup<BYTE>(1920, 1080);
		
		Active_GSystem->Change_Music(L"./Res/Sound/SuperPower.mp3", true, 100, BGM_VOLUME_FADE::NOW);

		Shoot_Sound = Ingame_Manager->Add_Component<SoundCLIP_Component>(L"Shoot_Sound");
		Shoot_Sound->Load_Sound(L"./Res/Sound/Shoot22.WAV", 2);
		Shoot_Sound->Lock_Check();

		Warning_Sound = Ingame_Manager->Add_Component<SoundCLIP_Component>(L"Warning_Sound");
		Warning_Sound->Load_Sound(L"./Res/Sound/Warning.WAV", 1);
		Warning_Sound->Lock_Check();

		Explosion_Sound = Ingame_Manager->Add_Component<SoundCLIP_Component>(L"Explosion_Sound");
		Explosion_Sound->Load_Sound(L"./Res/Sound/Explosion.WAV", 10);
		Explosion_Sound->Lock_Check();

		PowerUp_Sound = Ingame_Manager->Add_Component<SoundCLIP_Component>(L"PowerUp_Sound");
		PowerUp_Sound->Load_Sound(L"./Res/Sound/PowerUp.WAV", 2);
		PowerUp_Sound->Lock_Check();

		Electricity_Sound = Ingame_Manager->Add_Component<SoundCLIP_Component>(L"Electricity_Sound");
		Electricity_Sound->Load_Sound(L"./Res/Sound/Electricity.WAV", 2);
		Electricity_Sound->Lock_Check();

		End_Sound = Ingame_Manager->Add_Component<SoundCLIP_Component>(L"End_Sound");
		End_Sound->Load_Sound(L"./Res/Sound/End.WAV", 2);
		End_Sound->Lock_Check();
		break;
	}
	case SCENE::STAGE3:
		Ingame_Base_Bg = new GameObject(L"BBg");
		Ingame_Bg = new GameObject(L"Ingame_Bg");
		MaskBg = new GameObject(L"MaskBg");
		Ingame = new GameObject(L"Ingame");
		Boss = new GameObject(L"Boss");
		Player = new GameObject(L"Player");
		Ingame_Ui = new GameObject(L"Ingame_Ui");
		Player_Life_MN = new GameObject(L"Player_Life_MN");
		Ingame_Manager = new GameObject(L"Ingame_Manager");
		Hp_Item = new GameObject(L"Hp_Item");
		SpeedUp_Item = new GameObject(L"SpeedUp_Item");
		Active_GScene->Camera_Sprite->Load_Texture(L"Warning/Warning_Bg.png", 1, 1, false);
		Active_GScene->Camera_Sprite->Active = false;

	/*	SpriteRenderer_Component* BBg_Sc = Ingame_Base_Bg->Add_Component<SpriteRenderer_Component>(L"BBg_Sc");
		BBg_Sc->Load_Texture(L"Stage1/BBg.png", 1, 1, false);
		Ingame_Base_Bg->Render_Stack = 0;*/

		Stage1_Enemy_Man_Prefab = new GameObject(L"Stage1_Enemy_Man");
		Stage1_Enemy_Man_Prefab->Prefab = true;
		Enemy_Sc = Stage1_Enemy_Man_Prefab->Add_Component<SpriteRenderer_Component>(L"Stage1_Enemy_Man_Sc");
		Stage1_Enemy_Man_Prefab->transform.Set_LocalScale(0.5, 0.5, 0.5);
		Enemy_Sc->Load_Texture(L"Stage3/Stage3_Cube.png", 12, 1, false);
		Enemy_Sc->Lock_Check();
		Stage1_Enemy_Man_Prefab->Add_Component<FrameAni_Component>(L"Stage1_Enemy_Man_Prefab_Ani")->Set_FrameTime(75, true);
		//Stage1_Enemy_Man_Prefab->Get_Component<FrameAni_Component>()->Set_FrameTime(75, true);
		Stage1_Enemy_Man_Prefab->Add_Component<cStage1_Enemy_Dog>(L"Stage1_Enemy_Man_Script")->IsStage3 = true;


		Stage1_Enemy_Dog_Prefab = new GameObject(L"Stage1_Enemy_Dog");
		Stage1_Enemy_Dog_Prefab->Prefab = true;
		Stage1_Enemy_Dog_Prefab->transform.Set_LocalScale(1.5, 1.5, 1.5);
		Enemy_Sc = Stage1_Enemy_Dog_Prefab->Add_Component<SpriteRenderer_Component>(L"Stage1_Enemy_Dog");
		Enemy_Sc->Load_Texture(L"Stage3/Stage3_Mine.png", 12, 1, false);
		Enemy_Sc->Lock_Check();
		
		Stage1_Enemy_Dog_Prefab->Add_Component<FrameAni_Component>(L"Stage1_Enemy_Man_Prefab_Ani")->Set_FrameTime(75, true);
		Stage1_Enemy_Dog_Prefab->Add_Component<cStage1_Enemy_Dog>(L"Stage1_Enemy_Dog")->IsStage3 = true;


		Ingame_Bg->Add_Component<cBg>(L"Bg_Script");
		MaskBg->Add_Component<cMaskBg>(L"Mask_Script");
		Ingame->Add_Component<cIngame>(L"Ingame_Script");
		Boss->Add_Component<cStage3_Boss>(L"Boss_Script");
		/*	for (int i = 0; i < 3; i++)
				Enemy[i]->Add_Component<cEnemy>(L"Enemy_Script");*/
		Ingame_Ui->Add_Component<cIngame_Ui>(L"Ingame_Ui_Script");
		Player->Add_Component<cPlayer>(L"Player_Script");
		Player_Life_MN->Add_Component<cPlayer_Life>(L"Player_Life_Script");
		Ingame_Manager->Add_Component<cIngameManager>(L"cIngame_Manager_Script");
		Hp_Item->Add_Component<cHp_Item>(L"cHp_Item_Script");
		SpeedUp_Item->Add_Component<cSpeedUp_Item>(L"cSpeedUp_Item_Script");
		for (int i = 0; i < 3; i++)
		{
			Stage1_Enemy_Man[i] = Active_GSystem->Instantiate(Stage1_Enemy_Man_Prefab);
			Stage1_Enemy_Man[i]->Render_Stack = 3; //적
			Stage1_Enemy_Man[i]->Prefab = false;
			Stage1_Enemy_Dog[i] = Active_GSystem->Instantiate(Stage1_Enemy_Dog_Prefab);
			Stage1_Enemy_Dog[i]->Render_Stack = 3; //적
			Stage1_Enemy_Dog[i]->Prefab = false;
		}

		Bullet_Prefab = new GameObject(L"Bullet");
		Bullet_Prefab->Prefab = true;
		Bullet_Prefab->Add_Component<SpriteRenderer_Component>(L"Bullet_Sc")->Load_Texture(L"Enemy_Bullet_Blue.png", 1, 1, false);
		Bullet_Prefab->Get_Component<SpriteRenderer_Component>()->Lock_Check();
		Bullet_Prefab->Add_Component<cEnemy_BaseBullet>(L"cEnemy_BaseBullet_Script");
		Bullet_Prefab->Add_Component<TRS_Component>(L"Bullet_Prefabs_Trs")->Set_TRS(TRS_ENUM::SCALE, GVec3<float>(1, 1, 1), GVec3<float>(0.8f, 0.8f, 0.8f), -0.5f, TRS_LOOPTYPE::ROUNDTRIP, TRS_SPEEDTYPE::AVERAGE, 0, 0xFFFFFFFF);

		Boss3_Die_Eff_Prefab = new GameObject(L"Boss3_Die_Eff_Prefab");
		Boss3_Die_Eff_Prefab->Prefab = true;
		Boss3_Die_Eff_Prefab->Set_Center(true);
		Boss3_Die_Eff_Prefab->Render_Stack = 6;
		Boss3_Die_Eff_Prefab->Add_Component<cBoss3_Die_Eff>(L"Boss3_Die_Eff_Prefab_Script");
		Boss3_Die_Eff_Prefab->Add_Component<SpriteRenderer_Component>(L"Boss3_Die_Eff_Prefab_Sc");
		Boss3_Die_Eff_Prefab->Get_Component<SpriteRenderer_Component>()->Load_Texture(L"Eff/Boss3_Die_Eff.png", 3, 4, false);
		Boss3_Die_Eff_Prefab->Get_Component<SpriteRenderer_Component>()->Lock_Check();
		Boss3_Die_Eff_Prefab->Add_Component<FrameAni_Component>(L"Boss3_Die_Eff_Prefab_Ani")->Set_FrameTime(50, false);

		Active_GSystem->Change_Music(L"./Res/Sound/SuperPower.mp3", true, 100, BGM_VOLUME_FADE::NOW);

		Shoot_Sound = Ingame_Manager->Add_Component<SoundCLIP_Component>(L"Shoot_Sound");
		Shoot_Sound->Load_Sound(L"./Res/Sound/Shoot22.WAV", 2);
		Shoot_Sound->Lock_Check();

		Warning_Sound = Ingame_Manager->Add_Component<SoundCLIP_Component>(L"Warning_Sound");
		Warning_Sound->Load_Sound(L"./Res/Sound/Warning.WAV", 1);
		Warning_Sound->Lock_Check();

		Explosion_Sound = Ingame_Manager->Add_Component<SoundCLIP_Component>(L"Explosion_Sound");
		Explosion_Sound->Load_Sound(L"./Res/Sound/Explosion.WAV", 50);
		Explosion_Sound->Lock_Check();

		PowerUp_Sound = Ingame_Manager->Add_Component<SoundCLIP_Component>(L"PowerUp_Sound");
		PowerUp_Sound->Load_Sound(L"./Res/Sound/PowerUp.WAV", 2);
		PowerUp_Sound->Lock_Check();

		Electricity_Sound = Ingame_Manager->Add_Component<SoundCLIP_Component>(L"Electricity_Sound");
		Electricity_Sound->Load_Sound(L"./Res/Sound/Electricity.WAV", 2);
		Electricity_Sound->Lock_Check();

		End_Sound = Ingame_Manager->Add_Component<SoundCLIP_Component>(L"End_Sound");
		End_Sound->Load_Sound(L"./Res/Sound/End.WAV", 2);
		End_Sound->Lock_Check();
		break;
	case SCENE::HOWTOPLAY:
		{
			break;
		}
		// 해당 신에 관련된 것을 로딩한다
	case SCENE::RANKING:
		{
			break;
		}
	case SCENE::CREADIT:
		{
			break;
		}

	}
}
