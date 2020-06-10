#!/bin/sh

set -e

# Might as well ask for password up-front, right?
sudo -v

# Keep-alive: update existing sudo time stamp if set, otherwise do nothing.
while true; do sudo -n true; sleep 60; kill -0 "$$" || exit; done 2>/dev/null &

sudo losetup -Pf --show ZenithOS.hdd > loopback_dev
sudo partprobe `cat loopback_dev`

mkdir -p mnt
sudo mount `cat loopback_dev`p1 mnt

rm -rf src
mkdir src
sudo cp -rv mnt/* src/

sudo sync

sudo umount mnt
sudo losetup -d `cat loopback_dev`

rm -rf mnt
rm loopback_dev

sudo chown -R $USER:$USER src
