[Mesh]
  type = FileMesh
  file = phi_initial_0003_mesh.xdr
  dim = 2
  uniform_refine = 1
[]

[Variables]
  active = 'phi u T'
  [./T]
  [../]
  [./u]
  [../]
  [./phi]
  [../]
  [./T_x]
  [../]
  [./T_y]
  [../]
[]

[AuxVariables]
  [./phi_aux]
  [../]
[]

[Functions]
  [./T_func]
    type = SolutionFunction
    from_variable = T
    solution = T_initial
  [../]
  [./phi_func]
    type = SolutionFunction
    from_variable = phi
    solution = phi_initial
  [../]
[]

[Kernels]
  active = 'vapor_time phi_transition heat_diffusion phi_double_well heat_phi_time heat_time vapor_phi_time vapor_diffusion phi_time phi_square_gradient'
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
  [./homo_tx]
    type = HomogenizationHeatConduction
    variable = T_x
    component = 0
    diffusion_coefficient_name = conductivity
  [../]
  [./homo_ty]
    type = HomogenizationHeatConduction
    variable = T_y
    component = 1
    diffusion_coefficient_name = conductivity
  [../]
[]

[AuxKernels]
  [./phi_aux_kernel]
    type = PikaPhaseInitializeAux
    variable = phi_aux
    phase = phi
  [../]
[]

[BCs]
  active = 'Periodic T_hot T_cold'
  [./T_hot]
    type = DirichletBC
    variable = T
    boundary = top
    value = 260.8 # -5
  [../]
  [./T_cold]
    type = DirichletBC
    variable = T
    boundary = bottom
    value = 260 # -20
  [../]
  [./vapor_bc]
    type = ChemicalPotentialBC
    variable = u
    boundary = '0 1 2 3'
    phase_variable = phi
    temperature = T
  [../]
  [./Periodic]
    active = 'phi_periodic'
    [./phi_periodic]
      variable = phi
      auto_direction = y
    [../]
    [./Tx_periodic]
      variable = T_x
      auto_direction = 'y x'
    [../]
    [./Ty_periodic]
      variable = T_y
      auto_direction = 'x y'
    [../]
  [../]
[]

[Postprocessors]
  active = ''
  [./k_eff_x]
    type = HomogenizedThermalConductivity
    variable = T_x
    component = 0
    temp_y = T_y
    temp_x = T_x
    diffusion_coefficient_name = conductivity
  [../]
  [./k_eff_y]
    type = HomogenizedThermalConductivity
    variable = T_y
    component = 1
    temp_y = T_y
    temp_x = T_x
    diffusion_coefficient_name = conductivity
  [../]
[]

[UserObjects]
  [./phi_initial]
    type = SolutionUserObject
    mesh = phi_initial_0003_mesh.xdr
    nodal_variables = phi
    es = phi_initial_0003.xdr
  [../]
  [./T_initial]
    type = SolutionUserObject
    mesh = T_initial_0000_mesh.xdr
    nodal_variables = T
    es = T_initial_0000.xdr
  [../]
[]

[Executioner]
  # Preconditioned JFNK (default)
  type = Transient
  dt = 10
  solve_type = PJFNK
  petsc_options_iname = '-pc_type -pc_hypre_type'
  petsc_options_value = 'hypre boomeramg'
  end_time = 43200
  reset_dt = true
  dtmax = 100
  nl_abs_tol = 1e-12
  nl_rel_tol = 1e-07
[]

[Adaptivity]
  max_h_level = 4
  marker = combo_marker
  initial_marker = phi_above_marker
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
      markers = ' u_tol_marker  phi_error_marker'
    [../]
    [./u_tol_marker]
      type = ErrorToleranceMarker
      coarsen = 1e-7
      indicator = u_grad_indicator
      refine = 1e-6
    [../]
    [./phi_above_marker]
      type = ValueThresholdMarker
      variable = phi
      refine = 1.00000001
    [../]
    [./u_fraction_marker]
      type = ErrorFractionMarker
      coarsen = 0.05
      indicator = u_grad_indicator
      refine = 0.85
    [../]
    [./phi_error_marker]
      type = ErrorToleranceMarker
      coarsen = 1e-3
      indicator = phi_grad_indicator
      refine = 1e-2
    [../]
  [../]
[]

[Outputs]
  output_initial = true
  exodus = true
  csv = true
  file_base = 400_1e-5
  [./console]
    type = Console
    perf_log = true
    nonlinear_residuals = true
    linear_residuals = true
  [../]
  [./cp]
    interval = 20
    type = Checkpoint
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
  temperature = T
  interface_thickness = 1e-5
  temporal_scaling = 1e-4
  condensation_coefficient = .001
  phase = phi_aux
  output_properties = 'capillary_length beta diffusion_coefficient'
  outputs = all
[]

[PikaCriteriaOutput]
  air_criteria = false
  velocity_criteria = false
  time_criteria = false
  vapor_criteria = false
  chemical_potential = u
  phase = phi
  use_temporal_scaling = true
  ice_criteria = false
  interface_velocity_postprocessors = 'average max min'
[]

