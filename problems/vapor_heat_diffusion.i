[Mesh]
  type = GeneratedMesh
  dim = 2
  nx = 20
  ny = 20
  xmin = -1
  ymin = -1
  uniform_refine = 2
[]

[Variables]
  active = 'T'
  [./T]
  [../]
  [./u]
  [../]
[]

[AuxVariables]
  [./phi]
  [../]
[]

[Functions]
  [./phi_func]
    type = ParsedFunction
    value = -y^4+2*y^2
  [../]
[]

[Kernels]
  active = 'heat_diffusion heat_time'
  [./heat_diffusion]
    type = MatDiffusion
    variable = T
    D_name = conductivity
  [../]
  [./heat_time]
    type = PikaTimeDerivative
    variable = T
    property = heat_capacity
  [../]
  [./vapor_diffusion]
    type = MatDiffusion
    variable = u
    D_name = diffusion_coefficient
    block = 0
  [../]
  [./vapor_time]
    type = PikaTimeDerivative
    variable = u
    coefficient = 1.0
  [../]
[]

[AuxKernels]
  [./phi_aux]
    type = FunctionAux
    variable = phi
    function = phi_func
    block = 0
  [../]
[]

[BCs]
  [./T_hot]
    type = DirichletBC
    variable = T
    boundary = bottom
    value = 265
  [../]
  [./T_cold]
    type = DirichletBC
    variable = T
    boundary = top
    value = 260
  [../]
  [./insulated]
    type = NeumannBC
    variable = T
    boundary = 'left right'
  [../]
[]

[Executioner]
  type = Transient
  num_steps = 10
  end_time = 10
[]

[Adaptivity]
  max_h_level = 3
  steps = 5
  marker = T_marker
  initial_marker = T_marker
  [./Indicators]
    [./T_indic]
      type = GradientJumpIndicator
      variable = T
    [../]
  [../]
  [./Markers]
    [./T_marker]
      type = ErrorFractionMarker
      coarsen = .2
      indicator = T_indic
      refine = .7
    [../]
  [../]
[]

[Outputs]
  exodus = true
  console = false
  [./console]
    type = Console
    linear_residuals = true
  [../]
[]

[ICs]
  active = 'T_ic'
  [./u_ic]
    variable = u
    type = ConstantIC
    value = 0
  [../]
  [./T_ic]
    variable = T
    value = 260
    type = ConstantIC
    block = 0
  [../]
[]

[PikaMaterials]
  reference_temperature = 263.15
  phi = phi
  mobility = 1.0
  temperature = T
[]

