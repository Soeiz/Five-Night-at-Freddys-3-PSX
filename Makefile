.PHONY: all cleansub
all:
	mkpsxiso -y ./isoconfig.xml
cleansub:
	$(MAKE) clean
	rm -f fnaf3.cue fnaf3.bin

TARGET = fnaf3

SRCS = fnaf3.c \
tim/office/oLEFTpart2.tim \
tim/office/oLEFTpart2light.tim \
tim/office/officeMIDDLE.tim \
tim/office/officeMIDDLElight.tim \
tim/office/oRIGHTpart2.tim \
tim/office/oRIGHTpart2light.tim \
tim/office/fan1.tim \
tim/office/fan2.tim \
tim/office/fan3.tim \
tim/office/fan4.tim \
tim/office/mutecall.tim \
tim/timer/timer0.tim \
tim/timer/timer1.tim \
tim/timer/timer2.tim \
tim/timer/timer3.tim \
tim/timer/timer4.tim \
tim/timer/timer5.tim \
tim/timer/timer6.tim \
tim/timer/timer7.tim \
tim/timer/timer8.tim \
tim/timer/timer9.tim \
tim/timer/timer10.tim \
tim/timer/timer11.tim \
tim/timer/timer12.tim \
tim/timer/timer13.tim \
tim/timer/timer14.tim \
tim/timer/timer15.tim \
tim/timer/timer16.tim \
tim/timer/timer17.tim \
tim/timer/timer18.tim \
tim/timer/timer19.tim \
tim/timer/timer20.tim \
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
tim/load.tim \
tim/fnt.tim \
tim/GJSIX.tim \
tim/danger1.tim \
tim/danger2.tim \
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
tim/titlemenu/lines/6.tim \
vag/light.vag \
vag/monitor_down.vag \
vag/monitor_up.vag \
vag/mask-down.vag \
vag/mask-up.vag \
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

include ../common.mk 
