@echo off

start VisualStudio2010/Debug/ImmersiveKidz.exe -config data/sgct_config/VRArenaSimCenter.xml -local 0

start VisualStudio2010/Debug/ImmersiveKidz.exe -config data/sgct_config/VRArenaSimCenter.xml -local 1 --slave
start VisualStudio2010/Debug/ImmersiveKidz.exe -config data/sgct_config/VRArenaSimCenter.xml -local 2 --slave
start VisualStudio2010/Debug/ImmersiveKidz.exe -config data/sgct_config/VRArenaSimCenter.xml -local 3 --slave