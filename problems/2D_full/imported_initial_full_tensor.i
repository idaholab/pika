[Mesh]
  type = FileMesh
  file = phi_temp_diffusion_0010_mesh.xdr
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
  [./velocity]
    family = MONOMIAL
  [../]
[]

[Functions]
  [./T_func]
    type = SolutionFunction
    from_variable = T
    solution = initial_uo
  [../]
  [./phi_func]
    type = SolutionFunction
    from_variable = phi
    solution = initial_uo
  [../]
[]

[Kernels]
  [./heat_diffusion]
    type = TensorDiffusion
    variable = T
    use_temporal_scaling = true
    coefficient = 1.0
    mobility_tensor = conductivity_tensor
    block = 0
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
    type = TensorDiffusion
    variable = u
    use_temporal_scaling = true
    coefficient = 1.0
    mobility_tensor = diffusion_tensor
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

[AuxKernels]
  [./interface_velocity]
    type = PikaInterfaceVelocity
    variable = velocity
    phase = phi
    chemical_potential = u
  [../]
[]

[BCs]
  active = 'insulated_sides T_hot T_cold'
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

[Materials]
  [./conductivity_tensor]
    type = TensorMobilityMaterial
    block = 0
    phi = phi
    coefficient_name = conductivity_tensor
    M_2_property_name = conductivity_air
    M_1_property_name = conductivity_ice
  [../]
  [./diffusion_tensor]
    type = TensorMobilityMaterial
    block = 0
    phi = phi
    coefficient_name = diffusion_tensor
    M_2_property_name = water_vapor_diffusion_coefficient
    M_1_property_name = boltzmann
  [../]
[]

[Postprocessors]
[]

[UserObjects]
  [./initial_uo]
    type = SolutionUserObject
    system = nl0
    mesh = phi_temp_diffusion_0010_mesh.xdr
    nodal_variables = 'T phi'
    execute_on = initial
    es = phi_temp_diffusion_0010.xdr
  [../]
[]

[Executioner]
  # Preconditioned JFNK (default)
  type = Transient
  solve_type = PJFNK
  petsc_options = -
  petsc_options_iname = '-ksp_gmres_restart -pc_type -pc_hypre_type'
  petsc_options_value = '500 hypre boomeramg'
  end_time = 1000
  reset_dt = true
[]

[Adaptivity]
  max_h_level = 6
  initial_marker = u_marker
  marker = combo_mark
  initial_steps = 6
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
    active = 'phi_marker combo_mark u_marker'
    [./phi_marker]
      type = ErrorFractionMarker
      coarsen = .01
      indicator = phi_grad_indicator
      refine = .5
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
      refine = .95
      block = 0
      coarsen = .001
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
  [./console]
    type = Console
    perf_log = true
    nonlinear_residuals = true
    linear_residuals = true
  [../]
[]

[ICs]
  active = 'phase_ic vapor_ic temperature_ic'
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
  [./constant_temp_ic]
    variable = T
    type = ConstantIC
    value = 264.8
  [../]
[]

[PikaMaterials]
  phi = phi
  temperature = T
  interface_thickness = 5e-6
  temporal_scaling = 1e-4
  output_properties = 'diffusion_coefficient conductivity latent_heat tau lambda'
  outputs = all
  condensation_coefficient = .001
[]

