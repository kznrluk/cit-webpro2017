# CIT Web App
大学演習用。

## 以下メモ
index.html - リンク集

## How to Use
事前にpuzzle.cを適切な形でビルドしてください。

**gcc puzzle.c -o puzzle.cgi**

## Apacheを使う
Webブラウザから/puzzle.cgiにアクセスすることで使用できます。

## Node.jsを使う
Node.jsを使うと、Twitterからアイコンを取得しそれで遊ぶことができます。
Node.js 8.6.0以上推奨。

### 初期設定
webpro.jsの先頭部分を環境に合わせ書き換えてください。
GNU/Liunxで使用する場合、magickをconvertに置き換える必要があります。

### 実行
初期設定を行った後、 **node webpro.js** で実行できます。


## Puzzle.c
スライドパズルCGI用ソースファイル。

### エラー時に確認すべきこと
1. 権限は適切かどうか。
2. sudo -u www-data ./puzzle.cgi を行ってエラーが出ないかどうか。