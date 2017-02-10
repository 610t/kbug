.. BSD package system documentation master file, created by
   sphinx-quickstart on Fri Feb 10 05:35:31 2017.
   You can adapt this file completely to your liking, but it should at least
   contain the root `toctree` directive.

BSDのパッケージシステムについて
==============================================

.. toctree::
   :maxdepth: 2
   :caption: Contents:

BSDで、様々なソフトウエアをインストールする方法には、ふた通りの方法があります。

一つ目の方法は、ソースからコンパイルをしてバイナリ形式を作成する方式です。
この方法では、コンパイル時に様々なオプションを指定することが可能である場合があり、
特殊なオプションを指定したい場合にはこちらを使うことになります。
コンパイルにはそれなりに時間がかかるので、インストールのための時間が余計にかかります。

二つ目の方法は、実行可能形式であるバイナリ形式でソフトウエアをインストールする方法です。
すでにプログラムの設計図であるソースからのコンパイルが終わっている状態なので、
比較的短時間でインストールが完了します。
手軽にソフトウエアを試すには、こちらがお薦めです。

+--------+----------------+----------------------+----+
|形式    |インストール時間+オプション設定の自由度|備考|
+========+================+======================+====+
|バイナリ|短い            |デフォルト設定        |    |
+--------+----------------+----------------------+----+
|ソース  |長い            |                      |    |
+--------+----------------+----------------------+----+

以下、順にこれらの方法を見ていきましょう。

ソースからのインストール
==============================================
(NetBSD) pkgsrcの場合
------------------------
pkgsrc(https://www.pkgsrc.org/)は、NetBSDで利用されているソースからのアプリケーションインストールシステムです。
pkgsrcの特徴は、NetBSD以外にも様々なプラットホームで利用可能となっている点です。
サポートされているプラットホームは、 http://www.netbsd.org/docs/pkgsrc/introduction.html#intro.platforms にまとまっています。
複数のプラットホームでシステムを構築する必要がある場合、統一亭な操作で利用できるパッケージシステムとして、pkgsrcを選択することは大きなメリットとなります。

FreeBSD portsの場合
------------------------
はじめに、portsの定義であるportスケルトンを取得する必要があります。

::

% sudo portsnap fetch extract

次回以降、portスケルトンを更新するためには、以下のようにします。

::

% sudo portsnap fetch update

インストールしたいportのディレクトリに移動して、makeします。
::

% cd /usr/ports/lang/squeak
% sudo make install

OpenBSD portsの場合
------------------------

バイナリ形式でのソフトウエアのインストール
==============================================

NetBSD pkgの場合
------------------------
::

  % export "PKG_PATH=ftp://ftp.jaist.ac.jp/pub/pkgsrc/packages/OPSYS/ARCH/VERSIONS/All"

::

  % sudo pkg_add squeak

FreeBSD pkgの場合
------------------------
FreeBSD pkgのインストール
^^^^^^^^^^^^^^^^^^^^^^^^^^
::

% sudo pkg install scratch


FreeBSD pkgの更新
^^^^^^^^^^^^^^^^^
::

% sudo pkg update

::

% sudo pkg upgrade

OpenBSD packageの場合
------------------------
はじめに、packageをどこから取得するのかを指定するための環境変数PKG_PATHを定義しておきます。
この設定は、シェルの環境設定ファイルに書き込んでおくと良いでしょう。

* sh系の場合: 環境設定ファイル ~/.profile, ~/.zshrc など
::

  export PKG_PATH=http://ftp.jaist.ac.jp/pub/OpenBSD/$(uname -r)/packages/$(uname -p)/

* csh系の場合:環境設定ファイル ~/.cshrc など
::

  setenv PKG_PATH http://ftp.jaist.ac.jp/pub/OpenBSD/$(uname -r)/packages/$(uname -p)/

::

% doas pkg_add scratch

付録: super userとして作業するために
==============================================

sudo, doasを使ってroot権限で作業する
--------------------------------------
* /usr/local/etc/sudoer
|% visudo

suを使ってrootユーザになる
--------------------------------------
rootのパスワード必要

* /etc/group
|wheel::