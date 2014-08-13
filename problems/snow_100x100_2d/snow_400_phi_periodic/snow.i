[Mesh]
  type = FileMesh
  file = T_initial_0000_mesh.xdr
  dim = 2
[]

[Variables]
  active = 'phi u T'
  [./T]
  [../]
  [./u]
  [../]
  [./phi]
  [../]
  [./T_eff_y]
  [../]
  [./T_eff_x]
  [../]
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
  [./T_eff_y]
    type = HomogenizationHeatConduction
    variable = T
    component = 1
  [../]
  [./T_eff_x]
    type = HomogenizationHeatConduction
    variable = T
    component = 0
  [../]
[]

[BCs]
  [./T_hot]
    type = DirichletBC
    variable = T
    boundary = top
    value = 270
  [../]
  [./T_cold]
    type = DirichletBC
    variable = T
    boundary = bottom
    value = 268
  [../]
  [./Periodic]
    [./phi_y]
      variable = phi
      auto_direction = y
    [../]
  [../]
[]

[Postprocessors]
  active = ''
  [./k_eff_y]
    type = HomogenizedThermalConductivity
    variable = T_eff_y
    component = 1
    temp_y = T_eff_y
    temp_x = T_eff_x
  [../]
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
  l_max_its = 50
  nl_max_its = 12
  solve_type = PJFNK
  petsc_options_iname = '-pc_type -pc_hypre_type'
  petsc_options_value = 'hypre boomeramg'
  end_time = 20000
  reset_dt = true
  nl_rel_tol = 1e-07
  dtmax = 60
  nl_abs_tol = 1e-12
  [./TimeStepper]
    type = SolutionTimeAdaptiveDT
    percent_change = 0.25
    dt = 0.2
  [../]
[]

[Adaptivity]
  max_h_level = 5
  initial_marker = combo_mark
  marker = combo_mark
  initial_steps = 5
  [./Indicators]
    [./phi_grad_indicator]
      type = GradientJumpIndicator
      variable = phi
    [../]
    [./u_grad_indicator]
      type = GradientJumpIndicator
      variable = u
      block = 0
    [../]
  [../]
  [./Markers]
    active = 'combo_mark u_grad_marker phi_grad_marker'
    [./phi_grad_marker]
      type = ErrorFractionMarker
      coarsen = 0.1
      indicator = phi_grad_indicator
      refine = 0.8
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
      markers = 'phi_grad_marker u_grad_marker'
    [../]
    [./u_grad_marker]
      type = ErrorToleranceMarker
      indicator = u_grad_indicator
      coarsen = 1e-9
      refine = 5e-8
      block = 0
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
  temperature = T
  interface_thickness = 5e-6
  temporal_scaling = 1e-4
  condensation_coefficient = .01
  phase = phi
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
