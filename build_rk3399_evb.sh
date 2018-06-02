#!/bin/bash

make ARCH=arm64 rockchip_linux_defconfig
#make ARCH=arm64 rk3326-evb-linux-lp3-v10.img -j12
#make ARCH=arm64  rk3399-sapphire-excavator-linux.img -j12
#make ARCH=arm64  rk3399-firefly-linux.img -j12
#make ARCH=arm64  rk3399-zhi01-818-linux.img -j12
make ARCH=arm64 rk3399-binocular-818-linux.img -j12
