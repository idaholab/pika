[Mesh]
  type = FileMesh
  file = T_initial_0000_mesh.xdr
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
  [./heat_diffusion]
    type = TensorDiffusion
    variable = T
    use_temporal_scaling = true
    coefficient = 1
    mobility_tensor = tensor_conductivity
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
    coefficient = 1.0
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

[Materials]
  [./tensor_mobility_heat]
    type = TensorMobilityMaterial
    block = 0
    phi = phi
    M_2_property_name = conductivity_air
    M_1_property_name = conductivity_ice
    coefficient_name = tensor_conductivity
  [../]
[]

[Postprocessors]
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
[]

[Adaptivity]
  max_h_level = 10
  initial_marker = combo_mark
  marker = combo_mark
  initial_steps = 10
  [./Indicators]
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
    [./phi_marker]
      type = ErrorFractionMarker
      coarsen = .01
      indicator = phi_grad_indicator
      refine = .9
    [../]
    [./u_marker]
      type = ErrorFractionMarker
      indicator = u_jump_indicator
      refine = .96
      block = 0
      coarsen = 0.01
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
  checkpoint = true
  csv = true
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
  phi = phi
  temperature = T
  interface_thickness = 5e-6
  temporal_scaling = 1e-3
  output_properties = 'diffusion_coefficient conductivity latent_heat tau lambda'
  outputs = all
  condensation_coefficient = .001
[]

[PikaCriteriaOutput]
  phase = phi
  interface_velocity_postprocessors = average
  chemical_potential = u
[]

