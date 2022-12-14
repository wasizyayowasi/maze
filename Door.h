#pragma once

#include"Vec2.h"
#include "Player.h"

class Door {
public:
	Door();
	virtual ~Door();

	//グラフィックデータの設定
	void setHandle(int handle) { m_handle = handle; }

	void init();

	//
	void draw();

	//ドアの死亡判定用
	void setPadlockDead(bool isPadlookDead) { m_isPadlockDead = isPadlookDead; }
	void setSound(int sound) { m_sound = sound; }

	bool isCol(Player& player);

	void setDead(bool isDead) ;

	//データの取得
	Vec2 getPos()const { return m_pos; }					//左上座標
	Vec2 getBottomRight()const { return m_pos + m_size; }	//右下座標

private:
	//ハンドル
	int m_handle;

	int m_isDead;

	int m_isPadlockDead;

	int m_sound;

	int count;

	Vec2 m_pos;

	Vec2 m_size;
};