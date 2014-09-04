[Mesh]
  type = FileMesh
  file = T_initial_0000_mesh.xdr
  dim = 2
[]

[Variables]
<<<<<<< HEAD
  active = 'phi u T'
=======
>>>>>>> snow_small
  [./T]
  [../]
  [./u]
  [../]
  [./phi]
  [../]
<<<<<<< HEAD
  [./T_eff_y]
  [../]
=======
>>>>>>> snow_small
[]

[AuxVariables]
[]

[Functions]
  [./T_func]
    type = SolutionFunction
    from_variable = T
    solution = T_initial
  [../]
  [./phi_func]
    type = SolutionFunction
    solution = phi_initial
  [../]
[]

[Kernels]
<<<<<<< HEAD
  active = 'vapor_time phi_transition heat_diffusion phi_double_well heat_phi_time heat_time vapor_phi_time vapor_diffusion phi_time phi_square_gradient'
=======
>>>>>>> snow_small
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
<<<<<<< HEAD
    property = relaxation_time
=======
    property = tau
>>>>>>> snow_small
    scale = 1.0
  [../]
  [./phi_transition]
    type = PhaseTransition
    variable = phi
    mob_name = mobility
    chemical_potential = u
    coefficient = 1.0
<<<<<<< HEAD
    lambda = phase_field_coupling_constant
=======
>>>>>>> snow_small
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
<<<<<<< HEAD
  [./T_eff_y_diffusion]
    type = PikaDiffusion
    variable = T_eff_y
    use_temporal_scaling = true
    property = conductivity
  [../]
[]

[BCs]
  active = 'T_hot T_cold'
=======
[]

[BCs]
>>>>>>> snow_small
  [./T_hot]
    type = DirichletBC
    variable = T
    boundary = top
    value = 270 # -5
  [../]
  [./T_cold]
    type = DirichletBC
    variable = T
    boundary = bottom
    value = 269 # -20
  [../]
<<<<<<< HEAD
  [./T_eff_y_dirichlet]
    type = DirichletBC
    variable = T_eff_y
    boundary = bottom
    value = 263.15
  [../]
  [./T_eff_y_flux]
    type = NeumannBC
    variable = T_eff_y
    boundary = top
    value = 100
  [../]
[]

[Postprocessors]
  active = ''
  [./T_eff_x_top]
    type = SideAverageValue
    variable = T_eff_y
    boundary = top
  [../]
  [./k_eff]
    type = ThermalCond
    variable = T_eff_y
    flux = 100
    length_scale = 1
    T_hot = 263.15
    dx = 0.005
    boundary = top
  [../]
=======
[]

[Postprocessors]
>>>>>>> snow_small
[]

[UserObjects]
  [./phi_initial]
    type = SolutionUserObject
    system = aux0
    mesh = phi_initial_0001_mesh.xdr
    nodal_variables = phi_aux
    execute_on = initial
    es = phi_initial_0001.xdr
    system_variables = phi_aux
  [../]
  [./T_initial]
    type = SolutionUserObject
    mesh = T_initial_0000_mesh.xdr
    nodal_variables = T
    es = T_initial_0000.xdr
    system_variables = T
  [../]
[]

[Executioner]
  # Preconditioned JFNK (default)
  type = Transient
  solve_type = PJFNK
  petsc_options_iname = '-pc_type -pc_hypre_type'
  petsc_options_value = 'hypre boomeramg'
  end_time = 20000
  reset_dt = true
  nl_rel_tol = 1e-07
<<<<<<< HEAD
  dtmax = 60
  [./TimeStepper]
    type = SolutionTimeAdaptiveDT
    percent_change = 0.25
=======
  [./TimeStepper]
    type = SolutionTimeAdaptiveDT
    percent_change = 0.05
>>>>>>> snow_small
    dt = 1
  [../]
[]

[Adaptivity]
  max_h_level = 4
<<<<<<< HEAD
  initial_marker = combo_mark
=======
  initial_marker = u_marker
>>>>>>> snow_small
  marker = combo_mark
  initial_steps = 8
  [./Indicators]
    [./phi_grad_indicator]
      type = GradientJumpIndicator
      variable = phi
    [../]
<<<<<<< HEAD
    [./u_grad_indicator]
=======
    [./u_jump_indicator]
>>>>>>> snow_small
      type = GradientJumpIndicator
      variable = u
      block = 0
    [../]
  [../]
  [./Markers]
<<<<<<< HEAD
    active = 'combo_mark u_grad_marker phi_grad_marker'
    [./phi_grad_marker]
      type = ErrorFractionMarker
      coarsen = 0.2
      indicator = phi_grad_indicator
      refine = 0.7
=======
    active = 'combo_mark u_marker phi_grad_marker'
    [./phi_grad_marker]
      type = ErrorFractionMarker
      coarsen = .05
      indicator = phi_grad_indicator
      refine = .8
    [../]
    [./u_marker]
      type = ErrorFractionMarker
      indicator = u_jump_indicator
      refine = .8
      block = 0
      coarsen = 0.05
>>>>>>> snow_small
    [../]
    [./phi_above]
      type = ValueThresholdMarker
      variable = phi
      refine = 1.0000001
    [../]
    [./phi_below]
      type = ValueThresholdMarker
      variable = phi
      invert = true
      refine = -1.0000001
    [../]
    [./combo_mark]
      type = ComboMarker
      block = 0
<<<<<<< HEAD
      markers = 'phi_grad_marker u_grad_marker'
    [../]
    [./u_grad_marker]
      type = ErrorToleranceMarker
      indicator = u_grad_indicator
      coarsen = 1e-9
      refine = 1e-7
      block = 0
=======
      markers = 'u_marker phi_grad_marker'
>>>>>>> snow_small
    [../]
  [../]
[]

[Outputs]
  output_initial = true
  exodus = true
  checkpoint = true
  csv = true
  [./console]
    type = Console
    perf_log = true
    linear_residuals = true
    output_file = true
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
<<<<<<< HEAD
  temperature = T
  interface_thickness = 2e-5
  temporal_scaling = 1e-4
  output_properties = 'diffusion_coefficient conductivity latent_heat tau lambda'
  outputs = all
  condensation_coefficient = .001
  phase = phi
=======
  phi = phi
  temperature = T
  interface_thickness = 2e-5
  temporal_scaling = 1e-3
  output_properties = 'diffusion_coefficient conductivity latent_heat tau lambda'
  outputs = all
  condensation_coefficient = .001
>>>>>>> snow_small
[]

[PikaCriteriaOutput]
  phase = phi
  interface_velocity_postprocessors = 'average max min'
  chemical_potential = u
  air_criteria = false
  velocity_criteria = false
  time_criteria = false
  vapor_criteria = false
  use_temporal_scaling = true
  ice_criteria = false
[]

