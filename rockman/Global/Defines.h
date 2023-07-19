#pragma once

#define _USE_MATH_DEFINES

enum class Languages
{
	KOR,
	ENG,
	JP,
	Count,
};

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

enum class ResourceTypes
{
	Texture,
	Font,
	SoundBuffer,
	AnimationClip,
};

enum class SceneId
{
	None = -1,
	Stage1_1,
	Count,
};

enum class Collision
{
	None,
	Right = 1,
	Left,
	Top,
	Bottom,
};