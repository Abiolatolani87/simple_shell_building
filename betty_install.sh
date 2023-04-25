#!/bin/bash

git clone https://github.com/holbertonschool/Betty.git
cd Betty
sudo ./install.sh

chmod a+x betty
mv betty /home/codespace/.local/bin/betty
