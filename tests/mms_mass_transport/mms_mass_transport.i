[Mesh]
  type = GeneratedMesh
  dim = 2
  nx = 20
  ny = 20
[]

[Variables]
  [./u]
  [../]
[]

[AuxVariables]
  [./phi]
  [../]
  [./error]
  [../]
  [./u_exact]
  [../]
[]

[Functions]
  [./phi_func]
    type = ParsedFunction
    value = t*sin(pi*x)*cos(pi*y)
  [../]
  [./u_func]
    type = ParsedFunction
    value = exp(t)*sin(pi*x)*sin(pi*y)
  [../]
  [./dphi_dt_func]
    type = ParsedFunction
    value = 1/2*sin(pi*x)*cos(pi*y)
  [../]
[]

[Kernels]
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
  [../]
  [./phi_time]
    type = UserForcingFunction
    variable = u
    function = dphi_dt_func
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
    variable = error
    function = u_func
    error_type = percent
    solution_variable = u
  [../]
  [./u_exact]
    type = FunctionAux
    variable = u_exact
    function = u_func
  [../]
  [./D]
    type = MaterialRealAux
    variable = D
    property = diffusion_coefficient
  [../]
[]

[BCs]
  active = 'all'
  [./left]
    type = FunctionDirichletBC
    variable = u
    boundary = left
    function = u_func
  [../]
  [./right]
    type = FunctionDirichletBC
    variable = u
    boundary = right
    function = u_func
  [../]
  [./all]
    type = FunctionDirichletBC
    variable = u
    boundary = 'bottom left right top'
    function = u_func
  [../]
[]

[Materials]
  [./air]
    type = AirProperties
    block = 0
    property_user_object = potential_uo
  [../]
  [./phase]
    type = PhaseFieldProperties
    block = 0
    phi = phi
    property_user_object = potential_uo
  [../]
  [./constants]
    type = ConstantProperties
    block = 0
  [../]
  [./ice]
    type = IceProperties
    block = 0
    property_user_object = potential_uo
  [../]
[]

[Postprocessors]
  [./u_mid]
    type = PointValue
    variable = u
    point = '0.5 0.5 0'
  [../]
  [./L2_errror]
    type = ElementL2Error
    variable = u
    function = u_func
  [../]
[]

[UserObjects]
  [./potential_uo]
    type = ChemicalPotentialPropertyUserObject
  [../]
[]

[Executioner]
  type = Transient
  num_steps = 10
  dt = 0.1
[]

[Adaptivity]
[]

[Outputs]
  output_initial = true
  exodus = true
  console = true
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

