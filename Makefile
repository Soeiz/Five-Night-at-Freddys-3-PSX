.PHONY: all cleansub
all:
	mkpsxiso -y ./isoconfig.xml
cleansub:
	$(MAKE) clean
	rm -f fnaf3.cue fnaf3.bin

TARGET = fnaf3

SRCS = fnaf3.c \
tim/office/mutecall.tim \
tim/5am6/SAM.tim \
tim/5am6/5AM1.tim \
tim/5am6/5AM2.tim \
tim/5am6/5AM3.tim \
tim/5am6/5AM4.tim \
tim/5am6/5AM5.tim \
tim/5am6/6AM1.tim \
tim/5am6/6AM2.tim \
tim/5am6/6AM3.tim \
tim/5am6/6AM4.tim \
tim/5am6/6AM5.tim \
tim/5am6/6AM6.tim \
tim/office/SPRINGTRAP1.tim \
tim/office/SPRINGTRAP2.tim \
tim/office/panelsprite/PANEL0.tim \
tim/office/panelsprite/PANEL1.tim \
tim/office/panelsprite/PANEL2.tim \
tim/office/panelsprite/PANEL3.tim \
tim/office/panelsprite/PANEL4.tim \
tim/office/panelsprite/PANEL5.tim \
tim/camera/panel/8.tim \
tim/office/FREDDYWANDERING.tim \
tim/office/mangle.tim \
tim/Mpanel/AUDEVICE.tim \
tim/Mpanel/CAMSYS.tim \
tim/Mpanel/selection.tim \
tim/Mpanel/error.tim \
tim/Mpanel/EXIT.tim \
tim/Mpanel/Loadco.tim \
tim/Mpanel/MENU.tim \
tim/Mpanel/REBOOT.tim \
tim/Mpanel/RESTART.tim \
tim/Mpanel/VENTIL.tim \
tim/load.tim \
tim/fnt.tim \
tim/GJSIX.tim \
tim/titlemenu/nights/1ST.tim \
tim/titlemenu/nights/2ND.tim \
tim/titlemenu/nights/3RD.tim \
tim/titlemenu/nights/4TH.tim \
tim/titlemenu/nights/5TH.tim \
tim/titlemenu/nights/6TH.tim \
tim/titlemenu/nights/7TH.tim \
tim/titlemenu/lines/1.tim \
tim/titlemenu/lines/2.tim \
tim/titlemenu/lines/3.tim \
tim/titlemenu/lines/4.tim \
tim/titlemenu/lines/5.tim \
tim/titlemenu/SLTBUT.tim \
tim/titlemenu/NAME.tim \
tim/titlemenu/EXTRA.tim \
tim/titlemenu/NEWGAME.tim \
tim/titlemenu/LOADGAME.tim \
vag/light.vag \
vag/monitor_down.vag \
vag/monitor_up.vag \
vag/monitor_up_2.vag \
vag/officesound.vag \
vag/click.vag \
vag/screamer.vag \
vag/honk.vag \
vag/jamlight.vag \
vag/coin.vag \
vag/vent1.vag \
vag/vent2.vag \
vag/alarm.vag \
vag/windup.vag \
vag/BB1.vag \
vag/BB2.vag \
vag/BB3.vag \
vag/clickfail.vag \
vag/button.vag \
vag/consoleclosing.vag \
vag/consoleopening.vag \

include ../common.mk 
