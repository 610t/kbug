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
pkgsrcでコンパイルされた成果物は、package(pkg)としてまとめられます。

インストールするためには、pkgファイルをpkg_addするだけです。

pkg_addでは、ネットワーク経由でのインストールにも対応しています。
この場合、環境変数PKG_PATHに利用するサーバの情報を設定することで、そこにあるpkgのインストールが可能です。


環境変数PKG_PATHの設定
^^^^^^^^^^^^^^^^^^^^^^
環境変数PKG_PATHは、以下のように設定します。
::

  % export "PKG_PATH=ftp://ftp.netbsd.org/pub/pkgsrc/packages/OPSYS/ARCH/VERSIONS/All"

コマンドライン中で、以下の部分は自分の環境に読み変えます。
* OPSYS: オペレーティングシステムの名称。"NetBSD", "MirBSD", "Minix"など。
* ARCH: CPUアーキテクチャ。"i386", "amd64", "evbarm"など。
* VERSION: OSのリリースバージョン。"7.0.2", "7.0_2016Q4"など。

例えば、NetBSDでamd64アーキテクチャ、OSバージョンが7.0.2の場合は、以下のように指定します。
::

  % export "PKG_PATH=ftp://ftp.netbsd.org/pub/pkgsrc/packages/NetBSD/amd64/7.0.2/All"

ここで、ホスト部分(ftp.netbsd.org)は、NetBSDの場合、 http://netbsd.org/mirrors/ のミラーサイトを利用することができます。
できるだけ近くのサーバを利用するようにしましょう。

セキュリティ対策
^^^^^^^^^^^^^^^^^^^^^^
::

  % pkg_admin fetch-pkg-vulnerabilities
  % pkg_admin audit


実際のインストール
^^^^^^^^^^^^^^^^^^^^^^
インストールは、以下のようにpkg_addを実行します。
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

FreeBSD pkgのセキュリティ対策
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
::

  % pkg audit|head
  python27-2.7.11_3 is vulnerable:
  Python -- smtplib StartTLS stripping vulnerability
  CVE: CVE-2016-0772
  WWW: https://vuxml.FreeBSD.org/freebsd/8d5368ef-40fe-11e6-b2ec-b499baebfeaf.html
  
  libgcrypt-1.7.1 is vulnerable:
  gnupg -- attacker who obtains 4640 bits from the RNG can trivially predict the next 160 bits of output
  CVE: CVE-2016-6313
  WWW: https://vuxml.FreeBSD.org/freebsd/e1c71d8d-64d9-11e6-b38a-25a46b33f2ed.html

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