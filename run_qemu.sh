#!/bin/sh

qemu-system-x86_64 -net none -m 2G -enable-kvm -cpu host -smp 4 -hda ZenithOS.hdd
