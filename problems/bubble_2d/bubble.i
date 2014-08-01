[Mesh]
  type = FileMesh
  file = init_u_out_0010_mesh.xdr
  dim = 2
[]

[Variables]
  [./T]
  [../]
  [./u]
  [../]
  [./phi]
  [../]
[]

[AuxVariables]
  [./ss]
    order = CONSTANT
    family = MONOMIAL
  [../]
  [./v]
    order = CONSTANT
    family = MONOMIAL
  [../]
[]

[Functions]
  [./init_phi_func]
    type = SolutionFunction
    from_variable = phi
    solution = init_phi
  [../]
  [./init_T_func]
    type = SolutionFunction
    solution = init_T
  [../]
  [./init_u_func]
    type = SolutionFunction
    solution = init_u
  [../]
[]

[Kernels]
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
    use_temporal_scaling = true
    property = diffusion_coefficient
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
  [./supersaturation_aux]
    type = PikaSupersaturation
    variable = ss
    phase = phi
    chemical_potential = u
  [../]
  [./interface_velocity_aux]
    type = PikaInterfaceVelocity
    variable = v
    phase = phi
    chemical_potential = u
  [../]
[]

[BCs]
  active = 'T_hot T_cold'
  [./T_hot]
    type = DirichletBC
    variable = T
    boundary = bottom
    value = 267.15
  [../]
  [./T_cold]
    type = DirichletBC
    variable = T
    boundary = top
    value = 264.15
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

[UserObjects]
  [./init_phi]
    type = SolutionUserObject
    system = nl0
    mesh = init_phi_out_0010_mesh.xdr
    nodal_variables = phi
    execute_on = initial
    es = init_phi_out_0010.xdr
  [../]
  [./init_T]
    type = SolutionUserObject
    system = nl0
    mesh = init_T_out_0001_mesh.xdr
    nodal_variables = T
    es = init_T_out_0001.xdr
  [../]
  [./init_u]
    type = SolutionUserObject
    mesh = init_u_out_0010_mesh.xdr
    es = init_u_out_0010.xdr
    nodal_variables = u
  [../]
[]

[Executioner]
  # Preconditioned JFNK (default)
  type = Transient
  solve_type = PJFNK
  petsc_options = -
  petsc_options_iname = '-ksp_gmres_restart -pc_type -pc_hypre_type'
  petsc_options_value = '500 hypre boomeramg'
  end_time = 7200
  reset_dt = true
[]

[Adaptivity]
  max_h_level = 6
  initial_steps = 8
  initial_marker = phi_marker
  marker = phi_marker
  [./Indicators]
    [./phi_grad_indicator]
      type = GradientJumpIndicator
      variable = phi
    [../]
  [../]
  [./Markers]
    [./phi_marker]
      type = ErrorFractionMarker
      coarsen = .05
      indicator = phi_grad_indicator
      refine = .7
    [../]
  [../]
[]

[Outputs]
  output_initial = true
  exodus = true
  [./console]
    type = Console
    perf_log = true
    nonlinear_residuals = true
    linear_residuals = true
  [../]
[]

[ICs]
  [./phase_ic]
    variable = phi
    type = FunctionIC
    function = init_phi_func
  [../]
  [./temperature_ic]
    variable = T
    type = FunctionIC
    function = init_T_func
  [../]
  [./vapor_ic]
    variable = u
    type = FunctionIC
    block = 0
    function = init_u_func
  [../]
[]

[PikaMaterials]
  phi = phi
  temperature = T
  interface_thickness = 5e-6
  temporal_scaling = 1e-4
  condensation_coefficient = .001
[]

