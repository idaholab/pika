[Mesh]
  type = FileMesh
  file = temp_initial_cp/0005_mesh.cpr
  dim = 2
[]

[Variables]
  active = 'phi u'
  [./T]
  [../]
  [./u]
  [../]
  [./phi]
  [../]
[]

[AuxVariables]
  active = 'T'
  [./phi]
  [../]
  [./u]
  [../]
  [./T]
  [../]
[]

[Functions]
  active = ''
  [./T_func]
    type = SolutionFunction
    solution = T_initial_uo
  [../]
[]

[Kernels]
  active = 'vapor_time phi_transition phi_double_well vapor_phi_time vapor_diffusion phi_time phi_square_gradient'
  [./heat_diffusion]
    type = PikaDiffusion
    variable = T
    use_temporal_scaling = true
    property = conductivity
  [../]
  [./heat_time]
    type = PikaTimeDerivative
    variable = T
    property = heat_capacity
    scale = 1.0
  [../]
  [./heat_phi_time]
    type = PikaCoupledTimeDerivative
    variable = T
    property = latent_heat
    scale = -0.5
    use_temporal_scaling = true
    coupled_variable = phi
  [../]
  [./vapor_time]
    type = PikaTimeDerivative
    variable = u
    coefficient = 1.0
    scale = 1.0
  [../]
  [./vapor_diffusion]
    type = PikaDiffusion
    variable = u
    coefficient = 1e-7
    use_temporal_scaling = true
  [../]
  [./vapor_phi_time]
    type = PikaCoupledTimeDerivative
    variable = u
    coefficient = 0.5
    coupled_variable = phi
    use_temporal_scaling = true
  [../]
  [./phi_time]
    type = PikaTimeDerivative
    variable = phi
    property = tau
    scale = 1.0
  [../]
  [./phi_transition]
    type = PhaseTransition
    variable = phi
    mob_name = mobility
    chemical_potential = u
  [../]
  [./phi_double_well]
    type = DoubleWellPotential
    variable = phi
    mob_name = mobility
  [../]
  [./phi_square_gradient]
    type = ACInterface
    variable = phi
    mob_name = mobility
    kappa_name = interface_thickness_squared
  [../]
[]

[AuxKernels]
  active = ''
  [./T_aux]
    type = FunctionAux
    variable = T
    function = T_func
  [../]
[]

[BCs]
  active = ''
  [./T_hot]
    type = DirichletBC
    variable = T
    boundary = bottom
    value = 267.515 # -5
  [../]
  [./T_cold]
    type = DirichletBC
    variable = T
    boundary = top
    value = 264.8 # -20
  [../]
  [./insulated_sides]
    type = NeumannBC
    variable = T
    boundary = 'left right'
  [../]
  [./phi_bc]
    type = DirichletBC
    variable = phi
    boundary = '0 1 2 3 '
    value = 1.0
  [../]
  [./u_bottom]
    type = DirichletBC
    variable = u
    boundary = bottom
    value = -4.7e-6
  [../]
  [./u_top]
    type = DirichletBC
    variable = u
    boundary = top
    value = 4.7e-6
  [../]
[]

[Postprocessors]
[]

[UserObjects]
  active = 'property_uo'
  [./property_uo]
    type = PropertyUserObject
  [../]
  [./T_initial_uo]
    type = SolutionUserObject
    mesh = temp_diffusion_0005_mesh.xdr
    nodal_variables = T
    execute_on = custom
    es = temp_initial_cp
  [../]
[]

[Executioner]
  # Preconditioned JFNK (default)
  type = Transient
  num_steps = 5
  dt = 10000
  solve_type = PJFNK
  petsc_options_iname = '-ksp_gmres_restart -pc_type -pc_hypre_type'
  petsc_options_value = '500 hypre boomeramg'
[]

[Adaptivity]
  max_h_level = 5
  initial_steps = 5
  initial_marker = phi_marker
  marker = phi_marker
  [./Indicators]
    active = 'phi_grad_indicator'
    [./phi_grad_indicator]
      type = GradientJumpIndicator
      variable = phi
    [../]
    [./u_jump_indicator]
      type = GradientJumpIndicator
      variable = u
      block = 0
    [../]
  [../]
  [./Markers]
    active = 'phi_marker'
    [./phi_marker]
      type = ErrorFractionMarker
      coarsen = .12
      indicator = phi_grad_indicator
      refine = .6
    [../]
    [./T_marker]
      type = ErrorFractionMarker
      coarsen = 0.2
      indicator = T_jump_indicator
      refine = 0.7
    [../]
    [./u_marker]
      type = ErrorFractionMarker
      indicator = u_jump_indicator
      coarsen = .02
      refine = .5
      block = 0
    [../]
    [./combo_mark]
      type = ComboMarker
      block = 0
      markers = 'u_marker phi_marker'
    [../]
  [../]
[]

[Outputs]
  output_initial = true
  exodus = true
  file_base = temp_diffusion
  xdr = true
  [./console]
    type = Console
    perf_log = true
    nonlinear_residuals = true
    linear_residuals = true
  [../]
[]

[ICs]
  active = 'phase_ic vapor_ic'
  [./phase_ic]
    x1 = .0025
    y1 = .0025
    radius = 0.0005
    outvalue = 1
    variable = phi
    invalue = -1
    type = SmoothCircleIC
    int_width = 5e-5
  [../]
  [./temperature_ic]
    variable = T
    type = FunctionIC
    function = -543.0*y+267.515
  [../]
  [./vapor_ic]
    variable = u
    type = ChemicalPotentialIC
    phase_variable = phi
    temperature = T
  [../]
  [./constant_temp_ic]
    variable = T
    type = ConstantIC
    value = 264.8
  [../]
  [./vapor_function_ic]
    function = -4.7e-6+0.00188*y
    variable = u
    type = FunctionIC
    block = 0
  [../]
  [./pre_solved_T]
    function = T_func_initial
    variable = T
    type = FunctionIC
  [../]
[]

[PikaMaterials]
  phi = phi
  temperature = T
  interface_thickness = 1e-5
  temporal_scaling = 1e-4
  output_properties = diffusion_coefficient
  outputs = all
[]

