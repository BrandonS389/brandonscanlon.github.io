/* 
 * File:   BiomassControlsPIDController.c
 * Author: David
 *
 * Created on March 13, 2016, 10:28 PM
 */

#include "BiomassControlsPIDController.h"

#if defined(__XC)
#include <xc.h>        /* XC8 General Include File */
#elif defined(HI_TECH_C)
#include <htc.h>       /* HiTech General Include File */
#elif defined(__18CXX)
#include <p18cxxx.h>   /* C18 General Include File */
#endif

PIDController PIDControllerCreate(float processVariableSetPoint, float controllerGain,
        float integralTime, float derivativeTime, float minControllerOutput, float maxControllerOutput, float samplingPeriod , float initialControllerOffset) {
    PIDController newController;
    newController.processVariableSetPoint = processVariableSetPoint;
    newController.controllerGain = controllerGain;
    newController.integralTime = integralTime;
    newController.derivativeTime = derivativeTime;
    newController.error = 0;
    newController.previousProcessVariable = 0;
    newController.errorIntegral = initialControllerOffset;
    newController.controllerOutput = 0;
    newController.minControllerOutput = minControllerOutput;
    newController.maxControllerOutput = maxControllerOutput;
    newController.samplingPeriod = samplingPeriod;
    return newController;
}

// Non-interactive PID controller.
// Derivative on process variable, proportional and integral on error.
// With integral windup protection.
// co[n+1] = Kc * (e[n] + Ts/Ti*sum(e[n]) + Td*(pv[n]-pv[n-1])/Ts))1500 2300

void PIDControllerComputeOutput(PIDController *controller, float processVariable) {
    controller->error = controller->processVariableSetPoint - processVariable;
    if(controller->integralTime) {
        controller->errorIntegral = (1 / controller->integralTime) * controller->samplingPeriod * controller->error + controller->errorIntegral;
        controller->errorIntegral = controller->errorIntegral * controller->controllerGain < controller->minControllerOutput ? controller->minControllerOutput / controller->controllerGain : controller->errorIntegral;
        controller->errorIntegral = controller->errorIntegral * controller->controllerGain > controller->maxControllerOutput ? controller->maxControllerOutput / controller->controllerGain : controller->errorIntegral;
    }
    float derivativeComponentOutput = controller->derivativeTime*((processVariable - controller->previousProcessVariable))/controller->samplingPeriod;
    controller->controllerOutput = controller->controllerGain * (controller->error + controller->errorIntegral + derivativeComponentOutput);
    controller->previousProcessVariable = processVariable;
    controller->controllerOutput = controller->controllerOutput < controller->minControllerOutput ? controller->minControllerOutput : controller->controllerOutput;
    controller->controllerOutput = controller->controllerOutput > controller->maxControllerOutput ? controller->maxControllerOutput : controller->controllerOutput;
}