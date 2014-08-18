[Mesh]
  type = GeneratedMesh
  dim = 2
  nx = 10
  ny = 10
  xmax = 0.005
  ymax = 0.005
[]

[Variables]
  active = 'u T'
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
  [./phi]
  [../]
[]

[Functions]
  [./T_func]
    type = ParsedFunction
    value = 500*y+268
  [../]
  [./phi_func]
    type = SolutionFunction
    from_variable = phi
    solution = phi_initial
  [../]
[]

[Kernels]
  active = 'vapor_time heat_diffusion vapor_diffusion'
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
[]

[Executioner]
  # Preconditioned JFNK (default)
  type = Transient
  dt = 0.01
  solve_type = PJFNK
  petsc_options_iname = '-pc_type -pc_hypre_type'
  petsc_options_value = 'hypre boomeramg'
  end_time = 1
  reset_dt = true
  dtmax = 50
  nl_abs_tol = 1e-12
  nl_rel_tol = 1e-07
  [./TimeStepper]
    type = IterationAdaptiveDT
    dt = 0.001
  [../]
[]

[Adaptivity]
  max_h_level = 10
  marker = u_grad_marker
  initial_steps = 10
  initial_marker = phi_grad_marker
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
    [./u_grad_marker]
      type = ErrorFractionMarker
      coarsen = 0.1
      indicator = u_grad_indicator
      refine = 0.8
    [../]
    [./phi_grad_marker]
      type = ErrorFractionMarker
      coarsen = 0.1
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
    type = ChemicalPotentialIC
    block = 0
    phase_variable = phi
    temperature = T
  [../]
[]

[PikaMaterials]
  temperature = 268
  interface_thickness = 1e-6
  temporal_scaling = 1e-4
  outputs = all
  condensation_coefficient = .001
  phase = phi
[]

