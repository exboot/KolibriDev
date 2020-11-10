#!/bin/bash
IMG_DIR=build_img
ISO_DIR=build_iso
KERNEL_DIR="src/kernel"
FASMX_DIR="src/programs/develop/fasmx"

########### BUILD KERNEL ############
echo -e "\n====Build Kernel====\n"
cd $KERNEL_DIR
make clean > /dev/null
env lang=en make
cp -f bin/boot_fat12.bin ../..
../../tools/kerpack bin/kernel.mnt ../../$IMG_DIR/KERNEL.MNT
cd ../..

########## BUILD FASMX #############
echo -e "\n====Build FasmX====\n"
cd $FASMX_DIR
make 
make install
make clean
cd ../../../..

########## CHECK IMG SIZE ###########
size=$(du -shb build_img | cut -f1)
if (( $size > 1474560 )); then
    echo -e "\033[0;31m Error! Files do not fit into the image! \033[0;0m"
    read -s -n 1
    exit
fi


############# BUILD IMG #############
echo -e "\n====Build IMG====\n"
mkdir tmp
dd if=/dev/zero of=$ISO_DIR/kolibri.img bs=1k count=1440
mkfs.vfat -F12 $ISO_DIR/kolibri.img 
dd if=boot_fat12.bin of=$ISO_DIR/kolibri.img conv=notrunc bs=512 count=1
sudo mount -o loop,rw,sync $ISO_DIR/kolibri.img tmp
echo "Copying..."
sudo cp -rf $IMG_DIR/* tmp
sync
sudo umount tmp
sudo rm -rf tmp


############# BUILD ISO #############
echo -e "\n====Build ISO====\n"
cd $ISO_DIR
mkisofs -U -J -pad -b kolibri.img -c boot.catalog -hide-joliet boot.catalog -graft-points -A "KolibriDE AutoBuilder" -publisher "KolibriDE Team" -o ../kolibri.iso ./
cd ..

#############   CLEAN   ##############
./clean.sh > /dev/null

read -s -n 1

#
# THIS FILE WAS WRITTEN BY TURBOCAT2001, MAXCODEHACK, RGIMAD
#
