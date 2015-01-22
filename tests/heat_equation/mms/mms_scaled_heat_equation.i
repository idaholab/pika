[Mesh]
  type = GeneratedMesh
  dim = 2
  nx = 15
  ny = 15
  uniform_refine = 1
  elem_type = QUAD8
[]

[Variables]
  [./T]
    order = SECOND
  [../]
[]

[AuxVariables]
  [./phi]
    order = SECOND
  [../]
  [./abs_error]
  [../]
[]

[Functions]
  [./phi_func]
    type = ParsedFunction
    value = -t*(x*y)*(x*y)
  [../]
  [./T_func]
    type = ParsedFunction
    value = t*sin(2.0*pi*x)*sin(2.0*pi*y)
  [../]
[]

[Kernels]
  [./T_time]
    type = PikaTimeDerivative
    variable = T
    property = heat_capacity
    block = 0
    scale = 1.0
  [../]
  [./T_diff]
    type = PikaScaledMatDiffusion
    variable = T
    block = 0
    diffusivity = conductivity
  [../]
  [./mms]
    type = HeatEquationSourceMMS
    variable = T
    phase_variable = phi
    block = 0
  [../]
  [./phi_time]
    type = PikaScaledTimeDerivative
    variable = T
    scale = -0.5
    differentiated_variable = phi
    property = latent_heat
  [../]
[]

[AuxKernels]
  [./phi_kernel]
    type = FunctionAux
    variable = phi
    function = phi_func
  [../]
  [./error_aux]
    type = ErrorFunctionAux
    variable = abs_error
    function = T_func
    solution_variable = T
  [../]
[]

[BCs]
  [./all]
    type = FunctionDirichletBC
    variable = T
    boundary = 'bottom left right top'
    function = T_func
  [../]
[]

[PikaMaterials]
  phi = phi
  temperature = T
  temporal_scaling = 1e-4
[]

[Postprocessors]
  [./L2_errror]
    type = ElementL2Error
    variable = T
    function = T_func
  [../]
[]

[Executioner]
  type = Transient
  num_steps = 2
  dt = .1
[]

[Outputs]
  output_initial = true
  exodus = true
  [./oversample]
    refinements = 2
    oversample = true
    type = Exodus
  [../]
[]

[ICs]
  [./T_ic]
    function = T_func
    variable = T
    type = FunctionIC
  [../]
  [./phi_ic]
    function = phi_func
    variable = phi
    type = FunctionIC
  [../]
[]

