#!/bin/sh
# HOSTS="192.168.7.2 192.168.60.14 192.168.60.1"
HOSTS="192.168.61.11 192.168.61.15 192.168.7.2 192.168.60.14 192.168.60.1"
## ssh
if [ x"${SSH_AGENT_PID}" = x"" ];then
  eval `ssh-agent -s`
  ssh-add
fi

for h in ${HOSTS}
do
  echo "* Shutting down ${h}"
  ssh ${h} sudo /sbin/shutdown -p now
done
