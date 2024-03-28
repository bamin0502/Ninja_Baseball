#pragma once
#include "Scene.h"

class Bat;
class Enemy2;
class Tilemap;
class UiHUD;
class SpriteGo;
class TextGo;
class InputField;
class BaseBall;
class Stage1;
class Player;
class Player2;
class Enemy;
class WindyPlane;
class Item;
class PickupItem;
class Shutter;

class SceneDev1 : public Scene
{
public:
	Player* player = nullptr;

	Player2* player2 = nullptr;
	//Enemy* enemy = nullptr;
	//Enemy2* enemy2 = nullptr;
	BaseBall* baseBall = nullptr;
	Bat* bat = nullptr;
	Enemy* enemy = nullptr;
	Shutter* shutter = nullptr;

	bool cameraShakeOn = false;
	float cameraShakeTime = 1.f;

	bool isFighting = false;

	sf::Vector2f worldViewCenter = {0.f,0.f};

	sf::FloatRect stageRect;

	int currStage = 0;

	Stage1* stage = nullptr;

	bool enterToBossFloor = false;

	//내부 스테이지 카메라 중심
	float camCenter1;
	float camCenter2;
	float camCenter3;
	float camCenter4; //노말
	float camCenter5; //부서진1
	float camCenter6; //부서진2
	float camCenter7; //비행기 스테이지
	float camCenter8; //비행기 보스

protected :
	SceneDev1(const SceneDev1&)				= delete;
	SceneDev1(SceneDev1&&)					= delete;
	SceneDev1& operator=(const SceneDev1&)	= delete;
	SceneDev1& operator=(SceneDev1&&)		= delete;	
	
	sf::RectangleShape cameraRect;

	float xMax = 0.f;

	WindyPlane* windyPlane = nullptr;
	PickupItem* goldBatItem = nullptr;
	UiHUD* hud = nullptr;
	sf::Vector2f windowSize;


private:
	struct MonsterInfo
	{
		sf::FloatRect damageBox;
		std::shared_ptr<Enemy> monster;
	};
	std::vector<MonsterInfo> monsterInfos;
	std::vector<Enemy*> enemies;

	int sharedNormalAttack=0;
public:
	std::vector<Enemy*> GetEnemyList() { return enemies; }

	SceneDev1(SceneIDs id);
	~SceneDev1() override = default;
	sf::Vector2f ClampByTileMap(const sf::Vector2f point);

	void Init() override;
	void Release() override;
	virtual void Reset();
	void Enter() override;
	void Exit() override;
	void Update(float dt) override;
	void UpdateAwake(float dt);
	void UpdateGame(float dt);
	void UpdateGameover(float dt);
	void UpdatePause(float dt);
	void Draw(sf::RenderWindow& window);

	GameStatus GetStatus() const { return this->status; }
	void SetStatus(GameStatus newStatus);
	void SpawnEnemy(const std::string& type,const sf::Vector2f& position);
	void CameraShake(float dt);
	void SetNormalAttack(int value){ sharedNormalAttack = value; }
	int GetNormalAttack() const { return sharedNormalAttack; }
	void FightOn();
	void ClearStage();
	void MoveToBoss();
};