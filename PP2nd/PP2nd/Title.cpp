#include "Title.h"

/// タイトルのイメージ

/// メニュー画面でゲームモードを表示
/// 1 ストーリーモード(最後に実装) 2 体験版_簡単 3 体験版_難しい
/// クリックで確認UI表示 -> 承認でステージ読み込みシーンへ遷移

Title::Title()
{
	titleScreenUPtr = std::make_unique<TitleScreen>();
	titleScreenUPtr->Init();

}

Title::~Title()
{
}

void Title::Update() const
{
	titleScreenUPtr->Update();
}
