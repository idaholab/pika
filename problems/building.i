[Mesh]
  type = GeneratedMesh
  dim = 2
  nx = 10
  ny = 10
  xmax = 0.005
  ymax = 0.005
[]

[Variables]
  [./T]
  [../]
  [./phi]
  [../]
  [./u]
  [../]
[]

[ICs]
  [./phase_ic]
    x1 = 0.0025
    y1 = 0.0025
    radius = 0.0005
    outvalue = 1
    variable = phi
    3D_spheres = false
    invalue = -1
    type = SmoothCircleIC
  [../]
  [./temperature_ic]
    variable = T
    type = ConstantIC
    value = -10
  [../]
[]

