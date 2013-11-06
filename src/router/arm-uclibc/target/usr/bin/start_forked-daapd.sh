#! /bin/sh
#
#   tab tseng ,mount tmp on some target dir for test run 
#   
PATH=/bin:/sbin:/usr/bin:/usr/sbin:~/bin
export PATH

echo creating dir on /tmp
#mkdir /tmp/usr_var_
#mkdir /tmp/etc_
#mkdir /tmp/usr_etc
#mkdir /tmp/var_cache

test -z "/tmp/avahi" || mkdir "/tmp/avahi"
cp -f /usr/etc/avahi-daemon.conf /tmp/avahi/avahi-daemon.conf
cp -f  /etc/system.conf /tmp/system.conf
test -z "/tmp/system.d" || mkdir "/tmp/system.d"
cp -f  /etc/avahi-dbus.conf /tmp/system.d/avahi-dbus.conf


echo done....
#adduser messagebus
#addgroup netdev
#sed -i '1i root:*:0:0:root:/:/bin/sh' /etc/passwd

echo starting dbus...
dbus-daemon --config-file=/tmp/system.conf
sleep 3

echo starting avahi...
avahi-daemon -f /tmp/avahi/avahi-daemon.conf &
sleep 3

echo starting forked-daapd
test -z "/tmp/forked-daapd" || mkdir "/tmp/forked-daapd"
cp -f  /etc/forked-daapd.conf /tmp/forked-daapd.conf

echo done!
