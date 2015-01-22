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
  [../]
[]

[Executioner]
  # Preconditioned JFNK (default)
  type = Transient
  dt = 300
  solve_type = PJFNK
  petsc_options_iname = '-pc_type -pc_hypre_type'
  petsc_options_value = 'hypre boomeramg'
  scheme = crank-nicolson
  end_time = 14400
  dtmax = 300
  [./TimeStepper]
    type = IterationAdaptiveDT
    dt = 30
  [../]
[]

[Adaptivity]
  max_h_level = 3
  initial_steps = 3
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

