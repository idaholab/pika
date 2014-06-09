[Mesh]
  type = GeneratedMesh
  dim = 2
  nx = 10
  ny = 10
  elem_type = QUAD4
[]

[Variables]
  [./T]
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
    value = -t*(x*y)*(x*y)*(x*y)
  [../]
  [./T_func]
    type = ParsedFunction
    value = t*sin(2.0*pi*x)*sin(2.0*pi*y)
  [../]
[]

[Kernels]
  active = 'T_diff mms T_time'
  [./T_time]
    type = CoefficientTimeDerivative
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
    phi = phi
    use_dphi_dt = false
  [../]
  [./phi_time]
    type = MaterialUserForcingFunction
    variable = T
    material = latent_heat
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
    function = T_func
    solution_variable = T
  [../]
  [./T_exact]
    type = FunctionAux
    variable = T_exact
    function = T_func
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
  [./L2_errror]
    type = ElementL2Error
    variable = T
    function = T_func
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
  active = ''
  output_initial = true
  exodus = true
  file_base = mms_heat_equation_out
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

