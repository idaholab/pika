[Mesh]
  type = GeneratedMesh
  dim = 3
  nx = 7
  ny = 4
  nz = 7
  xmax = 0.7
  ymax = 0.4
  zmax = 0.7
[]

[Variables]
  [./T]
  [../]
[]

[AuxVariables]
  [./sw]
  [../]
[]

[Functions]
  [./shortwave]
    type = ParsedFunction
    value = SW*sin(w*pi*x)*sin(w*pi*y)
    vals = '0.7 700'
    vars = 'w SW'
  [../]
  [./longwave]
    type = ParsedFunction
    value = 235
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
    extinction = 75
    albedo = 0.78
  [../]
[]

[AuxKernels]
  [./sw_aux]
    type = FunctionAux
    variable = sw
    function = shortwave
  [../]
[]

[BCs]
  [./top]
    type = IbexSurfaceFluxBC
    variable = T
    boundary = top
    atmospheric_pressure = 100
    air_velocity = 1.3
    long_wave = 235
    relative_humidity = 10
    air_temperature = 263.15
  [../]
  [./bottom]
    type = DirichletBC
    variable = T
    boundary = bottom
    value = 263.15
  [../]
[]

[Materials]
  [./snow]
    type = IbexSnowMaterial
    block = 0
    temperature = T
  [../]
[]

[Executioner]
  # Preconditioned JFNK (default)
  type = Transient
  num_steps = 20
  dt = 60
  solve_type = PJFNK
  petsc_options_iname = '-pc_type -pc_hypre_type'
  petsc_options_value = 'hypre boomeramg'
  scheme = crank-nicolson
[]

[Adaptivity]
  max_h_level = 2
  initial_steps = 2
  marker = T_marker
  initial_marker = uniform
  [./Indicators]
    [./T_grad_indicator]
      type = GradientJumpIndicator
      variable = T
    [../]
  [../]
  [./Markers]
    [./T_marker]
      type = ErrorFractionMarker
      coarsen = 0.1
      indicator = T_grad_indicator
      refine = 0.8
    [../]
    [./uniform]
      type = BoxMarker
      bottom_left = '0 0.3 0.0'
      top_right = '0.7 0.4 0.7'
      inside = refine
      outside = do_nothing
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
  [./T_initial]
    variable = T
    type = ConstantIC
    value = 263.15
  [../]
[]

