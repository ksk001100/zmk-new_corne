# 右側 nice!view の Toyoterm 画像

右側は `nice_view_toyoterm` シールド、左側は従来の `nice_view` を使用します。
バッテリー・充電・左右間の接続状態の描画には、使用中のZMKブランチの
標準 `peripheral_status.c`、`util.c`、`bolt.c` をそのまま使います。
標準のランダムな画像選択先2つを同じ画像データに向けるため、起動時の絵は固定です。

## 画像

- `toyoterm-monochrome-master.png`: 承認済みの編集原画（imagegenで作成）。
- `toyoterm-68x140.png`: 実表示用の白黒2色画像、幅68×高さ140px。
- `toyoterm-preview.png`: 同じ画像を4倍に拡大した確認用画像。

生成時の編集指示: 元の端末キャラクターとランプを主役に、縦長・白黒・
小画面で読みやすい構図へ。細かな文字を省略し、鉢植えと玩具を簡略化。

## 再変換

Pillowが入ったPythonで、リポジトリ内の次のスクリプトを実行します。

```sh
python scripts/convert_nice_view_art.py
```

スクリプトは原画を68×140pxに縮小して二値化し、パネルの向きに合わせて
時計回りに90度回転した140×68pxのLVGL 1-bit indexed画像を
`boards/shields/nice_view_toyoterm/art.c` に出力します。
パレット8バイトと、各行をバイト境界に揃えた1224バイトのビットマップを含みます。
ファームウェアのビルド時にはPythonや原画は不要です。

## ビルド・書き込み

既存のGitHub Actions「Build ZMK firmware」が `build.yaml` の設定を使用します。
右側の対象は `nice_nano_v2` / `eyelash_corne_right nice_view_toyoterm` です。
ZMK開発環境がある場合は通常のwestワークスペースから次のようにビルドできます。

```sh
west build -s zmk/app -b nice_nano_v2 -d build/right -- -DZMK_CONFIG=/absolute/path/to/this/repo/config -DZMK_EXTRA_MODULES=/absolute/path/to/this/repo -DSHIELD="eyelash_corne_right nice_view_toyoterm"
```

完成した右側用UF2を右側に書き込みます。左側用の設定・画像は変更していません。

このシールドは現在のZMK v0.3系nice!view実装の画像シンボルと描画APIを使用します。
ZMKを更新する際は、標準ウィジェットとの互換性と画像の向きを再確認してください。
