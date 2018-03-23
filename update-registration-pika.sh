#!/bin/bash
# run this script with one or more arguments that are the directories that hold the code files for
# the objects you want to update.

dirs=$@

appname='PikaApp'

objs='
PropertyUserObject
PikaPhaseTimestepPostprocessor
PikaMaterial
TensorMobilityMaterial
IbexSnowMaterial
PikaTimeDerivative
PikaCoupledTimeDerivative
PikaDiffusion
PhaseTransition
TensorDiffusion
MassTransportSourceMMS
HeatEquationSourceMMS
PhaseEvolutionSourceMMS
MaterialUserForcingFunction
DoubleWellPotential
DoubleWellPotentialMMS
AntiTrapping
IbexShortwaveForcingFunction
PikaHomogenizedKernel
KaempferAnalyticPhaseIC
PikaChemicalPotentialIC
ErrorFunctionAux
PikaInterfaceVelocity
PikaWaterVaporConcentration
PikaSupersaturation
PikaCriteria
PikaPhaseInitializeAux
IbexSurfaceFluxBC
PikaChemicalPotentialBC
'

actions='
PikaMaterialAction setup_pika_material
PikaCriteriaAction setup_pika_criteria
'

for obj in $objs; do
    find $dirs | grep "/${obj}\.C$" | xargs perl -0777 -i'' -pe 's/(template ?<>\nInputParameters\n? ?validParams<(\w*)>\(\))/registerMooseObject\("'"$appname"'", \2\);\n\n\1/igs'
done

while read action task; do
    find $dirs | grep "/${action}\.C$" | xargs perl -0777 -i'' -pe 's/(template ?<>\nInputParameters\n? ?validParams<(\w*)>\(\))/registerMooseAction\("'"$appname"'", \2, "'"$task"'"\);\n\n\1/igs'
done <<< "$actions"
