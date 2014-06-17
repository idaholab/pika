[Mesh]
  type = GeneratedMesh
  dim = 2
  nx = 5
  ny = 5
  elem_type = QUAD4
[]

[Variables]
  [./u]
    order = FIRST
    family = LAGRANGE
  [../]
[]

[AuxVariables]
  [./phi]
  [../]
  [./abs_error]
  [../]
[]

[Functions]
  [./phi_func]
    type = ParsedFunction
    value = t*x*y
  [../]
  [./u_func]
    type = ParsedFunction
    value = t*sin(2*pi*x)*cos(2*pi*y)
  [../]
[]

[Kernels]
  active = 'u_diff u_time mms'
  [./u_time]
    type = TimeDerivative
    variable = u
  [../]
  [./u_diff]
    type = MatDiffusion
    variable = u
    D_name = diffusion_coefficient
    block = 0
  [../]
  [./mms]
    type = MassTransportSourceMMS
    variable = u
    phi = phi
    use_dphi_dt = false
  [../]
  [./phi_time]
    type = UserForcingFunction
    variable = u
    function = dphi_dt_func
  [../]
[]

[AuxKernels]
  active = 'error_aux phi_kernel'
  [./phi_kernel]
    type = FunctionAux
    variable = phi
    function = phi_func
  [../]
  [./error_aux]
    type = ErrorFunctionAux
    variable = abs_error
    function = u_func
    solution_variable = u
  [../]
  [./u_exact]
    type = FunctionAux
    variable = u_exact
    function = u_func
  [../]
[]

[BCs]
  [./all]
    type = FunctionDirichletBC
    variable = u
    boundary = 'bottom left right top'
    function = u_func
  [../]
[]

[PikaMaterials]
  phi = phi
  temperature = 273.15
[]

[Postprocessors]
  [./L2_error]
    type = ElementL2Error
    variable = u
    function = u_func
  [../]
  [./h_max]
    type = AverageElementSize
    variable = u
  [../]
[]

[Executioner]
  type = Transient
  num_steps = 5
  dt = 0.1
[]

[Outputs]
  output_initial = true
  console = true
  csv = true
[]

[ICs]
  [./u_ic]
    function = u_func
    variable = u
    type = FunctionIC
  [../]
  [./phi_ic]
    function = phi_func
    variable = phi
    type = FunctionIC
  [../]
[]
