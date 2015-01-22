[Mesh]
  type = GeneratedMesh
  dim = 2
  nx = 20
  ny = 20
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
  active = 'T_diff mms T_time'
  [./T_time]
    type = PikaTimeDerivative
    variable = T
    property = heat_capacity
    block = 0
  [../]
  [./T_diff]
    type = MatDiffusion
    variable = T
    D_name = conductivity
    block = 0
  [../]
  [./mms]
    type = HeatEquationSourceMMS
    variable = T
    phase_variable = phi
    block = 0
    use_dphi_dt = false
    use_time_scaling = false
  [../]
  [./phi_time]
    type = PikaTimeDerivative
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
  phase = phi
  temperature = T
  reference_temperature = 263.15
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
  dt = 0.1
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
