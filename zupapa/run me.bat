echo off
echo Build rom files
.\build
echo Build ISO
.\mkisofs -iso-level 1 -o OUTPUT/zupapa.iso -pad -N -V "ZUPAPA" DATA/Z80.Z80 SPR.SPR FIX.FIX DATA/PCM.PCM PRG.PRG DATA/TITLE_U.SYS DATA/TITLE_J.SYS DATA/TITLE_E.SYS DATA/LOGO_E.PRG DATA/LOGO_J.PRG DATA/LOGO_U.PRG DATA/ABS.TXT DATA/BIB.TXT DATA/CPY.TXT DATA/IPL.TXT
del fix.fix
del prg.prg
del spr.spr
echo Build complete - burn contents of OUTPUT to a CD or load them onto the SD card for SD Loader
pause