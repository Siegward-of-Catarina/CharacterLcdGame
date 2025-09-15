# LCDミニゲーム
RX210マイコンを使用したミニゲーム<br>
右から流れるアイテムを障害物をよけながら獲得していくゲーム
# デモ
| タイトル画面 | ゲーム画面 |
| :---------: | :-------: |
| ![title_gif](https://github.com/user-attachments/assets/e4bdb25f-de1d-4963-8739-b16aa9130368) | ![game_fin](https://github.com/user-attachments/assets/50453738-fab8-4e0f-8791-3ac55204a727) |
| **ゲームオーバー画面** | **リザルト画面** |
| ![gameover_fin](https://github.com/user-attachments/assets/7fb5aaf8-2ed5-4ce3-849f-2c7278c4c65a) | ![result_fin](https://github.com/user-attachments/assets/8d0124a1-f28c-416d-a04b-647c3a315b72) |

### プレイ動画
[動画を見る]( https://github.com/user-attachments/assets/30839473-f2b9-4b1d-b849-944749e79862 )

# 経緯
characterLcdの授業中、文字ではない図形を表示させるサンプルが紹介され、<br>
ドット絵表示できればゲームもできるな。と思ったのがきっかけです。<br>

# 目的
* ゲームを作りながら組込み開発への知識をより深める。<br>
* 授業では触れない所も自身で使ってみる。<br>
# 開発環境

* マイコン : Renesas Starter Kit for RX210(R5F5210BBxFP)
* IDE : CS+
* ビルドツール : CC-RX
* デバッグツール : RX E2 Lite
* 開発言語 : C言語 ( C99 )

# Note
### デバッグツール設定
* メインクロックソース : HOCO
* 動作周波数 : 50.0 MHz

# 開発してみて

## 工夫点

### リアルタイム性の確保
**問題**  
ゲーム速度や、アニメーション更新のため周期的に処理する必要があった。<br>
しかし授業では空ループで間隔制御していたので、リアルタイム性に欠けていた。<br>
**解決**  
- 初期段階では loop カウンタで処理周期を調整し、毎ループで全判定を通れるようにした。  
- 授業でハードウェアタイマを学んだ後、`現在時間 - 最終更新時間` の差分で処理を行う方式に変更。  
→ 安定した周期制御が可能になり、ゲームらしいリアルタイム性を確保できた。
- LCDへの文字描画コマンドを授業段階では安定のため長めの同期を取っていたが、マニュアルの最小同期時間へ変更し高速化。
- 再描画は更新があった時のみ実行し、最小限の再描画で済むようにした。
```c
typedef enum
{
    NONE            = 0,
    PLAYER_DRAW     = 1 << 0,
    PLAYER_CLEAR    = 1 << 1,
    // 省略
```
```c
obj->draw_flags |= PLAYER_CLEAR_DRAW;
//...
obj->draw_flags |= UI_DRAW;

```
```c
if(  obj->draw_flags & ( PLAYER_CLEAR_DRAW | PLAYER_DRAW ) )
```
---

### コードの整理
**問題**  
要素（プレイヤー、アイテム、スコアなど）が増えるにつれ、関係性が複雑化し、可読性が低下した。  

**解決**  
- 構造体と関数を組み合わせ、C言語でオブジェクト指向風の設計に。  
- オブジェクトごとにファイルを分割し、役割を明確化。  
→ 規模が大きくなっても管理しやすいコード構成を実現した。  

---

## 感想
- 今回は **パフォーマンスより可読性を優先** して開発を進めた。  
  ただし、組込み開発では「関数化やファイル分割を多用することが性能に与える影響」を常に意識する必要があると感じた。  
- C言語での実装を通して、**class やオブジェクト指向の便利さ** を強く実感した。 

# Author

作成情報を列挙する

* 作成者 倉本　星玖
* 所属　ポリテクセンター関西　Iotシステム科
* E-mail kuramoto.riku.zzz@gmail.com

# License

"hoge" is under [MIT license](https://en.wikipedia.org/wiki/MIT_License).

<p align="right">(<a href="#top">トップへ</a>)</p>
