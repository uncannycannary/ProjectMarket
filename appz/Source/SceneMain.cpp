/****************************************************************************/
/*!
\file SceneMain.cpp
\author Tan Jie Rong
\par email: soupsf@hotmail.com
\brief
Scene that updates and init, main scene to be rendered
*/
/****************************************************************************/
#include "SceneMain.h"
#include "GL\glew.h"

#include "shader.hpp"
#include "MeshBuilder.h"
#include "LoadTGA.h"
#include "PlayerHuman.h"
#include "PlayerFrog.h"
#include "Polygon.h"
#include "CollisionBody.h"
/****************************************************************************/
/*!
\brief
constructor to get mouse keyboard sound and graphics obj
\param Keyboard& keyboard 
object from keyboard class
\param GLMouse& mouse
object from GLmosuse class
\param Sound& snd
object from Sound class
\param Graphics& gfx
object from Graphics class
*/
/****************************************************************************/
SceneMain::SceneMain(Keyboard& keyboard, GLMouse& mouse, Sound& snd, Graphics& gfx)
	:
Scene(keyboard, mouse, snd, gfx)
{
}
/****************************************************************************/
/*!
\brief
default destructor
*/
/****************************************************************************/
SceneMain::~SceneMain(void)
{
}
/****************************************************************************/
/*!
\brief
Initialize all variables used and also to pass in drawOrders for other classes
*/
/****************************************************************************/
void SceneMain::Init()
{
	InnitLight();
	InnitTextures();
	AbientLight = 0.6;
	InnitMaterials();
	InnitSounds();
	InnitGeometry();
	InnitDraws();
	InnitCollisions();
	InnitForces();
	InnitLogic();
	player = new PlayerHuman;
	player->noOfItemInTrolley = 0;
	player->tempNoItemNeedToPay = 0;
	player->DrawIsEqualTo(globals.GetDraw(L"player_arm_left"), globals.GetDraw(L"player_arm_right"), globals.GetDraw(L"player_body"), globals.GetDraw(L"main"), globals.GetDraw(L"trolley5"));
	isJumping = false;
	isFalling = false;
	jumpedHeight = 0;
	isFrog = false;
	UpdateLv2 = false;
	UpdateLv1=true;
	paying=false;
	OpenLiftDoorInput = false;
	exit = false;
	snd.playSound("halot",true);
	state=MAINMENU;
	InteractDoor.DrawIsEqualTo(globals.GetDraw(L"outer_door_1_left"),globals.GetDraw(L"outer_door_1_right"),globals.GetDraw(L"outer_door_2_left"),globals.GetDraw(L"outer_door_2_right"), globals.GetDraw(L"inner_door_1"), globals.GetDraw(L"inner_door_2"), globals.GetDraw(L"liftdoor_1_left"),  globals.GetDraw(L"liftdoor_1_right"), globals.GetDraw(L"liftdoor_2_left"),  globals.GetDraw(L"liftdoor_2_right"));
	lostchild.DrawIsEqualTo(globals.GetDraw(L"main"), globals.GetDraw(L"player_body"), globals.GetDraw(L"lost_child_body"), globals.GetDraw(L"lost_child_arm_left"), globals.GetDraw(L"lost_child_arm_right"), globals.GetDraw(L"lost_child_leg_left"), globals.GetDraw(L"lost_child_leg_right"));
	father.DrawIsEqualTo(globals.GetDraw(L"father_body"), globals.GetDraw(L"father_arm_left"), globals.GetDraw(L"father_arm_right"), globals.GetDraw(L"father_leg_left"), globals.GetDraw(L"father_leg_right"));
	wizard.DrawIsEqualTo(globals.GetDraw(L"wizard_body"), globals.GetDraw(L"wizard_arm_left"), globals.GetDraw(L"wizard_arm_right"), globals.GetDraw(L"wizard_leg_left"), globals.GetDraw(L"wizard_leg_right"));
	SWLv2[0].DrawIsEqualTo(globals.GetDraw(L"shopper_wanderer_body0"), globals.GetDraw(L"shopper_wanderer_arm_left0"), globals.GetDraw(L"shopper_wanderer_arm_right0"), globals.GetDraw(L"shopper_wanderer_leg_left0"), globals.GetDraw(L"shopper_wanderer_leg_right0"));
	SWLv2[0].SetPosition(9);
	SWLv2[1].DrawIsEqualTo(globals.GetDraw(L"shopper_wanderer_body1"), globals.GetDraw(L"shopper_wanderer_arm_left1"), globals.GetDraw(L"shopper_wanderer_arm_right1"), globals.GetDraw(L"shopper_wanderer_leg_left1"), globals.GetDraw(L"shopper_wanderer_leg_right1"));
	SWLv2[1].SetPosition(0);
	SPLv1.DrawIsEqualTo(globals.GetDraw(L"shopper_payer_body"), globals.GetDraw(L"shopper_payer_leg_left"), globals.GetDraw(L"shopper_payer_leg_right"), globals.GetDraw(L"shopper_payer_items"), globals.GetDraw(L"lv1cabinet3_column1_0"), globals.GetDraw(L"cashiertable1"));
	SPLv1.SetPosition(0);
	SILv1.DrawIsEqualTo(globals.GetDraw(L"shopper_idler_body"), globals.GetDraw(L"shopper_idler_arm_left"), globals.GetDraw(L"shopper_idler_arm_right"), globals.GetDraw(L"shopper_idler_leg_left"), globals.GetDraw(L"shopper_idler_leg_right"));
	SILv1.SetPosition(0);
	RLv1[0].DrawIsEqualTo(globals.GetDraw(L"robotbody0"), globals.GetDraw(L"robotarm_left0"), globals.GetDraw(L"robotarm_right0"));
	RLv1[1].DrawIsEqualTo(globals.GetDraw(L"robotbody1"), globals.GetDraw(L"robotarm_left1"), globals.GetDraw(L"robotarm_right1"));
	item.DrawIsEqualTo(globals.GetDraw(L"trolley5"), globals.GetDraw(L"player_body"));
	lostchild.PlayerIsEqualTo(player);
	item.PlayerIsEqualTo(player);
	item.TrolleyIsEqualTo(trolley);
	for(int i = 0; i < 1246; ++i)
	{
		if(i < 360)// CAN_1 360
		{
			wchar_t Namebuffer[64];
			wsprintf(Namebuffer,L"can1_cabinet1_%d",i);
			item.AddItem(globals.GetDraw(Namebuffer));
		}
		else if(i < 420)// CAN_2 60
		{
			wchar_t Namebuffer[64];
			wsprintf(Namebuffer,L"can2_cabinet1_%d",i-360);
			item.AddItem(globals.GetDraw(Namebuffer));
		}
		else if(i < 670)// CAN_3 250
		{
			wchar_t Namebuffer[64];
			wsprintf(Namebuffer,L"can3_cabinet1_%d",i-420);
			item.AddItem(globals.GetDraw(Namebuffer));
		}
		else if(i < 706)// Packet1 36
		{
			wchar_t Namebuffer[64];
			wsprintf(Namebuffer,L"packet1_cabinet2_column1_%d",i-670);
			item.AddItem(globals.GetDraw(Namebuffer));
		}
		else if(i < 742)// Packet2 36
		{
			wchar_t Namebuffer[64];
			wsprintf(Namebuffer,L"packet2_cabinet2_column2_%d",i-706);
			item.AddItem(globals.GetDraw(Namebuffer));
		}
		else if(i < 934)// Packet3 192
		{
			wchar_t Namebuffer[64];
			wsprintf(Namebuffer,L"packet3_cabinet2_column1_%d",i-742);
			item.AddItem(globals.GetDraw(Namebuffer));
		}
		else if(i < 1114)// Can_4 180
		{
			wchar_t Namebuffer[64];
			wsprintf(Namebuffer,L"can4_cabinet2_column2_%d",i-934);
			item.AddItem(globals.GetDraw(Namebuffer));
		}
		else if(i < 1150)// Cereal1 36
		{
			wchar_t Namebuffer[64];
			wsprintf(Namebuffer,L"cereal1_cabinet3_%d",i-1114);
			item.AddItem(globals.GetDraw(Namebuffer));
		}
		else if(i < 1174)// Cereal2 24
		{
			wchar_t Namebuffer[64];
			wsprintf(Namebuffer,L"cereal2_cabinet3_%d",i-1150);
			item.AddItem(globals.GetDraw(Namebuffer));
		}
		else if(i < 1210)// Cereal3 36
		{
			wchar_t Namebuffer[64];
			wsprintf(Namebuffer,L"cereal3_cabinet3_%d",i-1174);
			item.AddItem(globals.GetDraw(Namebuffer));
		}
		else if(i < 1246)// Cereal4 36
		{
			wchar_t Namebuffer[64];
			wsprintf(Namebuffer,L"cereal4_cabinet3_%d",i-1210);
			item.AddItem(globals.GetDraw(Namebuffer));
		}
	}
	camera.Init(Vector3(0, 7, 5), Vector3(1, 0, 0), Vector3(0, 1, 0));
	gfx.SetProjectionTo(45.f, 4.f / 3.f, 0.1f, 90000.f);
	gfx.InitText(L"Image//ArialBlack.tga");
}
/****************************************************************************/
/*!
\brief
Initializes Sound
*/
/****************************************************************************/
void SceneMain::InnitSounds()
{
	snd.loadWave("pure", "sound//pure.wav");
	snd.loadWave("elevator","sound//elevator.wav");
	snd.loadWave("robot","sound//robot.wav");
	snd.loadWave("halot","sound//halot.wav");
	snd.loadWave("meet didact","sound//meet_didact.wav");
	snd.loadWave("didact freed","sound//didact_freed.wav");
	snd.loadWave("robot2","sound//robot2.wav");
}
/****************************************************************************/
/*!
\brief
Initializes logic like FPS and dt
*/
/****************************************************************************/
void SceneMain::InnitLogic()
{
	frameCounter = 0;
	accumulatingDT = 0;
	currentFPS = 60;
	drawVoxels = false;
}
/****************************************************************************/
/*!
\brief
Initializes texture
*/
/****************************************************************************/
void SceneMain::InnitTextures()
{
	globals.AddTexture(L"skybox", L"Image//skybox.tga");
	globals.AddTexture(L"ground", L"Image//ground.tga");
	globals.AddTexture(L"building", L"Image//large_forerunner_floor_plate.tga");
	globals.AddTexture(L"didact", L"Image//didact.tga");
	globals.AddTexture(L"ring", L"Image//ring.tga");
	globals.AddTexture(L"cashiertable texture", L"Image//cashiertable_texture.tga");
	globals.AddTexture(L"CabinetTexture", L"Image//CabinetTexture.tga");
	globals.AddTexture(L"can1", L"Image//can1.tga");
	globals.AddTexture(L"can2", L"Image//can2.tga");
	globals.AddTexture(L"can3", L"Image//can3.tga");
	globals.AddTexture(L"can4", L"Image//can4.tga");
	globals.AddTexture(L"cereal1", L"Image//cereal1.tga");
	globals.AddTexture(L"cereal2", L"Image//cereal2.tga");
	globals.AddTexture(L"cereal3", L"Image//cereal3.tga");
	globals.AddTexture(L"cereal4", L"Image//cereal4.tga");
	globals.AddTexture(L"packet1", L"Image//packet1.tga");
	globals.AddTexture(L"packet2", L"Image//packet2.tga");
	globals.AddTexture(L"packet3", L"Image//packet3.tga");
	globals.AddTexture(L"dullwhite", L"Image//dullwhite.tga");
	globals.AddTexture(L"lift", L"Image//blue.tga");
	globals.AddTexture(L"liftdoor", L"Image//liftdoor.tga");
	globals.AddTexture(L"door texture", L"Image//door_texture.tga");
	globals.AddTexture(L"travelatorslope texture2", L"Image//travelatorslope_texture2.tga");
	globals.AddTexture(L"travelatorhandle texture", L"Image//travelatorhandle_texture.tga");
	globals.AddTexture(L"trolleytexture", L"Image//TrolleyTexture.tga");
	globals.AddTexture(L"character1", L"Image//character1.tga");
	globals.AddTexture(L"character2", L"Image//character2.tga");
	globals.AddTexture(L"character3", L"Image//character3.tga");
	globals.AddTexture(L"character4", L"Image//character4.tga");
	globals.AddTexture(L"robot", L"Image//robot_texture.tga");
	globals.AddTexture(L"Quad1",L"Image//Quad1.tga");
	globals.AddTexture(L"Quad2",L"Image//Quad2.tga");
	globals.AddTexture(L"Quad3",L"Image//Quad3.tga");
	globals.AddTexture(L"Quad4",L"Image//Quad4.tga");
	globals.AddTexture(L"BG",L"Image//BG.tga");
	globals.AddTexture(L"target",L"Image//white.tga");
	globals.AddTexture(L"incredits",L"Image//incredits.tga");
	globals.AddTexture(L"inexit",L"Image//inexit.tga");
	globals.AddTexture(L"instructions",L"Image//instructions.tga");
	globals.AddTexture(L"liftlevel1",L"Image//liftlevel1.tga");
	globals.AddTexture(L"liftlevel2",L"Image//liftlevel2.tga");
	globals.AddTexture(L"lollipop",L"Image//lollipop_texture.tga");
}
/****************************************************************************/
/*!
\brief
Initializes material, combining texture and lighting.
*/
/****************************************************************************/
void SceneMain::InnitMaterials()
{
	globals.AddMaterial(Material(L"skybox",Component(AbientLight,AbientLight,AbientLight),Component(1,1,1),Component(1,1,1),20,globals.GetTexture(L"skybox")));
	globals.AddMaterial(Material(L"ground",Component(AbientLight,AbientLight,AbientLight),Component(1,1,1),Component(1,1,1),20,globals.GetTexture(L"ground")));
	globals.AddMaterial(Material(L"building",Component(AbientLight,AbientLight,AbientLight),Component(1,1,1),Component(1,1,1),20,globals.GetTexture(L"building")));
	globals.AddMaterial(Material(L"didact",Component(AbientLight,AbientLight,AbientLight),Component(1,1,1),Component(1,1,1),2000,globals.GetTexture(L"didact")));
	globals.AddMaterial(Material(L"ring",Component(AbientLight,AbientLight,AbientLight),Component(1,1,1),Component(1,1,1),2000,globals.GetTexture(L"ring")));
	globals.AddMaterial(Material(L"cashiertable",Component(AbientLight,AbientLight,AbientLight),Component(1,1,1),Component(1,1,1),20,globals.GetTexture(L"cashiertable texture")));
	globals.AddMaterial(Material(L"cabinet",Component(AbientLight,AbientLight,AbientLight),Component(1.2,1.2,1.2),Component(0.8,0.8,0.8),20,globals.GetTexture(L"CabinetTexture")));
	globals.AddMaterial(Material(L"can1",Component(AbientLight,AbientLight,AbientLight),Component(0.7,0.7,0.7),Component(0.5,0.5,0.5),10,globals.GetTexture(L"can1")));
	globals.AddMaterial(Material(L"can2",Component(AbientLight,AbientLight,AbientLight),Component(0.7,0.7,0.7),Component(0.5,0.5,0.5),10,globals.GetTexture(L"can2")));
	globals.AddMaterial(Material(L"can3",Component(AbientLight,AbientLight,AbientLight),Component(0.7,0.7,0.7),Component(0.5,0.5,0.5),10,globals.GetTexture(L"can3")));
	globals.AddMaterial(Material(L"can4",Component(AbientLight,AbientLight,AbientLight),Component(0.7,0.7,0.7),Component(0.5,0.5,0.5),10,globals.GetTexture(L"can4")));
	globals.AddMaterial(Material(L"cereal1",Component(AbientLight,AbientLight,AbientLight),Component(0.7,0.7,0.7),Component(0.5,0.5,0.5),10,globals.GetTexture(L"cereal1")));
	globals.AddMaterial(Material(L"cereal2",Component(AbientLight,AbientLight,AbientLight),Component(0.7,0.7,0.7),Component(0.5,0.5,0.5),10,globals.GetTexture(L"cereal2")));
	globals.AddMaterial(Material(L"cereal3",Component(AbientLight,AbientLight,AbientLight),Component(0.7,0.7,0.7),Component(0.5,0.5,0.5),10,globals.GetTexture(L"cereal3")));
	globals.AddMaterial(Material(L"cereal4",Component(AbientLight,AbientLight,AbientLight),Component(0.7,0.7,0.7),Component(0.5,0.5,0.5),10,globals.GetTexture(L"cereal4")));
	globals.AddMaterial(Material(L"packet1",Component(AbientLight,AbientLight,AbientLight),Component(0.7,0.7,0.7),Component(0.5,0.5,0.5),10,globals.GetTexture(L"packet1")));
	globals.AddMaterial(Material(L"packet2",Component(AbientLight,AbientLight,AbientLight),Component(0.7,0.7,0.7),Component(0.5,0.5,0.5),10,globals.GetTexture(L"packet2")));
	globals.AddMaterial(Material(L"packet3",Component(AbientLight,AbientLight,AbientLight),Component(0.7,0.7,0.7),Component(0.5,0.5,0.5),10,globals.GetTexture(L"packet3")));
	globals.AddMaterial(Material(L"dullwhite",Component(AbientLight,AbientLight,AbientLight),Component(1,1,1),Component(1,1,1),20,globals.GetTexture(L"dullwhite")));
	globals.AddMaterial(Material(L"lift",Component(AbientLight,AbientLight,AbientLight),Component(1,1,1),Component(1,1,1),20,globals.GetTexture(L"lift")));
	globals.AddMaterial(Material(L"liftdoor",Component(AbientLight,AbientLight,AbientLight),Component(1,1,1),Component(1,1,1),20,globals.GetTexture(L"liftdoor")));
	globals.AddMaterial(Material(L"door texture",Component(AbientLight,AbientLight,AbientLight),Component(1,1,1),Component(1,1,1),20,globals.GetTexture(L"door texture")));
	globals.AddMaterial(Material(L"travelatorhandle",Component(AbientLight,AbientLight,AbientLight),Component(1,1,1),Component(1,1,1),20,globals.GetTexture(L"travelatorhandle texture")));
	globals.AddMaterial(Material(L"travelatorslope",Component(AbientLight,AbientLight,AbientLight),Component(1,1,1),Component(1,1,1),20,globals.GetTexture(L"travelatorslope texture2")));
	globals.AddMaterial(Material(L"trolley",Component(AbientLight,AbientLight,AbientLight),Component(0.8,0.8,0.8),Component(0.6,0.6,0.6),10,globals.GetTexture(L"trolleytexture")));
	globals.AddMaterial(Material(L"character1",Component(AbientLight,AbientLight,AbientLight),Component(1,1,1),Component(1,1,1),20,globals.GetTexture(L"character1")));
	globals.AddMaterial(Material(L"character2",Component(AbientLight,AbientLight,AbientLight),Component(1,1,1),Component(1,1,1),20,globals.GetTexture(L"character2")));
	globals.AddMaterial(Material(L"character3",Component(AbientLight,AbientLight,AbientLight),Component(1,1,1),Component(1,1,1),20,globals.GetTexture(L"character3")));
	globals.AddMaterial(Material(L"character4",Component(AbientLight,AbientLight,AbientLight),Component(1,1,1),Component(1,1,1),20,globals.GetTexture(L"character4")));
	globals.AddMaterial(Material(L"robot",Component(AbientLight,AbientLight,AbientLight),Component(1,1,1),Component(1,1,1),20,globals.GetTexture(L"robot")));
	globals.AddMaterial(Material(L"Quad1",Component(AbientLight,AbientLight,AbientLight),Component(1,1,1),Component(1,1,1),20,globals.GetTexture(L"Quad1")));
	globals.AddMaterial(Material(L"Quad2",Component(AbientLight,AbientLight,AbientLight),Component(1,1,1),Component(1,1,1),20,globals.GetTexture(L"Quad2")));
	globals.AddMaterial(Material(L"Quad3",Component(AbientLight,AbientLight,AbientLight),Component(1,1,1),Component(1,1,1),20,globals.GetTexture(L"Quad3")));
	globals.AddMaterial(Material(L"Quad4",Component(AbientLight,AbientLight,AbientLight),Component(1,1,1),Component(1,1,1),20,globals.GetTexture(L"Quad4")));
	globals.AddMaterial(Material(L"target",Component(AbientLight,AbientLight,AbientLight),Component(1,1,1),Component(1,1,1),20,globals.GetTexture(L"target")));
	globals.AddMaterial(Material(L"BG",Component(AbientLight,AbientLight,AbientLight),Component(1,1,1),Component(1,1,1),20,globals.GetTexture(L"BG")));
	globals.AddMaterial(Material(L"incredits",Component(AbientLight,AbientLight,AbientLight),Component(1,1,1),Component(1,1,1),20,globals.GetTexture(L"incredits")));
	globals.AddMaterial(Material(L"inexit",Component(AbientLight,AbientLight,AbientLight),Component(1,1,1),Component(1,1,1),20,globals.GetTexture(L"inexit")));
	globals.AddMaterial(Material(L"instructions",Component(AbientLight,AbientLight,AbientLight),Component(1,1,1),Component(1,1,1),20,globals.GetTexture(L"instructions")));
	globals.AddMaterial(Material(L"liftlevel1",Component(AbientLight,AbientLight,AbientLight),Component(1,1,1),Component(1,1,1),20,globals.GetTexture(L"liftlevel1")));
	globals.AddMaterial(Material(L"liftlevel2",Component(AbientLight,AbientLight,AbientLight),Component(1,1,1),Component(1,1,1),20,globals.GetTexture(L"liftlevel2")));
	globals.AddMaterial(Material(L"lollipop",Component(AbientLight,AbientLight,AbientLight),Component(1,1,1),Component(1,1,1),20,globals.GetTexture(L"lollipop")));
}
/****************************************************************************/
/*!
\brief
Initializes light used
*/
/****************************************************************************/
void SceneMain::InnitLight()
{
	light[1].type = Light::LIGHT_DIRECTIONAL;
	light[1].position.Set(20, 20, 20);
	light[1].color.Set(1, 1, 1);
	light[1].power = 0.25;
	light[1].kC = 1.f;
	light[1].kL = 0.01f;
	light[1].kQ = 0.001f;
	light[1].cosCutoff = cos(Math::DegreeToRadian(180));
	light[1].cosInner = cos(Math::DegreeToRadian(30));
	light[1].exponent = 1.f;
	light[1].spotDirection.Set(0.f, 1.f, 1.f);

	gfx.AddLight(&light[1]);
}
/****************************************************************************/
/*!
\brief
Initializes geometry and obj
*/
/****************************************************************************/
void SceneMain::InnitGeometry()
{
	globals.AddMesh(MeshBuilder::GenerateOBJ(L"skybox", L"OBJ//skybox.obj"));
	globals.AddMesh(MeshBuilder::GenerateOBJ(L"sphere", L"OBJ//sphere.obj"));
	globals.AddMesh(MeshBuilder::GenerateOBJ(L"didact", L"OBJ//didact.obj"));
	globals.AddMesh(MeshBuilder::GenerateOBJ(L"ring", L"OBJ//ring.obj"));
	globals.AddMesh(MeshBuilder::GenerateRepeatQuad(L"ground", Color(1, 1, 1), 500.f, 500.f));
	globals.AddMesh(MeshBuilder::GenerateQuad(L"Quad1", Color(1, 1, 1), 10.f, 10.f));
	globals.AddMesh(MeshBuilder::GenerateQuad(L"BG", Color(1, 1, 1), 10.f, 10.f));
	globals.AddMesh(MeshBuilder::GenerateQuad(L"incredits", Color(1, 1, 1), 500.f, 500.f));
	globals.AddMesh(MeshBuilder::GenerateQuad(L"inexit", Color(1, 1, 1), 500.f, 500.f));
	globals.AddMesh(MeshBuilder::GenerateQuad(L"instructions", Color(1, 1, 1), 500.f, 500.f));
	globals.AddMesh(MeshBuilder::GenerateQuad(L"liftlevel1",Color(1,1,1),3.f,0.5f));
	globals.AddMesh(MeshBuilder::GenerateQuad(L"liftlevel2", Color(1, 1, 1), 3.f, 0.5f));
	globals.AddMesh(MeshBuilder::GenerateOBJ(L"cube", L"OBJ//cubey.obj"));
	globals.AddMesh(MeshBuilder::GenerateOBJ(L"cashiertable", L"OBJ//cashiertable.obj"));
	globals.AddMesh(MeshBuilder::GenerateOBJ(L"cabinet1", L"OBJ//Cabinet1.obj"));
	globals.AddMesh(MeshBuilder::GenerateOBJ(L"cabinet2", L"OBJ//Cabinet2.obj"));
	globals.AddMesh(MeshBuilder::GenerateOBJ(L"cabinet3", L"OBJ//Cabinet3.obj"));
	globals.AddMesh(MeshBuilder::GenerateOBJ(L"cabinet4", L"OBJ//Cabinet4.obj"));
	globals.AddMesh(MeshBuilder::GenerateOBJ(L"can1", L"OBJ//can1.obj"));
	globals.AddMesh(MeshBuilder::GenerateOBJ(L"can2", L"OBJ//can2.obj"));
	globals.AddMesh(MeshBuilder::GenerateOBJ(L"can3", L"OBJ//can3.obj"));
	globals.AddMesh(MeshBuilder::GenerateOBJ(L"can4", L"OBJ//can4.obj"));
	globals.AddMesh(MeshBuilder::GenerateOBJ(L"cereallump", L"OBJ//cerealLump.obj"));
	globals.AddMesh(MeshBuilder::GenerateOBJ(L"cereal1", L"OBJ//cereal1.obj"));
	globals.AddMesh(MeshBuilder::GenerateOBJ(L"cereal2", L"OBJ//cereal2.obj"));
	globals.AddMesh(MeshBuilder::GenerateOBJ(L"cereal3", L"OBJ//cereal3.obj"));
	globals.AddMesh(MeshBuilder::GenerateOBJ(L"cereal4", L"OBJ//cereal4.obj"));
	globals.AddMesh(MeshBuilder::GenerateOBJ(L"packet1", L"OBJ//packet1.obj"));
	globals.AddMesh(MeshBuilder::GenerateOBJ(L"packet2", L"OBJ//packet2.obj"));
	globals.AddMesh(MeshBuilder::GenerateOBJ(L"packet3", L"OBJ//packet3.obj"));
	globals.AddMesh(MeshBuilder::GenerateOBJ(L"building", L"OBJ//building.obj"));
	globals.AddMesh(MeshBuilder::GenerateOBJ(L"lift", L"OBJ//bluelift.obj"));
	globals.AddMesh(MeshBuilder::GenerateOBJ(L"liftdoor", L"OBJ//liftdoor.obj"));
	globals.AddMesh(MeshBuilder::GenerateOBJ(L"outerdoor", L"OBJ//outerdoor.obj"));
	globals.AddMesh(MeshBuilder::GenerateOBJ(L"innerdoor", L"OBJ//innerdoor.obj"));
	globals.AddMesh(MeshBuilder::GenerateOBJ(L"travelatorsupport", L"OBJ//travelatorsupport.obj"));
	globals.AddMesh(MeshBuilder::GenerateOBJ(L"travelatorslope", L"OBJ//travelatorslope.obj"));
	globals.AddMesh(MeshBuilder::GenerateOBJ(L"travelatorhandle", L"OBJ//travelatorhandle.obj"));
	globals.AddMesh(MeshBuilder::GenerateOBJ(L"trolley", L"OBJ//trolley.obj"));
	globals.AddMesh(MeshBuilder::GenerateOBJ(L"characterarm", L"OBJ//characterarm.obj"));
	globals.AddMesh(MeshBuilder::GenerateOBJ(L"characterleg", L"OBJ//characterleg.obj"));
	globals.AddMesh(MeshBuilder::GenerateOBJ(L"characterbody", L"OBJ//characterbody.obj"));
	globals.AddMesh(MeshBuilder::GenerateOBJ(L"wizardbody", L"OBJ//characterwizardbody.obj"));
	globals.AddMesh(MeshBuilder::GenerateOBJ(L"robotbody", L"OBJ//robotbody.obj"));
	globals.AddMesh(MeshBuilder::GenerateOBJ(L"robotarm", L"OBJ//robotarm.obj"));
	globals.AddMesh(MeshBuilder::GenerateOBJ(L"lollipop", L"OBJ//lollipop.obj"));
}
/****************************************************************************/
/*!
\brief
function to draw/load out every obj or images that will appear in scene
*/
/****************************************************************************/
void SceneMain::InnitDraws()
{
	//main will be the main draw order that all other draw orders are children of
	globals.AddDraw(drawOrder(L"main"));
	//Draw main menu
	//Draw SkyBox
	globals.AddDraw(drawOrder(L"skybox",globals.GetMesh(L"skybox"), &globals.GetMaterial(L"skybox"), &globals.GetDraw(L"main")));
	globals.GetDraw(L"skybox").transform.translate.Set(0,0,0);
	globals.GetDraw(L"skybox").transform.scale.Set(10000,10000,10000);

	//Draw Ground
	globals.AddDraw(drawOrder(L"ground",globals.GetMesh(L"ground"), &globals.GetMaterial(L"ground"), &globals.GetDraw(L"main"), true));
	globals.GetDraw(L"ground").transform.translate.Set(0,1.09,-40);

	//Draw Building
	globals.AddDraw(drawOrder(L"building",globals.GetMesh(L"building"), &globals.GetMaterial(L"building"), &globals.GetDraw(L"main"), false));
	globals.GetDraw(L"building").transform.translate.Set(0,0.1,-30);

	//Draw player target
	globals.AddDraw(drawOrder(L"target",globals.GetMesh(L"sphere"), &globals.GetMaterial(L"target"), &globals.GetDraw(L"main"), false));
	globals.GetDraw(L"target").transform.scale.Set(0.033,0.033,0.033);

	//Draw Didact
	globals.AddDraw(drawOrder(L"didact", globals.GetMesh(L"didact"), &globals.GetMaterial(L"didact"), &globals.GetDraw(L"main"), true));
	globals.GetDraw(L"didact").transform.translate.Set(17,15,-12);
	meetDidact.Set(17,15,-12);
	globals.GetDraw(L"didact").transform.scale.Set(10,10,10);

	//Draw Ring
	globals.AddDraw(drawOrder(L"ring", globals.GetMesh(L"ring"), &globals.GetMaterial(L"ring"), &globals.GetDraw(L"main"), true));
	globals.GetDraw(L"ring").transform.translate.Set(17,15,-12);
	globals.GetDraw(L"ring").transform.scale.Set(10,10,10);

	//Draw Player
	globals.AddDraw(drawOrder(L"player_body",globals.GetMesh(L"characterbody"), &globals.GetMaterial(L"character1"), &globals.GetDraw(L"main"), true));
	globals.AddDraw(drawOrder(L"player_arm_left",globals.GetMesh(L"characterarm"), &globals.GetMaterial(L"character1"), &globals.GetDraw(L"player_body"), true));
	globals.GetDraw(L"player_arm_left").transform.translate.Set(0,0.6,1.5);
	globals.GetDraw(L"player_arm_left").selfTransform.rotate.z = 115;
	globals.GetDraw(L"player_arm_left").selfTransform.rotate.y = 10;
	globals.AddDraw(drawOrder(L"player_arm_right",globals.GetMesh(L"characterarm"), &globals.GetMaterial(L"character1"), &globals.GetDraw(L"player_body"), true));
	globals.GetDraw(L"player_arm_right").transform.translate.Set(0,0.6,-1.5);
	globals.GetDraw(L"player_arm_right").selfTransform.rotate.z = 115;
	globals.GetDraw(L"player_arm_right").selfTransform.rotate.y = -10;
	globals.GetDraw(L"player_body").selfTransform.rotate.y = 90;
	globals.GetDraw(L"player_body").transform.translate.Set(10,4,0);

	//Draw Lost Child
	globals.AddDraw(drawOrder(L"lost_child_body",globals.GetMesh(L"characterbody"), &globals.GetMaterial(L"character2"), &globals.GetDraw(L"main"), true));
	globals.GetDraw(L"lost_child_body").transform.scale.Set(0.45,0.45,0.45);
	globals.GetDraw(L"lost_child_body").transform.rotate.Set(0,180,0);
	globals.GetDraw(L"lost_child_body").transform.translate.Set(3,2.9,-27); 
	globals.AddDraw(drawOrder(L"lost_child_arm_left",globals.GetMesh(L"characterarm"), &globals.GetMaterial(L"character2"), &globals.GetDraw(L"lost_child_body"), true));
	globals.GetDraw(L"lost_child_arm_left").transform.translate.Set(1.25,0.6,0);
	globals.GetDraw(L"lost_child_arm_left").transform.rotate.x = -5;
	globals.AddDraw(drawOrder(L"lost_child_arm_right",globals.GetMesh(L"characterarm"), &globals.GetMaterial(L"character2"), &globals.GetDraw(L"lost_child_body"), true));
	globals.GetDraw(L"lost_child_arm_right").transform.translate.Set(-1.25,0.6,0);
	globals.GetDraw(L"lost_child_arm_right").transform.rotate.x = -5;
	globals.AddDraw(drawOrder(L"lost_child_leg_left",globals.GetMesh(L"characterleg"), &globals.GetMaterial(L"character2"), &globals.GetDraw(L"lost_child_body"), true));
	globals.GetDraw(L"lost_child_leg_left").transform.translate.Set(0.5,-1.5,0);
	globals.AddDraw(drawOrder(L"lost_child_leg_right",globals.GetMesh(L"characterleg"), &globals.GetMaterial(L"character2"), &globals.GetDraw(L"lost_child_body"), true));
	globals.GetDraw(L"lost_child_leg_right").transform.translate.Set(-0.5,-1.5,0);

	//Draw Father
	globals.AddDraw(drawOrder(L"father_body",globals.GetMesh(L"characterbody"), &globals.GetMaterial(L"character2"), &globals.GetDraw(L"main"), true));
	globals.GetDraw(L"father_body").transform.translate.Set(18,5,-69);
	globals.GetDraw(L"father_body").transform.rotate.y = -90;
	globals.AddDraw(drawOrder(L"father_arm_left",globals.GetMesh(L"characterarm"), &globals.GetMaterial(L"character2"), &globals.GetDraw(L"father_body"), true));
	globals.GetDraw(L"father_arm_left").transform.translate.Set(1.25,0.6,0);
	globals.GetDraw(L"father_arm_left").transform.rotate.x = -5;
	globals.AddDraw(drawOrder(L"father_arm_right",globals.GetMesh(L"characterarm"), &globals.GetMaterial(L"character2"), &globals.GetDraw(L"father_body"), true));
	globals.GetDraw(L"father_arm_right").transform.translate.Set(-1.25,0.6,0);
	globals.GetDraw(L"father_arm_right").transform.rotate.x = -5;
	globals.AddDraw(drawOrder(L"father_leg_left",globals.GetMesh(L"characterleg"), &globals.GetMaterial(L"character2"), &globals.GetDraw(L"father_body"), true));
	globals.GetDraw(L"father_leg_left").transform.translate.Set(0.5,-1.5,0);
	globals.AddDraw(drawOrder(L"father_leg_right",globals.GetMesh(L"characterleg"), &globals.GetMaterial(L"character2"), &globals.GetDraw(L"father_body"), true));
	globals.GetDraw(L"father_leg_right").transform.translate.Set(-0.5,-1.5,0);


	//Draw Shopper Idler at level 1
	globals.AddDraw(drawOrder(L"shopper_idler_body",globals.GetMesh(L"characterbody"), &globals.GetMaterial(L"character1"), &globals.GetDraw(L"main"), true));
	globals.GetDraw(L"shopper_idler_body").transform.translate.Set(10,0.1,0);
	globals.AddDraw(drawOrder(L"shopper_idler_arm_left",globals.GetMesh(L"characterarm"), &globals.GetMaterial(L"character1"), &globals.GetDraw(L"shopper_idler_body"), true));
	globals.GetDraw(L"shopper_idler_arm_left").transform.translate.Set(1.25,0.6,0);
	globals.GetDraw(L"shopper_idler_arm_left").transform.rotate.x = -5;
	globals.AddDraw(drawOrder(L"shopper_idler_arm_right",globals.GetMesh(L"characterarm"), &globals.GetMaterial(L"character1"), &globals.GetDraw(L"shopper_idler_body"), true));
	globals.GetDraw(L"shopper_idler_arm_right").transform.translate.Set(-1.25,0.6,0);
	globals.GetDraw(L"shopper_idler_arm_right").transform.rotate.x = -5;
	globals.AddDraw(drawOrder(L"shopper_idler_leg_left",globals.GetMesh(L"characterleg"), &globals.GetMaterial(L"character1"), &globals.GetDraw(L"shopper_idler_body"), true));
	globals.GetDraw(L"shopper_idler_leg_left").transform.translate.Set(0.5,-1.5,0);
	globals.AddDraw(drawOrder(L"shopper_idler_leg_right",globals.GetMesh(L"characterleg"), &globals.GetMaterial(L"character1"), &globals.GetDraw(L"shopper_idler_body"), true));
	globals.GetDraw(L"shopper_idler_leg_right").transform.translate.Set(-0.5,-1.5,0);

	//Draw Shopper Wanderers at level 2
	drawOrder shopperwandererbody(L"shopper_wanderer_body",globals.GetMesh(L"characterbody"), &globals.GetMaterial(L"character1"), &globals.GetDraw(L"main"), true);
	Vector3 shopperwandererbodyTranslate(0,3.8,0);
	for(int i = 0; i < 2; ++i)
	{
		drawOrder buffer(shopperwandererbody);
		wchar_t Namebuffer[64];
		wsprintf(Namebuffer,L"shopper_wanderer_body%d",i);
		buffer.SetNameAs(Namebuffer);
		buffer.transform.translate = shopperwandererbodyTranslate;
		globals.AddDraw(buffer);
	}
	drawOrder shopperwandererarmleft(L"shopper_wanderer_arm_left",globals.GetMesh(L"characterarm"), &globals.GetMaterial(L"character1"), &globals.GetDraw(L"main"), true);
	Vector3 shopperwandererarmleftTranslate(1.25,0.6,0);
	float shopperwandererarmleftRotateX= -5;
	for(int i = 0; i < 2; ++i)
	{
		drawOrder buffer(shopperwandererarmleft);
		wchar_t Namebuffer[64];
		wsprintf(Namebuffer,L"shopper_wanderer_arm_left%d",i);
		buffer.SetNameAs(Namebuffer);
		wchar_t SWParentNamebuffer[64];
		wsprintf(SWParentNamebuffer,L"shopper_wanderer_body%d",i);
		buffer.SetParentAs(&globals.GetDraw(SWParentNamebuffer));
		buffer.transform.translate = shopperwandererarmleftTranslate;
		buffer.transform.rotate.x = shopperwandererarmleftRotateX;
		globals.AddDraw(buffer);
	}
	drawOrder shopperwandererarmright(L"shopper_wanderer_arm_right",globals.GetMesh(L"characterarm"), &globals.GetMaterial(L"character1"), &globals.GetDraw(L"main"), true);
	Vector3 shopperwandererarmrightTranslate(-1.25,0.6,0);
	float shopperwandererarmrightRotateX= -5;
	for(int i = 0; i < 2; ++i)
	{
		drawOrder buffer(shopperwandererarmright);
		wchar_t Namebuffer[64];
		wsprintf(Namebuffer,L"shopper_wanderer_arm_right%d",i);
		buffer.SetNameAs(Namebuffer);
		wchar_t SWParentNamebuffer[64];
		wsprintf(SWParentNamebuffer,L"shopper_wanderer_body%d",i);
		buffer.SetParentAs(&globals.GetDraw(SWParentNamebuffer));
		buffer.transform.translate = shopperwandererarmrightTranslate;
		buffer.transform.rotate.x = shopperwandererarmrightRotateX;
		globals.AddDraw(buffer);
	}
	drawOrder shopperwandererlegleft(L"shopper_wanderer_leg_left",globals.GetMesh(L"characterleg"), &globals.GetMaterial(L"character1"), &globals.GetDraw(L"main"), true);
	Vector3 shopperwandererlegleftTranslate(0.5,-1.5,0);
	for(int i = 0; i < 2; ++i)
	{
		drawOrder buffer(shopperwandererlegleft);
		wchar_t Namebuffer[64];
		wsprintf(Namebuffer,L"shopper_wanderer_leg_left%d",i);
		buffer.SetNameAs(Namebuffer);
		wchar_t SWParentNamebuffer[64];
		wsprintf(SWParentNamebuffer,L"shopper_wanderer_body%d",i);
		buffer.SetParentAs(&globals.GetDraw(SWParentNamebuffer));
		buffer.transform.translate = shopperwandererlegleftTranslate;
		globals.AddDraw(buffer);
	}
	drawOrder shopperwandererlegright(L"shopper_wanderer_leg_right",globals.GetMesh(L"characterleg"), &globals.GetMaterial(L"character1"), &globals.GetDraw(L"main"), true);
	Vector3 shopperwandererlegrightTranslate(-0.5,-1.5,0);
	for(int i = 0; i < 2; ++i)
	{
		drawOrder buffer(shopperwandererlegright);
		wchar_t Namebuffer[64];
		wsprintf(Namebuffer,L"shopper_wanderer_leg_right%d",i);
		buffer.SetNameAs(Namebuffer);
		wchar_t SWParentNamebuffer[64];
		wsprintf(SWParentNamebuffer,L"shopper_wanderer_body%d",i);
		buffer.SetParentAs(&globals.GetDraw(SWParentNamebuffer));
		buffer.transform.translate = shopperwandererlegrightTranslate;
		globals.AddDraw(buffer);
	}

	//Draw Wizard
	globals.AddDraw(drawOrder(L"wizard_body",globals.GetMesh(L"wizardbody"), &globals.GetMaterial(L"character4"), &globals.GetDraw(L"main"), true));
	globals.GetDraw(L"wizard_body").transform.translate.Set(-18,15,-102);
	globals.GetDraw(L"wizard_body").transform.rotate.y = 90;
	globals.AddDraw(drawOrder(L"wizard_arm_left",globals.GetMesh(L"characterarm"), &globals.GetMaterial(L"character4"), &globals.GetDraw(L"wizard_body"), true));
	globals.GetDraw(L"wizard_arm_left").transform.translate.Set(1.25,0.6,0);
	globals.AddDraw(drawOrder(L"wizard_arm_right",globals.GetMesh(L"characterarm"), &globals.GetMaterial(L"character4"), &globals.GetDraw(L"wizard_body"), true));
	globals.GetDraw(L"wizard_arm_right").transform.translate.Set(-1.25,0.6,0);
	globals.AddDraw(drawOrder(L"wizard_leg_left",globals.GetMesh(L"characterleg"), &globals.GetMaterial(L"character4"), &globals.GetDraw(L"wizard_body"), true));
	globals.GetDraw(L"wizard_leg_left").transform.translate.Set(0.5,-1.5,0);
	globals.AddDraw(drawOrder(L"wizard_leg_right",globals.GetMesh(L"characterleg"), &globals.GetMaterial(L"character4"), &globals.GetDraw(L"wizard_body"), true));
	globals.GetDraw(L"wizard_leg_right").transform.translate.Set(-0.5,-1.5,0);

	//Draw Lift
	drawOrder lift(L"lift",globals.GetMesh(L"lift"), &globals.GetMaterial(L"lift"), &globals.GetDraw(L"main"), true);
	//Vector3 liftTranslate(15.0,5.5,-101.6); orignal
	Vector3 liftTranslate(15.0,5.5,-97.6);
	for(int i = 0; i < 2; ++i)
	{
		drawOrder buffer(lift);
		wchar_t Namebuffer[64];
		wsprintf(Namebuffer,L"lift%d",i);
		buffer.SetNameAs(Namebuffer);
		buffer.transform.translate = liftTranslate;
		globals.AddDraw(buffer);
		liftTranslate+= Vector3(0,10.1,0);
	}
	//Draw Lift Directories level1
	globals.AddDraw(drawOrder(L"liftlevel1",globals.GetMesh(L"liftlevel1"), &globals.GetMaterial(L"liftlevel1"),&globals.GetDraw(L"main"),true));
	//globals.GetDraw(L"liftlevel1").transform.translate.Set(15.0,8.5,-99.2); orignal
	globals.GetDraw(L"liftlevel1").transform.translate.Set(15.0,8.5,-92.65);
	globals.GetDraw(L"liftlevel1").transform.rotate.Set(0,180,0);

	//Draw Lift Directories level2
	globals.AddDraw(drawOrder(L"liftlevel2",globals.GetMesh(L"liftlevel2"), &globals.GetMaterial(L"liftlevel2"),&globals.GetDraw(L"main"),true));
	//globals.GetDraw(L"liftlevel2").transform.translate.Set(15.0,18.6,-99.2); orignal
	globals.GetDraw(L"liftlevel2").transform.translate.Set(15.0,18.6,-92.65);
	globals.GetDraw(L"liftlevel2").transform.rotate.Set(0,180,0);

	//Draw liftdoor
	globals.AddDraw(drawOrder(L"liftdoor_1_left",globals.GetMesh(L"liftdoor"), &globals.GetMaterial(L"liftdoor"), &globals.GetDraw(L"main"), true));
	//globals.GetDraw(L"liftdoor_1_left").transform.translate.Set(14.0,5,-98.6); orignal
	globals.GetDraw(L"liftdoor_1_left").transform.scale.Set(1,1,0.8);
	globals.GetDraw(L"liftdoor_1_left").transform.translate.Set(14.0,5,-91.05);

	globals.AddDraw(drawOrder(L"liftdoor_1_right",globals.GetMesh(L"liftdoor"), &globals.GetMaterial(L"liftdoor"), &globals.GetDraw(L"main"), true));
	//globals.GetDraw(L"liftdoor_1_right").transform.translate.Set(16.0,5,-98.6); orignal
	globals.GetDraw(L"liftdoor_1_right").transform.scale.Set(1,1,0.8);
	globals.GetDraw(L"liftdoor_1_right").transform.translate.Set(16.0,5,-91.05);

	globals.AddDraw(drawOrder(L"liftdoor_2_left",globals.GetMesh(L"liftdoor"), &globals.GetMaterial(L"liftdoor"), &globals.GetDraw(L"main"), true));
	//globals.GetDraw(L"liftdoor_2_left").transform.translate.Set(14.0,15.1,-98.6); orignal
	globals.GetDraw(L"liftdoor_2_left").transform.scale.Set(1,1,0.8);
	globals.GetDraw(L"liftdoor_2_left").transform.translate.Set(14.0,15.1,-91.05);

	globals.AddDraw(drawOrder(L"liftdoor_2_right",globals.GetMesh(L"liftdoor"), &globals.GetMaterial(L"liftdoor"), &globals.GetDraw(L"main"), true));
	//globals.GetDraw(L"liftdoor_2_right").transform.translate.Set(16.0,15.1,-98.6); orignal
	globals.GetDraw(L"liftdoor_2_right").transform.scale.Set(1,1,0.8);
	globals.GetDraw(L"liftdoor_2_right").transform.translate.Set(16.0,15.1,-91.05);

	//Draw Cashier Table
	drawOrder cashiertable(L"cashiertable",globals.GetMesh(L"cashiertable"), &globals.GetMaterial(L"cashiertable"), &globals.GetDraw(L"main"), true);
	Vector3 cashiertableTranslate(5,1,-84.2);
	for(int i = 0; i < 2; ++i)
	{
		drawOrder buffer(cashiertable);
		wchar_t Namebuffer[64];
		wsprintf(Namebuffer,L"cashiertable%d",i);
		buffer.SetNameAs(Namebuffer);
		buffer.transform.translate = cashiertableTranslate;
		globals.AddDraw(buffer);
		cashiertableTranslate+= Vector3(-15,0,0);
	}

	//Draw cashier robot0
	globals.AddDraw(drawOrder(L"robotbody0",globals.GetMesh(L"robotbody"), &globals.GetMaterial(L"robot"), &globals.GetDraw(L"cashiertable0"), true));
	globals.GetDraw(L"robotbody0").transform.translate.Set(1,4,-4);

	globals.AddDraw(drawOrder(L"robotarm_left0",globals.GetMesh(L"robotarm"), &globals.GetMaterial(L"robot"), &globals.GetDraw(L"robotbody0"), true));
	globals.GetDraw(L"robotarm_left0").transform.translate.Set(-1,1,0);

	globals.AddDraw(drawOrder(L"robotarm_right0",globals.GetMesh(L"robotarm"), &globals.GetMaterial(L"robot"), &globals.GetDraw(L"robotbody0"), true));
	globals.GetDraw(L"robotarm_right0").transform.translate.Set(1,1,0);

	//Draw cashier robot1
	globals.AddDraw(drawOrder(L"robotbody1",globals.GetMesh(L"robotbody"), &globals.GetMaterial(L"robot"), &globals.GetDraw(L"cashiertable1"), true));
	globals.GetDraw(L"robotbody1").transform.translate.Set(1,4,-4);

	globals.AddDraw(drawOrder(L"robotarm_left1",globals.GetMesh(L"robotarm"), &globals.GetMaterial(L"robot"), &globals.GetDraw(L"robotbody1"), true));
	globals.GetDraw(L"robotarm_left1").transform.translate.Set(-1,1,0);

	globals.AddDraw(drawOrder(L"robotarm_right1",globals.GetMesh(L"robotarm"), &globals.GetMaterial(L"robot"), &globals.GetDraw(L"robotbody1"), true));
	globals.GetDraw(L"robotarm_right1").transform.translate.Set(1,1,0);

	//Draw main menu
	globals.AddDraw(drawOrder(L"Quad1",globals.GetMesh(L"Quad1"), &globals.GetMaterial(L"Quad1"),NULL, true));
	globals.GetDraw(L"Quad1").transform.translate.Set(1,4,-4);
	globals.AddDraw(drawOrder(L"Quad2",globals.GetMesh(L"Quad1"), &globals.GetMaterial(L"Quad2"), NULL, true));
	globals.GetDraw(L"Quad2").transform.translate.Set(1,4,-4);
	globals.AddDraw(drawOrder(L"Quad3",globals.GetMesh(L"Quad1"), &globals.GetMaterial(L"Quad3"), NULL, true));
	globals.GetDraw(L"Quad3").transform.translate.Set(1,4,-4);
	globals.AddDraw(drawOrder(L"Quad4",globals.GetMesh(L"Quad1"), &globals.GetMaterial(L"Quad4"), NULL, true));
	globals.GetDraw(L"Quad4").transform.translate.Set(1,4,-4);
	globals.AddDraw(drawOrder(L"BG",globals.GetMesh(L"BG"), &globals.GetMaterial(L"BG"), NULL, true));
	globals.GetDraw(L"BG").transform.translate.Set(1,4,-4);
	globals.AddDraw(drawOrder(L"incredits",globals.GetMesh(L"incredits"), &globals.GetMaterial(L"incredits"), NULL, true));
	globals.GetDraw(L"incredits").transform.translate.Set(1,4,-4);
	globals.AddDraw(drawOrder(L"inexit",globals.GetMesh(L"inexit"), &globals.GetMaterial(L"inexit"), NULL, true));
	globals.GetDraw(L"inexit").transform.translate.Set(1,4,-4);
	globals.AddDraw(drawOrder(L"instructions",globals.GetMesh(L"instructions"), &globals.GetMaterial(L"instructions"), NULL, true));
	globals.GetDraw(L"instructions").transform.translate.Set(1,4,-4);

	//Draw Travelator Support
	drawOrder travelatorsupport(L"travelatorsupport",globals.GetMesh(L"travelatorsupport"), &globals.GetMaterial(L"dullwhite"), &globals.GetDraw(L"main"), true);
	Vector3 travelatorsupportTranslate(-2,7.1,-21.7);
	for(int i = 0; i < 2; ++i)
	{
		drawOrder buffer(travelatorsupport);
		wchar_t Namebuffer[64];
		wsprintf(Namebuffer,L"travelatorsupport%d",i);
		buffer.SetNameAs(Namebuffer);
		buffer.transform.scale.Set(1,1,1.12);
		buffer.transform.translate = travelatorsupportTranslate;
		globals.AddDraw(buffer);
		travelatorsupportTranslate+= Vector3(0,0,-2.9);
	}
	//Draw Travelator Slope
	drawOrder travelatorslope(L"travelatorslope",globals.GetMesh(L"travelatorslope"), &globals.GetMaterial(L"travelatorslope"), &globals.GetDraw(L"main"), true);
	Vector3 travelatorslopeTranslate(-2,5.91,-21.7);
	for(int i = 0; i < 2; ++i)
	{
		drawOrder buffer(travelatorslope);
		wchar_t Namebuffer[64];
		wsprintf(Namebuffer,L"travelatorslope%d",i);
		buffer.SetNameAs(Namebuffer);
		buffer.transform.scale.Set(1,1,1.12);
		buffer.transform.translate = travelatorslopeTranslate;
		globals.AddDraw(buffer);
		travelatorslopeTranslate+= Vector3(0,0,-2.8);
	}
	//Draw Travelator Handle 1 AND 2
	drawOrder travelatorhandle(L"travelatorhandle",globals.GetMesh(L"travelatorhandle"), &globals.GetMaterial(L"travelatorhandle"), &globals.GetDraw(L"main"), true);
	Vector3 travelatorhandleTranslate(-1.8,7.8,-20.37);
	for(int i = 0; i < 2; ++i)
	{
		drawOrder buffer(travelatorhandle);
		wchar_t Namebuffer[64];
		wsprintf(Namebuffer,L"travelatorhandle%d",i);
		buffer.SetNameAs(Namebuffer);
		buffer.transform.translate = travelatorhandleTranslate;
		globals.AddDraw(buffer);
		travelatorhandleTranslate+= Vector3(0,0,-2.46);
	}
	//Draw Travelator Handle 3 AND 4
	drawOrder travelatorhandle2(L"travelatorhandle",globals.GetMesh(L"travelatorhandle"), &globals.GetMaterial(L"travelatorhandle"), &globals.GetDraw(L"main"), true);
	Vector3 travelatorhandleTranslate2(-1.8,7.8,-23.33);
	for(int i = 3; i < 5; ++i)
	{
		drawOrder buffer(travelatorhandle2);
		wchar_t Namebuffer[64];
		wsprintf(Namebuffer,L"travelatorhandle%d",i);
		buffer.SetNameAs(Namebuffer);
		buffer.transform.translate = travelatorhandleTranslate2;
		globals.AddDraw(buffer);
		travelatorhandleTranslate2+= Vector3(0,0,-2.46);
	}

	//Draw Outer Door
	globals.AddDraw(drawOrder(L"outer_door_1_right",globals.GetMesh(L"outerdoor"), &globals.GetMaterial(L"door texture"), &globals.GetDraw(L"main"), false));
	globals.GetDraw(L"outer_door_1_right").transform.scale.Set(1,1,0.9);
	globals.GetDraw(L"outer_door_1_right").transform.translate.Set(2,4.5,-8.5829);


	globals.AddDraw(drawOrder(L"outer_door_1_left",globals.GetMesh(L"outerdoor"), &globals.GetMaterial(L"door texture"), &globals.GetDraw(L"main"), false));
	globals.GetDraw(L"outer_door_1_left").transform.scale.Set(1,1,0.9);
	globals.GetDraw(L"outer_door_1_left").transform.translate.Set(-2,4.5,-8.5829);


	globals.AddDraw(drawOrder(L"outer_door_2_right",globals.GetMesh(L"outerdoor"), &globals.GetMaterial(L"door texture"), &globals.GetDraw(L"main"), false));
	globals.GetDraw(L"outer_door_2_right").transform.scale.Set(1,1,0.9);
	globals.GetDraw(L"outer_door_2_right").transform.translate.Set(-9,4.5,-105.4);


	globals.AddDraw(drawOrder(L"outer_door_2_left",globals.GetMesh(L"outerdoor"), &globals.GetMaterial(L"door texture"), &globals.GetDraw(L"main"), false));
	globals.GetDraw(L"outer_door_2_left").transform.scale.Set(1,1,0.9);
	globals.GetDraw(L"outer_door_2_left").transform.translate.Set(-13,4.5,-105.4);


	globals.AddDraw(drawOrder(L"inner_door_1",globals.GetMesh(L"innerdoor"), &globals.GetMaterial(L"door texture"), &globals.GetDraw(L"main"), false));
	globals.GetDraw(L"inner_door_1").transform.translate.Set(-17.5,4.5,-19.6);

	globals.AddDraw(drawOrder(L"inner_door_2",globals.GetMesh(L"innerdoor"), &globals.GetMaterial(L"door texture"), &globals.GetDraw(L"main"), false));
	globals.GetDraw(L"inner_door_2").transform.scale.Set(1,1,0.7);
	globals.GetDraw(L"inner_door_2").transform.translate.Set(-17.5,14.5,-19.5);

	//Draw Trolley First Row
	drawOrder trolley(L"trolley",globals.GetMesh(L"trolley"), &globals.GetMaterial(L"trolley"), &globals.GetDraw(L"main"), true);
	Vector3 trolleyTranslate(14,4.65,-16);
	for(int i = 0; i < 3; ++i)
	{
		drawOrder buffer(trolley);
		wchar_t Namebuffer[64];
		wsprintf(Namebuffer,L"trolley%d",i);
		buffer.SetNameAs(Namebuffer);
		buffer.transform.translate = trolleyTranslate;
		globals.AddDraw(buffer);
		trolleyTranslate+= Vector3(-1.5,0,0);
	}

	//Draw Trolley Second Row
	drawOrder trolley2(L"trolley",globals.GetMesh(L"trolley"), &globals.GetMaterial(L"trolley"), &globals.GetDraw(L"main"), true);
	Vector3 trolleyTranslate2(14,4.65,-12);
	for(int i = 3; i < 6; ++i)
	{
		drawOrder buffer(trolley2);
		wchar_t Namebuffer[64];
		wsprintf(Namebuffer,L"trolley%d",i);
		buffer.SetNameAs(Namebuffer);
		buffer.transform.translate = trolleyTranslate2;
		globals.AddDraw(buffer);
		trolleyTranslate2+= Vector3(-1.5,0,0);
	}

	//Draw lv1Cabinet3_column1
	drawOrder lv1cabinet3_column1(L"lv1cabinet3_column1",globals.GetMesh(L"cabinet3"), &globals.GetMaterial(L"cabinet"), &globals.GetDraw(L"main"), true);
	Vector3 lv1cabinet3_column1Translate(-3.5,1,-42);
	for(int i = 0; i < 2; ++i)
	{
		drawOrder buffer(lv1cabinet3_column1);
		wchar_t Namebuffer[64];
		wsprintf(Namebuffer,L"lv1cabinet3_column1_%d",i);
		buffer.SetNameAs(Namebuffer);
		buffer.transform.translate = lv1cabinet3_column1Translate; 
		globals.AddDraw(buffer);
		lv1cabinet3_column1Translate+= Vector3(0,0,-18);
	}

	//Draw lv2Cabinet1_column1
	drawOrder lv2cabinet1_column1(L"lv2cabinet1_column1",globals.GetMesh(L"cabinet1"), &globals.GetMaterial(L"cabinet"), &globals.GetDraw(L"main"), true);
	Vector3 lv2cabinet1_column1Translate(-18,11,-43);
	for(int i = 0; i < 5; ++i)
	{
		drawOrder buffer(lv2cabinet1_column1);
		wchar_t Namebuffer[64];
		wsprintf(Namebuffer,L"lv2cabinet1_column1_%d",i);
		buffer.SetNameAs(Namebuffer);
		buffer.transform.translate = lv2cabinet1_column1Translate; 
		buffer.transform.rotate.Set(0,90,0);
		globals.AddDraw(buffer);
		lv2cabinet1_column1Translate+= Vector3(0,0,-13);
	}

	//Draw lv2Cabinet2_column1
	drawOrder lv2cabinet2_column1(L"lv2cabinet2_column1",globals.GetMesh(L"cabinet2"), &globals.GetMaterial(L"cabinet"), &globals.GetDraw(L"main"), true);
	Vector3 lv2cabinet2_column1Translate(-2,11,-43);
	for(int i = 0; i < 4; ++i)
	{
		drawOrder buffer(lv2cabinet2_column1);
		wchar_t Namebuffer[64];
		wsprintf(Namebuffer,L"lv2cabinet2_column1_%d",i);
		buffer.SetNameAs(Namebuffer);
		buffer.transform.translate = lv2cabinet2_column1Translate; 
		buffer.transform.rotate.Set(0,-90,0);
		globals.AddDraw(buffer);
		lv2cabinet2_column1Translate+= Vector3(0,0,-16);
	}

	//Draw lv2Cabinet2_column2
	drawOrder lv2cabinet2_column2(L"lv2cabinet2_column2",globals.GetMesh(L"cabinet2"), &globals.GetMaterial(L"cabinet"), &globals.GetDraw(L"main"), true);
	Vector3 lv2cabinet2_column2Translate(1.5,11,-43);
	for(int i = 0; i < 4; ++i)
	{
		drawOrder buffer(lv2cabinet2_column2);
		wchar_t Namebuffer[64];
		wsprintf(Namebuffer,L"lv2cabinet2_column2_%d",i);
		buffer.SetNameAs(Namebuffer);
		buffer.transform.translate = lv2cabinet2_column2Translate; 
		buffer.transform.rotate.Set(0,90,0);
		globals.AddDraw(buffer);
		lv2cabinet2_column2Translate+= Vector3(0,0,-16);
	}
	//Draw Hidden room cabinets
	drawOrder lv2cabinet4_hiddenroom(L"lv2cabinet4_hiddenroom",globals.GetMesh(L"cabinet4"), &globals.GetMaterial(L"cabinet"), &globals.GetDraw(L"main"), true);
	Vector3 lv2cabinet4_hiddenroomTranslate(3,11,-16);
	for(int i = 0; i < 2; ++i)
	{
		drawOrder buffer(lv2cabinet4_hiddenroom);
		wchar_t Namebuffer[64];
		wsprintf(Namebuffer,L"lv2cabinet4_hiddenroom_%d",i);
		buffer.SetNameAs(Namebuffer);
		buffer.transform.translate = lv2cabinet4_hiddenroomTranslate; 
		buffer.transform.rotate.y=90;
		globals.AddDraw(buffer);
		lv2cabinet4_hiddenroomTranslate+= Vector3(-14,0,0);
	}
	drawOrder lv2cabinet5_hiddenroom(L"lv2cabinet5_hiddenroom",globals.GetMesh(L"cabinet4"), &globals.GetMaterial(L"cabinet"), &globals.GetDraw(L"main"), true);
	Vector3 lv2cabinet5_hiddenroomTranslate(10,11,-12);
	for(int i = 0; i < 2; ++i)
	{
		drawOrder buffer(lv2cabinet5_hiddenroom);
		wchar_t Namebuffer[64];
		wsprintf(Namebuffer,L"lv2cabinet5_hiddenroom_%d",i);
		buffer.SetNameAs(Namebuffer);
		buffer.transform.translate = lv2cabinet5_hiddenroomTranslate; 
		buffer.transform.rotate.y=90;
		globals.AddDraw(buffer);
		lv2cabinet5_hiddenroomTranslate+= Vector3(-14,0,0);
	}



	//Draw ShopperPayer
	globals.AddDraw(drawOrder(L"shopper_payer_body",globals.GetMesh(L"characterbody"), &globals.GetMaterial(L"character1"), &globals.GetDraw(L"main"), true));
	globals.AddDraw(drawOrder(L"shopper_payer_arm_left",globals.GetMesh(L"characterarm"), &globals.GetMaterial(L"character1"), &globals.GetDraw(L"shopper_payer_body"), true));
	globals.GetDraw(L"shopper_payer_arm_left").transform.translate.Set(1.25,0.6,0);
	globals.GetDraw(L"shopper_payer_arm_left").selfTransform.rotate.x = -70;
	globals.AddDraw(drawOrder(L"shopper_payer_arm_right",globals.GetMesh(L"characterarm"), &globals.GetMaterial(L"character1"), &globals.GetDraw(L"shopper_payer_body"), true));
	globals.GetDraw(L"shopper_payer_arm_right").transform.translate.Set(-1.25,0.6,0);
	globals.GetDraw(L"shopper_payer_arm_right").selfTransform.rotate.x = -70;
	globals.AddDraw(drawOrder(L"shopper_payer_leg_left",globals.GetMesh(L"characterleg"), &globals.GetMaterial(L"character1"), &globals.GetDraw(L"shopper_payer_body"), true));
	globals.GetDraw(L"shopper_payer_leg_left").transform.translate.Set(0.5,-1.5,0);
	globals.AddDraw(drawOrder(L"shopper_payer_leg_right",globals.GetMesh(L"characterleg"), &globals.GetMaterial(L"character1"), &globals.GetDraw(L"shopper_payer_body"), true));
	globals.GetDraw(L"shopper_payer_leg_right").transform.translate.Set(-0.5,-1.5,0);
	globals.AddDraw(drawOrder(L"shopper_payer_trolley",globals.GetMesh(L"trolley"), &globals.GetMaterial(L"trolley"), &globals.GetDraw(L"shopper_payer_body"), true));
	globals.GetDraw(L"shopper_payer_trolley").transform.translate.Set(0,-0.4,2);
	globals.GetDraw(L"shopper_payer_trolley").selfTransform.rotate.y = -90;
	globals.AddDraw(drawOrder(L"shopper_payer_items",globals.GetMesh(L"cereallump"), &globals.GetMaterial(L"cereal2"), &globals.GetDraw(L"lv1cabinet3_column1_0"), true));

	//CAN_1: 36 a bunch. 360cans total
	CreateItems(drawOrder(L"can1_cabinet1_%d",globals.GetMesh(L"can1"), &globals.GetMaterial(L"can1"), NULL, true),Vector3(-3.25,5.25,1), L"lv2cabinet1_column1_0", Rotation(0,0,0), 6, 6, 1, 0.5, -0.4, 2, 5, Vector3(1.5,0,0), Vector3(6.5,0,0));

	//CAN_2: 6 a bunch. 60cans total 
	CreateItems(drawOrder(L"can2_cabinet1_%d",globals.GetMesh(L"can2"), &globals.GetMaterial(L"can2"), NULL, true),Vector3(-3.25,2.8,1), L"lv2cabinet1_column1_0", Rotation(0,0,0), 2, 3, 0.45, 1.2, -0.9, 2, 5, Vector3(1.7,0,0), Vector3(6.5,0,0));
	//CAN_3: 25 a bunch. 250cans total
	CreateItems(drawOrder(L"can3_cabinet1_%d",globals.GetMesh(L"can3"), &globals.GetMaterial(L"can3"), NULL, true),Vector3(-3.2,0.3,1), L"lv2cabinet1_column1_0", Rotation(0,0,0), 5, 5, 1, 0.6, -0.5, 2, 5, Vector3(1.55,0,0), Vector3(6.65,0,0));
	//Packet1: 3 a bunch. 36packet total
	CreateItems(drawOrder(L"packet1_cabinet2_column1_%d",globals.GetMesh(L"packet1"), &globals.GetMaterial(L"packet1"), NULL, true),Vector3(3.15,6.3,0.9), L"lv2cabinet2_column1_0", Rotation(0,0,0), 3, 1, 0.9, 0, -1, 3, 4, Vector3(0,-2.9,0), Vector3(-16,5.8,0));
	//Packet2: 3 a bunch. 36packet total
	CreateItems(drawOrder(L"packet2_cabinet2_column2_%d",globals.GetMesh(L"packet2"), &globals.GetMaterial(L"packet2"), NULL, true),Vector3(3.15,6.3,0.9), L"lv2cabinet2_column2_0", Rotation(0,0,0), 3, 1, 0.9, 0, -1, 3, 4, Vector3(0,-2.9,0), Vector3(16,5.8,0));
	//Packet3: 16 a bunch. 192packet total
	CreateItems(drawOrder(L"packet3_cabinet2_column1_%d",globals.GetMesh(L"packet3"), &globals.GetMaterial(L"packet3"), NULL, true),Vector3(0.75,6.3,0.9), L"lv2cabinet2_column1_0", Rotation(0,0,0), 4, 4, 1, -1.3, -0.6, 3, 4, Vector3(3.95,-2.9,0), Vector3(-12.2,5.8,0));
	//CAN_4: 15 a bunch. 180cans total
	CreateItems(drawOrder(L"can4_cabinet2_column2_%d",globals.GetMesh(L"can4"), &globals.GetMaterial(L"can4"), NULL, true),Vector3(0.9,6.3,1), L"lv2cabinet2_column2_0", Rotation(0,90,0), 3, 5, 1, -1, -0.8, 3, 4, Vector3(3.95,-2.9,0), Vector3(20.2,5.8,0));
	//Cereal1: 18 a bunch. 36cereals total
	CreateItems(drawOrder(L"cereal1_cabinet3_%d",globals.GetMesh(L"cereal1"), &globals.GetMaterial(L"cereal1"), NULL, true),Vector3(-3.3,3,1.5), L"lv1cabinet3_column1_0", Rotation(0,0,0), 6, 3, 1.5, 1.4, 0.7, 1, 2, Vector3(0,0,0), Vector3(2.75,0,0));
	//Cereal2: 12 a bunch. 24cereals total
	CreateItems(drawOrder(L"cereal2_cabinet3_%d",globals.GetMesh(L"cereal2"), &globals.GetMaterial(L"cereal2"), NULL, true),Vector3(-3,3,-4.5), L"lv1cabinet3_column1_0", Rotation(0,180,0), 6, 2, -4.5, 1.6, 0.7, 1, 2, Vector3(0,0,0), Vector3(4.2,0,0));
	//Cereal3: 18 a bunch. 36cereals total
	CreateItems(drawOrder(L"cereal3_cabinet3_%d",globals.GetMesh(L"cereal3"), &globals.GetMaterial(L"cereal3"), NULL, true),Vector3(-3.3,3,1.5), L"lv1cabinet3_column1_1", Rotation(0,0,0), 6, 3, 1.5, 1.4, 0.7, 1, 2, Vector3(0,0,0), Vector3(2.75,0,0));
	//Cereal4: 18 a bunch. 36cereals total
	CreateItems(drawOrder(L"cereal4_cabinet3_%d",globals.GetMesh(L"cereal4"), &globals.GetMaterial(L"cereal4"), NULL, true),Vector3(-3.8,3,-4.5), L"lv1cabinet3_column1_1", Rotation(0,180,0), 6, 3, -4.5, 1.6, 0.7, 1, 2, Vector3(0,0,0), Vector3(2.75,0,0));

	//Draw Lollipop on ground
	globals.AddDraw(drawOrder(L"lollipop",globals.GetMesh(L"lollipop"), &globals.GetMaterial(L"lollipop"), &globals.GetDraw(L"main"), true));
	globals.GetDraw(L"lollipop").transform.rotate.Set(85,0,-45);
	globals.GetDraw(L"lollipop").transform.translate.Set(18,11.25,-21);
	//Draw Lollipop fences
	drawOrder BigLollipop(L"big_lollipop",globals.GetMesh(L"lollipop"), &globals.GetMaterial(L"lollipop"), &globals.GetDraw(L"main"), true);
	Vector3 BigLollipoptranslate(225,0,210);
	Vector3 BigLollipopscale(50,50,50);
	for(int i = 0; i < 20; ++i)
	{
		drawOrder buffer(BigLollipop);
		wchar_t Namebuffer[64];
		wsprintf(Namebuffer,L"big_lollipop%d",i);
		buffer.SetNameAs(Namebuffer);
		buffer.transform.scale = BigLollipopscale;
		buffer.transform.translate = BigLollipoptranslate;
		if(i > 9)
			buffer.transform.translate.z = -290;
		globals.AddDraw(buffer);
		if(i > 9)
			BigLollipoptranslate+= Vector3(50,0,0);
		else if(i < 9)
			BigLollipoptranslate+= Vector3(-50,0,0);
	}
	BigLollipoptranslate.z -= 25;
	for(int i = 20; i < 34; ++i)
	{
		drawOrder buffer(BigLollipop);
		wchar_t Namebuffer[64];
		wsprintf(Namebuffer,L"big_lollipop%d",i);
		buffer.SetNameAs(Namebuffer);
		buffer.transform.scale = BigLollipopscale * 1.5;
		buffer.transform.translate = BigLollipoptranslate;
		buffer.transform.rotate.y = 90;
		if(i > 26)
			buffer.transform.translate.x = -250;
		else
			buffer.transform.translate.x = 250;
		globals.AddDraw(buffer);
		if(i > 26)
			BigLollipoptranslate+= Vector3(0,0,75);
		if(i < 26)
			BigLollipoptranslate+= Vector3(0,0,-75);
	}
}
/****************************************************************************/
/*!
\brief
used to init items for hiddenroom
\param drawOrder& basedraw
baesedraw to get in item
\param const Vector3 offset
offset for how much to increase
\param Vector3 increment
increment for final value
*/
/****************************************************************************/
void SceneMain::InnitItems(const drawOrder& basedraw, const Vector3 offset, Vector3 increment)
{
	Vector3 individualOffset = offset;
	for(int i = 0; i < 2; ++i, individualOffset += increment)
	{
		drawOrder buffer(basedraw);
		wchar_t Namebuffer[64];
		wsprintf(Namebuffer,L"lv2cabinet5_hiddenroom_%d",i);
		buffer.SetNameAs(Namebuffer);
		buffer.transform.translate = individualOffset; 
		buffer.transform.rotate.y=90;
		globals.AddDraw(buffer);
	}
}
/****************************************************************************/
/*!
\brief
algorithm used for the creation of our items. 
\param drawOrder& item          
item: to pass in the obj used
\param Vector3 offset
offset: initial location of first item
\param std::wstring parentname
parentname: name of parents
\param Rotation RotateItem
RotateItem: to take in rotation
\param int ItemPerColumn
ItemPerColumn: how many items are there in a column
\param int ColumnPerCompartment
ColumnPerCompartment: how many column are there in a bunch
\param float defaultZ
defaultZ: starting position of each row based on Z axis
\param float ItemDistanceX
Distance X axis of each item
\param float ItemDistanceZ
Distance Z axis of each item
\param int NumBunch
How many set of items in one cabinet
\param int NumCabinet
How many Cabinet
\param Vector3 BunchOffset
difference of distance of each bunch
\param Vector3 CabinetOffset
difference of distance every cabinet
*/
/****************************************************************************/
void SceneMain::CreateItems(drawOrder& item, Vector3 offset, std::wstring parentname, Rotation RotateItem, int ItemPerColumn, int ColumnPerCompartment,float defaultZ, float ItemDistanceX,float ItemDistanceZ, int NumBunch, int NumCabinet, Vector3 BunchOffset, Vector3 CabinetOffset)
{	
	int item_count = 0;

	for(int i = 0; i < NumCabinet; i++) // place in 5 cabinet
	{
		if (i>0)
		{
			offset += CabinetOffset;
		}

		for(int i = 0; i < NumBunch; i++) // 2 bunch for one cabinet
		{	
			if (i>0)
			{
				offset += BunchOffset;
			}

			for(int i = 0; i < ColumnPerCompartment; ++i) // 6 column for one compartment
			{
				offset.z = defaultZ;
				if(i>0)
				{
					offset+= Vector3(ItemDistanceX,0,0);
				}

				for(int i = 0; i < ItemPerColumn; ++i) //6 cans in one column
				{

					drawOrder buffer(item);
					wchar_t Namebuffer[64];
					wsprintf(Namebuffer, item.GetName().c_str() , item_count);
					buffer.SetNameAs(Namebuffer);
					buffer.transform.translate = offset;
					buffer.transform.rotate = RotateItem;
					globals.AddDraw(buffer);
					offset+= Vector3(0,0,ItemDistanceZ);
					globals.GetDraw(buffer.GetName()).SetParentAs(&globals.GetDraw(parentname));

					item_count++;
				}
			}
		}
	}
}
/****************************************************************************/
/*!
\brief
initialising collisions with obj
*/
/****************************************************************************/
void SceneMain::InnitCollisions()
{
	globals.AddCollisionBody(CollisionBody(L"player", &globals.GetDraw(L"player_body"), &globals.GetDraw(L"player_body"), 1, 1, 0.1, 0.1));
	globals.GetCollisionBody(L"player").SetTerminalVelocityTo(Vector3(500,500,500));

	globals.AddCollisionBody(CollisionBody(L"ground", &globals.GetDraw(L"ground"), &globals.GetDraw(L"ground"), 0, 1, 0.1, 0.1));

	globals.AddCollisionBody(CollisionBody(L"building", &globals.GetDraw(L"building"), &globals.GetDraw(L"building"), 0, 1, 0.1, 0.1));

	for(std::map<std::wstring, CollisionBody*>::iterator body = globals.GetCollisionBodiesList().begin(), end = globals.GetCollisionBodiesList().end(); body != end; ++body)
	{
		body->second->GenerateVoxels();
	}
	globals.GetDraw(L"player_body").SetMeshTo(NULL);
}
/****************************************************************************/
/*!
\brief
initializing forces, acceleration.
*/
/****************************************************************************/
void SceneMain::InnitForces()
{
	Vector3 accelerationDueToGravity(0, -39.8f, 0);
	for(std::map<std::wstring, CollisionBody*>::iterator body = globals.GetCollisionBodiesList().begin(), end = globals.GetCollisionBodiesList().end(); body != end; ++body)
	{
		body->second->AddForce(accelerationDueToGravity * body->second->GetMass());
	}
}
/****************************************************************************/
/*!
\brief
updating of scene 
\param dt - deltatime
used to take in deltatime which allow movements and animations
\return
is update true or false
*/
/****************************************************************************/
bool SceneMain::Update(const double dt)
{
	float rotationspeed = 2;
	deltaTime = dt;
	accumulatingDT += deltaTime;
	frameCounter++;
	const double undateInterval = 0.2;
	if(accumulatingDT > undateInterval)
	{
		currentFPS = frameCounter / accumulatingDT;
		accumulatingDT -= undateInterval;
		frameCounter = 0;
	}
	if(keyboard.isKeyPressed(VK_ESCAPE) || exit == true)
	{
		return true;
	}

	DoUserInput();
	UpdateDraws();
	UpdateView();
	UpdateLight();
	UpdateLogic();
	//Target
	globals.GetDraw(L"target").transform.translate = camera.ReturnTarget();
	//Reset trolley and items if player exit outside
	Range<int> ExitRangeX(-16,-7);
	Range<int> ExitRangeY(0,5);
	Range<int> ExitRangeZ(-107,-106);
	if(ExitRangeX.IsInRange(globals.GetDraw(L"player_body").GetGlobalPosition().x) && ExitRangeY.IsInRange(globals.GetDraw(L"player_body").GetGlobalPosition().y) && ExitRangeZ.IsInRange(globals.GetDraw(L"player_body").GetGlobalPosition().z))
	{
		player->ResetTrolley();
		item.ResetItems();
		trolley.Reset();
	}
	if(globals.GetDraw(L"player_body").GetGlobalPosition().y <= 7)
	{
		SWLv2[0].Reset();
		SWLv2[1].Reset();
		UpdateLv1 = true;
		UpdateLv2 = false;
	}
	else if(globals.GetDraw(L"player_body").GetGlobalPosition().y >= 10)
	{
		SILv1.Reset();
		RLv1[0].Reset();
		RLv1[1].Reset();
		SPLv1.Reset();
		UpdateLv1 = false;
		UpdateLv2 = true;
	}
	else
	{
		UpdateLv1 = true;
		UpdateLv2 = true;
	}
	if(player->pay == true)
	{
		player->ReleaseTrolley(globals.GetDraw(L"trolley5").GetGlobalPosition());
		RLv1[0].Update(dt);
		if(player->tempNoItemNeedToPay > 0)
		{
			player->paying = true;
		}
		else if(player->tempNoItemNeedToPay == 0)
		{
			player->pay = false;
			player->TakingTrolley(camera);
		}
		if(player->paying == true)
		{
			item.PayItem(globals.GetDraw(L"player_body").GetGlobalPosition(), &globals.GetDraw(L"cashiertable0"), dt);
		}
	}
	else
	{
		RLv1[0].Reset();
	}
	if(UpdateLv2 == true)
	{

		wizard.Update(dt);
		if(wizard.castingDone == true && isFrog == false)
		{
			int temp = player->tempNoItemNeedToPay;
			int temp2 = player->noOfItemInTrolley;
			player->ReleaseTrolley(globals.GetDraw(L"trolley5").GetGlobalPosition());
			delete player;
			player = new PlayerFrog;
			player->tempNoItemNeedToPay = temp;
			player->noOfItemInTrolley = temp2;
			player->DrawIsEqualTo(globals.GetDraw(L"player_arm_left"), globals.GetDraw(L"player_arm_right"), globals.GetDraw(L"player_body"), globals.GetDraw(L"main"), globals.GetDraw(L"trolley5"));
			globals.GetDraw(L"player_arm_left").SetMeshTo(NULL);
			globals.GetDraw(L"player_arm_right").SetMeshTo(NULL);
			isFrog = true;
			wizard.castingDone = false;
		}
		for(int i = 0; i < 2; ++i)
		{
			SWLv2[i].Update(dt);
		}
		for(int i = 0; i < 2; ++i)
		{
			int j = i + 1;
			while(true)
			{
				if(j == 2)
					j = 0;
				if(j == i)
					break;
				SWLv2[i].RotateChar(SWLv2[j]);
				j++;
			}
		}
	}
	if(isFrog == true)
	{
		globals.GetDraw(L"lollipop").SetMeshTo(globals.GetMesh(L"lollipop"));
	}
	else
	{
		globals.GetDraw(L"lollipop").SetMeshTo(NULL);
	}
	if(UpdateLv1 ==true)
	{
		SPLv1.Update(dt);
		SILv1.Update(dt);
		RLv1[0].Update(dt);
		RLv1[1].Update(dt);
	}

	if(SPLv1.currentState==2)
	{
		paying=true;
	}
	else
	{
		paying=false;
	}
	if(paying==true)
	{
		RLv1[1].Update(dt);
	}
	else
	{
		RLv1[1].Reset();
	}

	if(father.interacted == true)
	{
		globals.GetDraw(L"lost_child_body").SetMeshTo(globals.GetMesh(L"characterbody"));
		globals.GetDraw(L"lost_child_arm_left").SetMeshTo(globals.GetMesh(L"characterarm"));
		globals.GetDraw(L"lost_child_arm_right").SetMeshTo(globals.GetMesh(L"characterarm"));
		globals.GetDraw(L"lost_child_leg_left").SetMeshTo(globals.GetMesh(L"characterleg"));
		globals.GetDraw(L"lost_child_leg_right").SetMeshTo(globals.GetMesh(L"characterleg"));

		if(player->isHoldingChild == false)
		{
			lostchild.Update(dt);
		}
	}
	else
	{
		globals.GetDraw(L"lost_child_body").SetMeshTo(NULL);
		globals.GetDraw(L"lost_child_arm_left").SetMeshTo(NULL);
		globals.GetDraw(L"lost_child_arm_right").SetMeshTo(NULL);
		globals.GetDraw(L"lost_child_leg_left").SetMeshTo(NULL);
		globals.GetDraw(L"lost_child_leg_right").SetMeshTo(NULL);
	}
	return false;


}
/****************************************************************************/
/*!
\brief
updating Logic for lifts, doors and main menus
*/
/****************************************************************************/
void SceneMain::UpdateLogic()
{
	if(state==START)
	{
		gameQuit=false;
	}
	else if(state==INST)
	{
		gameQuit=false;
	}
	else if(state==CREDITS)
	{
		gameQuit=false;
	}
	else if(state==CHOOSETOEXIT)
	{
		gameQuit=false;
	}
	else if(state==MAINMENU)
		gameQuit=false;
	if(option==1)
	{
		state=START;
	}
	else if(option==2)
	{
		state=INST;
	}
	else if(option==3)
	{
		state=CREDITS;
	}
	else if(option==4)
	{
		state=CHOOSETOEXIT;
		state=START;
	}
	else if(option==2)
	{
		state=INST;
	}
	else if(option==3)
	{
		state=CREDITS;
	}
	else if(option==4)
	{
		state=CHOOSETOEXIT;
	}
	InteractDoor.InteractWithDoors(deltaTime,globals.GetDraw(L"player_body").GetGlobalPosition(), globals.GetDraw(L"shopper_payer_body").GetGlobalPosition() );
	InteractDoor.InteractWithTravelator(deltaTime,globals.GetDraw(L"player_body").transform.translate);
	InteractDoor.InteractWithLiftsOPEN(deltaTime,globals.GetDraw(L"player_body").transform.translate, OpenLiftDoorInput); 
	InteractDoor.InteractWithLiftsCLOSE(deltaTime,globals.GetDraw(L"player_body").transform.translate, OpenLiftDoorInput);
	InteractDoor.TrolleyTeleportWithoutPlayer(deltaTime,globals.GetDraw(L"player_body").transform.translate, globals.GetDraw(L"trolley5").transform.translate);

	if(camera.IsLookingAt(meetDidact,10,10))
	{
		snd.playSound("meet didact");
		meetDidact.y = 5000;
	}

	if (InteractDoor.GetLiftDoorInRange() == true)
	{
		if(keyboard.isKeyPressed('E'))
		{

			if(OpenLiftDoorInput == false)
			{
				snd.playSound("elevator",true);
				InteractDoor.TeleportWithLifts(deltaTime,globals.GetDraw(L"player_body").transform.translate,globals.GetDraw(L"trolley5").transform.translate, player->isHoldingTrolley);
			}

			OpenLiftDoorInput = true;
		}

		else if(keyboard.isKeyPressed('Q'))
		{	
			OpenLiftDoorInput = false;
		}
	}

	else
	{
		OpenLiftDoorInput = false;
	}
	const double rotationspeed = 300;
	globals.GetDraw(L"ring").transform.rotate.y += rotationspeed * deltaTime;
}
/****************************************************************************/
/*!
\brief
updating view in frog and player perspective, camera lock on.
*/
/****************************************************************************/
void SceneMain::UpdateView()
{
	//the skybox is moved according to the camera position
	globals.GetDraw(L"skybox").transform.translate = Vector3(0,0,0) + camera.ReturnPosition();

	if(isFrog == false)
	{
		camera.Translate(globals.GetDraw(L"player_body").transform.translate - camera.ReturnPosition() + Vector3(0, 2.5, 0));
	}
	else
	{
		camera.Translate(globals.GetDraw(L"player_body").transform.translate - camera.ReturnPosition() + Vector3(0, -1, 0));
	}

	float player_rotationY = camera.GetRotation().y - globals.GetDraw(L"player_body").transform.rotate.y;
	float player_current_frame_rotationY = player_rotationY / 1.5;
	globals.GetDraw(L"player_body").transform.rotate.y += player_current_frame_rotationY;
	gfx.SetViewAt(camera);
}
/****************************************************************************/
/*!
\brief
updating lights
*/
/****************************************************************************/
void SceneMain::UpdateLight()
{
	gfx.UpdateLights();
}
/****************************************************************************/
/*!
\brief
updating draws
*/
/****************************************************************************/
void SceneMain::UpdateDraws()
{
	if(InteractDoor.GetTravelatorInRange() == false)
	{
		//where forces are applied
		for(std::map<std::wstring, CollisionBody*>::iterator body = globals.GetCollisionBodiesList().begin(), end = globals.GetCollisionBodiesList().end(); body != end; ++body)
		{
			//an object has 0 mass if it is infinitely heavy and forces will barely have any effect on it including gravity. This is totally how physics work
			body->second->UpdateVelocity(deltaTime);
			body->second->UpdateForcesTo(deltaTime);
		}
	}
	//where we do collision
	collisionSystem.CheckThisCollision(&globals.GetCollisionBody(L"ground"), &globals.GetCollisionBody(L"player"), deltaTime);
	collisionSystem.CheckThisCollision(&globals.GetCollisionBody(L"building"), &globals.GetCollisionBody(L"player"), deltaTime);
	collisionSystem.ResolveAllCollisionsAccordingTo(deltaTime);

	//draws are finally updated after processing
	if(InteractDoor.GetTravelatorInRange() == false)
	{
		for(std::map<std::wstring, CollisionBody*>::iterator body = globals.GetCollisionBodiesList().begin(), end = globals.GetCollisionBodiesList().end(); body != end; ++body)
		{
			body->second->UpdateTo(deltaTime);
		}
	}
}
/****************************************************************************/
/*!
\brief
rendering of text, sounds and menu options
*/
/****************************************************************************/
void SceneMain::Render()
{
	//clear depth and color buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnableVertexAttribArray(0); // 1st attribute buffer :vertices
	glEnableVertexAttribArray(1); // 2nd attribute buffer : colors
	glEnableVertexAttribArray(2); // 3rd attribute : normals
	glEnableVertexAttribArray(3); // 4th attribute : UV coordinates

	if(state==MAINMENU)
	{
		MS BG;
		BG.Translate(0,0,-0.01);
		BG.Scale(100,100,1);
		gfx.RenderMeshOnScreen(globals.GetDraw(L"BG"),BG.Top(), ORIENTATION_CENTRE);
		MS Quad1,Quad2,Quad3,Quad4;
		Quad1.Scale(20,7,1);
		Quad2.Scale(20,7,1);
		Quad3.Scale(20,7,1);
		Quad4.Scale(20,7,1);
		Quad1.Translate(0,50,0);
		Quad2.Translate(0,30,0);
		Quad3.Translate(0,10,0);
		Quad4.Translate(0,-10,0);
		gfx.RenderMeshOnScreen(globals.GetDraw(L"Quad1"),Quad1.Top(), ORIENTATION_CENTRE);
		gfx.RenderMeshOnScreen(globals.GetDraw(L"Quad2"),Quad2.Top(), ORIENTATION_CENTRE);
		gfx.RenderMeshOnScreen(globals.GetDraw(L"Quad3"),Quad3.Top(), ORIENTATION_CENTRE);
		gfx.RenderMeshOnScreen(globals.GetDraw(L"Quad4"),Quad4.Top(), ORIENTATION_CENTRE);
	}
	else if(state==START)
	{
		if(drawVoxels)
		{
			Material material(L"meep", Component(1,1,1), Component(1,1,1), Component(1,1,1),20,globals.GetTexture(L"building"));
			drawOrder draw_cube(L"cube", globals.GetMesh(L"cube"), &material, NULL, true);
			for(std::map<std::wstring, CollisionBody*>::iterator body = globals.GetCollisionBodiesList().begin(), end = globals.GetCollisionBodiesList().end(); body != end; ++body)
			{
				Mtx44 matrix(body->second->GetMatrix());
				for(std::vector<Voxel*>::iterator voxel = body->second->GetVoxelVector().begin(), end = body->second->GetVoxelVector().end(); voxel != end; ++voxel)
				{
					Mtx44 translate;
					translate.SetToTranslation(matrix * (*voxel)->GetPosition());
					gfx.RenderMesh(draw_cube, translate);
				}
			}
		}
		else
		{
			globals.GetDraw(L"main").Execute(gfx);
		}
	}
	else if(state==INST)
	{
		MS INST;
		INST.Translate(0,0,-0.01);
		INST.Scale(2,2,1);
		gfx.RenderMeshOnScreen(globals.GetDraw(L"instructions"),INST.Top(), ORIENTATION_CENTRE);
	}
	else if(state==CREDITS)
	{
		MS CREDITS;
		CREDITS.Translate(0,0,-0.01);
		CREDITS.Scale(2,2,1);
		gfx.RenderMeshOnScreen(globals.GetDraw(L"incredits"),CREDITS.Top(), ORIENTATION_CENTRE);
	}
	else if(state==CHOOSETOEXIT)
	{
		MS EXIT;
		EXIT.Translate(0,0,-0.01);
		EXIT.Scale(2,2,1);
		gfx.RenderMeshOnScreen(globals.GetDraw(L"inexit"),EXIT.Top(), ORIENTATION_CENTRE);
	}

	if(camera.IsLookingAt(globals.GetDraw(L"ring").GetGlobalPosition(),10,5))
	{
		gfx.RenderTextOnScreen("Press T to release didact!",Color(1,1,1),55,60,500);
	}

	Range<int>x(12,18);
	Range<int>y(0.1,5);
	Range<int>z(-104,-92);
	Vector3 Lift(globals.GetDraw(L"player_body").GetGlobalPosition());
	if(x.IsInRange(Lift.x)&&y.IsInRange(Lift.y)&&z.IsInRange(Lift.z))
	{
		gfx.RenderTextOnScreen("1.Press Q to close door!",Color(1,1,1),55,60,700);
		gfx.RenderTextOnScreen("2.Press E to move to level 2",Color(1,1,1),55,60,300);
	}

	Range<int>a(12,18);
	Range<int>b(9,14);
	Range<int>c(-104,-92);
	if(a.IsInRange(Lift.x)&&b.IsInRange(Lift.y)&&c.IsInRange(Lift.z))
	{
		gfx.RenderTextOnScreen("1.Press Q to close door!",Color(1,1,1),55,60,700);
		gfx.RenderTextOnScreen("2.Press E to move to level 1!",Color(1,1,1),55,60,300);
	}

	Range<int>d(14,18);
	Range<int>e(0.1,5);
	Range<int>f(-88,-84);
	if(d.IsInRange(Lift.x)&&e.IsInRange(Lift.y)&&f.IsInRange(Lift.z))
	{
		{
			gfx.RenderTextOnScreen("Press E to Open Lift door!",Color(1,1,1),55,60,500);
		}
	}
	Range<int>g(12,18);
	Range<int>h(9,14);
	Range<int>i(-88,-84);
	if(g.IsInRange(Lift.x)&&h.IsInRange(Lift.y)&&i.IsInRange(Lift.z))
	{
		{
			gfx.RenderTextOnScreen("Press E to Open Lift door!",Color(1,1,1),55,60,500);
		}
	}
	//wizard
	if(camera.IsLookingAt(globals.GetDraw(L"wizard_body").GetGlobalPosition(), 20, 10) && wizard.casting==false && isFrog == false)
	{
		gfx.RenderTextOnScreen("Press E to interact with wizard.",Color(1,1,1),55,60,500);
	}
	if(wizard.casting==true)
	{
		gfx.RenderTextOnScreen("MUHALABAJATA",Color(1,1,1),50,50,300);
	}
	if(camera.IsLookingAt(globals.GetDraw(L"wizard_body").GetGlobalPosition(), 20, 10) && isFrog==true)
	{
		gfx.RenderTextOnScreen("Opps, you had been turned into a",Color(1,1,1),55,60,500);
		gfx.RenderTextOnScreen("frog. Find an item on the ground",Color(1,1,1),55,60,450);
		gfx.RenderTextOnScreen("to restore back to human",Color(1,1,1),55,60,400);
	}
	//lollipop
	if(camera.IsLookingAt(globals.GetDraw(L"lollipop").GetGlobalPosition(), 90, 5) && isFrog==true)
	{
		gfx.RenderTextOnScreen("Press F to eat and turn back to human",Color(1,1,1),55,60,500);
	}
	//Father
	if(camera.IsLookingAt(globals.GetDraw(L"father_body").GetGlobalPosition(), 20, 10) && isFrog==false && father.interacted == false)
	{
		gfx.RenderTextOnScreen("Press E to interact with him",Color(1,1,1),55,60,500);
	}
	if(camera.IsLookingAt(globals.GetDraw(L"father_body").GetGlobalPosition(), 20, 10) && isFrog==false && father.interacted == true && player->isHoldingChild == false)
	{
		gfx.RenderTextOnScreen("I had lost my son!",Color(1,1,1),55,60,500);
		gfx.RenderTextOnScreen("Please help me find him.",Color(1,1,1),55,60,300);
	}
	else if (camera.IsLookingAt(globals.GetDraw(L"father_body").GetGlobalPosition(), 20, 10) && isFrog==false && father.interacted == true && player->isHoldingChild == true)
	{
		gfx.RenderTextOnScreen("OMG my son! Thankyou :')",Color(1,1,1),55,60,500);
	}
	//trolley takeable
	if(camera.IsLookingAt(globals.GetDraw(L"trolley5").GetGlobalPosition(), 20, 5))
	{
		if(player->isHoldingTrolley==false && player->isHoldingItem == false && player->isHoldingChild == false)
			gfx.RenderTextOnScreen("Press E to take trolley",Color(1,1,1),55,60,500);
		else if(player->isHoldingItem==true)
			gfx.RenderTextOnScreen("Press F to put item",Color(1,1,1),55,60,500);
	}
	//trolley untakeable
	if(player->isHoldingTrolley==false)
	{
		if(camera.IsLookingAt(globals.GetDraw(L"trolley0").GetGlobalPosition(), 20, 2.5))
			gfx.RenderTextOnScreen("*struck*",Color(1,1,1),25,250,300);
		if(camera.IsLookingAt(globals.GetDraw(L"trolley1").GetGlobalPosition(), 20, 2.5))
			gfx.RenderTextOnScreen("*struck*",Color(1,1,1),25,250,300);
		if(camera.IsLookingAt(globals.GetDraw(L"trolley2").GetGlobalPosition(), 20, 2.5))
			gfx.RenderTextOnScreen("*struck*",Color(1,1,1),25,250,300);
		if(camera.IsLookingAt(globals.GetDraw(L"trolley3").GetGlobalPosition(), 20, 2.5))
			gfx.RenderTextOnScreen("*struck*",Color(1,1,1),25,250,300);
		if(camera.IsLookingAt(globals.GetDraw(L"trolley4").GetGlobalPosition(), 20, 2.5))
			gfx.RenderTextOnScreen("*struck*",Color(1,1,1),25,250,300);
	}
	//robot
	if(camera.IsLookingAt(globals.GetDraw(L"robotbody0").GetGlobalPosition(), 20, 10) || camera.IsLookingAt(globals.GetDraw(L"robotbody1").GetGlobalPosition(), 20, 10))
	{
		snd.playSound("robot",true);
		gfx.RenderTextOnScreen("*Nice Robot*",Color(1,1,1),55,60,500);
	}
	//shopper npc
	if(camera.IsLookingAt(globals.GetDraw(L"shopper_wanderer_body0").GetGlobalPosition(), 20, 10) || camera.IsLookingAt(globals.GetDraw(L"shopper_wanderer_body1").GetGlobalPosition(), 20, 10) || camera.IsLookingAt(globals.GetDraw(L"shopper_payer_body").GetGlobalPosition(), 20, 10) || camera.IsLookingAt(globals.GetDraw(L"shopper_idler_body").GetGlobalPosition(), 20, 10))
	{
		gfx.RenderTextOnScreen("Hello!",Color(1,1,1),55,60,500);
	}

	//item
	for(int i = 0; i < 1246; ++i)
	{

		if(i < 360)// CAN_1  360
		{
			wchar_t Namebuffer[64];
			wsprintf(Namebuffer,L"can1_cabinet1_%d",i);
			if(camera.IsLookingAt(globals.GetDraw(Namebuffer).GetGlobalPosition(),7.5, 5) && item.taken[i] == false)
			{
				gfx.RenderTextOnScreen("Press F to pick/put items",Color(1,1,1),60,60,500);
			}
		}

		else if(i < 420)// CAN_2 60
		{
			wchar_t Namebuffer[64];
			wsprintf(Namebuffer,L"can2_cabinet1_%d",i-360);
			if(camera.IsLookingAt(globals.GetDraw(Namebuffer).GetGlobalPosition(), 7.5, 5)&& item.taken[i] == false)
			{
				gfx.RenderTextOnScreen("Press F to pick/put items",Color(1,1,1),60,60,500);
			}
		}
		else if(i < 670)// CAN_3 250
		{
			wchar_t Namebuffer[64];
			wsprintf(Namebuffer,L"can3_cabinet1_%d",i-420);
			if(camera.IsLookingAt(globals.GetDraw(Namebuffer).GetGlobalPosition(), 7.5, 5)&& item.taken[i] == false)
			{
				gfx.RenderTextOnScreen("Press F to pick/put items",Color(1,1,1),60,60,500);
			}
		}
		else if(i < 706)// Packet1 36
		{
			wchar_t Namebuffer[64];
			wsprintf(Namebuffer,L"packet1_cabinet2_column1_%d",i-670);
			if(camera.IsLookingAt(globals.GetDraw(Namebuffer).GetGlobalPosition(), 7.5, 5)&& item.taken[i] == false)
			{
				gfx.RenderTextOnScreen("Press F to pick/put items",Color(1,1,1),60,60,500);
			}
		}
		else if(i < 742)// Packet2 36
		{
			wchar_t Namebuffer[64];
			wsprintf(Namebuffer,L"packet2_cabinet2_column2_%d",i-706);
			if(camera.IsLookingAt(globals.GetDraw(Namebuffer).GetGlobalPosition(), 7.5, 5)&& item.taken[i] == false)
			{
				gfx.RenderTextOnScreen("Press F to pick/put items",Color(1,1,1),60,60,500);
			}
		}
		else if(i < 934)// Packet3 192
		{
			wchar_t Namebuffer[64];
			wsprintf(Namebuffer,L"packet3_cabinet2_column1_%d",i-742);
			if(camera.IsLookingAt(globals.GetDraw(Namebuffer).GetGlobalPosition(), 7.5, 5)&& item.taken[i] == false)
			{
				gfx.RenderTextOnScreen("Press F to pick/put items",Color(1,1,1),60,60,500);
			}
		}
		else if(i < 1114)// Can_4 180
		{
			wchar_t Namebuffer[64];
			wsprintf(Namebuffer,L"can4_cabinet2_column2_%d",i-934);
			if(camera.IsLookingAt(globals.GetDraw(Namebuffer).GetGlobalPosition(), 7.5, 5)&& item.taken[i] == false)
			{
				gfx.RenderTextOnScreen("Press F to pick/put items",Color(1,1,1),60,60,500);
			}
		}
		else if(i < 1150)// Cereal1 36
		{
			wchar_t Namebuffer[64];
			wsprintf(Namebuffer,L"cereal1_cabinet3_%d",i-1114);
			if(camera.IsLookingAt(globals.GetDraw(Namebuffer).GetGlobalPosition(), 7.5, 5)&& item.taken[i] == false)
			{
				gfx.RenderTextOnScreen("Press F to pick/put items",Color(1,1,1),60,60,500);
			}

		}
		else if(i < 1174)// Cereal2 24
		{
			wchar_t Namebuffer[64];
			wsprintf(Namebuffer,L"cereal2_cabinet3_%d",i-1150);
			if(camera.IsLookingAt(globals.GetDraw(Namebuffer).GetGlobalPosition(), 7.5, 5)&& item.taken[i] == false)
			{
				gfx.RenderTextOnScreen("Press F to pick/put items",Color(1,1,1),60,60,500);
			}
		}
		else if(i < 1210)// Cereal3 36
		{
			wchar_t Namebuffer[64];
			wsprintf(Namebuffer,L"cereal3_cabinet3_%d",i-1174);
			if(camera.IsLookingAt(globals.GetDraw(Namebuffer).GetGlobalPosition(), 20, 5)&& item.taken[i] == false)
			{
				gfx.RenderTextOnScreen("Press F to pick/put items",Color(1,1,1),60,60,500);
			}
		}
		else if(i < 1246)// Cereal4 36
		{
			wchar_t Namebuffer[64];
			wsprintf(Namebuffer,L"cereal4_cabinet3_%d",i-1210);
			if(camera.IsLookingAt(globals.GetDraw(Namebuffer).GetGlobalPosition(), 7.5, 5)&& item.taken[i] == false)
			{
				gfx.RenderTextOnScreen("Press F to pick/put items",Color(1,1,1),60,60,500);
			}
		}
	}

	char buffer1[126];
	char buffer2[126];
	Vector3 position = globals.GetDraw(L"player_body").GetGlobalPosition();
	sprintf(buffer1,"position:%.3f, %.3f, %.3f",position.x, position.y, position.z);
	gfx.RenderTextOnScreen(buffer1,Color(0,1,0),20,1,1);
	currentFPS = 1 / deltaTime;
	sprintf(buffer2,"FPS:%.3f", currentFPS);
	gfx.RenderTextOnScreen(buffer2,Color(0,1,0),20,1,40, ORIENTATION_TOP);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(3);
}
/****************************************************************************/
/*!
\brief
empty exit
*/
/****************************************************************************/
void SceneMain::Exit()
{
	snd.stopSound();
}
/****************************************************************************/
/*!
\brief
All user inputs
*/
/****************************************************************************/
void SceneMain::DoUserInput()
{
	double mouseX;
	double mouseY;
	mouse.Update(mouseX, mouseY);
	const int CAMERA_SPEED = 2.5;
	camera.Rotate(0, -mouseX, -mouseY);
	playerAcceleration.SetZero();
	double movingSpeed = 30;
	if(keyboard.isKeyPressed('Z'))
	{
		glEnable(GL_CULL_FACE);
	}
	if(keyboard.isKeyPressed('X'))
	{
		glDisable(GL_CULL_FACE);
	}
	if(keyboard.isKeyPressed('C'))
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
	if(keyboard.isKeyPressed('V'))
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	if(keyboard.isKeyPressed('5'))
	{
		drawVoxels = !drawVoxels;
	}
	if(state == START && player->pay == false && wizard.casting == false)
	{
		if(keyboard.isKeyPressed('N'))
		{
			state=MAINMENU;
		}
		if(isFrog == false)
		{
			if(keyboard.isKeyPressed('F'))
			{
				if(player->isHoldingTrolley == false && player->isHoldingItem == false && player->isHoldingChild == false) // Take item
				{
					item.InteractWithItem(camera);
				}
				else if(player->isHoldingItem == true) // put item
				{
					item.PutItem(camera);
				}
				if(player->isHoldingChild == false && father.interacted == true && player->isHoldingTrolley == false)
				{
					lostchild.PickUpChild(camera);
				}
			}
			if(keyboard.isKeyPressed('G') && paying == false && player->isHoldingTrolley == true && player->isHoldingItem == false && player->noOfItemInTrolley > 0 && player->pay == false)
			{
				//check range
				Range<int> PayingRangeX(-4,-2);
				Range<int> PayingRangeY(0,4);
				Range<int> PayingRangeZ(-85, -78);
				if(PayingRangeX.IsInRange(globals.GetDraw(L"player_body").GetGlobalPosition().x) && PayingRangeY.IsInRange(globals.GetDraw(L"player_body").GetGlobalPosition().y) && PayingRangeZ.IsInRange(globals.GetDraw(L"player_body").GetGlobalPosition().z)) // if in range
				{
					player->pay = true;
				}
			}
			if(keyboard.isKeyPressed('T') && camera.IsLookingAt(globals.GetDraw(L"ring").GetGlobalPosition(),10,5))
			{
				globals.GetDraw(L"didact").transform.translate.Set(0,342,-663);
				globals.GetDraw(L"didact").transform.scale.Set(10420,10420,10420);
				globals.GetDraw(L"ring").transform.translate.Set(0,342,-663);
				snd.playSound("didact freed");
			}
			if(keyboard.isKeyPressed('E') && player->isHoldingItem == false)
			{
				player->TakingTrolley(camera);
				if(wizard.checkInteract(camera) == true)
				{
					wizard.casting = true;
				}
				if(father.checkInteract(camera) == true)
				{
					father.interacted = true;
				}
				if(camera.IsLookingAt(globals.GetDraw(L"father_body").GetGlobalPosition(), 20, 10) && isFrog==false && father.interacted == true && player->isHoldingChild == true)
				{
					lostchild.Reset();
					father.interacted = false;
				}

			}
			if(keyboard.isKeyPressed('R'))
			{
				player->ReleaseTrolley(globals.GetDraw(L"trolley5").GetGlobalPosition());
			}
		}
		else
		{
			if(keyboard.isKeyPressed('F'))
			{
				if(item.EatLollipop(camera, globals.GetDraw(L"lollipop").GetGlobalPosition()))
				{
					int temp = player->tempNoItemNeedToPay;
					int temp2 = player->noOfItemInTrolley;
					delete player;
					player = new PlayerHuman;
					player->tempNoItemNeedToPay = temp;
					player->noOfItemInTrolley = temp2;
					player->DrawIsEqualTo(globals.GetDraw(L"player_arm_left"), globals.GetDraw(L"player_arm_right"), globals.GetDraw(L"player_body"), globals.GetDraw(L"main"), globals.GetDraw(L"trolley5"));
					globals.GetDraw(L"player_arm_left").SetMeshTo(globals.GetMesh(L"characterarm"));
					globals.GetDraw(L"player_arm_right").SetMeshTo(globals.GetMesh(L"characterarm"));
					isFrog = false;
				}
			}
		}
		if (keyboard.isKeyPressed('I'))
		{
			//ResetDidact
			globals.GetDraw(L"didact").transform.translate.Set(17,15,-12);
			meetDidact.Set(17,15,-12);
			globals.GetDraw(L"didact").transform.scale.Set(10,10,10);

			//Reset Ring
			globals.AddDraw(drawOrder(L"ring", globals.GetMesh(L"ring"), &globals.GetMaterial(L"ring"), &globals.GetDraw(L"main"), true));
			globals.GetDraw(L"ring").transform.translate.Set(17,15,-12);
			globals.GetDraw(L"ring").transform.scale.Set(10,10,10);

			int temp = player->tempNoItemNeedToPay;
			int temp2 = player->noOfItemInTrolley;
			delete player;
			player = new PlayerHuman;
			player->tempNoItemNeedToPay = temp;
			player->noOfItemInTrolley = temp2;
			player->DrawIsEqualTo(globals.GetDraw(L"player_arm_left"), globals.GetDraw(L"player_arm_right"), globals.GetDraw(L"player_body"), globals.GetDraw(L"main"), globals.GetDraw(L"trolley5"));
			globals.GetDraw(L"player_arm_left").SetMeshTo(globals.GetMesh(L"characterarm"));
			globals.GetDraw(L"player_arm_right").SetMeshTo(globals.GetMesh(L"characterarm"));
			isFrog = false;

			father.interacted = false;
		}
		if (keyboard.isKeyHold(VK_SHIFT))
		{
			movingSpeed *= 3 ;
		}

		if ( InteractDoor.GetTravelatorInRange() == false )
		{
			if(keyboard.isKeyHold('W') || keyboard.isKeyHold('S') || keyboard.isKeyHold('A') || keyboard.isKeyHold('D'))
			{
				if (keyboard.isKeyHold('W'))
				{
					playerAcceleration += player->MoveForward(camera, movingSpeed);
				}
				if (keyboard.isKeyHold('S'))
				{
					playerAcceleration += player->MoveBackward(camera, movingSpeed);
				}
				if (keyboard.isKeyHold('A'))
				{
					playerAcceleration += player->MoveLeft(camera, movingSpeed);
				}
				if (keyboard.isKeyHold('D'))
				{
					playerAcceleration += player->MoveRight(camera, movingSpeed);
				}
				if(isFrog == true && isJumping == false && isFalling == false)
				{
					isJumping = true;
				}
			}
			//Jump
			if (keyboard.isKeyHold(VK_SPACE) && isJumping == false && isFalling == false && isFrog == false)
			{
				isJumping = true;
			}
			if (keyboard.isKeyHold('O'))
			{	
				Vector3 tempVector;
				tempVector.Set(0, 50, 0);
				playerAcceleration += tempVector;
			}
			if (keyboard.isKeyHold('P'))
			{
				Vector3 tempVector;
				tempVector.Set(0, -50, 0);
				playerAcceleration += tempVector;
			}
		}
		if (keyboard.isKeyHold(VK_UP))
		{
			camera.Move(10.0f * deltaTime * CAMERA_SPEED, 0.0f, 0.0f);
		}
		if (keyboard.isKeyHold(VK_LEFT))
		{
			camera.Move(0.0f, 0.0f, -10.0f * deltaTime * CAMERA_SPEED);
		}
		if (keyboard.isKeyHold(VK_DOWN))
		{
			camera.Move(-10.0f * deltaTime * CAMERA_SPEED, 0.0f, 0.0f);
		}
		if (keyboard.isKeyHold(VK_RIGHT))
		{
			camera.Move(0.0f, 0.0f, 10.0f * deltaTime * CAMERA_SPEED);
		}
		if (keyboard.isKeyHold(VK_SPACE))
		{
			camera.Move(0,10 * deltaTime * CAMERA_SPEED,0);
		}
		if (keyboard.isKeyHold(VK_CONTROL))
		{
			camera.Move(0,-10 * deltaTime * CAMERA_SPEED,0);
		}

		//Jump
		if(isJumping == true)
		{
			if(jumpedHeight < 700 && isFalling == false)
			{
				Vector3 tempVector;
				tempVector.Set(0, 100, 0);
				playerAcceleration += tempVector;
				jumpedHeight += 100 - 50;
			}
			else
			{
				isJumping = false;
				isFalling = true;
				jumpedHeight = 700;
			}
		}
		if(isFalling == true)
		{
			if(jumpedHeight > 0)
			{
				jumpedHeight -= 20;
			}
			else
			{
				isFalling = false;
				jumpedHeight = 0;
			}
		}
		playerAcceleration = playerAcceleration;
		Force playerForce;
		playerForce.SetLifespanTo(0.0001);
		playerForce.SetVector(playerAcceleration);
		globals.GetCollisionBody(L"player").AddForce(playerForce);
	}
	else
	{
		if(keyboard.isKeyPressed('1'))
		{
			//snd.stopSound();
			snd.playSound("robot2",true);
			state=START;
		}
		if(keyboard.isKeyPressed('2'))
		{
			state=INST;	
		}
		if(keyboard.isKeyPressed('3'))
		{
			state=CREDITS;
		}
		if(keyboard.isKeyPressed('4'))
		{
			state=CHOOSETOEXIT;
		}
		if(keyboard.isKeyPressed('N'))
		{
			state=MAINMENU;
		}
		if(state==CHOOSETOEXIT && keyboard.isKeyPressed('Y'))
		{
			exit = true;
		}
	}
}