#! /bin/sh
#
#   tab tseng ,mount tmp on some target dir for test run 
#   
PATH=/bin:/sbin:/usr/bin:/usr/sbin:~/bin
export PATH

echo creating dir on /tmp
mkdir /tmp/usr_var_
mkdir /tmp/etc_
mkdir /tmp/usr_etc_
mkdir /tmp/var_cache

echo cp read only dir to tmp dir
cp -r /usr/var/* /tmp/usr_var_
cp -r /etc/*     /tmp/etc_
cp -r /usr/etc/* /tmp/usr_etc_
cp -r /var/cache/* /tmp/var_cache

echo mount
mount /tmp/usr_var_ /usr/var
mount /tmp/etc_ /etc
mount /tmp/usr_etc_ /usr/etc
mount /tmp/var_cache /var/cache

echo done....
