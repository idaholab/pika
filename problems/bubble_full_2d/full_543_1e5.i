[Mesh]
  type = FileMesh
  file = T_initial_543_1e5_0000_mesh.xdr
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
    use_temporal_scaling = true
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
  [./phi_aux_kernel]
    type = PikaPhaseInitializeAux
    variable = phi_aux
    phase = phi
  [../]
[]

[BCs]
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
[]

[Postprocessors]
[]

[UserObjects]
  [./phi_initial]
    type = SolutionUserObject
    mesh = T_initial_543_1e5_0000_mesh.xdr
    nodal_variables = phi
    es = T_initial_543_1e5_0000.xdr
    system = aux0
  [../]
  [./T_initial]
    type = SolutionUserObject
    mesh = T_initial_543_1e5_0000_mesh.xdr
    nodal_variables = T
    es = T_initial_543_1e5_0000.xdr
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
  dtmax = 50
  nl_abs_tol = 1e-13
  nl_rel_tol = 1e-07
  [./TimeStepper]
    type = SolutionTimeAdaptiveDT
    dt = 0.1
    percent_change = 0.5
  [../]
[]

[Adaptivity]
  max_h_level = 8
  marker = phi_marker
  [./Indicators]
    active = 'phi_grad_indicator'
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
    active = 'phi_marker'
    [./phi_marker]
      type = ErrorToleranceMarker
      coarsen = 1e-8
      indicator = phi_grad_indicator
      refine = 1e-7
    [../]
    [./u_marker]
      type = ErrorToleranceMarker
      coarsen = 1e-7
      indicator = u_grad_indicator
      refine = 1e-5
    [../]
    [./combo_marker]
      type = ComboMarker
      markers = 'phi_marker u_marker'
    [../]
  [../]
[]

[Outputs]
  output_initial = true
  exodus = true
  checkpoint = true
  csv = true
  file_base = full_543_1e5/out
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
  temperature = T
  interface_thickness = 1e-5
  temporal_scaling = 1e-4
  outputs = all
  condensation_coefficient = .001
  interface_kinetic_coefficient = 5.5e5
  capillary_length = 1.3e-9
  phase = phi
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

