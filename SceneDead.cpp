#include "DxLib.h"
#include "game.h"
#include "SceneDead.h"

namespace {
	constexpr int fontSize = 128;
}

SceneDead::SceneDead() {
	m_fadeBright = 0;
	m_fadeSpeed = 0;
}

SceneDead::~SceneDead() {

}

void SceneDead::init() {
	m_fadeBright = 0;
	m_fadeSpeed = 8;
}

void SceneDead::end() {
	SetDrawBright(255, 255, 255);
}

bool SceneDead::update() {

	// キー入力処理
	int padState = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	if (padState & PAD_INPUT_1) {
		return true;
	}
	return false;
}

void SceneDead::draw() {
	SetFontSize(fontSize);
	DrawString(Game::kScreenWidth / 2 - 250, Game::kScreenHeight / 6, "YOU DIED", GetColor(255, 0, 0));
	SetFontSize(60);
	DrawString(Game::kScreenWidth / 2 - 125, Game::kScreenHeight / 3 + 50, "Xで再挑戦", GetColor(255, 255, 255));
	DrawString(Game::kScreenWidth / 2 - 125, Game::kScreenHeight / 3 + 120, "Bで終了", GetColor(255, 255, 255));
}