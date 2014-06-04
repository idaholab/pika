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
[]

[Functions]
  [./phi_func]
    type = ParsedFunction
    value = t*sin(pi*x)*sin(pi*y)
  [../]
  [./u_func]
    type = ParsedFunction
    value = exp(t)*sin(pi*x)*sin(pi*y)
  [../]
  [./dphi_dt_func]
    type = ParsedFunction
    value = sin(pi*x)*sin(pi*y)
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
  [../]
[]

[AuxKernels]
  [./phi_kernel]
    type = FunctionAux
    variable = phi
    function = phi_func
  [../]
  [./dphi_dt]
    type = FunctionAux
    variable = phi
    function = dphi_dt_func
  [../]
[]

[BCs]
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
[]

