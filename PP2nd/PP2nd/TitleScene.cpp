#include "TitleScreen.h"
#include "TitleScene.h"

/// タイトルのイメージ
/// 近いカメラで配置場所を示す
/// 操作方法を字幕で表示
/// 置いたとき、カメラを引き全体像を表示する
/// 右クリック長押しでスキップできる(できれば実装)
/// タイトルロゴを表示
/// クリックでメニュー画面へ遷移
/// メニュー画面でゲームモードを表示
/// 1 ストーリーモード(最後に実装) 2 体験版_簡単 3 体験版_難しい
/// クリックで確認UI表示 -> 承認でステージ読み込みシーンへ遷移

TitleScene::TitleScene()
{
	titleScreenUPtr = make_unique<TitleScreen>();
}

TitleScene::~TitleScene()
{
}

void TitleScene::Update() const
{
}
