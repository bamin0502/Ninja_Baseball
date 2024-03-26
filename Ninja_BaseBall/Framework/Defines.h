#pragma once

enum class Origins
{
	TL,
	TC,
	TR,
	ML,
	MC,
	MR,
	BL,
	BC,
	BR,
	CUSTOM,
};

enum class Sides
{
	NONE = -1,
	LEFT,
	RIGHT,
	COUNT
};

enum class PlayerState
{
	NOTSET = -1,
	ALIVE,
	DEAD
};

enum class GameStatus
{
	Awake,
	Game,
	GameOver,
	Pause,
};

enum Layers
{
	None = 0,
	World = 1,
	Ui = 2,
	EveryThing = 0xFFFFFFFF
};

enum class Languages
{
	Korean,
	English,
};

enum class BossType
{
	WINDYPLANE,
};

enum class BossPartsStatus 
{
	Wing, 
	NoWing, 
	NoProp, 
	OneArm, 
	NoArm, 
	UNDEFINED
};

enum class EnemyAttackType
{
	Normal,
	ThrowBack,
	Homerun
};