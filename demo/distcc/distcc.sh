#!/bin/sh
## ssh
if [ x"${SSH_AGENT_PID}" = x"" ];then
  eval `ssh-agent -s`
  ssh-add
fi

# force DISPLAY at :0
export DISPLAY=:0
xset b off
xset s off

## terminal
#ssh -X 192.168.60.2 /usr/X11R7/bin/xterm -fn r16 &
#ssh -X 192.168.60.11 /usr/X11R7/bin/xterm -fn r16 &
#ssh -X 192.168.60.13 /usr/X11R7/bin/xterm -fn r16 &
## xload
xload -geometry 600x250-0+0 &
# ssh -X 192.168.61.11	/usr/X11R7/bin/xload -geometry 600x250-0+250 &
ssh -X 192.168.60.14	/usr/local/bin/xload -geometry 600x250-0+500 &
ssh -X 192.168.7.2	/usr/local/bin/xload -geometry 600x250-0+750 &
