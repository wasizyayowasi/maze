#include "DxLib.h"
#include"Map.h"

Map::Map() {
	m_handle = -1;

}

Map:: ~Map() {

}

//マップの初期化
void Map::init() {


}

//描画
void Map::draw() {
	DrawGraph(100, 25, m_handle, true);
}