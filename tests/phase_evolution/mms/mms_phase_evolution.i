[Mesh]
  type = GeneratedMesh
  dim = 2
<<<<<<< HEAD
  nx = 20
  ny = 20
=======
  nx = 10
  ny = 10
  elem_type = QUAD8
>>>>>>> 3fbfd84f8fad91aea639a1611852e440ccd7de63
[]

[Variables]
  [./phi]
    block = 0
  [../]
[]

[AuxVariables]
<<<<<<< HEAD
=======
  active = 'u T'
  [./abs_error]
  [../]
>>>>>>> 3fbfd84f8fad91aea639a1611852e440ccd7de63
  [./u]
    block = 0
  [../]
  [./T]
    block = 0
  [../]
[]

[Functions]
<<<<<<< HEAD
  [./u_func]
    type = ParsedFunction
    value = 0.5*sin(4.0*x*y)
  [../]
  [./T_func]
    type = ParsedFunction
    value = -10*x*y+273
=======
  [./phi_func]
    type = ParsedFunction
    value = t*sin(4*pi*x)*sin(4*pi*y)
  [../]
  [./u_func]
    type = ParsedFunction
    value = sin(4*x*y)
  [../]
  [./T_func]
    type = ParsedFunction
    value = 100*x*y
>>>>>>> 3fbfd84f8fad91aea639a1611852e440ccd7de63
  [../]
[]

[Kernels]
<<<<<<< HEAD
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
=======
>>>>>>> 3fbfd84f8fad91aea639a1611852e440ccd7de63
  [./mms]
    type = PhaseEvolutionSourceMMS
    variable = phi
    property_user_object = potential_uo
    block = 0
  [../]
<<<<<<< HEAD
=======
  [./phi_time]
    type = PikaTimeDerivative
    variable = phi
    property = tau
    block = 0
  [../]
>>>>>>> 3fbfd84f8fad91aea639a1611852e440ccd7de63
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
<<<<<<< HEAD
[]

[AuxKernels]
  [./T_kernel]
    type = FunctionAux
    variable = T
    function = T_func
    block = 0
  [../]
  [./u_kernel]
=======
  [./phi_transition]
    type = PhaseTransition
    variable = phi
    mob_name = mobility
    chemical_potential = u
    block = 0
  [../]
[]

[AuxKernels]
  active = 'T_exact u_exact'
  [./error_aux]
    type = ErrorFunctionAux
    variable = abs_error
    function = u_func
    solution_variable = u
  [../]
  [./u_exact]
>>>>>>> 3fbfd84f8fad91aea639a1611852e440ccd7de63
    type = FunctionAux
    variable = u
    function = u_func
    block = 0
  [../]
<<<<<<< HEAD
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
=======
  [./T_exact]
    type = FunctionAux
    variable = T
    function = T_func
  [../]
[]

[BCs]
  [./all]
    type = FunctionDirichletBC
    variable = phi
    boundary = 'bottom left right top'
    function = phi_func
  [../]
[]

[Materials]
  [./air]
    type = AirProperties
    block = 0
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
  [./phase_field]
>>>>>>> 3fbfd84f8fad91aea639a1611852e440ccd7de63
    type = PhaseFieldProperties
    block = 0
    phi = phi
    property_user_object = potential_uo
    temperature = T
  [../]
[]

<<<<<<< HEAD
=======
[Postprocessors]
  [./L2_errror]
    type = ElementL2Error
    variable = u
    function = u_func
  [../]
[]

>>>>>>> 3fbfd84f8fad91aea639a1611852e440ccd7de63
[UserObjects]
  [./potential_uo]
    type = ChemicalPotentialPropertyUserObject
  [../]
[]

[Executioner]
  type = Transient
  num_steps = 10
  dt = 0.1
<<<<<<< HEAD
  solve_type = PJFNK
  petsc_options_iname = '-pc_type -pc_hypre_type'
  petsc_options_value = 'hypre boomeramg'
[]

[Outputs]
  exodus = true
  [./console]
    type = Console
    linear_residuals = true
=======
[]

[Outputs]
  active = ''
  output_initial = true
  exodus = true
  console = true
  [./oversample]
    refinements = 2
    oversample = true
    type = Exodus
>>>>>>> 3fbfd84f8fad91aea639a1611852e440ccd7de63
  [../]
[]

[ICs]
<<<<<<< HEAD
  [./T_ic]
    function = T_func
    variable = T
    type = FunctionIC
    block = 0
  [../]
=======
>>>>>>> 3fbfd84f8fad91aea639a1611852e440ccd7de63
  [./u_ic]
    function = u_func
    variable = u
    type = FunctionIC
<<<<<<< HEAD
=======
  [../]
  [./phi_ic]
    function = phi_func
    variable = phi
    type = FunctionIC
  [../]
  [./T_IC]
    function = T_func
    variable = T
    type = FunctionIC
>>>>>>> 3fbfd84f8fad91aea639a1611852e440ccd7de63
    block = 0
  [../]
[]

