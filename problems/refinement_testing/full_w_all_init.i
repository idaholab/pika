[Mesh]
  type = GeneratedMesh
  dim = 2
  nx = 10
  ny = 10
  xmax = 0.005
  ymax = 0.005
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
  [./vel]
    order = CONSTANT
    family = MONOMIAL
  [../]
[]

[Functions]
  [./T_func]
    type = SolutionFunction
    from_variable = T
    solution = u_T_initial
  [../]
  [./phi_func]
    type = SolutionFunction
    from_variable = phi
    solution = phi_initial
  [../]
  [./u_func]
    type = SolutionFunction
    from_variable = u
    solution = u_T_initial
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
    property = relaxation_time
    scale = 1.0
  [../]
  [./phi_transition]
    type = PhaseTransition
    variable = phi
    mob_name = mobility
    chemical_potential = u
    coefficient = 1.0
    lambda = phase_field_coupling_constant
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
  [./vel_aux]
    type = PikaInterfaceVelocity
    variable = vel
    chemical_potential = u
    phase = phi
    execute_on = 'initial timestep_begin'
  [../]
[]

[BCs]
  [./T_hot]
    type = DirichletBC
    variable = T
    boundary = top
    value = 270.5 # -5
  [../]
  [./T_cold]
    type = DirichletBC
    variable = T
    boundary = bottom
    value = 268 # -20
  [../]
[]

[Postprocessors]
[]

[UserObjects]
  [./phi_initial]
    type = SolutionUserObject
    mesh = phi_initial.e-s009
    nodal_variables = phi
  [../]
  [./u_T_initial]
    type = SolutionUserObject
    mesh = u_T_initial.e-s010
    nodal_variables = 'u T'
  [../]
[]

[Executioner]
  # Preconditioned JFNK (default)
  type = Transient
  dt = 5
  solve_type = PJFNK
  petsc_options_iname = '-pc_type -pc_hypre_type'
  petsc_options_value = 'hypre boomeramg'
  reset_dt = true
  dtmax = 20
  nl_abs_tol = 1e-12
  nl_rel_tol = 1e-07
  [./TimeStepper]
    type = SolutionTimeAdaptiveDT
    dt = 5
  [../]
[]

[Adaptivity]
  max_h_level = 10
  marker = combo_marker
  initial_steps = 10
  initial_marker = combo_marker
  [./Indicators]
    [./phi_grad_indicator]
      type = GradientJumpIndicator
      variable = phi
    [../]
    [./u_grad_indicator]
      type = GradientJumpIndicator
      variable = u
    [../]
  [../]
  [./Markers]
    [./combo_marker]
      type = ComboMarker
      markers = 'phi_grad_marker u_grad_marker'
    [../]
    [./u_grad_marker]
      type = ErrorFractionMarker
      coarsen = 0.02
      indicator = u_grad_indicator
      refine = 0.8
    [../]
    [./phi_grad_marker]
      type = ErrorFractionMarker
      coarsen = 0.02
      indicator = phi_grad_indicator
      refine = 0.8
    [../]
  [../]
[]

[Outputs]
  output_initial = true
  exodus = true
  csv = true
  file_base = u_T_initial
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
    function = phi_func
  [../]
  [./temperature_ic]
    variable = T
    type = FunctionIC
    function = T_func
  [../]
  [./vapor_ic]
    variable = u
    type = FunctionIC
    block = 0
    function = u_func
  [../]
[]

[PikaMaterials]
  temperature = 268
  interface_thickness = 1e-6
  temporal_scaling = 1e-4
  outputs = all
  condensation_coefficient = .01
  phase = phi
[]

