.. 
 Copyright (c) 2017 Takeshi MUTOH All rights reserved.
 Redistribution and use in source and binary forms, with or without
 modification, are permitted provided that the following conditions
 are met:
 1. Redistributions of source code must retain the above copyright
    notice, this list of conditions and the following disclaimer.
 2. Redistributions in binary form must reproduce the above copyright
    notice, this list of conditions and the following disclaimer in the
    documentation and/or other materials provided with the distribution.
 THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

=================================
BSDで楽しむ!! Scratch / Squeak
=================================

============
はじめに
============
* http://qml.610t.org/FreeBSD/ScratchBSD.html

============
Squeak Etoys
============

Squeak VM環境構築
-------------------

Etoysのインストール
-------------------

Squeak+Gainerで遊ぶ
-------------------

============
Scratch 2.0
============

Scratch 2.0環境構築
---------------------

flash対応ブラウザをインストールする
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

flashpluginの設定
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

============
Scratch 1.4
============
Scratch 1.4環境の構築
------------------------

USB Camera
------------------------

Scratch Sensor Board
------------------------
* 日本で買えるScratchセンサーボード http://swikis.ddo.jp/WorldStethoscope/54

* なのぼ～ど http://tiisai.dip.jp/?page_id=935
* nekoboard2 https://www.switch-science.com/catalog/2700/

Scratch Remote Sensor
------------------------
* http://qml.610t.org/squeak/CodarDojoNara201612.html

* http://qml.610t.org/squeak/ScratchDay2016.html

.. .. image:: images/

Android
^^^^^^^^^^^^^^^^^^^^^
.. image:: images/PhysicalSensor4Scratch.png

ESP8266
^^^^^^^^^^^^^^^^^^^^^
.. image:: images/ESP8266-Scratch.png

micro:bit (chibi:bit)
^^^^^^^^^^^^^^^^^^^^^
* BBC micro:bit(chibi:bit)+scratch でのプログラミングテスト http://qiita.com/asondemita/items/8ad1a9d224ee54428bed

.. image:: images/microbit-Scratch.png

.. code-block:: python



  from microbit import *

  def get_sensor_data():
    x, y, z = accelerometer.get_x(), accelerometer.get_y(), accelerometer.get_z()
    a, b = button_a.is_pressed(), button_b.is_pressed()
    print(x, y, z, a, b)
  
  uart.init(115200)
  
  while True:
    sleep(100)
    get_sensor_data()
    if uart.any():
        str=uart.readline()
        display.scroll(str,wait=False,loop=True)

============
Scratch 3.0
============

Scratch 3.0環境の構築
---------------------

Node.js関連の設定
^^^^^^^^^^^^^^^^^

Scratch 3.0 github版のインストール
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

=====
CogVM
=====