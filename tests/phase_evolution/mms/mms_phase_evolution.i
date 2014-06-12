[Mesh]
  type = GeneratedMesh
  dim = 2
  nx = 20
  ny = 20
[]

[Variables]
  [./phi]
    block = 0
  [../]
[]

[AuxVariables]
  [./u]
    block = 0
  [../]
  [./T]
    block = 0
  [../]
[]

[Functions]
  [./u_func]
    type = ParsedFunction
    value = 0.5*sin(4.0*x*y)
  [../]
  [./T_func]
    type = ParsedFunction
    value = -10*x*y+273
  [../]
[]

[Kernels]
  active = 'phi_double_well phi_time'
  [./phi_time]
    type = PikaTimeDerivative
    variable = phi
    property = tau
    block = 0
  [../]
  [./phase_transition]
    type = PhaseTransition
    variable = phi
    mob_name = mobility
    chemical_potential = u
  [../]
  [./mms]
    type = PhaseEvolutionSourceMMS
    variable = phi
    property_user_object = potential_uo
    block = 0
  [../]
  [./phi_square_gradient]
    type = ACInterface
    variable = phi
    mob_name = mobility
    kappa_name = interface_thickness_squared
    block = 0
  [../]
  [./phi_double_well]
    type = PhaseFieldPotential
    variable = phi
    mob_name = mobility
    block = 0
  [../]
[]

[AuxKernels]
  [./T_kernel]
    type = FunctionAux
    variable = T
    function = T_func
    block = 0
  [../]
  [./u_kernel]
    type = FunctionAux
    variable = u
    function = u_func
    block = 0
  [../]
[]

[Materials]
  [./air_props]
    type = AirProperties
    block = 0
    property_user_object = potential_uo
    temperature = T
  [../]
  [./ice_props]
    type = IceProperties
    block = 0
    property_user_object = potential_uo
    temperature = T
  [../]
  [./constant_props]
    type = ConstantProperties
    block = 0
    property_user_object = potential_uo
  [../]
  [./phase_field_props]
    type = PhaseFieldProperties
    block = 0
    phi = phi
    property_user_object = potential_uo
    temperature = T
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
  solve_type = PJFNK
  petsc_options_iname = '-pc_type -pc_hypre_type'
  petsc_options_value = 'hypre boomeramg'
[]

[Outputs]
  exodus = true
  [./console]
    type = Console
    linear_residuals = true
  [../]
[]

[ICs]
  [./T_ic]
    function = T_func
    variable = T
    type = FunctionIC
    block = 0
  [../]
  [./u_ic]
    function = u_func
    variable = u
    type = FunctionIC
    block = 0
  [../]
[]

