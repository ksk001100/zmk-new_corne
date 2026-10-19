# 右側 nice!view のカスタム画像

右側は `nice_view_custom` シールド、左側は従来の `nice_view` を使用します。
バッテリー・充電・左右間の接続状態の描画には、使用中のZMKブランチの
標準 `peripheral_status.c`、`util.c`、`bolt.c` をそのまま使います。
標準のランダムな画像選択先2つを同じ画像データに向けるため、起動時の絵は固定です。

`nice_view_custom.conf` は標準の `nice_view.conf` と同じく、表示を有効にして
アイドル時の画面消去を無効にします。シールドの `.conf` は選択したシールド名で
読み込まれるため、`SHIELD_NICE_VIEW` の選択だけではこれらの設定は引き継がれません。
表示が無効な構成ではCMakeでエラーにし、画面のないUF2が生成されることを防ぎます。

## 画像

- `artwork-source.png`: 差し替え元のPNG画像。
- `artwork-68x140.png`: 実表示用の白黒2色画像、幅68×高さ140px。
- `artwork-preview.png`: 同じ画像を4倍に拡大した確認用画像。

## 画像の差し替え

1. `assets/nice_view/artwork-source.png` を好きな画像に差し替えます。
   幅68×高さ140px、または同じ縦横比の大きな画像がおすすめです。
2. Pillowが入ったPythonで、次の変換スクリプトを実行します。

```sh
python scripts/convert_nice_view_art.py
```

3. `artwork-preview.png` を確認し、生成された `art.c` と画像を含めてcommit・pushします。
4. GitHub Actionsで再ビルドし、右側用UF2だけを書き込みます。

画像を変更するたびにシールド名やビルド設定を変える必要はありません。

スクリプトは原画を68×140pxに縮小して二値化し、パネルの向きに合わせて
時計回りに90度回転した140×68pxのLVGL 1-bit indexed画像を
`boards/shields/nice_view_custom/art.c` に出力します。
パレット8バイトと、各行をバイト境界に揃えた1224バイトのビットマップを含みます。
実機で確認された白黒の極性に合わせ、画像のパレットを入れ替えています。
PNGプレビューは見せたい色のまま保持し、バッテリー・接続表示の色設定は変更しません。
ファームウェアのビルド時にはPythonや原画は不要です。

## ビルド・書き込み

既存のGitHub Actions「Build ZMK firmware」が `build.yaml` の設定を使用します。
右側の対象は `nice_nano_v2` / `eyelash_corne_right nice_view_custom` です。
ZMK開発環境がある場合は通常のwestワークスペースから次のようにビルドできます。

```sh
west build -s zmk/app -b nice_nano_v2 -d build/right -- -DZMK_CONFIG=/absolute/path/to/this/repo/config -DZMK_EXTRA_MODULES=/absolute/path/to/this/repo -DSHIELD="eyelash_corne_right nice_view_custom"
```

完成した右側用UF2を右側に書き込みます。左側用の設定・画像は変更していません。

このシールドは現在のZMK v0.3系nice!view実装の画像シンボルと描画APIを使用します。
ZMKを更新する際は、標準ウィジェットとの互換性と画像の向きを再確認してください。
