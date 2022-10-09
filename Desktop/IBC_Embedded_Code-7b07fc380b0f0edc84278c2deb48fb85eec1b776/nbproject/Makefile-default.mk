#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/EmbeddedThermoControl-gates-india-1.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/EmbeddedThermoControl-gates-india-1.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=
else
COMPARISON_BUILD=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=cs_woodmaster_400_configuration_bits.c cs_woodmaster_400_flowmeter.c cs_woodmaster_400_interrupts.c cs_woodmaster_400_main.c cs_woodmaster_400_message.c cs_woodmaster_400_oxy_sensor.c cs_woodmaster_400_potentiometer.c cs_woodmaster_400_pwm.c cs_woodmaster_400_serial_ports.c cs_woodmaster_400_system.c cs_woodmaster_400_thermistor.c cs_woodmaster_400_thermocouple.c cs_woodmaster_400_user.c ClearStakMain.c ClearStakStateMachine.c ClearStakPWMInput.c ClearStakInputParser.c ClearStakSerialInput.c ClearStakDataTable.c ClearStakOutputHandler.c ClearStakSerialHandler.c ClearStakEEPROMHandler.c BiomassControlsPIDController.c cs_pdk_400_sk_vfd.c cs_woodmaster_400_wattnode.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/cs_woodmaster_400_configuration_bits.p1 ${OBJECTDIR}/cs_woodmaster_400_flowmeter.p1 ${OBJECTDIR}/cs_woodmaster_400_interrupts.p1 ${OBJECTDIR}/cs_woodmaster_400_main.p1 ${OBJECTDIR}/cs_woodmaster_400_message.p1 ${OBJECTDIR}/cs_woodmaster_400_oxy_sensor.p1 ${OBJECTDIR}/cs_woodmaster_400_potentiometer.p1 ${OBJECTDIR}/cs_woodmaster_400_pwm.p1 ${OBJECTDIR}/cs_woodmaster_400_serial_ports.p1 ${OBJECTDIR}/cs_woodmaster_400_system.p1 ${OBJECTDIR}/cs_woodmaster_400_thermistor.p1 ${OBJECTDIR}/cs_woodmaster_400_thermocouple.p1 ${OBJECTDIR}/cs_woodmaster_400_user.p1 ${OBJECTDIR}/ClearStakMain.p1 ${OBJECTDIR}/ClearStakStateMachine.p1 ${OBJECTDIR}/ClearStakPWMInput.p1 ${OBJECTDIR}/ClearStakInputParser.p1 ${OBJECTDIR}/ClearStakSerialInput.p1 ${OBJECTDIR}/ClearStakDataTable.p1 ${OBJECTDIR}/ClearStakOutputHandler.p1 ${OBJECTDIR}/ClearStakSerialHandler.p1 ${OBJECTDIR}/ClearStakEEPROMHandler.p1 ${OBJECTDIR}/BiomassControlsPIDController.p1 ${OBJECTDIR}/cs_pdk_400_sk_vfd.p1 ${OBJECTDIR}/cs_woodmaster_400_wattnode.p1
POSSIBLE_DEPFILES=${OBJECTDIR}/cs_woodmaster_400_configuration_bits.p1.d ${OBJECTDIR}/cs_woodmaster_400_flowmeter.p1.d ${OBJECTDIR}/cs_woodmaster_400_interrupts.p1.d ${OBJECTDIR}/cs_woodmaster_400_main.p1.d ${OBJECTDIR}/cs_woodmaster_400_message.p1.d ${OBJECTDIR}/cs_woodmaster_400_oxy_sensor.p1.d ${OBJECTDIR}/cs_woodmaster_400_potentiometer.p1.d ${OBJECTDIR}/cs_woodmaster_400_pwm.p1.d ${OBJECTDIR}/cs_woodmaster_400_serial_ports.p1.d ${OBJECTDIR}/cs_woodmaster_400_system.p1.d ${OBJECTDIR}/cs_woodmaster_400_thermistor.p1.d ${OBJECTDIR}/cs_woodmaster_400_thermocouple.p1.d ${OBJECTDIR}/cs_woodmaster_400_user.p1.d ${OBJECTDIR}/ClearStakMain.p1.d ${OBJECTDIR}/ClearStakStateMachine.p1.d ${OBJECTDIR}/ClearStakPWMInput.p1.d ${OBJECTDIR}/ClearStakInputParser.p1.d ${OBJECTDIR}/ClearStakSerialInput.p1.d ${OBJECTDIR}/ClearStakDataTable.p1.d ${OBJECTDIR}/ClearStakOutputHandler.p1.d ${OBJECTDIR}/ClearStakSerialHandler.p1.d ${OBJECTDIR}/ClearStakEEPROMHandler.p1.d ${OBJECTDIR}/BiomassControlsPIDController.p1.d ${OBJECTDIR}/cs_pdk_400_sk_vfd.p1.d ${OBJECTDIR}/cs_woodmaster_400_wattnode.p1.d

# Object Files
OBJECTFILES=${OBJECTDIR}/cs_woodmaster_400_configuration_bits.p1 ${OBJECTDIR}/cs_woodmaster_400_flowmeter.p1 ${OBJECTDIR}/cs_woodmaster_400_interrupts.p1 ${OBJECTDIR}/cs_woodmaster_400_main.p1 ${OBJECTDIR}/cs_woodmaster_400_message.p1 ${OBJECTDIR}/cs_woodmaster_400_oxy_sensor.p1 ${OBJECTDIR}/cs_woodmaster_400_potentiometer.p1 ${OBJECTDIR}/cs_woodmaster_400_pwm.p1 ${OBJECTDIR}/cs_woodmaster_400_serial_ports.p1 ${OBJECTDIR}/cs_woodmaster_400_system.p1 ${OBJECTDIR}/cs_woodmaster_400_thermistor.p1 ${OBJECTDIR}/cs_woodmaster_400_thermocouple.p1 ${OBJECTDIR}/cs_woodmaster_400_user.p1 ${OBJECTDIR}/ClearStakMain.p1 ${OBJECTDIR}/ClearStakStateMachine.p1 ${OBJECTDIR}/ClearStakPWMInput.p1 ${OBJECTDIR}/ClearStakInputParser.p1 ${OBJECTDIR}/ClearStakSerialInput.p1 ${OBJECTDIR}/ClearStakDataTable.p1 ${OBJECTDIR}/ClearStakOutputHandler.p1 ${OBJECTDIR}/ClearStakSerialHandler.p1 ${OBJECTDIR}/ClearStakEEPROMHandler.p1 ${OBJECTDIR}/BiomassControlsPIDController.p1 ${OBJECTDIR}/cs_pdk_400_sk_vfd.p1 ${OBJECTDIR}/cs_woodmaster_400_wattnode.p1

# Source Files
SOURCEFILES=cs_woodmaster_400_configuration_bits.c cs_woodmaster_400_flowmeter.c cs_woodmaster_400_interrupts.c cs_woodmaster_400_main.c cs_woodmaster_400_message.c cs_woodmaster_400_oxy_sensor.c cs_woodmaster_400_potentiometer.c cs_woodmaster_400_pwm.c cs_woodmaster_400_serial_ports.c cs_woodmaster_400_system.c cs_woodmaster_400_thermistor.c cs_woodmaster_400_thermocouple.c cs_woodmaster_400_user.c ClearStakMain.c ClearStakStateMachine.c ClearStakPWMInput.c ClearStakInputParser.c ClearStakSerialInput.c ClearStakDataTable.c ClearStakOutputHandler.c ClearStakSerialHandler.c ClearStakEEPROMHandler.c BiomassControlsPIDController.c cs_pdk_400_sk_vfd.c cs_woodmaster_400_wattnode.c


CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/EmbeddedThermoControl-gates-india-1.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=18F86K22
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/cs_woodmaster_400_configuration_bits.p1: cs_woodmaster_400_configuration_bits.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/cs_woodmaster_400_configuration_bits.p1.d 
	@${RM} ${OBJECTDIR}/cs_woodmaster_400_configuration_bits.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=pickit3  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,-asmfile,+speed,-space,-debug --addrqual=ignore --mode=pro -P -N255 --warn=0 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/cs_woodmaster_400_configuration_bits.p1  cs_woodmaster_400_configuration_bits.c 
	@-${MV} ${OBJECTDIR}/cs_woodmaster_400_configuration_bits.d ${OBJECTDIR}/cs_woodmaster_400_configuration_bits.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/cs_woodmaster_400_configuration_bits.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/cs_woodmaster_400_flowmeter.p1: cs_woodmaster_400_flowmeter.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/cs_woodmaster_400_flowmeter.p1.d 
	@${RM} ${OBJECTDIR}/cs_woodmaster_400_flowmeter.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=pickit3  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,-asmfile,+speed,-space,-debug --addrqual=ignore --mode=pro -P -N255 --warn=0 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/cs_woodmaster_400_flowmeter.p1  cs_woodmaster_400_flowmeter.c 
	@-${MV} ${OBJECTDIR}/cs_woodmaster_400_flowmeter.d ${OBJECTDIR}/cs_woodmaster_400_flowmeter.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/cs_woodmaster_400_flowmeter.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/cs_woodmaster_400_interrupts.p1: cs_woodmaster_400_interrupts.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/cs_woodmaster_400_interrupts.p1.d 
	@${RM} ${OBJECTDIR}/cs_woodmaster_400_interrupts.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=pickit3  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,-asmfile,+speed,-space,-debug --addrqual=ignore --mode=pro -P -N255 --warn=0 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/cs_woodmaster_400_interrupts.p1  cs_woodmaster_400_interrupts.c 
	@-${MV} ${OBJECTDIR}/cs_woodmaster_400_interrupts.d ${OBJECTDIR}/cs_woodmaster_400_interrupts.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/cs_woodmaster_400_interrupts.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/cs_woodmaster_400_main.p1: cs_woodmaster_400_main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/cs_woodmaster_400_main.p1.d 
	@${RM} ${OBJECTDIR}/cs_woodmaster_400_main.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=pickit3  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,-asmfile,+speed,-space,-debug --addrqual=ignore --mode=pro -P -N255 --warn=0 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/cs_woodmaster_400_main.p1  cs_woodmaster_400_main.c 
	@-${MV} ${OBJECTDIR}/cs_woodmaster_400_main.d ${OBJECTDIR}/cs_woodmaster_400_main.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/cs_woodmaster_400_main.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/cs_woodmaster_400_message.p1: cs_woodmaster_400_message.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/cs_woodmaster_400_message.p1.d 
	@${RM} ${OBJECTDIR}/cs_woodmaster_400_message.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=pickit3  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,-asmfile,+speed,-space,-debug --addrqual=ignore --mode=pro -P -N255 --warn=0 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/cs_woodmaster_400_message.p1  cs_woodmaster_400_message.c 
	@-${MV} ${OBJECTDIR}/cs_woodmaster_400_message.d ${OBJECTDIR}/cs_woodmaster_400_message.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/cs_woodmaster_400_message.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/cs_woodmaster_400_oxy_sensor.p1: cs_woodmaster_400_oxy_sensor.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/cs_woodmaster_400_oxy_sensor.p1.d 
	@${RM} ${OBJECTDIR}/cs_woodmaster_400_oxy_sensor.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=pickit3  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,-asmfile,+speed,-space,-debug --addrqual=ignore --mode=pro -P -N255 --warn=0 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/cs_woodmaster_400_oxy_sensor.p1  cs_woodmaster_400_oxy_sensor.c 
	@-${MV} ${OBJECTDIR}/cs_woodmaster_400_oxy_sensor.d ${OBJECTDIR}/cs_woodmaster_400_oxy_sensor.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/cs_woodmaster_400_oxy_sensor.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/cs_woodmaster_400_potentiometer.p1: cs_woodmaster_400_potentiometer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/cs_woodmaster_400_potentiometer.p1.d 
	@${RM} ${OBJECTDIR}/cs_woodmaster_400_potentiometer.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=pickit3  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,-asmfile,+speed,-space,-debug --addrqual=ignore --mode=pro -P -N255 --warn=0 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/cs_woodmaster_400_potentiometer.p1  cs_woodmaster_400_potentiometer.c 
	@-${MV} ${OBJECTDIR}/cs_woodmaster_400_potentiometer.d ${OBJECTDIR}/cs_woodmaster_400_potentiometer.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/cs_woodmaster_400_potentiometer.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/cs_woodmaster_400_pwm.p1: cs_woodmaster_400_pwm.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/cs_woodmaster_400_pwm.p1.d 
	@${RM} ${OBJECTDIR}/cs_woodmaster_400_pwm.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=pickit3  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,-asmfile,+speed,-space,-debug --addrqual=ignore --mode=pro -P -N255 --warn=0 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/cs_woodmaster_400_pwm.p1  cs_woodmaster_400_pwm.c 
	@-${MV} ${OBJECTDIR}/cs_woodmaster_400_pwm.d ${OBJECTDIR}/cs_woodmaster_400_pwm.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/cs_woodmaster_400_pwm.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/cs_woodmaster_400_serial_ports.p1: cs_woodmaster_400_serial_ports.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/cs_woodmaster_400_serial_ports.p1.d 
	@${RM} ${OBJECTDIR}/cs_woodmaster_400_serial_ports.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=pickit3  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,-asmfile,+speed,-space,-debug --addrqual=ignore --mode=pro -P -N255 --warn=0 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/cs_woodmaster_400_serial_ports.p1  cs_woodmaster_400_serial_ports.c 
	@-${MV} ${OBJECTDIR}/cs_woodmaster_400_serial_ports.d ${OBJECTDIR}/cs_woodmaster_400_serial_ports.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/cs_woodmaster_400_serial_ports.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/cs_woodmaster_400_system.p1: cs_woodmaster_400_system.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/cs_woodmaster_400_system.p1.d 
	@${RM} ${OBJECTDIR}/cs_woodmaster_400_system.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=pickit3  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,-asmfile,+speed,-space,-debug --addrqual=ignore --mode=pro -P -N255 --warn=0 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/cs_woodmaster_400_system.p1  cs_woodmaster_400_system.c 
	@-${MV} ${OBJECTDIR}/cs_woodmaster_400_system.d ${OBJECTDIR}/cs_woodmaster_400_system.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/cs_woodmaster_400_system.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/cs_woodmaster_400_thermistor.p1: cs_woodmaster_400_thermistor.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/cs_woodmaster_400_thermistor.p1.d 
	@${RM} ${OBJECTDIR}/cs_woodmaster_400_thermistor.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=pickit3  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,-asmfile,+speed,-space,-debug --addrqual=ignore --mode=pro -P -N255 --warn=0 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/cs_woodmaster_400_thermistor.p1  cs_woodmaster_400_thermistor.c 
	@-${MV} ${OBJECTDIR}/cs_woodmaster_400_thermistor.d ${OBJECTDIR}/cs_woodmaster_400_thermistor.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/cs_woodmaster_400_thermistor.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/cs_woodmaster_400_thermocouple.p1: cs_woodmaster_400_thermocouple.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/cs_woodmaster_400_thermocouple.p1.d 
	@${RM} ${OBJECTDIR}/cs_woodmaster_400_thermocouple.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=pickit3  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,-asmfile,+speed,-space,-debug --addrqual=ignore --mode=pro -P -N255 --warn=0 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/cs_woodmaster_400_thermocouple.p1  cs_woodmaster_400_thermocouple.c 
	@-${MV} ${OBJECTDIR}/cs_woodmaster_400_thermocouple.d ${OBJECTDIR}/cs_woodmaster_400_thermocouple.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/cs_woodmaster_400_thermocouple.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/cs_woodmaster_400_user.p1: cs_woodmaster_400_user.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/cs_woodmaster_400_user.p1.d 
	@${RM} ${OBJECTDIR}/cs_woodmaster_400_user.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=pickit3  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,-asmfile,+speed,-space,-debug --addrqual=ignore --mode=pro -P -N255 --warn=0 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/cs_woodmaster_400_user.p1  cs_woodmaster_400_user.c 
	@-${MV} ${OBJECTDIR}/cs_woodmaster_400_user.d ${OBJECTDIR}/cs_woodmaster_400_user.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/cs_woodmaster_400_user.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/ClearStakMain.p1: ClearStakMain.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/ClearStakMain.p1.d 
	@${RM} ${OBJECTDIR}/ClearStakMain.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=pickit3  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,-asmfile,+speed,-space,-debug --addrqual=ignore --mode=pro -P -N255 --warn=0 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/ClearStakMain.p1  ClearStakMain.c 
	@-${MV} ${OBJECTDIR}/ClearStakMain.d ${OBJECTDIR}/ClearStakMain.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/ClearStakMain.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/ClearStakStateMachine.p1: ClearStakStateMachine.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/ClearStakStateMachine.p1.d 
	@${RM} ${OBJECTDIR}/ClearStakStateMachine.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=pickit3  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,-asmfile,+speed,-space,-debug --addrqual=ignore --mode=pro -P -N255 --warn=0 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/ClearStakStateMachine.p1  ClearStakStateMachine.c 
	@-${MV} ${OBJECTDIR}/ClearStakStateMachine.d ${OBJECTDIR}/ClearStakStateMachine.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/ClearStakStateMachine.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/ClearStakPWMInput.p1: ClearStakPWMInput.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/ClearStakPWMInput.p1.d 
	@${RM} ${OBJECTDIR}/ClearStakPWMInput.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=pickit3  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,-asmfile,+speed,-space,-debug --addrqual=ignore --mode=pro -P -N255 --warn=0 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/ClearStakPWMInput.p1  ClearStakPWMInput.c 
	@-${MV} ${OBJECTDIR}/ClearStakPWMInput.d ${OBJECTDIR}/ClearStakPWMInput.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/ClearStakPWMInput.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/ClearStakInputParser.p1: ClearStakInputParser.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/ClearStakInputParser.p1.d 
	@${RM} ${OBJECTDIR}/ClearStakInputParser.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=pickit3  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,-asmfile,+speed,-space,-debug --addrqual=ignore --mode=pro -P -N255 --warn=0 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/ClearStakInputParser.p1  ClearStakInputParser.c 
	@-${MV} ${OBJECTDIR}/ClearStakInputParser.d ${OBJECTDIR}/ClearStakInputParser.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/ClearStakInputParser.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/ClearStakSerialInput.p1: ClearStakSerialInput.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/ClearStakSerialInput.p1.d 
	@${RM} ${OBJECTDIR}/ClearStakSerialInput.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=pickit3  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,-asmfile,+speed,-space,-debug --addrqual=ignore --mode=pro -P -N255 --warn=0 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/ClearStakSerialInput.p1  ClearStakSerialInput.c 
	@-${MV} ${OBJECTDIR}/ClearStakSerialInput.d ${OBJECTDIR}/ClearStakSerialInput.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/ClearStakSerialInput.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/ClearStakDataTable.p1: ClearStakDataTable.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/ClearStakDataTable.p1.d 
	@${RM} ${OBJECTDIR}/ClearStakDataTable.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=pickit3  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,-asmfile,+speed,-space,-debug --addrqual=ignore --mode=pro -P -N255 --warn=0 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/ClearStakDataTable.p1  ClearStakDataTable.c 
	@-${MV} ${OBJECTDIR}/ClearStakDataTable.d ${OBJECTDIR}/ClearStakDataTable.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/ClearStakDataTable.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/ClearStakOutputHandler.p1: ClearStakOutputHandler.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/ClearStakOutputHandler.p1.d 
	@${RM} ${OBJECTDIR}/ClearStakOutputHandler.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=pickit3  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,-asmfile,+speed,-space,-debug --addrqual=ignore --mode=pro -P -N255 --warn=0 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/ClearStakOutputHandler.p1  ClearStakOutputHandler.c 
	@-${MV} ${OBJECTDIR}/ClearStakOutputHandler.d ${OBJECTDIR}/ClearStakOutputHandler.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/ClearStakOutputHandler.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/ClearStakSerialHandler.p1: ClearStakSerialHandler.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/ClearStakSerialHandler.p1.d 
	@${RM} ${OBJECTDIR}/ClearStakSerialHandler.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=pickit3  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,-asmfile,+speed,-space,-debug --addrqual=ignore --mode=pro -P -N255 --warn=0 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/ClearStakSerialHandler.p1  ClearStakSerialHandler.c 
	@-${MV} ${OBJECTDIR}/ClearStakSerialHandler.d ${OBJECTDIR}/ClearStakSerialHandler.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/ClearStakSerialHandler.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/ClearStakEEPROMHandler.p1: ClearStakEEPROMHandler.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/ClearStakEEPROMHandler.p1.d 
	@${RM} ${OBJECTDIR}/ClearStakEEPROMHandler.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=pickit3  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,-asmfile,+speed,-space,-debug --addrqual=ignore --mode=pro -P -N255 --warn=0 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/ClearStakEEPROMHandler.p1  ClearStakEEPROMHandler.c 
	@-${MV} ${OBJECTDIR}/ClearStakEEPROMHandler.d ${OBJECTDIR}/ClearStakEEPROMHandler.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/ClearStakEEPROMHandler.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/BiomassControlsPIDController.p1: BiomassControlsPIDController.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/BiomassControlsPIDController.p1.d 
	@${RM} ${OBJECTDIR}/BiomassControlsPIDController.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=pickit3  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,-asmfile,+speed,-space,-debug --addrqual=ignore --mode=pro -P -N255 --warn=0 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/BiomassControlsPIDController.p1  BiomassControlsPIDController.c 
	@-${MV} ${OBJECTDIR}/BiomassControlsPIDController.d ${OBJECTDIR}/BiomassControlsPIDController.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/BiomassControlsPIDController.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/cs_pdk_400_sk_vfd.p1: cs_pdk_400_sk_vfd.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/cs_pdk_400_sk_vfd.p1.d 
	@${RM} ${OBJECTDIR}/cs_pdk_400_sk_vfd.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=pickit3  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,-asmfile,+speed,-space,-debug --addrqual=ignore --mode=pro -P -N255 --warn=0 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/cs_pdk_400_sk_vfd.p1  cs_pdk_400_sk_vfd.c 
	@-${MV} ${OBJECTDIR}/cs_pdk_400_sk_vfd.d ${OBJECTDIR}/cs_pdk_400_sk_vfd.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/cs_pdk_400_sk_vfd.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/cs_woodmaster_400_wattnode.p1: cs_woodmaster_400_wattnode.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/cs_woodmaster_400_wattnode.p1.d 
	@${RM} ${OBJECTDIR}/cs_woodmaster_400_wattnode.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=pickit3  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,-asmfile,+speed,-space,-debug --addrqual=ignore --mode=pro -P -N255 --warn=0 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/cs_woodmaster_400_wattnode.p1  cs_woodmaster_400_wattnode.c 
	@-${MV} ${OBJECTDIR}/cs_woodmaster_400_wattnode.d ${OBJECTDIR}/cs_woodmaster_400_wattnode.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/cs_woodmaster_400_wattnode.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
else
${OBJECTDIR}/cs_woodmaster_400_configuration_bits.p1: cs_woodmaster_400_configuration_bits.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/cs_woodmaster_400_configuration_bits.p1.d 
	@${RM} ${OBJECTDIR}/cs_woodmaster_400_configuration_bits.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,-asmfile,+speed,-space,-debug --addrqual=ignore --mode=pro -P -N255 --warn=0 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/cs_woodmaster_400_configuration_bits.p1  cs_woodmaster_400_configuration_bits.c 
	@-${MV} ${OBJECTDIR}/cs_woodmaster_400_configuration_bits.d ${OBJECTDIR}/cs_woodmaster_400_configuration_bits.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/cs_woodmaster_400_configuration_bits.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/cs_woodmaster_400_flowmeter.p1: cs_woodmaster_400_flowmeter.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/cs_woodmaster_400_flowmeter.p1.d 
	@${RM} ${OBJECTDIR}/cs_woodmaster_400_flowmeter.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,-asmfile,+speed,-space,-debug --addrqual=ignore --mode=pro -P -N255 --warn=0 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/cs_woodmaster_400_flowmeter.p1  cs_woodmaster_400_flowmeter.c 
	@-${MV} ${OBJECTDIR}/cs_woodmaster_400_flowmeter.d ${OBJECTDIR}/cs_woodmaster_400_flowmeter.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/cs_woodmaster_400_flowmeter.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/cs_woodmaster_400_interrupts.p1: cs_woodmaster_400_interrupts.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/cs_woodmaster_400_interrupts.p1.d 
	@${RM} ${OBJECTDIR}/cs_woodmaster_400_interrupts.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,-asmfile,+speed,-space,-debug --addrqual=ignore --mode=pro -P -N255 --warn=0 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/cs_woodmaster_400_interrupts.p1  cs_woodmaster_400_interrupts.c 
	@-${MV} ${OBJECTDIR}/cs_woodmaster_400_interrupts.d ${OBJECTDIR}/cs_woodmaster_400_interrupts.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/cs_woodmaster_400_interrupts.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/cs_woodmaster_400_main.p1: cs_woodmaster_400_main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/cs_woodmaster_400_main.p1.d 
	@${RM} ${OBJECTDIR}/cs_woodmaster_400_main.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,-asmfile,+speed,-space,-debug --addrqual=ignore --mode=pro -P -N255 --warn=0 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/cs_woodmaster_400_main.p1  cs_woodmaster_400_main.c 
	@-${MV} ${OBJECTDIR}/cs_woodmaster_400_main.d ${OBJECTDIR}/cs_woodmaster_400_main.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/cs_woodmaster_400_main.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/cs_woodmaster_400_message.p1: cs_woodmaster_400_message.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/cs_woodmaster_400_message.p1.d 
	@${RM} ${OBJECTDIR}/cs_woodmaster_400_message.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,-asmfile,+speed,-space,-debug --addrqual=ignore --mode=pro -P -N255 --warn=0 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/cs_woodmaster_400_message.p1  cs_woodmaster_400_message.c 
	@-${MV} ${OBJECTDIR}/cs_woodmaster_400_message.d ${OBJECTDIR}/cs_woodmaster_400_message.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/cs_woodmaster_400_message.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/cs_woodmaster_400_oxy_sensor.p1: cs_woodmaster_400_oxy_sensor.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/cs_woodmaster_400_oxy_sensor.p1.d 
	@${RM} ${OBJECTDIR}/cs_woodmaster_400_oxy_sensor.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,-asmfile,+speed,-space,-debug --addrqual=ignore --mode=pro -P -N255 --warn=0 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/cs_woodmaster_400_oxy_sensor.p1  cs_woodmaster_400_oxy_sensor.c 
	@-${MV} ${OBJECTDIR}/cs_woodmaster_400_oxy_sensor.d ${OBJECTDIR}/cs_woodmaster_400_oxy_sensor.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/cs_woodmaster_400_oxy_sensor.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/cs_woodmaster_400_potentiometer.p1: cs_woodmaster_400_potentiometer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/cs_woodmaster_400_potentiometer.p1.d 
	@${RM} ${OBJECTDIR}/cs_woodmaster_400_potentiometer.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,-asmfile,+speed,-space,-debug --addrqual=ignore --mode=pro -P -N255 --warn=0 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/cs_woodmaster_400_potentiometer.p1  cs_woodmaster_400_potentiometer.c 
	@-${MV} ${OBJECTDIR}/cs_woodmaster_400_potentiometer.d ${OBJECTDIR}/cs_woodmaster_400_potentiometer.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/cs_woodmaster_400_potentiometer.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/cs_woodmaster_400_pwm.p1: cs_woodmaster_400_pwm.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/cs_woodmaster_400_pwm.p1.d 
	@${RM} ${OBJECTDIR}/cs_woodmaster_400_pwm.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,-asmfile,+speed,-space,-debug --addrqual=ignore --mode=pro -P -N255 --warn=0 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/cs_woodmaster_400_pwm.p1  cs_woodmaster_400_pwm.c 
	@-${MV} ${OBJECTDIR}/cs_woodmaster_400_pwm.d ${OBJECTDIR}/cs_woodmaster_400_pwm.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/cs_woodmaster_400_pwm.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/cs_woodmaster_400_serial_ports.p1: cs_woodmaster_400_serial_ports.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/cs_woodmaster_400_serial_ports.p1.d 
	@${RM} ${OBJECTDIR}/cs_woodmaster_400_serial_ports.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,-asmfile,+speed,-space,-debug --addrqual=ignore --mode=pro -P -N255 --warn=0 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/cs_woodmaster_400_serial_ports.p1  cs_woodmaster_400_serial_ports.c 
	@-${MV} ${OBJECTDIR}/cs_woodmaster_400_serial_ports.d ${OBJECTDIR}/cs_woodmaster_400_serial_ports.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/cs_woodmaster_400_serial_ports.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/cs_woodmaster_400_system.p1: cs_woodmaster_400_system.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/cs_woodmaster_400_system.p1.d 
	@${RM} ${OBJECTDIR}/cs_woodmaster_400_system.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,-asmfile,+speed,-space,-debug --addrqual=ignore --mode=pro -P -N255 --warn=0 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/cs_woodmaster_400_system.p1  cs_woodmaster_400_system.c 
	@-${MV} ${OBJECTDIR}/cs_woodmaster_400_system.d ${OBJECTDIR}/cs_woodmaster_400_system.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/cs_woodmaster_400_system.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/cs_woodmaster_400_thermistor.p1: cs_woodmaster_400_thermistor.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/cs_woodmaster_400_thermistor.p1.d 
	@${RM} ${OBJECTDIR}/cs_woodmaster_400_thermistor.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,-asmfile,+speed,-space,-debug --addrqual=ignore --mode=pro -P -N255 --warn=0 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/cs_woodmaster_400_thermistor.p1  cs_woodmaster_400_thermistor.c 
	@-${MV} ${OBJECTDIR}/cs_woodmaster_400_thermistor.d ${OBJECTDIR}/cs_woodmaster_400_thermistor.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/cs_woodmaster_400_thermistor.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/cs_woodmaster_400_thermocouple.p1: cs_woodmaster_400_thermocouple.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/cs_woodmaster_400_thermocouple.p1.d 
	@${RM} ${OBJECTDIR}/cs_woodmaster_400_thermocouple.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,-asmfile,+speed,-space,-debug --addrqual=ignore --mode=pro -P -N255 --warn=0 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/cs_woodmaster_400_thermocouple.p1  cs_woodmaster_400_thermocouple.c 
	@-${MV} ${OBJECTDIR}/cs_woodmaster_400_thermocouple.d ${OBJECTDIR}/cs_woodmaster_400_thermocouple.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/cs_woodmaster_400_thermocouple.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/cs_woodmaster_400_user.p1: cs_woodmaster_400_user.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/cs_woodmaster_400_user.p1.d 
	@${RM} ${OBJECTDIR}/cs_woodmaster_400_user.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,-asmfile,+speed,-space,-debug --addrqual=ignore --mode=pro -P -N255 --warn=0 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/cs_woodmaster_400_user.p1  cs_woodmaster_400_user.c 
	@-${MV} ${OBJECTDIR}/cs_woodmaster_400_user.d ${OBJECTDIR}/cs_woodmaster_400_user.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/cs_woodmaster_400_user.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/ClearStakMain.p1: ClearStakMain.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/ClearStakMain.p1.d 
	@${RM} ${OBJECTDIR}/ClearStakMain.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,-asmfile,+speed,-space,-debug --addrqual=ignore --mode=pro -P -N255 --warn=0 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/ClearStakMain.p1  ClearStakMain.c 
	@-${MV} ${OBJECTDIR}/ClearStakMain.d ${OBJECTDIR}/ClearStakMain.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/ClearStakMain.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/ClearStakStateMachine.p1: ClearStakStateMachine.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/ClearStakStateMachine.p1.d 
	@${RM} ${OBJECTDIR}/ClearStakStateMachine.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,-asmfile,+speed,-space,-debug --addrqual=ignore --mode=pro -P -N255 --warn=0 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/ClearStakStateMachine.p1  ClearStakStateMachine.c 
	@-${MV} ${OBJECTDIR}/ClearStakStateMachine.d ${OBJECTDIR}/ClearStakStateMachine.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/ClearStakStateMachine.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/ClearStakPWMInput.p1: ClearStakPWMInput.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/ClearStakPWMInput.p1.d 
	@${RM} ${OBJECTDIR}/ClearStakPWMInput.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,-asmfile,+speed,-space,-debug --addrqual=ignore --mode=pro -P -N255 --warn=0 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/ClearStakPWMInput.p1  ClearStakPWMInput.c 
	@-${MV} ${OBJECTDIR}/ClearStakPWMInput.d ${OBJECTDIR}/ClearStakPWMInput.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/ClearStakPWMInput.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/ClearStakInputParser.p1: ClearStakInputParser.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/ClearStakInputParser.p1.d 
	@${RM} ${OBJECTDIR}/ClearStakInputParser.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,-asmfile,+speed,-space,-debug --addrqual=ignore --mode=pro -P -N255 --warn=0 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/ClearStakInputParser.p1  ClearStakInputParser.c 
	@-${MV} ${OBJECTDIR}/ClearStakInputParser.d ${OBJECTDIR}/ClearStakInputParser.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/ClearStakInputParser.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/ClearStakSerialInput.p1: ClearStakSerialInput.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/ClearStakSerialInput.p1.d 
	@${RM} ${OBJECTDIR}/ClearStakSerialInput.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,-asmfile,+speed,-space,-debug --addrqual=ignore --mode=pro -P -N255 --warn=0 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/ClearStakSerialInput.p1  ClearStakSerialInput.c 
	@-${MV} ${OBJECTDIR}/ClearStakSerialInput.d ${OBJECTDIR}/ClearStakSerialInput.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/ClearStakSerialInput.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/ClearStakDataTable.p1: ClearStakDataTable.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/ClearStakDataTable.p1.d 
	@${RM} ${OBJECTDIR}/ClearStakDataTable.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,-asmfile,+speed,-space,-debug --addrqual=ignore --mode=pro -P -N255 --warn=0 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/ClearStakDataTable.p1  ClearStakDataTable.c 
	@-${MV} ${OBJECTDIR}/ClearStakDataTable.d ${OBJECTDIR}/ClearStakDataTable.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/ClearStakDataTable.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/ClearStakOutputHandler.p1: ClearStakOutputHandler.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/ClearStakOutputHandler.p1.d 
	@${RM} ${OBJECTDIR}/ClearStakOutputHandler.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,-asmfile,+speed,-space,-debug --addrqual=ignore --mode=pro -P -N255 --warn=0 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/ClearStakOutputHandler.p1  ClearStakOutputHandler.c 
	@-${MV} ${OBJECTDIR}/ClearStakOutputHandler.d ${OBJECTDIR}/ClearStakOutputHandler.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/ClearStakOutputHandler.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/ClearStakSerialHandler.p1: ClearStakSerialHandler.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/ClearStakSerialHandler.p1.d 
	@${RM} ${OBJECTDIR}/ClearStakSerialHandler.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,-asmfile,+speed,-space,-debug --addrqual=ignore --mode=pro -P -N255 --warn=0 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/ClearStakSerialHandler.p1  ClearStakSerialHandler.c 
	@-${MV} ${OBJECTDIR}/ClearStakSerialHandler.d ${OBJECTDIR}/ClearStakSerialHandler.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/ClearStakSerialHandler.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/ClearStakEEPROMHandler.p1: ClearStakEEPROMHandler.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/ClearStakEEPROMHandler.p1.d 
	@${RM} ${OBJECTDIR}/ClearStakEEPROMHandler.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,-asmfile,+speed,-space,-debug --addrqual=ignore --mode=pro -P -N255 --warn=0 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/ClearStakEEPROMHandler.p1  ClearStakEEPROMHandler.c 
	@-${MV} ${OBJECTDIR}/ClearStakEEPROMHandler.d ${OBJECTDIR}/ClearStakEEPROMHandler.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/ClearStakEEPROMHandler.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/BiomassControlsPIDController.p1: BiomassControlsPIDController.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/BiomassControlsPIDController.p1.d 
	@${RM} ${OBJECTDIR}/BiomassControlsPIDController.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,-asmfile,+speed,-space,-debug --addrqual=ignore --mode=pro -P -N255 --warn=0 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/BiomassControlsPIDController.p1  BiomassControlsPIDController.c 
	@-${MV} ${OBJECTDIR}/BiomassControlsPIDController.d ${OBJECTDIR}/BiomassControlsPIDController.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/BiomassControlsPIDController.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/cs_pdk_400_sk_vfd.p1: cs_pdk_400_sk_vfd.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/cs_pdk_400_sk_vfd.p1.d 
	@${RM} ${OBJECTDIR}/cs_pdk_400_sk_vfd.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,-asmfile,+speed,-space,-debug --addrqual=ignore --mode=pro -P -N255 --warn=0 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/cs_pdk_400_sk_vfd.p1  cs_pdk_400_sk_vfd.c 
	@-${MV} ${OBJECTDIR}/cs_pdk_400_sk_vfd.d ${OBJECTDIR}/cs_pdk_400_sk_vfd.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/cs_pdk_400_sk_vfd.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/cs_woodmaster_400_wattnode.p1: cs_woodmaster_400_wattnode.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/cs_woodmaster_400_wattnode.p1.d 
	@${RM} ${OBJECTDIR}/cs_woodmaster_400_wattnode.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,-asmfile,+speed,-space,-debug --addrqual=ignore --mode=pro -P -N255 --warn=0 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/cs_woodmaster_400_wattnode.p1  cs_woodmaster_400_wattnode.c 
	@-${MV} ${OBJECTDIR}/cs_woodmaster_400_wattnode.d ${OBJECTDIR}/cs_woodmaster_400_wattnode.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/cs_woodmaster_400_wattnode.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/EmbeddedThermoControl-gates-india-1.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE) --chip=$(MP_PROCESSOR_OPTION) -G -mdist/${CND_CONF}/${IMAGE_TYPE}/EmbeddedThermoControl-gates-india-1.${IMAGE_TYPE}.map  -D__DEBUG=1 --debugger=pickit3  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,-asmfile,+speed,-space,-debug --addrqual=ignore --mode=pro -P -N255 --warn=0 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"        $(COMPARISON_BUILD) --memorysummary dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml -odist/${CND_CONF}/${IMAGE_TYPE}/EmbeddedThermoControl-gates-india-1.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}     
	@${RM} dist/${CND_CONF}/${IMAGE_TYPE}/EmbeddedThermoControl-gates-india-1.${IMAGE_TYPE}.hex 
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/EmbeddedThermoControl-gates-india-1.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE) --chip=$(MP_PROCESSOR_OPTION) -G -mdist/${CND_CONF}/${IMAGE_TYPE}/EmbeddedThermoControl-gates-india-1.${IMAGE_TYPE}.map  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,-asmfile,+speed,-space,-debug --addrqual=ignore --mode=pro -P -N255 --warn=0 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"     $(COMPARISON_BUILD) --memorysummary dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml -odist/${CND_CONF}/${IMAGE_TYPE}/EmbeddedThermoControl-gates-india-1.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}     
	
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/default
	${RM} -r dist/default

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
