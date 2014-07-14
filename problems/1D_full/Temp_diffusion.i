[Mesh]
  type = FileMesh
  file = phi_diffusion_0021_mesh.xdr
  dim = 2
[]

[Variables]
  active = 'T'
  [./T]
  [../]
  [./u]
  [../]
  [./phi]
  [../]
[]

[AuxVariables]
  [./phi]
  [../]
[]

[Functions]
  [./T_func]
    type = ParsedFunction
    value = -200*x+261
  [../]
  [./phi_func]
    type = SolutionFunction
    from_variable = phi
    solution = intial_phi
  [../]
[]

[Kernels]
  active = 'heat_diffusion heat_time'
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
  active = 'T_hot T_cold'
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
[]

[Postprocessors]
[]

[UserObjects]
  [./intial_phi]
    type = SolutionUserObject
    system = nl0
    mesh = phi_diffusion_0021_mesh.xdr
    nodal_variables = phi
    es = phi_diffusion_0021.xdr
  [../]
[]

[Executioner]
  # Preconditioned JFNK (default)
  type = Transient
  num_steps = 3
  solve_type = PJFNK
  petsc_options_iname = '-ksp_gmres_restart -pc_type -pc_hypre_type'
  petsc_options_value = '500 hypre boomeramg'
  [./TimeStepper]
    type = SolutionTimeAdaptiveDT
    dt = 5
  [../]
[]

[Outputs]
  output_initial = true
  exodus = true
  file_base = temp_diffusion
  xdr = true
  [./console]
    type = Console
    perf_log = true
    nonlinear_residuals = true
    linear_residuals = true
  [../]
[]

[ICs]
  active = 'phase_ic temperature_ic'
  [./phase_ic]
    variable = phi
    type = FunctionIC
    function = phi_func
  [../]
  [./temperature_ic]
    variable = T
    type = ConstantIC
    value = 260
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
  interface_thickness = 5e-5
[]

