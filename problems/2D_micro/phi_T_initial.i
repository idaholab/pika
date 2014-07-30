[Mesh]
  type = GeneratedMesh
  dim = 2
  nx = 10
  ny = 10
  xmax = .005
  ymax = .005
  uniform_refine = 5
[]

[Variables]
  active = 'phi T'
  [./T]
  [../]
  [./u]
  [../]
  [./phi]
  [../]
[]

[AuxVariables]
  active = 'u'
  [./phi]
  [../]
  [./u]
  [../]
  [./T]
  [../]
[]

[Functions]
  [./phi_func]
    type = ImageFunction
    upper_value = -1
    lower_value = 1
    file = 0930_rr_rec_tra_bin__Tra1303.png
    threshold = 128
  [../]
[]

[Kernels]
  active = 'heat_diffusion phi_double_well heat_phi_time heat_time phi_time phi_square_gradient'
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
    coefficient = 1e-7
  [../]
  [./vapor_phi_time]
    type = PikaCoupledTimeDerivative
    variable = u
    coefficient = 0.5
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
  [./T_hot]
    type = DirichletBC
    variable = T
    boundary = bottom
    value = 267.515
  [../]
  [./T_cold]
    type = DirichletBC
    variable = T
    boundary = top
    value = 264.8
  [../]
[]

[Postprocessors]
[]

[UserObjects]
  [./phi_uo]
    type = SolutionUserObject
    mesh = i0930_2d_out.e
    nodal_variables = u
  [../]
[]

[Executioner]
  # Preconditioned JFNK (default)
  type = Transient
  num_steps = 20
  dt = 200
  solve_type = PJFNK
  petsc_options_iname = '-ksp_gmres_restart -pc_type -pc_hypre_type'
  petsc_options_value = '500 hypre boomeramg'
[]

[Adaptivity]
  max_h_level = 7
  marker = phi_marker
  [./Indicators]
    [./phi_grad_indicator]
      type = GradientJumpIndicator
      variable = phi
    [../]
    [./T_jump_indicator]
      type = GradientJumpIndicator
      variable = T
      block = 0
    [../]
  [../]
  [./Markers]
    active = 'phi_marker T_marker combo_marker'
    [./phi_marker]
      type = ErrorFractionMarker
      coarsen = .01
      indicator = phi_grad_indicator
      refine = .8
    [../]
    [./T_marker]
      type = ErrorFractionMarker
      coarsen = .02
      indicator = T_jump_indicator
      refine = 0.7
    [../]
    [./u_marker]
      type = ErrorFractionMarker
      indicator = u_jump_indicator
      coarsen = .02
      refine = .5
      block = 0
    [../]
    [./combo_marker]
      type = ComboMarker
      block = 0
      markers = 'T_marker phi_marker'
    [../]
  [../]
[]

[Outputs]
  output_initial = true
  exodus = true
  file_base = phi_temp_diffusion
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
    type = FunctionIC
    function = -543*y+267.515
  [../]
  [./vapor_ic]
    variable = u
    type = FunctionIC
    block = 0
    function = -4.7e-6
  [../]
  [./constant_temp_ic]
    variable = T
    type = ConstantIC
    value = 264.8
  [../]
[]

[PikaMaterials]
  phi = phi
  temperature = 263.15
  interface_thickness = 1e-5
  temporal_scaling = 1e-4
[]

