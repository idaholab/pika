[Mesh]
  type = GeneratedMesh
  dim = 2
  nx = 7
  ny = 8
  nz = 7
  xmax = 0.35
  ymax = 0.4
  zmax = 0.35
[]

[Variables]
  [./T]
  [../]
[]

[Functions]
  [./shortwave]
    type = ParsedFunction
    value = SW*sin(w*2*pi*x)
    vals = '0.7 650'
    vars = 'w SW'
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
  [../]
[]

[AuxKernels]
[]

[BCs]
  [./top]
    type = IbexSurfaceFluxBC
    variable = T
    boundary = top
    long_wave = 235
    short_wave = 0
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
    outputs = all
    snow_density = 174
  [../]
[]

[Executioner]
  # Preconditioned JFNK (default)
  type = Transient
  dt = 60
  solve_type = PJFNK
  petsc_options_iname = '-pc_type -pc_hypre_type'
  petsc_options_value = 'hypre boomeramg'
  scheme = crank-nicolson
  end_time = 36000
  [./TimeStepper]
    type = SolutionTimeAdaptiveDT
    percent_change = 0.5
    dt = 60
  [../]
[]

[Adaptivity]
  max_h_level = 2
  initial_steps = 2
  marker = T_marker
  initial_marker = T_marker
  [./Markers]
    [./T_marker]
      type = BoxMarker
      bottom_left = '0 0.3 0'
      top_right = '0.35 .4 0.35'
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

