[Mesh]
  type = GeneratedMesh
  dim = 2
  nx = 6
  ny = 6
  xmax = .002
  ymax = .002
  uniform_refine = 5
[]

[Variables]
  [./T]
  [../]
  [./u]
  [../]
  [./phi]
  [../]
  [./T_y]
    initial_condition = 268
  [../]
  [./T_x]
    initial_condition = 268
  [../]
[]

[AuxVariables]
  [./phi_aux]
  [../]
  [./T_aux]
  [../]
[]

[Functions]
  [./phi_func]
    type = SolutionFunction
    from_variable = phi
    solution = phi_initial
  [../]
  [./T_initial]
    type = ParsedFunction
    value = DT*y+T
    vals = 'temperature grad_T_y'
    vars = 'T DT'
  [../]
  [./T_constant]
    type = ParsedFunction
    value = T
    vals = temperature
    vars = T
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
  [./K_eff_y_diffusion]
    type = PikaDiffusion
    variable = T_y
    use_temporal_scaling = true
    property = conductivity
  [../]
  [./K_eff_x_diffusion]
    type = PikaDiffusion
    variable = T_x
    use_temporal_scaling = true
    property = conductivity
  [../]
[]

[AuxKernels]
  [./phi_aux_kernel]
    type = PikaPhaseInitializeAux
    variable = phi_aux
    phase = phi
  [../]
  [./func_aux]
    type = FunctionAux
    variable = T_aux
    function = T_initial
  [../]
[]

[BCs]
  [./T_hot]
    type = FunctionDirichletBC
    variable = T
    boundary = top
    function = T_initial
  [../]
  [./T_cold]
    type = FunctionDirichletBC
    variable = T
    boundary = bottom
    function = T_initial
  [../]
  [./Periodic]
    [./phi]
      variable = phi
      auto_direction = y
    [../]
  [../]
  [./T_y_hot]
    type = DirichletBC
    variable = T_y
    boundary = top
    value = 268
  [../]
  [./T_y_flux]
    type = NeumannBC
    variable = T_y
    boundary = bottom
    value = 0.5
  [../]
  [./T_x_hot]
    type = DirichletBC
    variable = T_x
    boundary = left
    value = 268
  [../]
  [./T_x_flux]
    type = NeumannBC
    variable = T_x
    boundary = right
    value = 0.5
  [../]
[]

[Postprocessors]
  [./temperature]
    type = Receiver
    default = 268
  [../]
  [./grad_T_y]
    type = Receiver
    default = 5
  [../]
  [./k_y_eff]
    type = ThermalCond
    variable = T_y
    flux = 0.5
    length_scale = 1e-4
    T_hot = 268
    dx = 0.002
    boundary = bottom
  [../]
  [./k_x_eff]
    type = ThermalCond
    variable = T_x
    flux = 0.5
    length_scale = 1e-4
    T_hot = 268
    dx = 0.002
    boundary = right
  [../]
[]

[UserObjects]
  [./phi_initial]
    type = SolutionUserObject
    mesh = phi_initial_0003_mesh.xdr
    nodal_variables = phi
    es = phi_initial_0003.xdr
  [../]
[]

[Executioner]
  # Preconditioned JFNK (default)
  type = Transient
  dt = 30
  l_max_its = 100
  solve_type = PJFNK
  petsc_options_iname = '-pc_type -pc_hypre_type'
  petsc_options_value = 'hypre boomeramg'
  end_time = 86400
  reset_dt = true
  dtmax = 100
  nl_abs_tol = 1e-12
  nl_rel_tol = 1e-07
  l_tol = 1e-04
[]

[Outputs]
  output_initial = true
  exodus = true
  csv = true
  [./console]
    type = Console
    perf_log = true
    nonlinear_residuals = true
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
    function = T_constant
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
  interface_thickness = 4e-5
  temporal_scaling = 1e-4
  condensation_coefficient = .005
  phase = phi_aux
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
  interface_velocity_postprocessors = 'max min'
[]
