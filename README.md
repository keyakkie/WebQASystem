# WebQASystem
回答者の区分 (社会人，大学生，高校生など) ごとに集計して結果を表示する Web アンケートシステムです．

## 概要
php が動いて，データベースに接続できる環境であれば使えると思います．  
mysql でしか検証していませんが，データベース関係の関数を変更すれば，多分，他のデータベースと連動しても使えると思います．

ユーザ認証などはせず，回答もデータベースに蓄積せずに，質問の度に全て削除する仕様です．

## 設定方法
1. ソース一式を Web サーバにコピーしてください．

2. データベースとデータベースのユーザを作成します．  
データベースの管理者として include/create_db.sql の中身を実行してください．

3. アンケートの質問項目を設定します．include/userinfo.inc の中身を適宜変更してください．

* getUserInfoKey() の中の変数を変更すればアンケートフォームの項目を変更できます．  
$userinfo_key はアンケートフォームの項目を設定します．半角のみ使用可能です．現在の仕様では，区分は attribute，意見は opinion に固定しています．  
$userinfo_formcategory は，アンケートフォームの種類を指定します．"text"，"select"，"button"，"click" から選べます．attribute は select と対応させてください．  
$userinfo_caption は，各項目の Web ページ上での表記を設定します．全角でも大丈夫です．  
$userinfo_default は，デフォルトの値を選択したい場合に記載してください．

* getAttributeKey() は区分を指定します．  
$attribute_key は，区分の項目です．半角のみ仕様できます．  
$attribute_caption は，区分の Wb ページ上での表記です．全角も仕様可できます．

* getOptionKey() は意見の選択肢を指定します．  
$option_key は，意見の項目です．半角のみ仕様できます．  
$option_caption は，意見の Wb ページ上での表記です．全角も仕様可できます．

基本的に，getUserInfoKey() での text の項目数，区分と意見の選択肢を増やす分には問題ないようになっていると思います．

## 仕様方法
・下記のページをご参照ください．
http://www.lsc.cs.titech.ac.jp/keyaki/WebQASystem/abst.html

## 連絡先
もし不具合や要望などがあれば keyakkie@gmail.com までご連絡ください．
