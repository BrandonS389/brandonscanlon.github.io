/* 
 * File:   BiomassControlsPIDController.h
 * Author: David
 *
 * Created on March 13, 2016, 10:28 PM
 */

#ifndef BIOMASSCONTROLSPIDCONTROLLER_H
#define	BIOMASSCONTROLSPIDCONTROLLER_H

#ifdef	__cplusplus
extern "C" {
#endif


typedef struct PIDController {
    float processVariableSetPoint;
    float controllerGain;
    float integralTime;
    float derivativeTime;
    float error;
    float previousProcessVariable;
    float errorIntegral;
    float minControllerOutput;
    float maxControllerOutput;
    float samplingPeriod;
    float controllerOutput;
} PIDController;

PIDController PIDControllerCreate(float processVariableSetPoint, float controllerGain,
        float integralTime, float derivativeTime, float minControllerOutput, float maxControllerOutput, float samplingPeriod, float initialControllerOffset);

void PIDControllerComputeOutput(PIDController *controller, float processVariable);
#ifdef	__cplusplus
}
#endif

#endif	/* BIOMASSCONTROLSPIDCONTROLLER_H */

