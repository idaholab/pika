[Mesh]
  type = GeneratedMesh
  dim = 2
  nx = 7
  ny = 8
  xmax = 0.35
  ymax = 0.4
  uniform_refine = 5
[]

[Variables]
  [./T]
  [../]
[]

[AuxVariables]
  [./k_eff]
    initial_condition = 1.1
  [../]
  [./grad_T_y]
    order = CONSTANT
    family = MONOMIAL
  [../]
  [./proc_id]
    order = CONSTANT
    family = MONOMIAL
  [../]
[]

[Functions]
  [./shortwave]
    type = ParsedFunction
    value = SW*sin(w*2*pi*x)
    vals = '650 0.7'
    vars = 'SW w'
  [../]
[]

[Kernels]
  [./T_diffusion]
    # Automatically uses "thermal_conductivity" material property
    type = HeatConduction
    variable = T
  [../]
  [./T_time]
    # Automatically uses "density" and "specfic_heat" material properties
    type = HeatConductionTimeDerivative
    variable = T
  [../]
  [./T_shortwave]
    type = IbexShortwaveForcingFunction
    variable = T
    short_wave = shortwave
    nir_albedo = 0.82
    vis_albedo = 0.96
  [../]
[]

[AuxKernels]
  [./temperature_gradient_y]
    type = VariableGradientComponent
    variable = grad_T_y
    component = y
    execute_on = 'initial timestep_end'
    gradient_variable = T
  [../]
  [./proc_id_aux]
    type = ProcessorIDAux
    variable = proc_id
  [../]
[]

[BCs]
  [./top]
    type = IbexSurfaceFluxBC
    variable = T
    boundary = top
    long_wave = 235
    short_wave = shortwave
  [../]
  [./bottom]
    type = DirichletBC
    variable = T
    boundary = bottom
    value = 264.15
  [../]
[]

[Materials]
  [./snow]
    type = IbexSnowMaterial
    block = 0
    temperature = T
    snow_density = 174
    thermal_conductivity_name = k_eff
  [../]
[]

[Executioner]
  # Preconditioned JFNK (default)
  type = Transient
  dt = 5
  solve_type = PJFNK
  petsc_options_iname = '-pc_type -pc_hypre_type'
  petsc_options_value = 'hypre boomeramg'
  scheme = crank-nicolson
  end_time = 86400
   dtmax = 60
  [./TimeStepper]
    type = IterationAdaptiveDT
    dt = 5
  [../]
[]

[Adaptivity]
  marker = marker
  max_h_level = 5
  [./Indicators]
    [./grad_indicator]
      type = GradientJumpIndicator
      variable = T
    [../]
  [../]
  [./Markers]
    [./marker]
      type = ErrorFractionMarker
      coarsen = 0.1
      indicator = grad_indicator
      refine = 0.7
    [../]
  [../]
[]

[Outputs]
  output_initial = true
  exodus = true
  csv = true
  print_linear_residuals = true
  print_perf_log = true
[]

[ICs]
  [./T_initial]
    variable = T
    type = ConstantIC
    value = 264.15
  [../]
[]

[MultiApps]
  [./micro]
    type = TransientMultiApp
    app_type = PikaApp
    positions = '0.1 0.1 0
                 0.35 0.1 0
                 0.35 0.35 0
                 0.35 0.39 0
                 0 0.39 0
                 0.1725, 0.2 0'
    input_files = micro_keff.i
  [../]
[]

[Transfers]
  [./keff_from_sub]
    type = MultiAppPostprocessorInterpolationTransfer
    direction = from_multiapp
    multi_app = micro
    variable = k_eff
    power = 1
    postprocessor = k_y_eff
  [../]
  [./T_to_sub]
    type = MultiAppVariableValueSamplePostprocessorTransfer
    direction = to_multiapp
    multi_app = micro
    source_variable = T
    postprocessor = temperature
  [../]
  [./grad_Ty_to_sub]
    type = MultiAppVariableValueSamplePostprocessorTransfer
    direction = to_multiapp
    multi_app = micro
    source_variable = grad_T_y
    postprocessor = grad_T_y
  [../]
[]
