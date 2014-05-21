[Mesh]
  type = GeneratedMesh
  dim = 2
  uniform_refine = 5
[]

[Variables]
  [./V]
  [../]
[]

[AuxVariables]
  [./phi]
  [../]
[]

[Kernels]
  [./diffusion]
    type = TensorDiffusion
    variable = V
    mobility_tensor = M_tensor
    block = 0
  [../]
[]

[BCs]
  [./left]
    type = DirichletBC
    variable = V
    boundary = left
    value = 1
  [../]
  [./right]
    type = DirichletBC
    variable = V
    boundary = right
    value = -1 # V(1,y)
  [../]
[]

[Materials]
  [./mobility]
    type = TensorMobilityMaterial
    block = 0
    phi = phi
    M_2 = 0.5
    M_1 = 1
  [../]
[]

[Executioner]
  type = Steady
  solve_type = PJFNK
[]

[ICs]
  [./circle_ic]
    int_width = 0.2
    x1 = 0.5
    y1 = 0.5
    radius = 0.25
    outvalue = 1
    variable = phi
    invalue = 0
    type = SmoothCircleIC
  [../]
[]

