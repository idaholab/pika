[Mesh]
  type = FileMesh
  file = phi_diffusion_0021_mesh.xdr
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
    solution = intial_T
  [../]
  [./phi_func]
    type = SolutionFunction
    from_variable = phi
    solution = initial_phi
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
    differentiated_variable = phi
    use_temporal_scaling = true
    coupled_variable = phi
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

[BCs]
  active = 'T_hot T_cold phi_bc'
  [./T_hot]
    type = DirichletBC
    variable = T
    boundary = left
    value = 261 # -5
  [../]
  [./T_cold]
    type = DirichletBC
    variable = T
    boundary = right
    value = 260 # -20
  [../]
  [./insulated_sides]
    type = NeumannBC
    variable = T
    boundary = 'top bottom'
  [../]
  [./phi_bc]
    type = DirichletBC
    variable = phi
    boundary = 'left right'
    value = 1
  [../]
[]

[Postprocessors]
[]

[UserObjects]
  [./intial_T]
    type = SolutionUserObject
    system = nl0
    mesh = temp_diffusion_0003_mesh.xdr
    nodal_variables = T
    es = temp_diffusion_0003.xdr
  [../]
  [./initial_phi]
    type = SolutionUserObject
    system = nl0
    mesh = phi_diffusion_0021_mesh.xdr
    nodal_variables = phi
    es = phi_diffusion_0021.xdr
  [../]
[]

[Preconditioning]
  [./smp_precond]
    type = SMP
    full = true
  [../]
[]

[Executioner]
  # Preconditioned JFNK (default)
  type = Transient
  solve_type = PJFNK
  petsc_options_iname = '-ksp_gmres_restart -pc_type -pc_hypre_type'
  petsc_options_value = '100 hypre boomeramg'
  end_time = 1300
[]

[Adaptivity]
  max_h_level = 5
  initial_steps = 2
  marker = combo
  initial_marker = phi_marker
  [./Indicators]
    [./phi_grad_jump]
      type = GradientJumpIndicator
      variable = phi
    [../]
    [./u_grad_jump]
      type = GradientJumpIndicator
      variable = u
    [../]
    [./T_grad_jump]
      type = GradientJumpIndicator
      variable = T
    [../]
  [../]
  [./Markers]
    [./phi_marker]
      type = ErrorFractionMarker
      coarsen = .01
      indicator = phi_grad_jump
      refine = .6
    [../]
    [./u_marker]
      type = ErrorFractionMarker
      coarsen = .01
      indicator = u_grad_jump
      refine = 0.6
    [../]
    [./combo]
      type = ComboMarker
      markers = 'phi_marker u_marker t_marker'
    [../]
    [./t_marker]
      type = ErrorFractionMarker
      coarsen = .01
      indicator = T_grad_jump
      refine = .5
    [../]
  [../]
[]

[Outputs]
  output_initial = true
  exodus = true
  file_base = phi_diffusion
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
  interface_thickness = 8e-5
  output_properties = 'tau equilibrium_concentration heat_capacity conductivity diffusion_coefficient latent_heat lambda'
  outputs = all
  temporal_scaling = 1e-4
[]

