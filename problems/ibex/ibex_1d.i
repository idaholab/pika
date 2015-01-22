[Mesh]
  type = GeneratedMesh
  dim = 1
  nx = 100
  xmax = 0.4
  ymax = 0
  zmax = 0
[]

[Variables]
  [./T]
  [../]
[]

[Functions]
  [./shortwave]
    type = ParsedFunction
    value = 650
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
    nir_albedo = 0.80
    direction = x
    vis_albedo = 0.96
  [../]
[]

[BCs]
  [./top]
    type = IbexSurfaceFluxBC
    variable = T
    boundary = right
    long_wave = 235
    short_wave = shortwave
    air_velocity = 1.3
    relative_humidity = 15
    air_temperature = 263.15
  [../]
  [./bottom]
    type = DirichletBC
    variable = T
    boundary = left
    value = 262.65
  [../]
[]

[Materials]
  [./snow]
    type = IbexSnowMaterial
    block = 0
    temperature = T
    snow_density = 174
    thermal_conductivity = 0.1
  [../]
[]

[VectorPostprocessors]
  [./line]
    type = LineValueSampler
    variable = T
    num_points = 100
    start_point = '0 0 0'
    end_point = '0.4 0 0'
    sort_by = x
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
  end_time = 28800
  dtmax = 300
  [./TimeStepper]
    type = IterationAdaptiveDT
    dt = 30
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
    value = 262.65
  [../]
[]

