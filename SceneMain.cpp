#include "DxLib.h"
#include "SceneMain.h"
#include "Map.h"
#include "Key.h"
#include "Door.h"

namespace {

	//グラフィックファイル名
	const char* const kPlayerGraphicFilename = "data/char.png";
	const char* const kEnemyGraphicFilename = "data/enemy.png";

}

SceneMain::SceneMain() {
	m_hMap = -1;
	m_hBackgroundHnadle = -1;
	m_hKey = -1;
	m_hDoor = -1;
	m_hPlayerDead = -1;
	m_hBotan = -1;
	m_sKeyHandle = -1;
	m_sPushBotan = -1;
	m_sOpenDoor = -1;
	playerDead = 0;
	playerDeadTime = 0;

	for (auto& playerHandle : m_hPlayerGraphic) {
		playerHandle = -1;
	}
	for (auto& EnemyHandle : m_hEnemyGraphic) {
		EnemyHandle = -1;
	}

}

SceneMain::~SceneMain() {

}

// 初期化
void SceneMain::init() {
	m_hMap = LoadGraph("data/labyrinth.png");
	m_hKey = LoadGraph("data/kagi.png");
	m_hDoor = LoadGraph("data/door.png");
	m_hPlayerDead = LoadGraph("data/tamasii.png");
	m_hBotan = LoadGraph("data/botan.png");
	m_hBackgroundHnadle = LoadGraph("data/haikei1.png");
	m_sKeyHandle = LoadSoundMem("soundEffect/coin07.mp3");
	m_sPushBotan = LoadSoundMem("soundEffect/switch1.mp3");
	m_sOpenDoor = LoadSoundMem("soundEffect/door.mp3");
	m_sDead = LoadSoundMem("soundEffect/dead.mp3");

	m_map.setHandle(m_hMap);
	m_map.setBackgroundHandle(m_hBackgroundHnadle);
	m_key.setHandle(m_hKey);
	m_door.setHandle(m_hDoor);
	m_player.setPlayerDeadHandle(m_hPlayerDead);
	m_botan.setHandle(m_hBotan);
	m_key.setSound(m_sKeyHandle);
	m_botan.setSound(m_sPushBotan);
	m_door.setSound(m_sOpenDoor);
	m_player.setSound(m_sDead);

	LoadDivGraph(kPlayerGraphicFilename, Player::kGraphicDivNum, Player::kGraphicDivX, Player::kGraphicDivY, Player::kGraphicSizeX, Player::kGraphicSizeY, m_hPlayerGraphic);
	LoadDivGraph(kEnemyGraphicFilename, Enemy::kGraphicDivNum, Enemy::kGraphicDivX, Enemy::kGraphicDivY, Enemy::kGraphicSizeX, Enemy::kGraphicSizeY, m_hEnemyGraphic);

	for (int i = 0; i < Player::kGraphicDivNum; i++) {
		m_player.setHandle(i, m_hPlayerGraphic[i]);
	}

	for (int i = 0; i < Enemy::kGraphicDivNum; i++) {
		m_enemy.setHandle(i, m_hEnemyGraphic[i]);
	}

	m_door.init();
	m_botan.init();
	m_key.init();
	m_player.init();
	m_enemy.init();

	playerDeadTime = 250;

}

// 終了処理
void SceneMain::end() {
	DeleteGraph(m_hMap);
	DeleteGraph(m_hBackgroundHnadle);
	DeleteGraph(m_hKey);
	DeleteGraph(m_hDoor);
	DeleteGraph(m_hPlayerDead);
	DeleteGraph(m_hBotan);

	DeleteSoundMem(m_sKeyHandle);
	DeleteSoundMem(m_sPushBotan);
	DeleteSoundMem(m_sOpenDoor);

	for (auto& playerHandle : m_hPlayerGraphic) {
		DeleteGraph(playerHandle);
	}

	for (auto& EnemyHandle : m_hEnemyGraphic) {
		DeleteGraph(EnemyHandle);
	}
}

// 毎フレームの処理
int SceneMain::update() {

	if (m_key.isCol(m_player)) {
		m_door.setPadlockDead(true);
		m_key.setDead(true);
	}
	if (m_door.isCol(m_player)) {
		m_door.setDead(true);
		if (m_player.clear()) {
			return 1;
		}
		return 0;
	}

	if (m_enemy.isCol(m_player)) {
		if(playerDeadTime >= 0){
		}
		else {
			return 2;
		}
	}
	else {
		m_player.update();
		m_player.trace();
	}

	if (m_botan.isCol(m_player)) {
		m_botan.setDead(true);
		m_enemy.pushBotan(true);
	}

	if (!m_door.isCol(m_player)) {
		if (!m_enemy.isCol(m_player)) {
			m_enemy.update(m_player);
		}
	}

	return 0;
}

// 毎フレームの描画
void SceneMain::draw() {
	m_map.draw();
	m_botan.draw();
	m_door.draw();
	if (!m_enemy.isCol(m_player)) {
		m_player.draw();
	}
	else {
		if (playerDeadTime >= 0) {
			m_player.deadDraw();
			if (playerDeadTime < 100) {
				m_player.soul();
			}
			playerDeadTime--;
			//DrawFormatString(0, 300, GetColor(255, 255, 255), "%d", playerDeadTime);
		}
	}
	m_key.draw();
	m_enemy.draw();
}